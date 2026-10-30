"""Generate and independently audit DPPSUM021..030, without HTML/upload."""
import argparse
from bisect import bisect_left,bisect_right
from concurrent.futures import ThreadPoolExecutor
from itertools import product, accumulate
import logging
import os
from pathlib import Path
import random
import re
import shlex
import subprocess
import sys
import tempfile

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from problem import Problem
import toml

UPLOAD={'time_limit':0.25,'group':'03','classes':'C','types':['dp_prefix_sum','dp_sequence'],'allowed_languages':['PY3','CPP11','CPP14','CPP17','CPP20','JAVA8','C','PAS'],'partial':True}


def decode(code,text):
    tokens=iter(text.split())
    n,q=int(next(tokens)),int(next(tokens))
    k=int(next(tokens)) if code in (23,25) else None
    a=next(tokens) if code==24 else [int(next(tokens)) for _ in range(n)]
    queries=[(int(next(tokens)),int(next(tokens))) for _ in range(q)]
    assert len(a)==n
    return a,queries,k


def encode(code,a,queries,k=None):
    return f'{len(a)} {len(queries)}'+(f' {k}' if code in (23,25) else '')+'\n'+(a if code==24 else ' '.join(map(str,a)))+'\n'+''.join(f'{l} {r}\n' for l,r in queries)


def brute(code,a,queries,k):
    answers=[]
    for l,r in queries:
        b=a[l-1:r]
        if code==21: row=[sum(x for x in b if x%2==0),sum(x for x in b if x%2!=0)]
        elif code==22: row=[sum(x for x in b if x>0),sum(x for x in b if x<0)]
        elif code==23: row=[sum(x%k==0 for x in b),sum(x for x in b if x%k==0)]
        elif code==24: row=[b.count(c) for c in 'abc']
        elif code==25: row=[sum(x<k for x in b),sum(x==k for x in b),sum(x>k for x in b)]
        else:
            pairs=list(zip(b,b[1:]))
            if code==26: value=sum(x==y for x,y in pairs)
            elif code==27: value=sum(y>x for x,y in pairs)
            elif code==28: value=sum(abs(y-x) for x,y in pairs)
            elif code==29: value=sum((x-y)%2!=0 for x,y in pairs)
            elif code==30: value=sum(y-x for x,y in pairs if y>x)
            row=[value]
        answers.append(row)
    return answers


def reference(code,a,queries,k):
    if code>=26:
        # Edges indexed by their LEFT endpoint, unlike the C++ right-endpoint prefix.
        def edge(x,y):
            if code==26: return x==y
            if code==27: return y>x
            if code==28: return abs(y-x)
            if code==29: return (x-y)%2!=0
            return y-x if y>x else 0
        p=[0]+list(accumulate(edge(x,y) for x,y in zip(a,a[1:])))
        return [[p[r-1]-p[l-1]] for l,r in queries]
    groups=[]
    if code==21: tests=[lambda x:x%2==0,lambda x:x%2!=0]
    elif code==22: tests=[lambda x:x>0,lambda x:x<0]
    elif code==23: tests=[lambda x:x%k==0]
    elif code==24: tests=[lambda x,c=c:x==c for c in 'abc']
    elif code==25: tests=[lambda x:x<k,lambda x:x==k,lambda x:x>k]
    for test in tests:
        positions=[]; sums=[0]
        for i,x in enumerate(a,1):
            if test(x): positions.append(i); sums.append(sums[-1]+(x if code in (21,22,23) else 1))
        groups.append((positions,sums))
    answers=[]
    for l,r in queries:
        row=[]
        for positions,sums in groups:
            lo,hi=bisect_left(positions,l),bisect_right(positions,r)
            if code==23: row.extend([hi-lo,sums[hi]-sums[lo]])
            else: row.append(sums[hi]-sums[lo])
        answers.append(row)
    return answers


def flatten(rows): return [x for row in rows for x in row]


def compile_source(path):
    flags=shlex.split(os.environ.get('CXXFLAGS','-O2 -std=c++17 -Wall -Wextra -Werror'))
    subprocess.run([os.environ.get('CXX','g++'),*flags,'-I',str(ROOT/'common'),'-I',str(ROOT/'atcoder'),str(path),'-o',str(path.with_suffix(''))],check=True)


def solve(p,text):
    result=subprocess.run([str(p/'sol/correct')],input=text,text=True,capture_output=True,timeout=5)
    assert result.returncode==0,(p,result.stderr)
    return list(map(int,result.stdout.split()))


