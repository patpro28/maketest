"""Generate, validate and independently check five max-plus DP problems; no HTML."""
import argparse
from bisect import bisect_right
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

NAMES = ["hanhtrinh", "lichtruc", "daynen", "cachba", "choncay"]
ORACLE = Path(__file__).with_name("oracle")


def run(executable, data="", *args, timeout=120):
    return subprocess.run([str(executable), *map(str, args)], input=data, text=True,
                          capture_output=True, check=True, timeout=timeout).stdout


def build(src):
    flags = shlex.split(os.getenv("CXXFLAGS", "-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result"))
    subprocess.run([os.getenv("CXX", "g++"), *flags, "-I", str(ROOT / "common"),
                    "-o", str(src.with_suffix("")), str(src)], check=True)


def walk(n, edges, s, t, k):
    return f"{n} {len(edges)} {s} {t} {k}\n" + "".join(f"{u} {v} {w}\n" for u, v, w in edges)


def calendar(scores, days):
    return f"{len(scores)} {days}\n" + "".join(" ".join(map(str, row)) + "\n" for row in scores)


def grammar(c, instructions):
    return f"{len(instructions)} {c}\n" + "".join(" ".join(map(str, row)) + "\n" for row in instructions)


def positions(a, operations):
    return f"{len(a)} {len(operations)}\n" + " ".join(map(str, a)) + "\n" + "".join(
        " ".join(map(str, row)) + "\n" for row in operations)


def tree(a, edges, updates):
    return f"{len(a)} {len(updates)}\n" + " ".join(map(str, a)) + "\n" + "".join(
        f"{u} {v}\n" for u, v in [*edges, *updates])


def labelled_tree(n, sequence):
    if n == 1:
        return []
    degree = [1] * (n + 1)
    for v in sequence:
        degree[v] += 1
    leaves = [v for v in range(1, n + 1) if degree[v] == 1]
    heapq.heapify(leaves)
    edges = []
    for v in sequence:
        u = heapq.heappop(leaves); edges.append((u, v)); degree[v] -= 1
        if degree[v] == 1:
            heapq.heappush(leaves, v)
    edges.append(tuple(leaves))
    return edges


def brute(kind, data):
    lines = [list(map(int, row.split())) for row in data.splitlines()]
    output = []
    if kind == 1:
        n, m, s, t, k = lines[0]; f = [None] * n; f[s-1] = 0
        for _ in range(k):
            next_values = [None] * n
            for u, v, w in lines[1:m+1]:
                if f[u-1] is not None:
                    value = f[u-1] + w
                    if next_values[v-1] is None or value > next_values[v-1]:
                        next_values[v-1] = value
            f = next_values
        return ["IMPOSSIBLE" if f[t-1] is None else str(f[t-1])]
    if kind == 2:
        p, d = lines[0]; dp = {(0, 0): 0}
        for day in range(d):
            next_values = {}
            for (older, last), value in dp.items():
                for job in range(4):
                    if job and (job == last or (older and last)):
                        continue
                    state = (last, job); score = value + (lines[1+day % p][job-1] if job else 0)
                    next_values[state] = max(next_values.get(state, -10**100), score)
            dp = next_values
        return [str(max(dp.values()))]
    if kind == 3:
        seq = [[]]
        for instruction in lines[1:]:
            if instruction[0] == 1:
                current = [instruction[1]]
            elif instruction[0] == 2:
                current = seq[instruction[1]] + seq[instruction[2]]
            else:
                current = seq[instruction[1]] * instruction[2]
            assert len(current) <= 2000
            seq.append(current); tails = []
            for x in current:
                p = bisect_right(tails, x)
                if p == len(tails):
                    tails.append(x)
                else:
                    tails[p] = x
            output.append(str(len(tails)))
    elif kind == 4:
        a = lines[1].copy()
        for op, x, y in lines[2:]:
            if op == 1:
                a[x-1] = y
            else:
                selected = a[x-1:y]; f = [0] * (len(selected)+3)
                for i, value in enumerate(selected):
                    f[i+3] = max(f[i+2], f[i] + value)
                answer = f[-1]
                if len(selected) <= 8:
                    enumerated = max(sum(value for i, value in enumerate(selected) if mask >> i & 1)
                                     for mask in range(1 << len(selected))
                                     if not (mask & (mask << 1) or mask & (mask << 2)))
                    assert answer == enumerated
                output.append(str(answer))
    else:
        n, q = lines[0]; a = lines[1].copy(); edges = lines[2:n+1]
        adj = [[] for _ in range(n)]
        for u, v in edges:
            adj[u-1].append(v-1); adj[v-1].append(u-1)
        parent = [-1] * n; order = [0]
        for u in order:
            for v in adj[u]:
                if v != parent[u]:
                    parent[v] = u; order.append(v)
        for u, x in lines[n+1:n+1+q]:
            a[u-1] = x; zero = [0]*n; one = a.copy()
            for v in order[::-1]:
                if parent[v] != -1:
                    zero[parent[v]] += max(zero[v], one[v]); one[parent[v]] += zero[v]
            answer = max(zero[0], one[0])
            if n <= 8:
                enumerated = max(sum(a[i] for i in range(n) if mask >> i & 1)
                                 for mask in range(1 << n)
                                 if all(not (mask >> (u-1) & 1 and mask >> (v-1) & 1) for u, v in edges))
                assert answer == enumerated
            output.append(str(answer))
    return output


