"""Generate and verify the third batch of ten SEG1 problems, without HTML."""
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

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE)); sys.path.insert(0, str(ROOT))
import toml
from problem import Problem
from check import audit_statement, run
from check_foundations import checked_compile
from check_remaining import check_checker
KINDS = [102,112,122,132,162,173,174,182,192,193]
NAMES = [f'segtree{k}' for k in KINDS]
ORACLE = HERE / 'oracle_search_next'


def encode(k, a, ops=(), c=5):
    if k == 122: return f'{len(a)}\n' + ' '.join(map(str,a)) + '\n'
    header = f'{c} {len(a)} {len(ops)}' if k == 193 else f'{len(a)} {len(ops)}'
    line = ''.join(a) if k == 174 else ' '.join(map(str,a))
    return header + '\n' + line + '\n' + ''.join(' '.join(map(str,op))+'\n' for op in ops)


def decode(k,data):
    lines = data.splitlines(); h = list(map(int,lines[0].split()))
    a = list(lines[1]) if k == 174 else list(map(int,lines[1].split()))
    n = h[1] if k == 193 else h[0]
    assert len(a) == n
    ops = [tuple(line.split()) if k == 174 else tuple(map(int,line.split())) for line in lines[2:]]
    if k == 174: ops = [(int(t),int(i),x if t=='1' else int(x)) for t,i,x in ops]
    assert (not ops and len(h)==1) if k==122 else len(ops)==h[-1]
    return h,a,ops


def brute(k,data):
    h,a,ops = decode(k,data); n=len(a); out=[]
    if k == 122:
        remaining=list(range(1,n+1));answer=[0]*n
        for i in range(n-1,-1,-1):answer[i]=remaining.pop(i-a[i])
        return list(map(str,answer))
    for op in ops:
        t=op[0]
        if k==192:
            p=op[1]-1
            if t==2:a[p]=0;continue
            answer=next((j for j in list(range(p,n))+list(range(p)) if a[j]==0),-1)
            out.append(answer+1 if answer!=-1 else -1)
            if answer!=-1:a[answer]=1
            continue
        if k==193:
            x=op[1]
            if t==1:a.append(x);continue
            available=[v for v in a if v>=x]
            answer=min(available) if available else -1;out.append(answer)
            if answer!=-1:a[a.index(answer)]-=x
            continue
        if t==1:
            i=op[1]-1
            a[i]=1-a[i] if k==112 else op[2]
            continue
        if k==102:answer=next((i+1 for i,x in enumerate(a) if x&op[1]),-1)
        elif k==112:
            p=op[1];candidates=[i+1 for i,x in enumerate(a) if x]
            answer=min(candidates,key=lambda i:(abs(i-p),i)) if candidates else -1
        elif k==132:
            total=sum(a);answer=(-1,-1);prefix=[0]
            for x in a:prefix.append(prefix[-1]+x)
            for p in range(1,n-1):
                for q in range(p+1,n):
                    if prefix[p]*3==total and prefix[q]*3==2*total:
                        answer=(p,q);break
                if answer!=(-1,-1):break
            out.extend(answer);continue
        elif k==162:
            _,l,r,d=op;answer=next((i+1 for i in range(l-1,r) if a[i]%d),-1)
        elif k==173:
            _,l,b=op;value=1;answer=l-1
            for i in range(l-1,n):
                value=math.lcm(value,a[i])
                if value>b:break
                answer=i+1
        elif k==174:
            _,l,limit=op;seen=set();answer=l-1
            for i in range(l-1,n):
                seen.add(a[i])
                if len(seen)>limit:break
                answer=i+1
        elif k==182:
            _,l,s,g=op;total=value=0;answer=-1
            for i in range(l-1,n):
                total+=a[i];value=math.gcd(value,a[i])
                if total>=s and value<=g:answer=i+1;break
        else:raise ValueError(k)
        out.append(answer)
    return list(map(str,out))


def check_case(p,k,data,expected=None):
    run(p/'verifier',data)
    scanned=brute(k,data)
    if expected is not None: assert scanned==list(map(str,expected)),(p,'scan reference',data)
    expected=scanned
    assert run(p/'sol/correct',data).split()==expected,(p,'solution',data,expected)
    assert run(ORACLE,data,k).split()==expected,(p,'independent reference',data,expected)


