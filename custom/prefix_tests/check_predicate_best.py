"""Generate and audit the 05x fixed-length predicate-count maximization group."""
import argparse
from bisect import bisect_left,bisect_right
from concurrent.futures import ThreadPoolExecutor
from itertools import product
import logging
import math
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile

sys.path.insert(0,str(Path(__file__).resolve().parent))
from check_levels23 import ROOT,UPLOAD,compile_source
sys.path.insert(0,str(ROOT))
from problem import Problem
import toml


def decode(code,text):
    header,body=text.split('\n',1);t=list(map(int,header.split()));n,k=t[:2]
    a=list(map(int,body.split()));assert len(a)==n
    return a,k,tuple(t[2:])


def encode(a,k,params=()):return ' '.join(map(str,(len(a),k)+tuple(params)))+'\n'+' '.join(map(str,a))+'\n'


def predicate(code,x,params):
    if code==51:return x%2==0
    if code==52:return x>0
    if code==53:return x<0
    if code==54:return x%params[0]==0
    if code==55:return params[0]<=x<=params[1]
    if code==56:return x>=0 and math.isqrt(x)**2==x
    if code==57:return x>=2 and all(x%d for d in range(2,math.isqrt(x)+1))
    if code==58:return str(x)==str(x)[::-1]
    if code==59:return '7' in str(x)
    raise ValueError(code)


def brute(code,a,k,params):
    counts=[sum(predicate(code,x,params) for x in a[left:left+k]) for left in range(len(a)-k+1)]
    best=max(counts);starts=[i+1 for i,count in enumerate(counts) if count==best]
    return [best,starts[0]]


PRIMES=None

