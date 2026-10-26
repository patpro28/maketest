"""Generate and independently validate PREFIX10..19 without exporting HTML."""
import argparse
from bisect import bisect_left
from concurrent.futures import ThreadPoolExecutor
from itertools import accumulate, product
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
from problem import Problem, compile as compile_source
import toml


def decode(k, text):
    t = iter(text.split())
    n = int(next(t))
    m = int(next(t)) if k == 14 else 0
    q = 0 if k == 19 else int(next(t))
    a = [[int(next(t)) for _ in range(m)] for _ in range(n)] if k == 14 else next(t) if k in (12, 17) else [int(next(t)) for _ in range(n)]
    queries = []
    for _ in range(q):
        if k == 14: queries.append(tuple(int(next(t)) for _ in range(4)))
        else:
            l, r = int(next(t)), int(next(t))
            queries.append((l, r, next(t)) if k == 12 else (l, r))
    return a, queries


def encode(k, a, queries):
    head = str(len(a)) + (' ' + str(len(a[0])) if k == 14 else '')
    head += '' if k == 19 else ' ' + str(len(queries))
    body = '\n'.join(' '.join(map(str, row)) for row in a) if k == 14 else a if k in (12, 17) else ' '.join(map(str, a))
    return head + '\n' + body + '\n' + ''.join(' '.join(map(str, q)) + '\n' for q in queries)


def brute(k, a, queries):
    if k == 19:
        return [sum(sum(a[:i]) == sum(a[i:j]) == sum(a[j:]) for i in range(1, len(a)) for j in range(i + 1, len(a)))]
    result = []
    for query in queries:
        l, r = query[:2]
        if k == 10: v = sum(x % 2 == 0 for x in a[l-1:r])
        elif k == 11: v = sum(x * (-1 if i % 2 else 1) for i, x in enumerate(a[l-1:r]))
        elif k == 12: v = a[l-1:r].count(query[2])
        elif k == 13: v = sum(i * x for i, x in enumerate(a[l-1:r], 1))
        elif k == 14:
            x1, y1, x2, y2 = query
            v = sum(sum(row[y1-1:y2]) for row in a[x1-1:x2])
        elif k == 15: v = sum(a[(l-1+i) % len(a)] for i in range(r))
        elif k == 16: v = sum(abs(a[i] - a[i-1]) for i in range(min(l, r), max(l, r)))
        elif k == 17: v = 1 + sum(a[i] != a[i-1] for i in range(l, r))
        elif k == 18: v = sum(sum(a[:i]) for i in range(l, r+1))
        result.append(v)
    return result


def reference(k, a, queries):
    """Independent algorithms for all full-size data, including a different split count."""
    n = len(a)
    if k == 19:
        if sum(a) % 3: return [0]
        target = sum(a) // 3
        prefix = list(accumulate(a))
        suffix_count = [0] * (n + 1)
        suffix = 0
        for i in range(n-1, -1, -1):
            suffix += a[i]
            suffix_count[i] = suffix_count[i+1] + (suffix == target)
        return [sum(suffix_count[i+2] for i in range(n-2) if prefix[i] == target)]
    if k == 12:
        # Occurrence indices and binary searches rather than 26 prefix arrays.
        positions = [[] for _ in range(26)]
        for i, c in enumerate(a, 1): positions[ord(c)-97].append(i)
        return [bisect_left(positions[ord(c)-97], r+1) - bisect_left(positions[ord(c)-97], l) for l, r, c in queries]
    if k == 14:
        # Row accumulation then vertical accumulation, independent of the C++ recurrence.
        m = len(a[0]); p = [[0] * (m+1)]
        for row in a:
            row_sum = [0] + list(accumulate(row))
            p.append([x+y for x, y in zip(p[-1], row_sum)])
        return [p[x2][y2] - p[x1-1][y2] - p[x2][y1-1] + p[x1-1][y1-1] for x1,y1,x2,y2 in queries]
    if k == 16:
        p = [0] + list(accumulate(abs(a[i]-a[i-1]) for i in range(1,n)))
        return [abs(p[r-1]-p[l-1]) for l,r in queries]
    if k == 17:
        # Group id of each character, equal to number of runs through that character.
        group = [1]
        for i in range(1,n): group.append(group[-1] + (a[i] != a[i-1]))
        return [group[r-1]-group[l-1]+1 for l,r in queries]
    if k == 10: p = [0] + list(accumulate(x % 2 == 0 for x in a))
    elif k == 11: p = [0] + list(accumulate(x * (-1 if i % 2 else 1) for i,x in enumerate(a)))
    elif k == 13:
        # Sum of prefix sums gives weights in reverse order; subtract from (R+1)*sum.
        p = [0] + list(accumulate(a)); double = [0] + list(accumulate(p[1:]))
        return [(r-l+2)* (p[r]-p[l-1]) - (double[r]-double[l-1] - (r-l+1)*p[l-1]) for l,r in queries]
    elif k == 15:
        p = [0] + list(accumulate(a))
        return [p[l+length-1]-p[l-1] if l+length-1 <= n else p[-1]-p[l-1]+p[l+length-1-n] for l,length in queries]
    elif k == 18:
        # Each deposit contributes to all later days in the requested interval.
        p = [0] + list(accumulate(a)); w = [0] + list(accumulate((i+1)*x for i,x in enumerate(a)))
        return [(r-l+1)*p[l-1] + (r+1)*(p[r]-p[l-1]) - (w[r]-w[l-1]) for l,r in queries]
    return [(p[r]-p[l-1]) * (-1 if k == 11 and l % 2 == 0 else 1) for l,r in queries]


