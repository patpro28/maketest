"""Generate and verify segtree000, 002, 011, 021, 030 and 031, without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import logging
import math
from pathlib import Path
import platform
import random
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(ROOT))
from problem import Problem, compile as compile_source
from check import audit_statement, check_checker, run

NAMES = ['segtree000', 'segtree002', 'segtree011', 'segtree021', 'segtree030', 'segtree031']
ORACLE = HERE / 'oracle_foundations'
DIVISORS = [x for x in range(1, 2521) if 2520 % x == 0]


def encode(kind, a, operations, k=0):
    head = f'{len(a)} {len(operations)}' + (f' {k}' if kind == 2 else '')
    return head + '\n' + ' '.join(map(str, a)) + '\n' + ''.join(
        ' '.join(map(str, op)) + '\n' for op in operations)


def decode(kind, data):
    lines = data.splitlines()
    head = list(map(int, lines[0].split()))
    n, q = head[:2]
    a = list(map(int, lines[1].split()))
    ops = [tuple(map(int, line.split())) for line in lines[2:]]
    assert len(a) == n and len(ops) == q
    return a, ops, head[2] if kind == 2 else 0


def brute(kind, data):
    a, ops, k = decode(kind, data)
    out = []
    for op in ops:
        if kind in (0, 2): l, r = op
        elif op[0] == 1:
            a[op[1] - 1] = op[2]
            continue
        else: _, l, r = op
        segment = a[l - 1:r]
        if kind in (0, 11): answer = [sum(segment)]
        elif kind == 2: answer = [sum(x >= k for x in segment)]
        elif kind == 21:
            minimum = min(segment)
            answer = [minimum, l + segment.index(minimum)]
        elif kind == 30: answer = [math.gcd(*segment)]
        elif kind == 31: answer = [math.lcm(*segment)]
        else: raise ValueError(kind)
        out.extend(map(str, answer))
    return out


def checked_compile(src):
    binary = src.with_suffix('.exe' if platform.system() == 'Windows' else '')
    binary.unlink(missing_ok=True)
    compile_source(src, ROOT)
    if not binary.is_file(): raise RuntimeError(f'Compilation failed: {src}')


def check_case(p, kind, data):
    run(p / 'verifier', data)
    expected = brute(kind, data)
    assert run(p / 'sol/correct', data).split() == expected, (p, 'solution', data, expected)
    assert run(ORACLE, data, kind).split() == expected, (p, 'oracle', data, expected)


def small_checks(p, kind):
    alphabet = [0, 1, 2] if kind in (0, 11) else [-1, 0, 1] if kind in (2, 21) else [1, 2, 6] if kind == 30 else [1, 8, 9]
    count = 0
    for n in range(1, 5):
        for a in itertools.product(alphabet, repeat=n):
            queries = [(l, r) if kind in (0, 2) else (2, l, r)
                       for l in range(1, n + 1) for r in range(l, n + 1)]
            operations = list(queries)
            if kind not in (0, 2):
                for i in range(1, n + 1):
                    for x in alphabet:
                        operations.append((1, i, x))
                        operations.extend(queries)
            for k in [-2, -1, 0, 1, 2] if kind == 2 else [0]:
                check_case(p, kind, encode(kind, a, operations, k))
                count += 1
    rng = random.Random(20261019 + kind)
    values = [0, 1, 2, 10**9] if kind in (0, 11) else [-10**9, -9, -1, 0, 1, 9, 10**9] if kind in (2, 21) else [1, 2, 6, 12, 30, 999999937, 10**9] if kind == 30 else DIVISORS
    for _ in range(150):
        n = rng.randint(1, 30)
        a = rng.choices(values, k=n)
        k = rng.choice(values) if kind == 2 else 0
        operations = []
        for _ in range(rng.randint(1, 150)):
            if kind not in (0, 2) and rng.randrange(2):
                operations.append((1, rng.randint(1, n), rng.choice(values)))
            else:
                l, r = sorted([rng.randint(1, n), rng.randint(1, n)])
                operations.append((l, r) if kind in (0, 2) else (2, l, r))
        check_case(p, kind, encode(kind, a, operations, k))
        count += 1
    return count


def check_invalid_input(p, kind):
    base = 0 if kind in (0, 2, 11, 21) else 1
    low, high = (-10**9, 10**9) if kind in (2, 21) else (0, 10**9) if kind in (0, 11) else (1, 10**9) if kind == 30 else (1, 2520)
    query = lambda l, r: (l, r) if kind in (0, 2) else (2, l, r)
    valid = encode(kind, [base], [query(1, 1)])
    bad = [encode(kind, [base], [query(0, 1)]), encode(kind, [base], [query(1, 2)]),
           encode(kind, [base, base], [query(2, 1)]), valid + '0\n', valid.rsplit('\n', 2)[0] + '\n']
    suffix = ' 0' if kind == 2 else ''
    for n, q in [(0, 1), (200001, 1), (1, 0), (1, 200001)]:
        bad.append(f'{n} {q}{suffix}\n')
    for value in [low - 1, high + 1]:
        bad.append(encode(kind, [value], [query(1, 1)]))
        if kind not in (0, 2): bad.append(encode(kind, [base], [(1, 1, value)]))
        if kind == 2: bad.append(encode(kind, [base], [query(1, 1)], value))
    if kind in (0, 2):
        bad.append(encode(kind, [base], [(2, 1, 1)]))
    else:
        bad.extend([encode(kind, [base], [(3, 1, 1)]), encode(kind, [base], [(1, 0, base)]),
                    encode(kind, [base], [(1, 2, base)]), encode(kind, [base], [(1, 1)])])
    if kind == 31:
        for value in [11, 16, 2519]:
            bad.extend([encode(kind, [value], [(2, 1, 1)]), encode(kind, [base], [(1, 1, value)])])
    for data in bad:
        result = subprocess.run([str(p / 'verifier')], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p, 'accepted invalid input', data)
    return len(bad)


def audit_coverage(p, kind):
    files = sorted((p / 'in').glob('*.in'))
    assert len(files) == 36
    dimensions = []
    large_sum = False
    threshold_equal = False
    for path in files:
        data = path.read_text()
        a, operations, k = decode(kind, data)
        dimensions.append((len(a), len(operations)))
        if kind in (0, 2): assert all(len(op) == 2 for op in operations)
        if kind == 2:
            threshold_equal |= any(x == k for x in a)
        if kind in (0, 11) and len(a) == 200000 and sum(a) > 2**31:
            large_sum = True
        if kind == 31:
            assert all(x in DIVISORS for x in a)
            assert all(op[2] in DIVISORS for op in operations if op[0] == 1)
    assert (200000, 200000) in dimensions
    assert any(n == 1 for n, _ in dimensions)
    assert any(n & (n - 1) for n, _ in dimensions)
    if kind in (0, 11): assert large_sum, 'Missing 64-bit sum case'
    if kind == 2: assert threshold_equal, 'Missing threshold equality'
    if kind not in (0, 2): assert (p / 'out/edge_10.out').read_text() == ''


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem', nargs='+', choices=NAMES, default=NAMES)
    parser.add_argument('--update-hashes', action='store_true')
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format='%(message)s')
    problems = [Problem(ROOT, ROOT / 'custom' / name) for name in args.problem]
    sources = [HERE / 'oracle_foundations.cpp']
    for problem in problems:
        problem.health_check()
        problem.generate_params_h()
        sources.extend([problem.basedir / 'sol/correct.cpp', problem.checker, problem.verifier])
        sources.extend(problem.basedir / 'gen' / test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} foundation problems...', flush=True)
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
        audit_statement(p)
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
            if path.stem.startswith(('edge', 'small', 'example')):
                assert brute(kind, data) == expected, (path, 'brute force differs')
        count = small_checks(p, kind)
        invalid = check_invalid_input(p, kind)
        check_checker(p, kind)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: 36 generated tests, {count} exhaustive/random checks, {invalid} invalid inputs; checker, samples, reproducibility, hashes OK ({time.monotonic() - started:.1f}s)', flush=True)
    print('All foundation checks passed; no HTML generated.', flush=True)


if __name__ == '__main__':
    main()
