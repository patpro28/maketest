"""Generate and audit the ten LCS problems without HTML or remote uploads."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass, field, replace
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
from problem_upload import ProblemUpload

CODES = [100, 101, 102, 103, 130, 131, 132, 150, 151, 152]
NAMES = [f'dpstr{code}' for code in CODES]
LANGUAGES = ['PY3', 'CPP11', 'CPP14', 'CPP17', 'CPP20', 'JAVA8', 'C', 'PAS']


@dataclass
class Case:
    a: str
    b: str
    weights: list = field(default_factory=list)
    u: list = field(default_factory=list)
    v: list = field(default_factory=list)
    target: str = 'a'
    k: int = 0


def decode(code, data):
    tokens = data.split()
    n, m = int(tokens[0]), int(tokens[1])
    if code == 151:
        return Case(tokens[3], tokens[4], k=int(tokens[2]))
    case = Case(tokens[2], tokens[3])
    if code == 130:
        case.weights = list(map(int, tokens[4:]))
    if code == 131:
        case.u = list(map(int, tokens[4:4+n]))
        case.v = list(map(int, tokens[4+n:4+n+m]))
    if code in (132, 150):
        case.target = tokens[4]
    return case


def encode(code, case):
    data = f'{len(case.a)} {len(case.b)}' + (f' {case.k}' if code == 151 else '')
    data += f'\n{case.a}\n{case.b}\n'
    if code == 130:
        data += ' '.join(map(str, case.weights))+'\n'
    if code == 131:
        data += ' '.join(map(str, case.u))+'\n'+' '.join(map(str, case.v))+'\n'
    if code in (132, 150):
        data += case.target+'\n'
    return data


def all_subsequences(s, weights=None):
    result = {}
    for mask in range(1 << len(s)):
        indices = [i for i in range(len(s)) if mask >> i & 1]
        text = ''.join(s[i] for i in indices)
        value = sum(weights[i] for i in indices) if weights is not None else len(text)
        result[text] = max(result.get(text, -1), value)
    return result


def brute(code, case):
    first = all_subsequences(case.a, case.u if code == 131 else None)
    second = all_subsequences(case.b, case.v if code == 131 else None)
    common = first.keys() & second.keys()
    if code in (100, 101):
        return max(map(len, common))
    if code == 102:
        return len(case.a)+len(case.b)-2*max(map(len, common))
    if code == 103:
        return len(case.a)+len(case.b)-max(map(len, common))
    if code == 130:
        return max(sum(case.weights[ord(c)-97] for c in text) for text in common)
    if code == 131:
        return sum(case.u)+sum(case.v)-max(first[text]+second[text] for text in common)
    if code == 132:
        return max((len(text) for text in common if text.endswith(case.target)), default=-1)
    if code == 150:
        return max((len(text) for text in common if case.target in text), default=-1)
    if code == 151:
        return max(len(text) for text in common if sum(c in 'aeiou' for c in text) <= case.k)
    if code == 152:
        return max(len(text) for text in common if all(a != b for a, b in zip(text, text[1:])))
    raise ValueError(code)


def run(executable, data, *args, timeout=5):
    result = subprocess.run([str(executable), *map(str, args)], input=data, text=True,
                            capture_output=True, timeout=timeout)
    assert result.returncode == 0, (executable, result.stderr)
    return result.stdout.strip()


def compile_source(source):
    standard = 'c++11' if source.parent.name == 'sol' else 'c++17'
    result = subprocess.run(['g++', '-O2', f'-std={standard}', '-Wall', '-Wextra', '-Werror',
                             '-Wno-unused-result', '-I', str(ROOT/'common'), str(source),
                             '-o', str(source.with_suffix(''))], text=True, capture_output=True)
    assert result.returncode == 0, (source, result.stderr)


def load_reference(p):
    spec = importlib.util.spec_from_file_location(p.name+'_reference', p/'sol/correct.py')
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module.solve


def is_subsequence(small, large):
    it = iter(large)
    return all(c in it for c in small)


def value(code, case, output):
    if code != 101:
        tokens = output.split()
        assert len(tokens) == 1, (code, output)
        return int(tokens[0])
    tokens = output.split()
    assert tokens, 'Empty trace output'
    length = int(tokens[0])
    assert len(tokens) == (2 if length else 1), output
    text = tokens[1] if length else ''
    assert len(text) == length and is_subsequence(text, case.a) and is_subsequence(text, case.b), output
    return length


def audit_statement(p, code, reference):
    task = (p/'task.md').read_text()
    headings = re.findall(r'^#{1,6} .+$', task, re.M)
    assert headings[0].startswith('# '+p.name.upper()+' — ')
    assert headings[1:] == ['### Đề bài', '### Dữ liệu vào', '### Dữ liệu ra', '### Ràng buộc',
                            '### Sample Input 1', '### Sample Output 1',
                            '### Sample Input 2', '### Sample Output 2', '### Giải thích'], (p, headings)
    blocks = re.findall(r'```text\n(.*?)\n```', task, re.S)
    assert len(blocks) == 4, p
    for i in range(2):
        data = (p/'gen'/f'example_{i:02}.in').read_text()
        assert blocks[2*i]+'\n' == data, (p, 'sample input')
        case = decode(code, data)
        assert value(code, case, blocks[2*i+1]) == value(code, case, reference(data)) == brute(code, case)
    solution = (p/'solution.md').read_text()
    assert not re.search(r'kiểm thử|bộ sinh|oracle|verifier|checker|benchmark|chạy test', solution, re.I), p
    assert not list(p.glob('*.html')), p


def audit_config(problem, code):
    upload = dict(time_limit=0.5, group='03', classes='C', types=['dp_string'],
                  allowed_languages=LANGUAGES, partial=True)
    if code == 101:
        upload['checker'] = 'custom'
    assert problem.config['upload'] == upload, problem.basedir
    assert problem.config['timelimit'] == 0.5
    assert sum(t['number'] for t in problem.config['tests']) == (40 if code == 150 else 32)
    metadata = ProblemUpload(problem)
    if code == 101:
        assert metadata.custom_checker == problem.checker
        assert metadata.checker_source == problem.checker.read_bytes()
        assert 'checker' not in metadata.manifest and 'checker_args' not in metadata.manifest
    else:
        assert metadata.manifest['checker'] == 'standard'


def random_cases(code, rng):
    alphabet = 'abc' if code == 152 else 'abcez'
    for _ in range(100):
        n, m = rng.randint(1, 9), rng.randint(1, 9)
        a = ''.join(rng.choice(alphabet) for _ in range(n))
        b = ''.join(rng.choice(alphabet) for _ in range(m))
        yield Case(a, b, weights=[rng.choice([0, 1, 2, 10**9]) for _ in range(26)],
                   u=[rng.choice([0, 1, 9, 10**9]) for _ in range(n)],
                   v=[rng.choice([0, 1, 9, 10**9]) for _ in range(m)],
                   target=rng.choice('abcz'), k=rng.randint(0, 5))


def exhaustive_cases(code):
    words = [''.join(chars) for n in range(1, 4) for chars in itertools.product('ab', repeat=n)]
    for a, b in itertools.product(words, repeat=2):
        yield Case(a, b, weights=[1, 7]+[0]*24, u=[1+i%3 for i in range(len(a))],
                   v=[4-i%3 for i in range(len(b))], target='a', k=1)


def targeted_cases(code):
    pairs = [('abc','abc'), ('aaa','bbb'), ('abc','bac'), ('aaaa','aaa'),
             ('abc','cab'), ('abx','xab'), ('abaca','bacab'), ('aabbc','aabbc'),
             ('a','aaaa'), ('abab','baba'), ('abba','baba')]
    for a, b in pairs:
        if code == 152:
            a, b = a.replace('x','c'), b.replace('x','c')
        yield Case(a, b, weights=[1, 1, 10]+[0]*23,
                   u=[10**9 if i%2 else 0 for i in range(len(a))],
                   v=[0 if i%2 else 10**9 for i in range(len(b))], target='b', k=0)
    if code in (132, 150):
        for a, b, c in [('abx','xab','x'), ('xa','xa','x'), ('ax','ax','x'),
                         ('aaa','bbb','a'), ('aaa','aaa','z'), ('abca','abca','b')]:
            yield Case(a, b, target=c)
    if code == 151:
        for k in range(6):
            yield Case('aeioua','aeioua', k=k)
            yield Case('bcdzb','bcdzb', k=k)
    if code == 131:
        yield Case('aaa','a', u=[5,9,2],v=[4])
        yield Case('ab','ba',u=[100,1],v=[1,100])
        yield Case('abc','abc',u=[0,0,0],v=[0,0,0])


def audit_verifier(p, code, sample, nmax):
    case = decode(code, sample)
    lines = sample.splitlines()
    bad = ['', sample+'0\n', '0 1\na\na\n', sample.rsplit('\n', 2)[0]+'\n']
    for length in [-1, 0, nmax+1]:
        for which in (0,1):
            head = lines[0].split()
            head[which] = str(length)
            bad.append(' '.join(head)+'\n'+'\n'.join(lines[1:])+'\n')
    for row in (1,2):
        for text in ('#', lines[row]+lines[row], ''):
            edited = lines.copy(); edited[row] = text
            bad.append('\n'.join(edited)+'\n')
    if code == 130:
        for replacement in (-1, 10**9+1):
            bad.append(encode(code, replace(case, weights=[replacement]+case.weights[1:])))
        bad.append(encode(code, replace(case, weights=case.weights[:-1])))
    if code == 131:
        for field_name in ('u','v'):
            weights = getattr(case, field_name)
            for replacement in (-1, 10**9+1):
                bad.append(encode(code, replace(case, **{field_name:[replacement]+weights[1:]})))
            bad.append(encode(code, replace(case, **{field_name:weights[:-1]})))
    if code in (132,150):
        for target in ('A','aa','1'):
            bad.append(encode(code, replace(case,target=target)))
    if code == 151:
        bad += [encode(code, replace(case,k=-1)), encode(code, replace(case,k=6))]
    if code == 152:
        bad.append(encode(code, replace(case,a='z'*len(case.a))))
    for data in bad:
        result = subprocess.run([str(p/'verifier')], input=data, text=True, capture_output=True)
        assert result.returncode != 0, (p, 'accepted invalid input', data)


def check_outputs(p, data, answer, outputs):
    with tempfile.TemporaryDirectory() as directory:
        inp, ans, out = [Path(directory)/name for name in ('input','answer','output')]
        inp.write_text(data); ans.write_text(answer+'\n')
        for output, correct in outputs:
            out.write_text(output)
            result = subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)], capture_output=True)
            assert (result.returncode == 0) == correct, (p, output, result.stderr)


def audit_checker(p, code, sample, reference):
    good = reference(sample)
    if code == 101:
        # Both optima must pass although the official answer contains only "ac".
        check_outputs(p, '3 3\nabc\nbac\n', '2\nac', [
            ('2\nac\n', True), ('2\nbc\n', True), (' 2\nbc \n', True),
            ('2\nab\n', False), ('1\na\n', False), ('2\na\n', False),
            ('3\nabc\n', False), ('2\nzz\n', False), ('2\nAC\n', False),
            ('2\nac\n0\n', False), ('', False), ('x\n', False), ('-1\n', False)])
        check_outputs(p, '1 1\na\nb\n', '0', [('0\n',True), ('0\n\n',True),
                                                        ('0\na\n',False), ('1\na\n',False)])
        check_outputs(p, '4 3\naaaa\naaa\n', '3\naaa', [('3\naaa\n',True), ('2\naa\n',False)])
    else:
        expected = int(good)
        check_outputs(p, sample, good, [(good+'\n',True),(' \n'+good+' \n',True),
                       (str(expected+1)+'\n',False),('',False),('abc\n',False),
                       (good+' 0\n',False),(good+' junk\n',False)])
        if code in (132,150):
            check_outputs(p,'1 1\na\nb\nz\n','-1',[('-1\n',True),('0\n',False)])


def assert_reproducible(problem):
    for test in problem.config['tests']:
        if test['name'].endswith('.cpp'):
            exe = problem.basedir/'gen'/Path(test['name']).stem
            for seed in range(test['number']):
                expected = (problem.basedir/'in'/f'{exe.name}_{seed:02}.in').read_text().strip()
                assert run(exe, '', seed) == expected, (exe, seed)


def audit_prefix_regressions(p):
    # (correct answer, output of the submitted prefix-only algorithm).
    answers = [(-1, 1), (1, 2), (1, 3), (1, 3), (2, 4), (2, 4), (1, 299), (3, 299)]
    for seed, (correct, wrong) in enumerate(answers):
        path = p/'in'/f'regression_{seed:02}.in'
        data = path.read_text()
        official = int((p/'out'/f'regression_{seed:02}.out').read_text())
        submitted = int(run(p/'tests/prefix_only_wrong', data))
        assert official == correct and submitted == wrong, (path, official, submitted)
        check_outputs(p, data, str(correct), [(str(correct)+'\n', True),
                                             (str(submitted)+'\n', False)])
    return len(answers)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem', nargs='+', choices=NAMES, default=NAMES)
    parser.add_argument('--update-hashes', action='store_true')
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR)
    problems = [Problem(ROOT, ROOT/'custom'/name) for name in args.problem]
    sources = []
    for problem in problems:
        problem.health_check(); problem.generate_params_h()
        audit_config(problem, int(problem.basedir.name[5:]))
        sources += [problem.get_correct_filename(),problem.checker,problem.verifier]
        sources += [problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp')]
        if problem.basedir.name == 'dpstr150':
            sources.append(problem.basedir/'tests/prefix_only_wrong.cpp')
    print(f'Compiling {len(sources)} sources for {len(problems)} LCS problems...', flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source,sources):
            pass
    for problem in problems:
        started = time.monotonic()
        p = problem.basedir; code = int(p.name[5:]); reference = load_reference(p)
        audit_statement(p, code, reference)
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True)
        problem.judge(p/'sol/correct.cpp',{}); problem.judge(p/'sol/correct.py',{})
        assert problem.check_all_solutions_used()
        generated_brute = 0; maximum = False; wide = False; full_k = False
        for path in sorted((p/'in').glob('*.in')):
            data = path.read_text(); case = decode(code,data)
            expected = value(code,case,(p/'out'/path.with_suffix('.out').name).read_text())
            assert value(code,case,reference(data)) == expected, (path,'reference mismatch')
            wide |= expected > 2**31-1
            largest = len(case.a) == len(case.b) == problem.config['params']['N_MAX']
            maximum |= largest; full_k |= largest and case.k == 5
            if path.stem.startswith(('example','edge','small')) or (path.stem.startswith('regression')
                                                                    and max(len(case.a),len(case.b)) <= 9):
                assert brute(code,case) == expected, (path,'enumeration mismatch')
                generated_brute += 1
        assert maximum, (p,'missing both maximum lengths')
        if code == 151: assert full_k, 'Missing maximum lengths with K=5'
        if code in (130,131): assert wide, (p,'missing a 64-bit answer')
        count = 0
        rng = random.Random(20261028+code)
        for case in itertools.chain(exhaustive_cases(code),random_cases(code,rng),targeted_cases(code)):
            data = encode(code,case); expected = brute(code,case)
            assert value(code,case,reference(data)) == expected, (p,data,'Python mismatch')
            assert value(code,case,run(p/'sol/correct',data)) == expected, (p,data,'C++ mismatch')
            count += 1
        sample = (p/'gen/example_00.in').read_text()
        audit_verifier(p,code,sample,problem.config['params']['N_MAX'])
        audit_checker(p,code,sample,reference)
        if code == 150:
            rejected = audit_prefix_regressions(p)
            print(f'{p.name}: prefix-only wrong solution rejected on all {rejected} regression tests.', flush=True)
        if code in (130,131):
            candidates = [(p/'in'/f'max_{i:02}.in').read_text() for i in range(6)]
            data = max(candidates,key=lambda data:int(reference(data)))
            answer = reference(data)
            check_outputs(p,data,answer,[(answer+'\n',True),(str(int(answer)+1)+'\n',False)])
        assert_reproducible(problem)
        if args.update_hashes:
            (p/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
        problem.assert_hashes()
        pairs = sum(test['number'] for test in problem.config['tests'])
        print(f'{p.name}: {pairs} pairs, C++/Python AC at 0.5s; {generated_brute} generated brute checks; '
              f'{count} additional brute checks; statements, metadata, checker, verifier, '
              f'reproducibility and hashes OK ({time.monotonic()-started:.1f}s).', flush=True)
    print('All checks passed. No HTML generated or problems uploaded. dpstr101 requires its custom checker.',flush=True)


if __name__ == '__main__':
    main()
