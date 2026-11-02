"""Generate/audit 07x rectangle queries without HTML or uploads."""
import argparse
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
    tokens=iter(text.split());n,m,q=int(next(tokens)),int(next(tokens)),int(next(tokens))
    params=(int(next(tokens)),) if code==74 else (int(next(tokens)),int(next(tokens))) if code==75 else ()
    a=[[int(next(tokens)) for _ in range(m)] for _ in range(n)]
    queries=[tuple(int(next(tokens)) for _ in range(4)) for _ in range(q)]
    return a,queries,params


def encode(a,queries,params=()):
    return ' '.join(map(str,(len(a),len(a[0]),len(queries))+tuple(params)))+'\n'+'\n'.join(' '.join(map(str,row)) for row in a)+'\n'+''.join(' '.join(map(str,q))+'\n' for q in queries)


def value(code,x,params):
    if code==70:return x
    if code==71:return int(x%2==0)
    if code==72:return int(x>0)
    if code==73:return int(x<0)
    if code==74:return int(x%params[0]==0)
    if code==75:return int(params[0]<=x<=params[1])
    if code==76:return int(x>=0 and math.isqrt(x)**2==x)
    if code==77:return int(x>=2 and all(x%d for d in range(2,math.isqrt(x)+1)))
    if code==78:return int(str(x)==str(x)[::-1])
    if code==79:return int('7' in str(x))
    raise ValueError(code)


def brute(code,a,queries,params):
    b=[[value(code,x,params) for x in row] for row in a]
    return [sum(sum(row[y1-1:y2]) for row in b[x1-1:x2]) for x1,y1,x2,y2 in queries]


PRIMES=None

