"""Generate and verify SEGTREE016–019 without exporting HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from itertools import product
import logging
from pathlib import Path
import random
import re
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(ROOT))

from problem import Problem
from check import audit_statement, check_checker, run
from check_foundations import checked_compile

# Match the stable kinds used by the generators and the reference solution.
CASE_KINDS = {
    "segtree016": 16,
    "segtree017": 17,
    "segtree018": 19,
    "segtree019": 18,
}
NAMES = list(CASE_KINDS)
ORACLE = HERE / "oracle_point_range_sum"
LIMIT = 10**9


def encode(kind, a, operations, step, weights):
    head = f"{len(a)} {len(operations)}"
    if kind == 18:
        head += f" {step}"
    lines = [head, " ".join(map(str, a))]
    if kind == 19:
        lines.append(" ".join(map(str, weights)))
    lines.extend(" ".join(map(str, op)) for op in operations)
    return "\n".join(lines) + "\n"


def decode(kind, data):
    lines = data.splitlines()
    n, q, *extra = map(int, lines[0].split())
    a = list(map(int, lines[1].split()))
    weights = list(map(int, lines[2].split())) if kind == 19 else None
    operations = [tuple(map(int, line.split())) for line in lines[3 if kind == 19 else 2:]]
    assert len(a) == n and len(operations) == q
    assert weights is None or len(weights) == n
    return a, operations, extra[0] if extra else 1, weights


def brute(kind, data):
    a, operations, step, weights = decode(kind, data)
    answers = []
    for operation in operations:
        t, i, x, *rest = operation
        if t == 1:
            if kind == 16:
                a[i - 1] -= rest[0]
                a[x - 1] += rest[0]
            elif kind == 17:
                a[i - 1] += x
            else:
                a[i - 1] = x
        else:
            if kind == 17:
                length = (x - i) % len(a) + 1
                total = sum(a[(i - 1 + offset) % len(a)] for offset in range(length))
            elif kind == 19:
                total = sum(a[j] * weights[j] for j in range(i - 1, x))
            else:
                total = sum(a[i - 1:x:step])
            answers.append(str(total))
    return answers


def check_small(p, kind, data):
    run(p / "verifier", data)
    expected = brute(kind, data)
    assert run(p / "sol/correct", data).split() == expected, (p, data, expected)
    assert run(ORACLE, data, kind).split() == expected, (p, "Fenwick reference", data, expected)


def small_checks(p, kind):
    count = 0
    for n in range(1, 5):
        indices = range(1, n + 1)
        queries = [(2, l, r) for l in indices for r in indices if kind == 17 or l <= r]
        if kind == 16:
            updates = [(1, i, j, x) for i in indices for j in indices for x in (0, 2)]
        else:
            updates = [(1, i, x) for i in indices for x in (-2, 0, 3)]
        operations = list(queries)
        for update in updates:
            operations.append(update)
            operations.extend(queries)
        steps = indices if kind == 18 else (1,)
        weights = [(-2, 0, 3)[i % 3] for i in range(n)]
        for a in product((-2, 0, 3), repeat=n):
            for step in steps:
                check_small(p, kind, encode(kind, a, operations, step, weights))
                count += 1

    rng = random.Random(20261111 + kind)
    for case in range(150):
        n = rng.randint(1, 40)
        step = rng.choice((1, n, rng.randint(1, n)))
        values = (-LIMIT, -3, -1, 0, 1, 3, LIMIT)
        a = rng.choices(values, k=n)
        weights = rng.choices((-10000, -3, 0, 4, 10000), k=n)
        operations = []
        for _ in range(rng.randint(1, 100)):
            left, right = rng.randint(1, n), rng.randint(1, n)
            if rng.randrange(100) < (20, 50, 85)[case % 3]:
                if kind == 16:
                    operations.append((1, left, right, rng.choice((0, 1, LIMIT))))
                else:
                    operations.append((1, left, rng.choice(values)))
            else:
                if kind != 17 and left > right:
                    left, right = right, left
                operations.append((2, left, right))
        check_small(p, kind, encode(kind, a, operations, step, weights))
        count += 1
    return count


def invalid_checks(p, kind):
    a, weights = [-LIMIT, 0, LIMIT], [-10000, 0, 10000]

    def data(ops, values=a, step=2, fixed=weights):
        return encode(kind, values, ops, step, fixed)

    query = [(2, 1, 3)]
    valid = data(query)
    suffix = " 2" if kind == 18 else ""
    bad = [
        valid + "2 1 1\n", "\n".join(valid.splitlines()[:-1]) + "\n",
        data([(0, 1, 1)]), data([(3, 1, 1)]), data([(2, 0, 1)]),
        data([(2, 1, 4)]), data([(2, 1, 1, 0)]), data([(1, 1)]),
        data(query, values=[LIMIT + 1, 0, 0]), data(query, values=[-LIMIT - 1, 0, 0]),
    ]
    for n, q in ((0, 1), (200001, 1), (3, 0), (3, 200001)):
        bad.append(f"{n} {q}{suffix}\n")
    if kind != 17:
        bad.append(data([(2, 3, 1)]))
    if kind == 16:
        bad.extend(data([op]) for op in ((1, 1, 2, -1), (1, 1, 2, LIMIT + 1),
                                         (1, 1, 4, 0), (1, 4, 1, 0), (1, 1, 2)))
    else:
        bad.extend(data([op]) for op in ((1, 1, LIMIT + 1), (1, 1, -LIMIT - 1), (1, 4, 0)))
    if kind == 18:
        bad.extend(data(query, step=step) for step in (0, 4))
    if kind == 19:
        bad.extend(data(query, fixed=fixed) for fixed in ((-10001, 0, 0), (10001, 0, 0), (0, 0)))
    for case in bad:
        result = subprocess.run([str(p / "verifier")], input=case, text=True, capture_output=True)
        assert result.returncode != 0, (p, "accepted invalid input", case)
    return len(bad)


def audit(problem, kind, paths):
    p = problem.basedir
    upload = problem.config["upload"]
    assert problem.config["timelimit"] == upload["time_limit"] == 1.0
    assert upload["types"] == ["ds_segment_tree"]
    assert len(paths) == 36
    dimensions = [tuple(map(int, path.read_text().splitlines()[0].split()[:2])) for path in paths]
    assert (200000, 200000) in dimensions and any(n == 1 for n, _ in dimensions)
    assert any(n & (n - 1) for n, _ in dimensions)
    assert (p / "out/edge_10.out").read_text() == ""
    expected_extreme = {
        16: 200000 * LIMIT,
        17: 200001 * LIMIT,
        18: 199998 * LIMIT,
        19: 199998 * LIMIT * 10000,
    }
    assert (p / "out/max_01.out").read_text().split() == [str(expected_extreme[kind])]
    assert not list(p.rglob("*.html"))
    assert not re.search(r"^# ", (p / "solution.md").read_text(), re.M)
    audit_statement(p, with_subtask=False)


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
        sources.extend(p / "gen" / test["name"] for test in problem.config["tests"]
                       if test["name"].endswith(".cpp"))
    print(f"Compiling {len(problems)} point-update/range-sum problems...", flush=True)
    with ThreadPoolExecutor(max_workers=4) as executor:
        list(executor.map(checked_compile, sources))

    count = 0
    for problem in problems:
        p = problem.basedir
        kind = CASE_KINDS[p.name]
        problem.make_inputs()
        problem.verify_inputs()
        problem.make_outputs(True)
        problem.judge(p / "sol/correct.cpp", {})
        assert problem.check_all_solutions_used()
        paths = sorted((p / "in").glob("*.in"))
        audit(problem, kind, paths)
        for test in problem.config["tests"]:
            if test["name"].endswith(".cpp"):
                executable = p / "gen" / Path(test["name"]).stem
                for seed in range(test["number"]):
                    saved = p / "in" / f"{executable.name}_{seed:02}.in"
                    assert run(executable, "", seed) == saved.read_text()
        for path in paths:
            data = path.read_text()
            output = (p / "out" / path.with_suffix(".out").name).read_text()
            assert len(output.splitlines()) == sum(op[0] == 2 for op in decode(kind, data)[1])
            assert run(ORACLE, data, kind).split() == output.split(), (path, "Fenwick reference differs")
            if path.stem.startswith(("edge", "small", "example")):
                assert brute(kind, data) == output.split(), (path, "direct reference differs")
        additional = small_checks(p, kind)
        invalid = invalid_checks(p, kind)
        check_checker(p, kind)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        count += additional
        print(f"{p.name}: 36 tests, {additional} additional comparisons, "
              f"{invalid} invalid inputs, 1 s and hashes OK", flush=True)
    print(f"Verified {36 * len(problems)} official tests and {count} additional cases.", flush=True)


if __name__ == "__main__":
    main()
