"""Generate and check DTPLAN, including PLAN.INP/PLAN.OUT; no HTML export."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from fractions import Fraction
import itertools
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
import time

HERE=Path(__file__).resolve().parent
PACKAGE=HERE.parent
ROOT=PACKAGE.parents[1]
sys.path.insert(0,str(ROOT))
from problem import Problem
from problem_upload import ProblemUpload
MOD=10**9


def legacy_cases():
    mapping={'example_00':'example_00'}
    mapping.update({f'edge_{i:02}':f'sub1_{i:02}' for i in range(10)})
    mapping.update({f'small_{i:02}':f'sub1_{i+10:02}' for i in range(10)})
    for i in range(6):
        group,index=(1,20+i) if i<2 else (2,i-2) if i<4 else (3,i-3)
        mapping[f'stages_{i:02}']=f'sub{group}_{index:02}'
    mapping.update({f'max_{i:02}':f'sub4_{i:02}' for i in range(12)})
    mapping.update({f'stress_{i:02}':f'sub4_{i+19:02}' for i in range(8)})
    for index,seed in enumerate((0,1,2,4,5,6,7)):
        mapping[f'random_{seed:02}']=f'sub4_{index+12:02}'
    mapping['random_03']='sub3_00'
    assert len(mapping)==len(set(mapping.values()))==55
    return mapping


def legacy_path(folder,name):
    extension='in' if folder=='in' else 'out'
    return PACKAGE/folder/f'{legacy_cases()[name]}.{extension}'


def score_checks(problem):
    expected={1:(25,4,100),2:(10,20,200),3:(10,30,300),4:(40,10,400)}
    assert 'manifest' not in problem.config['upload']
    assert problem.config['upload']['points']==100
    upload=ProblemUpload(problem)
    cases=upload.manifest['cases'];assert len(cases)==86
    points={case['input_file'][:-3]:case['points'] for case in cases}
    assert points['example_00']==0 and sum(points.values())==1000
    assert set(points)=={path.stem for path in (PACKAGE/'in').glob('*.in')}
    assert all('type' not in case for case in cases)
    for group,(number,per_test,total) in expected.items():
        selected=[(name,value) for name,value in points.items() if name.startswith(f'sub{group}_')]
        assert len(selected)==number and all(value==per_test for _,value in selected)
        assert sum(value for _,value in selected)==total
        assert Fraction(total,sum(points.values()))==Fraction(group,10)
        for name,value in selected:
            pairs,A,B=decode((PACKAGE/'in'/f'{name}.in').read_text())
            actual=1 if max(A,B)<=1000 else 2 if len(pairs)<=3 else 3 if len(pairs)<=10 else 4
            assert actual==group,(name,actual,group)
    return {group:total for group,(_,_,total) in expected.items()}


def build(src):
    flags=shlex.split(os.getenv('CXXFLAGS','-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result'))
    subprocess.run([os.getenv('CXX','g++'),*flags,'-I',str(ROOT/'common'),'-o',str(src.with_suffix('')),str(src)],check=True)


def run(executable,data,cwd=None,timeout=10):
    return subprocess.run([str(executable)],input=data,text=True,capture_output=True,check=True,cwd=cwd,timeout=timeout).stdout


def encode(pairs,A,B):
    return f'{len(pairs)} {A} {B}\n'+''.join(f'{a} {b}\n' for a,b in pairs)


def decode(data):
    words=list(map(int,data.split()));m,A,B=words[:3]
    return [tuple(words[i:i+2]) for i in range(3,3+2*m,2)],A,B


def brute(data):
    pairs,A,B=decode(data);dp=[[0]*(B+1) for _ in range(A+1)];dp[0][0]=1
    for a,b in pairs:
        for x in range(a,A+1):
            for y in range(b,B+1):
                dp[x][y]=(dp[x][y]+dp[x-a][y-b])%MOD
    return dp[A][B]


def enumerate_quantities(data):
    pairs,A,B=decode(data)
    def dfs(i,a,b):
        if i==len(pairs):return int(a==0 and b==0)
        x,y=pairs[i]
        return sum(dfs(i+1,a-x*k,b-y*k) for k in range(min(a//x,b//y)+1))
    return dfs(0,A,B)%MOD


def small_cases():
    coefficients=list(itertools.product(range(1,6),repeat=2))
    for pair in coefficients:
        for A in range(1,8):
            for B in range(1,8):yield encode([pair],A,B)
    for pairs in itertools.combinations_with_replacement(coefficients,2):
        for A,B in ((1,1),(6,6),(11,13)):yield encode(pairs,A,B)
    rng=random.Random(2026110101)
    for _ in range(300):
        m=rng.randint(1,20)
        pairs=[rng.choice(coefficients) for _ in range(m)]
        yield encode(pairs,rng.randint(1,45),rng.randint(1,45))


def audit():
    text=(PACKAGE/'task.md').read_text()
    expected=['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc','Subtask','Sample Input 1','Sample Output 1','Giải thích']
    assert text.splitlines()[0]=='# DTPLAN — Kế hoạch sản xuất'
    assert re.findall(r'^### (.+)$',text,re.M)==expected
    assert len(re.findall(r'^#+ ',text,re.M))==len(expected)+1
    assert not list(PACKAGE.rglob('*.html'))
    assert re.findall(r'^\| ([1-4]) \| (\d+)% \|',text,re.M)==[('1','10'),('2','20'),('3','30'),('4','40')]
    for label,folder,ext in [('Input','in','in'),('Output','out','out')]:
        match=re.search(rf'### Sample {label} 1\n\n```text\n(.*?)```',text,re.S)
        assert match and match[1]==(PACKAGE/folder/f'example_00.{ext}').read_text()
    solution=(PACKAGE/'solution.md').read_text()
    assert not re.search(r'(?m)^ {0,3}#(?:[ \t]|$)', solution)
    assert not re.search(r'oracle|verifier|checker|benchmark|kiểm thử|kiểm chứng|bộ sinh|chạy test',solution,re.I)


def invalid_checks():
    sample=(PACKAGE/'gen/example_00.in').read_text()
    cases=['',sample+'0\n',sample.rsplit('\n',2)[0]+'\n','0 1 1\n','21 1 1\n',
           '1 0 1\n1 1\n','1 1 0\n1 1\n','1 1000000001 1\n1 1\n','1 1 1000000001\n1 1\n',
           '1 -1 1\n1 1\n','1 1 1\n0 1\n','1 1 1\n1 0\n','1 1 1\n6 1\n','1 1 1\n1 6\n',
           '1 1 1\n-1 1\n','1 1\n1 1\n']
    for data in cases:
        result=subprocess.run([str(PACKAGE/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,('Accepted invalid input',data)
    run(PACKAGE/'verifier',sample.replace(' ','   '))
    return len(cases)


def checker_checks():
    count=0
    with tempfile.TemporaryDirectory() as directory:
        actual=Path(directory)/'actual';answer=Path(directory)/'answer'
        for case in ('example_00','edge_02','max_00'):
            inp=legacy_path('in',case);good=legacy_path('out',case).read_text();answer.write_text(good)
            wrong=str((int(good)+1)%MOD)+'\n'
            variants=[(good,True),(' \n'+good.strip()+' \n',True),(wrong,False),('',False),('-1\n',False),
                      ('1000000000\n',False),('9'*50+'\n',False),('1.0\n',False),('x\n',False),
                      (good+'0\n',False),(good+'garbage\n',False)]
            for data,accepted in variants:
                actual.write_text(data)
                result=subprocess.run([str(PACKAGE/'checker'),str(inp),str(actual),str(answer)],capture_output=True)
                assert (result.returncode==0)==accepted,(data,result.stderr);count+=1
    return count


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format='%(message)s');problem=Problem(ROOT,PACKAGE)
    problem.health_check();problem.generate_params_h()
    sources=[PACKAGE/'sol/correct.cpp',PACKAGE/'verifier.cpp',PACKAGE/'checker.cpp',HERE/'oracle.cpp']
    sources += [PACKAGE/'gen'/t['name'] for t in problem.config['tests'] if t['name'].endswith('.cpp')]
    print(f'Compiling {len(sources)} programs...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(build,sources))
    problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
    problem.judge(problem.get_correct_filename(),{});assert problem.check_all_solutions_used();audit()
    maximum=0;started=time.monotonic()
    with tempfile.TemporaryDirectory() as directory:
        files=sorted((PACKAGE/'in').glob('*.in'));assert len(files)==86
        totals=score_checks(problem)
        print(f'DTPLAN: score weights {totals}; total 1000; ratios 10/20/30/40%; no custom manifest',flush=True)
        for i,path in enumerate(files,1):
            data=path.read_text();expected=int((PACKAGE/'out'/path.with_suffix('.out').name).read_text())
            assert int(run(HERE/'oracle',data,cwd=directory))==expected,path.name
            pairs,A,B=decode(data)
            if len(set(pairs))==1:
                a,b=pairs[0]
                closed=math.comb(A//a+len(pairs)-1,len(pairs)-1)%MOD if A%a==0 and B%b==0 and A//a==B//b else 0
                assert expected==closed,path.name
            if max(A,B)<=100:assert expected==brute(data),path.name
            before=time.monotonic();assert int(run(PACKAGE/'sol/correct',data,cwd=directory,timeout=1))==expected
            maximum=max(maximum,time.monotonic()-before)
            if i%10==0:print(f'DTPLAN: independently checked {i}/{len(files)} official tests',flush=True)
        for test in problem.config['tests']:
            if test['name'].endswith('.cpp'):
                stem=Path(test['name']).stem
                for seed in range(test['number']):
                    generated=subprocess.run([str(PACKAGE/'gen'/stem),str(seed)],capture_output=True,text=True,check=True).stdout
                    assert generated==(PACKAGE/'in'/f'{stem}_{seed:02}.in').read_text()
        assert len(decode(legacy_path('in','stress_00').read_text())[0])==20
        for seed in range(12):
            assert len(decode(legacy_path('in',f'max_{seed:02}').read_text())[0])==20
        for seed in (1,2):
            assert legacy_path('out',f'stress_{seed:02}').read_text()==legacy_path('out','stress_00').read_text()
        for seed in range(6):
            pairs,A,B=decode(legacy_path('in',f'stages_{seed:02}').read_text())
            assert len(pairs)==(20 if seed<2 else 3 if seed<4 else 10)
            assert max(A,B)==(1000 if seed<2 else 10**9 if seed<4 else 999999937 if seed==4 else (1<<29)+1)
        # Count actual grouped transitions, not a product of loose state-space bounds.
        profiled=Path(directory)/'profiled'
        flags=shlex.split(os.getenv('CXXFLAGS','-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result'))
        subprocess.run([os.getenv('CXX','g++'),*flags,'-DCOUNT_TRANSITIONS',str(PACKAGE/'sol/correct.cpp'),'-o',str(profiled)],check=True)
        data=legacy_path('in','stress_00').read_text()
        measured=subprocess.run([str(profiled)],input=data,text=True,capture_output=True,check=True,cwd=directory,timeout=2)
        transitions=int(measured.stderr.strip());assert transitions==32003440
        assert measured.stdout==legacy_path('out','stress_00').read_text()
        print(f'DTPLAN: sub4_19 (formerly stress_00) performs {transitions} grouped transitions',flush=True)
        print('DTPLAN: checking small cases against two-dimensional DP...',flush=True)
        small=0;quantity_checks=0
        for data in small_cases():
            run(PACKAGE/'verifier',data);expected=brute(data)
            assert int(run(PACKAGE/'sol/correct',data,cwd=directory))==int(run(HERE/'oracle',data,cwd=directory))==expected,(data,expected)
            if len(decode(data)[0])<=2:
                assert expected==enumerate_quantities(data);quantity_checks+=1
            small+=1
        # Reordering product types and swapping resources preserve counts.
        rng=random.Random(2026110102);metamorphic=0
        for _ in range(20):
            m=rng.randint(1,20);pairs=[(rng.randint(1,5),rng.randint(1,5)) for _ in range(m)]
            A=rng.randint(1,10**9);B=rng.randint(1,10**9)
            if rng.randrange(2):
                A=B=0
                for a,b in pairs:
                    x=rng.randint(0,10**6);A+=a*x;B+=b*x
            data=encode(pairs,A,B);expected=int(run(HERE/'oracle',data,cwd=directory));rng.shuffle(pairs)
            for transformed in (encode(pairs,A,B),encode([(b,a) for a,b in pairs],B,A)):
                assert int(run(PACKAGE/'sol/correct',transformed,cwd=directory))==expected;metamorphic+=1
        for index in (0,1,2):
            data=legacy_path('in',f'max_{index:02}').read_text();answer=legacy_path('out',f'max_{index:02}').read_text()
            (Path(directory)/'PLAN.INP').write_text(data)
            assert run(PACKAGE/'sol/correct','',cwd=directory)==''
            assert (Path(directory)/'PLAN.OUT').read_text()==answer
        (Path(directory)/'PLAN.INP').unlink()
    invalid=invalid_checks();checker=checker_checks()
    if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
    problem.assert_hashes()
    print(f'DTPLAN: PASS; 86 official; {small} small; {quantity_checks} direct enumerations; {metamorphic} symmetry checks; '
          f'3 file-I/O checks; {invalid} invalid-input; {checker} checker tests; hashes verified; '
          f'max reference runtime {maximum:.4f}s; {time.monotonic()-started:.1f}s',flush=True)


if __name__=='__main__':main()
