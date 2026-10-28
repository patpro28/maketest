"""Generate and audit three segment-tree graph-compression problems, without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
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

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT))
from problem import Problem

NAMES = ['vexe', 'daychuyen', 'dichchuyen']
ORACLE = HERE / 'oracle'


def run(executable, data='', *args, timeout=60):
    return subprocess.run([str(executable), *map(str, args)], input=data, text=True,
                          capture_output=True, check=True, timeout=timeout).stdout


def build(source):
    flags = shlex.split(os.getenv('CXXFLAGS', '-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result'))
    subprocess.run([os.getenv('CXX', 'g++'), *flags, '-I', str(ROOT / 'common'),
                    '-o', str(source.with_suffix('')), str(source)], check=True)


def encode(kind, n, rows, s=1, t=1, durations=None):
    head = [n, len(rows)]
    if kind in (1, 3): head.append(s)
    if kind == 3: head.append(t)
    result = ' '.join(map(str, head)) + '\n'
    if kind == 2: result += ' '.join(map(str, durations or [1] * n)) + '\n'
    return result + ''.join(' '.join(map(str, row)) + '\n' for row in rows)


def decode(kind, data):
    lines = data.splitlines()
    head = list(map(int, lines[0].split()))
    n, q = head[:2]
    durations = list(map(int, lines[1].split())) if kind == 2 else None
    rows = [tuple(map(int, line.split())) for line in lines[2 if kind == 2 else 1:]]
    assert len(rows) == q
    if kind == 2: assert len(durations) == n
    return head, durations, rows


def brute(kind, data):
    """Explicit original graph; Bellman-Ford or repeated prerequisite scanning."""
    head, durations, rows = decode(kind, data)
    n = head[0]
    if kind == 2:
        prerequisites = [set() for _ in range(n)]
        for l, r, u in rows: prerequisites[u - 1].update(range(l - 1, r))
        finish = [None] * n
        while True:
            changed = False
            for u in range(n):
                if finish[u] is not None: continue
                if all(finish[v] is not None for v in prerequisites[u]):
                    finish[u] = durations[u] + max((finish[v] for v in prerequisites[u]), default=0)
                    changed = True
            if not changed: break
        return [str(-1 if None in finish else max(finish))]
    edges = []
    if kind == 1:
        for u, l, r, cost in rows:
            edges.extend((u - 1, v - 1, cost) for v in range(l, r + 1))
    else:
        for l, r, a, b, cost in rows:
            edges.extend((u - 1, v - 1, cost) for u in range(l, r + 1) for v in range(a, b + 1))
    inf = 10**30
    dist = [inf] * n
    dist[head[2] - 1] = 0
    for _ in range(n - 1):
        changed = False
        for u, v, cost in edges:
            if dist[u] != inf and dist[v] > dist[u] + cost:
                dist[v] = dist[u] + cost
                changed = True
        if not changed: break
    answer = dist if kind == 1 else [dist[head[3] - 1]]
    return [str(-1 if x == inf else x) for x in answer]


def check_case(p, kind, data):
    run(p / 'verifier', data)
    expected = brute(kind, data)
    actual = run(p / 'sol/correct', data).split()
    assert actual == expected, (p.name, 'solution', data, expected, actual)
    actual = run(ORACLE, data, kind).split()
    assert actual == expected, (p.name, 'oracle', data, expected, actual)


def small_checks(p, kind):
    count = 0
    for n in range(1, 4):
        intervals = [(l, r) for l in range(1, n + 1) for r in range(l, n + 1)]
        if kind == 1:
            for u, (l, r), cost, s in itertools.product(range(1, n + 1), intervals, [0, 1, 10**9], range(1, n + 1)):
                check_case(p, kind, encode(kind, n, [(u, l, r, cost)], s=s)); count += 1
        elif kind == 2:
            # Every directed point-dependency graph on at most three jobs, including loops.
            pairs = list(itertools.product(range(1, n + 1), repeat=2))
            for mask in range(1 << len(pairs)):
                rows = [(u, u, v) for j, (u, v) in enumerate(pairs) if mask >> j & 1]
                check_case(p, kind, encode(kind, n, rows, durations=[1, 10**9, 7][:n])); count += 1
        else:
            endpoints = sorted({(1, n), (n, 1), ((n + 1) // 2, (n + 1) // 2)})
            for (l, r), (a, b), cost, (s, t) in itertools.product(intervals, intervals, [0, 10**9], endpoints):
                check_case(p, kind, encode(kind, n, [(l, r, a, b, cost)], s=s, t=t)); count += 1
    rng = random.Random(20261027 + kind)
    for case in range(250):
        n = rng.randint(1, 12)
        q = rng.randint(0, 40)
        rows = []
        durations = [rng.choice([1, 2, 7, 10**9]) for _ in range(n)]
        permutation = list(range(n)); rng.shuffle(permutation)
        rank = [0] * n
        for i, u in enumerate(permutation): rank[u] = i
        dag_rules = [(l, r, u) for u in range(1, n + 1) for l in range(1, n + 1)
                     for r in range(l, n + 1) if all(rank[v - 1] < rank[u - 1] for v in range(l, r + 1))] if kind == 2 and case % 2 == 0 else None
        for _ in range(q):
            l, r = sorted([rng.randint(1, n), rng.randint(1, n)])
            cost = rng.choice([0, 1, 2, 10**9, rng.randint(0, 100)])
            if kind == 1: row = (rng.randint(1, n), l, r, cost)
            elif kind == 2:
                if dag_rules is not None:
                    if not dag_rules: break
                    row = rng.choice(dag_rules)
                else: row = (l, r, rng.randint(1, n))
            else:
                a, b = sorted([rng.randint(1, n), rng.randint(1, n)])
                row = (l, r, a, b, cost)
            rows.append(row)
        data = encode(kind, n, rows, rng.randint(1, n), rng.randint(1, n), durations)
        check_case(p, kind, data); count += 1
        if case < 20:
            # Rule order and duplicate rules cannot change the answer.
            head, _, _ = decode(kind, data)
            rng.shuffle(rows)
            if rows: rows.append(rows[0])
            transformed = encode(kind, n, rows, head[2] if kind != 2 else 1, head[3] if kind == 3 else 1, durations)
            assert brute(kind, transformed) == brute(kind, data)
            check_case(p, kind, transformed); count += 1
    return count


def invalid_checks(p, kind):
    valid = encode(kind, 2, [], s=1, t=2)
    head, _, _ = decode(kind, valid)
    bad = [valid + '0\n', valid[:-1], '']
    for field, values in [(0, [0, 100001]), (1, [-1, 100001])]:
        for value in values:
            modified = head[:]; modified[field] = value
            bad.append(' '.join(map(str, modified)) + '\n')
    row = [1, 1, 2, 0] if kind == 1 else [1, 1, 2] if kind == 2 else [1, 1, 2, 2, 0]
    fields = [[0, 3], [0, 3], [0, 3], [-1, 10**9 + 1]] if kind == 1 else \
             [[0, 3], [0, 3], [0, 3]] if kind == 2 else \
             [[0, 3], [0, 3], [0, 3], [0, 3], [-1, 10**9 + 1]]
    for i, values in enumerate(fields):
        for value in values:
            changed = row[:]; changed[i] = value
            bad.append(encode(kind, 2, [changed], t=2))
    reversed_row = row[:]
    left = 1 if kind == 1 else 0
    reversed_row[left:left + 2] = [2, 1]
    bad.append(encode(kind, 2, [reversed_row]))
    if kind == 3:
        bad.append(encode(kind, 2, [(1, 2, 2, 1, 0)]))
    bad.extend([encode(kind, 2, [row[:-1]]), encode(kind, 2, [row + [0]])])
    if kind in (1, 3):
        for s in [0, 3]: bad.append(encode(kind, 2, [], s=s))
    if kind == 3:
        for t in [0, 3]: bad.append(encode(kind, 2, [], t=t))
    if kind == 2:
        for value in [0, -1, 10**9 + 1]: bad.append(encode(kind, 2, [], durations=[1, value]))
        bad.append('2 0\n1\n')
    for data in bad:
        result = subprocess.run([str(p / 'verifier')], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p.name, 'accepted invalid input', data)
    return len(bad)


def checker_checks(p):
    with tempfile.TemporaryDirectory() as directory:
        inp, actual, answer = [Path(directory) / x for x in ('in', 'actual', 'answer')]
        for case in ['example_00', 'example_01', 'max_01']:
            inp.write_text((p / 'in' / f'{case}.in').read_text())
            good = (p / 'out' / f'{case}.out').read_text()
            answer.write_text(good)
            tokens = good.split()
            wrong = tokens[:]; wrong[0] = str(int(wrong[0]) + 1)
            tests = [(good, True), (' \n' + '\t '.join(tokens) + '\n', True),
                     (' '.join(wrong) + '\n', False), (' '.join(tokens[:-1]) + '\n', False),
                     (good + '0\n', False), (good + 'garbage\n', False),
                     ('word\n', False), ('9223372036854775808\n', False)]
            for data, accept in tests:
                actual.write_text(data)
                result = subprocess.run([str(p / 'checker'), str(inp), str(actual), str(answer)], capture_output=True)
                assert (result.returncode == 0) == accept, (p.name, case, data[:100], result.stderr)


def audit(problem, kind):
    p = problem.basedir
    text = (p / 'task.md').read_text()
    assert text.splitlines()[0].startswith(f'# {p.name.upper()} — ')
    expected = ['Đề bài', 'Dữ liệu vào', 'Dữ liệu ra', 'Ràng buộc',
                'Sample Input 1', 'Sample Output 1', 'Sample Input 2', 'Sample Output 2', 'Giải thích']
    assert re.findall(r'^### (.+)$', text, re.M) == expected
    assert len(re.findall(r'^#+ ', text, re.M)) == len(expected) + 1
    for i in range(2):
        for label, folder, ext in [('Input', 'in', 'in'), ('Output', 'out', 'out')]:
            match = re.search(rf'### Sample {label} {i+1}\n\n```text\n(.*?)```', text, re.S)
            assert match and match[1] == (p / folder / f'example_{i:02}.{ext}').read_text()
    assert not list(p.glob('*.html'))
    assert len(list((p / 'in').glob('*.in'))) == 36
    assert len(list((p / 'out').glob('*.out'))) == 36
    assert problem.config['upload']['time_limit'] == problem.config['timelimit']
    assert problem.config['upload']['memory_limit'] == 524288
    dimensions = []
    for path in (p / 'in').glob('*.in'):
        head, _, _ = decode(kind, path.read_text())
        dimensions.append(tuple(head[:2]))
    assert (100000, 100000) in dimensions
    assert any(n == 1 for n, _ in dimensions)
    assert any(q == 0 for _, q in dimensions)
    assert any(n & (n - 1) for n, _ in dimensions)
    chain = (p / 'out/max_01.out').read_text().split()
    if kind == 1: assert chain == [str(i * 10**9) for i in range(100000)]
    if kind == 2: assert chain == [str(100000 * 10**9)]
    if kind == 3: assert chain == [str(99999 * 10**9)]
    if kind == 1:
        assert (p / 'out/max_02.out').read_text().split() == ['0'] * 100000
        assert (p / 'out/max_04.out').read_text().split() == ['0'] + ['-1'] * 99999
    if kind == 2: assert (p / 'out/max_02.out').read_text().split() == ['-1']
    if kind == 3:
        assert (p / 'out/max_02.out').read_text().split() == ['0']
        assert (p / 'out/max_03.out').read_text().split() == ['2']
        assert (p / 'out/max_04.out').read_text().split() == ['-1']


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem', nargs='+', choices=NAMES, default=NAMES)
    parser.add_argument('--update-hashes', action='store_true')
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format='%(message)s')
    problems = [Problem(ROOT, ROOT / 'custom' / name) for name in args.problem]
    sources = [HERE / 'oracle.cpp']
    for problem in problems:
        problem.health_check(); problem.generate_params_h()
        p = problem.basedir
        sources.extend([p / 'sol/correct.cpp', p / 'checker.cpp', p / 'verifier.cpp'])
        sources.extend(p / 'gen' / test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} graph-compression problems...', flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(build, sources): pass
    extra = 0
    for problem in problems:
        started = time.monotonic()
        p = problem.basedir
        kind = NAMES.index(p.name) + 1
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True)
        problem.judge(p / 'sol/correct.cpp', {})
        assert problem.check_all_solutions_used()
        audit(problem, kind)
        print(f'{p.name}: 36 generated tests and time limit passed; checking independent oracle...', flush=True)
        for path in sorted((p / 'in').glob('*.in')):
            data = path.read_text()
            expected = (p / 'out' / path.with_suffix('.out').name).read_text().split()
            actual = run(ORACLE, data, kind).split()
            assert actual == expected, (path, 'independent oracle differs')
            if path.stem.startswith(('example', 'edge', 'small')):
                assert brute(kind, data) == expected, (path, 'explicit original graph differs')
        for test in problem.config['tests']:
            if not test['name'].endswith('.cpp'): continue
            exe = p / 'gen' / Path(test['name']).stem
            for seed in range(test['number']):
                assert run(exe, '', seed) == (p / 'in' / f'{exe.name}_{seed:02}.in').read_text()
        count = small_checks(p, kind); extra += count
        invalid = invalid_checks(p, kind)
        checker_checks(p)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: 36 tests, {count} exhaustive/random/metamorphic cases, {invalid} invalid inputs; checker, samples, reproducibility and hashes OK ({time.monotonic()-started:.1f}s)', flush=True)
    print(f'All checks passed: {36*len(problems)} generated tests and {extra} additional cases; no Subtask or HTML.', flush=True)


if __name__ == '__main__':
    main()
