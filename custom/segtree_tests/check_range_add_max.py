"""Generate and verify range-add/range-maximum queries using lazy propagation without HTML."""
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
from problem import Problem
from check import audit_statement,check_checker,run
from check_foundations import checked_compile
P=ROOT/'custom/segtree220'
ORACLE=HERE/'oracle_range_add_max'


def encode(a,operations):
    return f'{len(a)} {len(operations)}\n'+' '.join(map(str,a))+'\n'+''.join(' '.join(map(str,op))+'\n' for op in operations)


def decode(data):
    lines=data.splitlines();n,m=map(int,lines[0].split());a=list(map(int,lines[1].split()))
    operations=[tuple(map(int,line.split())) for line in lines[2:]]
    assert len(a)==n and len(operations)==m and all(len(op)==(4 if op[0]==0 else 3) for op in operations)
    return a,operations


def brute(data):
    a,operations=decode(data);answers=[]
    for op in operations:
        t,l,r=op[:3]
        if t==0:
            for i in range(l-1,r):a[i]+=op[3]
        else:answers.append(str(max(a[l-1:r])))
    return answers


def check_case(data):
    run(P/'verifier',data);expected=brute(data)
    assert run(P/'sol/correct',data).split()==expected,('solution',data,expected)
    assert run(ORACLE,data).split()==expected,('independent reference',data,expected)


def small_checks():
    count=0
    for n in range(1,6):
        ranges=[(l,r) for l in range(1,n+1) for r in range(l,n+1)]
        queries=[(1,l,r) for l,r in ranges]
        for a in itertools.product([-2,0,3],repeat=n):
            ops=list(queries)
            for l,r in ranges:
                for k in [-2,0,3]:ops.append((0,l,r,k));ops.extend(queries)
            check_case(encode(a,ops));count+=1
    # Every pair of small interval additions, including nested/overlapping/disjoint intervals.
    for n in range(1,5):
        ranges=[(l,r) for l in range(1,n+1) for r in range(l,n+1)]
        queries=[(1,l,r) for l,r in ranges]
        updates=[(0,l,r,k) for l,r in ranges for k in [-1,1]]
        for first in updates:
            for second in updates:
                check_case(encode([-3]*n,[first]+queries+[second]+queries));count+=1
    rng=random.Random(20261101220)
    for trial in range(200):
        n=rng.randint(1,40);a=rng.choices([-10000,-7,-1,0,1,7,10000],k=n);ops=[]
        for _ in range(rng.randint(1,160)):
            l,r=sorted([rng.randint(1,n),rng.randint(1,n)])
            if rng.randrange(100)<[10,50,90][trial%3]:
                ops.append((0,l,r,rng.choice([-10000,-7,-1,0,1,7,10000])))
                if trial%5==0:ops.extend([(1,l,r),(1,1,n)])
            else:ops.append((1,l,r))
        check_case(encode(a,ops));count+=1
    extras=[[-10000],[10000],[0]*17,[-10000]*17,[10000]*17,[-9,4,-3,2,-6,8,-1],[-10000]*15+[10000]+[-10000]*17]
    for a in extras:
        n=len(a);queries=[(1,l,r) for l in range(1,n+1) for r in range(l,n+1)];ops=list(queries)
        for l,r in [(1,n),(1,1),(n,n),(max(1,n//2),n)]:
            for k in [-10000,10000,0,-10000]:ops.append((0,l,r,k));ops.extend(queries)
        check_case(encode(a,ops));count+=1
    a=[-7]*1001;ops=[]
    for l,r in [(1,1001),(450,451),(1,450),(451,900),(899,1001),(1,1001)]:
        ops.extend([(0,l,r,10000),(1,l,r),(1,1,1001),(0,l,r,-10000),(1,1,1001)])
    check_case(encode(a,ops));count+=1
    return count


def invalid_inputs():
    valid=encode([0],[(1,1,1)])
    bad=['0 1\n','100001 1\n','1 0\n','1 100001\n',encode([-10001],[(1,1,1)]),encode([10001],[(1,1,1)]),
         encode([0],[(1,0,1)]),encode([0],[(1,1,2)]),encode([0,1],[(1,2,1)]),valid+'0\n','1 1\n0\n',
         '1 1\n0\n1 1\n','1 1\n0\n1 1 1 0\n','1\n0\n1\n1 1 1\n','2 1\n0\n1 1 1\n',
         '1 1\n0 1\n1 1 1\n','1 2\n0\n1 1 1\n',encode([0],[(2,1,1)]),encode([0],[(-1,1,1)]),
         encode([0],[(0,0,1,1)]),encode([0],[(0,1,2,1)]),encode([0,1],[(0,2,1,1)]),
         encode([0],[(0,1,1,-10001)]),encode([0],[(0,1,1,10001)]),'1 1\n0\n0 1 1\n','1 1\n0\n0 1 1 1 1\n']
    for data in bad:
        result=subprocess.run([str(P/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,('accepted invalid input',data)
    return len(bad)


def audit(problem):
    upload=problem.config['upload']
    assert problem.config['timelimit']==upload['time_limit']==1.0
    assert upload['types']==['ds_segment_tree']
    files=sorted((P/'in').glob('*.in'));assert len(files)==36
    dims=[]
    for path in files:
        a,operations=decode(path.read_text());dims.append((len(a),len(operations)))
        assert all(0<=op[0]<=1 and 1<=op[1]<=op[2]<=len(a) and (op[0]==1 or -10000<=op[3]<=10000) for op in operations)
        assert len((P/'out'/path.with_suffix('.out').name).read_text().splitlines())==sum(op[0]==1 for op in operations)
    assert (100000,100000) in dims
    assert any(n==1 for n,_ in dims) and any(n&(n-1) for n,_ in dims)
    assert all(int(x)<0 for x in (P/'out/max_01.out').read_text().split())
    assert (P/'out/max_02.out').read_text()=='1000000000\n'
    assert (P/'out/max_05.out').read_text()=='-1000000000\n'
    assert (P/'out/edge_10.out').read_text()==''
    assert (P/'out/example_00.out').read_text()=='4\n'
    assert not list(P.rglob('*.html'))
    audit_statement(P,with_subtask=False)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format='%(message)s');started=time.monotonic()
    problem=Problem(ROOT,P);problem.health_check();problem.generate_params_h()
    sources=[P/'sol/correct.cpp',problem.checker,problem.verifier,HERE/'oracle_range_add_max.cpp']
    sources.extend(P/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print('Compiling SEGTREE220 and independent reference...',flush=True)
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
        if path.stem.startswith(('edge','small','example')):assert brute(data)==expected,(path,'direct array simulation differs')
    count=small_checks();invalid=invalid_inputs();check_checker(P,220)
    if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
    problem.assert_hashes()
    print(f'SEGTREE220: 36 generated tests, {count} exhaustive/random cases, {invalid} invalid inputs; 1s limit, direct array simulation, checker, samples, upload, reproducibility and hashes OK ({time.monotonic()-started:.1f}s). No Subtask or HTML.',flush=True)


if __name__=='__main__':main()
