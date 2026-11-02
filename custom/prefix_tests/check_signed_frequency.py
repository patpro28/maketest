"""Generate/audit 09x signed prefix sums plus frequency tables."""
import argparse
from bisect import bisect_left,bisect_right
from collections import defaultdict
from concurrent.futures import ThreadPoolExecutor
from itertools import accumulate,product
import logging
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
    header,body=text.split('\n',1);t=list(map(int,header.split()));n=t[0]
    a=list(map(int,body.split()));assert len(a)==n
    return a,tuple(t[1:])


def encode(a,params):return ' '.join(map(str,(len(a),)+tuple(params)))+'\n'+' '.join(map(str,a))+'\n'


def accepted(code,total,length,positive,negative,params):
    if code==90:return total==0
    if code==91:return total==params[0]
    if code==92:return total==params[0] and length%2==0
    if code==93:return total==params[0] and length%2==1
    if code==94:return total==params[0] and length>=params[1]
    if code==95:return total==params[0] and length<=params[1]
    if code==96:return total==params[0] and params[1]<=length<=params[2]
    if code==97:return total%params[0]==0
    if code==98:return total%params[0]==params[1]
    return positive==negative


def brute(code,a,params):
    answer=0
    for left in range(len(a)):
        total=positive=negative=0
        for right in range(left,len(a)):
            x=a[right];total+=x;positive+=x>0;negative+=x<0
            answer+=accepted(code,total,right-left+1,positive,negative,params)
    return [answer]


def reference(code,a,params):
    # Group all prefix indices, then restrict index ranges by binary search.
    transformed=[(x>0)-(x<0) for x in a] if code==99 else a
    p=[0]+list(accumulate(transformed));groups=defaultdict(list)
    for i,total in enumerate(p):
        key=(total,i%2) if code in (92,93) else total%params[0] if code in (97,98) else total
        groups[key].append(i)
    answer=0;target=params[0] if 91<=code<=96 else 0
    for r in range(1,len(a)+1):
        lo,hi=0,r-1
        if code==94:hi=r-params[1]
        if code==95:lo=max(0,r-params[1])
        if code==96:lo=max(0,r-params[2]);hi=r-params[1]
        if hi<lo:continue
        wanted=p[r]-target
        if code in (92,93):wanted=(wanted,r%2 if code==92 else 1-r%2)
        if code==97:wanted=p[r]%params[0]
        if code==98:wanted=(p[r]-params[1])%params[0]
        indices=groups.get(wanted,())
        answer+=bisect_right(indices,hi)-bisect_left(indices,lo)
    return [answer]


def solve(p,text):
    r=subprocess.run([str(p/'sol/correct')],input=text,text=True,capture_output=True,timeout=5)
    assert r.returncode==0,(p,r.stderr)
    return list(map(int,r.stdout.split()))


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
        assert list(map(int,blocks[2*i+1].split()))==brute(code,*decode(code,blocks[2*i]))
    cfg=toml.load(p/'info.toml');assert cfg['upload']==UPLOAD
    assert cfg['title'].startswith(f'PREFIX{code:03} - ')
    sol=(p/'solution.md').read_text()
    assert not re.search(r'(?m)^ {0,3}#(?:[ \t]|$)', sol)
    assert all(word not in sol.lower() for word in ('oracle','verifier','checker','benchmark','bộ sinh','kiểm thử'))
    assert not list(p.glob('*.html'))


def small_params(code,n):
    if code in (90,99):return [()]
    if code in (91,92,93):return [(x,) for x in (-1,0,1)]
    if code in (94,95):return [(t,k) for t in (-1,0,1) for k in range(1,n+1)]
    if code==96:return [(t,lo,hi) for t in (-1,0,1) for lo in range(1,n+1) for hi in range(lo,n+1)]
    if code==97:return [(m,) for m in (1,2,3)]
    return [(m,c) for m in (1,2,3) for c in range(m)]


def small_cases(code):
    for n in range(1,4):
        for a in product((-1,0,1),repeat=n):
            for params in small_params(code,n):yield list(a),params
    rng=random.Random(20261102+code)
    for turn in range(160):
        n=rng.randint(1,20)
        a=[rng.choice([-1000000000,-2,-1,0,0,1,2,1000000000,rng.randint(-20,20)]) for _ in range(n)]
        if turn%5==0:a=[0]*n
        target=rng.choice([-200000000000000,-1,0,1,200000000000000,sum(a),rng.choice(a)])
        if code in (90,99):params=()
        elif code in (91,92,93):params=(target,)
        elif code in (94,95):params=(target,rng.choice([1,n,rng.randint(1,n)]))
        elif code==96:
            lo,hi=sorted([rng.randint(1,n),rng.randint(1,n)]);params=(target,lo,hi)
            if turn%3==0:params=(target,1,n)
        elif code==97:params=(rng.choice([1,2,3,7,200000]),)
        else:
            m=rng.choice([1,2,3,7,200000]);params=(m,rng.randrange(m))
        yield a,params