def audit(p,code):
    text=(p/'task.md').read_text()
    assert text.startswith(f'# PREFIX{code:03} — ')
    assert re.findall(r'^### (.+)$',text,re.M)==['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc','Sample Input 1','Sample Output 1','Sample Input 2','Sample Output 2','Giải thích']
    assert 'Subtask' not in text
    blocks=re.findall(r'```text\n(.*?)```',text,re.S); assert len(blocks)==4
    for i in range(2):
        assert blocks[2*i]==(p/'gen'/f'example_{i:02}.in').read_text()
        assert list(map(int,blocks[2*i+1].split()))==flatten(brute(code,*decode(code,blocks[2*i])))
    cfg=toml.load(p/'info.toml')
    assert cfg['title'].startswith(f'PREFIX{code:03} - ')
    assert cfg['upload']==UPLOAD
    sol=(p/'solution.md').read_text()
    assert sol.startswith(f'# PREFIX{code:03} — ')
    assert all(word not in sol.lower() for word in ('oracle','verifier','checker','benchmark','bộ sinh','kiểm thử'))
    assert not list(p.glob('*.html'))


def small_cases(code):
    for n in range(1,5):
        queries=[(l,r) for l in range(1,n+1) for r in range(l,n+1)]
        for a in product('abc' if code==24 else (-1,0,1),repeat=n):
            yield ''.join(a) if code==24 else list(a),queries,2 if code==23 else 0 if code==25 else None
    rng=random.Random(20261030+code)
    for _ in range(160):
        n=rng.randint(1,20)
        a=''.join(rng.choice('abc') for _ in range(n)) if code==24 else [rng.choice([-1000000000,-3,-1,0,1,2,1000000000,rng.randint(-20,20)]) for _ in range(n)]
        k=rng.choice([1,2,7,1000000000]) if code==23 else rng.choice([-1000000000,0,3,1000000000]) if code==25 else None
        queries=[(l,r) for l in range(1,n+1) for r in range(l,n+1)]
        yield a,queries,k


def negative_checks(p,code):
    good=(p/'gen/example_00.in').read_text();a,q,k=decode(code,good)
    header,body=good.split('\n',1);t=header.split()
    invalid=[header+'\n',good+'0\n']
    for index,value in ((0,'0'),(0,'200001'),(1,'0'),(1,'200001')):
        bad=t[:];bad[index]=value;invalid.append(' '.join(bad)+'\n'+body)
    if code==24:
        invalid += [encode(code,'d'+a[1:],q,k),good.replace('\n'+a+'\n','\n'+a+'a\n',1)]
    else:
        invalid += [encode(code,[-1000000001]+a[1:],q,k),encode(code,[1000000001]+a[1:],q,k)]
    invalid += [encode(code,a,[(0,1)],k),encode(code,a,[(1,len(a)+1)],k),encode(code,a,[(2,1)],k)]
    if code in (23,25): invalid += [encode(code,a,q,bad) for bad in ((0,1000000001) if code==23 else (-1000000001,1000000001))]
    for data in invalid:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(p,'accepted invalid',data)
    good_output=(p/'out/example_00.out').read_text();tokens=good_output.split()
    with tempfile.TemporaryDirectory() as td:
        candidate=Path(td)/'answer.out'
        variants=[(good_output,True),('\n\t'+'  '.join(tokens)+'\n',True),(' '.join([str(int(tokens[0])+1)]+tokens[1:]),False),(' '.join(tokens[:-1]),False),(good_output+'42\n',False),('abc\n',False)]
        for value,ok in variants:
            candidate.write_text(value)
            result=subprocess.run([str(p/'checker'),str(p/'in/example_00.in'),str(candidate),str(p/'out/example_00.out')],capture_output=True)
            assert (result.returncode==0)==ok,(p,value,result.stderr)
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
    large=False;maximum=False
    for path in paths:
        text=path.read_text();a,q,k=decode(code,text)
        expected=flatten(reference(code,a,q,k))
        large |= any(abs(x)>2**31-1 for x in expected)
        maximum |= len(a)==200000 and len(q)==200000
        assert list(map(int,(p/'out'/(path.stem+'.out')).read_text().split()))==expected,(p,path,'reference')
        assert solve(p,text)==expected,(p,path,'solution')
    assert maximum
    if code in (21,22,23,28,30): assert large,(p,'missing 64-bit case')
    count=0
    for a,q,k in small_cases(code):
        expected=flatten(brute(code,a,q,k))
        assert flatten(reference(code,a,q,k))==expected,(code,'reference',a,k)
        assert solve(p,encode(code,a,q,k))==expected,(code,a,k)
        count+=1
    attacks=negative_checks(p,code)
    if generate:
        problem.ignore_warning=True;problem.write_hashes()
        problem.make_inputs();problem.verify_inputs()
    problem.assert_hashes()
    print(f'dppsum{code:03}: 22 tests, {count} brute comparisons, {attacks} verifier/checker checks; hashes OK',flush=True)


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--problem',choices=[f'dppsum{code:03}' for code in range(21,31)]);ap.add_argument('--generate',action='store_true')
    args=ap.parse_args();logging.basicConfig(level=logging.ERROR)
    for code in range(21,31):
        if args.problem is None or args.problem==f'dppsum{code:03}':check(code,args.generate)

if __name__=='__main__':main()
