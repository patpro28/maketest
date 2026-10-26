"""Generate and verify ten further SEG1 problems, without HTML."""
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
from check import audit_statement,run
from check_foundations import checked_compile
from check_remaining import check_checker

KINDS=[101,111,121,131,151,161,171,172,181,191]
NAMES=[f'segtree{k}' for k in KINDS]
ORACLE=HERE/'oracle_search_more'


def encode(k,a,ops,*,d=3,b=None,n=None):
    if n is None: n=len(a)-(k==101)
    text=f'{n} {len(ops)}'+(f' {d}' if k==161 else '')+'\n'
    if k!=191:text+=' '.join(map(str,a))+'\n'
    if k==181:text+=' '.join(map(str,b))+'\n'
    return text+''.join(' '.join(map(str,op))+'\n' for op in ops)


def decode(k,data):
    lines=data.splitlines();h=list(map(int,lines[0].split()));n,q=h[:2]
    off=1 if k==191 else 3 if k==181 else 2
    assert len(lines)==q+off
    a=[] if k==191 else list(map(int,lines[1].split()))
    assert k==191 or len(a)==n+(k==101)
    b=list(map(int,lines[2].split())) if k==181 else None
    assert b is None or len(b)==n
    return h,a,b,[tuple(map(int,line.split())) for line in lines[off:]]


def brute(k,data):
    import math
    lines=data.splitlines(); header=list(map(int,lines[0].split())); n,q=header[:2]
    if k==191:
        a=list(range(1,n+1)); start=0; out=[]
        for line in lines[1:]:
            start=(start+int(line)-1)%len(a);out.append(a.pop(start))
            if a: start%=len(a)
        return list(map(str,out))
    a=list(map(int,lines[1].split())); off=2
    if k==181: b=list(map(int,lines[2].split()));off=3
    out=[]
    for line in lines[off:]:
        op=list(map(int,line.split()));t=op[0]
        if k==101:
            a[op[1]]+=1 if t==1 else -1
            out.append(next((i for i,x in enumerate(a) if x==0),n+1));continue
        if k==121:
            if t==1:a[op[1]-1]+=op[2];continue
            rem=op[1];ans=-1
            for i,x in enumerate(a):
                if rem<=x:ans=i+1;a[i]-=1;break
                rem-=x
            out.append(ans);continue
        if t==1:
            a[op[1]-1]=op[2]
            if k==181:b[op[1]-1]=op[3]
            continue
        if k==111:
            l,r=op[1:];ans=next((i+1 for i in range(l-1,r-1) if a[i]>a[i+1]),-1)
        elif k==131:
            l,r=op[1:];need=(sum(a[l-1:r])+1)//2;ans=l
            for i in range(l-1,r):
                need-=a[i]
                if need<=0:ans=i+1;break
        elif k==151:
            p=op[1];ans=next((i+1 for i in range(p,n) if a[i]<a[p-1]),-1)
        elif k==161:
            l,r,rank=op[1:];pos=[i+1 for i in range(l-1,r) if a[i]%header[2]==0];ans=pos[rank-1] if rank<=len(pos) else -1
        elif k==171:
            l,g=op[1:];v=0;ans=l-1
            for i in range(l-1,n):
                v=math.gcd(v,a[i])
                if v<g:break
                ans=i+1
        elif k==172:
            l,m=op[1:];v=0;ans=-1
            for i in range(l-1,n):
                v|=a[i]
                if v&m==m:ans=i+1;break
        elif k==181:
            l,s,rank=op[1:];v=w=0;ans=-1
            for i in range(l-1,n):
                v+=a[i];w+=b[i]
                if v>=s and w>=rank:ans=i+1;break
        out.append(ans)
    return list(map(str,out))

def check_case(p,k,data):
    run(p/'verifier',data)
    expected=brute(k,data)
    assert run(p/'sol/correct',data).split()==expected,(p,'solution differs',data,expected)
    assert run(ORACLE,data,k).split()==expected,(p,'oracle differs',data,expected)