def reference(code,a,queries,params):
    # Offline row sweep: keep one column-prefix vector instead of a 2D prefix table.
    global PRIMES
    if code==77 and PRIMES is None:
        PRIMES=bytearray(b'\1')*1000001;PRIMES[:2]=b'\0\0'
        for d in range(2,1001):
            if PRIMES[d]:PRIMES[d*d::d]=bytes((1000000-d*d)//d+1)
    n,m=len(a),len(a[0]);events=[[] for _ in range(n+1)];answers=[0]*len(queries)
    for index,(x1,y1,x2,y2) in enumerate(queries):
        events[x2].append((index,y1,y2,1))
        events[x1-1].append((index,y1,y2,-1))
    columns=[0]*(m+1)
    for row in range(n+1):
        if row:
            total=0
            for j,x in enumerate(a[row-1],1):
                total+=PRIMES[x] if code==77 else value(code,x,params)
                columns[j]+=total
        for index,y1,y2,sign in events[row]:answers[index]+=sign*(columns[y2]-columns[y1-1])
    return answers


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


def all_rectangles(n,m):return [(x1,y1,x2,y2) for x1 in range(1,n+1) for x2 in range(x1,n+1) for y1 in range(1,m+1) for y2 in range(y1,m+1)]


def small_cases(code):
    rng=random.Random(20261102+code)
    alphabet=(0,1,2) if code>=77 else (-1,0,1)
    if code==78:alphabet=(0,10,11)
    if code==79:alphabet=(0,7,77)
    params=(2,) if code==74 else (-1,0) if code==75 else ()
    for n,m in [(1,1),(1,2),(2,1),(2,2)]:
        for raw in product(alphabet,repeat=n*m):
            a=[list(raw[i*m:(i+1)*m]) for i in range(n)]
            yield a,all_rectangles(n,m),params
    for turn in range(160):
        n,m=rng.randint(1,7),rng.randint(1,7)
        low,high=(0,1000000) if code==77 else (0,1000000000) if code>=78 else (-1000000000,1000000000)
        pool=[0,1,2,3,4,7,11,17,25,77,121,1001,999983,999999,1000000]
        if code!=77:pool += [999950883,999950884,999950885,999999999,1000000000]
        if low<0:pool += [-1,-2,-3,-1000000000]
        a=[[rng.choice(pool+[rng.randint(low,high)]) for _ in range(m)] for _ in range(n)]
        params=(rng.choice([1,2,7,1000000000]),) if code==74 else tuple(sorted([rng.randint(low,high),rng.randint(low,high)])) if code==75 else ()
        if code==75 and turn%3==0:params=(rng.choice(rng.choice(a)),)*2
        yield a,all_rectangles(n,m),params


def negative_checks(p,code):
    good=(p/'gen/example_00.in').read_text();a,queries,params=decode(code,good)
    header,body=good.split('\n',1);t=header.split();invalid=[header+'\n',good+'0\n']
    for index,badvalue in [(0,0),(0,501),(1,0),(1,501),(2,0),(2,200001)]:
        bad=t[:];bad[index]=str(badvalue);invalid.append(' '.join(bad)+'\n'+body)
    low,high=(0,1000000) if code==77 else (0,1000000000) if code>=78 else (-1000000000,1000000000)
    for badvalue in (low-1,high+1):
        bad=[row[:] for row in a];bad[0][0]=badvalue;invalid.append(encode(bad,queries,params))
    n,m=len(a),len(a[0])
    for query in [(0,1,1,1),(1,0,1,1),(1,1,n+1,1),(1,1,1,m+1),(2,1,1,1),(1,2,1,1)]:invalid.append(encode(a,[query],params))
    if code==74:invalid += [encode(a,queries,(d,)) for d in (0,1000000001)]
    if code==75:invalid += [encode(a,queries,pair) for pair in [(1,0),(-1000000001,0),(0,1000000001)]]
    for data in invalid:
        r=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert r.returncode!=0,(p,'accepted invalid',data)
    attempts=0
    with tempfile.TemporaryDirectory() as td:
        candidate=Path(td)/'candidate.out'
        for example in (0,1):
            answer=(p/'out'/f'example_{example:02}.out').read_text();tokens=answer.split()
            variants=[(answer,True),('\n\t'+'  '.join(tokens)+'\n',True),(' '.join([str(int(tokens[0])+1)]+tokens[1:]),False),(' '.join(tokens[:-1]),False),(answer+'0\n',False),('abc\n',False)]
            for output,ok in variants:
                candidate.write_text(output)
                r=subprocess.run([str(p/'checker'),str(p/'in'/f'example_{example:02}.in'),str(candidate),str(p/'out'/f'example_{example:02}.out')],capture_output=True)
                assert (r.returncode==0)==ok,(p,example,output,r.stderr)
                attempts+=1
    return len(invalid)+attempts


def check(code,generate):
    p=ROOT/'custom'/f'dppsum{code:03}';audit(p,code)
    problem=Problem(ROOT,p)
    if generate:
        problem.health_check();problem.generate_params_h()
        with ThreadPoolExecutor(max_workers=4) as pool:
            list(pool.map(compile_source,[p/'sol/correct.cpp',p/'gen/cases.cpp',p/'verifier.cpp',p/'checker.cpp']))
        problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
    paths=sorted((p/'in').glob('*.in'));assert len(paths)==22
    coverage=dict.fromkeys(('row','column','nonsquare','maximum','full','single','inner','zero','positive'),False)
    if code==70:coverage.update(large_positive=False,large_negative=False)
    for path in paths:
        text=path.read_text();a,queries,params=decode(code,text);n,m=len(a),len(a[0])
        expected=reference(code,a,queries,params)
        assert list(map(int,(p/'out'/(path.stem+'.out')).read_text().split()))==expected,(p,path,'reference')
        assert solve(p,text)==expected,(p,path,'solution')
        coverage['row']|=n==1 and m>1;coverage['column']|=m==1 and n>1;coverage['nonsquare']|=n!=m
        coverage['maximum']|=n==500 and m==500 and len(queries)==200000
        coverage['full']|=(1,1,n,m) in queries
        coverage['single']|=any(x1==x2 and y1==y2 for x1,y1,x2,y2 in queries)
        coverage['inner']|=any(x1>1 and y1>1 for x1,y1,x2,y2 in queries)
        coverage['zero']|=0 in expected;coverage['positive']|=any(x>0 for x in expected)
        if code==70:
            coverage['large_positive']|=any(x>2**31-1 for x in expected)
            coverage['large_negative']|=any(x<-(2**31) for x in expected)
    assert all(coverage.values()),(p,coverage)
    count=0
    for a,queries,params in small_cases(code):
        expected=brute(code,a,queries,params)
        assert reference(code,a,queries,params)==expected,(code,'reference',a,params)
        assert solve(p,encode(a,queries,params))==expected,(code,a,params)
        count+=1
    attacks=negative_checks(p,code)
    if generate:
        problem.ignore_warning=True;problem.write_hashes()
        problem.make_inputs();problem.verify_inputs()
    problem.assert_hashes()
    print(f'dppsum{code:03}: 22 tests, {count} brute comparisons, {attacks} verifier/checker checks; hashes OK',flush=True)


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--problem',choices=[f'dppsum{code:03}' for code in range(70,80)]);ap.add_argument('--generate',action='store_true')
    args=ap.parse_args();logging.basicConfig(level=logging.ERROR)
    for code in range(70,80):
        if args.problem is None or args.problem==f'dppsum{code:03}':check(code,args.generate)

if __name__=='__main__':main()