def small_cases(kind):
    rng = random.Random(2026102900 + kind)
    if kind == 1:
        pairs = [(u, v) for u in (1, 2) for v in (1, 2)]
        for weights in itertools.product((None, -1, 2), repeat=4):
            edges = [(u, v, w) for (u, v), w in zip(pairs, weights) if w is not None]
            for k in (0, 1, 2, 3, 6):
                for t in (1, 2):
                    yield walk(2, edges, 1, t, k)
        for _ in range(160):
            n = rng.randint(1, 7)
            edges = [(rng.randint(1, n), rng.randint(1, n), rng.randint(-10, 10)) for _ in range(rng.randint(0, 40))]
            yield walk(n, edges, rng.randint(1, n), rng.randint(1, n), rng.randint(0, 20))
    elif kind == 2:
        for row in itertools.product((-3, 0, 4), repeat=3):
            for days in range(9):
                yield calendar([row], days)
        for _ in range(180):
            p = rng.randint(1, 7)
            yield calendar([rng.choices([-9, -1, 0, 1, 7], k=3) for _ in range(p)], rng.randint(0, 40))
    elif kind == 3:
        for length in range(7):
            for word in itertools.product((1, 2), repeat=length):
                instructions = [(1, 1), (1, 2)]
                if not word:
                    instructions.append((3, 1, 0))
                else:
                    current = word[0]
                    for value in word[1:]:
                        instructions.append((2, current, value)); current = len(instructions)
                    instructions.append((3, current, 3))
                yield grammar(2, instructions)
        for _ in range(220):
            c = rng.randint(1, 5); n = rng.randint(1, 35); instructions = []; length = [0]
            for i in range(1, n+1):
                op = rng.randint(1, 3) if i > 1 else 1
                if op == 1:
                    instructions.append((1, rng.randint(1, c))); length.append(1)
                else:
                    u = rng.randrange(1, i)
                    if op == 2:
                        v = rng.randrange(1, i)
                        if length[u] + length[v] > 300:
                            instructions.append((3, u, 0)); length.append(0)
                        else:
                            instructions.append((2, u, v)); length.append(length[u]+length[v])
                    else:
                        k = rng.randint(0, min(4, 300//length[u])) if length[u] else rng.randint(0, 4)
                        instructions.append((3, u, k)); length.append(length[u]*k)
            yield grammar(c, instructions)
    elif kind == 4:
        for n in range(1, 6):
            for a in itertools.product((-2, 0, 3), repeat=n):
                ops = [(2, l, r) for l in range(1, n+1) for r in range(l, n+1)]
                rng.shuffle(ops)
                for p in range(1, n+1):
                    ops += [(1, p, 5-p), (2, 1, n)]
                yield positions(a, ops)
        for _ in range(160):
            n = rng.randint(1, 25); a = rng.choices([-10**9, -1, 0, 1, 10**9], k=n); ops = [(2, 1, n)]
            for _ in range(35):
                if rng.randrange(2):
                    ops.append((1, rng.randint(1, n), rng.randint(-20, 20)))
                else:
                    l, r = sorted((rng.randint(1, n), rng.randint(1, n))); ops.append((2, l, r))
            yield positions(a, ops)
    else:
        for n in range(1, 5):
            for sequence in itertools.product(range(1, n+1), repeat=max(0, n-2)):
                edges = labelled_tree(n, sequence)
                for a in itertools.product((-1, 3), repeat=n):
                    updates = [(u, x) for u in range(1, n+1) for x in (5, -6, 0)]
                    yield tree(a, edges, updates)
        for _ in range(150):
            n = rng.randint(1, 35); edges = labelled_tree(n, [rng.randint(1, n) for _ in range(max(0, n-2))])
            rng.shuffle(edges)
            updates = [(rng.randint(1, n), rng.choice([-10**9, -1, 0, 1, 10**9])) for _ in range(35)]
            yield tree(rng.choices([-4, 0, 7], k=n), edges, updates)
        for n in (1, 2, 5, 10, 20):
            for sign in (-1, 1):
                yield tree([sign*10**9]*n, [(u, u+1) for u in range(1, n)],
                           [(n, x) for x in (0, 10**9, -10**9, 0, 10**9)])


def audit_statement(p):
    text = (p / "task.md").read_text()
    assert text.splitlines()[0].startswith(f"# {p.name.upper()} — ")
    expected = ["Đề bài", "Dữ liệu vào", "Dữ liệu ra", "Ràng buộc"]
    for i in range(1, 4):
        expected += [f"Sample Input {i}", f"Sample Output {i}"]
    expected.append("Giải thích")
    assert re.findall(r"^### (.+)$", text, re.M) == expected
    assert len(re.findall(r"^#+ ", text, re.M)) == len(expected)+1
    assert "Subtask" not in text and not list(p.glob("*.html"))
    for i in range(3):
        for label, folder, ext in [("Input", "in", "in"), ("Output", "out", "out")]:
            match = re.search(rf"### Sample {label} {i+1}\n\n```text\n(.*?)```", text, re.S)
            assert match and match[1] == (p / folder / f"example_{i:02}.{ext}").read_text(), (p.name, label, i)
    solution = (p / "solution.md").read_text()
    assert not re.search(r"oracle|verifier|checker|benchmark|kiểm thử|kiểm chứng|bộ sinh|chạy test", solution, re.I)


def invalid_checks(p, kind):
    sample = (p / "gen/example_00.in").read_text()
    cases = ["", sample+"0\n", sample.rsplit("\n", 2)[0]+"\n"]
    if kind == 1:
        cases += ["0 0 1 1 0\n", "31 0 1 1 0\n", "1 2001 1 1 1\n", "1 -1 1 1 0\n",
                  "1 0 0 1 0\n", "1 0 1 2 0\n", "1 0 1 1 -1\n", "1 0 1 1 1000000000001\n",
                  "1 1 1 1 1\n1 1 1000001\n", "1 1 1 1 1\n1 1 -1000001\n", "1 1 1 1 1\n1 2 0\n"]
    elif kind == 2:
        cases += ["0 0\n", "100001 1\n", "1 -1\n0 0 0\n", "1 1000000000001\n0 0 0\n",
                  "1 1\n0 0 1000001\n", "1 1\n-1000001 0 0\n", "1 1\n1 2\n", "1 1\n1 2 3 4\n"]
    elif kind == 3:
        cases += ["0 1\n", "20001 1\n", "1 0\n1 1\n", "1 6\n1 1\n", "1 1\n1 0\n",
                  "1 1\n1 2\n", "1 1\n2 1 1\n", "1 1\n3 1 0\n", "1 1\n4 1\n",
                  "2 1\n1 1\n2 1 2\n", "2 1\n1 1\n3 1 -1\n", "2 1\n1 1\n3 1 1000000000001\n",
                  "3 1\n1 1\n3 1 1000000000000\n2 2 1\n", "3 1\n1 1\n3 1 1000000000000\n3 2 2\n"]
    elif kind == 4:
        cases += ["0 1\n", "1 0\n0\n", "100001 1\n", "1 100001\n0\n",
                  positions([10**9+1], [(2, 1, 1)]), positions([-10**9-1], [(2, 1, 1)]),
                  positions([0], [(1, 1, 10**9+1), (2, 1, 1)]), positions([0], [(1, 0, 0), (2, 1, 1)]),
                  positions([0], [(2, 1, 2)]), positions([0, 0], [(2, 2, 1)]),
                  positions([0], [(3, 1, 1)]), positions([0], [(1, 1, 0)])]
    else:
        cases += ["0 1\n", "1 0\n0\n", "100001 1\n", "1 100001\n0\n",
                  tree([10**9+1], [], [(1, 0)]), tree([-10**9-1], [], [(1, 0)]),
                  tree([0], [], [(1, 10**9+1)]), tree([0], [], [(0, 0)]), tree([0], [], [(2, 0)]),
                  tree([0, 0], [(1, 1)], [(1, 0)]), tree([0]*3, [(1, 2), (2, 1)], [(1, 0)]),
                  tree([0]*4, [(1, 2), (2, 3), (3, 1)], [(1, 0)])]
    for data in cases:
        result = subprocess.run([str(p / "verifier")], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p.name, "Accepted invalid input", data)
    return len(cases)


def checker_checks(p):
    count = 0
    with tempfile.TemporaryDirectory() as directory:
        actual, answer = Path(directory) / "actual", Path(directory) / "answer"
        for case in ("example_00", "example_01", "max_00"):
            inp = p / "in" / f"{case}.in"; good = (p / "out" / f"{case}.out").read_text()
            answer.write_text(good); words = good.split()
            variants = [(good, True), (" \n\t"+good.strip()+" \n", True), ("", False),
                        (good+"0\n", False), (good+"garbage\n", False), ("x\n", False),
                        ("1.0\n", False), ("9"*50+"\n", False)]
            for i in sorted({0, len(words)-1}):
                wrong = words.copy(); wrong[i] = "0" if wrong[i] == "IMPOSSIBLE" else str(int(wrong[i])+1)
                variants.append(("\n".join(wrong)+"\n", False))
            if len(words) > 1:
                variants.append(("\n".join(words[:-1])+"\n", False))
            if p.name == "hanhtrinh":
                variants.append(("IMPOSSIBLE\n" if words[0] != "IMPOSSIBLE" else "-1\n", False))
            for data, accepted in variants:
                actual.write_text(data)
                result = subprocess.run([str(p / "checker"), str(inp), str(actual), str(answer)], capture_output=True)
                assert (result.returncode == 0) == accepted, (p.name, data[:80], result.stderr)
                count += 1
    return count


def official_checks(problem, kind):
    p = problem.basedir; files = sorted((p / "in").glob("*.in"))
    expected_count = sum(test["number"] for test in problem.config["tests"])
    assert len(files) == expected_count == 30
    for i, path in enumerate(files, 1):
        expected = run(ORACLE, path.read_text(), kind).split()
        actual = (p / "out" / path.with_suffix(".out").name).read_text().split()
        assert expected == actual, (str(path), expected[:10], actual[:10])
        if i % 5 == 0:
            print(f"{p.name}: independently checked {i}/{len(files)} official tests", flush=True)
    for test in problem.config["tests"]:
        if test["name"].endswith(".cpp"):
            stem = Path(test["name"]).stem
            assert run(p / "gen" / stem, "", 0) == (p / "in" / f"{stem}_00.in").read_text()
    for i in range(8):
        header = list(map(int, (p / "in" / f"max_{i:02}.in").open().readline().split()))
        if kind == 1:
            assert header[0] == 30
        elif kind == 2:
            assert header[0] >= 99991
        elif kind == 3:
            assert header[0] == 20000
        else:
            assert header == [100000, 100000]
    if kind == 1:
        assert (p / "out/max_00.out").read_text().strip() == str(10**18)
        assert (p / "out/max_02.out").read_text().strip() == str(-10**18)
    if kind == 2:
        assert (p / "out/max_00.out").read_text().strip() == str((10**12//3*2 + 10**12%3)*10**6)
    return len(files)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--problem", nargs="+", choices=NAMES, default=NAMES)
    parser.add_argument("--update-hashes", action="store_true")
    args = parser.parse_args(); logging.basicConfig(level=logging.ERROR, format="%(message)s")
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
        p = problem.basedir; started = time.monotonic(); kind = NAMES.index(p.name)+1
        print(f"{p.name}: generating and validating official tests...", flush=True)
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True)
        problem.judge(problem.get_correct_filename(), {}); assert problem.check_all_solutions_used()
        audit_statement(p); official = official_checks(problem, kind)
        print(f"{p.name}: checking small cases against direct DP/enumeration...", flush=True)
        count = 0
        for data in small_cases(kind):
            expected = brute(kind, data); run(p / "verifier", data)
            actual = run(p / "sol/correct", data).split(); oracle = run(ORACLE, data, kind).split()
            assert actual == oracle == expected, (p.name, data, expected[:15], actual[:15], oracle[:15])
            count += 1
        invalid = invalid_checks(p, kind); checker = checker_checks(p)
        if args.update_hashes:
            problem.ignore_warning = True; problem.write_hashes()
        problem.assert_hashes()
        print(f"{p.name}: PASS; {official} official; {count} small; {invalid} invalid-input; "
              f"{checker} checker tests; hashes verified; {time.monotonic()-started:.1f}s", flush=True)


if __name__ == "__main__":
    main()