def queries(k,n):
    if k==111 or k==131:return [(2,l,r) for l in range(1,n+1) for r in range(l,n+1)]
    if k==151:return [(2,p) for p in range(1,n+1)]
    if k==161:return [(2,l,r,rank) for l in range(1,n+1) for r in range(l,n+1) for rank in range(1,n+1)]
    if k==171:return [(2,l,g) for l in range(1,n+1) for g in range(1,9)]
    if k==172:return [(2,l,mask) for l in range(1,n+1) for mask in range(1,9)]
    if k==181:return [(2,l,s,rank) for l in range(1,n+1) for s in [1,2,3,10] for rank in range(1,n+1)]
    raise ValueError(k)


def small_checks(p,k):
    count=0
    if k==191:
        for n in range(1,5):
            for steps in itertools.product(range(1,n+2),repeat=n):
                check_case(p,k,encode(k,[],[(x,) for x in steps],n=n));count+=1
    elif k==101:
        for n in range(1,5):
            for initial in itertools.product([0,1,2],repeat=n+1):
                a=list(initial);ops=[]
                for x in range(n+1):
                    for _ in range(a[x]):ops.append((2,x))
                    ops.extend([(1,x),(1,x),(2,x),(2,x),(1,x)])
                for x in range(n+1):ops.append((2,x))
                check_case(p,k,encode(k,initial,ops));count+=1
    elif k==121:
        for n in range(1,5):
            for initial in itertools.product([0,1,2],repeat=n):
                ops=[(2,rank) for rank in [sum(initial)+1,1,2,1,1,1,1,1,1]]
                for pos in range(1,n+1):ops.extend([(1,pos,3),(2,1),(2,2),(2,10**18)])
                check_case(p,k,encode(k,initial,ops));count+=1
    elif k==181:
        for n in range(1,4):
            for pairs in itertools.product([(0,0),(1,0),(0,1),(1,1)],repeat=n):
                a,b=map(list,zip(*pairs));q=queries(k,n);ops=list(q)
                for i in range(1,n+1):
                    for x,y in [(0,0),(1,0),(0,1),(1,1)]:ops.append((1,i,x,y));ops.extend(q)
                check_case(p,k,encode(k,a,ops,b=b));count+=1
    else:
        alphabet=[-1,0,1] if k==161 else [1,2,6] if k==171 else [0,1,2,4] if k==172 else [0,1,2]
        for n in range(1,5):
            for initial in itertools.product(alphabet,repeat=n):
                q=queries(k,n);ops=list(q)
                for i in range(1,n+1):
                    for x in alphabet:ops.append((1,i,x));ops.extend(q)
                for d in ([1,2,10**9] if k==161 else [3]):
                    check_case(p,k,encode(k,initial,ops,d=d));count+=1
    rng=random.Random(20261021+k)
    values=[-10**9,-7,-1,0,1,2,3,6,7,12,18,10**9]
    if k not in (111,161):values=[x for x in values if x>=0]
    if k==171:values=[x for x in values if x>0]
    if k==172:values=[0,1,2,3,4,7,8,31,1<<19,(1<<20)-1]
    for _ in range(150):
        n=rng.randint(1,35);a=rng.choices(values,k=n+(k==101));b=rng.choices([0,1],k=n)
        ops=[];state=list(a);d=rng.choice([1,2,3,7,10**9])
        for j in range(rng.randint(1,n) if k==191 else rng.randint(1,200)):
            if k==191:ops.append((rng.choice([1,2,n,n+1,10**18,rng.randint(1,10**18)]),));continue
            if k==101:
                x=rng.randrange(n+1);t=rng.randint(1,2)
                if state[x]==0:t=1
                state[x]+=1 if t==1 else -1;ops.append((t,x));continue
            if k==121:
                ops.append((1,rng.randint(1,n),rng.choice([1,2,7,10**9])) if rng.randrange(2) else (2,rng.choice([1,2,7,10**9,10**18])));continue
            if rng.randrange(2):
                i=rng.randint(1,n);x=rng.choice(values)
                ops.append((1,i,x,rng.randrange(2)) if k==181 else (1,i,x));continue
            l,r=sorted([rng.randint(1,n),rng.randint(1,n)])
            if k in (111,131):op=(2,l,r)
            elif k==151:op=(2,l)
            elif k==161:op=(2,l,r,rng.randint(1,n))
            elif k==171:op=(2,l,rng.choice([1,2,4,7,10**9]))
            elif k==172:op=(2,l,rng.choice([1,2,3,7,8,1<<19,(1<<20)-1]))
            elif k==181:op=(2,l,rng.choice([1,2,7,10**9,10**18]),rng.randint(1,n))
            ops.append(op)
        check_case(p,k,encode(k,a,ops,b=b,n=n,d=d));count+=1
    # Explicit block boundaries, values differing from divisibility tests, and strict inequalities.
    if k in (111,131,151,161,171,172,181):
        n=1001;a=[6 if k==171 else 0]*n;b=[0]*n
        ops=[]
        if k==111:ops=[(1,450,1),(2,449,451),(1,450,0),(1,451,-1),(2,450,452),(2,452,n)]
        elif k==131:ops=[(2,450,451),(1,450,10**9),(1,451,10**9),(2,450,451),(2,451,n),(1,450,0),(2,450,451)]
        elif k==151:ops=[(1,450,7),(2,450),(1,451,7),(2,450),(1,451,6),(2,450)]
        elif k==161:ops=[(2,450,451,2),(1,450,1),(2,450,451,1),(2,450,451,2),(1,451,-3),(2,450,451,1)]
        elif k==171:ops=[(2,1,4),(2,450,7),(1,451,5),(2,450,4),(2,451,4),(2,451,6)]
        elif k==172:ops=[(1,450,1),(1,451,6),(2,450,3),(2,451,3),(2,451,2),(2,452,1)]
        else:ops=[(1,450,10**9,0),(1,451,0,1),(2,450,10**9,1),(2,451,1,1),(1,451,10**9,1),(2,450,2*10**9,1)]
        check_case(p,k,encode(k,a,ops,b=b));count+=1
    return count


