"""Generate and verify SEGTREE221–229 without exporting HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from itertools import product
import logging
from pathlib import Path
import random
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(ROOT))
from problem import Problem
from check import audit_statement, check_checker, run
from check_foundations import checked_compile

KINDS = range(221, 230)
NAMES = [f"segtree{kind}" for kind in KINDS]
ORACLE = HERE / "oracle_range_add_extrema"
SIZE_LIMIT = 100000
VALUE_LIMIT = 10**9
QUERY_LIMIT = 10**15


def encode(kind, values, operations, slope=0):
    header = [len(values), len(operations)]
    if kind == 227:
        header.append(slope)
    lines = [header, values, *operations]
    return "\n".join(" ".join(map(str, line)) for line in lines) + "\n"


def decode(kind, data):
    lines = data.splitlines()
    n, q, *parameters = map(int, lines[0].split())
    assert len(parameters) == (kind == 227)
    values = list(map(int, lines[1].split()))
    operations = [tuple(map(int, line.split())) for line in lines[2:]]
    assert len(values) == n and len(operations) == q
    query_arity = {227: 5, 229: 8}.get(kind, 3)
    assert all(len(op) == (query_arity if op[0] == 1 else 4) for op in operations)
    return values, operations, parameters[0] if parameters else 0


def line_error(values, slope, lower, upper):
    def error(height):
        return max(abs(value - (height + offset * slope)) for offset, value in enumerate(values))

    if upper - lower <= 20:
        return min(error(height) for height in range(lower, upper + 1))

    # The error is convex as a function of the proposed integer height.
    while lower < upper:
        mid = (lower + upper) // 2
        if error(mid) <= error(mid + 1):
            upper = mid
        else:
            lower = mid + 1
    return error(lower)


def budget_spread(group_a, group_b, outside, budget):
    unmodified = group_a + group_b + outside
    original_width = max(unmodified) - min(unmodified)
    if budget <= 16:
        best = original_width
        for x in range(budget + 1):
            raised_a = [value + x for value in group_a]
            for y in range(budget - x + 1):
                candidate = raised_a + [value + y for value in group_b] + outside
                best = min(best, max(candidate) - min(candidate))
        return best

    # For larger budgets, check the pairwise inequalities between the three
    # groups. The bounds on x, y, and x-y give the least feasible total shift.
    a_low, a_high = min(group_a), max(group_a)
    b_low, b_high = min(group_b), max(group_b)
    outside_low, outside_high = (min(outside), max(outside)) if outside else (0, 0)

    def feasible(width):
        if width < max(a_high - a_low, b_high - b_low, outside_high - outside_low):
            return False
        x_low, y_low = 0, 0
        x_high, y_high = budget, budget
        if outside:
            x_low = max(0, outside_high - a_low - width)
            y_low = max(0, outside_high - b_low - width)
            x_high = min(budget, outside_low - a_high + width)
            y_high = min(budget, outside_low - b_high + width)
        # The smallest feasible x and y start at their lower bounds. Only
        # the smaller side of a violated difference constraint has to rise.
        x = max(x_low, y_low + b_high - a_low - width)
        y = max(y_low, x_low + a_high - b_low - width)
        return x <= x_high and y <= y_high and x + y <= budget

    lo, hi = 0, original_width
    while lo < hi:
        mid = (lo + hi) // 2
        if feasible(mid):
            hi = mid
        else:
            lo = mid + 1
    return lo


def brute(kind, data):
    a, operations, slope = decode(kind, data)
    n = len(a)
    answers = []
    for operation in operations:
        t, left, right, *extra = operation
        first = left - 1
        if kind == 225 and left > right:
            positions = [*range(first, n), *range(right)]
        else:
            positions = range(first, right)
        if t == 0:
            for index in positions:
                a[index] += extra[0]
            continue

        values = [a[index] for index in positions]
        if kind == 221:
            answer = (min(values),)
        elif kind == 222:
            answer = (max(values) - min(values),)
        elif kind == 223:
            minimum = min(values)
            answer = (minimum, left + values.index(minimum))
        elif kind == 224:
            maximum = max(values)
            answer = (maximum, values.count(maximum))
        elif kind == 225:
            answer = (max(values),)
        elif kind == 226:
            answer = (0,)
            if len(values) >= 2:
                candidates = (values[:i] + values[i + 1:] for i in range(len(values)))
                answer = (min(max(c) - min(c) for c in candidates),)
        elif kind == 227:
            answer = (line_error(values, slope, *extra),)
        elif kind == 228:
            candidates = [abs(a[i] - a[n - 1 - i]) for i in positions
                          if i < n - 1 - i and first <= n - 1 - i < right]
            answer = (max(candidates, default=0),)
        else:
            u, v, s, t, budget = extra
            outside = a[first:u - 1] + a[v:s - 1] + a[t:right]
            answer = (budget_spread(a[u - 1:v], a[s - 1:t], outside, budget),)
        answers.extend(map(str, answer))
    return answers


def check_case(path, kind, data):
    run(path / "verifier", data)
    expected = brute(kind, data)
    assert run(path / "sol/correct", data).split() == expected, (path, data, expected)
    assert run(ORACLE, data, kind).split() == expected, (path, "reference", data, expected)


def make_query(kind, left, right, rng):
    if kind == 227:
        center = rng.choice([-QUERY_LIMIT + 20, QUERY_LIMIT - 20, -VALUE_LIMIT,
                             VALUE_LIMIT, rng.randint(-12, 12)])
        return (1, left, right, center, center + rng.randint(0, 20))
    if kind == 229:
        if left == right:
            return (0, left, right, rng.randint(-3, 3))
        cut = rng.randint(left, right - 1)
        u = rng.randint(left, cut)
        v = rng.randint(u, cut)
        s = rng.randint(cut + 1, right)
        t = rng.randint(s, right)
        return (1, left, right, u, v, s, t,
                rng.choice([0, 1, 5, 16, 17, VALUE_LIMIT, QUERY_LIMIT]))
    return (1, left, right)


def small_checks(path, kind):
    count = 0
    rng = random.Random(20261112 + kind)
    for n in range(1, 5):
        ranges = [(l, r) for l in range(1, n + 1) for r in range(1, n + 1)
                  if kind == 225 or l <= r]
        if kind == 227:
            queries = [(1, l, r, p, s) for l, r in ranges for p, s in [(-8, 8), (2, 4), (-4, -2)]]
        elif kind == 229:
            queries = [(1, 1, n, u, v, s, t, budget)
                       for u, v in ranges for s, t in ranges if v < s
                       for budget in (0, 1, 5)]
        else:
            queries = [(1, l, r) for l, r in ranges]
        operations = list(queries)
        for left, right in ranges:
            for delta in (-3, 2):
                operations.append((0, left, right, delta))
                operations.extend(queries)
        for values in product((-3, 0, 2), repeat=n):
            slope = rng.choice([-4, 0, 3])
            check_case(path, kind, encode(kind, values, operations, slope))
            count += 1

    values = [-VALUE_LIMIT, -7, -3, -1, 0, 1, 5, VALUE_LIMIT]
    for trial in range(120):
        n = rng.randint(1, 45)
        slope = rng.choice(values)
        operations = []
        for _ in range(rng.randint(1, 90)):
            left, right = rng.randint(1, n), rng.randint(1, n)
            if kind != 225 and left > right:
                left, right = right, left
            if rng.randrange(100) < (20, 50, 85)[trial % 3]:
                operations.append((0, left, right, rng.choice(values)))
            else:
                operations.append(make_query(kind, left, right, rng))
        check_case(path, kind, encode(kind, rng.choices(values, k=n), operations, slope))
        count += 1

    n = 963
    operations = []
    for left, right in [(1, n), (1, 321), (320, 323), (319, 641), (321, 960), (640, n)]:
        operations.extend([(0, left, right, VALUE_LIMIT),
                           make_query(kind, left, right, rng), make_query(kind, 1, n, rng),
                           (0, left, right, -VALUE_LIMIT), make_query(kind, 1, n, rng)])
    check_case(path, kind, encode(kind, rng.choices(values, k=n), operations, -VALUE_LIMIT))
    return count + 1


def invalid_checks(path, kind):
    initial = [-2, 0, 4, 4]
    query = {227: (1, 1, 4, -1, 3), 229: (1, 1, 4, 1, 2, 3, 4, 5)}.get(kind, (1, 1, 4))

    def data(op=query, values=initial, slope=1):
        return encode(kind, values, [op], slope)

    valid = data()
    header_extra = " 0" if kind == 227 else ""
    bad = [
        f"0 1{header_extra}\n", f"100001 1{header_extra}\n",
        f"4 0{header_extra}\n", f"4 100001{header_extra}\n",
        data(values=[-VALUE_LIMIT - 1, 0, 0, 0]),
        data(values=[VALUE_LIMIT + 1, 0, 0, 0]),
        f"4 1{header_extra}\n0 0 0\n" + " ".join(map(str, query)) + "\n",
        valid + "0 1 1 0\n", "\n".join(valid.splitlines()[:-1]) + "\n",
        data((2, *query[1:])), data((1, 0, *query[2:])), data((1, 1, 5, *query[3:])),
        data(query[:-1]), data((*query, 0)), data((0, 1, 4)),
        data((0, 0, 4, 1)), data((0, 1, 5, 1)),
        data((0, 1, 4, -VALUE_LIMIT - 1)), data((0, 1, 4, VALUE_LIMIT + 1)),
        data((0, 1, 4, 0, 0)),
    ]
    if kind != 225:
        bad.extend([data((1, 4, 1, *query[3:])), data((0, 4, 1, 1))])
    if kind == 227:
        bad.extend([data(slope=-VALUE_LIMIT - 1), data(slope=VALUE_LIMIT + 1),
                    data((1, 1, 4, 2, 1)), data((1, 1, 4, -QUERY_LIMIT - 1, 0)),
                    data((1, 1, 4, 0, QUERY_LIMIT + 1))])
    if kind == 229:
        bad.extend(data(op) for op in [
            (1, 2, 4, 1, 2, 3, 4, 0), (1, 1, 3, 1, 2, 3, 4, 0),
            (1, 1, 4, 2, 1, 3, 4, 0), (1, 1, 4, 1, 2, 4, 3, 0),
            (1, 1, 4, 1, 3, 3, 4, 0), (1, 1, 4, 3, 4, 1, 2, 0),
            (1, 1, 4, 1, 2, 3, 4, -1), (1, 1, 4, 1, 2, 3, 4, QUERY_LIMIT + 1),
        ])
    for case in bad:
        result = subprocess.run([str(path / "verifier")], input=case, text=True, capture_output=True)
        assert result.returncode != 0, (path, "accepted invalid input", case)
    return len(bad)


def audit(problem, files):
    path = problem.basedir
    assert problem.config["timelimit"] == problem.config["upload"]["time_limit"] == 1.0
    assert problem.config["upload"]["types"] == ["ds_segment_tree"]
    assert len(files) == 36
    assert (path / "out/edge_10.out").read_text() == ""
    assert not list(path.rglob("*.html"))
    assert not any(line.startswith("# ") for line in (path / "solution.md").read_text().splitlines())
    audit_statement(path, with_subtask=False)


def verify_outputs(path, kind, files):
    maximum_size = False
    for file in files:
        data = file.read_text()
        values, operations, _ = decode(kind, data)
        maximum_size |= len(values) == len(operations) == SIZE_LIMIT
        output = (path / "out" / file.with_suffix(".out").name).read_text()
        lines = output.splitlines()
        fields = 2 if kind in (223, 224) else 1
        assert len(lines) == sum(op[0] == 1 for op in operations), file
        assert all(len(line.split()) == fields for line in lines), file
        expected = output.split()
        assert run(ORACLE, data, kind).split() == expected, (file, "block reference differs")
        if len(values) <= 200 and len(operations) <= 500:
            assert brute(kind, data) == expected, (file, "direct reference differs")
    assert maximum_size, (path, "missing maximum dimensions")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--problem", nargs="+", choices=NAMES, default=NAMES)
    parser.add_argument("--update-hashes", action="store_true")
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format="%(message)s")

    problems = [Problem(ROOT, ROOT / "custom" / name) for name in args.problem]
    sources = [ORACLE.with_suffix(".cpp")]
    for problem in problems:
        path = problem.basedir
        problem.health_check()
        problem.generate_params_h()
        sources.extend([path / "sol/correct.cpp", problem.checker, problem.verifier])
        sources.extend(path / "gen" / test["name"] for test in problem.config["tests"]
                       if test["name"].endswith(".cpp"))
    print(f"Compiling {len(problems)} range-add/extrema problems...", flush=True)
    with ThreadPoolExecutor(max_workers=4) as executor:
        list(executor.map(checked_compile, sources))

    count = 0
    for problem in problems:
        path = problem.basedir
        kind = int(path.name[7:])
        problem.make_inputs()
        problem.verify_inputs()
        problem.make_outputs(True)
        problem.judge(path / "sol/correct.cpp", {})
        assert problem.check_all_solutions_used()
        files = sorted((path / "in").glob("*.in"))
        audit(problem, files)
        verify_outputs(path, kind, files)
        for test in problem.config["tests"]:
            if test["name"].endswith(".cpp"):
                executable = path / "gen" / Path(test["name"]).stem
                for seed in range(test["number"]):
                    saved = path / "in" / f"{executable.name}_{seed:02}.in"
                    assert run(executable, "", seed) == saved.read_text(), saved
        additional = small_checks(path, kind)
        invalid = invalid_checks(path, kind)
        check_checker(path, kind)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        count += additional
        print(f"{path.name}: {len(files)} tests, {additional} additional comparisons, "
              f"{invalid} invalid inputs, 1 s and hashes OK", flush=True)
    print(f"Verified {36 * len(problems)} official tests and {count} additional cases.", flush=True)


if __name__ == "__main__":
    main()
