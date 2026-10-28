"""Generate and verify advanced practice problems and 30/30/40 scoring, without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import json
import logging
import os
from pathlib import Path
import random
import re
import shlex
import subprocess
import sys
import tempfile
import time

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from problem import Problem

NAMES = ["mangdong", "matma", "tachlo"]
ORACLE = Path(__file__).with_name("oracle")


def run(executable, data="", *args, timeout=90):
    return subprocess.run([str(executable), *map(str, args)], input=data, text=True,
                          capture_output=True, check=True, timeout=timeout).stdout


def build(src):
    flags = shlex.split(os.getenv("CXXFLAGS", "-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result"))
    subprocess.run([os.getenv("CXX", "g++"), *flags, "-I", str(ROOT / "common"),
                    "-o", str(src.with_suffix("")), str(src)], check=True)


def membership(name, data):
    lines = data.splitlines()
    if name == "mangdong":
        n, q = map(int, lines[0].split())
        return n <= 2000 and q <= 2000, not any(line.startswith("-") for line in lines[2:])
    if name == "matma":
        _, length = map(int, lines[0].split())
        return length <= 10, length <= 100000
    n, _ = map(int, lines[0].split())
    return n <= 200, n <= 3000


def audit_scoring(problem, update):
    p = problem.basedir
    groups = {1: [], 2: [], 3: []}
    for test in problem.config["tests"]:
        stem = Path(test["name"]).stem
        for i in range(test["number"]):
            case = f"{stem}_{i:02}"
            data = (p / "in" / f"{case}.in").read_text()
            one, two = membership(p.name, data)
            if stem.startswith("sub"):
                group = int(stem[-1])
            else:
                group = 1 if one else 2 if two else 3
            assert group != 1 or one, (p.name, case, "violates subtask 1")
            assert group != 2 or two, (p.name, case, "violates subtask 2")
            groups[group].append(case)
    cases = []
    for group, points in [(1, 30), (2, 30), (3, 40)]:
        assert groups[group]
        cases.append({"type": "S", "points": points})
        for case in groups[group]:
            cases.append({"input_file": f"{case}.in", "output_file": f"{case}.out"})
        cases.append({"type": "E"})
    manifest = {"checker": "standard", "cases": cases}
    path = p / "manifest.json"
    if update:
        path.write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + "\n")
    assert json.loads(path.read_text()) == manifest
    configured_manifest = problem.config.get("upload", {}).get("manifest")
    assert configured_manifest is None or configured_manifest == "manifest.json"
    return "/".join(str(len(groups[g])) for g in (1, 2, 3))


def audit_statement(p):
    text = (p / "task.md").read_text()
    assert text.splitlines()[0].startswith(f"# {p.name.upper()} — ")
    expected = ["Đề bài", "Dữ liệu vào", "Dữ liệu ra", "Ràng buộc", "Subtask"]
    for i in range(1, 4):
        expected += [f"Sample Input {i}", f"Sample Output {i}"]
    expected.append("Giải thích")
    assert re.findall(r"^### (.+)$", text, re.M) == expected
    assert len(re.findall(r"^#+ ", text, re.M)) == len(expected) + 1
    rows = re.findall(r"^\| ([123]) \| (\d+)% \| (.+) \|$", text, re.M)
    assert [row[:2] for row in rows] == [("1", "30"), ("2", "30"), ("3", "40")]
    assert rows[-1][2] == "Không có ràng buộc bổ sung"
    assert "| Subtask | Tỉ lệ | Ràng buộc bổ sung |" in text
    for i in range(3):
        for label, folder, ext in [("Input", "in", "in"), ("Output", "out", "out")]:
            match = re.search(rf"### Sample {label} {i+1}\n\n```text\n(.*?)```", text, re.S)
            assert match and match[1] == (p / folder / f"example_{i:02}.{ext}").read_text()
    assert (p / "solution.md").exists()
    assert not list(p.glob("*.html"))


def network_data(n, colors, ops):
    return f"{n} {len(ops)}\n" + " ".join(map(str, colors)) + "\n" + "\n".join(ops) + "\n"


def message_data(patterns, length):
    return f"{len(patterns)} {length}\n" + "".join(f"{s} {w}\n" for s, w in patterns)


def batch_data(a, k):
    return f"{len(a)} {k}\n" + " ".join(map(str, a)) + "\n"


def small_cases(kind):
    rng = random.Random(20261027 + kind)
    if kind == 1:
        for n, depth in [(2, 6), (3, 3)]:
            edges = list(itertools.combinations(range(1, n + 1), 2))
            for choices in itertools.product(range(len(edges) + 1), repeat=depth):
                if 0 not in choices:
                    continue
                for colors in itertools.product((0, 1), repeat=n):
                    ops, active = [], set()
                    for choice in choices:
                        if choice == 0:
                            ops.append("?")
                        else:
                            u, v = edges[choice - 1]
                            key = (u, v)
                            remove = key in active
                            ops.append(f"{'-' if remove else '+'} {v} {u}")
                            if remove:
                                active.remove(key)
                            else:
                                active.add(key)
                    yield network_data(n, colors, ops)
        edges = [(1, 2), (2, 3), (1, 3)]
        for order in itertools.permutations(edges):
            for removed in edges:
                other = next(e for e in edges if e != removed)
                ops = [f"+ {u} {v}" for u, v in order] + ["?", f"- {removed[0]} {removed[1]}",
                      "?", f"- {other[0]} {other[1]}", "?", f"+ {removed[1]} {removed[0]}", "?"]
                for colors in itertools.product((0, 1), repeat=3):
                    yield network_data(3, colors, ops)
        for _ in range(180):
            n = rng.randint(1, 12)
            edges = list(itertools.combinations(range(1, n + 1), 2))
            active, ops = set(), []
            for _ in range(rng.randint(1, 70)):
                if not edges or rng.random() < .4:
                    ops.append("?")
                else:
                    edge = rng.choice(edges)
                    remove = edge in active
                    u, v = edge
                    if rng.randrange(2):
                        u, v = v, u
                    ops.append(f"{'-' if remove else '+'} {u} {v}")
                    if remove:
                        active.remove(edge)
                    else:
                        active.add(edge)
            ops.append("?")
            yield network_data(n, rng.choices((0, 1), k=n), ops)
    elif kind == 2:
        for pattern in ("a", "b", "c", "aa", "ba", "aba"):
            for weight in (-2, 0, 3):
                for length in range(1, 7):
                    yield message_data([(pattern, weight)], length)
        for s, t in itertools.combinations_with_replacement(("a", "aa", "ba", "aba"), 2):
            for a, b in itertools.product((-2, 0, 3), repeat=2):
                for length in (2, 5):
                    yield message_data([(s, a), (t, b)], length)
        for weights in itertools.product((-3, 0, 2), repeat=3):
            yield message_data(list(zip("abc", weights)), 4)
        for i in range(240):
            patterns = []
            for _ in range(rng.randint(1, 8)):
                patterns.append(("".join(rng.choices("abc", k=rng.randint(1, 5))), rng.randint(-10, 10)))
            yield message_data(patterns, rng.randint(1, 7) if i < 180 else rng.randint(9, 30))
    else:
        for n in range(1, 7):
            for a in itertools.product(range(1, min(2, n) + 1), repeat=n):
                for k in range(1, n + 1):
                    yield batch_data(a, k)
        for _ in range(240):
            n = rng.randint(1, 45)
            yield batch_data(rng.choices(range(1, min(n, 7) + 1), k=n), rng.randint(1, min(n, 20)))


def differential(p, kind):
    count = 0
    for data in small_cases(kind):
        run(p / "verifier", data)
        expected = run(ORACLE, data, kind).split()
        actual = run(p / "sol/correct", data).split()
        assert actual == expected, (p.name, data, expected, actual)
        count += 1
    return count


def invalid_checks(p, kind):
    sample = (p / "gen/example_00.in").read_text()
    bad = ["", sample + "0\n", sample.rsplit("\n", 2)[0] + "\n"]
    if kind == 1:
        bad += ["0 1\n\n?\n", "200001 1\n", "1 0\n0\n", "1 200001\n0\n",
                network_data(1, [2], ["?"]), network_data(2, [0, 1], ["+ 1 2"]),
                network_data(2, [0, 1], ["- 1 2", "?"]),
                network_data(2, [0, 1], ["+ 1 2", "+ 2 1", "?"]),
                network_data(2, [0, 1], ["+ 1 1", "?"]),
                network_data(2, [0, 1], ["+ 0 2", "?"]),
                network_data(2, [0, 1], ["+ 1 3", "?"]), network_data(1, [0], ["!"])]
    elif kind == 2:
        bad += ["0 1\n", "21 1\n", message_data([("a", 0)], 0),
                message_data([("a", 0)], 10**12+1), message_data([("a", 1001)], 1),
                message_data([("a", -1001)], 1), message_data([("d", 0)], 1),
                message_data([("A", 0)], 1), message_data([("a"*81, 0)], 1),
                message_data([("a"*27, 0), ("b"*27, 0), ("c"*27, 0)], 1)]
    else:
        bad += ["0 1\n", "100001 1\n", batch_data([1], 0), batch_data([1], 2),
                batch_data([1]*21, 21), batch_data([0], 1), batch_data([2], 1)]
    for data in bad:
        result = subprocess.run([str(p / "verifier")], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p.name, "Accepted invalid input", data)
    return len(bad)


def checker_checks(p):
    count = 0
    with tempfile.TemporaryDirectory() as directory:
        actual, answer = Path(directory) / "actual", Path(directory) / "answer"
        for case in ("example_00", "example_01", "sub3_00"):
            inp = p / "in" / f"{case}.in"
            good = (p / "out" / f"{case}.out").read_text()
            answer.write_text(good)
            words = good.split()
            variants = [(good, True), (" \n\t" + good.strip() + " \t\n", True), ("", False),
                        (good + "0\n", False), (good + "x\n", False), ("x\n", False),
                        ("1.0\n", False), ("9"*50 + "\n", False)]
            for i in sorted({0, len(words)-1}):
                wrong = words.copy(); wrong[i] = str(int(wrong[i]) + 1)
                variants.append(("\n".join(wrong) + "\n", False))
            if len(words) > 1:
                variants.append(("\n".join(words[:-1]) + "\n", False))
            for data, accepted in variants:
                actual.write_text(data)
                result = subprocess.run([str(p / "checker"), str(inp), str(actual), str(answer)], capture_output=True)
                assert (result.returncode == 0) == accepted, (p.name, data, result.stderr)
                count += 1
    return count


def generated_checks(problem, kind):
    p = problem.basedir
    files = sorted((p / "in").glob("*.in"))
    assert len(files) == sum(test["number"] for test in problem.config["tests"])
    for index, path in enumerate(files, 1):
        try:
            expected = run(ORACLE, path.read_text(), kind).split()
        except subprocess.CalledProcessError as error:
            raise AssertionError((str(path), error.stderr)) from error
        actual = (p / "out" / path.with_suffix(".out").name).read_text().split()
        assert actual == expected, (str(path), expected[:10], actual[:10])
        if index % 10 == 0:
            print(f"{p.name}: oracle checked {index}/{len(files)} official tests", flush=True)
    for test in problem.config["tests"]:
        if test["name"].endswith(".cpp"):
            name = Path(test["name"]).stem
            assert run(p / "gen" / name, "", 0) == (p / "in" / f"{name}_00.in").read_text()
    if p.name == "mangdong":
        for seed, name, answer, queries in [(0, "blue_chain", 100000, 2),
                                            (1, "mixed_large_pairs", 3200000000, 3),
                                            (2, "rollback_cycles", 99500, 501)]:
            stem = f"stress_{seed:02}"
            data = (p / "in" / f"{stem}.in").read_text()
            assert run(p / "gen/stress", "", seed) == data
            assert data == (p / "tests/counterexamples" / f"{name}.in").read_text()
            values = list(map(int, (p / "out" / f"{stem}.out").read_text().split()))
            expected = [answer] * queries
            if seed == 2:
                expected[-1] = 0
            assert values == expected
    return len(files)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--problem", nargs="+", choices=NAMES, default=NAMES)
    parser.add_argument("--update-hashes", action="store_true")
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format="%(message)s")
    problems = []
    for name in args.problem:
        paths = [ROOT / "dtqg" / name, ROOT / "custom" / name]
        basedir = next((path for path in paths if (path / "info.toml").is_file()), None)
        assert basedir is not None, f"Cannot locate problem {name}"
        problems.append(Problem(ROOT, basedir))
    sources = [ORACLE.with_suffix(".cpp")]
    for problem in problems:
        problem.health_check(); problem.generate_params_h()
        sources += [problem.get_correct_filename(), problem.verifier, problem.checker]
        sources += [problem.basedir / "gen" / t["name"] for t in problem.config["tests"] if t["name"].endswith(".cpp")]
    print(f"Compiling {len(sources)} programs...", flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        list(pool.map(build, sources))
    for problem in problems:
        started = time.monotonic()
        p = problem.basedir; kind = NAMES.index(p.name) + 1
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True)
        problem.judge(problem.get_correct_filename(), {})
        assert problem.check_all_solutions_used()
        audit_statement(p)
        official = generated_checks(problem, kind)
        scoring = audit_scoring(problem, args.update_hashes)
        print(f"{p.name}: checking small independent cases...", flush=True)
        small = differential(p, kind)
        invalid = invalid_checks(p, kind)
        checker = checker_checks(p)
        if args.update_hashes:
            problem.ignore_warning = True; problem.write_hashes()
        problem.assert_hashes()
        print(f"{p.name}: PASS; {official} official; {small} differential; {invalid} invalid-input; "
              f"{checker} checker tests; subtask cases {scoring}; 30/30/40 and hashes verified; "
              f"{time.monotonic()-started:.1f}s", flush=True)


if __name__ == "__main__":
    main()
