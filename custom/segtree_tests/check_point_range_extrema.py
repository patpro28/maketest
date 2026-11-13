"""Generate and verify SEGTREE024 and SEGTREE026–029 without exporting HTML."""
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

KINDS = (24, 26, 27, 28, 29)
NAMES = [f"segtree{kind:03}" for kind in KINDS]
ORACLE = HERE / "oracle_point_range_extrema"
SIZE_LIMIT = 200000
VALUE_LIMIT = 10**9
QUERY_ARITY = {24: 4, 26: 5, 27: 5, 28: 3, 29: 3}


def encode(values, operations):
    header = (len(values), len(operations))
    return "\n".join(" ".join(map(str, row)) for row in [header, values, *operations]) + "\n"


def decode(kind, data):
    lines = data.splitlines()
    n, q = map(int, lines[0].split())
    values = list(map(int, lines[1].split()))
    operations = [tuple(map(int, line.split())) for line in lines[2:]]
    assert len(values) == n and len(operations) == q
    assert all(op[0] in (1, 2) and len(op) == (3 if op[0] == 1 else QUERY_ARITY[kind])
               for op in operations)
    return values, operations


def brute(kind, data):
    a, operations = decode(kind, data)
    answers = []
    for type_, first, third, *extra in operations:
        if type_ == 1:
            a[first - 1] = third
            continue

        values = a[first - 1:third]
        if kind == 24:
            answer = max(abs(value - extra[0]) for value in values)
        elif kind == 26:
            u, v = extra
            answer = max(value for index, value in enumerate(values, first) if not u <= index <= v)
        elif kind == 27:
            u, v = extra
            answer = max(abs(x - y) for x in values for y in a[u - 1:v])
        elif kind == 28:
            answer = max(value if offset % 2 == 0 else -value
                         for offset, value in enumerate(values))
        else:
            distinct = sorted(set(values), reverse=True)
            answer = distinct[1] if len(distinct) >= 2 else -1
        answers.append(str(answer))
    return answers


def all_queries(kind, n):
    ranges = [(l, r) for l in range(1, n + 1) for r in range(l, n + 1)]
    if kind == 24:
        return [(2, l, r, h) for l, r in ranges for h in (-VALUE_LIMIT, -2, 0, 3, VALUE_LIMIT)]
    if kind == 26:
        return [(2, l, r, u, v) for l, r in ranges for u, v in ranges
                if l <= u <= v <= r and (l, r) != (u, v)]
    if kind == 27:
        return [(2, l, r, u, v) for l, r in ranges for u, v in ranges if r < u]
    return [(2, l, r) for l, r in ranges]


def random_query(kind, n, rng):
    l, r = sorted((rng.randint(1, n), rng.randint(1, n)))
    if kind == 24:
        return (2, l, r, rng.choice((-VALUE_LIMIT, -3, 0, 3, VALUE_LIMIT)))
    if kind in (26, 27):
        if n == 1:
            return (1, 1, 0)
        if l == r:
            l, r = (l - 1, r) if l > 1 else (1, 2)
        if kind == 26:
            u, v = sorted((rng.randint(l, r), rng.randint(l, r)))
            if (u, v) == (l, r):
                v -= 1
            return (2, l, r, u, v)
        cut = rng.randint(l, r - 1)
        return (2, l, rng.randint(l, cut), rng.randint(cut + 1, r), r)
    return (2, l, r)


def check_case(path, kind, data):
    run(path / "verifier", data)
    expected = brute(kind, data)
    assert run(path / "sol/correct", data).split() == expected, (path, data, expected)
    assert run(ORACLE, data, kind).split() == expected, (path, "block reference", data, expected)


