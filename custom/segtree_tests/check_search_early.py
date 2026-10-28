"""Generate and verify eight further SEG1 problems in 100–129, without HTML."""
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
KINDS=[103,104,113,114,115,123,124,125]
NAMES=[f'segtree{k}' for k in KINDS]
ORACLE=HERE/'oracle_search_early'


def encode(k,a,ops=(),b=None,m=None,w=None):
    if k==123:return f'{len(a)} {m} {w}\n'+' '.join(map(str,a))+'\n'
    text=f'{len(a)} {len(ops)}\n'
    text+=(''.join(a) if k in (114,125) else ' '.join(map(str,a)))+'\n'
    if k in (114,125):text+=(''.join(b) if k==114 else ' '.join(map(str,b)))+'\n'
    return text+''.join(' '.join(map(str,op))+'\n' for op in ops)


def decode(k,data):
    lines=data.splitlines();h=list(map(int,lines[0].split()))
    a=list(lines[1]) if k in (114,125) else list(map(int,lines[1].split()))
    assert len(a)==h[0]
    b=(list(lines[2]) if k==114 else list(map(int,lines[2].split()))) if k in (114,125) else None
    if b is not None:assert len(b)==h[0]
    if k==123:assert len(lines)==2;return h,a,b,[]
    ops=[]
    for line in lines[3 if k in (114,125) else 2:]:
        tokens=line.split();t=int(tokens[0])
        if k==114 and t==1:op=(t,int(tokens[1]),int(tokens[2]),tokens[3])
        elif k==125 and t==1:op=(t,int(tokens[1]),tokens[2],int(tokens[3]))
        else:op=tuple(map(int,tokens))
        ops.append(op)
    assert len(ops)==h[1]
    return h,a,b,ops


