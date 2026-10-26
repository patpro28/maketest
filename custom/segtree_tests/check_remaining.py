"""Generate and verify the six remaining basic range query problems, without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import logging
import math
from pathlib import Path
import random
import subprocess
import sys
import tempfile
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(ROOT))
from problem import Problem
from check import audit_statement, run
from check_foundations import checked_compile

NAMES = ['segtree001', 'segtree012', 'segtree013', 'segtree022', 'segtree023', 'segtree032']
ORACLE = HERE / 'oracle_remaining'


def encode(a, operations):
    return f'{len(a)} {len(operations)}\n' + ' '.join(map(str, a)) + '\n' + ''.join(
        ' '.join(map(str, op)) + '\n' for op in operations)


def decode(data):
    lines = data.splitlines()
    n, q = map(int, lines[0].split())
    a = list(map(int, lines[1].split()))
    operations = [tuple(map(int, line.split())) for line in lines[2:]]
    assert len(a) == n and len(operations) == q
    return a, operations


def brute(kind, data):
    a, operations = decode(data)
    out = []
    for op in operations:
        if kind == 1: l, r = op
        elif op[0] == 1:
            a[op[1] - 1] = op[2]
            continue
        else: l, r = op[1:3]
        values = a[l - 1:r]
        if kind == 1: answer = [min(values), max(values), max(values) - min(values)]
        elif kind == 12: answer = [sum(x for x in values if x > 0), -sum(x for x in values if x < 0)]
        elif kind == 13: answer = [sum(x if i % 2 == 0 else -x for i, x in enumerate(values))]
        elif kind == 22: answer = [sum(sorted(values)[-2:])]
        elif kind == 23: answer = ['YES' if all(op[3] <= x <= op[4] for x in values) else 'NO']
        elif kind == 32: answer = [math.gcd(*(abs(values[i] - values[i - 1]) for i in range(1, len(values))))]
        else: raise ValueError(kind)
        out.extend(map(str, answer))
    return out


def check_case(p, kind, data):
    run(p / 'verifier', data)
    expected = brute(kind, data)
    assert run(p / 'sol/correct', data).split() == expected, (p, 'solution', data, expected)
    assert run(ORACLE, data, kind).split() == expected, (p, 'reference', data, expected)


def small_checks(p, kind):
    count = 0
    alphabet = [-1, 0, 1]
    for n in range(2 if kind == 22 else 1, 5):
        for a in itertools.product(alphabet, repeat=n):
            queries = []
            for l in range(1, n + 1):
                for r in range(l + (kind == 22), n + 1):
                    if kind == 1: queries.append((l, r))
                    elif kind == 23:
                        for u, v in [(-2, 2), (-1, -1), (-1, 0), (-1, 1), (0, 0), (0, 1), (1, 1)]:
                            queries.append((2, l, r, u, v))
                    else: queries.append((2, l, r))
            operations = list(queries)
            if kind != 1:
                for i in range(1, n + 1):
                    for x in alphabet:
                        operations.append((1, i, x))
                        operations.extend(queries)
            check_case(p, kind, encode(a, operations))
            count += 1
    rng = random.Random(20261019 + kind)
    values = [-10**9, -30, -7, -2, -1, 0, 1, 2, 7, 30, 10**9]
    for _ in range(150):
        n = rng.randint(2 if kind == 22 else 1, 30)
        a = rng.choices(values, k=n)
        operations = []
        for _ in range(rng.randint(1, 150)):
            if kind != 1 and rng.randrange(2): operations.append((1, rng.randint(1, n), rng.choice(values)))
            else:
                if kind == 22: l, r = sorted(rng.sample(range(1, n + 1), 2))
                else: l, r = sorted([rng.randint(1, n), rng.randint(1, n)])
                if kind == 1: operations.append((l, r))
                elif kind == 23:
                    u, v = sorted(rng.choices(values, k=2))
                    operations.append((2, l, r, u, v))
                else: operations.append((2, l, r))
        check_case(p, kind, encode(a, operations))
        count += 1
    return count


def check_invalid_input(p, kind):
    n = 2 if kind == 22 else 1
    a = [0] * n
    def query(l, r):
        if kind == 1: return l, r
        if kind == 23: return 2, l, r, -1, 1
        return 2, l, r
    valid = encode(a, [query(1, n)])
    bad = [encode(a, [query(0, n)]), encode(a, [query(1, n + 1)]),
           encode([0, 0], [query(2, 1)]), valid + '0\n', valid.rsplit('\n', 2)[0] + '\n']
    for invalid_n, invalid_q in [(0, 1), (200001, 1), (n, 0), (n, 200001)]: bad.append(f'{invalid_n} {invalid_q}\n')
    if kind == 22:
        bad.extend([encode([0], [(2, 1, 1)]), encode(a, [(2, 1, 1)])])
    for value in [-10**9 - 1, 10**9 + 1]:
        bad.append(encode([value] * n, [query(1, n)]))
        if kind != 1: bad.append(encode(a, [(1, 1, value)]))
    if kind == 1: bad.append(encode(a, [(2, 1, 1)]))
    else:
        bad.extend([encode(a, [(3, 1, n)]), encode(a, [(1, 0, 0)]),
                    encode(a, [(1, n + 1, 0)]), encode(a, [(1, 1)])])
    if kind == 23:
        bad.extend([encode(a, [(2, 1, n, 1, -1)]), encode(a, [(2, 1, n, -10**9 - 1, 1)]),
                    encode(a, [(2, 1, n, -1, 10**9 + 1)]), encode(a, [(2, 1, n)]),
                    encode(a, [(2, 1, n, -1, 1, 0)])])
    for data in bad:
        result = subprocess.run([str(p / 'verifier')], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p, 'accepted invalid input', data)
    return len(bad)


def check_checker(p, kind):
    with tempfile.TemporaryDirectory() as directory:
        directory = Path(directory)
        inp, actual, ans = [directory / name for name in ('in', 'actual', 'ans')]
        for case in ['example_00', 'edge_10']:
            inp.write_text((p / 'in' / f'{case}.in').read_text())
            good = (p / 'out' / f'{case}.out').read_text()
            ans.write_text(good)
            tokens = good.split()
            tests = [(good, True), (' \n' + ' \t'.join(tokens) + '\n', True),
                     (good + '0\n', False), (good + 'garbage\n', False)]
            if tokens:
                wrong = list(tokens)
                wrong[0] = ('NO' if tokens[0] == 'YES' else 'YES') if kind == 23 else str(int(tokens[0]) + 1)
                tests.extend([('', False), (' '.join(wrong), False), (' '.join(tokens[:-1]), False), ('x\n', False)])
            for data, accepted in tests:
                actual.write_text(data)
                result = subprocess.run([str(p / 'checker'), str(inp), str(actual), str(ans)], capture_output=True)
                assert (result.returncode == 0) == accepted, (p, data, result.stderr)


def audit_coverage(p, kind):
    files = sorted((p / 'in').glob('*.in'))
    assert len(files) == 36
    dimensions = []
    large = False
    for path in files:
        a, ops = decode(path.read_text())
        dimensions.append((len(a), len(ops)))
        if kind == 1: assert all(len(op) == 2 for op in ops)
        if kind == 22: assert all(op[1] < op[2] for op in ops if op[0] == 2)
        if kind == 23: assert all(len(op) == 5 and op[3] <= op[4] for op in ops if op[0] == 2)
        if kind == 12: large |= max(sum(x for x in a if x > 0), -sum(x for x in a if x < 0)) > 2**31
        if kind == 13: large |= abs(sum(x if i % 2 == 0 else -x for i, x in enumerate(a))) > 2**31
    assert (200000, 200000) in dimensions
    assert any(n == (2 if kind == 22 else 1) for n, _ in dimensions)
    assert any(n & (n - 1) for n, _ in dimensions)
    if kind in (12, 13): assert large, 'Missing 64-bit sum coverage'
    if kind != 1: assert (p / 'out/edge_10.out').read_text() == ''
    if kind == 32: assert '2000000000' in (p / 'out/max_04.out').read_text().split()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem', nargs='+', choices=NAMES, default=NAMES)
    parser.add_argument('--update-hashes', action='store_true')
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format='%(message)s')
    problems = [Problem(ROOT, ROOT / 'custom' / name) for name in args.problem]
    sources = [HERE / 'oracle_remaining.cpp']
    for problem in problems:
        problem.health_check()
        problem.generate_params_h()
        sources.extend([problem.basedir / 'sol/correct.cpp', problem.checker, problem.verifier])
        sources.extend(problem.basedir / 'gen' / test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} remaining problems...', flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(checked_compile, sources): pass
    for problem in problems:
        started = time.monotonic()
        p = problem.basedir
        kind = int(p.name[7:])
        problem.make_inputs()
        problem.verify_inputs()
        problem.make_outputs(True)
        problem.judge(p / 'sol/correct.cpp', {})
        assert problem.check_all_solutions_used()
        audit_statement(p, with_subtask=False)
        audit_coverage(p, kind)
        for test in problem.config['tests']:
            if not test['name'].endswith('.cpp'): continue
            exe = p / 'gen' / Path(test['name']).stem
            for seed in range(test['number']):
                assert run(exe, '', seed) == (p / 'in' / f'{exe.name}_{seed:02}.in').read_text()
        for path in sorted((p / 'in').glob('*.in')):
            data = path.read_text()
            expected = (p / 'out' / path.with_suffix('.out').name).read_text().split()
            assert run(ORACLE, data, kind).split() == expected, (path, 'reference differs')
            if path.stem.startswith(('edge', 'small', 'example')): assert brute(kind, data) == expected, (path, 'brute force differs')
        count = small_checks(p, kind)
        invalid = check_invalid_input(p, kind)
        check_checker(p, kind)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: 36 generated tests, {count} exhaustive/random checks, {invalid} invalid inputs; checker, samples, reproducibility, hashes OK ({time.monotonic() - started:.1f}s)', flush=True)
    print('All remaining checks passed; no Subtask sections or HTML generated.', flush=True)


if __name__ == '__main__':
    main()