def small_checks(path, kind):
    alphabet = (0, 1, 4) if kind == 29 else (-4, 0, 3)
    count = 0
    for n in range(1, 5):
        queries = all_queries(kind, n)
        operations = list(queries)
        for index in range(1, n + 1):
            for value in alphabet:
                operations.append((1, index, value))
                operations.extend(queries)
        for a in product(alphabet, repeat=n):
            check_case(path, kind, encode(a, operations))
            count += 1

    rng = random.Random(20261112 + kind)
    values = (0, 0, 1, 4, VALUE_LIMIT) if kind == 29 else (-VALUE_LIMIT, -4, -1, 0, 1, 4, VALUE_LIMIT)
    for case in range(140):
        n = rng.randint(1, 40)
        operations = []
        for _ in range(rng.randint(1, 80)):
            if rng.randrange(100) < (20, 50, 85)[case % 3]:
                operations.append((1, rng.randint(1, n), rng.choice(values)))
            else:
                operations.append(random_query(kind, n, rng))
        check_case(path, kind, encode(rng.choices(values, k=n), operations))
        count += 1

    n = 905
    operations = [(1, i, rng.choice(values)) for i in (1, 448, 449, 450, 896, 897, n)]
    operations += {
        24: [(2, 1, n, -VALUE_LIMIT), (2, 448, 450, VALUE_LIMIT), (2, 449, 899, 0)],
        26: [(2, 1, n, 448, 897), (2, 448, 896, 448, 449), (2, 449, 897, 896, 897)],
        27: [(2, 1, 449, 450, n), (2, 448, 449, 896, 897), (2, 449, 449, n, n)],
        28: [(2, 1, n), (2, 2, n), (2, 448, 899), (2, 449, 899), (2, 896, 897)],
        29: [(2, 1, n), (2, 1, 448), (2, 448, 449), (2, 449, 897), (2, 896, 897)],
    }[kind]
    check_case(path, kind, encode(rng.choices(values, k=n), operations))
    return count + 1


def invalid_checks(path, kind):
    initial = [0, 0, 3, 4]
    query = {
        24: (2, 1, 4, 0),
        26: (2, 1, 4, 2, 3),
        27: (2, 1, 2, 3, 4),
        28: (2, 1, 4),
        29: (2, 1, 4),
    }[kind]

    def data(op=query, values=initial):
        return encode(values, [op])

    valid = data()
    below_min = -1 if kind == 29 else -VALUE_LIMIT - 1
    bad = [
        "0 1\n", "200001 1\n", "4 0\n", "4 200001\n",
        data(values=[below_min, 0, 0, 0]), data(values=[VALUE_LIMIT + 1, 0, 0, 0]),
        "4 1\n0 0 0\n" + " ".join(map(str, query)) + "\n",
        valid + "1 1 0\n", "\n".join(valid.splitlines()[:-1]) + "\n",
        data((0, 1, 0)), data((3, *query[1:])), data((2, 0, *query[2:])),
        data((2, 1, 5, *query[3:])), data((2, 4, 1, *query[3:])),
        data(query[:-1]), data((*query, 0)), data((1, 1)),
        data((1, 0, 0)), data((1, 5, 0)),
        data((1, 1, below_min)), data((1, 1, VALUE_LIMIT + 1)), data((1, 1, 0, 0)),
    ]
    if kind == 24:
        bad.extend([data((2, 1, 4, -VALUE_LIMIT - 1)), data((2, 1, 4, VALUE_LIMIT + 1))])
    if kind == 26:
        bad.extend(data(op) for op in [
            (2, 1, 4, 1, 4), (2, 1, 1, 1, 1), (2, 2, 4, 1, 3),
            (2, 1, 3, 2, 4), (2, 1, 4, 3, 2),
        ])
    if kind == 27:
        bad.extend(data(op) for op in [
            (2, 1, 2, 2, 4), (2, 1, 3, 2, 4), (2, 3, 4, 1, 2),
            (2, 1, 2, 4, 3), (2, 1, 2, 3, 5),
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
    dimensions = set()
    for file in files:
        data = file.read_text()
        values, operations = decode(kind, data)
        dimensions.add((len(values), len(operations)))
        output = (path / "out" / file.with_suffix(".out").name).read_text()
        lines = output.splitlines()
        assert len(lines) == sum(op[0] == 2 for op in operations), file
        assert all(len(line.split()) == 1 for line in lines), file
        expected = output.split()
        assert run(ORACLE, data, kind).split() == expected, (file, "block reference differs")
        if len(values) <= 200 and len(operations) <= 500:
            assert brute(kind, data) == expected, (file, "direct reference differs")
    assert (SIZE_LIMIT, SIZE_LIMIT) in dimensions, (path, "missing maximum dimensions")
    assert any(n == 1 for n, _ in dimensions), (path, "missing single-element input")


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
    print(f"Compiling {len(problems)} point-update/extrema problems...", flush=True)
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