def check_invalid_input(p,k):
    valid=(p/'gen/example_00.in').read_text()
    h,a,b,ops=decode(k,valid);n=h[0]
    bad=[valid+'0\n','\n'.join(valid.splitlines()[:-1])+'\n']
    for nn,qq in [(0,1),(200001,1),(1,0),(1,200001)]:bad.append(f'{nn} {qq}\n')
    if k==191:
        bad += ['1 2\n1\n1\n','1 1\n0\n','1 1\n1000000000000000001\n','1 1\n1 2\n']
    else:
        d=h[2] if k==161 else 3
        kwargs=dict(d=d,b=b,n=n)
        def enc(oo,aa=a,**kw):return encode(k,aa,oo,**(kwargs|kw))
        bad += [enc([(0,)]),enc([(3,)]),enc([(1,)])]
        if k==101:
            bad += [enc([(1,-1)]),enc([(1,n+1)]),encode(k,[0,0],[(2,0)]),enc([(1,1,1)])]
        elif k==121:
            bad += [enc([(1,0,1)]),enc([(1,n+1,1)]),enc([(1,1,0)]),enc([(1,1,10**9+1)]),enc([(2,0)]),enc([(2,10**18+1)]),enc([(2,1,1)])]
        else:
            low=-10**9 if k in (111,161) else 1 if k==171 else 0
            high=(1<<20)-1 if k==172 else 10**9
            for pos in [0,n+1]:bad.append(enc([(1,pos,low,0)] if k==181 else [(1,pos,low)]))
            for x in [low-1,high+1]:
                bad.append(enc([(1,1,x,0)] if k==181 else [(1,1,x)]))
            if k in (111,131,161):
                extra=(1,) if k==161 else ()
                for l,r in [(0,n),(1,n+1),(n,1)]:bad.append(enc([(2,l,r,*extra)]))
                if k==161:
                    bad += [enc([(2,1,n,0)]),enc([(2,1,n,n+1)]),enc([(2,1,n)])]
                    for dd in [0,10**9+1]:bad.append(enc([(2,1,n,1)],d=dd))
            elif k==151:bad += [enc([(2,0)]),enc([(2,n+1)]),enc([(2,1,1)])]
            elif k in (171,172):
                for x in [0,high+1]:bad.append(enc([(2,1,x)]))
                bad += [enc([(2,0,1)]),enc([(2,n+1,1)]),enc([(2,1)])]
            else:
                bad += [enc([(1,1,0,-1)]),enc([(1,1,0,2)]),enc([(1,1,0)]),enc([(2,0,1,1)]),enc([(2,n+1,1,1)])]
                for s,rank in [(0,1),(10**18+1,1),(1,0),(1,n+1)]:bad.append(enc([(2,1,s,rank)]))
        # Initial array limits, including the second array of flags.
        low=1 if k==171 else -10**9 if k in (111,161) else 0
        high=(1<<20)-1 if k==172 else 10**9
        for x in [low-1,high+1]:
            aa=list(a);aa[0]=x;bad.append(enc(ops,aa))
        if k==181:
            bb=list(b);bb[0]=2;bad.append(enc(ops,b=bb))
    for data in bad:
        r=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert r.returncode!=0,(p,'accepted invalid data',data)
    return len(bad)


