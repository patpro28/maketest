"""Generate DPPSUM031..040 and check fixed-length counts independently."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from itertools import product
import json
import logging
import math
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile

# Only repository mechanics and the common upload schema are shared.
sys.path.insert(0,str(Path(__file__).resolve().parent))
from check_levels23 import ROOT,UPLOAD,compile_source
sys.path.insert(0,str(ROOT))
from problem import Problem
import toml


def decode(code,text):
    header,body=text.split('\n',1)
    values=list(map(int,header.split()));n,k=values[:2]
    a=list(map(int,body.split()));assert len(a)==n
    return a,k,tuple(values[2:])


def encode(code,a,k,params=()):
    return ' '.join(map(str,(len(a),k)+tuple(params)))+'\n'+' '.join(map(str,a))+'\n'


def matches(code,total,params):
    if code==31:return total==params[0]
    if code==32:return total>params[0]
    if code==33:return total<params[0]
    if code==34:return params[0]<=total<=params[1]
    if code==35:return total%params[0]==0
    if code==36:return total%params[0]==params[1]
    if code==37:return total%2==0
    if code==38:return sum(map(int,str(total)))==params[0]
    if code==39:return total>=0 and math.isqrt(total)**2==total
    if code==40:return str(total)==str(total)[::-1]
    raise ValueError(code)


def brute(code,a,k,params):
    return sum(matches(code,sum(a[left:left+k]),params) for left in range(len(a)-k+1))


def reference(code,a,k,params):
    # Rolling sum; the official C++ solution uses a prefix array instead.
    total=sum(a[:k]);answer=int(matches(code,total,params))
    for right in range(k,len(a)):
        total+=a[right]-a[right-k]
        answer+=matches(code,total,params)
    return answer


def solve(p,text):
    r=subprocess.run([str(p/'sol/correct')],input=text,text=True,capture_output=True,timeout=5)
    assert r.returncode==0,(p,r.stderr)
    t=r.stdout.split();assert len(t)==1,(p,r.stdout)
    return int(t[0])


def audit(p,code):
    text=(p/'task.md').read_text()
    assert text.startswith(f'# PREFIX{code:03} — ')
    assert re.findall(r'^### (.+)$',text,re.M)==['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc','Sample Input 1','Sample Output 1','Sample Input 2','Sample Output 2','Giải thích']
    assert 'Subtask' not in text
    blocks=re.findall(r'```text\n(.*?)```',text,re.S);assert len(blocks)==4
    for i in range(2):
        assert blocks[2*i]==(p/'gen'/f'example_{i:02}.in').read_text()
        assert int(blocks[2*i+1])==brute(code,*decode(code,blocks[2*i]))
    cfg=toml.load(p/'info.toml');assert cfg['upload']==UPLOAD
    assert cfg['title'].startswith(f'PREFIX{code:03} - ')
    sol=(p/'solution.md').read_text()
    assert not re.search(r'(?m)^ {0,3}#(?:[ \t]|$)', sol)
    assert all(word not in sol.lower() for word in ('oracle','verifier','checker','benchmark','bộ sinh','kiểm thử'))
    assert not list(p.glob('*.html'))


def choose_params(code,total,rng):
    if code in (31,32,33):return (total+rng.choice([-1,0,1]),)
    if code==34:return (total-rng.randint(0,2),total+rng.randint(0,2))
    if code==35:return (rng.choice([1,2,3,7,1000000000]),)
    if code==36:
        m=rng.choice([1,2,3,7,1000000000]);return m,rng.choice([total%m,rng.randrange(m)])
    if code==38:return (rng.choice([0,135,sum(map(int,str(total)))]),)
    return ()


def small_cases(code):
    rng=random.Random(20261102+code)
    for n in range(1,5):
        for raw in product((0,1,2) if code in (36,38,40) else (-1,0,1),repeat=n):
            a=list(raw)
            for k in range(1,n+1):yield a,k,choose_params(code,sum(a[:k]),rng)
    for _ in range(160):
        n=rng.randint(1,20);k=rng.randint(1,n)
        low=0 if code in (36,38,40) else -1000000000
        pool=[0,1,2,4,9,11,99,121,999999999,1000000000]
        if low<0:pool += [-1,-4,-1000000000]
        a=[rng.choice(pool+[rng.randint(low,1000000000)]) for _ in range(n)]
        yield a,k,choose_params(code,sum(a[:k]),rng)


def negative_checks(p,code):
    good=(p/'gen/example_00.in').read_text();a,k,params=decode(code,good)
    header,body=good.split('\n',1);t=header.split()
    invalid=[header+'\n',good+'0\n']
    for idx,val in [(0,0),(0,200001),(1,0),(1,len(a)+1)]:
        bad=t[:];bad[idx]=str(val);invalid.append(' '.join(bad)+'\n'+body)
    low=0 if code in (36,38,40) else -1000000000
    invalid += [encode(code,[low-1]+a[1:],k,params),encode(code,[1000000001]+a[1:],k,params)]
    if code in (31,32,33):invalid += [encode(code,a,k,(x,)) for x in (-200000000000001,200000000000001)]
    if code==34:invalid += [encode(code,a,k,x) for x in [(1,0),(-200000000000001,0),(0,200000000000001)]]
    if code==35:invalid += [encode(code,a,k,(x,)) for x in (0,1000000001)]
    if code==36:invalid += [encode(code,a,k,x) for x in [(0,0),(1000000001,0),(4,-1),(4,4)]]
    if code==38:invalid += [encode(code,a,k,(x,)) for x in (-1,136)]
    for data in invalid:
        r=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert r.returncode!=0,(p,'accepted bad input',data)
    answer=int((p/'out/example_00.out').read_text())
    with tempfile.TemporaryDirectory() as td:
        candidate=Path(td)/'candidate.out'
        for output,ok in [(f'{answer}\n',True),(f' \n\t{answer}  \n',True),(f'{answer+1}\n',False),('-1\n',False),('',False),(f'{answer}\n0\n',False),('abc\n',False)]:
            candidate.write_text(output)
            r=subprocess.run([str(p/'checker'),str(p/'in/example_00.in'),str(candidate),str(p/'out/example_00.out')],capture_output=True)
            assert (r.returncode==0)==ok,(p,output,r.stderr)
    return len(invalid)+7


def check(code,generate):
    p=ROOT/'custom'/f'dppsum{code:03}';audit(p,code)
    problem=Problem(ROOT,p)
    if generate:
        problem.health_check();problem.generate_params_h()
        with ThreadPoolExecutor(max_workers=4) as pool:
            list(pool.map(compile_source,[p/'sol/correct.cpp',p/'gen/cases.cpp',p/'verifier.cpp',p/'checker.cpp']))
        problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
    paths=sorted((p/'in').glob('*.in'));assert len(paths)==22
    has_one=has_all=has_max=large=False
    for path in paths:
        text=path.read_text();a,k,params=decode(code,text)
        expected=reference(code,a,k,params)
        assert int((p/'out'/(path.stem+'.out')).read_text())==expected,(p,path,'reference')
        assert solve(p,text)==expected,(p,path,'solution')
        has_one|=k==1;has_all|=k==len(a);has_max|=len(a)==200000
        # Track a window sum outside 32-bit range, regardless of its predicate result.
        large|=abs(sum(a[:k]))>2**31-1
    assert has_one and has_all and has_max and large,p
    count=0
    for a,k,params in small_cases(code):
        expected=brute(code,a,k,params)
        assert reference(code,a,k,params)==expected,(code,'reference',a,k,params)
        assert solve(p,encode(code,a,k,params))==expected,(code,a,k,params)
        count+=1
    attacks=negative_checks(p,code)
    if generate:
        problem.ignore_warning=True;problem.write_hashes()
        problem.make_inputs();problem.verify_inputs()
    problem.assert_hashes()
    print(f'dppsum{code:03}: 22 tests, {count} brute comparisons, {attacks} verifier/checker checks; hashes OK',flush=True)


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--problem',choices=[f'dppsum{code:03}' for code in range(31,41)]);ap.add_argument('--generate',action='store_true')
    args=ap.parse_args();logging.basicConfig(level=logging.ERROR)
    for code in range(31,41):
        if args.problem is None or args.problem==f'dppsum{code:03}':check(code,args.generate)

if __name__=='__main__':main()
