"""Generate and verify three static queries that need more than prefix sums."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import logging
import math
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
KINDS=[6,7,9]
NAMES=[f'segtree{k:03}' for k in KINDS]
ORACLE=HERE/'oracle_static_three'


def decode(data):
    lines=data.splitlines();n,q=map(int,lines[0].split());a=list(map(int,lines[1].split()))
    queries=[tuple(map(int,line.split())) for line in lines[2:]]
    assert len(a)==n and len(queries)==q and all(len(query)==2 for query in queries)
    return a,queries

def encode(a,queries):return f'{len(a)} {len(queries)}\n'+' '.join(map(str,a))+'\n'+''.join(f'{l} {r}\n' for l,r in queries)
def brute(k,data):
    lines=data.splitlines();n,q=map(int,lines[0].split());a=list(map(int,lines[1].split()));out=[]
    assert len(a)==n and len(lines)==q+2
    for line in lines[2:]:
        l,r=map(int,line.split());segment=a[l-1:r]
        if k==6:
            prices=sorted(set(segment));answer=prices[1] if len(prices)>1 else -1
        elif k==7:
            answer=1
            for x in segment:answer=math.lcm(answer,x)
            if answer>10**18:answer=-1
        else:answer=min((segment[i]+segment[i+1] for i in range(len(segment)-1)),default=-1)
        out.append(str(answer))
    return out


def check_case(p,k,data):
    run(p/'verifier',data);expected=brute(k,data)
    assert run(p/'sol/correct',data).split()==expected,(p,'solution',data,expected)
    assert run(ORACLE,data,k).split()==expected,(p,'independent reference',data,expected)


def small_checks(p,k):
    count=0;alphabet=[0,1,2,7] if k==6 else [1,2,3,6] if k==7 else [0,1,3,7]
    for n in range(1,6):
        queries=[(l,r) for l in range(1,n+1) for r in range(l,n+1)]
        for a in itertools.product(alphabet,repeat=n):check_case(p,k,encode(a,queries));count+=1
    rng=random.Random(20261102+k)
    values=[0,1,2,3,4,6,10,12,18,30,999999937,999999929,999999893,10**9]
    if k==7:values=values[1:]
    for _ in range(200):
        n=rng.randint(1,40);a=rng.choices(values,k=n)
        queries=[tuple(sorted([rng.randint(1,n),rng.randint(1,n)])) for _ in range(rng.randint(1,100))]
        check_case(p,k,encode(a,queries));count+=1
    extras={6:[[0],[10**9],[3]*17,[1,1,2,1,2],[0,2,4],[1,1,4],[10**9,0,10**9,0]],
            7:[[1],[10**9],[6]*17,[2,6],[3,5],[999999937,999999929],[999999937,999999929,999999893],[1,999999937,1,999999929,1]],
            9:[[0],[10**9],[10**9]*17,[1,4,1,4],[1,1,4,4],[1,100,2,3,100,1],[10**9,10**9,0,0]]}[k]
    for a in extras:
        queries=[(l,r) for l in range(1,len(a)+1) for r in range(l,len(a)+1)]
        check_case(p,k,encode(a,queries));count+=1
    n=1001;a=[1]*n
    if k==6:a[449]=0;a[450]=10**9;a[899]=2
    if k==7:a[449]=999999937;a[450]=999999929;a[899]=999999893
    if k==9:a=[10**9]*n;a[449]=0;a[450]=1;a[899]=0;a[900]=0
    queries=[(1,n),(1,450),(450,451),(451,900),(899,901),(450,900),(901,n),(n,n)]
    check_case(p,k,encode(a,queries));count+=1
    # A single prefix-sum difference and interval length cannot determine any of these answers.
    left,right={6:([0,2,4],[1,1,4]),7:([2,6],[3,5]),9:([1,4,1,4],[1,1,4,4])}[k]
    assert len(left)==len(right) and sum(left)==sum(right)
    assert brute(k,encode(left,[(1,len(left))]))!=brute(k,encode(right,[(1,len(right))]))
    return count


def invalid_inputs(p,k):
    low=1 if k==7 else 0
    valid=encode([low],[(1,1)])
    bad=['0 1\n','200001 1\n','1 0\n','1 200001\n',encode([low-1],[(1,1)]),encode([10**9+1],[(1,1)]),
         encode([low],[(0,1)]),encode([low],[(1,2)]),encode([low,low],[(2,1)]),valid+'0\n',
         '1 1\n'+str(low)+'\n','1 1\n'+str(low)+'\n1\n','1 1\n'+str(low)+'\n1 1 1\n',
         '1\n'+str(low)+'\n1\n1 1\n','2 1\n'+str(low)+'\n1 1\n','1 1\n'+str(low)+' 1\n1 1\n']
    for data in bad:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(p,'accepted invalid input',data)
    return len(bad)


def audit(problem,k):
    p=problem.basedir;template=toml.load(ROOT/'custom/segtree000/info.toml')['upload'];template['types']=['ds_segment_tree']
    assert problem.config['upload']==template and problem.config['timelimit']==template['time_limit']==0.5
    assert problem.config['params']['VALUE_MIN']==(1 if k==7 else 0)
    files=sorted((p/'in').glob('*.in'));assert len(files)==36;dims=[]
    for path in files:
        a,queries=decode(path.read_text());dims.append((len(a),len(queries)))
        assert len((p/'out'/path.with_suffix('.out').name).read_text().splitlines())==len(queries)
    assert (200000,200000) in dims and any(n==1 for n,_ in dims) and any(n&(n-1) for n,_ in dims)
    for seed in [1,2]:
        a,queries=decode((p/'in'/f'max_{seed:02}.in').read_text())
        answer=(p/'out'/f'max_{seed:02}.out').read_text().split()
        if seed==2:assert len(answer)==200000 and set(answer)=={{6:'1',7:'1000000000',9:'2000000000'}[k]}
        elif k==6:assert set(answer)=={'-1'}
        elif k==7:assert set(answer)=={'1'}
        else:assert all(x==('-1' if l==r else '14') for x,(l,r) in zip(answer,queries))
    assert not list(p.rglob('*.html'));audit_statement(p,with_subtask=False)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES);parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args();logging.basicConfig(level=logging.ERROR,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem];sources=[HERE/'oracle_static_three.cpp']
    for problem in problems:
        problem.health_check();problem.generate_params_h()
        sources.extend([problem.basedir/'sol/correct.cpp',problem.checker,problem.verifier])
        sources.extend(problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} static segment tree problems...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(checked_compile,sources):pass
    total=0
    for problem in problems:
        started=time.monotonic();p=problem.basedir;k=int(p.name[7:])
        problem.make_inputs();problem.verify_inputs();problem.make_outputs(True);problem.judge(p/'sol/correct.cpp',{})
        assert problem.check_all_solutions_used();audit(problem,k)
        for test in problem.config['tests']:
            if not test['name'].endswith('.cpp'):continue
            exe=p/'gen'/Path(test['name']).stem
            for seed in range(test['number']):assert run(exe,'',seed)==(p/'in'/f'{exe.name}_{seed:02}.in').read_text()
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text();expected=(p/'out'/path.with_suffix('.out').name).read_text().split()
            assert run(ORACLE,data,k).split()==expected,(path,'independent reference differs')
            if path.stem.startswith(('edge','small','example')):assert brute(k,data)==expected,(path,'direct reference differs')
        count=small_checks(p,k);total+=count;invalid=invalid_inputs(p,k);check_checker(p,k)
        if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: 36 generated tests, {count} exhaustive/random cases, {invalid} invalid inputs; 0.5s limit, checker, samples, upload, reproducibility and hashes OK ({time.monotonic()-started:.1f}s)',flush=True)
    print(f'All static checks passed: {36*len(problems)} generated tests and {total} additional cases; prefix-sum counterexamples verified, no Subtask or HTML.',flush=True)


if __name__=='__main__':main()
