"""Generate and independently verify TDIFF000–TDIFF009 without HTML export."""

import argparse
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from itertools import accumulate, groupby
import os
from pathlib import Path
import re
import shlex
import subprocess
import sys
from tempfile import TemporaryDirectory
from time import perf_counter

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from problem import Problem, execcmd

LIMIT = 200000
VALUE = 10**9


def differences(values):
    return [right - left for left, right in zip([0] + values, values)]


def changed(values, left, right, delta):
    return [
        value + (delta if left <= index <= right else 0)
        for index, value in enumerate(values, 1)
    ]


def oracle(kind, data):
    tokens = iter(map(int, data.split()))

    def take(count):
        return [next(tokens) for _ in range(count)]

    answer = []
    for _ in range(next(tokens)):
        n = next(tokens)
        if kind == 2:
            k, anchor = take(2)
            relative = list(accumulate([0] + take(n - 1)))
            answer.extend(value + anchor - relative[k - 1] for value in relative)
            continue
        q = next(tokens) if kind == 8 else 0
        a = take(n)
        if kind == 0:
            answer.extend(differences(a))
        elif kind == 1:
            answer.extend(accumulate(a))
        elif kind == 3:
            lengths = [sum(1 for _ in run) for _, run in groupby(accumulate(a))]
            answer.append(len(lengths))
            start = 1
            for length in lengths:
                answer.extend((start, start + length - 1))
                start += length
        elif kind in (4, 5, 6, 7):
            values = list(accumulate(a))
            if kind == 4:
                left, delta = take(2)
                values = changed(values, left, n, delta)
            elif kind == 5:
                position, value = take(2)
                values[position - 1] = value
            else:
                values = changed(values, *take(3))
            answer.extend(values if kind == 7 else differences(values))
        elif kind == 8:
            values = [0] + list(accumulate(a))
            for _ in range(q):
                left, right, delta, position = take(4)
                current = values[position] + (delta if left <= position <= right else 0)
                previous = values[position - 1] + (delta if left < position <= right + 1 else 0)
                answer.append(current - previous)
        else:
            b = take(n)
            mismatches = [i for i, pair in enumerate(zip(a, b)) if pair[0] != pair[1]]
            if mismatches:
                first, last = mismatches[0], mismatches[-1]
                delta = b[first] - a[first]
                if changed(a, first + 1, last + 1, delta) == b:
                    answer.extend((first + 1, last + 1, delta))
                    continue
            answer.append(-1)
    assert next(tokens, None) is None
    return answer


def read_samples(base):
    statement = (base / 'task.md').read_text()
    assert statement.startswith(f'# {base.name.upper()} — ')
    assert re.findall(r'^#{1,6} .+$', statement, re.M)[1:] == [
        '### Đề bài', '### Dữ liệu vào', '### Dữ liệu ra', '### Ràng buộc',
        '### Sample Input 1', '### Sample Output 1',
        '### Sample Input 2', '### Sample Output 2', '### Giải thích',
    ]
    assert r'\sum_{i=1}^{T} N_i \le 2\cdot 10^5' in statement
    editorial = (base / 'solution.md').read_text()
    assert not re.search(r'^# |oracle|verifier|checker|benchmark|kiểm thử', editorial, re.I | re.M)
    assert {'## Ý tưởng', '## Chứng minh tính đúng đắn', '## Độ phức tạp'} <= set(editorial.splitlines())
    for index in range(2):
        def block(label):
            pattern = rf'^### Sample {label} {index + 1}\n\n```text\n(.*?)```'
            return re.search(pattern, statement, re.M | re.S)[1]
        data = block('Input')
        assert (base / 'gen' / f'example_{index:02d}.in').read_text() == data
        yield data, block('Output')


def case(kind, n, q=1):
    line = '0' + ' 0' * (n - 1) + '\n'
    if kind == 2:
        return f'{n} 1 0\n' + (line[2:] if n > 1 else '')
    if kind == 8:
        return f'{n} {q}\n' + line + '1 1 0 1\n' * q
    extra = {4: '1 0\n', 5: '1 0\n', 6: '1 1 0\n', 7: '1 1 0\n', 9: line}
    return f'{n}\n' + line + extra.get(kind, '')


def invalid_inputs(kind, sample):
    yield 'T bằng 0', '0\n'
    yield 'T vượt giới hạn', '10001\n' + case(kind, 1) * 10001
    yield 'N bằng 0', '1\n0\n'
    yield 'N vượt giới hạn', '1\n200001\n'
    yield 'tổng N vượt giới hạn', '2\n' + case(kind, LIMIT) + case(kind, 1)
    yield 'thiếu dữ liệu', sample[:sample.rindex('\n', 0, -1) + 1]
    yield 'thừa dữ liệu', sample + '0\n'
    if kind == 8:
        yield 'tổng Q vượt giới hạn', '2\n' + case(kind, 1, LIMIT) + case(kind, 1)
        yield 'Q bằng 0', '1\n1 0\n0\n'
        yield 'Q vượt giới hạn', '1\n1 200001\n0\n'
        yield 'vị trí ngoài dãy', '1\n1 1\n0\n1 1 0 2\n'
    if kind == 2:
        yield 'mốc ngoài dãy', '1\n1 2 0\n'
        yield 'giá trị mốc vượt giới hạn', f'1\n1 1 {VALUE + 1}\n'
        yield 'chênh lệch vượt giới hạn', f'1\n2 1 0\n{VALUE + 1}\n'
    else:
        header, _, *rest = case(kind, 1).splitlines()
        yield 'giá trị ngoài giới hạn', '\n'.join(['1', header, str(VALUE + 1), *rest, ''])
        if kind == 9:
            yield 'giá trị của B ngoài giới hạn', f'1\n1\n0\n{-VALUE - 1}\n'
    if kind in (6, 7, 8):
        header = '2 1' if kind == 8 else '2'
        query_position = ' 1' if kind == 8 else ''
        yield 'đoạn đảo đầu mút', f'1\n{header}\n0 0\n2 1 0{query_position}\n'
    if kind in (4, 5, 6, 7, 8):
        header = '1 1' if kind == 8 else '1'
        ends = '1' if kind in (4, 5) else '1 1'
        position = ' 1' if kind == 8 else ''
        yield 'giá trị cập nhật vượt giới hạn', f'1\n{header}\n0\n{ends} {-VALUE - 1}{position}\n'


