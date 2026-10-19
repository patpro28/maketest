"""Build and verify DPTREE17/18/19/22 without generating HTML."""
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

NAMES = ["dptree17", "dptree18", "dptree19", "dptree22"]
ORACLE = Path(__file__).with_name("oracle")
MOD = 10**9 + 7


def run(executable, data="", *args, timeout=20):
    return subprocess.run([str(executable), *map(str, args)], input=data,
                          text=True, capture_output=True, check=True,
                          timeout=timeout).stdout


def build(src):
    flags = shlex.split(os.getenv(
        "CXXFLAGS", "-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result"))
    subprocess.run([os.getenv("CXX", "g++"), *flags, "-I", str(ROOT / "common"),
                    "-o", str(src.with_suffix("")), str(src)], check=True)


def encode(kind, n, edges, values=None):
    data = f"{n}\n"
    if kind in (18, 22):
        data += " ".join(map(str, values)) + "\n"
    for edge in edges:
        data += " ".join(map(str, edge if kind == 19 else edge[:2])) + "\n"
    return data


def decode(kind, data):
    lines = data.splitlines()
    n = int(lines[0])
    values = list(map(int, lines[1].split())) if kind in (18, 22) else []
    edges = [tuple(map(int, x.split())) for x in lines[2 if values else 1:]]
    assert len(edges) == n - 1
    return n, edges, values


def audit_statement(p):
    text = (p / "task.md").read_text()
    assert text.splitlines()[0].startswith(f"# {p.name.upper()} — ")
    headings = re.findall(r"^### (.+)$", text, re.M)
    assert headings == [
        "Đề bài", "Dữ liệu vào", "Dữ liệu ra", "Ràng buộc", "Subtask",
        "Sample Input 1", "Sample Output 1", "Sample Input 2", "Sample Output 2",
        "Giải thích"]
    assert len(re.findall(r"^#+ ", text, re.M)) == len(headings) + 1
    assert "| Subtask | Tỉ lệ | Ràng buộc bổ sung |" in text
    assert re.findall(r"^\| \d+ \| (\d+)% \| (.+) \|$", text, re.M) == [
        ("100", "Không có ràng buộc bổ sung")]
    for i in range(2):
        for label, folder, extension in [("Input", "in", "in"), ("Output", "out", "out")]:
            found = re.search(
                rf"### Sample {label} {i+1}\n\n" + r"\x60{3}text\n(.*?)\x60{3}",
                text, re.S)
            assert found and found[1] == (
                p / folder / f"example_{i:02}.{extension}").read_text(), (p, label, i)
    assert not (p / "task.html").exists()
    assert (p / "solution.md").exists()


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
        edges.append((u + 1, v + 1))
        degree[u] -= 1
        if degree[u] == 1:
            heapq.heappush(leaves, u)
    edges.append(tuple(u + 1 for u in leaves))
    return edges


def check_case(p, kind, data):
    run(p / "verifier", data)
    expected = run(ORACLE, data, kind).split()
    actual = run(p / "sol/correct", data).split()
    assert actual == expected, (p.name, data, expected, actual)