def reference(code,a,k,params):
    global PRIMES
    if code==57 and PRIMES is None:
        PRIMES=bytearray(b'\1')*1000001;PRIMES[:2]=b'\0\0'
        for d in range(2,1001):
            if PRIMES[d]:PRIMES[d*d::d]=bytes((1000000-d*d)//d+1)
    positions=[i for i,x in enumerate(a,1) if (PRIMES[x] if code==57 else predicate(code,x,params))]
    # Binary searches over marked positions, then lexicographic choice of (-count,start).
    ranked=[(-(bisect_right(positions,left+k-1)-bisect_left(positions,left)),left) for left in range(1,len(a)-k+2)]
    negative,first=min(ranked)
    count=-negative;ties=sum(value==negative for value,left in ranked)
    return [count,first],ties


def solve(p,text):
    r=subprocess.run([str(p/'sol/correct')],input=text,text=True,capture_output=True,timeout=5)
    assert r.returncode==0,(p,r.stderr)
    return list(map(int,r.stdout.split()))


def audit(p,code):
    text=(p/'task.md').read_text()
    assert text.startswith(f'# PREFIX{code:03} — ')
    assert re.findall(r'^### (.+)$',text,re.M)==['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc','Sample Input 1','Sample Output 1','Sample Input 2','Sample Output 2','Giải thích']
    assert 'Subtask' not in text
    blocks=re.findall(r'```text\n(.*?)```',text,re.S);assert len(blocks)==4
    for i in range(2):
        assert blocks[2*i]==(p/'gen'/f'example_{i:02}.in').read_text()
        assert list(map(int,blocks[2*i+1].split()))==brute(code,*decode(code,blocks[2*i]))
    cfg=toml.load(p/'info.toml');assert cfg['upload']==UPLOAD
    assert cfg['title'].startswith(f'PREFIX{code:03} - ')
    sol=(p/'solution.md').read_text()
    assert not re.search(r'(?m)^ {0,3}#(?:[ \t]|$)', sol)
    assert all(word not in sol.lower() for word in ('oracle','verifier','checker','benchmark','bộ sinh','kiểm thử'))
    assert not list(p.glob('*.html'))


def small_cases(code):
    rng=random.Random(20261102+code)
    alphabet=(0,1,2) if code>=57 else (-1,0,1)
    params=(2,) if code==54 else (-1,0) if code==55 else ()
    for n in range(1,5):
        for raw in product(alphabet,repeat=n):
            for k in range(1,n+1):yield list(raw),k,params
    for turn in range(160):
        n=rng.randint(1,20);k=rng.randint(1,n)
        low,high=(0,1000000) if code==57 else (0,1000000000) if code>=58 else (-1000000000,1000000000)
        pool=[0,1,2,3,4,7,11,17,25,77,121,1001,999983,999999,1000000]
        if code!=57:pool += [999950883,999950884,999950885,999999999,1000000000]
        if low<0:pool += [-1,-2,-3,-1000000000]
        a=[rng.choice(pool+[rng.randint(low,high)]) for _ in range(n)]
        params=(rng.choice([1,2,7,1000000000]),) if code==54 else tuple(sorted([rng.randint(low,high),rng.randint(low,high)])) if code==55 else ()
        if code==55 and turn%3==0:params=(rng.choice(a),)*2
        yield a,k,params


def negative_checks(p,code):
    good=(p/'gen/example_00.in').read_text();a,k,params=decode(code,good)
    header,body=good.split('\n',1);t=header.split();invalid=[header+'\n',good+'0\n']
    for index,value in [(0,0),(0,200001),(1,0),(1,len(a)+1)]:
        bad=t[:];bad[index]=str(value);invalid.append(' '.join(bad)+'\n'+body)
    low,high=(0,1000000) if code==57 else (0,1000000000) if code>=58 else (-1000000000,1000000000)
    invalid += [encode([low-1]+a[1:],k,params),encode([high+1]+a[1:],k,params)]
    if code==54:invalid += [encode(a,k,(m,)) for m in (0,1000000001)]
    if code==55:invalid += [encode(a,k,pair) for pair in [(1,0),(-1000000001,0),(0,1000000001)]]
    for data in invalid:
        r=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert r.returncode!=0,(p,'accepted invalid',data)
    tokens=(p/'out/example_00.out').read_text().split()
    variants=[(' '.join(tokens)+'\n',True),('\n\t'+'  '.join(tokens)+'\n',True),('',False),(' '.join(tokens[:-1]),False),(' '.join(tokens)+'\n0\n',False),('abc\n',False)]
    for index in range(2):
        wrong=tokens[:];wrong[index]=str(int(wrong[index])+1);variants.append((' '.join(wrong),False))
    with tempfile.TemporaryDirectory() as td:
        candidate=Path(td)/'candidate.out'
        for output,ok in variants:
            candidate.write_text(output)
            r=subprocess.run([str(p/'checker'),str(p/'in/example_00.in'),str(candidate),str(p/'out/example_00.out')],capture_output=True)
            assert (r.returncode==0)==ok,(p,output,r.stderr)
    return len(invalid)+len(variants)


def check(code,generate):
    p=ROOT/'custom'/f'dppsum{code:03}';audit(p,code)
    problem=Problem(ROOT,p)
    if generate:
        problem.health_check();problem.generate_params_h()
        with ThreadPoolExecutor(max_workers=4) as pool:
            list(pool.map(compile_source,[p/'sol/correct.cpp',p/'gen/cases.cpp',p/'verifier.cpp',p/'checker.cpp']))
        problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
    paths=sorted((p/'in').glob('*.in'));assert len(paths)==22
    coverage=dict.fromkeys(('k1','kn','kn1','maximum','zero','ties','unique_first','unique_last'),False)
    for path in paths:
        text=path.read_text();a,k,params=decode(code,text)
        expected,ties=reference(code,a,k,params)
        assert list(map(int,(p/'out'/(path.stem+'.out')).read_text().split()))==expected,(p,path,'reference')
        assert solve(p,text)==expected,(p,path,'solution')
        coverage['k1']|=k==1;coverage['kn']|=k==len(a);coverage['kn1']|=len(a)>1 and k==len(a)-1
        coverage['maximum']|=len(a)==200000
        coverage['zero']|=expected==[0,1]
        coverage['ties']|=ties>1
        coverage['unique_first']|=ties==1 and expected[1]==1 and len(a)>k
        coverage['unique_last']|=ties==1 and expected[1]==len(a)-k+1 and len(a)>k
    assert all(coverage.values()),(p,coverage)
    count=0
    for a,k,params in small_cases(code):
        expected=brute(code,a,k,params)
        assert reference(code,a,k,params)[0]==expected,(code,'reference',a,k,params)
        assert solve(p,encode(a,k,params))==expected,(code,a,k,params)
        count+=1
    attacks=negative_checks(p,code)
    if generate:
        problem.ignore_warning=True;problem.write_hashes()
        problem.make_inputs();problem.verify_inputs()
    problem.assert_hashes()
    print(f'dppsum{code:03}: 22 tests, {count} brute comparisons, {attacks} verifier/checker checks; hashes OK',flush=True)


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--problem',choices=[f'dppsum{code:03}' for code in range(51,60)]);ap.add_argument('--generate',action='store_true')
    args=ap.parse_args();logging.basicConfig(level=logging.ERROR)
    for code in range(51,60):
        if args.problem is None or args.problem==f'dppsum{code:03}':check(code,args.generate)

if __name__=='__main__':main()