def queries(k,n):
    if k==102:return [(2,m) for m in range(1,16)]
    if k==112:return [(2,p) for p in range(1,n+1)]
    if k==132:return [(2,)]
    if k==162:return [(2,l,r,d) for l in range(1,n+1) for r in range(l,n+1) for d in [1,2,3,4,7]]
    if k==173:return [(2,l,b) for l in range(1,n+1) for b in [1,2,3,4,6,12,10**18]]
    if k==174:return [(2,l,b) for l in range(1,n+1) for b in [1,2,3,26]]
    if k==182:return [(2,l,s,g) for l in range(1,n+1) for s in [1,2,7,10**18] for g in [1,2,4,10**9]]
    raise ValueError(k)


def small_checks(p,k):
    count=0
    if k==122:
        # Derive e from each permutation, rather than assume the reconstruction rule.
        for n in range(1,7):
            for permutation in itertools.permutations(range(1,n+1)):
                e=[sum(x>permutation[i] for x in permutation[:i]) for i in range(n)]
                check_case(p,k,encode(k,e),permutation);count+=1
    elif k==193:
        for c in range(1,4):
            for n in range(4):
                for initial in itertools.product(range(c+1),repeat=n):
                    ops=[(2,w) for w in range(1,c+1)]*3
                    for capacity in range(c+1):
                        ops.extend([(1,capacity),(1,capacity)])
                        ops.extend((2,w) for w in range(1,c+1))
                    check_case(p,k,encode(k,initial,ops,c));count+=1
    elif k==192:
        for n in range(1,6):
            for initial in itertools.product([0,1],repeat=n):
                ops=[(1,p) for p in range(1,n+1)]*2
                for pos in range(1,n+1):ops.extend([(2,pos),(2,pos),(1,n),(1,pos)])
                check_case(p,k,encode(k,initial,ops));count+=1
    else:
        alphabet=[0,1] if k==112 else [0,1,2,4] if k==102 else ['a','b','c'] if k==174 else [1,2,3,6] if k==173 else [1,2,6] if k in (162,182) else [0,1,2]
        lengths=range(3,6) if k==132 else range(1,6) if k==112 else range(1,5)
        for n in lengths:
            for initial in itertools.product(alphabet,repeat=n):
                q=queries(k,n);ops=list(q)
                for i in range(1,n+1):
                    for x in ([0] if k==112 else alphabet):
                        ops.append((1,i) if k==112 else (1,i,x));ops.extend(q)
                check_case(p,k,encode(k,initial,ops));count+=1
    rng=random.Random(20261021+9000000+k)
    values=[0,1,2,3,6,7,12,18,999999893,999999929,999999937,10**9]
    if k in (162,173,182):values=values[1:]
    if k==102:values=[0,1,2,3,7,8,1<<19,(1<<20)-1]
    if k in (112,192):values=[0,1]
    if k==174:values=list('abcxyz')
    for _ in range(150):
        n=rng.randint(3 if k==132 else 1,35)
        if k==122:
            a=list(range(1,n+1));rng.shuffle(a)
            e=[sum(x>a[i] for x in a[:i]) for i in range(n)]
            check_case(p,k,encode(k,e),a);count+=1;continue
        c=rng.randint(1,35)
        a=rng.choices(range(c+1),k=rng.randint(0,35)) if k==193 else rng.choices(values,k=n)
        ops=[]
        for _ in range(rng.randint(1,200)):
            if k==193:
                ops.append((1,rng.randint(0,c)) if rng.randrange(2) else (2,rng.randint(1,c)));continue
            if k==192:ops.append((rng.randint(1,2),rng.randint(1,n)));continue
            if rng.randrange(2):
                i=rng.randint(1,n);ops.append((1,i) if k==112 else (1,i,rng.choice(values)));continue
            l,r=sorted([rng.randint(1,n),rng.randint(1,n)])
            if k==102:op=(2,rng.choice([1,2,3,7,8,1<<19,(1<<20)-1]))
            elif k==112:op=(2,l)
            elif k==132:op=(2,)
            elif k==162:op=(2,l,r,rng.choice([1,2,3,4,7,10**9]))
            elif k==173:op=(2,l,rng.choice([1,2,3,12,10**9,10**18]))
            elif k==174:op=(2,l,rng.choice([1,2,3,25,26]))
            else:op=(2,l,rng.choice([1,2,7,10**9,10**18]),rng.choice([1,2,4,7,10**9]))
            ops.append(op)
        check_case(p,k,encode(k,a,ops,c));count+=1
    extra=[]
    if k==132:
        extra=[encode(k,[0,0,0],[(2,)]),encode(k,[0,0,3],[(2,)]),encode(k,[1,1,1,0],[(2,)]),
               encode(k,[3,0,0,0,0,0],[(2,)]),encode(k,[1,0,0,1,0,1],[(2,)])]
    elif k==173:
        # Products beyond 64 bits; a previously capped node becomes small after updates.
        extra=[encode(k,[999999937,999999929,999999893,1],[(2,1,10**18),(1,2,1),(2,1,10**18),(1,3,1),(2,1,999999937),(2,1,999999936)]),
               encode(k,[10**9,999999999,999999937],[(2,1,999999999000000000),(2,1,999999998999999999),(2,1,10**18)])]
    if k in (102,112,162,173,174,182,192):
        n=1001
        if k==102:a=[0]*n;ops=[(1,450,1<<19),(2,1<<19),(1,450,0),(1,451,3),(2,2),(2,1<<19)]
        elif k==112:a=[0]*n;ops=[(1,450),(1,452),(2,451),(1,450),(2,451),(2,n)]
        elif k==162:a=[6]*n;ops=[(2,450,451,3),(1,451,5),(2,450,451,3),(2,452,n,3),(2,451,451,2)]
        elif k==173:a=[1]*n;ops=[(1,450,6),(1,451,5),(2,450,6),(2,450,30),(2,451,4)]
        elif k==174:a=['a']*n;ops=[(1,450,'z'),(2,449,1),(2,450,1),(2,450,2),(1,451,'z'),(2,450,1)]
        elif k==182:a=[6]*n;ops=[(1,450,10),(1,451,5),(2,450,1,1),(2,449,20,2),(2,451,5,5),(2,1,10**18,1)]
        else:a=[1]*n;ops=[(2,450),(2,451),(1,451),(1,451),(1,451),(2,1),(1,n)]
        extra.append(encode(k,a,ops))
    for data in extra:check_case(p,k,data);count+=1
    return count


