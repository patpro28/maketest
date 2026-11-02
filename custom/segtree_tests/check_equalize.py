"""Generate and verify range equalization by +1/+2 increments and point assignments without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import logging
from pathlib import Path
import random
import subprocess
import sys
import time

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[1]
sys.path.insert(0,str(HERE));sys.path.insert(0,str(ROOT))
import toml
from problem import Problem
from check import audit_statement,check_checker,run
from check_foundations import checked_compile
P=ROOT/'custom/segtree073'
ORACLE=HERE/'oracle_equalize'


def encode(a,operations):
    return f'{len(a)} {len(operations)}\n'+' '.join(map(str,a))+'\n'+''.join(' '.join(map(str,op))+'\n' for op in operations)


def decode(data):
    lines=data.splitlines();n,q=map(int,lines[0].split());a=list(map(int,lines[1].split()))
    operations=[tuple(map(int,line.split())) for line in lines[2:]]
    assert len(a)==n and len(operations)==q and all(len(op)==3 for op in operations)
    return a,operations


def brute(data):
    a,operations=decode(data);answers=[]
    for t,x,y in operations:
        if t==1:a[x-1]=y;continue
        values=a[x-1:y];maximum=max(values);gap=maximum-min(values)+2
        # Enumerate target values and use a coin-change DP for small differences.
        # Raising the target by 2 adds one move for every element, so later targets cannot win.
        if gap<=64:
            dp=[0]+[1000]*gap
            for d in range(1,gap+1):dp[d]=min(dp[d-1]+1,dp[d-2]+1 if d>=2 else 1000)
            answer=min(sum(dp[target-value] for value in values) for target in range(maximum,maximum+3))
        else:
            answer=min(sum((target-value)//2+(target-value)%2 for value in values) for target in range(maximum,maximum+3))
        answers.append(str(answer))
    return answers


def check_case(data):
    run(P/'verifier',data);expected=brute(data)
    assert run(P/'sol/correct',data).split()==expected,('solution',data,expected)
    assert run(ORACLE,data).split()==expected,('independent reference',data,expected)


def small_checks():
    count=0
    for n in range(1,6):
        queries=[(2,l,r) for l in range(1,n+1) for r in range(l,n+1)]
        for a in itertools.product([1,2,3,4],repeat=n):
            ops=list(queries)*2
            for i in range(1,n+1):
                for x in [1,2,3,4]:ops.append((1,i,x));ops.extend(queries)
            check_case(encode(a,ops));count+=1
    rng=random.Random(20261101073)
    for trial in range(200):
        n=rng.randint(1,40);a=rng.choices([1,2,3,4,5,999999937,999999999,10**9],k=n);ops=[]
        for _ in range(rng.randint(1,160)):
            if rng.randrange(100)<[10,50,90][trial%3]:
                i=rng.randint(1,n);x=rng.choice([1,2,3,4,5,999999999,10**9]);ops.append((1,i,x))
                if trial%5==0:ops.extend([(2,i,i),(2,1,n),(2,1,n)])
            else:
                l,r=sorted([rng.randint(1,n),rng.randint(1,n)]);ops.append((2,l,r))
        check_case(encode(a,ops));count+=1
    extras=[[1],[10**9],[1,2,3,4,5],[1,1,2],[1,2,2],[2,2,3],[2,3,4],[1,10**9],[1,999999999,10**9]]
    for a in extras:
        n=len(a);queries=[(2,l,r) for l in range(1,n+1) for r in range(l,n+1)];ops=list(queries)*2
        for pos in [1,n,(n+1)//2]:
            for value in [1,2,999999999,10**9,10**9,1]:ops.append((1,pos,value));ops.extend(queries)
        check_case(encode(a,ops));count+=1
    a=[1]*1403;ops=[(2,1,len(a))]
    for pos in [699,700,701,702,1399,1400,1401,1403]:
        ops.extend([(1,pos,10**9),(2,pos,pos),(2,max(1,pos-2),min(len(a),pos+2)),(2,1,len(a)),(1,pos,999999999),(2,1,len(a)),(1,pos,1),(2,1,len(a))])
    check_case(encode(a,ops));count+=1
    return count


def invalid_inputs():
    valid=encode([1],[(2,1,1)])
    bad=['0 1\n','500001 1\n','1 0\n','1 500001\n',encode([0],[(2,1,1)]),encode([-1],[(2,1,1)]),encode([10**9+1],[(2,1,1)]),
         encode([1],[(2,0,1)]),encode([1],[(2,1,2)]),encode([1,2],[(2,2,1)]),valid+'0\n','1 1\n1\n',
         '1 1\n1\n2 1\n','1 1\n1\n2 1 1 1\n','1\n1\n1\n2 1 1\n','2 1\n1\n2 1 1\n',
         '1 1\n1 2\n2 1 1\n','1 2\n1\n2 1 1\n',encode([1],[(0,1,1)]),encode([1],[(3,1,1)]),
         encode([1],[(1,0,1)]),encode([1],[(1,2,1)]),encode([1],[(1,1,0)]),encode([1],[(1,1,10**9+1)])]
    for data in bad:
        result=subprocess.run([str(P/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,('accepted invalid input',data)
    return len(bad)


def audit(problem):
    template=toml.load(ROOT/'custom/segtree000/info.toml')['upload'];template['types']=['ds_segment_tree']
    assert problem.config['upload']==template and problem.config['timelimit']==template['time_limit']==0.5
    files=sorted((P/'in').glob('*.in'));assert len(files)==36
    dims=[]
    for path in files:
        a,operations=decode(path.read_text());dims.append((len(a),len(operations)))
        assert all(1<=t<=2 and 1<=x<=len(a) and (1<=y<=10**9 if t==1 else x<=y<=len(a)) for t,x,y in operations)
        assert len((P/'out'/path.with_suffix('.out').name).read_text().splitlines())==sum(t==2 for t,_,_ in operations)
    assert (500000,500000) in dims
    assert any(n==1 for n,_ in dims) and any(n&(n-1) for n,_ in dims)
    assert set((P/'out/max_01.out').read_text().split())=={'0'}
    assert set((P/'out/max_02.out').read_text().split())=={'249999500000000'}
    assert (P/'out/edge_10.out').read_text()==''
    assert len((P/'out/max_05.out').read_text().splitlines())==1
    assert (P/'out/example_00.out').read_text()=='1\n0\n'
    assert not list(P.rglob('*.html'))
    audit_statement(P,with_subtask=False)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format='%(message)s');started=time.monotonic()
    problem=Problem(ROOT,P);problem.health_check();problem.generate_params_h()
    sources=[P/'sol/correct.cpp',problem.checker,problem.verifier,HERE/'oracle_equalize.cpp']
    sources.extend(P/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print('Compiling SEGTREE073 and independent reference...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(checked_compile,sources):pass
    problem.make_inputs();problem.verify_inputs();problem.make_outputs(True);problem.judge(P/'sol/correct.cpp',{})
    assert problem.check_all_solutions_used();audit(problem)
    for test in problem.config['tests']:
        if not test['name'].endswith('.cpp'):continue
        exe=P/'gen'/Path(test['name']).stem
        for seed in range(test['number']):assert run(exe,'',seed)==(P/'in'/f'{exe.name}_{seed:02}.in').read_text()
    for path in sorted((P/'in').glob('*.in')):
        data=path.read_text();expected=(P/'out'/path.with_suffix('.out').name).read_text().split()
        assert run(ORACLE,data).split()==expected,(path,'independent reference differs')
        if path.stem.startswith(('edge','small','example')):assert brute(data)==expected,(path,'direct target/coin-DP checks differs')
    count=small_checks();invalid=invalid_inputs();check_checker(P,73)
    if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
    problem.assert_hashes()
    print(f'SEGTREE073: 36 generated tests, {count} exhaustive/random cases, {invalid} invalid inputs; 0.5s limit, direct target/coin-DP checks, checker, samples, upload, reproducibility and hashes OK ({time.monotonic()-started:.1f}s). No Subtask or HTML.',flush=True)


if __name__=='__main__':main()
