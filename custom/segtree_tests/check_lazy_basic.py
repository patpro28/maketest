"""Generate and verify six basic lazy/point-query problems without HTML."""
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
KINDS=list(range(200,206))
NAMES=[f'segtree{k}' for k in KINDS]
ORACLE=HERE/'oracle_lazy_basic'
LIMITS={200:(-10**9,10**9),201:(0,10**9),202:(0,10**9),203:(0,10**9),204:(1,10**9),205:(1,3)}


def decode(k,data):
    lines=data.splitlines();n,q=map(int,lines[0].split());a=list(map(int,lines[1].split()))
    ops=[tuple(map(int,line.split())) for line in lines[2:]]
    assert len(a)==n and len(ops)==q
    assert all(len(op)==(2 if op[0]==2 else 5 if k==205 else 4) for op in ops)
    return a,ops

def encode(a,ops):return f'{len(a)} {len(ops)}\n'+' '.join(map(str,a))+'\n'+''.join(' '.join(map(str,op))+'\n' for op in ops)
def brute(k,data):
    lines=data.splitlines();n,q=map(int,lines[0].split());a=list(map(int,lines[1].split()));out=[]
    assert len(a)==n and len(lines)==q+2
    for line in lines[2:]:
        op=list(map(int,line.split()))
        if op[0]==2:out.append(str(a[op[1]-1]));continue
        _,l,r,x,*other=op
        for i in range(l-1,r):
            if k==200:a[i]+=x
            elif k==201:a[i]=x
            elif k==202:a[i]=max(a[i],x)
            elif k==203:a[i]=min(a[i],x)
            elif k==204:
                import math
                a[i]=math.gcd(a[i],x)
            else:
                y=other[0];a[i]=y if a[i]==x else x if a[i]==y else a[i]
    return out


def check_case(p,k,data):
    run(p/'verifier',data);expected=brute(k,data)
    assert run(p/'sol/correct',data).split()==expected,(p,'solution',data,expected)
    assert run(ORACLE,data,k).split()==expected,(p,'independent reference',data,expected)


def small_checks(p,k):
    count=0
    alphabet=[-1,0,1] if k==200 else [0,1,2] if k==201 else [0,1,3] if k in (202,203) else [1,6,10] if k==204 else [1,2,3]
    choices=[-2,0,3] if k==200 else [0,1,2] if k==201 else [0,1,3] if k in (202,203) else [1,2,3,6,10,15] if k==204 else list(itertools.product(range(1,4),repeat=2))
    def update(l,r,x):return (1,l,r,*x) if k==205 else (1,l,r,x)
    for n in range(1,5):
        queries=[(2,i) for i in range(1,n+1)]
        for initial in itertools.product(alphabet,repeat=n):
            ops=list(queries)
            for l in range(1,n+1):
                for r in range(l,n+1):
                    for x in choices:ops.append(update(l,r,x));ops.extend(queries)
            check_case(p,k,encode(initial,ops));count+=1
    pairs=[(1,2),(2,3),(1,3)] if k==205 else choices[:3]
    updates=[update(l,r,x) for l,r in [(1,3),(1,1),(2,3),(1,2)] for x in pairs]
    for first in updates:
        for second in updates:
            ops=[first,second]+[(2,i) for i in range(1,4)]+[first]+[(2,i) for i in range(1,4)]
            check_case(p,k,encode([alphabet[0],alphabet[1],alphabet[2]],ops));count+=1
    if k==205:
        for sequence in itertools.product([(1,2),(2,3),(1,3)],repeat=5):
            ops=[(1,1,3,*pair) for pair in sequence]+[(2,1),(2,2),(2,3)]
            check_case(p,k,encode([1,2,3],ops));count+=1
    rng=random.Random(20261101+k)
    low,high=LIMITS[k]
    pool=[x for x in [-10**9,-7,-1,0,1,2,3,6,10,12,15,30,999999937,10**9] if low<=x<=high]
    for trial in range(200):
        n=rng.randint(1,35);a=rng.choices(pool,k=n);ops=[]
        for _ in range(rng.randint(1,200)):
            if rng.randrange(100)<[10,50,90][trial%3]:
                l,r=sorted([rng.randint(1,n),rng.randint(1,n)])
                x=(rng.randint(1,3),rng.randint(1,3)) if k==205 else rng.choice(pool)
                ops.append(update(l,r,x))
            else:ops.append((2,rng.randint(1,n)))
        check_case(p,k,encode(a,ops));count+=1
    n=1001;a=[alphabet[0]]*n;ops=[]
    q=[(2,i) for i in [1,449,450,451,899,900,901,n]]
    for l,r in [(1,n),(450,451),(1,450),(451,900),(899,n),(1,n)]:
        for x in choices:ops.append(update(l,r,x));ops.extend(q)
    check_case(p,k,encode(a,ops));count+=1
    if k==200:a=[10**9];ops=[(1,1,1,10**9)]*3+[(2,1),(1,1,1,-10**9),(2,1)]
    elif k==201:a=[9]*5;ops=[(1,1,5,0),(1,2,4,7),(1,3,3,0),(2,3),(2,1),(2,2),(1,1,5,3),(2,3)]
    elif k==202:a=[0,10**9,2];ops=[(1,1,3,7),(1,2,3,0),(2,1),(2,2),(1,1,3,6),(2,3)]
    elif k==203:a=[0,10**9,2];ops=[(1,1,3,7),(1,2,3,10**9),(2,2),(1,1,3,0),(2,1),(2,3)]
    elif k==204:a=[10**9,999999937,30];ops=[(1,1,3,6),(1,2,3,10),(2,1),(2,2),(2,3),(1,1,3,1),(2,1)]
    else:a=[1,2,3];ops=[(1,1,3,1,2),(1,2,2,2,3),(1,1,3,2,3),(2,1),(2,2),(2,3),(1,1,3,3,3),(2,1)]
    check_case(p,k,encode(a,ops));count+=1
    return count