def require_exit(command, *, accept, timeout, data=None, context, reason=None):
    process = subprocess.run(command, input=data, capture_output=True, timeout=timeout)
    assert (process.returncode == 0) == accept, (context, process.returncode, process.stderr)
    if reason is not None:
        assert reason in process.stderr, (context, process.stderr)


def compile_source(source, standard):
    compiler = os.environ.get('CXX', 'g++')
    flags = shlex.split(os.environ.get('CXXFLAGS', '-O2 -Wall -Wextra -Werror'))
    binary = execcmd(source)[0]
    subprocess.run([compiler, *flags, f'-std={standard}', '-I', str(ROOT / 'common'),
                    str(source), '-o', binary], check=True)


def audit(kind, update_hashes):
    base = ROOT / 'custom' / f'tdiff{kind:03}'
    examples = list(read_samples(base))
    for data, expected in examples:
        assert oracle(kind, data) == list(map(int, expected.split())), f'{base.name}: sai đáp án mẫu'

    problem = Problem(ROOT, base)
    problem.ignore_warning = False
    problem.health_check()
    timeout = problem.config['timelimit']
    assert timeout == problem.config['upload']['time_limit'] == 1.0
    assert problem.config['params']['N_MAX'] == LIMIT
    assert problem.config['params']['T_MAX'] == 10000
    if kind == 8:
        assert problem.config['params']['Q_MAX'] == LIMIT
    assert problem.config['title'] == (base / 'task.md').read_text().splitlines()[0][2:]
    problem.generate_params_h()
    for source in (base / 'gen/cases.cpp', problem.verifier, problem.checker):
        compile_source(source, 'c++17')
    compile_source(problem.get_correct_filename(), 'c++11')
    problem.make_inputs()

    output_dir = base / 'out'
    output_dir.mkdir(exist_ok=True)
    longest = 0.0
    coverage = Counter()
    with TemporaryDirectory() as scratch:
        expected_path = Path(scratch) / 'expected.out'
        wrong_path = Path(scratch) / 'wrong.out'
        for input_path in sorted((base / 'in').glob('*.in')):
            data = input_path.read_bytes()
            coverage['cases'] += 1
            coverage['multiple'] += int(int(data.split(maxsplit=1)[0]) > 1)
            require_exit(execcmd(problem.verifier), accept=True, timeout=timeout,
                         data=data, context=input_path.name)
            output_path = output_dir / f'{input_path.stem}.out'
            started = perf_counter()
            problem.run_solution(problem.get_correct_filename(), input_path, output_path, timeout)
            longest = max(longest, perf_counter() - started)
            expected = oracle(kind, data)
            assert list(map(int, output_path.read_bytes().split())) == expected, input_path
            if input_path.stem.startswith('example_'):
                index = int(input_path.stem.split('_')[-1])
                assert output_path.read_text() == examples[index][1], input_path
            expected_path.write_text(' '.join(map(str, expected)) + '\n')
            args = [str(input_path), str(output_path), str(expected_path)]
            require_exit(execcmd(problem.checker, args), accept=True, timeout=timeout,
                         context=input_path.name)
        input_path = base / 'in/example_00.in'
        expected = list(map(int, examples[0][1].split()))
        expected_path.write_text(' '.join(map(str, expected)) + '\n')
        for wrong in ([], expected + [0], [expected[0] + 1] + expected[1:]):
            wrong_path.write_text(' '.join(map(str, wrong)) + '\n')
            args = [str(input_path), str(wrong_path), str(expected_path)]
            require_exit(execcmd(problem.checker, args), accept=False, timeout=timeout,
                         context='checker phải từ chối đầu ra sai')
    aggregate_errors = {
        'tổng N vượt giới hạn': b'sum of N exceeds',
        'tổng Q vượt giới hạn': b'sum of Q exceeds',
    }
    for label, data in invalid_inputs(kind, examples[0][0]):
        require_exit(execcmd(problem.verifier), accept=False, timeout=timeout,
                     data=data.encode(), context=label, reason=aggregate_errors.get(label))
        coverage['invalid'] += 1
    assert coverage['multiple'] >= 2
    assert coverage['cases'] == sum(test['number'] for test in problem.config['tests'])
    if update_hashes:
        problem.ignore_warning = True
        problem.write_hashes()
    problem.assert_hashes()
    return f"{base.name.upper()} {coverage['cases']} test, {coverage['invalid']} đầu vào bị từ chối, tối đa {longest:.3f} s"


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem', type=int, choices=range(10))
    parser.add_argument('--update-hashes', action='store_true')
    parser.add_argument('--jobs', type=int, default=3)
    args = parser.parse_args()
    kinds = range(10) if args.problem is None else [args.problem]
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        for summary in pool.map(lambda kind: audit(kind, args.update_hashes), kinds):
            print(summary, flush=True)


if __name__ == '__main__':
    main()
