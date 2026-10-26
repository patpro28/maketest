"""Generate and verify six replacement SEG0 problems without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import logging
import math
from pathlib import Path
import random
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(ROOT))
import toml
from problem import Problem
from check import audit_statement, run
from check_foundations import checked_compile
from check_remaining import check_checker

NAMES = ['segtree004', 'segtree014', 'segtree015', 'segtree025', 'segtree033', 'segtree051']
ORACLE = HERE / 'oracle_refill'
LIMITS = {4: (1, 10**9), 14: (0, 10**9), 15: (0, 10**9),
          25: (-10**9, 10**9), 33: (1, 10**9), 51: (-10**9, 10**9)}


def encode(kind, a, operations, setting=0):
    head = f'{len(a)} {len(operations)}' + (f' {setting}' if kind in (15, 33, 51) else '')
    return head + '\n' + ' '.join(map(str, a)) + '\n' + ''.join(' '.join(map(str, op)) + '\n' for op in operations)


def decode(kind, data):
    lines = data.splitlines()
    head = list(map(int, lines[0].split()))
    n, q = head[:2]
    a = list(map(int, lines[1].split()))
    ops = [tuple(map(int, line.split())) for line in lines[2:]]
    assert len(a) == n and len(ops) == q
    return a, ops, head[2] if len(head) == 3 else 0


def brute(kind, data):
    a, ops, setting = decode(kind, data)
    out = []
    for op in ops:
        if kind == 4: l, r = op
        elif op[0] == 1:
            if kind == 14: a[op[1] - 1] += op[2]
            else: a[op[1] - 1] = op[2]
            continue
        else: _, l, r = op
        values = a[l - 1:r]
        if kind == 4: answer = math.gcd(*values)
        elif kind == 14: answer = sum(values)
        elif kind == 15: answer = sum(values) % setting
        elif kind == 25: answer = max((abs(values[i] - values[i - 1]) for i in range(1, len(values))), default=0)
        elif kind == 33:
            result = math.lcm(*values)
            answer = result if result <= setting else -1
        elif kind == 51: answer = sum(x % setting == 0 for x in values)
        else: raise ValueError(kind)
        out.append(str(answer))
    return out


def check_case(p, kind, data):
    run(p / 'verifier', data)
    expected = brute(kind, data)
    assert run(p / 'sol/correct', data).split() == expected, (p, 'solution', data, expected)
    assert run(ORACLE, data, kind).split() == expected, (p, 'reference', data, expected)


def small_checks(p, kind):
    alphabet = [1, 2, 6] if kind in (4, 33) else [0, 1, 2] if kind in (14, 15) else [-1, 0, 1]
    settings = [1, 2, 7, 10**9] if kind == 15 else [1, 2, 5, 6, 12, 10**18] if kind == 33 else [1, 2, 3] if kind == 51 else [0]
    count = 0
    for n in range(1, 5):
        for a in itertools.product(alphabet, repeat=n):
            queries = [(l, r) if kind == 4 else (2, l, r) for l in range(1, n + 1) for r in range(l, n + 1)]
            ops = list(queries)
            if kind != 4:
                for i in range(1, n + 1):
                    for x in alphabet:
                        ops.append((1, i, x))
                        ops.extend(queries)
            for setting in settings:
                check_case(p, kind, encode(kind, a, ops, setting))
                count += 1
    rng = random.Random(20261020 + 1000000 + kind)
    low, high = LIMITS[kind]
    values = [x for x in [-10**9, -7, -1, 0, 1, 2, 3, 5, 6, 7, 12, 30, 97, 999999937, 10**9] if low <= x <= high]
    choices = [1, 2, 3, 7, 97, 999999937, 10**9] if kind in (15, 51) else [1, 6, 12, 30, 10**9 - 1, 10**9, 10**18] if kind == 33 else [0]
    for _ in range(150):
        n = rng.randint(1, 30)
        a = rng.choices(values, k=n)
        ops = []
        for _ in range(rng.randint(1, 150)):
            if kind != 4 and rng.randrange(2): ops.append((1, rng.randint(1, n), rng.choice(values)))
            else:
                l, r = sorted([rng.randint(1, n), rng.randint(1, n)])
                ops.append((l, r) if kind == 4 else (2, l, r))
        check_case(p, kind, encode(kind, a, ops, rng.choice(choices)))
        count += 1
    if kind == 25:
        a = [0] * 1001
        ops = [(1, 500, 10**9), (2, 499, 501), (1, 501, -10**9), (2, 500, 501),
               (2, 501, 502), (1, 1, -10**9), (2, 1, 2), (1, 1001, 10**9), (2, 1000, 1001)]
        check_case(p, kind, encode(kind, a, ops))
        count += 1
    if kind == 33:
        pair = [999999937, 999999929]
        product = math.lcm(*pair)
        for b in [product - 1, product, product + 1]:
            check_case(p, kind, encode(kind, pair, [(2, 1, 2), (2, 1, 1), (2, 2, 2)], b))
            count += 1
        cases = [([*pair, 999999893], 10**18,
                  [(2, 1, 3), (2, 1, 2), (1, 3, 1), (2, 1, 3), (1, 1, 1), (2, 1, 3), (1, 2, 1), (2, 1, 3)]),
                 ([1, 1], 1, [(1, 1, 2), (2, 1, 2), (1, 2, 2), (2, 1, 2), (1, 1, 1), (2, 1, 2), (1, 2, 1), (2, 1, 2)])]
        for a, b, ops in cases:
            check_case(p, kind, encode(kind, a, ops, b))
            count += 1
    return count


def check_invalid_input(p, kind):
    low, high = LIMITS[kind]
    base = 1 if low == 1 else 0
    setting = 7 if kind in (15, 33, 51) else 0
    query = lambda l, r: (l, r) if kind == 4 else (2, l, r)
    valid = encode(kind, [base], [query(1, 1)], setting)
    bad = [encode(kind, [base], [query(0, 1)], setting), encode(kind, [base], [query(1, 2)], setting),
           encode(kind, [base, base], [query(2, 1)], setting), valid + '0\n', valid.rsplit('\n', 2)[0] + '\n']
    suffix = f' {setting}' if kind in (15, 33, 51) else ''
    for n, q in [(0, 1), (200001, 1), (1, 0), (1, 200001)]: bad.append(f'{n} {q}{suffix}\n')
    for x in [low - 1, high + 1]:
        bad.append(encode(kind, [x], [query(1, 1)], setting))
        if kind != 4: bad.append(encode(kind, [base], [(1, 1, x)], setting))
    if kind == 4: bad.append(encode(kind, [base], [(2, 1, 1)]))
    else:
        bad.extend([encode(kind, [base], [(3, 1, 1)], setting), encode(kind, [base], [(1, 0, base)], setting),
                    encode(kind, [base], [(1, 2, base)], setting), encode(kind, [base], [(1, 1)], setting)])
    if kind in (15, 33, 51):
        for invalid in [0, 10**18 + 1 if kind == 33 else 10**9 + 1]:
            bad.append(encode(kind, [base], [query(1, 1)], invalid))
        bad.append(encode(kind, [base], [query(1, 1)], setting).replace(f'1 1 {setting}\n','1 1\n',1))
    for data in bad:
        result = subprocess.run([str(p / 'verifier')], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p, 'accepted invalid input', data)
    return len(bad)


def audit_coverage(problem, kind):
    p = problem.basedir
    files = sorted((p / 'in').glob('*.in'))
    assert len(files) == 36
    dimensions = []
    for path in files:
        a, ops, setting = decode(kind, path.read_text())
        dimensions.append((len(a), len(ops)))
        if kind == 4: assert all(len(op) == 2 for op in ops)
    assert (200000, 200000) in dimensions
    assert any(n == 1 for n, _ in dimensions)
    assert any(n & (n - 1) for n, _ in dimensions)
    if kind != 4: assert (p / 'out/edge_10.out').read_text() == ''
    if kind == 14: assert max(map(int,(p / 'out/max_02.out').read_text().split())) > 2**31
    if kind == 25: assert '2000000000' in (p / 'out/max_04.out').read_text().split()
    if kind == 33:
        a, _, b = decode(kind, (p / 'in/edge_03.in').read_text())
        assert math.lcm(*a) > 2**63
        assert str(math.lcm(*a[:2])) in (p / 'out/edge_03.out').read_text().split()
        assert '-1' in (p / 'out/edge_11.out').read_text().split()
        assert '6' in (p / 'out/edge_11.out').read_text().split()
        assert b == 10**18
    template = toml.load(ROOT / 'custom/segtree012/info.toml')['upload']
    shared_fields = ('group', 'classes', 'types', 'allowed_languages', 'partial')
    assert all(problem.config['upload'][key] == template[key] for key in shared_fields)
    assert problem.config['timelimit'] == problem.config['upload']['time_limit'] == 1.0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem', nargs='+', choices=NAMES, default=NAMES)
    parser.add_argument('--update-hashes', action='store_true')
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format='%(message)s')
    problems = [Problem(ROOT, ROOT / 'custom' / name) for name in args.problem]
    sources = [HERE / 'oracle_refill.cpp']
    for problem in problems:
        problem.health_check()
        problem.generate_params_h()
        sources.extend([problem.basedir / 'sol/correct.cpp', problem.checker, problem.verifier])
        sources.extend(problem.basedir / 'gen' / test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} replacement problems...', flush=True)
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
        audit_coverage(problem, kind)
        for test in problem.config['tests']:
            if not test['name'].endswith('.cpp'): continue
            exe = p / 'gen' / Path(test['name']).stem
            for seed in range(test['number']):
                assert run(exe, '', seed) == (p / 'in' / f'{exe.name}_{seed:02}.in').read_text()
        for path in sorted((p / 'in').glob('*.in')):
            data = path.read_text()
            expected = (p / 'out' / path.with_suffix('.out').name).read_text().split()
            assert run(ORACLE, data, kind).split() == expected, (path, 'reference differs')
            if path.stem.startswith(('edge','small','example')): assert brute(kind, data) == expected, (path, 'brute force differs')
        count = small_checks(p, kind)
        invalid = check_invalid_input(p, kind)
        check_checker(p, kind)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: 36 generated tests, {count} exhaustive/random checks, {invalid} invalid inputs; 1s limit, checker, samples, upload settings, reproducibility, hashes OK ({time.monotonic() - started:.1f}s)', flush=True)
    print('All replacement checks passed; no Subtask sections or HTML generated.', flush=True)


if __name__ == '__main__':
    main()