def check_invalid_input(p,k):
    valid=(p/'gen/example_00.in').read_text();h,a,ops=decode(k,valid)
    bad=[valid+'0\n','\n'.join(valid.splitlines()[:-1])+'\n']
    if k==122:
        bad += ['0\n','200001\n','1\n-1\n','1\n1\n','2\n1 0\n','2\n0 2\n']
    else:
        if k==193:
            bad += [f'{c} {n} {q}\n' for c,n,q in [(0,0,1),(200001,0,1),(1,-1,1),(1,200001,1),(1,0,0),(1,0,200001)]]
            for op in [(0,1),(3,1),(1,-1),(1,6),(2,0),(2,6),(1,),(2,1,1)]:bad.append(encode(k,[],[op],5))
            bad.extend([encode(k,[-1],[(2,1)],5),encode(k,[6],[(2,1)],5)])
        else:
            minimum=3 if k==132 else 1
            bad += [f'{n} {q}\n' for n,q in [(minimum-1,1),(200001,1),(minimum,0),(minimum,200001)]]
            for op in [(0,),(3,),(1,)]:bad.append(encode(k,a,[op]))
            n=len(a)
            if k==102:
                extras=[(1,0,0),(1,n+1,0),(1,1,-1),(1,1,1<<20),(2,0),(2,1<<20),(2,),(2,1,1)]
            elif k in (112,192):extras=[(1,0),(1,n+1),(2,0),(2,n+1),(1,1,0),(2,1,0)]
            elif k==132:extras=[(1,0,0),(1,n+1,0),(1,1,-1),(1,1,10**9+1),(2,1)]
            elif k==162:extras=[(1,0,1),(1,n+1,1),(1,1,0),(1,1,10**9+1),(2,0,n,1),(2,1,n+1,1),(2,n,1,1),(2,1,n,0),(2,1,n,10**9+1),(2,1,n)]
            elif k==173:extras=[(1,0,1),(1,n+1,1),(1,1,0),(1,1,10**9+1),(2,0,1),(2,n+1,1),(2,1,0),(2,1,10**18+1),(2,1)]
            elif k==174:extras=[(1,0,'a'),(1,n+1,'a'),(1,1,'A'),(1,1,'aa'),(2,0,1),(2,n+1,1),(2,1,0),(2,1,27),(2,1,'a')]
            else:extras=[(1,0,1),(1,n+1,1),(1,1,0),(1,1,10**9+1),(2,0,1,1),(2,n+1,1,1),(2,1,0,1),(2,1,10**18+1,1),(2,1,1,0),(2,1,1,10**9+1),(2,1,1)]
            bad.extend(encode(k,a,[op]) for op in extras)
            if k==174:
                bad.extend([encode(k,['A']+a[1:],ops),valid.replace('abacaba','abacab'),valid.replace('abacaba','abacabaa')])
            else:
                low=1 if k in (162,173,182) else 0
                high=1 if k in (112,192) else (1<<20)-1 if k==102 else 10**9
                for x in [low-1,high+1]:bad.append(encode(k,[x]+a[1:],ops))
    for data in bad:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(p,'accepted invalid input',data)
    return len(bad)