def brute(k,data):
    h,a,b,ops=decode(k,data);n=len(a);out=[]
    if k==123:
        w=h[2]
        return [str(sorted(a[i:i+w])[(w-1)//2]) for i in range(n-w+1)]
    for op in ops:
        t=op[0]
        if k in (103,124):
            if t in (1,2):a[op[1]-1]+=1 if t==1 else -1;continue
            if k==103:
                best=max(a);out.append(a.index(best)+1 if best else -1)
            else:
                candidates=[i+1 for i,x in enumerate(a) if x>0]
                out.append(candidates[op[1]-1] if len(candidates)>=op[1] else -1)
            continue
        if t==1:
            if k==114:(a if op[1]==1 else b)[op[2]-1]=op[3]
            elif k==125:a[op[1]-1]=op[2];b[op[1]-1]=op[3]
            else:a[op[1]-1]=op[2]
            continue
        if k==104:out.append(next((i+1 for i,x in enumerate(a) if x&op[1]!=op[1]),-1))
        elif k==113:out.append(next((i+1 for i in range(1,n-1) if a[i]>a[i-1] and a[i]>a[i+1]),-1))
        elif k==114:out.append(next((i for i in range(n) if a[i]!=b[i]),n))
        elif k==115:
            maximum=max(a);positions=[i+1 for i,x in enumerate(a) if x==maximum];out.extend([positions[0],positions[-1]])
        elif k==125:
            rank=op[1];found=False
            for i,x in enumerate(b):
                if rank<=x:out.extend([a[i],i+1,rank]);found=True;break
                rank-=x
            if not found:out.append(-1)
    return list(map(str,out))


def check_case(p,k,data):
    run(p/'verifier',data)
    expected=brute(k,data)
    assert run(p/'sol/correct',data).split()==expected,(p,'solution',data,expected)
    assert run(ORACLE,data,k).split()==expected,(p,'independent reference',data,expected)


def queries(k,n):
    if k==103:return [(3,)]
    if k==124:return [(3,rank) for rank in range(1,n+1)]
    if k==104:return [(2,m) for m in [1,2,3,4,5,6,7,1<<19,(1<<20)-1]]
    if k in (113,114,115):return [(2,)]
    if k==125:return [(2,rank) for rank in list(range(1,2*n+2))+[10**18]]
    raise ValueError(k)


def small_checks(p,k):
    count=0
    if k==123:
        for n in range(1,6):
            for initial in itertools.product([1,2,3],repeat=n):
                for w in range(1,n+1):check_case(p,k,encode(k,initial,m=3,w=w));count+=1
    elif k in (103,124):
        for n in range(1,5):
            for initial in itertools.product([0,1,2],repeat=n):
                q=queries(k,n);ops=list(q)
                for i,x in enumerate(initial,1):
                    for _ in range(x):ops.append((2,i));ops.extend(q)
                    for op in [(1,i),(1,i),(2,i),(2,i),(1,i)]:ops.append(op);ops.extend(q)
                for i in range(1,n+1):ops.append((2,i));ops.extend(q)
                check_case(p,k,encode(k,initial,ops));count+=1
    elif k==114:
        for n in range(1,5):
            for a in itertools.product('ab',repeat=n):
                for b in itertools.product('ab',repeat=n):
                    ops=[(2,)]
                    for which in [1,2]:
                        for i in range(1,n+1):
                            for c in 'ab':ops.extend([(1,which,i,c),(2,)])
                    check_case(p,k,encode(k,a,ops,b=b));count+=1
    elif k==125:
        for n in range(1,4):
            for a in itertools.product('ab',repeat=n):
                for b in itertools.product([0,1,2],repeat=n):
                    q=queries(k,n);ops=list(q)
                    for i in range(1,n+1):
                        for c in 'ab':
                            for x in [0,1,2]:ops.append((1,i,c,x));ops.extend(q)
                    check_case(p,k,encode(k,a,ops,b=b));count+=1
    else:
        alphabet=[0,1,2,7] if k==104 else [-1,0,1]
        for n in range(1,6 if k==113 else 5):
            for initial in itertools.product(alphabet,repeat=n):
                q=queries(k,n);ops=list(q)
                for i in range(1,n+1):
                    for x in alphabet:ops.append((1,i,x));ops.extend(q)
                check_case(p,k,encode(k,initial,ops));count+=1
    rng=random.Random(20261027+k)
    values=[0,1,2,3,7,10**9]
    if k in (113,115):values=[-10**9,-7,-1,0,1,7,10**9]
    if k==104:values=[0,1,2,3,7,1<<19,(1<<20)-1]
    for _ in range(150):
        n=rng.randint(1,35)
        if k==123:
            m=rng.randint(1,35);a=rng.choices(range(1,m+1),k=n)
            check_case(p,k,encode(k,a,m=m,w=rng.randint(1,n)));count+=1;continue
        a=rng.choices(list('abcxyz') if k in (114,125) else values,k=n)
        b=rng.choices(list('abcxyz') if k==114 else values,k=n) if k in (114,125) else None
        state=list(a);ops=[]
        for _ in range(rng.randint(1,200)):
            update=rng.randrange(2)
            if k in (103,124):
                if update:
                    i=rng.randrange(n);t=rng.randint(1,2)
                    if state[i]==0:t=1
                    state[i]+=1 if t==1 else -1;op=(t,i+1)
                else:op=(3,) if k==103 else (3,rng.randint(1,n))
            elif update:
                i=rng.randint(1,n)
                if k==114:op=(1,rng.randint(1,2),i,rng.choice('abcxyz'))
                elif k==125:op=(1,i,rng.choice('abcxyz'),rng.choice(values))
                else:op=(1,i,rng.choice(values))
            elif k==104:op=(2,rng.choice([1,2,3,7,1<<19,(1<<20)-1]))
            elif k==125:op=(2,rng.choice([1,2,7,10**9,10**9+1,2147483648,10**18]))
            else:op=(2,)
            ops.append(op)
        check_case(p,k,encode(k,a,ops,b=b));count+=1
    extras=[]
    if k==123:
        extras=[encode(k,[1]*20,m=1,w=2),encode(k,[1,6,1,6,1,6],m=6,w=4),encode(k,[6,5,4,3,2,1],m=6,w=6)]
    else:
        n=1001
        if k==103:a=[0]*n;ops=[(1,450),(1,451),(3,),(2,450),(3,),(1,450),(3,)];b=None
        elif k==124:a=[0]*n;ops=[(1,450),(1,451),(1,450),(3,2),(2,450),(3,2),(2,450),(3,1)];b=None
        elif k==104:a=[1048575]*n;ops=[(1,450,524287),(2,1<<19),(1,450,1048575),(1,451,0),(2,1),(2,1<<19)];b=None
        elif k==113:a=[0]*n;ops=[(1,450,1),(2,),(1,451,1),(2,),(1,450,0),(2,),(1,452,2),(2,)];b=None
        elif k==114:a=['a']*n;b=['a']*n;ops=[(1,2,450,'z'),(2,),(1,1,450,'z'),(2,),(1,1,451,'z'),(2,)]
        elif k==115:a=[-10**9]*n;ops=[(2,),(1,450,-1),(1,451,-1),(2,),(1,450,-10**9),(2,)];b=None
        else:
            a=['a']*n;b=[0]*n;ops=[(1,450,'z',10**9),(1,451,'z',10**9),(2,10**9),(2,10**9+1),(2,2*10**9),(2,2*10**9+1),(1,450,'a',0),(2,1)]
            extras.append(encode(k,['a','a','z'],[(2,2147483648),(2,3000000000),(2,3000000001),(1,2,'b',0),(2,1000000001)],b=[10**9]*3))
        extras.append(encode(k,a,ops,b=b))
    for data in extras:check_case(p,k,data);count+=1
    return count


def check_invalid_input(p,k):
    valid=(p/'gen/example_00.in').read_text();h,a,b,ops=decode(k,valid)
    bad=[valid+'0\n','\n'.join(valid.splitlines()[:-1])+'\n'];n=len(a)
    if k==123:
        bad += [f'{nn} {mm} {ww}\n' for nn,mm,ww in [(0,1,1),(200001,1,1),(1,0,1),(1,200001,1),(1,1,0),(1,1,2)]]
        bad += [encode(k,[0],m=1,w=1),encode(k,[2],m=1,w=1)]
    else:
        bad += [f'{nn} {qq}\n' for nn,qq in [(0,1),(200001,1),(1,0),(1,200001)]]
        def enc(oo,aa=a,bb=b):return encode(k,aa,oo,b=bb)
        bad += [enc([(0,)]),enc([(4 if k in (103,124) else 3,)]),enc([(1,)])]
        if k in (103,124):
            extra=[(1,0),(1,n+1),(2,0),(2,n+1),(1,1,0)]
            if k==103:extra += [(3,1)]
            else:extra += [(3,0),(3,n+1),(3,)]
            bad.append(encode(k,[0],[(2,1)]))
        elif k==104:extra=[(1,0,0),(1,n+1,0),(1,1,-1),(1,1,1<<20),(2,0),(2,1<<20),(2,),(2,1,1)]
        elif k in (113,115):extra=[(1,0,0),(1,n+1,0),(1,1,-10**9-1),(1,1,10**9+1),(2,1)]
        elif k==114:
            extra=[(1,0,1,'a'),(1,3,1,'a'),(1,1,0,'a'),(1,2,n+1,'a'),(1,1,1,'A'),(1,1,1,'aa'),(1,1,1),(2,1)]
        else:extra=[(1,0,'a',0),(1,n+1,'a',0),(1,1,'A',0),(1,1,'aa',0),(1,1,'a',-1),(1,1,'a',10**9+1),(1,1,'a'),(2,0),(2,10**18+1),(2,),(2,1,1)]
        bad.extend(enc([op]) for op in extra)
        if k in (114,125):
            bad += [enc(ops,['A']+a[1:]),enc(ops,a[:-1]),enc(ops,a+['a'])]
            if k==114:bad += [enc(ops,bb=['A']+b[1:]),enc(ops,bb=b[:-1]),enc(ops,bb=b+['a'])]
            else:
                for x in [-1,10**9+1]:bad.append(enc(ops,bb=[x]+b[1:]))
        else:
            low=-10**9 if k in (113,115) else 0;high=(1<<20)-1 if k==104 else 10**9
            for x in [low-1,high+1]:bad.append(enc(ops,[x]+a[1:]))
    for data in bad:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(p,'accepted invalid input',data)
    return len(bad)


def check_checker(p,k):
    with tempfile.TemporaryDirectory() as directory:
        directory=Path(directory);inp,actual,ans=[directory/name for name in ('in','actual','ans')]
        for case in ['example_00','example_01','edge_10']:
            inp.write_text((p/'in'/f'{case}.in').read_text());good=(p/'out'/f'{case}.out').read_text();ans.write_text(good);tokens=good.split()
            tests=[(good,True),(' \n'+' \t'.join(tokens)+'\n',True),(good+'0\n',False),(good+'garbage\n',False)]
            if tokens:
                tests += [('',False),(' '.join(tokens[:-1]),False),('x\n',False)]
                for i in range(min(len(tokens),6) if k==125 else 1):
                    wrong=list(tokens);wrong[i]=('b' if tokens[i]=='a' else 'a') if tokens[i].isalpha() else str(int(tokens[i])+1)
                    tests.append((' '.join(wrong),False))
                if k==125:
                    tests += [('A '+' '.join(tokens[1:]),False),(' '.join(tokens)+' x',False)]
            for data,accepted in tests:
                actual.write_text(data);r=subprocess.run([str(p/'checker'),str(inp),str(actual),str(ans)],capture_output=True)
                assert (r.returncode==0)==accepted,(p,'checker',data,r.stderr)


def audit_coverage(problem,k):
    p=problem.basedir;files=sorted((p/'in').glob('*.in'));assert len(files)==36
    template=toml.load(ROOT/'custom/segtree000/info.toml')['upload']
    assert problem.config['upload']==template and problem.config['timelimit']==template['time_limit']==0.5
    dims=[]
    for path in files:
        h,a,b,ops=decode(k,path.read_text());dims.append((h[0],0 if k==123 else h[1]))
    assert (200000,0 if k==123 else 200000) in dims
    assert any(n==1 for n,_ in dims) and any(n&(n-1) for n,_ in dims)
    if k!=123:assert (p/'out/edge_10.out').read_text()==''
    answer=(p/'out/max_01.out').read_text().split()
    if k in (103,104,115,124):assert set(answer)=={'200000'}
    if k in (113,114):assert set(answer)=={'199999'}
    if k==123:assert len(answer)==100001 and set(answer)=={'1'}
    if k==125:assert answer[:3]==['z','200000','1000000000'] and len(answer)==600000
    assert not list(p.rglob('*.html'))
    for md in p.glob('*.md'):assert all(c>=32 or c in (9,10) for c in md.read_bytes()),md


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args();logging.basicConfig(level=logging.ERROR,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem];sources=[HERE/'oracle_search_early.cpp']
    for problem in problems:
        problem.health_check();problem.generate_params_h()
        sources.extend([problem.basedir/'sol/correct.cpp',problem.checker,problem.verifier])
        sources.extend(problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} SEG1 problems in 100–129...',flush=True)
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
    print(f'All early SEG1 checks passed: {36*len(problems)} generated tests and {total} additional cases; no Subtask or HTML.',flush=True)


if __name__=='__main__':main()
