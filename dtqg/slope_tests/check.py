"""Build and verify the four slope-trick practice problems, without HTML."""
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

NAMES = ["dieuphoi", "bamtin", "ondinh", "canmang"]
ORACLE = Path(__file__).with_name("oracle")


def run(executable, data="", *args, timeout=90):
    return subprocess.run([str(executable), *map(str, args)], input=data, text=True,
                          capture_output=True, check=True, timeout=timeout).stdout


def build(src):
    flags = shlex.split(os.getenv("CXXFLAGS", "-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result"))
    subprocess.run([os.getenv("CXX", "g++"), *flags, "-I", str(ROOT / "common"),
                    "-o", str(src.with_suffix("")), str(src)], check=True)


def convoy(a, length, gap):
    data = f"{len(a)}\n" + "".join(f"{x} {l}\n" for x, l in zip(a, length))
    if gap:
        data += " ".join(map(str, gap)) + "\n"
    return data


def tracking(intervals, moves):
    return f"{len(intervals)}\n" + "".join(f"{a} {b}\n" for a, b in intervals) + "".join(
        f"{u} {v}\n" for u, v in moves)


def signal(a, w, c):
    data = f"{len(a)}\n" + "".join(f"{x} {weight}\n" for x, weight in zip(a, w))
    if c:
        data += " ".join(map(str, c)) + "\n"
    return data


def sensors(a, edges):
    return f"{len(a)}\n" + " ".join(map(str, a)) + "\n" + "".join(
        f"{u+1} {v+1} {d}\n" for u, v, d in edges)


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
    rng = random.Random(2026102700 + kind)
    if kind == 1:
        for n in range(1, 5):
            for a in itertools.product((-2, 0, 2), repeat=n):
                for length, gap in [(1, 0), (2, 1)]:
                    yield convoy(a, [length]*n, [gap]*(n-1))
        for _ in range(250):
            n = rng.randint(1, 25)
            yield convoy(rng.choices(range(-10, 11), k=n), rng.choices(range(1, 6), k=n),
                         rng.choices(range(6), k=n-1))
    elif kind == 2:
        for n in range(1, 4):
            for intervals in itertools.product([(0, 0), (2, 2), (0, 2), (-2, -1)], repeat=n):
                for variant in range(4):
                    moves = [((0, 0) if variant == 0 else (2, 0) if variant == 1 else (0, 2)
                              if variant == 2 else (1, 3) if i % 2 else (3, 1)) for i in range(n-1)]
                    yield tracking(intervals, moves)
        for _ in range(200):
            n = rng.randint(1, 25)
            intervals = [sorted([rng.randint(-8, 8), rng.randint(-8, 8)]) for _ in range(n)]
            yield tracking(intervals, [(rng.randint(0, 8), rng.randint(0, 8)) for _ in range(n-1)])
    elif kind == 3:
        for a in itertools.product((0, 2, 5), repeat=2):
            for w in itertools.product((1, 2, 7), repeat=2):
                for c in (1, 3, 8):
                    yield signal(a, w, [c])
        for a in itertools.product((0, 3), repeat=3):
            for w in itertools.product((1, 4), repeat=3):
                for c in itertools.product((1, 3), repeat=2):
                    yield signal(a, w, c)
        for a, w in itertools.product((0, 10**6), (1, 10**6)):
            yield signal([a], [w], [])
        for _ in range(250):
            n = rng.randint(1, 30)
            yield signal(rng.choices(range(9), k=n), rng.choices([1, 2, 3, 17, 10**6], k=n),
                         rng.choices([1, 2, 4, 19, 10**6], k=n-1))
    else:
        for n in range(1, 5):
            for sequence in itertools.product(range(n), repeat=max(0, n-2)):
                edges = labelled_tree(n, sequence)
                for a in itertools.product((-2, 1), repeat=n):
                    for d in (0, 1, 4):
                        yield sensors(a, [(u, v, d) for u, v in edges])
        for _ in range(200):
            n = rng.randint(1, 25)
            raw = labelled_tree(n, [rng.randrange(n) for _ in range(max(0, n-2))])
            edges = [(u, v, rng.randint(0, 10)) for u, v in raw]
            rng.shuffle(edges)
            yield sensors(rng.choices(range(-5, 6), k=n), edges)


