"""Build, generate and verify the three practice problems without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import heapq
import itertools
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

NAMES = ["tramtiepte", "doituyen", "chiachuyen"]
ORACLE = Path(__file__).with_name("oracle")


def run(executable, data="", *args, timeout=30):
    return subprocess.run([str(executable), *map(str, args)], input=data,
                          text=True, capture_output=True, check=True,
                          timeout=timeout).stdout


def build(src):
    flags = shlex.split(os.getenv("CXXFLAGS", "-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result"))
    subprocess.run([os.getenv("CXX", "g++"), *flags, "-I", str(ROOT / "common"),
                    "-o", str(src.with_suffix("")), str(src)], check=True)


def audit_statement(p):
    text = (p / "task.md").read_text()
    assert text.splitlines()[0].startswith(f"# {p.name.upper()} — ")
    expected = ["Đề bài", "Dữ liệu vào", "Dữ liệu ra", "Ràng buộc"]
    for i in range(1, 4):
        expected.extend([f"Sample Input {i}", f"Sample Output {i}"])
    expected.append("Giải thích")
    assert re.findall(r"^### (.+)$", text, re.M) == expected
    assert len(re.findall(r"^#+ ", text, re.M)) == len(expected) + 1
    assert "Subtask" not in text
    for i in range(3):
        for label, folder, ext in [("Input", "in", "in"), ("Output", "out", "out")]:
            found = re.search(rf"### Sample {label} {i+1}\n\n```text\n(.*?)```", text, re.S)
            assert found and found[1] == (p / folder / f"example_{i:02}.{ext}").read_text()
    assert not (p / "task.html").exists()
    assert (p / "solution.md").exists()


def encode_tree(a, b, edges):
    return f"{len(a)}\n" + " ".join(map(str, a)) + "\n" + " ".join(map(str, b)) + "\n" + "".join(
        f"{u+1} {v+1} {w}\n" for u, v, w in edges)


def encode_route(n, fee, edges, s, t):
    return f"{n} {len(edges)} {s+1} {t+1}\n" + " ".join(map(str, fee)) + "\n" + "".join(
        f"{u+1} {v+1} {c} {w}\n" for u, v, c, w in edges)


def encode_partition(h, l, r, c):
    return f"{len(h)} {l} {r} {c}\n" + " ".join(map(str, h)) + "\n"


def labelled_tree(n, sequence):
    if n == 1:
        return []
    degree = [1] * n
    for u in sequence:
        degree[u] += 1
    leaves = [u for u in range(n) if degree[u] == 1]
    heapq.heapify(leaves)
    edges = []
    for u in sequence:
        v = heapq.heappop(leaves)
        edges.append((u, v))
        degree[u] -= 1
        if degree[u] == 1:
            heapq.heappush(leaves, u)
    edges.append(tuple(leaves))
    return edges


def small_cases(kind):
    rng = random.Random(20261025 + kind)
    if kind == 1:
        # All labelled trees through five vertices; random fees and symmetric ties.
        for n in range(1, 6):
            for sequence in itertools.product(range(n), repeat=max(0, n - 2)):
                raw = labelled_tree(n, sequence)
                for symmetric in (False, True):
                    edges = [(u, v, 1 if symmetric else rng.choice([1, 7, 1000])) for u, v in raw]
                    a = [1] * n if symmetric else rng.choices([0, 1, 1000], k=n)
                    b = [0] * n if symmetric else rng.choices([0, 1, 99, 10**15], k=n)
                    yield encode_tree(a, b, edges)
        for _ in range(200):
            n = rng.randint(1, 30)
            seq = [rng.randrange(n) for _ in range(max(0, n - 2))]
            edges = [(u, v, rng.randint(1, 1000)) for u, v in labelled_tree(n, seq)]
            rng.shuffle(edges)
            yield encode_tree(rng.choices([0, 1, 20, 1000], k=n),
                              rng.choices([0, 7, 200, 10**15], k=n), edges)
    elif kind == 2:
        # Every subset of directed, labelled edges on two cities, including loops.
        universe = [(u, v, c, 1) for u in range(2) for v in range(2) for c in (1, 10**9)]
        for mask in range(1 << len(universe)):
            edges = [e for i, e in enumerate(universe) if mask >> i & 1]
            for fee in ([0, 0], [3, 7]):
                yield encode_route(2, fee, edges, 0, 1)
        for _ in range(250):
            n = rng.randint(1, 9)
            edges = [(rng.randrange(n), rng.randrange(n), rng.choice([1, 2, 10**9]),
                      rng.choice([1, 3, 10**9])) for _ in range(rng.randint(0, 40))]
            yield encode_route(n, rng.choices([0, 2, 10**9], k=n), edges,
                               rng.randrange(n), rng.randrange(n))
    else:
        # Every binary-height sequence through length five and every [L,R].
        for n in range(1, 6):
            for h in itertools.product((1, 5), repeat=n):
                for l in range(1, n + 1):
                    for r in range(l, n + 1):
                        for c in (0, 3):
                            yield encode_partition(h, l, r, c)
        for _ in range(250):
            n = rng.randint(1, 45)
            l = rng.randint(1, n)
            r = rng.randint(l, n)
            yield encode_partition(rng.choices([1, 2, 5, 10**9], k=n), l, r,
                                   rng.choice([0, 1, 7, 10**9]))


def differential_checks(p, kind):
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
    bad = ["", "0\n", "200001\n", sample + "0\n", sample.rsplit("\n", 2)[0] + "\n"]
    if kind == 1:
        bad.extend([encode_tree([-1], [0], []), encode_tree([1001], [0], []),
                    encode_tree([0], [10**15 + 1], []), encode_tree([0], [-1], [])])
        for edges in [[(0, 0, 1), (1, 2, 1)], [(0, 1, 1), (1, 0, 1)],
                      [(0, 3, 1), (0, 1, 1)], [(0, 1, 0), (1, 2, 1)],
                      [(0, 1, 1001), (1, 2, 1)]]:
            bad.append(encode_tree([0] * 3, [0] * 3, edges))
        bad.append(encode_tree([0] * 4, [0] * 4, [(0, 1, 1), (1, 2, 1), (2, 0, 1)]))
    elif kind == 2:
        bad.extend(["1 -1 1 1\n0\n", "1 200001 1 1\n0\n",
                    "1 0 0 1\n0\n", "1 0 1 2\n0\n",
                    "1 0 1 1\n-1\n", "1 0 1 1\n1000000001\n"])
        for e in [(0, 1, 0, 1), (0, 1, 1, 0), (0, 2, 1, 1),
                  (0, 1, 10**9 + 1, 1), (0, 1, 1, 10**9 + 1)]:
            bad.append(encode_route(2, [0, 0], [e], 0, 1))
    else:
        bad.extend([encode_partition([1, 2], 0, 2, 0), encode_partition([1, 2], 2, 1, 0),
                    encode_partition([1, 2], 1, 3, 0), encode_partition([1], 1, 1, -1),
                    encode_partition([1], 1, 1, 10**9 + 1), encode_partition([0], 1, 1, 0),
                    encode_partition([10**9 + 1], 1, 1, 0)])
    for data in bad:
        result = subprocess.run([str(p / "verifier")], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p.name, "Accepted invalid input", data)
    return len(bad)


def checker_checks(p):
    count = 0
    with tempfile.TemporaryDirectory() as directory:
        directory = Path(directory)
        actual, answer = directory / "actual", directory / "answer"
        for case in ("example_00", "example_01", "max_00"):
            inp = p / "in" / f"{case}.in"
            good = (p / "out" / f"{case}.out").read_text()
            answer.write_text(good)
            words = good.split()
            variants = [(good, True), (" \n\t" + good.strip() + " \t\n", True),
                        ("", False), (good + "0\n", False), (good + "x\n", False),
                        ("x\n", False), ("1.0\n", False), ("9" * 50 + "\n", False)]
            for i in range(len(words)):
                wrong = words.copy()
                wrong[i] = str(int(wrong[i]) + 1)
                variants.append((" ".join(wrong) + "\n", False))
            if len(words) > 1:
                variants.append((words[0] + "\n", False))
            for data, accepted in variants:
                actual.write_text(data)
                result = subprocess.run([str(p / "checker"), str(inp), str(actual), str(answer)],
                                        capture_output=True)
                assert (result.returncode == 0) == accepted, (p.name, data, result.stderr)
                count += 1
    return count


def generated_checks(problem, kind):
    p = problem.basedir
    files = sorted((p / "in").glob("*.in"))
    assert len(files) == sum(test["number"] for test in problem.config["tests"])
    for path in files:
        try:
            expected = run(ORACLE, path.read_text(), kind, timeout=90).split()
        except subprocess.CalledProcessError as error:
            raise AssertionError((str(path), error.stderr)) from error
        actual = (p / "out" / path.with_suffix(".out").name).read_text().split()
        assert expected == actual, (path, expected, actual)
    for test in problem.config["tests"]:
        if not test["name"].endswith(".cpp"):
            continue
        name = Path(test["name"]).stem
        original = (p / "in" / f"{name}_00.in").read_text()
        assert run(p / "gen" / name, "", 0) == original, (p.name, "Nondeterministic generator", name)
    if p.name == "doituyen":
        cases = [(0, "different_lines", 1000000002), (1, "same_line", 2),
                 (2, "self_loops", 1), (5, "hub_self_loops", 2000000001)]
        for seed, name, answer in cases:
            stem = f"stress_{seed:02}"
            original = (p / "in" / f"{stem}.in").read_text()
            assert run(p / "gen/stress", "", seed) == original
            assert original == (p / "tests/counterexamples" / f"{name}.in").read_text()
            assert int((p / "out" / f"{stem}.out").read_text()) == answer
        for seed, answer in [(3, 1000000102), (4, 2000000002)]:
            stem = f"stress_{seed:02}"
            data = (p / "in" / f"{stem}.in").read_text()
            assert run(p / "gen/stress", "", seed) == data
            rows = data.splitlines()
            n, m, s, t = map(int, rows[0].split())
            assert n == 133334 and m == 199998 and s != t
            pairs = set()
            for row in rows[2:]:
                u, v, _, _ = map(int, row.split())
                assert u != v and (u, v) not in pairs
                pairs.add((u, v))
            assert len(pairs) == m
            assert int((p / "out" / f"{stem}.out").read_text()) == answer
    return len(files)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--problem", nargs="+", choices=NAMES, default=NAMES)
    parser.add_argument("--update-hashes", action="store_true")
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format="%(message)s")
    problems = [Problem(ROOT, ROOT / "custom" / name) for name in args.problem]
    sources = [ORACLE.with_suffix(".cpp")]
    for problem in problems:
        problem.health_check()
        problem.generate_params_h()
        p = problem.basedir
        sources.extend([p / "sol/correct.cpp", problem.verifier, problem.checker])
        sources.extend(p / "gen" / test["name"] for test in problem.config["tests"]
                       if test["name"].endswith(".cpp"))
    print(f"Compiling {len(sources)} programs...", flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        list(pool.map(build, sources))
    for problem in problems:
        started = time.monotonic()
        p = problem.basedir
        kind = NAMES.index(p.name) + 1
        problem.make_inputs()
        problem.verify_inputs()
        problem.make_outputs(True)
        problem.judge(p / "sol/correct.cpp", {})
        assert problem.check_all_solutions_used()
        audit_statement(p)
        generated = generated_checks(problem, kind)
        print(f"{p.name}: {generated} generated cases match independent oracles; checking small cases...", flush=True)
        small = differential_checks(p, kind)
        invalid = invalid_checks(p, kind)
        checker = checker_checks(p)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        print(f"{p.name}: PASS; {generated} generated, {small} differential, "
              f"{invalid} invalid-input, {checker} checker checks; hashes verified; "
              f"{time.monotonic()-started:.1f}s", flush=True)


if __name__ == "__main__":
    main()
