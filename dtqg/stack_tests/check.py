"""Generate and verify the four advanced stack problems without exporting HTML."""
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

NAMES = ["second", "khungsang", "cuasomin", "duongmin"]
ORACLE = Path(__file__).with_name("oracle")
SLOW = Path(__file__).with_name("slow_duongmin")
SLOW_SECOND = Path(__file__).with_name("slow_second")


def run(executable, data="", *args, timeout=90):
    return subprocess.run([str(executable), *map(str, args)], input=data, text=True,
                          capture_output=True, check=True, timeout=timeout).stdout


def build(src):
    flags = shlex.split(os.getenv("CXXFLAGS", "-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result"))
    subprocess.run([os.getenv("CXX", "g++"), *flags, "-I", str(ROOT / "common"),
                    "-o", str(src.with_suffix("")), str(src)], check=True)


def permutation(a):
    return f"{len(a)}\n" + " ".join(map(str, a)) + "\n"


def board(rows):
    return f"{len(rows)} {len(rows[0])}\n" + "\n".join(rows) + "\n"


def windows(a, queries):
    return f"{len(a)} {len(queries)}\n" + " ".join(map(str, a)) + "\n" + "".join(
        f"{l} {r}\n" for l, r in queries)


def paths(a, edges, queries):
    return f"{len(a)} {len(queries)}\n" + " ".join(map(str, a)) + "\n" + "".join(
        f"{u+1} {v+1}\n" for u, v in edges) + "".join(f"{v+1} {k}\n" for v, k in queries)


def labelled_tree(n, sequence):
    if n == 1:
        return []
    degree = [1]*n
    for u in sequence:
        degree[u] += 1
    leaves = [u for u in range(n) if degree[u] == 1]
    heapq.heapify(leaves)
    edges = []
    for u in sequence:
        v = heapq.heappop(leaves); edges.append((u, v)); degree[u] -= 1
        if degree[u] == 1:
            heapq.heappush(leaves, u)
    edges.append(tuple(leaves))
    return edges


def depths(n, edges):
    adj = [[] for _ in range(n)]
    for u, v in edges:
        adj[u].append(v); adj[v].append(u)
    depth, order = [0]*n, [0]
    depth[0] = 1
    for u in order:
        for v in adj[u]:
            if not depth[v]:
                depth[v] = depth[u] + 1; order.append(v)
    return depth


def small_cases(kind):
    rng = random.Random(2026102800 + kind)
    if kind == 1:
        for n in range(1, 7):
            for a in itertools.permutations(range(1, n+1)):
                yield permutation(a)
        for _ in range(250):
            n = rng.randint(1, 35); a = list(range(1, n+1)); rng.shuffle(a)
            yield permutation(a)
    elif kind == 2:
        for r in range(1, 4):
            for c in range(1, 4):
                for bits in itertools.product("01", repeat=r*c):
                    yield board(["".join(bits[i*c:(i+1)*c]) for i in range(r)])
        for _ in range(180):
            r, c = rng.randint(1, 8), rng.randint(1, 8)
            yield board(["".join(rng.choices("01", k=c)) for _ in range(r)])
    elif kind == 3:
        for n in range(1, 6):
            for a in itertools.product((0, 1, 3), repeat=n):
                queries = [(l, r) for l in range(1, n+1) for r in range(l, n+1)]
                rng.shuffle(queries)
                yield windows(a, queries)
        for _ in range(250):
            n = rng.randint(1, 45)
            a = rng.choices([0, 1, 2, 7, 10**6], k=n)
            queries = [sorted([rng.randint(1, n), rng.randint(1, n)]) for _ in range(rng.randint(1, 50))]
            yield windows(a, queries)
    else:
        for n in range(1, 5):
            for sequence in itertools.product(range(n), repeat=max(0, n-2)):
                edges = labelled_tree(n, sequence); d = depths(n, edges)
                queries = [(v, k) for v in range(n) for k in range(1, d[v]+1)]
                for a in itertools.product((0, 3), repeat=n):
                    yield paths(a, edges, queries)
        for _ in range(220):
            n = rng.randint(1, 35)
            edges = labelled_tree(n, [rng.randrange(n) for _ in range(max(0, n-2))])
            rng.shuffle(edges); d = depths(n, edges)
            queries = []
            for _ in range(50):
                v = rng.randrange(n); queries.append((v, rng.randint(1, d[v])))
            yield paths(rng.choices([0, 1, 3, 7, 10**9], k=n), edges, queries)
        for stem in (2, 3, 5, 10):
            edges = [(i-1, i) for i in range(1, stem)] + [(stem-1, v) for v in range(stem, 2*stem)]
            d = depths(2*stem, edges)
            queries = [(v, k) for v in range(2*stem) for k in range(1, d[v]+1)]
            for leaf in (0, 1):
                yield paths(list(range(2, stem+2)) + [leaf]*stem, edges, queries)


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
        assert actual == expected, (p.name, data, expected[:10], actual[:10])
        count += 1
    return count