def invalid_inputs(p,k):
    valid=(p/'gen/example_00.in').read_text();a,ops=decode(k,valid);n=len(a);low,high=LIMITS[k]
    bad=[valid+'0\n','\n'.join(valid.splitlines()[:-1])+'\n']
    bad += [f'{nn} {qq}\n' for nn,qq in [(0,1),(200001,1),(1,0),(1,200001)]]
    def enc(operations,initial=a):return encode(initial,operations)
    def up(l,r,x):return (1,l,r,x,1) if k==205 else (1,l,r,x)
    bad += [enc([(0,)]),enc([(3,)]),enc([(1,)]),enc([(2,)]),enc([(2,0)]),enc([(2,n+1)]),enc([(2,1,1)]),
            enc([up(0,n,low)]),enc([up(1,n+1,low)]),enc([up(n,1,low)]),enc([up(1,n,low-1)]),enc([up(1,n,high+1)]),
            enc(ops,[low-1]+a[1:]),enc(ops,[high+1]+a[1:]),enc([(1,1,n,low,1,1)]),enc([(1,1,n)])]
    if k==205:bad += [enc([(1,1,n,1,0)]),enc([(1,1,n,1,4)]),enc([(1,1,n,1)])]
    for data in bad:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(p,'accepted invalid input',data)
    return len(bad)


def audit(problem,k):
    p=problem.basedir
    template=toml.load(ROOT/'custom/segtree000/info.toml')['upload'];template['types']=['ds_segment_tree']
    assert problem.config['upload']==template and problem.config['timelimit']==template['time_limit']==0.5
    assert problem.config['params']['VALUE_MIN']==LIMITS[k][0] and problem.config['params']['VALUE_MAX']==LIMITS[k][1]
    files=sorted((p/'in').glob('*.in'));assert len(files)==36;dims=[]
    for path in files:
        a,ops=decode(k,path.read_text());dims.append((len(a),len(ops)))
        assert len((p/'out'/path.with_suffix('.out').name).read_text().splitlines())==sum(op[0]==2 for op in ops)
    assert (200000,200000) in dims and any(n==1 for n,_ in dims) and any(n&(n-1) for n,_ in dims)
    assert (p/'out/edge_10.out').read_text()==''
    expected={200:'1000000000',201:'0',202:'777',203:'777',204:'2',205:'2'}[k]
    late=(p/'out/max_01.out').read_text().split();assert len(late)==199999 and set(late)=={expected}
    if k==200:assert (p/'out/max_02.out').read_text()=='200000000000000\n'
    assert len((p/'out/max_02.out').read_text().splitlines())==1
    assert len((p/'out/max_05.out').read_text().splitlines())==1
    assert not list(p.rglob('*.html'));audit_statement(p,with_subtask=False)


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES);parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args();logging.basicConfig(level=logging.ERROR,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem];sources=[HERE/'oracle_lazy_basic.cpp']
    for problem in problems:
        problem.health_check();problem.generate_params_h()
        sources.extend([problem.basedir/'sol/correct.cpp',problem.checker,problem.verifier])
        sources.extend(problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} basic lazy segment tree problems...',flush=True)
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
            if path.stem.startswith(('edge','small','example')):assert brute(k,data)==expected,(path,'direct array simulation differs')
        count=small_checks(p,k);total+=count;invalid=invalid_inputs(p,k);check_checker(p,k)
        if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: 36 generated tests, {count} exhaustive/random cases, {invalid} invalid inputs; 0.5s limit, checker, samples, upload, reproducibility and hashes OK ({time.monotonic()-started:.1f}s)',flush=True)
    print(f'All basic lazy checks passed: {36*len(problems)} generated tests and {total} additional cases; no Subtask or HTML.',flush=True)


if __name__=='__main__':main()
