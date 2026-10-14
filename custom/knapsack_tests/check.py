"""Generate, validate and cross-check knapsack10..19 without HTML dependencies."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from functools import lru_cache
import itertools
import json
import logging
import math
import os
from pathlib import Path
import random
import re
import shutil
import subprocess
import sys
if hasattr(sys,"set_int_max_str_digits"):
    sys.set_int_max_str_digits(10001)
import tempfile
import time

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from problem import Problem

MOD=998244353

def run(exe,data,*args,timeout=15):
    result=subprocess.run([str(exe),*map(str,args)],input=data.encode(),capture_output=True,timeout=timeout,check=True)
    return result.stdout.decode().strip()

def decode(num,data):
    a=list(map(int,data.split()))
    if num in (10,): return (a[1],a[2:])
    if num in (11,14,18): return a[1:]
    if num==12: return (a[1],a[2],a[3],list(zip(a[4::2],a[5::2])))
    if num==15: return (a[0],a[1:])
    if num==16: return list(zip(a[1::2],a[2::2]))
    if num in (13,17): return (a[1],list(zip(a[2::2],a[3::2])))
    if num==19: return (a[1],list(zip(a[2::3],a[3::3],a[4::3])))
    raise ValueError(num)

def encode(num,case):
    if num==10:
        x,a=case; return f'{len(a)} {x}\n'+' '.join(map(str,a))+'\n'
    if num in (11,14,18): return f'{len(case)}\n'+' '.join(map(str,case))+'\n'
    if num==12:
        s,k,x,a=case; return f'{len(a)} {s} {k} {x}\n'+''.join(f'{v} {w}\n' for v,w in a)
    if num==15:
        n,c=case; return f'{n}\n'+' '.join(map(str,c))+'\n'
    if num==16: return f'{len(case)}\n'+''.join(f'{v} {w}\n' for v,w in case)
    cap,a=case
    return f'{len(a)} {cap}\n'+''.join(' '.join(map(str,row))+'\n' for row in a)

def subset_sums(a):
    result=[0]*(1<<len(a))
    for mask in range(1,len(result)):
        bit=mask & -mask; result[mask]=result[mask^bit]+a[bit.bit_length()-1]
    return result

def string_reference(case):
    # Optimize full strings directly, rather than computing lengths and greedy reconstruction.
    n,c=case
    def larger(a,b): return (len(a),a)>(len(b),b)
    @lru_cache(None)
    def suffix(budget):
        if budget==0: return ''
        best=None
        for d,cost in enumerate(c):
            if cost<=budget:
                tail=suffix(budget-cost)
                if tail is not None:
                    candidate=str(d)+tail
                    if best is None or larger(candidate,best): best=candidate
        return best
    best='0' if n==c[0] else None
    for d in range(1,10):
        if c[d]<=n:
            tail=suffix(n-c[d])
            if tail is not None:
                candidate=str(d)+tail
                if best is None or larger(candidate,best): best=candidate
    return '-1' if best is None else best

def numeric_string_reference(case):
    # Exact-cost DP using arbitrary-precision integer comparisons and appending digits.
    # Keep only positive numbers; handle the single zero separately.
    n,c=case; best=[-1]*(n+1)
    for budget in range(1,n+1):
        for d in range(10):
            remaining=budget-c[d]
            if remaining==0 and d>0: best[budget]=max(best[budget],d)
            elif remaining>0 and best[remaining]>0: best[budget]=max(best[budget],best[remaining]*10+d)
    if best[n]>=0: return str(best[n])
    return '0' if n==c[0] else '-1'

def brute(num,case):
    if num==10:
        x,a=case; total=sum(a)
        return 'YES' if any(2*p-total==x for p in subset_sums(a)) else 'NO'
    if num==11:
        total=sum(case); return str(min(max(s,total-s) for s in subset_sums(case)))
    if num==12:
        s,k,x,a=case; base=s+sum(v for v,_ in a); sums=subset_sums([b-a for a,b in a])
        return 'YES' if any(mask.bit_count()<=k and base+delta==x for mask,delta in enumerate(sums)) else 'NO'
    if num==13:
        x,a=case; costs=subset_sums([c for c,_ in a]); points=subset_sums([p for _,p in a])
        return str(min((c for c,p in zip(costs,points) if p>=x),default=-1))
    if num==14:
        total=sum(case); k=len(case)//2
        return str(min(abs(total-2*s) for mask,s in enumerate(subset_sums(case)) if mask.bit_count()==k))
    if num==15: return string_reference(case)
    if num==16:
        weights=subset_sums([b for _,b in case]); count=0
        maxima=[0]*len(weights)
        for mask in range(1,len(weights)):
            bit=mask & -mask; maxima[mask]=max(maxima[mask^bit],case[bit.bit_length()-1][0])
            count+=weights[mask]<=maxima[mask]
        return str(count%MOD)
    if num==17:
        cap,a=case; weights=subset_sums([w for w,_ in a]); values=subset_sums([v for _,v in a]); best=-1
        for mask in range(1,len(weights)):
            bits=mask
            while bits:
                bit=bits & -bits; bits^=bit; i=bit.bit_length()-1
                if weights[mask]-a[i][0]+a[i][0]//2<=cap: best=max(best,values[mask])
        return str(best)
    if num==18:
        best=sum(case)
        for assignment in itertools.product(range(3),repeat=len(case)):
            loads=[0,0,0]
            for v,k in zip(case,assignment): loads[k]+=v
            best=min(best,max(loads))
        return str(best)
    if num==19:
        cap,a=case; costs=subset_sums([c for _,c,_ in a]); values=subset_sums([v for _,_,v in a]); best=0
        for mask in range(len(costs)):
            if costs[mask]>cap: continue
            if all(not (mask>>i & 1) or p==0 or (mask>>(p-1) & 1) for i,(p,_,_) in enumerate(a)):
                best=max(best,values[mask])
        return str(best)
    raise ValueError(num)

def bit_reference(num,case):
    if num in (10,11):
        if num==10: x,a=case
        else: a=case
        total=sum(a); reachable=1
        for v in a: reachable|=reachable<<v
        if num==10:
            if abs(x)>total or (total+x)%2: return 'NO'
            return 'YES' if reachable>>((total+x)//2)&1 else 'NO'
        lower=reachable & ((1<<(total//2+1))-1)
        return str(total-(lower.bit_length()-1))
    if num==12:
        s,k,x,a=case; delta=x-s-sum(v for v,_ in a)
        if delta<0 or delta>sum(b-a for a,b in a): return 'NO'
        possible=[1]+[0]*k
        for i,(v,w) in enumerate(a):
            for j in range(min(k,i+1),0,-1): possible[j]|=possible[j-1]<<(w-v)
        return 'YES' if any(p>>delta & 1 for p in possible) else 'NO'
    if num==14:
        total=sum(case); k=len(case)//2; possible=[1]+[0]*k
        for i,v in enumerate(case):
            for j in range(min(k,i+1),0,-1): possible[j]|=possible[j-1]<<v
        return str(min(abs(total-2*s) for s in range(total+1) if possible[k]>>s & 1))
    raise ValueError(num)

def random_case(num,rng):
    n=rng.randint(1,10)
    if num==10: return (rng.randint(-100,100),[rng.randint(1,20) for _ in range(n)])
    if num==11: return [rng.randint(1,30) for _ in range(n)]
    if num==12:
        s=rng.randint(0,100); k=rng.randint(0,n); a=[(rng.randint(1,1000000000),rng.randint(1,100)) for _ in range(n)]
        a=[(v,v+d) for v,d in a]; base=s+sum(v for v,_ in a)
        x=base+sum(b-v for v,b in a[:rng.randint(0,n)]) if rng.randrange(2) else base+rng.randint(-10,200)
        return s,k,x,a
    if num==13: return rng.randint(1,150),[(rng.choice([1,2,3,1000000000]),rng.randint(1,30)) for _ in range(n)]
    if num==14: return [rng.randint(1,20) for _ in range(max(2,n))]
    if num==15: return rng.randint(1,25),[rng.randint(1,30) for _ in range(10)]
    if num==16: return [(rng.randint(1,40),rng.randint(1,20)) for _ in range(n)]
    if num==17: return rng.randint(0,60),[(rng.randint(1,90),rng.choice([1,2,3,1000000000])) for _ in range(n)]
    if num==18: return [rng.randint(1,20) for _ in range(rng.randint(1,7))]
    if num==19: return rng.randint(0,40),[(0 if i==0 else rng.randint(1,i),rng.randint(1,20),rng.choice([1,2,3,1000000000])) for i in range(n)]
    raise ValueError(num)

def exhaustive_cases(num):
    if num==10:
        for n in range(1,4):
            for a in itertools.product(range(1,4),repeat=n):
                for x in range(-sum(a)-1,sum(a)+2): yield x,list(a)
    elif num in (11,14,18):
        for n in range(2 if num==14 else 1,5):
            for a in itertools.product((1,2,3),repeat=n): yield list(a)
    elif num==12:
        for diffs in itertools.product((1,2,3),repeat=3):
            for k in range(4):
                for extra in range(8): yield 0,k,3+extra,[(1,1+d) for d in diffs]
    elif num==13:
        for points in itertools.product((1,2,3),repeat=3):
            for x in range(1,8): yield x,[(i+1,p) for i,p in enumerate(points)]
    elif num==15:
        for c0,c1,c9 in itertools.product((1,2,3,4),repeat=3):
            for n in range(1,7): yield n,[c0,c1]+[10]*7+[c9]
    elif num==16:
        for values in itertools.product(((1,1),(1,2),(2,1),(2,2)),repeat=3): yield list(values)
    elif num==17:
        for weights in itertools.product((1,2,3),repeat=3):
            for cap in range(5): yield cap,[(w,i+1) for i,w in enumerate(weights)]
    elif num==19:
        for p3 in (1,2):
            for costs in itertools.product((1,2,3),repeat=3):
                for cap in range(5): yield cap,list(zip((0,1,p3),costs,(1,2,10)))

INVALID={
10:['0 0\n1\n','1 1000000001\n1\n','1 0\n0\n','2 0\n10001 10000\n'],
11:['0\n1\n','1\n0\n','2\n10001 10000\n'],
12:['1 0 2 0\n1 2\n','1 0 -1 0\n1 2\n','1 0 0 0\n1 1\n','1 0 0 0\n1 102\n','1 0 0 1000000000001\n1 2\n'],
13:['1 0\n1 1\n','1 1\n0 1\n','1 1\n1 0\n','1 1\n1000000001 1\n'],
14:['1\n1\n','2\n0 1\n','2\n3001 3000\n'],
15:['0\n1 1 1 1 1 1 1 1 1 1\n','1\n0 1 1 1 1 1 1 1 1 1\n','10001\n1 1 1 1 1 1 1 1 1 1\n'],
16:['0\n','1\n0 1\n','1\n1 0\n','1\n5001 1\n'],
17:['1 -1\n1 1\n','1 0\n0 1\n','1 0\n40001 1\n','1 0\n1 0\n'],
18:['0\n1\n','1\n0\n','2\n300 301\n'],
19:['1 0\n1 1 1\n','2 1\n0 1 1\n2 1 1\n','2 1\n0 1 1\n0 1 1\n','1 501\n0 1 1\n','1 0\n0 0 1\n'],
}

def check_io_tools(problem,num):
    p=problem.basedir; data=(p/'gen/example_00.in').read_text(); expected=(p/'out/example_00.out').read_text().strip()
    for bad in INVALID[num]+[data+'0\n',data.rsplit('\n',2)[0]+'\n']:
        result=subprocess.run([str(p/'verifier')],input=bad.encode(),capture_output=True)
        assert result.returncode!=0,(p,bad,'invalid input accepted')
    with tempfile.TemporaryDirectory() as tmp:
        tmp=Path(tmp); inp,ans,out=[tmp/name for name in ('in','ans','out')]
        inp.write_text(data); ans.write_text(expected+'\n')
        wrong='NO' if expected=='YES' else 'YES' if expected=='NO' else str(int(expected)+1)
        for text,ok in [(expected+'\n',True),(' \n'+expected+' \n',True),(wrong+'\n',False),
                        (expected+' 0\n',False),('',False),('x\n',False)]:
            out.write_text(text)
            result=subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True)
            assert (result.returncode==0)==ok,(p,text,result.stderr)
        # A long integer output must be compared as a string, without overflow.
        if num==15:
            long_answer='9'*10000; ans.write_text(long_answer+'\n'); out.write_text(long_answer+'\n')
            assert subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True).returncode==0
            out.write_text(long_answer[:-1]+'8\n')
            assert subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True).returncode!=0

def compile_source(source):
    compiler=os.environ.get('CXX') or shutil.which('g++-16') or shutil.which('g++') or 'c++'
    command=[compiler,'-std=c++17','-O2','-Wall','-Wextra','-Werror','-Wno-unused-result','-I',str(ROOT/'common'),str(source),'-o',str(source.with_suffix(''))]
    result=subprocess.run(command,capture_output=True)
    if result.returncode:
        sys.stderr.write(result.stderr.decode())
        raise RuntimeError(f"Compilation failed: {source}")

def audit_statement(p):
    statement=(p/'task.md').read_text()
    inputs=re.findall(r'### Sample Input \d+\n\n```text\n(.*?)```',statement,re.S)
    outputs=re.findall(r'### Sample Output \d+\n\n```text\n(.*?)```',statement,re.S)
    assert len(inputs)==len(outputs)==2
    for i,(inp,out) in enumerate(zip(inputs,outputs)):
        assert inp==(p/'gen'/f'example_{i:02}.in').read_text()
        assert out==(p/'out'/f'example_{i:02}.out').read_text()
    assert sum(map(int,re.findall(r'\| \d+ \| (\d+)%',statement)))==100

def audit_coverage(p,num):
    cases=[decode(num,path.read_text()) for path in (p/'in').glob('*.in')]
    membership=[0,0,0]; large=False
    full_points=False; near_full_points=False
    for case in cases:
        if num==10: n=len(case[1]); small=n<=20; middle=sum(case[1])<=2000; large |= n==200 and sum(case[1])==20000
        elif num==11: n=len(case); small=n<=20; middle=sum(case)<=2000; large |= n==200 and sum(case)==20000
        elif num==12: n=len(case[3]); small=n<=20; middle=n<=60; large |= n==200 and sum(b-a for a,b in case[3])==20000
        elif num==13:
            n=len(case[1]); small=n<=20; middle=case[0]<=2000; large |= n==200 and case[0]==20000
            points=[p for _,p in case[1]]
            full_points |= n==200 and case[0]==20000 and sum(points)==4000000
            near_full_points |= n==200 and case[0]==20000 and all(p==19999 for p in points)
        elif num==14: n=len(case); small=n<=20; middle=sum(case)<=600; large |= n==60 and sum(case)==6000
        elif num==15: small=case[0]<=20; middle=len(set(case[1]))==1; large |= case[0]==10000
        elif num==16: n=len(case); small=n<=20; middle=all(a<=500 for a,_ in case); large |= n==2000 and max(a for a,_ in case)==5000
        elif num==17: n=len(case[1]); small=n<=20; middle=case[0]<=2000; large |= n==200 and case[0]==20000
        elif num==18: n=len(case); small=n<=10; middle=sum(case)<=100; large |= n==60 and sum(case)==600
        elif num==19: n=len(case[1]); small=n<=20; middle=all(p==i for i,(p,_,_) in enumerate(case[1]) if i); large |= n==200 and case[0]==500
        membership[0]+=small; membership[1]+=middle; membership[2]+=1
    assert min(membership)>0 and large,(p,membership,large)
    if num==13: assert full_points and near_full_points,(p,'missing full-sum point boundaries')
    return membership


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',default=[f'knapsack{i}' for i in range(10,20)])
    parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args()
    names=args.problem
    if any(name not in [f'knapsack{i}' for i in range(10,20)] for name in names): parser.error('Unknown problem')
    logging.basicConfig(level=logging.WARNING,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in names]
    sources=[Path(__file__).with_name('oracle.cpp')]
    for problem in problems:
        problem.health_check(); problem.generate_params_h()
        sources += [problem.basedir/'sol/correct.cpp',problem.checker,problem.verifier]
        sources += [problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp')]
    print(f'Compiling sources for {len(problems)} problems...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source,sources): pass
    for problem in problems:
        started=time.monotonic(); p=problem.basedir; num=int(p.name[8:])
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True)
        problem.judge(p/'sol/correct.cpp',{})
        assert problem.check_all_solutions_used()
        test_count=sum(test['number'] for test in problem.config['tests'])
        assert len(list((p/'in').glob('*.in')))==test_count
        audit_statement(p)
        audit_coverage(p,num)
        checked=0
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text(); case=decode(num,data); expected=(p/'out'/path.with_suffix('.out').name).read_text().strip()
            if num in (10,11,12,14): actual=bit_reference(num,case)
            elif num==15:
                actual=numeric_string_reference(case)
            else: actual=run(Path(__file__).with_name('oracle'),data,num,timeout=30)
            assert actual==expected,(path,actual[:100],expected[:100]); checked+=1
            if path.stem.startswith(('edge','small','example')):
                assert brute(num,case)==expected,(path,'enumeration mismatch')
        # Closed forms for long digit strings and modular/large answers.
        formula=0
        for path in sorted((p/'in').glob('*.in')):
            case=decode(num,path.read_text()); expected=(p/'out'/path.with_suffix('.out').name).read_text().strip(); actual=None
            if num==15:
                n,c=case
                if len(set(c))==1: actual='9'*(n//c[0]) if n%c[0]==0 else '-1'
                elif c[0]==1 and len(set(c[1:]))==1:
                    price=c[1]; actual='9'+'0'*(n-price) if n>=price else '0' if n==1 else '-1'
                elif all(v==2 for v in c) and n%2: actual='-1'
            if num==16 and len(set(case))==1:
                a,b=case[0]; actual=str(sum(math.comb(len(case),k) for k in range(1,min(len(case),a//b)+1))%MOD)
            if num==13:
                target,activities=case
                if all(p>=target for _,p in activities): actual=str(min(c for c,_ in activities))
                elif len(activities)>=2 and 2*min(p for _,p in activities)>=target:
                    candidates=[c for c,p in activities if p>=target]
                    candidates.append(sum(sorted(c for c,_ in activities)[:2]))
                    actual=str(min(candidates))
            if num in (11,18) and len(set(case))==1:
                actual=str(math.ceil(len(case)/(2 if num==11 else 3))*case[0])
            if num==14 and len(set(case))==1: actual=str((len(case)%2)*case[0])
            if num==19 and all(c==1 for _,c,_ in case[1]) and len(set(v for _,_,v in case[1]))==1:
                actual=str(min(len(case[1]),case[0])*case[1][0][2])
            if actual is not None:
                assert actual==expected,(path,actual[:100],expected[:100]); formula+=1
        rng=random.Random(20261007+num); count=0
        for case in itertools.chain(exhaustive_cases(num),(random_case(num,rng) for _ in range(200))):
            data=encode(num,case); expected=brute(num,case); actual=run(p/'sol/correct',data)
            assert actual==expected,(p,data,actual,expected); count+=1
        check_io_tools(problem,num)
        if args.update_hashes: (p/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
        problem.assert_hashes()
        assert not list(p.glob('*.html'))
        print(f'{p.name}: {test_count} valid test pairs; {checked} independent references, {formula} formulas; {count} exhaustive/random cases; verifier/checker and hashes OK ({time.monotonic()-started:.1f}s).',flush=True)
    print('All checks passed. No HTML generated.',flush=True)

if __name__=='__main__': main()