def small_checks(p, kind):
    rng = random.Random(20261018 + kind)
    count = 0
    # Every labelled tree up to five vertices, constructed by Prüfer sequences.
    for n in range(2 if kind == 19 else 1, 6):
        for sequence in itertools.product(range(n), repeat=max(0, n - 2)):
            raw = labelled_tree(n, sequence)
            for variant in range(1 if kind == 17 else 2):
                edges = [(u, v, rng.choice([1, 2, 9, 10**9])) for u, v in raw]
                alphabet = [-9, -1, 0, 1, 8, 10**9] if kind == 18 else [1, 2, 9, 10**9]
                values = rng.choices(alphabet, k=n)
                if variant == 0 and kind in (18, 22):
                    values = [(-1 if kind == 18 else 1)] * n
                check_case(p, kind, encode(kind, n, edges, values))
                count += 1
    # Enumerate all small value assignments, independently of the DP states.
    if kind != 17:
        for n in range(2 if kind == 19 else 1, 4):
            for sequence in itertools.product(range(n), repeat=max(0, n - 2)):
                raw = labelled_tree(n, sequence)
                alphabet = [-1, 0, 1] if kind == 18 else [1, 2, 3]
                length = n - 1 if kind == 19 else n
                for values in itertools.product(alphabet, repeat=length):
                    edges = [(u, v, values[i] if kind == 19 else 1)
                             for i, (u, v) in enumerate(raw)]
                    check_case(p, kind, encode(kind, n, edges, values))
                    count += 1
    for _ in range(240):
        n = rng.randint(2 if kind == 19 else 1, 16)
        raw = labelled_tree(n, [rng.randrange(n) for _ in range(max(0, n - 2))])
        edges = [(u, v, rng.choice([1, 2, 3, 17, 10**9])) for u, v in raw]
        rng.shuffle(edges)
        alphabet = [-10**9, -7, -1, 0, 1, 8, 10**9] if kind == 18 else [1, 2, 7, 10**9]
        check_case(p, kind, encode(kind, n, edges, rng.choices(alphabet, k=n)))
        count += 1
    return count


def simple_expected(kind, n, edges, values):
    """Closed forms and an unweighted greedy oracle for large special cases."""
    degree = [0] * n
    for u, v, *_ in edges:
        degree[u - 1] += 1
        degree[v - 1] += 1
    if kind == 17:
        if max(degree) <= 2:
            a, b = 0, 1
            for _ in range(n + 2):
                a, b = b, (a + b) % MOD
            return a
        if max(degree) == n - 1:
            return (pow(2, n - 1, MOD) + 1) % MOD
    elif kind == 18:
        if min(values) >= 0:
            return sum(values)
        if max(values) <= 0:
            return max(values)
    elif kind == 19 and len({w for _, _, w in edges}) == 1:
        return degree[0] * edges[0][2]
    elif kind == 22 and len(set(values)) == 1:
        # Unit-cost domination: place a station at the parent of an uncovered
        # deepest leaf. This greedy oracle does not use the weighted DP.
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u - 1].append(v - 1)
            adj[v - 1].append(u - 1)
        parent, order = [-1] * n, [0]
        for u in order:
            for v in adj[u]:
                if v != parent[u]:
                    parent[v] = u
                    order.append(v)
        state = [0] * n  # 0 uncovered, 1 station, 2 covered
        stations = 0
        for u in reversed(order):
            children = [state[v] for v in adj[u] if parent[v] == u]
            if 0 in children:
                state[u] = 1
                stations += 1
            elif 1 in children:
                state[u] = 2
        if state[0] == 0:
            stations += 1
        return stations * values[0]
    return None


def audit_generated(p, kind):
    files = sorted((p / "in").glob("*.in"))
    assert len(files) == 38
    n_values, brute_count, analytical = [], 0, 0
    for path in files:
        data = path.read_text()
        n, edges, values = decode(kind, data)
        n_values.append(n)
        actual = int((p / "out" / path.with_suffix(".out").name).read_text())
        if n <= 20:
            assert int(run(ORACLE, data, kind)) == actual, (path, "brute differs")
            brute_count += 1
        expected = simple_expected(kind, n, edges, values)
        if expected is not None:
            assert actual == expected, (path, expected, actual)
            analytical += 1
        if kind == 17:
            assert 0 <= actual < MOD
        elif kind == 18:
            assert max(values) <= actual <= sum(x for x in values if x > 0) or (
                max(values) < 0 and actual == max(values))
        elif kind == 19:
            assert 1 <= actual <= sum(w for _, _, w in edges)
        else:
            assert min(values) <= actual <= sum(values)
    assert n_values.count(200000) == 8
    assert min(n_values) == (2 if kind == 19 else 1)
    return brute_count, analytical


