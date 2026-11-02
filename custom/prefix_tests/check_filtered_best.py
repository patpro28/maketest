"""Generate/audit 06x: fixed-length sum maximization with a count filter."""
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
    header,body=text.split('\n',1);t=list(map(int,header.split()));n,k,required=t[:3]
    a=list(map(int,body.split()));assert len(a)==n
    return a,k,required,tuple(t[3:])


def encode(a,k,required,params=()):return ' '.join(map(str,(len(a),k,required)+tuple(params)))+'\n'+' '.join(map(str,a))+'\n'


def predicate(code,x,params):
    if code==60:return x%2==0
    if code==61:return x>0
    if code==62:return x<0
    if code==63:return x%params[0]==0
    if code==64:return params[0]<=x<=params[1]
    if code==65:return x>=0 and math.isqrt(x)**2==x
    if code==66:return x>=2 and all(x%d for d in range(2,math.isqrt(x)+1))
    if code==67:return str(x)==str(x)[::-1]
    if code==68:return '7' in str(x)
    if code==69:return sum(map(int,str(x)))==params[0]
    raise ValueError(code)


def brute(code,a,k,required,params):
    candidates=[]
    for left in range(len(a)-k+1):
        segment=a[left:left+k]
        if sum(predicate(code,x,params) for x in segment)>=required:candidates.append((sum(segment),-left-1))
    if not candidates:return None
    best,negative=max(candidates)
    return [best,-negative]


PRIMES=None