def solve(p, text):
    start = time.monotonic()
    result = subprocess.run([str(p/'sol/correct')], input=text, text=True, capture_output=True, timeout=5)
    assert result.returncode == 0, (p, result.stderr)
    return list(map(int, result.stdout.split())), time.monotonic() - start


def audit(p, k):
    text = (p/'task.md').read_text()
    assert text.startswith(f'# PREFIX{k} — ')
    expected = ['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc','Sample Input 1','Sample Output 1','Sample Input 2','Sample Output 2','Giải thích']
    assert re.findall(r'^### (.*)$', text, re.M) == expected, p
    assert 'Subtask' not in text
    blocks = re.findall(r'```text\n(.*?)```', text, re.S)
    assert len(blocks) == 4
    for i in range(2):
        assert blocks[2*i] == (p/'gen'/f'example_{i:02}.in').read_text()
        a,q = decode(k, blocks[2*i])
        assert brute(k,a,q) == list(map(int,blocks[2*i+1].split()))
    config = toml.load(p/'info.toml')
    assert config['upload'] == toml.load(ROOT/'custom/prefix09/info.toml')['upload']
    assert not list(p.glob('*.html'))


def small_cases(k):
    rng = random.Random(20261023 + k)
    # Enumerate small signed arrays; each input combines every possible interval.
    if k != 14:
        alphabet = 'ab' if k in (12,17) else (0,1,2) if k == 18 else (-1,0,1)
        for n in range(3 if k == 19 else 1, 5):
            for raw in product(alphabet, repeat=n):
                a = ''.join(raw) if k in (12,17) else list(raw)
                queries = [(l,r) for l in range(1,n+1) for r in range(l,n+1)]
                if k in (15,16): queries = list(product(range(1,n+1), repeat=2))
                if k == 12: queries = [(l,r,c) for l,r in queries for c in 'abz']
                yield a, [] if k == 19 else queries
    for _ in range(160):
        n = rng.randint(3 if k == 19 else 1, 16)
        if k == 14:
            m = rng.randint(1,12)
            a = [[rng.randint(-20,20) for _ in range(m)] for _ in range(n)]
            queries = [(1,1,n,m),(n,m,n,m)]
            for _ in range(20):
                x1,x2 = sorted([rng.randint(1,n),rng.randint(1,n)])
                y1,y2 = sorted([rng.randint(1,m),rng.randint(1,m)])
                queries.append((x1,y1,x2,y2))
        else:
            a = ''.join(rng.choice('abcz') for _ in range(n)) if k in (12,17) else [rng.randint(0 if k==18 else -20,20) for _ in range(n)]
            queries = []
            if k != 19:
                for _ in range(20):
                    l,r = rng.randint(1,n),rng.randint(1,n)
                    if k not in (15,16): l,r = sorted((l,r))
                    queries.append((l,r,rng.choice('abcz')) if k==12 else (l,r))
        yield a,queries


