"""Generate/audit 08x nonnegative arrays with variable-length intervals."""
import argparse
from bisect import bisect_left,bisect_right
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

EXPECTED_UPLOAD = {**UPLOAD, "types": [*UPLOAD["types"], "tech_two_pointers"]}


def decode(code,text):
    header,body=text.split('\n',1);t=list(map(int,header.split()));n=t[0]
    a=list(map(int,body.split()));assert len(a)==n
    return a,tuple(t[1:])


def encode(a,params):return ' '.join(map(str,(len(a),)+tuple(params)))+'\n'+' '.join(map(str,a))+'\n'


def accepted(code,total,params):
    if code in (80,81,84):return total<=params[0]
    if code in (82,83,86):return total>=params[0]
    if code==85:return total<params[0]
    if code==87:return total>params[0]
    if code==88:return total==params[0]
    return params[0]<=total<=params[1]


def brute(code,a,params):
    candidates=[]
    for left in range(len(a)):
        total=0
        for right in range(left,len(a)):
            total+=a[right]
            if accepted(code,total,params):candidates.append((right-left+1,left+1,right+1))
    if code>=84:return [len(candidates)]
    if not candidates:return [0,0,0] if code in (81,83) else [0]
    best=min(candidates,key=lambda x:((-x[0] if code<82 else x[0]),x[1]))
    return list(best) if code in (81,83) else [best[0]]


def reference(code,a,params):
    # Nondecreasing prefix array with binary searches, without moving-window pointers.
    p=[0]+list(accumulate(a));n=len(a)
    if code<84:
        candidates=[];target=params[0]
        for right in range(1,n+1):
            if code<82:
                previous=bisect_left(p,p[right]-target,0,right)
                if previous<right:candidates.append((right-previous,previous+1,right))
            else:
                previous=bisect_right(p,p[right]-target,0,right)-1
                if previous>=0:candidates.append((right-previous,previous+1,right))
        if not candidates:return ([0,0,0] if code in (81,83) else [0]),dict(found=False,ties=0)
        best=min(candidates,key=lambda x:((-x[0] if code<82 else x[0]),x[1]))
        ties=sum(x[0]==best[0] for x in candidates)
        return (list(best) if code in (81,83) else [best[0]]),dict(found=True,ties=ties)
    answer=0
    for right in range(1,n+1):
        current=p[right]
        if code==84:answer+=right-bisect_left(p,current-params[0],0,right)
        elif code==85:answer+=right-bisect_right(p,current-params[0],0,right)
        elif code==86:answer+=bisect_right(p,current-params[0],0,right)
        elif code==87:answer+=bisect_left(p,current-params[0],0,right)
        elif code==88:answer+=bisect_right(p,current-params[0],0,right)-bisect_left(p,current-params[0],0,right)
        else:answer+=bisect_right(p,current-params[0],0,right)-bisect_left(p,current-params[1],0,right)
    return [answer],{}


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
    cfg=toml.load(p/'info.toml');assert cfg['upload']==EXPECTED_UPLOAD
    assert cfg['title'].startswith(f'PREFIX{code:03} - ')
    sol=(p/'solution.md').read_text()
    assert not re.search(r'(?m)^ {0,3}#(?:[ \t]|$)', sol)
    assert all(word not in sol.lower() for word in ('oracle','verifier','checker','benchmark','bộ sinh','kiểm thử'))
    assert not list(p.glob('*.html'))


def small_cases(code):
    for n in range(1,4):
        for a in product((0,1,2),repeat=n):
            if code==89:
                for upper in range(sum(a)+2):
                    for lower in range(upper+1):yield list(a),(lower,upper)
            else:
                for target in range(sum(a)+2):yield list(a),(target,)
    rng=random.Random(20261102+code)
    for turn in range(160):
        n=rng.randint(1,20)
        a=[rng.choice([0,0,1,2,7,1000000000,rng.randint(0,1000000000)]) for _ in range(n)]
        if turn%4==0:a=[0]*n
        choices=[0,1,sum(a)//2,sum(a),sum(a)+1,200000000000000]
        params=tuple(sorted((rng.choice(choices),rng.choice(choices)))) if code==89 else (rng.choice(choices),)
        yield a,params


def negative_checks(p,code):
    good=(p/'gen/example_00.in').read_text();a,params=decode(code,good)
    header,body=good.split('\n',1);t=header.split();invalid=[header+'\n',good+'0\n']
    for value in (0,200001):
        bad=t[:];bad[0]=str(value);invalid.append(' '.join(bad)+'\n'+body)
    invalid += [encode([-1]+a[1:],params),encode([1000000001]+a[1:],params)]
    invalid += [encode(a,par) for par in ((-1,0),(0,200000000000001),(1,0))] if code==89 else [encode(a,(x,)) for x in (-1,200000000000001)]
    for data in invalid:
        r=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert r.returncode!=0,(p,'accepted invalid',data)
    attempts=0
    with tempfile.TemporaryDirectory() as td:
        candidate=Path(td)/'candidate.out'
        for example in range(3):
            answer=(p/'out'/f'example_{example:02}.out').read_text();tokens=answer.split()
            variants=[(answer,True),('\n\t'+'  '.join(tokens)+'\n',True),('',False),(' '.join(tokens[:-1]),False),(answer+'0\n',False),('abc\n',False)]
            for index in range(len(tokens)):
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
    coverage=dict.fromkeys(('maximum','zero_threshold','all_zero','mixed_zero','large_total','positive','zero_answer'),False)
    if code>=84:coverage['large_count']=False
    if code==89:coverage['equal_bounds']=False
    for path in paths:
        text=path.read_text();a,params=decode(code,text);expected,details=reference(code,a,params)
        assert list(map(int,(p/'out'/(path.stem+'.out')).read_text().split()))==expected,(p,path,'reference')
        assert solve(p,text)==expected,(p,path,'solution')
        coverage['maximum']|=len(a)==200000
        coverage['zero_threshold']|=params[0]==0
        coverage['all_zero']|=all(x==0 for x in a)
        coverage['mixed_zero']|=0 in a and any(x>0 for x in a)
        coverage['large_total']|=sum(a)>2**31-1
        coverage['positive']|=expected[0]>0;coverage['zero_answer']|=expected[0]==0
        if code>=84:coverage['large_count']|=expected[0]>2**31-1
        if code==89:coverage['equal_bounds']|=params[0]==params[1]
    assert all(coverage.values()),(p,coverage)
    count=0
    for a,params in small_cases(code):
        expected=brute(code,a,params)
        assert reference(code,a,params)[0]==expected,(code,'reference',a,params)
        assert solve(p,encode(a,params))==expected,(code,a,params)
        count+=1
    attacks=negative_checks(p,code)
    if generate:
        problem.ignore_warning=True;problem.write_hashes()
        problem.make_inputs();problem.verify_inputs()
    problem.assert_hashes()
    print(f'dppsum{code:03}: 23 tests, {count} brute comparisons, {attacks} verifier/checker checks; hashes OK',flush=True)


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--problem',choices=[f'dppsum{code:03}' for code in range(80,90)]);ap.add_argument('--generate',action='store_true')
    args=ap.parse_args();logging.basicConfig(level=logging.ERROR)
    for code in range(80,90):
        if args.problem is None or args.problem==f'dppsum{code:03}':check(code,args.generate)

if __name__=='__main__':main()
