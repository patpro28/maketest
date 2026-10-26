"""Generate and audit dpstring00..09, with no HTML or network operations."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import importlib.util
import itertools
import json
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
from problem import Problem
import toml

NAMES = [f'dpstring{i:02}' for i in range(10)]
LANGUAGES = ['PY3', 'CPP11', 'CPP14', 'CPP17', 'CPP20', 'JAVA8', 'C', 'PAS']


def run(executable, data, *args, timeout=5):
    result = subprocess.run([str(executable), *map(str, args)], input=data,
                            text=True, capture_output=True, timeout=timeout)
    assert result.returncode == 0, (executable, result.stderr)
    return result.stdout.strip()


def compile_source(source):
    # The submitted solutions also compile as C++11.
    standard = 'c++11' if source.parent.name == 'sol' else 'c++17'
    command = ['g++', '-O2', f'-std={standard}', '-Wall', '-Wextra', '-Werror',
               '-Wno-unused-result', '-I', str(ROOT/'common'), str(source),
               '-o', str(source.with_suffix(''))]
    result = subprocess.run(command, text=True, capture_output=True)
    assert result.returncode == 0, (source, result.stdout, result.stderr)


def decode(num, data):
    tokens = data.split()
    n = int(tokens[0])
    if num == 5:
        return tokens[3], [], int(tokens[1]), int(tokens[2])
    return tokens[1], list(map(int, tokens[2:])) if num else [1]*n, 0, 0


def encode(num, case):
    s, w, x, y = case
    if num == 5:
        return f'{len(s)} {x} {y}\n{s}\n'
    return f'{len(s)}\n{s}\n' + (' '.join(map(str, w))+'\n' if num else '')


def valid_subsequence(num, s):
    if num in (0, 2):
        return all(a != b for a, b in zip(s, s[1:]))
    if num == 1:
        return all((a in 'aeiou') != (b in 'aeiou') for a, b in zip(s, s[1:]))
    if num == 3:
        return 'aaa' not in s and 'bbb' not in s
    if num == 6:
        types = ''.join('v' if c in 'aeiou' else 'c' for c in s)
        return 'vv' not in types and 'ccc' not in types
    if num == 7:
        return len(s) % 2 == 0 and all(s[i] != s[i+1] for i in range(0, len(s), 2))
    if num == 8:
        return 'aba' not in s
    raise ValueError(num)


def brute(num, case):
    s, w, x, y = case
    if num == 5:
        best = 10**30
        unknown = [i for i, c in enumerate(s) if c == '?']
        for letters in itertools.product('AB', repeat=len(unknown)):
            result = list(s)
            for i, c in zip(unknown, letters):
                result[i] = c
            value = sum(x if a+b == 'AB' else y if a+b == 'BA' else 0
                        for a, b in zip(result, result[1:]))
            best = min(best, value)
        return best
    if num in (4, 9):
        alphabet = 'RGB' if num == 4 else 'ABCD'
        distance = 1 if num == 4 else 2
        def visit(i, tail):
            if i == len(s):
                return 0
            return min((0 if c == s[i] else w[i]) + visit(i+1, (tail+c)[-distance:])
                       for c in alphabet if c not in tail)
        return visit(0, '')
    keep = 0
    for mask in range(1 << len(s)):
        selected = [i for i in range(len(s)) if mask >> i & 1]
        text = ''.join(s[i] for i in selected)
        if valid_subsequence(num, text):
            keep = max(keep, sum(w[i] for i in selected))
    return keep if num in (1, 6, 7) else sum(w) - keep


def load_reference(p):
    spec = importlib.util.spec_from_file_location(p.name+'_reference', p/'sol/correct.py')
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.solve


def audit_statement(p, reference):
    task = (p/'task.md').read_text()
    headings = re.findall(r'^#{1,6} .+$', task, re.M)
    assert headings[0].startswith('# '+p.name.upper()+' — '), (p, headings)
    expected = ['### Đề bài', '### Dữ liệu vào', '### Dữ liệu ra', '### Ràng buộc',
                '### Sample Input 1', '### Sample Output 1',
                '### Sample Input 2', '### Sample Output 2', '### Giải thích']
    assert headings[1:] == expected, (p, headings)
    blocks = re.findall(r'```text\n(.*?)\n```', task, re.S)
    assert len(blocks) == 4, p
    for i in range(2):
        data = (p/'gen'/f'example_{i:02}.in').read_text()
        assert blocks[2*i]+'\n' == data, p
        assert str(reference(data)) == blocks[2*i+1], (p, 'sample answer')
    assert not list(p.glob('*.html')), p


def audit_config(problem):
    config = problem.config
    assert config['timelimit'] == 0.5
    assert config['upload'] == dict(time_limit=0.5, group='03', classes='C',
                                   types=['dp_string'], allowed_languages=LANGUAGES, partial=True)
    assert sum(test['number'] for test in config['tests']) == 32
    assert len(config['solutions']) == 2


def random_cases(num, rng):
    alphabet = 'RGB' if num == 4 else 'AB?' if num == 5 else 'ABCD' if num == 9 else 'abeiz' if num in (1, 6) else 'abcz' if num == 2 else 'ab'
    for _ in range(100):
        n = rng.randint(1, 7 if num in (4, 9) else 11)
        s = ''.join(rng.choice(alphabet) for _ in range(n))
        w = [rng.choice([0, 1, 2, 9, 10**9]) for _ in range(n)] if num else [1]*n
        yield s, w, rng.choice([0, 1, 7, 10**9]), rng.choice([0, 2, 9, 10**9])


def exhaustive_cases(num):
    alphabet = 'RGB' if num == 4 else 'AB?' if num == 5 else 'ABCD' if num == 9 else 'ab'
    maximum = 3 if num in (4, 5, 9) else 6
    for n in range(1, maximum+1):
        for symbols in itertools.product(alphabet, repeat=n):
            s = ''.join(symbols)
            yield s, [1]*n if num == 0 else [1+(i%3) for i in range(n)], 3, 7


def audit_verifier(p, num, sample):
    s, w, x, y = decode(num, sample)
    cases = [sample+'0\n', '', '0\n', sample.replace(s, '#'*len(s), 1),
             sample.replace(s, s+s, 1), sample.rsplit('\n', 2)[0]+'\n']
    nmax = toml.load(p/'info.toml')['params']['N_MAX']
    cases += [sample.replace(str(len(s)), str(nmax+1), 1)]
    if num == 5:
        cases += [encode(num, (s, [], -1, y)), encode(num, (s, [], x, 10**9+1))]
    elif num != 0:
        cases += [encode(num, (s, [-1]+w[1:], 0, 0)),
                  encode(num, (s, [10**9+1]+w[1:], 0, 0)),
                  encode(num, (s, w[:-1], 0, 0))]
    for data in cases:
        result = subprocess.run([str(p/'verifier')], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p, 'accepted invalid input', data)


def audit_checker(p, data, expected):
    with tempfile.TemporaryDirectory() as directory:
        inp, out, ans = [Path(directory)/name for name in ('input', 'output', 'answer')]
        inp.write_text(data)
        ans.write_text(str(expected)+'\n')
        for value, correct in [(str(expected)+'\n', True),
                               (' \n'+str(expected)+' \n', True),
                               (str(expected+1)+'\n', False), ('', False), ('abc\n', False),
                               (str(expected)+' 0\n', False), (str(expected)+' junk\n', False)]:
            out.write_text(value)
            result = subprocess.run([str(p/'checker'), str(inp), str(out), str(ans)], capture_output=True)
            assert (result.returncode == 0) == correct, (p, value, result.stderr)


def assert_reproducible(problem):
    for test in problem.config['tests']:
        if not test['name'].endswith('.cpp'):
            continue
        exe = problem.basedir/'gen'/Path(test['name']).stem
        for seed in range(test['number']):
            expected = (problem.basedir/'in'/f'{exe.name}_{seed:02}.in').read_text().strip()
            assert run(exe, '', seed) == expected, (exe, seed, 'not reproducible')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem', nargs='+', choices=NAMES, default=NAMES)
    parser.add_argument('--update-hashes', action='store_true')
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR)
    problems = [Problem(ROOT, ROOT/'custom'/name) for name in args.problem]
    sources = []
    for problem in problems:
        problem.health_check()
        problem.generate_params_h()
        audit_config(problem)
        sources += [problem.get_correct_filename(), problem.checker, problem.verifier]
        sources += [problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp')]
    print(f'Compiling {len(sources)} sources for {len(problems)} problems...', flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source, sources):
            pass
    for problem in problems:
        started = time.monotonic()
        p = problem.basedir
        num = int(p.name[-2:])
        reference = load_reference(p)
        audit_statement(p, reference)
        problem.make_inputs()
        problem.verify_inputs()
        problem.make_outputs(True)
        problem.judge(p/'sol/correct.cpp', {})
        problem.judge(p/'sol/correct.py', {})
        assert problem.check_all_solutions_used()
        generated_brute = 0
        maximum = False
        wide_answer = False
        for path in sorted((p/'in').glob('*.in')):
            data = path.read_text()
            case = decode(num, data)
            expected = int((p/'out'/path.with_suffix('.out').name).read_text())
            assert reference(data) == expected, (path, 'independent reference differs')
            wide_answer |= expected > 2**31-1
            maximum |= len(case[0]) == problem.config['params']['N_MAX']
            if path.stem.startswith(('example', 'small', 'edge')):
                assert brute(num, case) == expected, (path, 'enumeration differs')
                generated_brute += 1
        assert maximum, p
        if num in (1, 2, 3, 4, 5, 6, 7, 9):
            assert wide_answer, (p, 'missing a 64-bit answer test')
        count = 0
        rng = random.Random(20261025+num)
        for case in itertools.chain(exhaustive_cases(num), random_cases(num, rng)):
            data = encode(num, case)
            expected = brute(num, case)
            assert reference(data) == expected, (p, data, 'Python reference')
            assert int(run(p/'sol/correct', data)) == expected, (p, data, 'C++ reference')
            count += 1
        sample = (p/'gen/example_00.in').read_text()
        audit_verifier(p, num, sample)
        # Check the checker with both the sample and the largest numeric answer.
        audit_checker(p, sample, reference(sample))
        data = max((path.read_text() for path in (p/'in').glob('*.in')), key=reference)
        audit_checker(p, data, reference(data))
        assert_reproducible(problem)
        if args.update_hashes:
            (p/'hash.json').write_text(json.dumps(problem.calc_hashes(), indent=2, sort_keys=True)+'\n')
        problem.assert_hashes()
        print(f'{p.name}: 32 test pairs, C++/Python AC within 0.5s; {generated_brute} generated brute checks; '
              f'{count} exhaustive/random checks; statement, metadata, checker, verifier, '
              f'reproducibility and hashes OK ({time.monotonic()-started:.1f}s).', flush=True)
    print('All checks passed. No HTML generated and no problems uploaded.', flush=True)


if __name__ == '__main__':
    main()