def reference(code,a,k,required,params):
    global PRIMES
    if code==66 and PRIMES is None:
        PRIMES=bytearray(b'\1')*1000001;PRIMES[:2]=b'\0\0'
        for d in range(2,1001):
            if PRIMES[d]:PRIMES[d*d::d]=bytes((1000000-d*d)//d+1)
    positions=[i for i,x in enumerate(a,1) if (PRIMES[x] if code==66 else predicate(code,x,params))]
    # Rolling total, binary-search count, lexicographic ranking of feasible windows.
    total=sum(a[:k]);candidates=[];unrestricted=None
    for left in range(1,len(a)-k+2):
        if left>1:total+=a[left+k-2]-a[left-2]
        unrestricted=total if unrestricted is None else max(unrestricted,total)
        count=bisect_right(positions,left+k-1)-bisect_left(positions,left)
        if count>=required:candidates.append((-total,left))
    if not candidates:return None,dict(ties=0,unrestricted=unrestricted)
    negative,first=min(candidates);ties=sum(value==negative for value,left in candidates)
    return [-negative,first],dict(ties=ties,unrestricted=unrestricted)


def parse_output(text):
    tokens=text.split()
    if tokens==['NONE']:return None
    assert len(tokens)==2,text
    return list(map(int,tokens))


def solve(p,text):
    r=subprocess.run([str(p/'sol/correct')],input=text,text=True,capture_output=True,timeout=5)
    assert r.returncode==0,(p,r.stderr)
    return parse_output(r.stdout)


def audit(p,code):
    text=(p/'task.md').read_text()
    assert text.startswith(f'# PREFIX{code:03} — ')
    headings=['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc']
    for i in range(1,4):headings.extend([f'Sample Input {i}',f'Sample Output {i}'])
    headings.append('Giải thích')
    assert re.findall(r'^### (.+)$',text,re.M)==headings
    assert 'Subtask' not in text
    blocks=re.findall(r'```text\n(.*?)```',text,re.S);assert len(blocks)==6
    for i in range(3):
        assert blocks[2*i]==(p/'gen'/f'example_{i:02}.in').read_text()
        assert parse_output(blocks[2*i+1])==brute(code,*decode(code,blocks[2*i]))
    cfg=toml.load(p/'info.toml');assert cfg['upload']==UPLOAD
    assert cfg['title'].startswith(f'PREFIX{code:03} - ')
    sol=(p/'solution.md').read_text()
    assert not re.search(r'(?m)^ {0,3}#(?:[ \t]|$)', sol)
    assert all(word not in sol.lower() for word in ('oracle','verifier','checker','benchmark','bộ sinh','kiểm thử'))
    assert not list(p.glob('*.html'))


def small_cases(code):
    rng=random.Random(20261102+code)
    alphabet=(0,1,2) if code>=66 else (-1,0,1)
    if code==67:alphabet=(0,10,11)
    if code==68:alphabet=(0,7,77)
    params=(2,) if code==63 else (-1,0) if code==64 else (1,) if code==69 else ()
    for n in range(1,4):
        for raw in product(alphabet,repeat=n):
            for k in range(1,n+1):
                for required in range(k+1):yield list(raw),k,required,params
    for turn in range(160):
        n=rng.randint(1,18);k=rng.randint(1,n);required=rng.randint(0,k)
        low,high=(0,1000000) if code==66 else (0,1000000000) if code>=67 else (-1000000000,1000000000)
        pool=[0,1,2,3,4,7,11,17,25,77,121,1001,999983,999999,1000000]
        if code!=66:pool += [999950883,999950884,999950885,999999999,1000000000]
        if low<0:pool += [-1,-2,-3,-1000000000]
        a=[rng.choice(pool+[rng.randint(low,high)]) for _ in range(n)]
        params=(rng.choice([1,2,7,1000000000]),) if code==63 else tuple(sorted([rng.randint(low,high),rng.randint(low,high)])) if code==64 else (rng.choice([0,1,7,81]),) if code==69 else ()
        if code==64 and turn%3==0:params=(rng.choice(a),)*2
        yield a,k,required,params


def negative_checks(p,code):
    good=(p/'gen/example_00.in').read_text();a,k,required,params=decode(code,good)
    header,body=good.split('\n',1);t=header.split();invalid=[header+'\n',good+'0\n']
    for index,value in [(0,0),(0,200001),(1,0),(1,len(a)+1),(2,-1),(2,k+1)]:
        bad=t[:];bad[index]=str(value);invalid.append(' '.join(bad)+'\n'+body)
    low,high=(0,1000000) if code==66 else (0,1000000000) if code>=67 else (-1000000000,1000000000)
    invalid += [encode([low-1]+a[1:],k,required,params),encode([high+1]+a[1:],k,required,params)]
    if code==63:invalid += [encode(a,k,required,(m,)) for m in (0,1000000001)]
    if code==64:invalid += [encode(a,k,required,pair) for pair in [(1,0),(-1000000001,0),(0,1000000001)]]
    if code==69:invalid += [encode(a,k,required,(h,)) for h in (-1,82)]
    for data in invalid:
        r=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert r.returncode!=0,(p,'accepted invalid',data)
    attempts=0
    with tempfile.TemporaryDirectory() as td:
        candidate=Path(td)/'candidate.out'
        for example in (0,1,2):
            answer=(p/'out'/f'example_{example:02}.out').read_text();tokens=answer.split()
            variants=[(answer,True),('\n\t'+'  '.join(tokens)+'\n',True),('',False),(answer+'0\n',False),('abc\n',False)]
            if tokens==['NONE']:variants += [('0 1\n',False),('none\n',False),('-1 1\n',False)]
            else:
                variants.append(('NONE\n',False));variants.append((tokens[0]+'\n',False))
                for index in range(2):
                    wrong=tokens[:];wrong[index]=str(int(wrong[index])+1);variants.append((' '.join(wrong),False))
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
    paths=sorted((p/'in').glob('*.in'));assert len(paths)==23
    coverage=dict.fromkeys(('k1','kn','kn1','maximum','t0','tk','feasible','none','ties','filter_matters','large_positive'),False)
    if code<66:coverage['large_negative']=False
    for path in paths:
        text=path.read_text();a,k,required,params=decode(code,text)
        expected,details=reference(code,a,k,required,params)
        assert parse_output((p/'out'/(path.stem+'.out')).read_text())==expected,(p,path,'reference')
        assert solve(p,text)==expected,(p,path,'solution')
        coverage['k1']|=k==1;coverage['kn']|=k==len(a);coverage['kn1']|=len(a)>1 and k==len(a)-1
        coverage['maximum']|=len(a)==200000;coverage['t0']|=required==0;coverage['tk']|=required==k
        coverage['none']|=expected is None
        if expected is not None:
            coverage['feasible']=True;coverage['ties']|=details['ties']>1
            coverage['filter_matters']|=expected[0]<details['unrestricted']
            coverage['large_positive']|=expected[0]>2**31-1
            if code<66:coverage['large_negative']|=expected[0]<-(2**31)
    assert all(coverage.values()),(p,coverage)
    count=0
    for a,k,required,params in small_cases(code):
        expected=brute(code,a,k,required,params)
        assert reference(code,a,k,required,params)[0]==expected,(code,'reference',a,k,required,params)
        assert solve(p,encode(a,k,required,params))==expected,(code,a,k,required,params)
        count+=1
    attacks=negative_checks(p,code)
    if generate:
        problem.ignore_warning=True;problem.write_hashes()
        problem.make_inputs();problem.verify_inputs()
    problem.assert_hashes()
    print(f'dppsum{code:03}: 23 tests, {count} brute comparisons, {attacks} verifier/checker checks; hashes OK',flush=True)


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--problem',choices=[f'dppsum{code:03}' for code in range(60,70)]);ap.add_argument('--generate',action='store_true')
    args=ap.parse_args();logging.basicConfig(level=logging.ERROR)
    for code in range(60,70):
        if args.problem is None or args.problem==f'dppsum{code:03}':check(code,args.generate)

if __name__=='__main__':main()
