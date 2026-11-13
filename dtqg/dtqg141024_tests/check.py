"""Generate and verify the four contest suites without exporting HTML."""
import argparse
import itertools
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile
import time

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))

from problem import Problem, execcmd
from problem_upload import ProblemUpload

CODES = ('dtocsen', 'dtorchard', 'dtesport', 'dtquanhe')
OPS = {
    '<': lambda x, y: x < y,
    '>': lambda x, y: x > y,
    '<=': lambda x, y: x <= y,
    '>=': lambda x, y: x >= y,
    '=': lambda x, y: x == y,
}
INVALID = {
    'dtocsen': ['0 1\n1\n', '1 1\n1000000000001\n', '1 2\n1\n', '1 1\n0 0\n'],
    'dtorchard': ['1 2\n1 1\n', '1 2\n0 2\n', '2 100001\n', '3 5001\n', '1 2\n01\n00\n'],
    'dtesport': ['1 1\n0\n3 1 2\n', '1 1\n0\n3 1 1 0\n', '1 1\n0\n1 1 1 0 1000001\n',
                 '2 1\n0 1\n2 2 1 0 0\n'],
    'dtquanhe': ['2 1\n0<2\n', '2 1\n1 != 2\n', '2 1\n1==2\n', '1 1\n1<1\n',
                  '3 3\n1<2\n2<=3\n1>=3\n'],
}


def verify(problem, data, valid=True):
    result = subprocess.run(execcmd(problem.verifier), input=data, text=True, capture_output=True)
    if (result.returncode == 0) != valid:
        raise AssertionError((problem.basedir.name, data, result.stderr))


def judge_output(problem, input_path, candidate, answer, accepted=True):
    args = list(map(str, (input_path, candidate, answer)))
    result = subprocess.run(execcmd(problem.checker, args), text=True, capture_output=True)
    if (result.returncode == 0) != accepted:
        raise AssertionError((problem.basedir.name, args, result.stderr))


def snail(target, moves):
    visited = set()
    height = day = 0
    while height not in visited:
        visited.add(height)
        for step, move in enumerate(moves):
            height = max(0, height + move)
            if height >= target:
                return day, step
        day += 1
    return -1, -1


def orchard(grid):
    n, m = len(grid), len(grid[0])
    best = n * m
    for top, bottom in itertools.combinations(range(n + 1), 2):
        for left, right in itertools.combinations(range(m + 1), 2):
            if (bottom - top) * (right - left) == n * m:
                continue
            cost = sum(grid[i][j] != (top <= i < bottom and left <= j < right)
                       for i in range(n) for j in range(m))
            best = min(best, cost)
    return best


def esport(values, operations):
    values = values[:]
    answers = []
    for kind, l, r, *change in operations:
        l -= 1
        if kind == 3:
            best = length = 1
            for i in range(l + 1, r):
                if length > 1 and values[i] - values[i - 1] == values[i - 1] - values[i - 2]:
                    length += 1
                else:
                    length = 2
                best = max(best, length)
            answers.append(best)
        else:
            start, slope = change
            for i in range(l, r):
                value = start + (i - l) * slope
                values[i] = values[i] + value if kind == 1 else value
    return answers


def relation(n, constraints):
    for maximum in range(n):
        for values in itertools.product(range(maximum + 1), repeat=n):
            if all(OPS[op](values[u], values[v]) for u, op, v in constraints):
                return values
    raise AssertionError('Expected a feasible assignment')


def row(values):
    return ' '.join(map(str, values)) + '\n'


def random_cases(code):
    rng = random.Random(141024)
    for _ in range(120):
        if code == 'dtocsen':
            target = rng.randint(1, 40)
            moves = [rng.randint(-12, 12) for _ in range(rng.randint(1, 10))]
            yield row((target, len(moves))) + row(moves), row(snail(target, moves))
        elif code == 'dtorchard':
            n, m = rng.randint(1, 5), rng.randint(2, 7)
            grid = [[rng.randrange(2) for _ in range(m)] for _ in range(n)]
            grid[0][0], grid[-1][-1] = 0, 1
            yield row((n, m)) + ''.join(map(row, grid)), row([orchard(grid)])
        elif code == 'dtesport':
            n, q = rng.randint(1, 25), rng.randint(1, 150)
            values = [rng.randint(-4, 4) for _ in range(n)]
            operations = []
            for _ in range(q):
                l = rng.randint(1, n)
                kind, r = rng.randint(1, 3), rng.randint(l, n)
                args = [] if kind == 3 else [rng.randint(-6, 6), rng.randint(-6, 6)]
                operations.append([kind, l, r, *args])
            data = row((n, q)) + row(values) + ''.join(map(row, operations))
            yield data, ''.join(row([x]) for x in esport(values, operations))
        else:
            n, m = rng.randint(1, 5), rng.randint(1, 18)
            values = [rng.randint(0, n - 1) for _ in range(n)]
            constraints = []
            for _ in range(m):
                u, v = rng.randrange(n), rng.randrange(n)
                op = rng.choice([op for op, match in OPS.items() if match(values[u], values[v])])
                constraints.append((u, op, v))
            data = row((n, m)) + ''.join(f'{u + 1}{op}{v + 1}\n' for u, op, v in constraints)
            yield data, row(relation(n, constraints))