def negative_checks(p,k):
    good = (p/'gen/example_00.in').read_text()
    a,q = decode(k,good)
    # Missing body, extra token, invalid N, upper/lower value bounds and invalid queries.
    invalid = [good.split('\n',1)[0]+'\n',good+'0\n', '0'+good[good.index(' ' if k != 19 else '\n'):]]
    if k in (12,17):
        invalid += [encode(k,'A'+a[1:],q),good.replace('\n'+a+'\n','\n'+a+'a\n',1)]
    elif k == 14:
        b = [row[:] for row in a]; b[0][0] = 1000000001
        invalid += [encode(k,b,q),encode(k,a,[(1,1,len(a)+1,1)])]
        invalid += ['701 1 1\n','1 701 1\n']
    else:
        bound = 1000000 if k in (13,18) else 1000000000
        invalid += [encode(k,[bound+1]+a[1:],q),encode(k,[-1 if k==18 else -bound-1]+a[1:],q)]
    if k == 19: invalid += ['2\n0 0\n','200001\n']
    elif k != 14:
        bad = (1,len(a)+1,'a') if k==12 else (1,len(a)+1)
        invalid.append(encode(k,a,[bad]))
        bad = (0,1,'a') if k==12 else (0,1)
        invalid.append(encode(k,a,[bad]))
        if k not in (15,16): invalid.append(encode(k,a,[(2,1,'a') if k==12 else (2,1)]))
        if k==12: invalid.append(encode(k,a,[(1,1,'ab')]))
    for data in invalid:
        result = subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode != 0,(p,'accepted bad input',data)
    answer = (p/'out/example_00.out').read_text(); tokens = answer.split()
    with tempfile.TemporaryDirectory() as td:
        candidate = Path(td)/'answer.out'
        wrong = [str(int(tokens[0])+1)] + tokens[1:]
        for output,ok in [(answer,True),('\n\t'+'  '.join(tokens)+'\n',True),(' '.join(wrong),False),(' '.join(tokens[:-1]),False),(answer+'42\n',False),('abc\n',False)]:
            candidate.write_text(output)
            result = subprocess.run([str(p/'checker'),str(p/'in/example_00.in'),str(candidate),str(p/'out/example_00.out')],capture_output=True)
            assert (result.returncode==0)==ok,(p,output,result.stderr)
    return len(invalid)+6


def check(k, generate):
    p = ROOT/'custom'/f'prefix{k}'; audit(p,k)
    problem = Problem(ROOT,p)
    if generate:
        problem.health_check(); problem.generate_params_h()
        sources = [p/'sol/correct.cpp',p/'gen/cases.cpp',p/'verifier.cpp',p/'checker.cpp']
        # These compilations have independent outputs; compiler failures are checked explicitly.
        with ThreadPoolExecutor(max_workers=4) as pool:
            list(pool.map(lambda source: compile_source(source,ROOT),sources))
        for source in sources: assert source.with_suffix('').exists(), source
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True)
    maximum_time = 0
    paths = sorted((p/'in').glob('*.in'))
    assert len(paths)==22,(p,len(paths))
    for inp in paths:
        text = inp.read_text(); a,q = decode(k,text)
        expected = reference(k,a,q)
        actual = list(map(int,(p/'out'/(inp.stem+'.out')).read_text().split()))
        assert actual == expected,(p,inp,'independent reference')
        # Check freshly run solution and record full-case running time.
        actual,elapsed = solve(p,text)
        maximum_time = max(maximum_time,elapsed)
        assert actual == expected,(p,inp,'solution')
    small = 0
    for a,q in small_cases(k):
        expected = brute(k,a,q)
        assert reference(k,a,q)==expected,(k,a,q,'oracle')
        actual,_ = solve(p,encode(k,a,q))
        assert actual == expected,(k,a,q,actual,expected)
        small += 1
    attacks = negative_checks(p,k)
    if generate:
        problem.ignore_warning=True; problem.write_hashes()
        problem.make_inputs(); problem.verify_inputs(); problem.assert_hashes()
    else: problem.assert_hashes()
    print(f'prefix{k}: 22 tests, {small} brute comparisons, {attacks} validator/checker checks; hashes OK; slowest {maximum_time:.3f}s',flush=True)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--problem',choices=[f'prefix{k}' for k in range(10,20)])
    parser.add_argument('--generate',action='store_true')
    args=parser.parse_args(); logging.basicConfig(level=logging.ERROR)
    for k in range(10,20):
        if args.problem is None or args.problem==f'prefix{k}': check(k,args.generate)

if __name__ == '__main__': main()
