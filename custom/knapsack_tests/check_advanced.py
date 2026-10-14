"""Generate and verify KNAPSACK20..29, including boundaries, without HTML."""
import argparse
from collections import deque
from concurrent.futures import ThreadPoolExecutor
from functools import lru_cache
import itertools
import json
import logging
import math
from pathlib import Path
import random
import subprocess
import sys
import tempfile
import time

sys.path.insert(0,str(Path(__file__).resolve().parent))
from check import ROOT,Problem,compile_source,run,audit_statement
from check_basic import assert_reproducible

NAMES=[f'knapsack{i}' for i in range(20,30)]
MOD=10**9+7

@lru_cache(None)
def robot_distances():
    distance=[-1]*1001; distance[1]=0; queue=deque([1])
    while queue:
        u=queue.popleft()
        for x in range(1,u+1):
            v=u+u//x
            if v<=1000 and distance[v]<0: distance[v]=distance[u]+1; queue.append(v)
    return distance

def decode(num,data):
    a=list(map(int,data.split()))
    if num in (20,23,24): return a[1],list(zip(a[2::2],a[3::2]))
    if num==21: return a[1],a[2:]
    if num==22: return a[1],a[2],a[3:]
    if num==25: return a[1],a[2],list(zip(a[3::3],a[4::3],a[5::3]))
    if num==26: return a[1],list(zip(a[2::3],a[3::3],a[4::3]))
    if num==27: return list(zip(a[1::2],a[2::2]))
    if num==28: return a[0],a[1],a[2:]
    if num==29: return a[2:2+a[0]],a[2+a[0]:]
    raise ValueError(num)

def encode(num,case):
    if num in (20,23,24,26):
        target,a=case; return f'{len(a)} {target}\n'+''.join(' '.join(map(str,row))+'\n' for row in a)
    if num==21:
        x,a=case; return f'{len(a)} {x}\n'+' '.join(map(str,a))+'\n'
    if num==22:
        k,t,a=case; return f'{len(a)} {k} {t}\n'+' '.join(map(str,a))+'\n'
    if num==25:
        x,y,a=case; return f'{len(a)} {x} {y}\n'+''.join(' '.join(map(str,row))+'\n' for row in a)
    if num==27: return f'{len(case)}\n'+''.join(f'{a} {b}\n' for a,b in case)
    if num==28:
        b,m,c=case; return f'{b} {m}\n'+' '.join(map(str,c))+'\n'
    if num==29:
        a,queries=case; return f'{len(a)} {len(queries)}\n'+' '.join(map(str,a))+'\n'+''.join(f'{x}\n' for x in queries)
    raise ValueError(num)

def numeric_reference(case):
    # Keep the largest positive INTEGER at each exact cost and remainder.
    budget,m,c=case; best=[[-1]*m for _ in range(budget+1)]
    for spent in range(1,budget+1):
        for d in range(1,10):
            if spent==c[d]: best[spent][d%m]=max(best[spent][d%m],d)
        for d in range(10):
            previous=spent-c[d]
            if previous<1: continue
            for r,value in enumerate(best[previous]):
                if value>0:
                    new_r=(10*r+d)%m; candidate=value*10+d
                    if candidate>best[spent][new_r]: best[spent][new_r]=candidate
    if best[budget][0]>0: return str(best[budget][0])
    return '0' if c[0]==budget else '-1'

