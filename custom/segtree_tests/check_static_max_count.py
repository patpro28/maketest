"""Generate and verify offline additions followed by static range maximum/count queries without HTML."""
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
P=ROOT/'custom/segtree005'
ORACLE=HERE/'oracle_static_max_count'


def encode(n,updates,queries):
    return f'{n} {len(updates)}\n'+''.join(f'{l} {r} {k}\n' for l,r,k in updates)+f'{len(queries)}\n'+''.join(f'{l} {r}\n' for l,r in queries)


def decode(data):
    lines=data.splitlines();n,m=map(int,lines[0].split())
    updates=[tuple(map(int,line.split())) for line in lines[1:m+1]];q=int(lines[m+1])
    queries=[tuple(map(int,line.split())) for line in lines[m+2:]]
    assert len(updates)==m and len(queries)==q and all(len(op)==3 for op in updates) and all(len(op)==2 for op in queries)
    return n,updates,queries


def brute(data):
    n,updates,queries=decode(data);a=[0]*n;answers=[]
    for l,r,k in updates:
        for i in range(l-1,r):a[i]+=k
    for l,r in queries:
        segment=a[l-1:r];value=max(segment);answers.extend([str(value),str(segment.count(value))])
    return answers


def check_case(data):
    run(P/'verifier',data);expected=brute(data)
    assert run(P/'sol/correct',data).split()==expected,('solution',data,expected)
    assert run(ORACLE,data).split()==expected,('independent reference',data,expected)


def small_checks():
    count=0
    for n in range(1,6):
        queries=[(l,r) for l in range(1,n+1) for r in range(l,n+1)]
        choices=[(l,r,k) for l,r in queries for k in [1,2]]
        for first in choices:
            check_case(encode(n,[first],queries));count+=1
            for second in choices:check_case(encode(n,[first,second],queries));count+=1
    rng=random.Random(20261101005)
    for _ in range(200):
        n=rng.randint(1,35);updates=[];queries=[]
        for _ in range(rng.randint(1,80)):
            l,r=sorted([rng.randint(1,n),rng.randint(1,n)]);updates.append((l,r,rng.choice([1,2,3,7,999999937,10**9])))
        for _ in range(rng.randint(1,100)):
            l,r=sorted([rng.randint(1,n),rng.randint(1,n)]);queries.append((l,r))
        check_case(encode(n,updates,queries));count+=1
    extras=[(1,[(1,1,10**9)]*3),
            (7,[(2,2,1)]),(7,[(1,7,3)]),(7,[(1,1,3),(7,7,3)]),
            (7,[(1,3,1),(5,7,1)]),(7,[(1,7,10**9),(2,6,10**9),(3,5,10**9)]),
            (513,[(1,256,10**9),(257,513,10**9),(256,257,1)])]
    for n,updates in extras:
        queries=[(l,r) for l in range(1,n+1) for r in range(l,n+1)] if n<=7 else [(1,n),(1,256),(257,n),(256,257),(255,258),(256,256),(257,257),(n,n)]
        check_case(encode(n,updates,queries));count+=1
    return count


def invalid_inputs():
    valid=encode(1,[(1,1,1)],[(1,1)])
    bad=['0 1\n','200001 1\n','1 0\n','1 200001\n','1 1\n1 1 1\n0\n','1 1\n1 1 1\n200001\n',
         encode(1,[(0,1,1)],[(1,1)]),encode(1,[(1,2,1)],[(1,1)]),encode(2,[(2,1,1)],[(1,1)]),
         encode(1,[(1,1,0)],[(1,1)]),encode(1,[(1,1,-1)],[(1,1)]),encode(1,[(1,1,10**9+1)],[(1,1)]),
         encode(1,[(1,1,1)],[(0,1)]),encode(1,[(1,1,1)],[(1,2)]),encode(2,[(1,2,1)],[(2,1)]),
         valid+'0\n','1 1\n1 1 1\n1\n','1 1\n1 1\n1\n1 1\n','1 1\n1 1 1 1\n1\n1 1\n',
         '1 1\n1 1 1\n1\n1\n','1 1\n1 1 1\n1\n1 1 1\n']
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
        n,updates,queries=decode(path.read_text());dims.append((n,len(updates),len(queries)))
        assert len((P/'out'/path.with_suffix('.out').name).read_text().splitlines())==len(queries)
    assert (200000,200000,200000) in dims
    assert any(n==1 for n,_,_ in dims) and any(n&(n-1) for n,_,_ in dims)
    assert (P/'out/example_00.out').read_text()=='3 1\n'
    expected={1:'200000000000000 200000',2:'0 100000',3:'1 200000',4:'100000000000000 2'}
    for seed,answer in expected.items():
        assert (P/'out'/f'max_{seed:02}.out').read_text().splitlines()[0]==answer
    assert not list(P.rglob('*.html'))
    audit_statement(P,with_subtask=False)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format='%(message)s');started=time.monotonic()
    problem=Problem(ROOT,P);problem.health_check();problem.generate_params_h()
    sources=[P/'sol/correct.cpp',problem.checker,problem.verifier,HERE/'oracle_static_max_count.cpp']
    sources.extend(P/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print('Compiling SEGTREE005 and independent reference...',flush=True)
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
    count=small_checks();invalid=invalid_inputs();check_checker(P,5)
    if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
    problem.assert_hashes()
    print(f'SEGTREE005: 36 generated tests, {count} exhaustive/random cases, {invalid} invalid inputs; 0.5s limit, direct array simulation, checker, samples, upload, reproducibility and hashes OK ({time.monotonic()-started:.1f}s). No Subtask or HTML.',flush=True)


if __name__=='__main__':main()