def audit_statement(p):
    text = (p / "task.md").read_text()
    assert text.splitlines()[0].startswith(f"# {p.name.upper()} — ")
    expected = ["Đề bài", "Dữ liệu vào", "Dữ liệu ra", "Ràng buộc"]
    for i in range(1, 4):
        expected += [f"Sample Input {i}", f"Sample Output {i}"]
    expected.append("Giải thích")
    assert re.findall(r"^### (.+)$", text, re.M) == expected
    assert len(re.findall(r"^#+ ", text, re.M)) == len(expected) + 1
    assert "Subtask" not in text
    for i in range(3):
        for label, folder, ext in [("Input", "in", "in"), ("Output", "out", "out")]:
            match = re.search(rf"### Sample {label} {i+1}\n\n```text\n(.*?)```", text, re.S)
            assert match and match[1] == (p / folder / f"example_{i:02}.{ext}").read_text()
    assert not list(p.glob("*.html"))
    assert (p / "solution.md").exists()


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
    maximum = 100000 if kind == 4 else 200000
    bad = ["", "0\n", f"{maximum+1}\n", sample + "0\n", sample.rsplit("\n", 2)[0] + "\n"]
    if kind == 1:
        bad += [convoy([0], [0], []), convoy([0], [10**6+1], []),
                convoy([-10**9-1], [1], []), convoy([10**9+1], [1], []),
                convoy([0, 0], [1, 1], [-1]), convoy([0, 0], [1, 1], [10**6+1])]
    elif kind == 2:
        bad += [tracking([(2, 1)], []), tracking([(-10**9-1, 0)], []),
                tracking([(0, 10**9+1)], []), tracking([(0, 0), (0, 0)], [(-1, 0)]),
                tracking([(0, 0), (0, 0)], [(0, 10**9+1)])]
    elif kind == 3:
        bad += [signal([-1], [1], []), signal([10**6+1], [1], []), signal([0], [0], []),
                signal([0], [10**6+1], []), signal([0, 0], [1, 1], [0]),
                signal([0, 0], [1, 1], [10**6+1])]
    else:
        bad += [sensors([10**9+1], []), sensors([-10**9-1], []),
                sensors([0, 0], [(0, 1, -1)]), sensors([0, 0], [(0, 1, 10**9+1)]),
                sensors([0, 0], [(0, 0, 0)]), sensors([0, 0], [(0, 2, 0)]),
                sensors([0]*3, [(0, 1, 0), (1, 0, 0)]),
                sensors([0]*4, [(0, 1, 0), (1, 2, 0), (2, 0, 0)])]
    for data in bad:
        result = subprocess.run([str(p / "verifier")], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p.name, "Accepted invalid input", data)
    return len(bad)


def checker_checks(p):
    count = 0
    with tempfile.TemporaryDirectory() as directory:
        actual, answer = Path(directory) / "actual", Path(directory) / "answer"
        for case in ("example_00", "example_01", "max_00"):
            inp = p / "in" / f"{case}.in"
            good = (p / "out" / f"{case}.out").read_text()
            answer.write_text(good)
            variants = [(good, True), (" \n\t" + good.strip() + " \n", True),
                        (str(int(good)+1) + "\n", False), ("", False), (good + "0\n", False),
                        (good + "garbage\n", False), ("x\n", False), ("1.0\n", False), ("9"*50 + "\n", False)]
            for data, accepted in variants:
                actual.write_text(data)
                result = subprocess.run([str(p / "checker"), str(inp), str(actual), str(answer)], capture_output=True)
                assert (result.returncode == 0) == accepted, (p.name, data, result.stderr)
                count += 1
    return count


def generated_checks(problem, kind):
    p = problem.basedir
    files = sorted((p / "in").glob("*.in"))
    assert len(files) == 45
    for index, path in enumerate(files, 1):
        data = path.read_text()
        expected = run(ORACLE, data, kind).split()
        actual = (p / "out" / path.with_suffix(".out").name).read_text().split()
        assert actual == expected, (str(path), expected, actual)
        if index % 10 == 0:
            print(f"{p.name}: oracle checked {index}/45 official tests", flush=True)
    for test in problem.config["tests"]:
        if test["name"].endswith(".cpp"):
            stem = Path(test["name"]).stem
            assert run(p / "gen" / stem, "", 0) == (p / "in" / f"{stem}_00.in").read_text()
    nmax = 100000 if kind == 4 else 200000
    assert all(int((p / "in" / f"max_{i:02}.in").read_text().splitlines()[0]) == nmax for i in range(12))
    return len(files)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--problem", nargs="+", choices=NAMES, default=NAMES)
    parser.add_argument("--update-hashes", action="store_true")
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format="%(message)s")
    problems = [Problem(ROOT, ROOT / "dtqg" / name) for name in args.problem]
    sources = [ORACLE.with_suffix(".cpp")]
    for problem in problems:
        problem.health_check(); problem.generate_params_h()
        sources += [problem.get_correct_filename(), problem.verifier, problem.checker]
        sources += [problem.basedir / "gen" / t["name"] for t in problem.config["tests"] if t["name"].endswith(".cpp")]
    print(f"Compiling {len(sources)} programs...", flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        list(pool.map(build, sources))
    for problem in problems:
        started = time.monotonic(); p = problem.basedir; kind = NAMES.index(p.name) + 1
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True)
        problem.judge(problem.get_correct_filename(), {})
        assert problem.check_all_solutions_used()
        audit_statement(p)
        official = generated_checks(problem, kind)
        print(f"{p.name}: checking small independent cases...", flush=True)
        small = differential(p, kind)
        invalid = invalid_checks(p, kind)
        checker = checker_checks(p)
        if args.update_hashes:
            problem.ignore_warning = True; problem.write_hashes()
        problem.assert_hashes()
        print(f"{p.name}: PASS; {official} official; {small} differential; {invalid} invalid-input; "
              f"{checker} checker tests; hashes verified; {time.monotonic()-started:.1f}s", flush=True)


if __name__ == "__main__":
    main()