def audit_coverage(problem,k):
    p=problem.basedir
    template=toml.load(ROOT/'custom/segtree000/info.toml')['upload']
    assert problem.config['upload']==template
    assert problem.config['timelimit']==template['time_limit']==0.5
    files=sorted((p/'in').glob('*.in'));assert len(files)==36
    dims=[]
    for path in files:
        h,a,b,ops=decode(k,path.read_text());dims.append(tuple(h[:2]))
    assert (200000,200000) in dims
    assert any(n==1 for n,_ in dims) and any(n&(n-1) for n,_ in dims)
    if k not in (101,191):assert (p/'out/edge_10.out').read_text()==''
    answer=(p/'out/max_01.out').read_text().split()
    if k==101:assert answer[:2]==['200000','200001']
    if k==111:assert set(answer)=={'199999'}
    if k in (121,131,161,172,181):assert set(answer)=={'200000'}
    if k==151:assert set(answer)=={'-1'}
    if k==171:assert set(answer)=={'200000'}
    if k==191:assert len(set(answer))==200000 and set(map(int,answer))==set(range(1,200001))
    assert not list(p.glob('*.html'))
    for path in list(p.glob('*.md')):
        assert all(c>=32 or c in (9,10) for c in path.read_bytes()),path


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true')
    parser.add_argument('--skip-compile',action='store_true',help='Reuse binaries already compiled in this workspace')
    args=parser.parse_args();logging.basicConfig(level=logging.ERROR,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem]
    sources=[HERE/'oracle_search_more.cpp']
    for problem in problems:
        problem.health_check();problem.generate_params_h()
        sources.extend([problem.basedir/'sol/correct.cpp',problem.checker,problem.verifier])
        sources.extend(problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    if not args.skip_compile:
        print(f'Compiling {len(problems)} further SEG1 problems...',flush=True)
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
            assert run(ORACLE,data,k).split()==expected,(path,'reference differs')
            if path.stem.startswith(('edge','small','example')):assert brute(k,data)==expected,(path,'brute differs')
        count=small_checks(p,k);total+=count
        invalid=check_invalid_input(p,k);check_checker(p,k)
        if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: 36 generated tests, {count} exhaustive/random cases, {invalid} invalid inputs; 0.5s limit, checker, samples, upload, reproducibility, hashes OK ({time.monotonic()-started:.1f}s)',flush=True)
    print(f'All further SEG1 checks passed: {36*len(problems)} generated tests and {total} additional cases; no Subtask or HTML.',flush=True)


if __name__=='__main__':main()