def brute(num,case):
    if num==20:
        h,a=case; best=None
        def visit(i,damage,cost):
            nonlocal best
            if damage>=h:
                best=cost if best is None else min(best,cost); return
            if i==len(a): return
            c,d=a[i]
            for copies in range((h-damage+d-1)//d+1): visit(i+1,damage+copies*d,cost+copies*c)
        visit(0,0,0); return str(best)
    if num==21:
        target,a=case; best=None; ways=0
        def visit(i,left,count):
            nonlocal best,ways
            if i==len(a):
                if left==0:
                    if best is None or count<best: best=count; ways=1
                    elif count==best: ways+=1
                return
            for copies in range(left//a[i]+1): visit(i+1,left-copies*a[i],count+copies)
        visit(0,target,0); return '-1 0' if best is None else f'{best} {ways%MOD}'
    if num==22:
        k,t,a=case; ways=0
        def visit(i,left,total):
            nonlocal ways
            if i==len(a): ways+=left==0 and total==k*t; return
            for copies in range(left+1): visit(i+1,left-copies,total+copies*a[i])
        visit(0,k,0); return str(ways%MOD)
    if num==23:
        target,a=case; d=robot_distances(); a=[(d[b]+1,v) for b,v in a]
        return brute_maximum(target,a)
    if num==24:
        target,a=case; answer=-1
        for cost,value in a:
            if cost//2<=target: answer=max(answer,value+int(brute_maximum(target-cost//2,a)))
        return str(answer)
    if num==25:
        x,y,a=case; best=0
        def visit(i,left_x,left_y,value):
            nonlocal best
            if i==len(a): best=max(best,value); return
            ax,ay,v=a[i]
            for copies in range(min(left_x//ax,left_y//ay)+1): visit(i+1,left_x-copies*ax,left_y-copies*ay,value+copies*v)
        visit(0,x,y,0); return str(best)
    if num==26:
        target,a=case; best=0
        def visit(i,left,value):
            nonlocal best
            if i==len(a): best=max(best,value); return
            fee,c,v=a[i]; visit(i+1,left,value)
            for copies in range(1,max(0,(left-fee)//c)+1): visit(i+1,left-fee-copies*c,value+copies*v)
        visit(0,target,0); return str(best)
    if num==27:
        limit=max(a for a,_ in case); ways=0
        def visit(i,load,strength):
            nonlocal ways
            if i==len(case): ways+=load>0 and load<=strength; return
            a,b=case[i]
            for copies in range((limit-load)//b+1): visit(i+1,load+copies*b,max(strength,a) if copies else strength)
        visit(0,0,0); return str(ways%MOD)
    if num==28:
        budget,m,c=case; answer=-1
        def visit(left,value,nonempty):
            nonlocal answer
            if left==0:
                if nonempty and value%m==0: answer=max(answer,value)
                return
            for d in range(10):
                if c[d]>left: continue
                if not nonempty and d==0:
                    if left==c[0]: answer=max(answer,0)
                else: visit(left-c[d],value*10+d,True)
        visit(budget,0,False); return str(answer)
    if num==29:
        a,queries=case; largest=max(queries); possible=[False]*(largest+1); possible[0]=True
        for s in range(largest+1):
            if possible[s]:
                for v in a:
                    if s+v<=largest: possible[s+v]=True
        return '\n'.join('YES' if possible[x] else 'NO' for x in queries)
    raise ValueError(num)

def brute_maximum(target,a):
    best=0
    def visit(i,left,value):
        nonlocal best
        if i==len(a): best=max(best,value); return
        cost,v=a[i]
        for copies in range(left//cost+1): visit(i+1,left-copies*cost,value+copies*v)
    visit(0,target,0); return str(best)

def tiny(num,case):
    if num in (20,21,23,24,26): return case[0]<=20 and len(case[1])<=5
    if num==22: return case[0]<=6 and len(case[2])<=5
    if num==25: return max(case[:2])<=10 and len(case[2])<=5
    if num==27: return len(case)<=5 and max(a for a,_ in case)<=20
    if num==28: return case[0]<=4
    if num==29: return max(case[1])<=200
    return False

def formula(num,case):
    if num==20:
        h,a=case
        if len(set(d for _,d in a))==1: return str(((h+a[0][1]-1)//a[0][1])*min(c for c,_ in a))
    if num==21:
        x,a=case
        if len(a)==1: return f'{x//a[0]} 1' if x%a[0]==0 else '-1 0'
        if x==0: return '0 1'
    if num==22:
        k,t,a=case
        if len(set(a))==1: return str(math.comb(k+len(a)-1,len(a)-1)%MOD) if a[0]==t else '0'
    if num==23:
        k,a=case
        if all(b==1 for b,_ in a): return str(k*max(v for _,v in a))
    if num==24:
        w,a=case
        if len(set(a))==1:
            c,v=a[0]; return str((1+(w-c//2)//c)*v) if c//2<=w else '-1'
    if num==25:
        x,y,a=case
        if len(set(a))==1:
            ax,ay,v=a[0]; return str(min(x//ax,y//ay)*v)
    if num==26:
        w,a=case
        if len(set(a))==1:
            f,c,v=a[0]; return str(max(0,(w-f)//c)*v)
    if num==27:
        if len(set(case))==1:
            a,b=case[0]; return str((math.comb(a//b+len(case),len(case))-1)%MOD)
    if num==28:
        b,m,c=case
        if len(set(c))==1 and b%c[0]: return '-1'
        if all(x==1 for x in c) and m==1: return '9'*b
        if all(x==1 for x in c) and m==50: return '9'*(b-2)+'50' if b>=2 else '0'
        if c==[1]+[2]*9 and m==7: return '0' if b==1 else '7'+'0'*(b-2)
    if num==29:
        a,queries=case; m=min(a)
        if all(v%m==0 for v in a): return '\n'.join('YES' if x%m==0 else 'NO' for x in queries)
    return None

def random_case(num,rng):
    n=rng.randint(1,4); target=rng.randint(0,15)
    if num==20: return target,[(rng.choice([1,2,10**9]),rng.randint(1,8)) for _ in range(n)]
    if num==21: return target,rng.sample(range(1,12),n)
    if num==22: return rng.randint(1,5),rng.randint(1,6),[rng.randint(1,6) for _ in range(n)]
    if num==23: return target,[(rng.randint(1,20),rng.choice([1,3,10**9])) for _ in range(n)]
    if num==24: return target,[(rng.randint(1,20),rng.choice([1,3,10**9])) for _ in range(n)]
    if num==25: return rng.randint(0,8),rng.randint(0,8),[(rng.randint(1,6),rng.randint(1,6),rng.choice([1,3,10**9])) for _ in range(n)]
    if num==26: return target,[(rng.randint(0,8),rng.randint(1,8),rng.choice([1,3,10**9])) for _ in range(n)]
    if num==27: return [(rng.randint(1,10),rng.randint(1,8)) for _ in range(n)]
    if num==28: return rng.randint(1,4),rng.randint(1,15),[rng.randint(1,6) for _ in range(10)]
    if num==29: return [rng.randint(1,20) for _ in range(n)],[rng.randint(0,200) for _ in range(10)]
    raise ValueError(num)

def exhaustive_cases(num):
    if num==20:
        for c,d,h in itertools.product((1,2,3),(1,2,3),range(8)): yield h,[(c,d),(2,3)]
    elif num==21:
        for a in itertools.combinations(range(1,6),3):
            for x in range(11): yield x,list(a)
    elif num==22:
        for a in itertools.product((1,2,3),repeat=3):
            for k,t in itertools.product(range(1,4),range(1,4)): yield k,t,list(a)
    elif num==23:
        for b,k in itertools.product(range(1,11),range(8)): yield k,[(b,3),(1,1)]
    elif num==24:
        for c1,c2,w in itertools.product((1,2,3),repeat=3): yield w,[(c1,3),(c2,2)]
    elif num==25:
        for x,y in itertools.product(range(6),repeat=2): yield x,y,[(1,2,3),(2,1,4)]
    elif num==26:
        for f,c,w in itertools.product(range(3),(1,2,3),range(8)): yield w,[(f,c,3),(1,2,4)]
    elif num==27:
        for a in itertools.product(((1,1),(1,2),(2,1),(2,2)),repeat=3): yield list(a)
    elif num==28:
        for c0,c9,b,m in itertools.product((1,2),(1,2),range(1,5),(1,2,3,7)):
            yield b,m,[c0]+[5]*8+[c9]
    elif num==29:
        for a in itertools.combinations_with_replacement(range(1,8),3): yield list(a),list(range(31))

INVALID={
20:['0 0\n','1 -1\n1 1\n','1 20001\n1 1\n','1 1\n0 1\n','1 1\n1 0\n','1 1\n1 1000000001\n'],
21:['0 0\n\n','1 -1\n1\n','1 20001\n1\n','1 0\n0\n','2 3\n1 1\n'],
22:['0 1 1\n1\n','1 0 1\n1\n','1 41 1\n1\n','1 1 0\n1\n','1 1 1\n51\n'],
23:['0 0\n','1 -1\n1 1\n','1 20001\n1 1\n','1 0\n0 1\n','1 0\n1001 1\n','1 0\n1 0\n'],
24:['0 0\n','1 -1\n1 1\n','1 10001\n1 1\n','1 0\n0 1\n','1 0\n20001 1\n','1 0\n1 0\n'],
25:['0 0 0\n','1 -1 0\n1 1 1\n','1 0 201\n1 1 1\n','1 0 0\n0 1 1\n','1 0 0\n1 0 1\n','1 0 0\n1 1 0\n'],
26:['0 0\n','1 -1\n0 1 1\n','1 20001\n0 1 1\n','1 0\n-1 1 1\n','1 0\n20001 1 1\n','1 0\n0 0 1\n','1 0\n0 1 0\n'],
27:['0\n','1\n0 1\n','1\n1 0\n','1\n5001 1\n','1\n1 5001\n'],
28:['0 1\n1 1 1 1 1 1 1 1 1 1\n','2001 1\n1 1 1 1 1 1 1 1 1 1\n','1 0\n1 1 1 1 1 1 1 1 1 1\n','1 51\n1 1 1 1 1 1 1 1 1 1\n','1 1\n0 1 1 1 1 1 1 1 1 1\n'],
29:['0 1\n\n0\n','1 0\n1\n','1 1\n0\n0\n','2 1\n5001 6000\n0\n','1 1\n1\n-1\n','1 1\n1\n1000000000000000001\n'],
}

def check_io(p,num):
    data=(p/'gen/example_00.in').read_text(); expected=(p/'out/example_00.out').read_text().strip()
    for invalid in INVALID[num]+[data+'0\n',data.rsplit('\n',2)[0]+'\n']:
        assert subprocess.run([str(p/'verifier')],input=invalid.encode(),capture_output=True).returncode!=0,(p,invalid)
    with tempfile.TemporaryDirectory() as temp:
        temp=Path(temp); inp,ans,out=[temp/name for name in ('in','ans','out')]
        inp.write_text(data); ans.write_text(expected+'\n'); tokens=expected.split()
        changed=tokens.copy(); changed[-1]='NO' if tokens[-1]=='YES' else 'YES' if tokens[-1]=='NO' else str(int(tokens[-1])+1)
        for value,ok in [(expected+'\n',True),(' \n'+' '.join(tokens)+' \n',True),(' '.join(changed)+'\n',False),('',False),('x\n',False),(expected+' 0\n',False)]:
            out.write_text(value); result=subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True)
            assert (result.returncode==0)==ok,(p,value[:100],result.stderr)
        # Also check every boundary answer and long/multi-token output.
        for path in sorted((p/'in').glob('max_*.in')):
            inp.write_text(path.read_text()); answer=(p/'out'/path.with_suffix('.out').name).read_text()
            ans.write_text(answer); out.write_text(answer)
            assert subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True).returncode==0,p


def audit_coverage(p,num):
    counts=[0,0,0]; peak=False; boundary=False
    for path in (p/'in').glob('*.in'):
        case=decode(num,path.read_text()); small=False; middle=False
        if num in (20,21,23,24,26):
            target,a=case; small=len(a)<=5 and target<=20; middle=target<=(1000 if num==24 else 2000)
            limit=10000 if num==24 else 20000; max_n=200 if num==26 else 100
            peak |= len(a)==max_n and target==limit
            if num==20: boundary |= any(d==10**9 for _,d in a)
            if num==21: boundary |= 20000 in a
            if num==23:
                small &= all(b<=20 for b,_ in a); middle=all(b<=100 for b,_ in a); boundary |= any(b==1000 for b,_ in a)
            if num==24: boundary |= any(c==20000 for c,_ in a)
            if num==26: boundary |= any(f==20000 and c==20000 for f,c,_ in a)
        elif num==22:
            k,t,a=case; small=len(a)<=5 and k<=5; middle=k<=10; peak |= len(a)==40 and k==40 and t==50; boundary |= 50 in a
        elif num==25:
            x,y,a=case; small=len(a)<=5 and max(x,y)<=10; middle=max(x,y)<=50; peak |= len(a)==40 and x==y==200; boundary |= any(ax==ay==200 for ax,ay,_ in a)
        elif num==27:
            small=len(case)<=5 and max(a for a,_ in case)<=20; middle=max(a for a,_ in case)<=500; peak |= len(case)==200 and max(a for a,_ in case)==5000; boundary |= any(b==5000 for _,b in case)
        elif num==28:
            b,m,c=case; small=b<=10; middle=m==1; peak |= b==2000 and m==50; boundary |= 2000 in c
        elif num==29:
            a,queries=case; small=max(queries)<=100000; middle=min(a)<=100; peak |= len(a)==50 and len(queries)==100000 and min(a)==5000; boundary |= max(queries)==10**18 and 1000000 in a
        counts[0]+=small; counts[1]+=middle; counts[2]+=1
    assert counts[2]==32 and min(counts)>0 and peak and boundary,(p,counts,peak,boundary)
    return counts

def special_counts(p,num):
    if num==21:
        x,a=decode(num,(p/'in/max_02.in').read_text()); best=[x+1]*(x+1); ways=[0]*(x+1); best[0]=0; ways[0]=1
        for coin in a:
            for s in range(coin,x+1):
                if best[s-coin]==x+1: continue
                candidate=best[s-coin]+1
                if candidate<best[s]: best[s]=candidate; ways[s]=ways[s-coin]
                elif candidate==best[s]: ways[s]+=ways[s-coin]
        assert ways[x]>MOD
        assert f'{best[x]} {ways[x]%MOD}'==(p/'out/max_02.out').read_text().strip()
    if num==22:
        assert math.comb(79,39)>MOD
    if num==27:
        assert math.comb(5200,200)-1>MOD

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true'); args=parser.parse_args()
    logging.basicConfig(level=logging.WARNING,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem]
    sources=[Path(__file__).with_name('oracle_advanced.cpp')]
    for problem in problems:
        problem.health_check(); problem.generate_params_h(); sources.extend([problem.basedir/'sol/correct.cpp',problem.checker,problem.verifier])
        sources.extend(problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} advanced problems...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source,sources): pass
    for problem in problems:
        started=time.monotonic(); p=problem.basedir; num=int(p.name[8:])
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True); problem.judge(p/'sol/correct.cpp',{})
        assert problem.check_all_solutions_used(); audit_statement(p); coverage=audit_coverage(p,num); formulas=0; enumerated=0
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text(); case=decode(num,data); expected=(p/'out'/path.with_suffix('.out').name).read_text().strip()
            actual=numeric_reference(case) if num==28 else run(Path(__file__).with_name('oracle_advanced'),data,num,timeout=30)
            assert actual==expected,(path,actual[:100],expected[:100])
            if tiny(num,case): assert brute(num,case)==expected,(path,'brute mismatch'); enumerated+=1
            closed=formula(num,case)
            if closed is not None: assert closed==expected,(path,'formula mismatch',closed[:100],expected[:100]); formulas+=1
        rng=random.Random(20261014+num); count=0
        for case in itertools.chain(exhaustive_cases(num),(random_case(num,rng) for _ in range(200))):
            data=encode(num,case); expected=brute(num,case); actual=run(p/'sol/correct',data)
            assert actual==expected,(p,data,actual,expected); count+=1
        special_counts(p,num); check_io(p,num); assert_reproducible(problem)
        if args.update_hashes: (p/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
        problem.assert_hashes(); assert not list(p.glob('*.html'))
        print(f'{p.name}: 32 validated test pairs and independent references; {count} exhaustive/random cases; {enumerated} enumerated files; {formulas} formulas; subtask coverage {coverage}; verifier/checker, reproducibility and hashes OK ({time.monotonic()-started:.1f}s).',flush=True)
    print('All advanced checks passed. No HTML generated.',flush=True)

if __name__=='__main__': main()
