"""Generate and verify static maximum-subarray queries without HTML."""
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
P=ROOT/'custom/segtree310'
ORACLE=HERE/'oracle_max_subarray'


def encode(a,queries):
    return f'{len(a)}\n'+' '.join(map(str,a))+f'\n{len(queries)}\n'+''.join(f'{l} {r}\n' for l,r in queries)


def decode(data):
    lines=data.splitlines();n=int(lines[0]);a=list(map(int,lines[1].split()));m=int(lines[2])
    queries=[tuple(map(int,line.split())) for line in lines[3:]]
    assert len(a)==n and len(queries)==m and all(len(query)==2 for query in queries)
    return a,queries


def brute(data):
    a,queries=decode(data);answers=[]
    for l,r in queries:
        best=None
        for i in range(l-1,r):
            total=0
            for j in range(i,r):
                total+=a[j]
                if best is None or total>best:best=total
        answers.append(str(best))
    return answers


def check_case(data):
    run(P/'verifier',data);expected=brute(data)
    assert run(P/'sol/correct',data).split()==expected,('solution',data,expected)
    assert run(ORACLE,data).split()==expected,('independent reference',data,expected)


def small_checks():
    count=0
    for n in range(1,6):
        queries=[(l,r) for l in range(1,n+1) for r in range(l,n+1)]
        for a in itertools.product([-3,-1,0,1,3],repeat=n):
            check_case(encode(a,queries));count+=1
    rng=random.Random(20261101310)
    for _ in range(200):
        n=rng.randint(1,40);a=rng.choices([-10**9,-9,-2,-1,0,1,2,7,10**9],k=n)
        queries=[tuple(sorted([rng.randint(1,n),rng.randint(1,n)])) for _ in range(rng.randint(1,100))]
        check_case(encode(a,queries));count+=1
    extras=[[-10**9],[10**9],[0]*17,[-10**9]*17,[10**9]*17,
            [3,-100,7,8,-1,6,-100,9],[-9,4,3,-2,6,-20,5],
            [-10**9]*15+[10**9]+[-10**9]*17]
    for a in extras:
        queries=[(l,r) for l in range(1,len(a)+1) for r in range(l,len(a)+1)]
        check_case(encode(a,queries));count+=1
    return count


def invalid_inputs():
    valid=encode([0],[(1,1)])
    bad=['0\n','50001\n',encode([-10**9-1],[(1,1)]),encode([10**9+1],[(1,1)]),
         '1\n0\n0\n','1\n0\n50001\n',encode([0],[(0,1)]),encode([0],[(1,2)]),encode([0,1],[(2,1)]),
         valid+'0\n','1\n0\n1\n','1\n0\n1\n1\n','1\n0\n1\n1 1 1\n',
         '1 1\n0\n1\n1 1\n','2\n0\n1\n1 1\n','1\n0 1\n1\n1 1\n','1\n0\n2\n1 1\n']
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
        a,queries=decode(path.read_text());dims.append((len(a),len(queries)))
        assert all(1<=l<=r<=len(a) for l,r in queries)
    assert (50000,50000) in dims
    assert any(n==1 for n,_ in dims) and any(n&(n-1) for n,_ in dims)
    assert all(int(x)<0 for x in (P/'out/max_01.out').read_text().split())
    assert set((P/'out/max_02.out').read_text().split())=={'50000000000000'}
    assert (P/'out/example_00.out').read_text()=='7\n5\n6\n'
    assert not list(P.rglob('*.html'))
    audit_statement(P,with_subtask=False)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format='%(message)s');started=time.monotonic()
    problem=Problem(ROOT,P);problem.health_check();problem.generate_params_h()
    sources=[P/'sol/correct.cpp',problem.checker,problem.verifier,HERE/'oracle_max_subarray.cpp']
    sources.extend(P/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print('Compiling SEGTREE310 and independent reference...',flush=True)
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
        if path.stem.startswith(('edge','small','example')):assert brute(data)==expected,(path,'subarray enumeration differs')
    count=small_checks();invalid=invalid_inputs();check_checker(P,310)
    if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
    problem.assert_hashes()
    print(f'SEGTREE310: 36 generated tests, {count} exhaustive/random cases, {invalid} invalid inputs; 0.5s limit, subarray enumeration, checker, samples, upload, reproducibility and hashes OK ({time.monotonic()-started:.1f}s). No Subtask or HTML.',flush=True)


if __name__=='__main__':main()