def invalid_checks(p, kind):
    sample = (p / "gen/example_00.in").read_text()
    bad = ["", sample + "0\n", sample.rsplit("\n", 2)[0] + "\n"]
    if kind == 1:
        bad += ["0\n", "200001\n", permutation([0]), permutation([2]), permutation([1, 1]), permutation([-1, 2])]
    elif kind == 2:
        bad += ["0 1\n", "1 0\n", "1000001 1\n", "1001 1000\n", "1 2\n1\n",
                "1 1\n11\n", "1 1\n2\n", "1 2\n0 1\n"]
    elif kind == 3:
        bad += ["0 1\n", "200001 1\n", "1 0\n", "1 200001\n", windows([-1], [(1, 1)]),
                windows([10**6+1], [(1, 1)]), windows([0], [(0, 1)]), windows([0], [(1, 2)]),
                windows([0, 0], [(2, 1)])]
    else:
        bad += ["0 1\n", "200001 1\n", "1 0\n", "1 200001\n", paths([-1], [], [(0, 1)]),
                paths([10**9+1], [], [(0, 1)]), paths([0], [], [(0, 0)]), paths([0], [], [(0, 2)]),
                paths([0], [], [(1, 1)]), paths([0, 0], [(0, 0)], [(0, 1)]),
                paths([0]*3, [(0, 1), (1, 0)], [(0, 1)]),
                paths([0]*4, [(0, 1), (1, 2), (2, 0)], [(0, 1)]),
                paths([0]*3, [(0, 1), (0, 2)], [(1, 3)])]
    for data in bad:
        r = subprocess.run([str(p / "verifier")], input=data, text=True, capture_output=True)
        assert r.returncode != 0, (p.name, "Accepted invalid input", data)
    return len(bad)


def checker_checks(p):
    count = 0
    with tempfile.TemporaryDirectory() as directory:
        actual, answer = Path(directory) / "actual", Path(directory) / "answer"
        for case in ("example_00", "example_01", "max_00"):
            inp = p / "in" / f"{case}.in"
            good = (p / "out" / f"{case}.out").read_text(); answer.write_text(good)
            words = good.split()
            variants = [(good, True), (" \n\t" + good.strip() + " \n", True), ("", False),
                        (good + "0\n", False), (good + "garbage\n", False), ("x\n", False),
                        ("1.0\n", False), ("9"*50 + "\n", False)]
            for i in sorted({0, len(words)-1}):
                wrong = words.copy(); wrong[i] = str(int(wrong[i])+1)
                variants.append(("\n".join(wrong) + "\n", False))
            if len(words) > 1:
                variants.append(("\n".join(words[:-1]) + "\n", False))
            for data, accepted in variants:
                actual.write_text(data)
                r = subprocess.run([str(p / "checker"), str(inp), str(actual), str(answer)], capture_output=True)
                assert (r.returncode == 0) == accepted, (p.name, data[:80], r.stderr)
                count += 1
    return count


