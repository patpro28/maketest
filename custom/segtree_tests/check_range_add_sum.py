"""Generate and verify SEGTREE210–219 without exporting HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from itertools import product
import logging
import math
from pathlib import Path
import random
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(ROOT))
import toml
from problem import Problem
from check import audit_statement, check_checker, run
from check_foundations import checked_compile

KINDS = range(210, 220)
NAMES = [f"segtree{k}" for k in KINDS]
ORACLE = HERE / "oracle_range_add_sum"
LIMITS = {213: 1000, 215: 10**9, 218: 10000, 219: 10000}
AXIS_END = 10**9


def encode(kind, a, ops, setting=None, weights=None):
    if kind == 218:
        lines = [str(len(ops))]
    else:
        head = f"{len(a)} {len(ops)}"
        if kind in (215, 217):
            head += f" {setting}"
        lines = [head, " ".join(map(str, a))]
        if kind == 219:
            lines.append(" ".join(map(str, weights)))
    lines.extend(" ".join(map(str, op)) for op in ops)
    return "\n".join(lines) + "\n"


def decode(kind, data):
    lines = data.splitlines()
    if kind == 218:
        n, q, setting, a, weights, start = AXIS_END, int(lines[0]), None, [], [], 1
    else:
        n, q, *other = map(int, lines[0].split())
        setting = other[0] if other else None
        a = list(map(int, lines[1].split()))
        assert len(a) == n
        start = 3 if kind == 219 else 2
        weights = list(map(int, lines[2].split())) if kind == 219 else []
        assert kind != 219 or len(weights) == n
    ops = [tuple(map(int, line.split())) for line in lines[start:]]
    assert len(ops) == q
    return n, a, setting, weights, ops


def brute(kind, data):
    n, a, setting, weights, ops = decode(kind, data)
    answers = []
    if kind == 218:
        updates = []
        for t, left, right, *delta in ops:
            if t == 1:
                updates.append((left, right, delta[0]))
            else:
                answer = sum(x * max(0, min(right, r) - max(left, l) + 1)
                             for l, r, x in updates)
                answers.append(str(answer))
        return answers

    for t, left, right, *delta in ops:
        if kind == 211 and left > right:
            positions = [*range(left, n + 1), *range(1, right + 1)]
        else:
            positions = range(left, right + 1, setting if kind == 217 else 1)
        if t == 1:
            for i in positions:
                a[i - 1] += delta[0]
            continue
        values = [a[i - 1] for i in positions]
        total = sum(values)
        if kind == 212:
            odd = sum(a[i - 1] for i in positions if i % 2)
            answer = (odd, total - odd)
        elif kind == 213:
            answer = (sum(i * value for i, value in enumerate(values, 1)),)
        elif kind == 214:
            answer = (sum(values[::2]) - sum(values[1::2]),)
        elif kind == 215:
            answer = (total % setting,)
        elif kind == 216:
            divisor = math.gcd(total, len(values))
            answer = (total // divisor, len(values) // divisor)
        elif kind == 219:
            answer = (sum(a[i - 1] * weights[i - 1] for i in positions),)
        else:
            answer = (total,)
        answers.extend(map(str, answer))
    return answers


def check_small(p, kind, data):
    run(p / "verifier", data)
    expected = brute(kind, data)
    assert run(p / "sol/correct", data).split() == expected, (p, data, expected)
    assert run(ORACLE, data, kind).split() == expected, (p, "reference", data, expected)


def small_checks(p, kind):
    count = 0
    for n in range(1, 5):
        ranges = [(l, r) for l in range(1, n + 1) for r in range(1, n + 1)
                  if kind == 211 or l <= r]
        queries = [(2, l, r) for l, r in ranges]
        ops = list(queries)
        for left, right in ranges:
            for delta in (-3, 0, 2):
                ops.append((1, left, right, delta))
                ops.extend(queries)
        settings = range(1, n + 1) if kind == 217 else (1, 2, 7) if kind == 215 else (None,)
        arrays = ([],) if kind == 218 else product((-2, 0, 3), repeat=n)
        for a in arrays:
            for setting in settings:
                check_small(p, kind, encode(kind, a, ops, setting, [i % 3 for i in range(n)]))
                count += 1

    rng = random.Random(20261110 + kind)
    limit = LIMITS.get(kind, 10**8)
    for case in range(140):
        n = rng.randint(1, 40)
        a = rng.choices([-limit, -7, -1, 0, 1, 5, limit], k=n)
        weights = rng.choices([0, 1, 2, 10000], k=n)
        setting = rng.choice([1, 2, 7, 999999937, 10**9]) if kind == 215 else rng.randint(1, n)
        choices = [1, 2, 3, AXIS_END // 2, AXIS_END - 1, AXIS_END]
        ops = []
        for _ in range(rng.randint(1, 100)):
            if kind == 218:
                l, r = sorted(rng.choices(choices, k=2))
            else:
                l, r = rng.randint(1, n), rng.randint(1, n)
                if kind != 211 and l > r:
                    l, r = r, l
            if rng.randrange(100) < (20, 50, 85)[case % 3]:
                ops.append((1, l, r, rng.choice([-limit, -1, 0, 1, limit])))
            else:
                ops.append((2, l, r))
        check_small(p, kind, encode(kind, a, ops, setting, weights))
        count += 1
    return count


def invalid_checks(p, kind):
    n = 3
    a = [0] * n
    setting = 2
    weights = [0, 2, 10000]
    limit = LIMITS.get(kind, 10**8)
    end = AXIS_END if kind == 218 else n

    def data(ops, values=a, parameter=setting, fixed=weights):
        return encode(kind, values, ops, parameter, fixed)

    valid = data([(2, 1, 1)])
    bad = [
        valid + "2 1 1\n", "\n".join(valid.splitlines()[:-1]) + "\n",
        data([(0, 1, 1)]), data([(3, 1, 1)]), data([(2, 0, 1)]),
        data([(2, 1, end + 1)]), data([(2, 1, 1, 0)]),
        data([(1, 1, 1)]), data([(1, 1, 1, limit + 1)]),
        data([(1, 1, 1, -limit - 1)]),
    ]
    if kind != 211:
        bad.append(data([(2, 2, 1)]))
    if kind == 218:
        bad.extend(["0\n", "200001\n"])
    else:
        extra = " 2" if kind in (215, 217) else ""
        bad.extend([f"0 1{extra}\n", f"200001 1{extra}\n", f"3 0{extra}\n", f"3 200001{extra}\n"])
        bad.extend([data([(2, 1, 1)], values=[limit + 1, 0, 0]),
                    data([(2, 1, 1)], values=[-limit - 1, 0, 0])])
    if kind in (215, 217):
        bad.extend(data([(2, 1, 1)], parameter=value)
                   for value in (0, (10**9 if kind == 215 else n) + 1))
    if kind == 219:
        bad.extend(data([(2, 1, 1)], fixed=value)
                   for value in ([-1, 2, 0], [10001, 2, 0]))
    for case in bad:
        result = subprocess.run([str(p / "verifier")], input=case, text=True, capture_output=True)
        assert result.returncode != 0, (p, "accepted invalid input", case)
    return len(bad)


def audit(problem, kind):
    p = problem.basedir
    expected = toml.load(ROOT / "custom/segtree220/info.toml")["upload"]
    expected["time_limit"] = 1.0
    assert problem.config["timelimit"] == 1.0 and problem.config["upload"] == expected
    assert problem.config["params"]["VALUE_MAX"] == LIMITS.get(kind, 10**8)
    files = sorted((p / "in").glob("*.in"))
    assert len(files) == 36
    dimensions = []
    for path in files:
        n, _, _, _, ops = decode(kind, path.read_text())
        dimensions.append((n, len(ops)))
        out = p / "out" / path.with_suffix(".out").name
        assert len(out.read_text().splitlines()) == sum(op[0] == 2 for op in ops)
    assert (AXIS_END if kind == 218 else 200000, 200000) in dimensions
    assert (p / "out/edge_10.out").read_text() == ""
    # The largest repeated full-range additions have a known closed-form answer.
    n, _, setting, _, ops = decode(kind, (p / "in/max_01.in").read_text())
    value = LIMITS.get(kind, 10**8) * (len(ops) - (kind == 218))
    expected_large = {
        210: [n * value], 211: [n * value],
        212: [(n + 1) // 2 * value, n // 2 * value],
        213: [n * (n + 1) // 2 * value], 214: [n % 2 * value],
        215: [n * value % (setting or 1)], 216: [value, 1],
        217: [n * value], 218: [n * value], 219: [n * value * 10000],
    }[kind]
    assert (p / "out/max_01.out").read_text().split() == list(map(str, expected_large))
    assert not list(p.rglob("*.html"))
    assert not (p / "solution.md").read_text().startswith("# ")
    audit_statement(p, with_subtask=False)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--problem", nargs="+", choices=NAMES, default=NAMES)
    parser.add_argument("--update-hashes", action="store_true")
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format="%(message)s")
    problems = [Problem(ROOT, ROOT / "custom" / name) for name in args.problem]
    sources = [HERE / "oracle_range_add_sum.cpp"]
    for problem in problems:
        p = problem.basedir
        problem.health_check()
        problem.generate_params_h()
        sources.extend([p / "sol/correct.cpp", problem.checker, problem.verifier])
        sources.extend(p / "gen" / test["name"] for test in problem.config["tests"]
                       if test["name"].endswith(".cpp"))

    print(f"Compiling {len(problems)} range-add/sum problems...", flush=True)
    with ThreadPoolExecutor(max_workers=4) as executor:
        list(executor.map(checked_compile, sources))

    count = 0
    for problem in problems:
        p = problem.basedir
        kind = int(p.name[7:])
        problem.make_inputs()
        problem.verify_inputs()
        problem.make_outputs(True)
        problem.judge(p / "sol/correct.cpp", {})
        assert problem.check_all_solutions_used()
        audit(problem, kind)
        for test in problem.config["tests"]:
            if not test["name"].endswith(".cpp"):
                continue
            executable = p / "gen" / Path(test["name"]).stem
            for seed in range(test["number"]):
                saved = p / "in" / f"{executable.name}_{seed:02}.in"
                assert run(executable, "", seed) == saved.read_text()
        for path in sorted((p / "in").glob("*.in")):
            data = path.read_text()
            expected = (p / "out" / path.with_suffix(".out").name).read_text().split()
            assert run(ORACLE, data, kind).split() == expected, (path, "Fenwick reference differs")
            if path.stem.startswith(("edge", "small", "example")):
                assert brute(kind, data) == expected, (path, "direct reference differs")
        additional = small_checks(p, kind)
        invalid = invalid_checks(p, kind)
        check_checker(p, kind)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        count += additional
        print(f"{p.name}: 36 tests, {additional} additional comparisons, {invalid} invalid inputs, 1 s and hashes OK",
              flush=True)
    print(f"Verified {36 * len(problems)} official tests and {count} additional cases.", flush=True)


if __name__ == "__main__":
    main()
