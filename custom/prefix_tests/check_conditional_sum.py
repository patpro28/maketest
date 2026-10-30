"""Generate and audit DPPSUM011..020 (labels PREFIX011..020) without HTML or network operations."""
import argparse
from bisect import bisect_left, bisect_right
from concurrent.futures import ThreadPoolExecutor
from itertools import product
import json
import logging
import math
import os
from pathlib import Path
import random
import re
import shlex
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from problem import Problem
import toml


def decode(k, text):
    t = list(map(int, text.split()))
    n, q = t[:2]
    count = 1 if k in (3, 8) else 2 if k == 4 else 0
    params = tuple(t[2:2+count])
    a = t[2+count:2+count+n]
    tail = t[2+count+n:]
    queries = list(zip(tail[::2], tail[1::2]))
    assert len(a) == n and len(queries) == q
    return a, queries, params


def encode(k, a, queries, params=()):
    return ' '.join(map(str, (len(a),len(queries))+tuple(params)))+'\n'+' '.join(map(str,a))+'\n'+''.join(f'{l} {r}\n' for l,r in queries)


def trial_prime(x):
    return x >= 2 and all(x % d for d in range(2, math.isqrt(x)+1))


PRIMES = None

def predicate(k, x, params):
    if k == 0: return x % 2 == 0
    if k == 1: return x > 0
    if k == 2: return x < 0
    if k == 3: return x % params[0] == 0
    if k == 4: return params[0] <= x <= params[1]
    if k == 5: return x >= 0 and math.isqrt(x)**2 == x
    if k == 6: return trial_prime(x)
    if k == 7: return str(x) == str(x)[::-1]
    if k == 8: return sum(map(int,str(x))) == params[0]
    if k == 9: return '7' in str(x)
    raise ValueError(k)