def audit_coverage(problem,k):
    p=problem.basedir;files=sorted((p/'in').glob('*.in'));assert len(files)==36
    template=toml.load(ROOT/'custom/segtree000/info.toml')['upload']
    assert problem.config['upload']==template
    assert problem.config['timelimit']==template['time_limit']==0.5
    dims=[]
    for path in files:
        h,a,ops=decode(k,path.read_text())
        dims.append((h[0],len(ops)))
    assert (200000,0 if k==122 else 200000) in dims
    assert any(n==(3 if k==132 else 1) for n,_ in dims)
    assert any(n&(n-1) for n,_ in dims)
    if k!=122:assert (p/'out/edge_10.out').read_text()==''
    answer=(p/'out/max_01.out').read_text().split()
    if k in (102,112,162,173,182):assert set(answer)=={'200000'}
    if k==122:assert list(map(int,answer))==list(range(1,200001))
    if k==132:assert answer[:2]==['66666','133333']
    if k==174:assert set(answer)=={'199999'}
    if k==192:assert answer[0]=='200000' and set(answer[1:])=={'-1'}
    if k==193:assert list(map(int,answer))==list(range(200000,0,-1))
    assert not list(p.rglob('*.html'))
    for path in p.glob('*.md'):assert all(c>=32 or c in (9,10) for c in path.read_bytes()),path


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args();logging.basicConfig(level=logging.ERROR,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem]
    sources=[HERE/'oracle_search_next.cpp']
    for problem in problems:
        problem.health_check();problem.generate_params_h()
        sources.extend([problem.basedir/'sol/correct.cpp',problem.checker,problem.verifier])
        sources.extend(problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} next SEG1 problems...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(checked_compile,sources):pass
    total=0
    for problem in problems:
        started=time.monotonic();p=problem.basedir;k=int(p.name[7:])
        problem.make_inputs();problem.verify_inputs();problem.make_outputs(True);problem.judge(p/'sol/correct.cpp',{})
        assert problem.check_all_solutions_used()
        audit_statement(p,with_subtask=False);audit_coverage(problem,k)
        for test in problem.config['tests']:
            if not test['name'].endswith('.cpp'):continue
            exe=p/'gen'/Path(test['name']).stem
            for seed in range(test['number']):assert run(exe,'',seed)==(p/'in'/f'{exe.name}_{seed:02}.in').read_text()
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text();expected=(p/'out'/path.with_suffix('.out').name).read_text().split()
            assert run(ORACLE,data,k).split()==expected,(path,'independent reference differs')
            if path.stem.startswith(('edge','small','example')):assert brute(k,data)==expected,(path,'scan reference differs')
        count=small_checks(p,k);total+=count
        invalid=check_invalid_input(p,k);check_checker(p,k)
        if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: 36 generated tests, {count} exhaustive/random cases, {invalid} invalid inputs; 0.5s limit, checker, samples, upload, reproducibility, hashes OK ({time.monotonic()-started:.1f}s)',flush=True)
    print(f'All next SEG1 checks passed: {36*len(problems)} generated tests and {total} additional cases; no Subtask or HTML.',flush=True)


if __name__=='__main__':main()
