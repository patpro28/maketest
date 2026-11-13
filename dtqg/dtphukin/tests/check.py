"""Generate and verify DTPHUKIN without exporting HTML."""
import argparse
from functools import lru_cache
from pathlib import Path
import re
import subprocess
import sys
import tempfile
from time import perf_counter

BASE = Path(__file__).resolve().parents[1]
ROOT = BASE.parents[1]
sys.path.insert(0, str(ROOT))

from problem import Problem, execcmd


@lru_cache(None)
def can_fill(length, state):
    if state == (1 << length) - 1:
        return True
    for left in range(length):
        for right in range(left + 1, length + 1):
            width = right - left
            interval = ((1 << width) - 1) << left
            new_state = state | interval
            if new_state != state and 2 * (state & interval).bit_count() > width:
                if can_fill(length, new_state):
                    return True
    return False


def check_exhaustive(command, time_limit):
    arrays = [(n, bits) for n in range(1, 11) for bits in range(1 << n)]
    data = [str(len(arrays))]
    expected = []
    for n, bits in arrays:
        data.extend((str(n), ' '.join(str((bits >> i) & 1) for i in range(n))))
        expected.append(sum(
            can_fill(right - left, (bits >> left) & ((1 << (right - left)) - 1))
            for left in range(n) for right in range(left + 1, n + 1)
        ))
    output = subprocess.run(command, input='\n'.join(data) + '\n', text=True,
                            capture_output=True, timeout=time_limit, check=True)
    actual = list(map(int, output.stdout.split()))
    assert len(actual) == len(expected), 'Wrong number of output values'
    for (n, bits), got, want in zip(arrays, actual, expected):
        if got != want:
            values = [bits >> i & 1 for i in range(n)]
            raise AssertionError(f'{values}: expected {want}, got {got}')
    return len(arrays)


def check_problem(update_hashes):
    problem = Problem(ROOT, BASE)
    time_limit = problem.config['timelimit']
    assert time_limit == problem.config['upload']['time_limit'] == 1.0
    statement = (BASE / 'task.md').read_text()
    assert statement.splitlines()[0] == '# ' + problem.config['title']
    assert re.findall(r'^### (.*)$', statement, re.M) == [
        'Đề bài', 'Dữ liệu vào', 'Dữ liệu ra', 'Ràng buộc',
        'Sample Input 1', 'Sample Output 1', 'Sample Input 2', 'Sample Output 2', 'Giải thích',
    ]
    samples = re.findall(r'^```text\n(.*?)^```$', statement, re.M | re.S)
    assert not re.search(r'^# ', (BASE / 'solution.md').read_text(), re.M)

    problem.health_check()
    problem.generate_params_h()
    sources = (BASE / 'gen/cases.cpp', problem.verifier, problem.checker,
               problem.get_correct_filename())
    for source in sources:
        source.with_suffix('.exe' if sys.platform == 'win32' else '').unlink(missing_ok=True)
    problem.compile_gens()
    problem.compile_verifier()
    problem.compile_checker()
    problem.compile_correct()
    problem.clean()
    problem.make_inputs()
    problem.verify_inputs()

    maximum_time = 0.0
    inputs = sorted((BASE / 'in').glob('*.in'))
    outdir = BASE / 'out'
    outdir.mkdir()
    for infile in inputs:
        outfile = outdir / (infile.stem + '.out')
        start = perf_counter()
        problem.run_solution(problem.get_correct_filename(), infile, outfile, timeout=time_limit)
        maximum_time = max(maximum_time, perf_counter() - start)
        subprocess.run(execcmd(problem.checker, list(map(str, (infile, outfile, outfile)))),
                       check=True, capture_output=True)

    for index in range(2):
        assert (BASE / 'in' / f'example_{index:02}.in').read_text() == samples[2 * index]
        assert (outdir / f'example_{index:02}.out').read_text() == samples[2 * index + 1]
    for index, value in {2: 0, 3: 20000100000, 5: 66667, 7: 200001,
                         8: 200001, 9: 9999900002}.items():
        assert (outdir / f'cases_{index:02}.out').read_text() == f'{value}\n'

    invalid = (
        '0\n', '10001\n', '1\n0\n', '1\n200001\n', '1\n1\n2\n', '1\n2\n1\n',
        '2\n200000\n' + '0 ' * 199999 + '0\n1\n0\n',
    )
    for data in invalid:
        result = subprocess.run(execcmd(problem.verifier), input=data, text=True, capture_output=True)
        assert result.returncode != 0, 'Verifier accepted invalid input'

    with tempfile.TemporaryDirectory() as directory:
        candidate = Path(directory) / 'actual.out'
        for data in ('3\n1\n5\n', '3\n1\n', '3\n1\n6\n0\n'):
            candidate.write_text(data)
            args = [BASE / 'in/example_00.in', candidate, outdir / 'example_00.out']
            result = subprocess.run(execcmd(problem.checker, list(map(str, args))), capture_output=True)
            assert result.returncode != 0, 'Checker accepted incorrect output'

    exhaustive = check_exhaustive(execcmd(problem.get_correct_filename()), time_limit)
    if update_hashes:
        problem.ignore_warning = True
        problem.write_hashes()
    problem.assert_hashes()
    print(f'{len(inputs)} test files, {exhaustive} exhaustive arrays, '
          f'{len(invalid)} invalid inputs, 3 incorrect outputs, '
          f'{len(problem.calc_hashes())} hashes, max {maximum_time:.3f}s')


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--update-hashes', action='store_true')
    args = parser.parse_args()
    check_problem(args.update_hashes)