def targeted_answers(code):
    if code == 'dtocsen':
        return {3: '1 0\n', 4: '1 0\n', 5: '999999999999 0\n', 6: '0 2\n',
                8: '-1 -1\n', 9: '999999999999 9999\n', 10: '-1 -1\n', 11: '1 0\n'}
    if code == 'dtorchard':
        return {0: '0\n', 1: '0\n', 2: '4\n', 3: '0\n', 6: '2\n', 9: '151\n', 11: '0\n'}
    if code == 'dtesport':
        return {0: '1\n' * 3, 1: '', 2: '2\n2\n2\n1\n',
                10: '300000\n' * 30000, 14: '2\n'}
    return {0: '0\n', 4: row(range(100000)), 5: row([0] * 100000),
            6: row([0] * 100000), 8: row(i // 2 for i in range(100000))}


def check_problem(code, update):
    base = ROOT / 'dtqg' / code
    problem = Problem(ROOT, base)
    limit = problem.config['timelimit']
    upload = ProblemUpload(problem)
    assert limit == upload.payload['time_limit'] == 1.0
    if code == 'dtquanhe':
        assert upload.custom_checker == problem.checker
    statement = (base / 'task.md').read_text()
    samples = re.findall(
        r'### Sample Input (\d+)\n\n\x60{3}text\n(.*?)\x60{3}\n\n'
        r'### Sample Output \1\n\n\x60{3}text\n(.*?)\x60{3}', statement, re.S)
    expected_headings = ['Đề bài', 'Dữ liệu vào', 'Dữ liệu ra', 'Ràng buộc']
    for index, (label, _, _) in enumerate(samples, 1):
        assert label == str(index)
        expected_headings.extend([f'Sample Input {index}', f'Sample Output {index}'])
    assert re.findall(r'^### (.*)$', statement, re.M) == expected_headings + ['Giải thích']
    assert statement.splitlines()[0] == '# ' + problem.config['title']
    assert problem.config['title'].startswith(code.upper() + ' — ')
    assert not re.search(r'^# ', (base / 'solution.md').read_text(), re.M)
    assert len(samples) == problem.config['tests'][0]['number']

    problem.health_check()
    problem.generate_params_h()
    for src in (problem.checker, problem.verifier, problem.get_correct_filename(), base / 'gen/cases.cpp'):
        src.with_suffix('.exe' if sys.platform == 'win32' else '').unlink(missing_ok=True)
    problem.compile_gens()
    problem.compile_verifier()
    problem.compile_correct()
    problem.compile_checker()
    problem.clean()
    problem.make_inputs()
    problem.verify_inputs()

    output_dir = base / 'out'
    output_dir.mkdir()
    longest = 0
    for input_path in sorted((base / 'in').glob('*.in')):
        output = output_dir / (input_path.stem + '.out')
        start = time.perf_counter()
        problem.run_solution(problem.get_correct_filename(), input_path, output, timeout=limit)
        longest = max(longest, time.perf_counter() - start)
        judge_output(problem, input_path, output, output)

    with tempfile.TemporaryDirectory() as directory:
        temp = Path(directory)
        input_path, candidate, answer = (temp / name for name in ('case.in', 'actual.out', 'answer.out'))
        for i, (_, data, expected) in enumerate(samples):
            sample_input = base / 'in' / f'example_{i:02}.in'
            sample_output = output_dir / f'example_{i:02}.out'
            assert sample_input.read_text() == data
            answer.write_text(expected)
            judge_output(problem, sample_input, sample_output, answer)
        for i, expected in targeted_answers(code).items():
            answer.write_text(expected)
            judge_output(problem, base / 'in' / f'cases_{i:02}.in',
                         output_dir / f'cases_{i:02}.out', answer)
        for data, expected in random_cases(code):
            verify(problem, data)
            input_path.write_text(data)
            answer.write_text(expected)
            problem.run_solution(problem.get_correct_filename(), input_path, candidate, timeout=limit)
            judge_output(problem, input_path, candidate, answer)
        for data in INVALID[code]:
            verify(problem, data, valid=False)
        sample = base / 'in' / 'example_00.in'
        reference = output_dir / 'example_00.out'
        for output in ('', reference.read_text() + '999\n', '999\n' + reference.read_text()):
            candidate.write_text(output)
            judge_output(problem, sample, candidate, reference, accepted=False)
        if code == 'dtquanhe':
            for output, accepted in [('0 1 2 0 2 3\n', True), ('0 1 2 1 2 3\n', True),
                                     ('0 1 2 1 2 4\n', False), ('0 1 2 2 2 3\n', False)]:
                candidate.write_text(output)
                judge_output(problem, sample, candidate, reference, accepted)

    if update:
        problem.ignore_warning = True
        problem.write_hashes()
    problem.assert_hashes()
    print(f'{code} | {sum(test["number"] for test in problem.config["tests"])} official + 120 independent'
          f' | max {longest:.3f}s | {len(problem.calc_hashes())} hashes', flush=True)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--problem', choices=CODES)
    parser.add_argument('--update-hashes', action='store_true')
    args = parser.parse_args()
    for code in (args.problem,) if args.problem else CODES:
        check_problem(code, args.update_hashes)