def check_invalid_input(p, kind):
    sample = (p / "gen/example_00.in").read_text()
    bad = ["", "0\n", "200001\n", sample + "0\n",
           sample.rsplit("\n", 2)[0] + "\n"]
    n = 4
    values = [1] * n
    # Self-loop, parallel edges, cycle with an isolated vertex, invalid endpoints.
    for raw in [
        [(1, 1), (1, 2), (2, 3)],
        [(1, 2), (2, 1), (3, 4)],
        [(1, 2), (2, 3), (3, 1)],
        [(0, 2), (2, 3), (3, 4)],
        [(1, 5), (2, 3), (3, 4)],
    ]:
        bad.append(encode(kind, n, [(u, v, 1) for u, v in raw], values))
    if kind == 19:
        bad += ["1\n", "2\n1 2 0\n", "2\n1 2 -1\n", "2\n1 2 1000000001\n"]
    elif kind in (18, 22):
        for x in ([-1000000001, 1000000001] if kind == 18 else [0, -1, 1000000001]):
            bad.append(encode(kind, 1, [], [x]))
        bad.append("2\n1\n1 2\n")
    for data in bad:
        result = subprocess.run([str(p / "verifier")], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p.name, "accepted invalid input", data)
    return len(bad)


def check_checker(p):
    checks = 0
    with tempfile.TemporaryDirectory() as directory:
        directory = Path(directory)
        inp, actual, ans = [directory / x for x in ("input", "actual", "answer")]
        for case in ("example_00", "example_01", "max_00"):
            inp.write_text((p / "in" / f"{case}.in").read_text())
            good = (p / "out" / f"{case}.out").read_text()
            ans.write_text(good)
            tests = [(good, True), (" \n\t" + good.strip() + " \t\n", True),
                     (str(int(good) + 1) + "\n", False), ("", False),
                     (good + "0\n", False), (good + "garbage\n", False),
                     ("x\n", False), ("1.0\n", False), ("999999999999999999999999\n", False)]
            for data, accepted in tests:
                actual.write_text(data)
                result = subprocess.run([str(p / "checker"), str(inp), str(actual), str(ans)],
                                        capture_output=True)
                assert (result.returncode == 0) == accepted, (p.name, data, result.stderr)
                checks += 1
    return checks


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
        sources += [p / "sol/correct.cpp", problem.checker, problem.verifier]
        sources += [p / "gen" / test["name"] for test in problem.config["tests"]
                    if test["name"].endswith(".cpp")]
    print(f"Compiling {len(sources)} programs...", flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        list(pool.map(build, sources))
    for problem in problems:
        started = time.monotonic()
        p = problem.basedir
        kind = int(p.name[6:])
        problem.make_inputs()
        problem.verify_inputs()
        problem.make_outputs(True)
        # Enforces the configured time limit and checks every generated answer.
        problem.judge(p / "sol/correct.cpp", {})
        assert problem.check_all_solutions_used()
        audit_statement(p)
        brute_count, analytical = audit_generated(p, kind)
        for test in problem.config["tests"]:
            if not test["name"].endswith(".cpp"):
                continue
            exe = p / "gen" / Path(test["name"]).stem
            for seed in range(test["number"]):
                assert run(exe, "", seed) == (
                    p / "in" / f"{exe.name}_{seed:02}.in").read_text(), (p, exe, seed)
        count = small_checks(p, kind)
        invalid = check_invalid_input(p, kind)
        checker_count = check_checker(p)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        # Convenient upload bundle containing the flat .in/.out pairs.
        problem.zip()
        print(f"{p.name}: 38 generated tests ({brute_count} brute, {analytical} analytical), "
              f"{count} exhaustive/random checks, {invalid} invalid inputs, "
              f"{checker_count} checker checks; samples, reproducibility, hashes, ZIP OK "
              f"({time.monotonic() - started:.1f}s)", flush=True)
    print("All checks passed; no HTML generated.", flush=True)


if __name__ == "__main__":
    main()
