"""Generate and verify five SEG1 problems in 110–129, without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import logging
from pathlib import Path
import random
import subprocess
import sys
import tempfile
import time

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[1]
sys.path.insert(0,str(HERE));sys.path.insert(0,str(ROOT))
import toml
from problem import Problem
from check import audit_statement,run
from check_foundations import checked_compile
KINDS=[116,126,127,128,129]
NAMES=[f'segtree{k}' for k in KINDS]
ORACLE=HERE/'oracle_search_five'


def encode(k,a,ops,b=None,n=None):
    n=n if k==128 else len(a)
    data=f'{n} {len(ops)}\n'
    if k!=128:data+=' '.join(map(str,a))+'\n'
    if k==116:data+=' '.join(map(str,b))+'\n'
    return data+''.join(' '.join(map(str,op))+'\n' for op in ops)

def decode(k,data):
    lines=data.splitlines();n,q=map(int,lines[0].split());offset=1
    a=[];b=None
    if k!=128:a=list(map(int,lines[offset].split()));offset+=1
    if k==116:b=list(map(int,lines[offset].split()));offset+=1
    ops=[tuple(map(int,line.split())) for line in lines[offset:]]
    assert len(ops)==q
    if k!=128:assert len(a)==n
    if b is not None:assert len(b)==n
    return n,a,b,ops

def brute(k,data):
    n,a,b,ops=decode(k,data);out=[]
    if k==128:a=list(range(1,n+1))
    for op in ops:
        t=op[0]
        if k==116:
            if t==1:b[op[1]-1]=op[2]
            else:out.append(next((i+1 for i in range(n-1) if b[i]>a[i+1]),-1))
        elif k==126:
            if t==1:a[op[1]-1]=op[2]
            else:
                starts=[i+1 for i in range(n) if i==0 or a[i]!=a[i-1]]
                out.append(starts[op[1]-1] if len(starts)>=op[1] else -1)
        elif k==127:
            if t in (1,2):a[op[1]-1]+=1 if t==1 else -1
            else:
                missing=[i+1 for i,x in enumerate(a) if x==0]
                out.append(missing[op[1]-1] if len(missing)>=op[1] else -1)
        elif k==128:
            if t==1:a.remove(op[1]);a.append(op[1])
            else:out.append(a[op[1]-1])
        else:
            if t==1:a[op[1]-1]=op[2];continue
            rank=op[1];found=False
            for i,c in enumerate(a,1):
                if rank>c*(c-1)//2:rank-=c*(c-1)//2;continue
                for u in range(1,c):
                    if rank>c-u:rank-=c-u
                    else:out.extend([i,u,u+rank]);found=True;break
                break
            if not found:out.append(-1)
    return list(map(str,out))


def check_case(p,k,data):
    run(p/'verifier',data)
    expected=brute(k,data)
    assert run(p/'sol/correct',data).split()==expected,(p,'solution',data,expected)
    assert run(ORACLE,data,k).split()==expected,(p,'independent reference',data,expected)


def small_checks(p,k):
    count=0
    def check(a,ops,b=None,n=None):
        nonlocal count
        check_case(p,k,encode(k,a,ops,b=b,n=n));count+=1
    if k==116:
        for n in range(1,6):
            a=list(range(1,n+1))
            for offset in itertools.product([-1,0,1],repeat=n):
                b=[max(a[i],(a[i+1] if i+1<n else a[i])+offset[i]) for i in range(n)]
                ops=[(2,)]
                for i in range(n):
                    for x in [a[i],a[min(n-1,i+1)],a[min(n-1,i+1)]+1,10**9]:ops.extend([(1,i+1,x),(2,)])
                check(a,ops,b)
    elif k==126:
        for n in range(1,6):
            for a in itertools.product([1,2,3],repeat=n):
                queries=[(2,r) for r in range(1,n+1)];ops=list(queries)
                for i in range(1,n+1):
                    for c in [1,2,3]:ops.append((1,i,c));ops.extend(queries)
                check(a,ops)
    elif k==127:
        for n in range(1,5):
            for a in itertools.product([0,1,2],repeat=n):
                queries=[(3,r) for r in range(1,n+1)];ops=list(queries)
                for i,x in enumerate(a,1):
                    for _ in range(x):ops.append((2,i));ops.extend(queries)
                    for t in [1,1,2,2,1,2]:ops.append((t,i));ops.extend(queries)
                check(a,ops)
    elif k==128:
        for n in range(1,6):
            for moves in itertools.product(range(1,n+1),repeat=3):
                queries=[(2,r) for r in range(1,n+1)];ops=list(queries)
                for x in moves:ops.append((1,x));ops.extend(queries)
                check([],ops,n=n)
    else:
        for n in range(1,5):
            for a in itertools.product([0,1,2,3],repeat=n):
                queries=[(2,r) for r in range(1,sum(x*(x-1)//2 for x in a)+2)];ops=list(queries)
                for i in range(1,n+1):
                    for x in [0,1,2,4]:ops.append((1,i,x));ops.extend([(2,r) for r in range(1,6*n+2)])
                check(a,ops)
        for c in range(2,26):check([c],[(2,r) for r in range(1,c*(c-1)//2+2)])
    rng=random.Random(20261031+k)
    for _ in range(180):
        n=rng.randint(1,35);ops=[]
        if k==116:a=sorted(rng.sample(range(1,200),n));b=[rng.randint(x,1000) for x in a]
        elif k==126:a=rng.choices([1,2,3,10**9],k=n);b=None
        elif k==127:a=rng.choices([0,1,2,3,10**9],k=n);b=None
        elif k==129:a=rng.choices([0,1,2,3,4,8],k=n);b=None
        else:a=[];b=None
        state=list(a)
        for _ in range(rng.randint(1,200)):
            i=rng.randint(1,n)
            if rng.randrange(2):
                if k==116:op=(1,i,rng.choice([a[i-1],10**9,rng.randint(a[i-1],1000)]))
                elif k==126:op=(1,i,rng.choice([1,2,3,10**9]))
                elif k==127:
                    t=1 if state[i-1]==0 or rng.randrange(2) else 2
                    state[i-1]+=1 if t==1 else -1;op=(t,i)
                elif k==128:op=(1,i)
                else:op=(1,i,rng.randint(0,8));state[i-1]=op[2]
            elif k==116:op=(2,)
            elif k in (126,128):op=(2,rng.randint(1,n))
            elif k==127:op=(3,rng.randint(1,n))
            else:
                total=sum(x*(x-1)//2 for x in state)
                op=(2,rng.choice([1,max(1,total),total+1,10**18,rng.randint(1,max(1,total))]))
            ops.append(op)
        check(a,ops,b,n)
    # Boundaries around split points and 64-bit ranks, outside the exhaustive alphabets.
    if k==116:check([1,2,10**9],[(2,),(1,1,2),(2,),(1,1,3),(2,),(1,3,10**9),(2,)],b=[1,10**9,10**9])
    if k==126:check([1]*1001,[(2,1),(2,2),(1,450,2),(2,2),(2,3),(1,451,2),(2,3),(1,450,1),(2,2),(1,451,1),(2,2)])
    if k==127:check([10**9,0,0,1],[(1,1),(3,1),(1,2),(3,1),(2,2),(3,1),(2,4),(3,3),(3,4)])
    if k==128:check([],[(1,1)]*200+[(2,1),(2,2),(2,3),(1,3),(2,1),(1,3),(2,3)],n=3)
    if k==129:
        a=[10000]*100;total=sum(x*(x-1)//2 for x in a)
        ranks=[1,9999,10000,49995000,49995001,2147483648,total,total+1,10**18]
        for u in [1,2,17,4999,5000,9998,9999]:
            f=u*(20000-u-1)//2;ranks.extend([f-1,f,f+1])
        check(a,[(2,r) for r in ranks]+[(1,1,0),(2,1),(1,100,1),(2,total)])
        check([0,1,2],[(2,1),(1,3,0),(2,1),(1,1,10000),(2,49995000),(1,1,1),(2,1)])
    return count


def check_invalid_input(p,k):
    valid=(p/'gen/example_00.in').read_text();n,a,b,ops=decode(k,valid)
    bad=[valid+'0\n','\n'.join(valid.splitlines()[:-1])+'\n']
    bad += [f'{nn} {qq}\n' for nn,qq in [(0,1),(200001,1),(1,0),(1,200001)]]
    def enc(oo,aa=a,bb=b,nn=n):return encode(k,aa,oo,b=bb,n=nn)
    bad += [enc([(0,)]),enc([(4 if k==127 else 3,)]),enc([(1,)])]
    if k==116:
        extra=[(1,0,1),(1,n+1,10**9),(1,1,a[0]-1),(1,1,10**9+1),(2,1)]
        bad += [enc(ops,aa=[0]+a[1:]),enc(ops,aa=[a[1],a[1]]+a[2:]),enc(ops,aa=list(reversed(a))),enc(ops,bb=[a[0]-1]+b[1:]),enc(ops,bb=[10**9+1]+b[1:])]
    elif k==126:
        extra=[(1,0,1),(1,n+1,1),(1,1,0),(1,1,10**9+1),(2,0),(2,n+1),(2,1,1),(2,)]
        bad += [enc(ops,aa=[0]+a[1:]),enc(ops,aa=[10**9+1]+a[1:])]
    elif k==127:
        extra=[(1,0),(1,n+1),(2,0),(2,n+1),(3,0),(3,n+1),(3,1,1),(3,)]
        bad += [enc(ops,aa=[-1]+a[1:]),enc(ops,aa=[10**9+1]+a[1:]),encode(k,[0],[(2,1)]),encode(k,[1],[(2,1),(2,1)])]
    elif k==128:extra=[(1,0),(1,n+1),(2,0),(2,n+1),(1,1,1),(2,1,1),(2,)]
    else:
        extra=[(1,0,0),(1,n+1,0),(1,1,-1),(1,1,10001),(2,0),(2,10**18+1),(2,1,1),(2,)]
        bad += [enc(ops,aa=[-1]+a[1:]),enc(ops,aa=[10001]+a[1:])]
    bad += [enc([op]) for op in extra]
    for data in bad:
        r=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert r.returncode!=0,(p,'accepted invalid input',data)
    return len(bad)


def check_checker(p,k):
    with tempfile.TemporaryDirectory() as directory:
        d=Path(directory);inp,actual,ans=[d/name for name in ('in','actual','ans')]
        for case in ['example_00','example_01','edge_10']:
            inp.write_text((p/'in'/f'{case}.in').read_text());good=(p/'out'/f'{case}.out').read_text();ans.write_text(good);tokens=good.split()
            tests=[(good,True),(' \n'+' \t'.join(tokens)+'\n',True),(good+'0\n',False),(good+'x\n',False)]
            if tokens:
                tests += [('',False),(' '.join(tokens[:-1]),False),('x\n',False)]
                for i in range(min(len(tokens),9)):
                    wrong=list(tokens);wrong[i]=str(int(tokens[i])+1);tests.append((' '.join(wrong),False))
            for data,accepted in tests:
                actual.write_text(data);r=subprocess.run([str(p/'checker'),str(inp),str(actual),str(ans)],capture_output=True)
                assert (r.returncode==0)==accepted,(p,'checker',data,r.stderr)


def audit_coverage(problem,k):
    p=problem.basedir;files=sorted((p/'in').glob('*.in'));assert len(files)==36
    template=toml.load(ROOT/'custom/segtree000/info.toml')['upload']
    template['types']=['ds_segment_tree']
    assert problem.config['upload']==template and problem.config['timelimit']==template['time_limit']==0.5
    dims=[]
    for path in files:
        n,a,b,ops=decode(k,path.read_text());dims.append((n,len(ops)))
    assert (200000,200000) in dims
    assert any(n==1 for n,_ in dims) and any(n&(n-1) for n,_ in dims)
    assert (p/'out/edge_10.out').read_text()==''
    answer=(p/'out/max_01.out').read_text().split()
    if k==116:assert len(answer)==200000 and set(answer)=={'199999'}
    if k in (126,127,128):assert len(answer)==200000 and set(answer)=={'200000'}
    if k==129:assert len(answer)==600000 and answer==['200000','9999','10000']*200000
    assert not list(p.rglob('*.html'))
    for md in p.glob('*.md'):assert all(c>=32 or c in (9,10) for c in md.read_bytes()),md


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args();logging.basicConfig(level=logging.ERROR,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem];sources=[HERE/'oracle_search_five.cpp']
    for problem in problems:
        problem.health_check();problem.generate_params_h()
        sources.extend([problem.basedir/'sol/correct.cpp',problem.checker,problem.verifier])
        sources.extend(problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} SEG1 problems in 110–129...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(checked_compile,sources):pass
    total=0
    for problem in problems:
        started=time.monotonic();p=problem.basedir;k=int(p.name[7:])
        problem.make_inputs();problem.verify_inputs();problem.make_outputs(True);problem.judge(p/'sol/correct.cpp',{})
        assert problem.check_all_solutions_used();audit_statement(p,with_subtask=False);audit_coverage(problem,k)
        for test in problem.config['tests']:
            if not test['name'].endswith('.cpp'):continue
            exe=p/'gen'/Path(test['name']).stem
            for seed in range(test['number']):assert run(exe,'',seed)==(p/'in'/f'{exe.name}_{seed:02}.in').read_text()
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text();expected=(p/'out'/path.with_suffix('.out').name).read_text().split()
            assert run(ORACLE,data,k).split()==expected,(path,'independent reference differs')
            if path.stem.startswith(('edge','small','example')):assert brute(k,data)==expected,(path,'scan reference differs')
        count=small_checks(p,k);total+=count;invalid=check_invalid_input(p,k);check_checker(p,k)
        if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: 36 generated tests, {count} exhaustive/random cases, {invalid} invalid inputs; 0.5s limit, checker, samples, upload, reproducibility, hashes OK ({time.monotonic()-started:.1f}s)',flush=True)
    print(f'All five SEG1 checks passed: {36*len(problems)} generated tests and {total} additional cases; no Subtask or HTML.',flush=True)


if __name__=='__main__':main()
