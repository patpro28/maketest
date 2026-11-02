"""Generate DPPSUM041..050 and audit fixed-length optimums independently."""
import argparse
from bisect import bisect_left, bisect_right
from concurrent.futures import ThreadPoolExecutor
from itertools import product
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


def decode(text):
    t=list(map(int,text.split()));n,k=t[:2];a=t[2:]
    assert len(a)==n
    return a,k


def encode(a,k):return f'{len(a)} {k}\n'+' '.join(map(str,a))+'\n'


def brute(code,a,k):
    sums=[sum(a[left:left+k]) for left in range(len(a)-k+1)]
    best=max(sums) if code%2 else min(sums)
    starts=[i+1 for i,value in enumerate(sums) if value==best]
    if code in (41,42):return [best]
    if code in (43,44):return [starts[0]]
    if code in (45,46):return [starts[-1]]
    if code in (47,48):return [len(starts)]
    if code==49:return [best,starts[0],len(starts)]
    return [best,starts[-1],len(starts)]


def reference(code,a,k):
    # Rolling sums plus sorting: independent of the official prefix + running-best scan.
    total=sum(a[:k]);ranked=[(total,1)]
    for r in range(k,len(a)):
        total+=a[r]-a[r-k]
        ranked.append((total,r-k+2))
    ranked.sort()
    best=ranked[-1][0] if code%2 else ranked[0][0]
    lo=bisect_left(ranked,(best,0));hi=bisect_right(ranked,(best,len(a)+1))
    first,last,count=ranked[lo][1],ranked[hi-1][1],hi-lo
    mapping={41:[best],42:[best],43:[first],44:[first],45:[last],46:[last],47:[count],48:[count],49:[best,first,count],50:[best,last,count]}
    return mapping[code],(best,first,last,count)


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
        assert list(map(int,blocks[2*i+1].split()))==brute(code,*decode(blocks[2*i]))
    cfg=toml.load(p/'info.toml');assert cfg['upload']==UPLOAD
    assert cfg['title'].startswith(f'PREFIX{code:03} - ')
    sol=(p/'solution.md').read_text()
    assert not re.search(r'(?m)^ {0,3}#(?:[ \t]|$)', sol)
    assert all(word not in sol.lower() for word in ('oracle','verifier','checker','benchmark','bộ sinh','kiểm thử'))
    assert not list(p.glob('*.html'))


def small_cases(code):
    for n in range(1,5):
        for raw in product((-1,0,1),repeat=n):
            for k in range(1,n+1):yield list(raw),k
    rng=random.Random(20261102+code)
    for _ in range(160):
        n=rng.randint(1,20);k=rng.randint(1,n)
        pool=[-1000000000,-7,-1,0,1,7,1000000000,rng.randint(-20,20)]
        yield [rng.choice(pool) for _ in range(n)],k


def negative_checks(p):
    good=(p/'gen/example_00.in').read_text();a,k=decode(good)
    header,body=good.split('\n',1);t=header.split()
    invalid=[header+'\n',good+'0\n']
    for index,value in [(0,0),(0,200001),(1,0),(1,len(a)+1)]:
        bad=t[:];bad[index]=str(value);invalid.append(' '.join(bad)+'\n'+body)
    invalid += [encode([-1000000001]+a[1:],k),encode([1000000001]+a[1:],k)]
    for data in invalid:
        r=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert r.returncode!=0,(p,'accepted invalid input',data)
    answer=(p/'out/example_00.out').read_text();tokens=answer.split()
    variants=[(answer,True),('\n\t'+'  '.join(tokens)+'\n',True),(' '.join([str(int(tokens[0])+1)]+tokens[1:]),False),(' '.join(tokens[:-1]),False),(answer+'0\n',False),('abc\n',False)]
    if len(tokens)==3:
        for i in (1,2):
            wrong=tokens[:];wrong[i]=str(int(wrong[i])+1);variants.append((' '.join(wrong),False))
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
    coverage=dict.fromkeys(('k1','kn','kn1','maximum','large_positive','large_negative','all_negative','ties','unique_first','unique_last'),False)
    for path in paths:
        text=path.read_text();a,k=decode(text)
        expected,(best,first,last,count)=reference(code,a,k)
        assert list(map(int,(p/'out'/(path.stem+'.out')).read_text().split()))==expected,(p,path,'reference')
        assert solve(p,text)==expected,(p,path,'solution')
        coverage['k1']|=k==1;coverage['kn']|=k==len(a);coverage['kn1']|=len(a)>1 and k==len(a)-1
        coverage['maximum']|=len(a)==200000
        coverage['large_positive']|=best>2**31-1;coverage['large_negative']|=best<-(2**31)
        coverage['all_negative']|=all(x<0 for x in a)
        coverage['ties']|=count>1
        coverage['unique_first']|=count==1 and first==1 and len(a)>k
        coverage['unique_last']|=count==1 and last==len(a)-k+1 and len(a)>k
    assert all(coverage.values()),(p,coverage)
    count=0
    for a,k in small_cases(code):
        expected=brute(code,a,k)
        assert reference(code,a,k)[0]==expected,(code,'reference',a,k)
        assert solve(p,encode(a,k))==expected,(code,a,k)
        count+=1
    attacks=negative_checks(p)
    if generate:
        problem.ignore_warning=True;problem.write_hashes()
        problem.make_inputs();problem.verify_inputs()
    problem.assert_hashes()
    print(f'dppsum{code:03}: 22 tests, {count} brute comparisons, {attacks} verifier/checker checks; hashes OK',flush=True)


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--problem',choices=[f'dppsum{code:03}' for code in range(41,51)]);ap.add_argument('--generate',action='store_true')
    args=ap.parse_args();logging.basicConfig(level=logging.ERROR)
    for code in range(41,51):
        if args.problem is None or args.problem==f'dppsum{code:03}':check(code,args.generate)

if __name__=='__main__':main()
