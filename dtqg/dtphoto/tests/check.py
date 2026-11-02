"""Generate and verify DTPHOTO, including witnesses for its movement promise; no HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from fractions import Fraction
import hashlib
import itertools
import logging
import os
from pathlib import Path
import random
import re
import shlex
import subprocess
import sys
import tempfile
import time

HERE=Path(__file__).resolve().parent
PACKAGE=HERE.parent
ROOT=PACKAGE.parents[1]
sys.path.insert(0,str(ROOT))
from problem import Problem
from problem_upload import ProblemUpload
BRUTE=HERE/'brute_assignment'


def score_checks(problem):
    upload=ProblemUpload(problem);assert 'manifest' not in problem.config['upload']
    assert problem.config['upload']['points']==100
    cases=upload.manifest['cases'];assert len(cases)==45
    assert all('type' not in case for case in cases)
    points={case['input_file'][:-3]:case['points'] for case in cases}
    assert set(points)=={path.stem for path in (PACKAGE/'in').glob('*.in')}
    assert points['example_00']==0 and sum(points.values())==330
    tiny=[name for name in points if name.startswith('tiny_')]
    other=[name for name in points if name not in tiny and name!='example_00']
    assert len(tiny)==11 and len(other)==33
    assert all(points[name]==9 for name in tiny) and all(points[name]==7 for name in other)
    for name in tiny:
        assert 1<=int((PACKAGE/'in'/f'{name}.in').open().readline())<=8
    for name in other:
        assert int((PACKAGE/'in'/f'{name}.in').open().readline())>8
    assert Fraction(sum(points[name] for name in tiny),sum(points.values()))==Fraction(3,10)
    return tiny


def build(src):
    flags=shlex.split(os.getenv('CXXFLAGS','-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result'))
    subprocess.run([os.getenv('CXX','g++'),*flags,'-I',str(ROOT/'common'),'-o',str(src.with_suffix('')),str(src)],check=True)


def run(executable,data='',*args,cwd=None,timeout=20):
    return subprocess.run([str(executable),*map(str,args)],input=data,text=True,capture_output=True,check=True,cwd=cwd,timeout=timeout).stdout


def encode(photos):
    return str(len(photos[0]))+'\n'+''.join(' '.join(map(str,row))+'\n' for row in photos)


def decode(data):
    rows=[list(map(int,row.split())) for row in data.splitlines()]
    n=rows[0][0];assert len(rows)==6 and all(len(row)==n for row in rows[1:]);return n,rows[1:]


def verify_witness(photos,standard,owner):
    n=len(standard);assert sorted(standard)==list(range(1,n+1))
    assert len(owner)==n+1 and all(0<=x<=5 for x in owner[1:])
    for k,row in enumerate(photos,1):
        assert sorted(row)==list(range(1,n+1))
        # Remove exactly the athletes who left in this photo from both orders.
        assert [x for x in row if owner[x]!=k]==[x for x in standard if owner[x]!=k]


def quadratic_order(photos):
    n=len(photos[0]);positions=[{x:i for i,x in enumerate(row)} for row in photos]
    rank=[0]*(n+1)
    for x in range(1,n+1):
        for y in range(x+1,n+1):
            if sum(p[x]<p[y] for p in positions)>=3:rank[y]+=1
            else:rank[x]+=1
    assert sorted(rank[1:])==list(range(n))
    return sorted(range(1,n+1),key=lambda x:rank[x])


def model(standard,owner,style,rng):
    photos=[]
    for k in range(1,6):
        kept=[x for x in standard if owner[x]!=k];moved=[x for x in standard if owner[x]==k]
        if style==0:photos.append(moved[::-1]+kept)
        elif style==1:photos.append(kept+moved[::-1])
        else:
            rng.shuffle(moved);buckets=[[] for _ in range(len(kept)+1)]
            for x in moved:buckets[rng.randrange(len(buckets))].append(x)
            row=[]
            for gap,bucket in enumerate(buckets):
                row+=bucket
                if gap<len(kept):row.append(kept[gap])
            photos.append(row)
    return photos


def small_cases():
    rng=random.Random(2026110205);seen=set()
    for n in range(1,5):
        standard=list(range(1,n+1));standard=standard[1:]+standard[:1]
        for assigned in itertools.product(range(6),repeat=n):
            owner=[0,*assigned]
            for style in range(2):
                photos=model(standard,owner,style,rng);data=encode(photos)
                if data not in seen:
                    seen.add(data);yield data,standard,owner
    # Every five-photo tuple for two athletes admits a witness: at most two bad photos.
    for bits in itertools.product(range(2),repeat=5):
        photos=[[2,1] if bit else [1,2] for bit in bits]
        standard=[2,1] if sum(bits)>=3 else [1,2];owner=[0,0,0]
        bad=[k for k,row in enumerate(photos,1) if row!=standard]
        for athlete,k in zip((1,2),bad):owner[athlete]=k
        data=encode(photos)
        if data not in seen:seen.add(data);yield data,standard,owner
    for case in range(500):
        n=rng.randint(1,40);standard=list(range(1,n+1));rng.shuffle(standard)
        owner=[0]+[rng.randrange(6) for _ in range(n)]
        if case%10==0:owner=[0]*(n+1)
        if case%10==1:owner=[0]+[rng.randint(1,5)]*n
        photos=model(standard,owner,2,rng);data=encode(photos)
        if data not in seen:seen.add(data);yield data,standard,owner


def wrong_heuristics(photos,standard):
    n=len(standard);pos=[{x:i for i,x in enumerate(row)} for row in photos]
    return {
        'first_photo':photos[0]!=standard,
        'median_position':sorted(range(1,n+1),key=lambda x:(sorted(p[x] for p in pos)[2],x))!=standard,
        'average_position':sorted(range(1,n+1),key=lambda x:(sum(p[x] for p in pos),x))!=standard,
        'three_photos':any(sum(p[x]<p[y] for p in pos[:3])<2 for x,y in zip(standard,standard[1:])),
    }


def audit():
    text=(PACKAGE/'task.md').read_text()
    expected=['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc','Subtask','Sample Input 1','Sample Output 1','Giải thích']
    assert text.splitlines()[0]=='# DTPHOTO — Chụp ảnh'
    assert re.findall(r'^### (.+)$',text,re.M)==expected
    assert len(re.findall(r'^#+ ',text,re.M))==len(expected)+1
    assert re.findall(r'^\| ([1-2]) \| (\d+)% \|',text,re.M)==[('1','30'),('2','70')]
    assert not list(PACKAGE.rglob('*.html'))
    for label,folder,ext in [('Input','in','in'),('Output','out','out')]:
        match=re.search(rf'### Sample {label} 1\n\n```text\n(.*?)```',text,re.S)
        assert match and match[1]==(PACKAGE/folder/f'example_00.{ext}').read_text()
    solution=(PACKAGE/'solution.md').read_text();assert not re.search(r'(?m)^ {0,3}#(?:[ \t]|$)', solution)
    assert not re.search(r'oracle|verifier|checker|benchmark|kiểm thử|kiểm chứng|bộ sinh|chạy test',solution,re.I)


def invalid_checks():
    sample=(PACKAGE/'gen/example_00.in').read_text()
    good=[[1,2,3]]*5
    cases=['',sample+'0\n',sample.rsplit('\n',2)[0]+'\n','0\n','100001\n','-1\n',
           '3\n'+'1 2 3\n'*4,'3\n'+'1 2 3\n'*6,'3\n'+'1 2\n'+'1 2 3\n'*4,
           '3\n'+'1 2 3 4\n'+'1 2 3\n'*4]
    for row in ([1,1,3],[0,2,3],[1,2,4],[-1,2,3]):
        photos=[x.copy() for x in good];photos[2]=row;cases.append(encode(photos))
    cases += ['1\n1\n1\nx\n1\n1\n','1\n1\n1\n1.0\n1\n1\n']
    for data in cases:
        result=subprocess.run([str(PACKAGE/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,('Accepted invalid input',data)
    run(PACKAGE/'verifier',sample.replace(' ','   '))
    return len(cases)


def checker_checks():
    count=0
    with tempfile.TemporaryDirectory() as directory:
        actual=Path(directory)/'actual';answer=Path(directory)/'answer'
        for case in ('example_00','tiny_00','max_02'):
            inp=PACKAGE/'in'/f'{case}.in';good=(PACKAGE/'out'/f'{case}.out').read_text();words=good.split();n=len(words);answer.write_text(good)
            variants=[(good,True),(' \n\t'+'   '.join(words)+' \n',True),('',False),('0\n',False),('-1\n',False),
                      (str(n+1)+'\n',False),('9'*50+'\n',False),('1.0\n',False),('x\n',False),
                      (good+'1\n',False),(good+'garbage\n',False)]
            if n>1:
                swapped=words.copy();swapped[0],swapped[1]=swapped[1],swapped[0]
                duplicate=words.copy();duplicate[1]=duplicate[0]
                variants += [(' '.join(swapped)+'\n',False),(' '.join(duplicate)+'\n',False),(' '.join(words[:-1])+'\n',False)]
            for data,accepted in variants:
                actual.write_text(data)
                result=subprocess.run([str(PACKAGE/'checker'),str(inp),str(actual),str(answer)],capture_output=True)
                assert (result.returncode==0)==accepted,(case,data[:80],result.stderr);count+=1
    return count


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format='%(message)s');problem=Problem(ROOT,PACKAGE)
    problem.health_check();problem.generate_params_h()
    sources=[PACKAGE/'sol/correct.cpp',PACKAGE/'verifier.cpp',PACKAGE/'checker.cpp',HERE/'oracle.cpp',BRUTE.with_suffix('.cpp')]
    sources += [PACKAGE/'gen'/t['name'] for t in problem.config['tests'] if t['name'].endswith('.cpp')]
    print(f'Compiling {len(sources)} programs...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(build,sources))
    problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
    problem.judge(problem.get_correct_filename(),{});assert problem.check_all_solutions_used();audit()
    started=time.monotonic();maximum=0;witnesses={};failures={name:False for name in ('first_photo','median_position','average_position','three_photos')}
    tiny_names=score_checks(problem)
    print('DTPHOTO: 11 tiny tests x 9 and 33 other tests x 7; score split 30/70%; example 0 points',flush=True)
    witnesses['example_00']=([1,3,5,7,9,2,4,6,8],[0,3,2,1,2,4,2,5,1,0])
    for test in problem.config['tests']:
        if test['name'].endswith('.cpp'):
            stem=Path(test['name']).stem
            for seed in range(test['number']):
                name=f'{stem}_{seed:02}'
                assert run(PACKAGE/'gen'/stem,'',seed)==(PACKAGE/'in'/f'{name}.in').read_text()
                rows=[list(map(int,row.split())) for row in run(PACKAGE/'gen'/stem,'',seed,'witness').splitlines()]
                assert len(rows)==3 and len(rows[1])==len(rows[2])==rows[0][0]
                witnesses[name]=(rows[1],[0,*rows[2]])
    with tempfile.TemporaryDirectory() as directory:
        files=sorted((PACKAGE/'in').glob('*.in'));assert len(files)==45
        brute_maximum=0;small_brute=0
        for i,path in enumerate(files,1):
            data=path.read_text();n,photos=decode(data);standard,owner=witnesses[path.stem]
            verify_witness(photos,standard,owner)
            expected=list(map(int,(PACKAGE/'out'/path.with_suffix('.out').name).read_text().split()))
            assert expected==standard,path.name
            assert list(map(int,run(HERE/'oracle',data,cwd=directory).split()))==standard,path.name
            if n<=200:
                assert quadratic_order(photos)==standard
                for name,failed in wrong_heuristics(photos,standard).items():failures[name] |= failed
            if path.stem in tiny_names:
                before=time.monotonic()
                assert list(map(int,run(BRUTE,data,cwd=directory,timeout=1).split()))==standard
                brute_maximum=max(brute_maximum,time.monotonic()-before)
            before=time.monotonic()
            assert list(map(int,run(PACKAGE/'sol/correct',data,cwd=directory,timeout=1).split()))==standard
            maximum=max(maximum,time.monotonic()-before)
            if path.stem.startswith('max_'):assert n==100000
            if i%10==0:print(f'DTPHOTO: checked {i}/{len(files)} official cases and movement witnesses',flush=True)
        assert all(failures.values()),failures
        # Majority can define an order even for photos violating the movement promise.
        # The direct movement-set enumeration must reject this semantic counterexample.
        impossible=encode([[3,2,1],[3,2,1],[1,2,3],[1,2,3],[1,2,3]])
        assert quadratic_order(decode(impossible)[1])==[1,2,3]
        assert run(BRUTE,impossible,cwd=directory).strip()=='IMPOSSIBLE'
        print('DTPHOTO: checking small cases against all-pairs majority ranks...',flush=True)
        small=0
        for data,standard,owner in small_cases():
            _,photos=decode(data);verify_witness(photos,standard,owner);run(PACKAGE/'verifier',data)
            assert quadratic_order(photos)==standard
            assert list(map(int,run(PACKAGE/'sol/correct',data,cwd=directory).split()))==standard
            assert list(map(int,run(HERE/'oracle',data,cwd=directory).split()))==standard
            if len(standard)<=8:
                assert list(map(int,run(BRUTE,data,cwd=directory,timeout=1).split()))==standard
                small_brute+=1
            small+=1
        for name in ('example_00','max_02','max_11'):
            data=(PACKAGE/'in'/f'{name}.in').read_text();expected=(PACKAGE/'out'/f'{name}.out').read_text()
            (Path(directory)/'PHOTO.INP').write_text(data)
            assert run(PACKAGE/'sol/correct','',cwd=directory)==''
            assert (Path(directory)/'PHOTO.OUT').read_text()==expected
        (Path(directory)/'PHOTO.INP').unlink()
    invalid=invalid_checks();checker=checker_checks()
    if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
    problem.assert_hashes()
    print(f'DTPHOTO: PASS; 45 official with valid witnesses; all 11 tiny tests checked by 5^n assignments and topological sorting; {small} small; {small_brute} small cases also enumerated; 1 impossible movement case rejected; 4 wrong heuristics rejected; '
          f'3 file-I/O; {invalid} invalid-input; {checker} checker checks; hashes verified; '
          f'max reference runtime {maximum:.4f}s; max assignment runtime {brute_maximum:.4f}s; {time.monotonic()-started:.1f}s',flush=True)


if __name__=='__main__':main()
