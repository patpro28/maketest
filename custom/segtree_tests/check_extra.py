"""Generate and verify seven additional segment tree problems and upload metadata, without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from functools import reduce
import itertools
import logging
import math
from operator import xor
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
from check_remaining import check_checker as check_output_checker

NAMES = ['segtree003', 'segtree080', 'segtree070', 'segtree071', 'segtree081', 'segtree072', 'segtree034']
# Stable fixture identifiers keep the random seeds and existing test hashes unchanged.
CASE_KINDS = {'segtree003': 3, 'segtree080': 4, 'segtree070': 14,
              'segtree071': 15, 'segtree081': 25, 'segtree072': 33, 'segtree034': 34}
ORACLE = HERE / 'oracle_extra'
LIMITS = {3: (0, 10**9), 4: (-1, 1), 14: (-10**8, 10**8), 15: (-10000, 10000),
          25: (-10**9, 10**9), 33: (1, 10**9), 34: (-10**9, 10**9)}


def encode(kind, a, operations):
    array = ''.join('(' if x == 1 else ')' for x in a) if kind == 4 else ' '.join(map(str, a))
    return f'{len(a)} {len(operations)}\n{array}\n' + ''.join(' '.join(map(str, op)) + '\n' for op in operations)


def decode(kind, data):
    lines = data.splitlines()
    n, q = map(int, lines[0].split())
    a = [1 if c == '(' else -1 for c in lines[1]] if kind == 4 else list(map(int, lines[1].split()))
    operations = [tuple(map(int, line.split())) for line in lines[2:]]
    assert len(a) == n and len(operations) == q
    return a, operations


def brute(kind, data):
    a, operations = decode(kind, data)
    out = []
    for op in operations:
        if kind in (3, 4): l, r = op
        elif op[0] == 1:
            a[op[1] - 1] = op[2]
            continue
        else: l, r = op[1:3]
        values = a[l - 1:r]
        if kind == 3: answer = [reduce(xor, values, 0)]
        elif kind == 4:
            balance = 0
            valid = True
            for x in values:
                balance += x
                if balance < 0: valid = False
            answer = ['YES' if valid and balance == 0 else 'NO']
        elif kind == 14: answer = [sum((i + 1) * x for i, x in enumerate(values))]
        elif kind == 15: answer = [sum((x - op[3])**2 for x in values)]
        elif kind == 25: answer = [max(values[j] - values[i] for i in range(len(values)) for j in range(i + 1, len(values)))]
        elif kind == 33:
            g = math.gcd(*values)
            answer = [g, sum(x // g for x in values)]
        elif kind == 34: answer = [math.gcd(*(abs(x - op[3]) for x in values))]
        else: raise ValueError(kind)
        out.extend(map(str, answer))
    return out


def check_case(p, kind, data):
    run(p / 'verifier', data)
    expected = brute(kind, data)
    assert run(p / 'sol/correct', data).split() == expected, (p, 'solution', data, expected)
    assert run(ORACLE, data, kind).split() == expected, (p, 'reference', data, expected)


def small_checks(p, kind):
    alphabet = [0, 1, 2] if kind == 3 else [-1, 1] if kind == 4 else [1, 2, 6] if kind == 33 else [-1, 0, 1]
    count = 0
    for n in range(2 if kind == 25 else 1, 9 if kind == 4 else 5):
        for a in itertools.product(alphabet, repeat=n):
            queries = []
            for l in range(1, n + 1):
                for r in range(l + (kind == 25), n + 1):
                    if kind in (3, 4): queries.append((l, r))
                    elif kind in (15, 34):
                        queries.extend((2, l, r, c) for c in [-2, -1, 0, 1, 2])
                    else: queries.append((2, l, r))
            operations = list(queries)
            if kind not in (3, 4):
                for i in range(1, n + 1):
                    for x in alphabet:
                        operations.append((1, i, x))
                        operations.extend(queries)
            check_case(p, kind, encode(kind, a, operations))
            count += 1
    rng = random.Random(20261020 + kind)
    low, high = LIMITS[kind]
    values = [-10**9, -10**8, -10000, -7, -1, 0, 1, 2, 6, 12, 10000, 10**8, 10**9]
    values = [-1, 1] if kind == 4 else [x for x in values if low <= x <= high]
    for _ in range(150):
        n = rng.randint(2 if kind == 25 else 1, 30)
        a = rng.choices(values, k=n)
        operations = []
        for _ in range(rng.randint(1, 150)):
            if kind not in (3, 4) and rng.randrange(2): operations.append((1, rng.randint(1, n), rng.choice(values)))
            else:
                if kind == 25: l, r = sorted(rng.sample(range(1, n + 1), 2))
                else: l, r = sorted([rng.randint(1, n), rng.randint(1, n)])
                if kind in (3, 4): operations.append((l, r))
                elif kind in (15, 34): operations.append((2, l, r, rng.choice(values)))
                else: operations.append((2, l, r))
        check_case(p, kind, encode(kind, a, operations))
        count += 1
    if kind == 3:
        check_case(p, kind, encode(kind, [2**29, 2**29 - 1], [(1, 2), (2, 2)]))
        count += 1
    return count


def check_invalid_input(p, kind):
    n = 2 if kind == 25 else 1
    low, high = LIMITS[kind]
    a = [1 if kind in (4, 33) else 0] * n
    def query(l, r):
        if kind in (3, 4): return l, r
        if kind in (15, 34): return 2, l, r, 0
        return 2, l, r
    valid = encode(kind, a, [query(1, n)])
    bad = [encode(kind, a, [query(0, n)]), encode(kind, a, [query(1, n + 1)]),
           encode(kind, a * 2, [query(2, 1)]), valid + '0\n', valid.rsplit('\n', 2)[0] + '\n']
    for invalid_n, invalid_q in [(0, 1), (200001, 1), (n, 0), (n, 200001)]: bad.append(f'{invalid_n} {invalid_q}\n')
    if kind == 25: bad.extend([encode(kind, [0], [(2, 1, 1)]), encode(kind, a, [(2, 1, 1)])])
    if kind == 4:
        bad.extend(['1 1\na\n1 1\n', '2 1\n(\n1 2\n', '1 1\n()\n1 1\n', '2 1\n( )\n1 2\n'])
    else:
        for x in [low - 1, high + 1]:
            bad.append(encode(kind, [x] * n, [query(1, n)]))
            if kind not in (3, 4): bad.append(encode(kind, a, [(1, 1, x)]))
            if kind in (15, 34): bad.append(encode(kind, a, [(2, 1, n, x)]))
    if kind in (3, 4): bad.append(encode(kind, a, [(2, 1, n)]))
    else:
        bad.extend([encode(kind, a, [(3, 1, n)]), encode(kind, a, [(1, 0, a[0])]),
                    encode(kind, a, [(1, n + 1, a[0])]), encode(kind, a, [(1, 1)])])
    if kind in (15, 34): bad.extend([encode(kind, a, [(2, 1, n)]), encode(kind, a, [(2, 1, n, 0, 0)])])
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
        a, operations = decode(kind, path.read_text())
        dimensions.append((len(a), len(operations)))
        if kind in (3, 4): assert all(len(op) == 2 for op in operations)
        if kind == 25: assert all(op[1] < op[2] for op in operations if op[0] == 2)
        if kind in (15, 34): assert all(len(op) == 4 for op in operations if op[0] == 2)
    assert (200000, 200000) in dimensions
    assert any(n == (2 if kind == 25 else 1) for n, _ in dimensions)
    assert any(n & (n - 1) for n, _ in dimensions)
    if kind not in (3, 4): assert (p / 'out/edge_10.out').read_text() == ''
    if kind in (14, 15, 33):
        output = (p / ('out/max_04.out' if kind == 33 else 'out/max_01.out')).read_text().split()
        assert max(map(lambda x: abs(int(x)), output)) > 2**31, 'Missing 64-bit results'
    if kind == 25: assert (p / 'out/example_01.out').read_text().split()[0] == '-2'
    if kind == 34: assert '2000000000' in (p / 'out/max_01.out').read_text().split()
    template = toml.load(ROOT / 'custom/segtree012/info.toml')['upload']
    # Shared classification stays aligned; limits may be configured per problem.
    shared_fields = ('group', 'classes', 'types', 'allowed_languages', 'partial')
    upload = problem.config['upload']
    assert {key: upload[key] for key in shared_fields} == {
        key: template[key] for key in shared_fields
    }, (p, 'shared upload metadata differs')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem', nargs='+', choices=NAMES, default=NAMES)
    parser.add_argument('--update-hashes', action='store_true')
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format='%(message)s')
    problems = [Problem(ROOT, ROOT / 'custom' / name) for name in args.problem]
    sources = [HERE / 'oracle_extra.cpp']
    for problem in problems:
        problem.health_check()
        problem.generate_params_h()
        sources.extend([problem.basedir / 'sol/correct.cpp', problem.checker, problem.verifier])
        sources.extend(problem.basedir / 'gen' / test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} extra problems...', flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(checked_compile, sources): pass
    for problem in problems:
        started = time.monotonic()
        p = problem.basedir
        kind = CASE_KINDS[p.name]
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
            if path.stem.startswith(('edge', 'small', 'example')): assert brute(kind, data) == expected, (path, 'brute force differs')
        count = small_checks(p, kind)
        invalid = check_invalid_input(p, kind)
        check_output_checker(p, 23 if kind == 4 else kind)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: 36 generated tests, {count} exhaustive/random checks, {invalid} invalid inputs; checker, samples, upload metadata, reproducibility, hashes OK ({time.monotonic() - started:.1f}s)', flush=True)
    print('All extra checks passed; no Subtask sections or HTML generated.', flush=True)


if __name__ == '__main__':
    main()
