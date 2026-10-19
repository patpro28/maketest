"""Generate and verify the six basic segment tree problems, without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import logging
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile
import time

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from problem import Problem, compile as compile_source

NAMES = ['segtree020', 'segtree010', 'segtree050', 'segtree060', 'segtree051', 'segtree090']
ORACLE = Path(__file__).with_name('oracle')


def run(executable, data, *args, timeout=20):
    result = subprocess.run([str(executable), *map(str, args)], input=data,
                            text=True, capture_output=True, timeout=timeout, check=True)
    return result.stdout


def encode(a, operations):
    return f'{len(a)} {len(operations)}\n' + ' '.join(map(str, a)) + '\n' + ''.join(
        ' '.join(map(str, op)) + '\n' for op in operations)


def brute(kind, data):
    lines = data.splitlines()
    n, q = map(int, lines[0].split())
    a = list(map(int, lines[1].split()))
    assert len(a) == n and len(lines) == q + 2
    out = []
    for line in lines[2:]:
        op = list(map(int, line.split()))
        if op[0] == 1:
            a[op[1] - 1] = 1 - a[op[1] - 1] if kind == 10 else op[2]
            continue
        l, r = op[1] - 1, op[2]
        values = a[l:r]
        if kind == 10: answer = [sum(values)]
        elif kind == 20: answer = [min(values), max(values), max(values) - min(values)]
        elif kind == 50:
            even = sum(x % 2 == 0 for x in values)
            answer = [even, len(values) - even]
        elif kind == 60:
            best = max(values)
            answer = [best, values.count(best)]
        elif kind == 51:
            answer = ['0' if 0 in values else '-' if sum(x < 0 for x in values) % 2 else '+']
        elif kind == 90:
            answer = [1 + sum(a[i] != a[i - 1] for i in range(l + 1, r))]
        else: raise ValueError(kind)
        out.extend(map(str, answer))
    return out


def audit_statement(p):
    text = (p / 'task.md').read_text()
    assert text.splitlines()[0].startswith(f'# {p.name.upper()} — ')
    headings = re.findall(r'^### (.+)$', text, re.M)
    assert headings == ['Đề bài', 'Dữ liệu vào', 'Dữ liệu ra', 'Ràng buộc', 'Subtask',
                        'Sample Input 1', 'Sample Output 1', 'Sample Input 2', 'Sample Output 2', 'Giải thích']
    assert len(re.findall(r'^#+ ', text, re.M)) == len(headings) + 1
    assert '| Subtask | Tỉ lệ | Ràng buộc bổ sung |' in text
    percentages = re.findall(r'^\| \d+ \| (\d+)% \| (.+) \|$', text, re.M)
    assert sum(int(x) for x, _ in percentages) == 100
    assert percentages == [('100', 'Không có ràng buộc bổ sung')]
    for i in range(2):
        for label, folder, extension in [('Input', 'in', 'in'), ('Output', 'out', 'out')]:
            found = re.search(rf'### Sample {label} {i+1}\n\n```text\n(.*?)```', text, re.S)
            assert found and found[1] == (p / folder / f'example_{i:02}.{extension}').read_text(), (p, label, i)
    assert not (p / 'task.html').exists()


def check_case(p, kind, data, validate=True):
    if validate: run(p / 'verifier', data)
    expected = brute(kind, data)
    actual = run(p / 'sol/correct', data).split()
    assert actual == expected, (p, data, expected, actual)
    assert run(ORACLE, data, kind).split() == expected, (p, 'reference', data)


def small_checks(p, kind):
    alphabet = [0, 1] if kind == 10 else [1, 2, 3] if kind == 90 else [-1, 0, 1]
    count = 0
    for n in range(1, 5):
        for a in itertools.product(alphabet, repeat=n):
            queries = [(2, l, r) for l in range(1, n + 1) for r in range(l, n + 1)]
            ops = list(queries)
            for i in range(1, n + 1):
                for x in alphabet:
                    ops.append((1, i) if kind == 10 else (1, i, x))
                    ops.extend(queries)
            check_case(p, kind, encode(a, ops))
            count += 1
    rng = random.Random(20261017 + kind)
    values = [0, 1] if kind == 10 else [1, 2, 3, 10**9] if kind == 90 else [-10**9, -9, -2, -1, 0, 1, 2, 9, 10**9]
    for _ in range(150):
        n = rng.randint(1, 30)
        a = rng.choices(values, k=n)
        ops = []
        for _ in range(rng.randint(1, 150)):
            if rng.randrange(2):
                i = rng.randint(1, n)
                ops.append((1, i) if kind == 10 else (1, i, rng.choice(values)))
            else:
                l, r = sorted([rng.randint(1, n), rng.randint(1, n)])
                ops.append((2, l, r))
        check_case(p, kind, encode(a, ops))
        count += 1
    return count


def check_invalid_input(p, kind):
    base = 1 if kind == 90 else 0
    sample = (p / 'gen/example_00.in').read_text()
    bad = ['0 1\n\n2 1 1\n', '200001 1\n', '1 0\n0\n', '1 200001\n',
           f'1 1\n{base}\n3 1 1\n', f'1 1\n{base}\n2 0 1\n',
           f'1 1\n{base}\n2 1 2\n', f'2 1\n{base} {base}\n2 2 1\n',
           sample + '0\n', sample.rsplit('\n', 2)[0] + '\n']
    limits = [-1, 2] if kind == 10 else [0, 10**9 + 1] if kind == 90 else [-10**9 - 1, 10**9 + 1]
    for value in limits:
        bad.append(f'1 1\n{value}\n2 1 1\n')
        if kind != 10: bad.append(f'1 1\n{base}\n1 1 {value}\n')
    bad.extend([f'1 1\n{base}\n1 0' + ('' if kind == 10 else f' {base}') + '\n',
                f'1 1\n{base}\n1 2' + ('' if kind == 10 else f' {base}') + '\n'])
    if kind == 10: bad.append('1 1\n0\n1 1 0\n')
    for data in bad:
        result = subprocess.run([str(p / 'verifier')], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p, 'accepted malformed input', data)
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
                     (good + 'garbage\n', False), (good + '0\n', False)]
            if tokens:
                wrong = list(tokens)
                wrong[0] = ('+' if tokens[0] != '+' else '-') if kind == 51 else str(int(tokens[0]) + 1)
                tests += [('', False), (' '.join(wrong), False), (' '.join(tokens[:-1]), False), ('x\n', False)]
            for data, accepted in tests:
                actual.write_text(data)
                result = subprocess.run([str(p / 'checker'), str(inp), str(actual), str(ans)], capture_output=True)
                assert (result.returncode == 0) == accepted, (p, case, data, result.stderr)


def audit_coverage(p):
    files = list((p / 'in').glob('*.in'))
    assert len(files) == 36
    dimensions = [tuple(map(int, f.open().readline().split())) for f in files]
    assert (200000, 200000) in dimensions
    assert any(n == 1 for n, _ in dimensions)
    assert any(n & (n - 1) for n, _ in dimensions)
    assert (p / 'out/edge_10.out').read_text() == ''


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem', nargs='+', choices=NAMES, default=NAMES)
    parser.add_argument('--update-hashes', action='store_true')
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR, format='%(message)s')
    problems = [Problem(ROOT, ROOT / 'custom' / name) for name in args.problem]
    sources = [Path(__file__).with_name('oracle.cpp')]
    for problem in problems:
        problem.health_check()
        problem.generate_params_h()
        sources.extend([problem.basedir / 'sol/correct.cpp', problem.checker, problem.verifier])
        sources.extend(problem.basedir / 'gen' / test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} problems...', flush=True)
    # These independent compiler jobs do not involve agent delegation.
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(lambda src: compile_source(src, ROOT), sources): pass
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
        audit_coverage(p)
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
    print('All checks passed; no HTML generated.', flush=True)


if __name__ == '__main__':
    main()