def generated_checks(problem, kind):
    p = problem.basedir
    expected_count = sum(test["number"] for test in problem.config["tests"])
    files = sorted((p / "in").glob("*.in")); assert len(files) == expected_count
    for i, path in enumerate(files, 1):
        try:
            expected = run(ORACLE, path.read_text(), kind).split()
        except subprocess.CalledProcessError as error:
            raise AssertionError((str(path), error.stderr)) from error
        actual = (p / "out" / path.with_suffix(".out").name).read_text().split()
        assert actual == expected, (str(path), expected[:10], actual[:10])
        if i % 10 == 0:
            print(f"{p.name}: oracle checked {i}/{expected_count} official tests", flush=True)
    for test in problem.config["tests"]:
        if test["name"].endswith(".cpp"):
            stem = Path(test["name"]).stem
            assert run(p / "gen" / stem, "", 0) == (p / "in" / f"{stem}_00.in").read_text()
    for i in range(12):
        header = list(map(int, (p / "in" / f"max_{i:02}.in").open().readline().split()))
        assert header[0] == 200000 if kind == 1 else header[0]*header[1] == 1000000 if kind == 2 else header == [200000, 200000]
    if kind == 1:
        n = problem.config["params"]["N_MAX"]; m = n // 2
        base = list(range(n - 1, m - 1, -1)) + [n] + list(range(1, m))
        for seed in range(2):
            words = list(map(int, (p / "in" / f"jump_{seed:02}.in").read_text().split()))
            assert words[0] == n
            assert words[1:] == (base if seed == 0 else base[::-1])
    return len(files)


def check_slow(p, limit):
    # First establish that this intentionally slow solver is functionally correct.
    for i in range(3):
        data = (p / "in" / f"example_{i:02}.in").read_text()
        assert run(SLOW, data).split() == (p / "out" / f"example_{i:02}.out").read_text().split()
    cases = list(small_cases(4))
    for data in cases[-20:]:
        assert run(SLOW, data).split() == run(p / "sol/correct", data).split()
    for seed in (3, 4):
        path = p / "in" / f"max_{seed:02}.in"
        try:
            with path.open() as f:
                subprocess.run([str(SLOW)], stdin=f, text=True, capture_output=True, check=True, timeout=limit)
        except subprocess.TimeoutExpired:
            print(f"duongmin: pop/rollback baseline exceeds {limit}s on {path.name}", flush=True)
        else:
            raise AssertionError(f"Pop/rollback baseline unexpectedly fits the time limit on {path.name}")


def check_slow_second(p, limit):
    for seed in range(3):
        data = (p / "in" / f"example_{seed:02}.in").read_text()
        assert run(SLOW_SECOND, data).split() == (p / "out" / f"example_{seed:02}.out").read_text().split()
    for data in list(small_cases(1))[-20:]:
        assert run(SLOW_SECOND, data).split() == run(ORACLE, data, 1).split()
    for n in (8, 10, 1000):
        m = n // 2
        a = list(range(n - 1, m - 1, -1)) + [n] + list(range(1, m))
        for values in (a, a[::-1]):
            data = permutation(values)
            assert run(SLOW_SECOND, data).split() == run(ORACLE, data, 1).split()
    for seed in range(2):
        path = p / "in" / f"jump_{seed:02}.in"
        try:
            with path.open() as f:
                subprocess.run([str(SLOW_SECOND)], stdin=f, text=True, capture_output=True, check=True, timeout=limit)
        except subprocess.TimeoutExpired:
            print(f"second: repeated-link baseline exceeds {limit}s on {path.name}", flush=True)
        else:
            raise AssertionError(f"Repeated-link baseline unexpectedly fits the time limit on {path.name}")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--problem", nargs="+", choices=NAMES, default=NAMES)
    parser.add_argument("--update-hashes", action="store_true")
    parser.add_argument("--check-slow", action="store_true", help="Benchmark the intentionally quadratic SECOND/DUONGMIN baselines")
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format="%(message)s")
    problems = [Problem(ROOT, ROOT / "dtqg" / name) for name in args.problem]
    sources = [ORACLE.with_suffix(".cpp")]
    if args.check_slow and "duongmin" in args.problem:
        sources.append(SLOW.with_suffix(".cpp"))
    if args.check_slow and "second" in args.problem:
        sources.append(SLOW_SECOND.with_suffix(".cpp"))
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
        small = differential(p, kind); invalid = invalid_checks(p, kind); checker = checker_checks(p)
        if p.name == "duongmin" and args.check_slow:
            check_slow(p, problem.config["timelimit"])
        if p.name == "second" and args.check_slow:
            check_slow_second(p, problem.config["timelimit"])
        if args.update_hashes:
            problem.ignore_warning = True; problem.write_hashes()
        problem.assert_hashes()
        print(f"{p.name}: PASS; {official} official; {small} differential; {invalid} invalid-input; "
              f"{checker} checker tests; hashes verified; {time.monotonic()-started:.1f}s", flush=True)


if __name__ == "__main__":
    main()