def reference(k, a, queries, params):
    global PRIMES
    if k == 6 and PRIMES is None:
        PRIMES = bytearray(b'\1') * 1000001
        PRIMES[:2] = b'\0\0'
        for i in range(2,1001):
            if PRIMES[i]:
                PRIMES[i*i::i] = bytes((1000000-i*i)//i+1)
    positions = []
    weights = [0]
    for i, x in enumerate(a, 1):
        if PRIMES[x] if k == 6 else predicate(k, x, params):
            positions.append(i)
            weights.append(weights[-1] + x)
    return [weights[bisect_right(positions,r)]-weights[bisect_left(positions,l)] for l,r in queries]


def brute(k, a, queries, params):
    return [sum(x for x in a[l-1:r] if predicate(k,x,params)) for l,r in queries]


def compile_source(source):
    compiler = os.environ.get('CXX','g++')
    flags = shlex.split(os.environ.get('CXXFLAGS','-O2 -std=c++17 -Wall -Wextra -Werror'))
    subprocess.run([compiler,*flags,'-I',str(ROOT/'common'),'-I',str(ROOT/'atcoder'),str(source),'-o',str(source.with_suffix(''))],check=True)


def solve(p, text):
    result = subprocess.run([str(p/'sol/correct')],input=text,text=True,capture_output=True,timeout=5)
    assert result.returncode == 0,(p,result.stderr)
    return list(map(int,result.stdout.split()))


def audit(p,k):
    text = (p/'task.md').read_text()
    assert text.startswith(f'# PREFIX{k+11:03} — ')
    assert re.findall(r'^### (.+)$',text,re.M) == ['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc','Sample Input 1','Sample Output 1','Sample Input 2','Sample Output 2','Giải thích']
    assert 'Subtask' not in text
    assert toml.load(p/'info.toml')['title'].startswith(f'PREFIX{k+11:03} - ')
    assert (p/'solution.md').read_text().startswith(f'# PREFIX{k+11:03} — ')
    blocks = re.findall(r'```text\n(.*?)```',text,re.S)
    assert len(blocks)==4
    for i in range(2):
        assert blocks[2*i] == (p/'gen'/f'example_{i:02}.in').read_text()
        assert list(map(int,blocks[2*i+1].split())) == brute(k,*decode(k,blocks[2*i]))
    expected_upload = {
        'time_limit': 0.25, 'group': '03', 'classes': 'C',
        'types': ['dp_prefix_sum', 'dp_sequence'],
        'allowed_languages': ['PY3', 'CPP11', 'CPP14', 'CPP17', 'CPP20', 'JAVA8', 'C', 'PAS'],
        'partial': True,
    }
    assert toml.load(p/'info.toml')['upload'] == expected_upload
    assert not list(p.glob('*.html'))


def small_cases(k):
    alphabet = (-1,0,1) if k <= 5 else (0,1,2) if k == 6 else (0,7,10)
    for n in range(1,5):
        queries = [(l,r) for l in range(1,n+1) for r in range(l,n+1)]
        params = (2,) if k == 3 else (-1,0) if k == 4 else (7,) if k == 8 else ()
        for a in product(alphabet,repeat=n): yield list(a),queries,params
    rng = random.Random(20261026+k)
    for turn in range(160):
        n = rng.randint(1,20)
        low,high = (-10**9,10**9) if k<=5 else (0,10**6) if k==6 else (0,10**9)
        a = [rng.randint(low,high) for _ in range(n)]
        if k == 5:
            root = rng.randint(0,31622)
            pool = [0,-1,1,root*root,max(low,root*root-1),min(high,root*root+1),high]
            a = [rng.choice(pool) for _ in range(n)]
        if k == 6: a = [rng.choice([0,1,2,3,4,25,997,999983,999999,1000000,rng.randint(0,1000000)]) for _ in range(n)]
        if k == 7: a = [rng.choice([0,1,10,11,121,1001,999999999,1000000000,rng.randint(0,1000000000)]) for _ in range(n)]
        if k == 9: a = [rng.choice([0,7,17,77,700000007,777777777,999999999,1000000000,rng.randint(0,1000000000)]) for _ in range(n)]
        params = (rng.choice([1,2,7,10**9]),) if k == 3 else tuple(sorted((rng.randint(low,high),rng.randint(low,high)))) if k == 4 else (rng.choice([0,1,7,10,81]),) if k == 8 else ()
        if k == 4 and turn % 4 == 0:
            value = rng.choice(a); params=(value,value)
        if k == 8 and turn % 3 == 0:
            a[0] = rng.choice([0,7,19,999999999]); params=(sum(map(int,str(a[0]))),)
        queries = [(l,r) for l in range(1,n+1) for r in range(l,n+1)]
        yield a,queries,params


def negative_checks(p,k):
    good = (p/'gen/example_00.in').read_text(); a,q,params=decode(k,good)
    header,body = good.split('\n',1)
    tokens=header.split()
    invalid=[header+'\n',good+'0\n']
    for index,value in [(0,'0'),(0,'200001'),(1,'0'),(1,'200001')]:
        bad=tokens[:]; bad[index]=value; invalid.append(' '.join(bad)+'\n'+body)
    low,high=(-10**9,10**9) if k<=5 else (0,10**6) if k==6 else (0,10**9)
    invalid += [encode(k,[low-1]+a[1:],q,params),encode(k,[high+1]+a[1:],q,params)]
    invalid += [encode(k,a,[(0,1)],params),encode(k,a,[(1,len(a)+1)],params),encode(k,a,[(2,1)],params)]
    if k in (3,8):
        limits=(-1,82) if k==8 else (0,1000000001)
        invalid += [encode(k,a,q,(x,)) for x in limits]
    if k==4:
        invalid += [encode(k,a,q,(1,0)),encode(k,a,q,(-1000000001,0)),encode(k,a,q,(0,1000000001))]
    for data in invalid:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode != 0,(p,'accepted invalid input',data)
    good_answer=(p/'out/example_00.out').read_text(); t=good_answer.split()
    with tempfile.TemporaryDirectory() as td:
        candidate=Path(td)/'candidate.out'
        variants=[(good_answer,True),('\n\t'+'  '.join(t)+'\n',True),(' '.join([str(int(t[0])+1)]+t[1:]),False),(' '.join(t[:-1]),False),(good_answer+'0\n',False),('-1\n',False),('abc\n',False)]
        for output,ok in variants:
            candidate.write_text(output)
            result=subprocess.run([str(p/'checker'),str(p/'in/example_00.in'),str(candidate),str(p/'out/example_00.out')],capture_output=True)
            assert (result.returncode==0)==ok,(p,'checker',output,result.stderr)
    return len(invalid)+len(variants)


def check(k,generate):
    p=ROOT/'custom'/f'dppsum{k+11:03}'; audit(p,k)
    problem=Problem(ROOT,p)
    if generate:
        problem.health_check(); problem.generate_params_h()
        with ThreadPoolExecutor(max_workers=4) as pool:
            list(pool.map(compile_source,[p/'sol/correct.cpp',p/'gen/cases.cpp',p/'verifier.cpp',p/'checker.cpp']))
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True)
    paths=sorted((p/'in').glob('*.in')); assert len(paths)==22
    max_size=0
    has_large_sum=False
    for path in paths:
        text=path.read_text(); a,queries,params=decode(k,text)
        max_size=max(max_size,len(a))
        expected=reference(k,a,queries,params)
        has_large_sum |= any(abs(value) > 2**31-1 for value in expected)
        actual=list(map(int,(p/'out'/(path.stem+'.out')).read_text().split()))
        assert actual==expected,(p,path,'reference')
        assert solve(p,text)==expected,(p,path,'solution')
    assert max_size==200000
    assert has_large_sum,(p,"missing 64-bit sum case")
    count=0
    for a,queries,params in small_cases(k):
        expected=brute(k,a,queries,params)
        assert reference(k,a,queries,params)==expected,(k,'reference',a,params)
        assert solve(p,encode(k,a,queries,params))==expected,(k,a,params)
        count+=1
    attacks=negative_checks(p,k)
    if generate:
        problem.ignore_warning=True; problem.write_hashes()
        problem.make_inputs(); problem.verify_inputs()
    problem.assert_hashes()
    print(f'dppsum{k+11:03}: 22 tests, {count} brute comparisons, {attacks} verifier/checker checks; hashes OK',flush=True)


def main():
    ap=argparse.ArgumentParser()
    ap.add_argument('--problem',choices=[f'dppsum{k+11:03}' for k in range(10)])
    ap.add_argument('--generate',action='store_true')
    args=ap.parse_args(); logging.basicConfig(level=logging.ERROR)
    for k in range(10):
        if args.problem is None or args.problem==f'dppsum{k+11:03}': check(k,args.generate)

if __name__=='__main__': main()