def negative_checks(p,code):
    good=(p/'gen/example_00.in').read_text();a,params=decode(code,good)
    header,body=good.split('\n',1);t=header.split();invalid=[header+'\n',good+'0\n']
    for n in (0,200001):
        bad=t[:];bad[0]=str(n);invalid.append(' '.join(bad)+'\n'+body)
    invalid += [encode([-1000000001]+a[1:],params),encode([1000000001]+a[1:],params)]
    if 91<=code<=96:
        for target in (-200000000000001,200000000000001):invalid.append(encode(a,(target,)+params[1:]))
    if code in (94,95):invalid += [encode(a,(params[0],k)) for k in (0,len(a)+1)]
    if code==96:invalid += [encode(a,(params[0],lo,hi)) for lo,hi in [(0,1),(2,1),(1,len(a)+1)]]
    if code==97:invalid += [encode(a,(m,)) for m in (0,200001)]
    if code==98:invalid += [encode(a,pair) for pair in [(0,0),(200001,0),(3,-1),(3,3)]]
    for data in invalid:
        r=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert r.returncode!=0,(p,'accepted invalid',data)
    attempts=0
    with tempfile.TemporaryDirectory() as td:
        candidate=Path(td)/'candidate.out'
        for example in range(3):
            answer=(p/'out'/f'example_{example:02}.out').read_text();value=int(answer)
            variants=[(answer,True),(f' \n\t{value}  \n',True),('',False),(f'{value+1}\n',False),('-1\n',False),(answer+'0\n',False),('abc\n',False)]
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
    keys=['maximum','negative_values','zero_values','positive_values','large_positive_prefix','large_negative_prefix','large_count','positive_answer','zero_answer']
    if 91<=code<=96:keys+=['negative_target']
    if code in (94,95):keys+=['k1','kn']
    if code==96:keys+=['fixed_length','all_lengths']
    if code in (97,98):keys+=['modulus_one','modulus_max']
    if code==98:keys+=['nonzero_residue']
    coverage=dict.fromkeys(keys,False)
    for path in paths:
        text=path.read_text();a,params=decode(code,text);expected=reference(code,a,params)
        assert list(map(int,(p/'out'/(path.stem+'.out')).read_text().split()))==expected,(p,path,'reference')
        assert solve(p,text)==expected,(p,path,'solution')
        raw=[0]+list(accumulate(a))
        coverage['maximum']|=len(a)==200000
        coverage['negative_values']|=any(x<0 for x in a);coverage['zero_values']|=0 in a;coverage['positive_values']|=any(x>0 for x in a)
        coverage['large_positive_prefix']|=max(raw)>2**31-1;coverage['large_negative_prefix']|=min(raw)<-(2**31)
        coverage['large_count']|=expected[0]>2**31-1;coverage['positive_answer']|=expected[0]>0;coverage['zero_answer']|=expected[0]==0
        if 91<=code<=96:coverage['negative_target']|=params[0]<0
        if code in (94,95):coverage['k1']|=params[1]==1;coverage['kn']|=params[1]==len(a)
        if code==96:coverage['fixed_length']|=params[1]==params[2];coverage['all_lengths']|=params[1]==1 and params[2]==len(a)
        if code in (97,98):coverage['modulus_one']|=params[0]==1;coverage['modulus_max']|=params[0]==200000
        if code==98:coverage['nonzero_residue']|=params[1]>0
    assert all(coverage.values()),(p,coverage)
    count=0
    for a,params in small_cases(code):
        expected=brute(code,a,params)
        assert reference(code,a,params)==expected,(code,'reference',a,params)
        assert solve(p,encode(a,params))==expected,(code,a,params)
        count+=1
    attacks=negative_checks(p,code)
    if generate:
        problem.ignore_warning=True;problem.write_hashes()
        problem.make_inputs();problem.verify_inputs()
    problem.assert_hashes()
    print(f'dppsum{code:03}: 23 tests, {count} brute comparisons, {attacks} verifier/checker checks; hashes OK',flush=True)


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--problem',choices=[f'dppsum{code:03}' for code in range(90,100)]);ap.add_argument('--generate',action='store_true')
    args=ap.parse_args();logging.basicConfig(level=logging.ERROR)
    for code in range(90,100):
        if args.problem is None or args.problem==f'dppsum{code:03}':check(code,args.generate)

if __name__=='__main__':main()
