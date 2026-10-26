"""Generate and verify DPTREE23--DPTREE26 without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import logging
from pathlib import Path
import random
import re
import sys
import time
import subprocess
import zipfile

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT))
sys.path.insert(0, str(HERE))
from problem import Problem
from check import build, run, labelled_tree, check_checker

NAMES = ["dptree23", "dptree24", "dptree25", "dptree26"]
ORACLE = HERE / "oracle_binary"
MOD = 10**9 + 7


def encode(kind, n, edges, values=None):
    data = f"{n}\n"
    if kind == 23:
        data += " ".join(map(str, values)) + "\n"
    elif kind == 24:
        data += "".join(f"{a} {b}\n" for a, b in values)
    data += "".join(" ".join(map(str, e if kind == 24 else e[:2])) + "\n" for e in edges)
    return data


def decode(kind, data):
    lines = data.splitlines()
    n, offset, values = int(lines[0]), 1, []
    if kind == 23:
        values, offset = list(map(int, lines[1].split())), 2
    elif kind == 24:
        values = [tuple(map(int, s.split())) for s in lines[1:n+1]]
        offset = n + 1
    edges = [tuple(map(int, s.split())) for s in lines[offset:]]
    assert len(edges) == n - 1
    return n, edges, values


def audit_statement(p):
    text = (p / "task.md").read_text()
    assert text.splitlines()[0].startswith(f"# {p.name.upper()} — ")
    headings = re.findall(r"^### (.+)$", text, re.M)
    assert headings == [
        "Đề bài", "Dữ liệu vào", "Dữ liệu ra", "Ràng buộc",
        "Sample Input 1", "Sample Output 1", "Sample Input 2", "Sample Output 2",
        "Giải thích"]
    assert len(re.findall(r"^#+ ", text, re.M)) == len(headings) + 1
    for i in range(2):
        for label, folder, extension in [("Input", "in", "in"), ("Output", "out", "out")]:
            match = re.search(
                rf"### Sample {label} {i+1}\n\n" + r"\x60{3}text\n(.*?)\x60{3}",
                text, re.S)
            assert match and match[1] == (
                p / folder / f"example_{i:02}.{extension}").read_text(), (p, label, i)
    assert not (p / "task.html").exists()
    assert (p / "solution.md").exists()


def check_case(p, kind, data, expected=None):
    run(p / "verifier", data)
    if expected is None:
        expected = int(run(ORACLE, data, kind))
    actual = int(run(p / "sol/correct", data))
    assert actual == expected, (p.name, data, expected, actual)


def exact_antichain_tree(target):
    """Construct a tree with exactly target antichains before taking modulo."""
    steps = []
    while target > 3:
        if target % 2 == 0:
            steps.append("inc")
            target -= 1
        else:
            steps.append("double_inc")
            target = (target - 1) // 2
    n, root = target - 1, 0
    edges = [(0, 1)] if n == 2 else []
    for step in reversed(steps):
        edges.append((n, root))
        root = n
        n += 1
        if step == "double_inc":
            edges.append((root, n))
            n += 1
    labels = [u for u in range(n) if u != root]
    mapping = {root: 1}
    mapping.update({u: i + 2 for i, u in enumerate(labels)})
    return n, [(mapping[u], mapping[v]) for u, v in edges]


def small_checks(p, kind):
    rng = random.Random(20261022 + kind)
    count = 0
    for n in range(1, 6):
        for sequence in itertools.product(range(n), repeat=max(0, n - 2)):
            raw = labelled_tree(n, sequence)
            for variant in range(2 if kind <= 24 else 1):
                edges = [(u, v, rng.choice([0, 1, 9, 10**9])) for u, v in raw]
                if kind == 23:
                    values = [1] * n if variant == 0 else rng.choices([1, 2, 9, 10**9], k=n)
                else:
                    values = [(rng.choice([0, 1, 9, 10**9]),
                               rng.choice([0, 1, 9, 10**9])) for _ in range(n)]
                    if variant == 0:
                        values = [(0, 0)] * n
                check_case(p, kind, encode(kind, n, edges, values))
                count += 1
    if kind <= 24:
        for n in range(1, 4):
            for sequence in itertools.product(range(n), repeat=max(0, n - 2)):
                raw = labelled_tree(n, sequence)
                alphabet = [1, 2, 3] if kind == 23 else [(0, 0), (0, 1), (1, 0), (1, 1)]
                for values in itertools.product(alphabet, repeat=n):
                    for weights in itertools.product([0, 1] if kind == 24 else [0], repeat=n-1):
                        edges = [(u, v, weights[i]) for i, (u, v) in enumerate(raw)]
                        check_case(p, kind, encode(kind, n, edges, values))
                        count += 1
    for _ in range(240):
        n = rng.randint(1, 16)
        raw = labelled_tree(n, [rng.randrange(n) for _ in range(max(0, n-2))])
        edges = [(u, v, rng.choice([0, 1, 2, 17, 10**9])) for u, v in raw]
        edges = [(u, v, w) if rng.randrange(2) else (v, u, w) for u, v, w in edges]
        rng.shuffle(edges)
        values = rng.choices([1, 2, 7, 10**9], k=n) if kind == 23 else [
            (rng.choice([0, 1, 7, 10**9]), rng.choice([0, 1, 7, 10**9])) for _ in range(n)]
        check_case(p, kind, encode(kind, n, edges, values))
        count += 1
    if kind == 25:
        for target in [MOD-1, MOD, MOD+1]:
            n, edges = exact_antichain_tree(target)
            check_case(p, kind, encode(kind, n, edges), target % MOD)
            count += 1
    return count


def simple_expected(kind, n, edges, values):
    degree = [0] * n
    for u, v, *_ in edges:
        degree[u-1] += 1
        degree[v-1] += 1
    if kind == 23:
        if n == 1:
            return 0
        if max(degree) == n - 1:
            center = degree.index(n-1)
            return min(values[center], sum(values) - values[center])
        if len(set(values)) == 1:
            # Maximum matching by greedy leaf elimination; Konig's theorem
            # equates it to the minimum unweighted cover on this bipartite tree.
            adj = [[] for _ in range(n)]
            for u, v in edges:
                adj[u-1].append(v-1)
                adj[v-1].append(u-1)
            parent, order = [-1] * n, [0]
            for u in order:
                for v in adj[u]:
                    if v != parent[u]:
                        parent[v] = u
                        order.append(v)
            matched, pairs = [False] * n, 0
            for u in reversed(order[1:]):
                p = parent[u]
                if not matched[u] and not matched[p]:
                    matched[u] = matched[p] = True
                    pairs += 1
            return pairs * values[0]
    elif kind == 24:
        if not any(w for _, _, w in edges):
            return sum(min(a, b) for a, b in values)
        if all(a == b for a, b in values):
            return sum(a for a, _ in values)
        baseline = sum(min(a, b) for a, b in values)
        preferred = [int(b < a) for a, b in values]
        surcharge = sum(w for u, v, w in edges if preferred[u-1] != preferred[v-1])
        # Changing any preferred color costs more than all edges combined.
        if min(abs(a-b) for a, b in values) > sum(w for _, _, w in edges):
            return baseline + surcharge
    elif kind == 25:
        if n == 1:
            return 2
        if max(degree) <= 2 and degree[0] == 1:
            return (n + 1) % MOD
        if max(degree) == n - 1:
            return ((pow(2, n-1, MOD) + 1) if degree[0] == n-1
                    else pow(2, n-2, MOD) + 2) % MOD
    elif kind == 26:
        if max(degree) <= 2:
            a, b = 0, 1
            for _ in range(n+1):
                a, b = b, (a+b) % MOD
            return a
        if max(degree) == n - 1:
            return n % MOD
    return None


def audit_generated(p, kind):
    paths = sorted((p / "in").glob("*.in"))
    assert len(paths) == 38
    sizes, brute_count, analytical = [], 0, 0
    for path in paths:
        data = path.read_text()
        n, edges, values = decode(kind, data)
        sizes.append(n)
        answer = int((p / "out" / path.with_suffix(".out").name).read_text())
        if n <= 20:
            assert int(run(ORACLE, data, kind)) == answer, (path, "brute differs")
            brute_count += 1
        expected = simple_expected(kind, n, edges, values)
        if expected is not None:
            assert answer == expected, (path, expected, answer)
            analytical += 1
        if kind == 23:
            assert 0 <= answer <= sum(values)
        elif kind == 24:
            assert sum(min(a, b) for a, b in values) <= answer <= min(
                sum(a for a, _ in values), sum(b for _, b in values))
        else:
            assert 0 <= answer < MOD
    assert min(sizes) == 1 and sizes.count(200000) == 8
    return brute_count, analytical


def invalid_inputs(p, kind):
    sample = (p / "gen/example_00.in").read_text()
    bad = ["", "0\n", "200001\n", sample + "0\n",
           sample.rsplit("\n", 2)[0] + "\n"]
    values = [1] * 4 if kind == 23 else [(0, 1)] * 4
    for raw in [
        [(1, 1), (1, 2), (2, 3)], [(1, 2), (2, 1), (3, 4)],
        [(1, 2), (2, 3), (3, 1)], [(0, 2), (2, 3), (3, 4)],
        [(1, 5), (2, 3), (3, 4)],
    ]:
        bad.append(encode(kind, 4, [(u, v, 1) for u, v in raw], values))
    if kind == 23:
        for x in [0, -1, 1000000001]:
            bad.append(encode(kind, 1, [], [x]))
        bad.append("2\n1\n1 2\n")
    elif kind == 24:
        for x in [-1, 1000000001]:
            bad.extend([encode(kind, 1, [], [(x, 0)]),
                        encode(kind, 1, [], [(0, x)]),
                        encode(kind, 2, [(1, 2, x)], [(0, 0), (0, 0)])])
        bad.extend(["1\n0\n", "2\n0 0\n1 2 3\n"])
    for data in bad:
        result = subprocess.run([str(p / "verifier")], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p.name, "accepted malformed input", data)
    return len(bad)


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
        sources.extend([p / "sol/correct.cpp", problem.checker, problem.verifier])
        sources.extend(p / "gen" / t["name"] for t in problem.config["tests"]
                       if t["name"].endswith(".cpp"))
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
        invalid = invalid_inputs(p, kind)
        checker_count = check_checker(p)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        problem.zip()
        with zipfile.ZipFile(p / (p.name + ".zip")) as archive:
            assert len(archive.namelist()) == 76 and archive.testzip() is None
        print(f"{p.name}: 38 generated tests ({brute_count} brute, {analytical} analytical), "
              f"{count} exhaustive/random/special checks, {invalid} invalid inputs, "
              f"{checker_count} checker checks; samples, reproducibility, hashes, ZIP OK "
              f"({time.monotonic() - started:.1f}s)", flush=True)
    print("All checks passed; no HTML generated.", flush=True)


if __name__ == "__main__":
    main()
