"""Build and verify eight PALINCUT/PLAN variants, without exporting HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from functools import lru_cache
import importlib.util
import itertools
import json
import logging
from math import comb
import os
from pathlib import Path
import random
import re
import shlex
import subprocess
import sys
import tempfile
import time

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[1]
sys.path.insert(0,str(ROOT))
from problem import Problem
from problem_upload import ProblemUpload
CODES=['dtpalorder','dtpalcount','dtpalpre','dtpalcost','dtplanone','dtplankinds','dtplantotal','dtplanbits']
MOD=10**9


def run(executable,data='',*args,timeout=30):
    return subprocess.run([str(executable),*map(str,args)],input=data,text=True,capture_output=True,check=True,timeout=timeout).stdout


def build(src):
    flags=shlex.split(os.getenv('CXXFLAGS','-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result'))
    subprocess.run([os.getenv('CXX','g++'),*flags,'-I',str(ROOT/'common'),str(src),'-o',str(src.with_suffix(''))],check=True)


def parse(code,data):
    words=iter(data.split())
    if code.startswith('dtpal'):
        s=next(words)
        if code=='dtpalcount':
            d=int(next(words));pairs=[(int(next(words)),int(next(words))) for _ in range(d)]
            return s,pairs
        k=int(next(words));e=int(next(words)) if code=='dtpalpre' else 0
        lengths=[int(next(words)) for _ in range(k)]
        if code=='dtpalpre':return s,lengths,[(int(next(words))-1,int(next(words))-1) for _ in range(e)]
        if code=='dtpalcost':return s,lengths,[int(next(words)) for _ in s]
        return s,lengths
    m=int(next(words));A=int(next(words))
    if code=='dtplanone':return m,A,[int(next(words)) for _ in range(m)]
    B=int(next(words));extra=int(next(words)) if code in ('dtplankinds','dtplantotal') else None
    pairs=[(int(next(words)),int(next(words))) for _ in range(m)]
    return m,A,B,extra,pairs


def pal_brute(code,data):
    parsed=parse(code,data);s=parsed[0];n=len(s)
    if code=='dtpalorder':
        lengths=parsed[1]
        @lru_cache(None)
        def solve(i,p):
            if i==len(lengths):return True
            L=lengths[i]
            return any(s[a:a+L]==s[a:a+L][::-1] and solve(i+1,a+L) for a in range(p,n-L+1))
        return solve(0,0)
    if code=='dtpalcount':lengths=[L for L,c in parsed[1] for _ in range(c)]
    else:lengths=parsed[1]
    k=len(lengths);need=[0]*k
    if code=='dtpalpre':
        for u,v in parsed[2]:need[v]|=1<<u
    weights=parsed[2] if code=='dtpalcost' else [0]*n
    prefix=[0]
    for w in weights:prefix.append(prefix[-1]+w)
    @lru_cache(None)
    def solve(mask,p):
        if mask==(1<<k)-1:return 0
        answer=10**30
        for i,L in enumerate(lengths):
            if mask>>i&1 or need[i]&mask!=need[i]:continue
            for a in range(p,n-L+1):
                t=s[a:a+L]
                if t==t[::-1]:answer=min(answer,prefix[a+L]-prefix[a]+solve(mask|(1<<i),a+L))
        return answer
    answer=solve(0,0)
    return (-1 if answer>=10**30 else answer) if code=='dtpalcost' else answer<10**30


def acyclic(k,edges):
    adj=[[] for _ in range(k)];degree=[0]*k
    for u,v in edges:adj[u].append(v);degree[v]+=1
    queue=[i for i in range(k) if not degree[i]]
    for x in queue:
        for y in adj[x]:
            degree[y]-=1
            if not degree[y]:queue.append(y)
    return len(queue)==k


def pal_reference(code,data):
    parsed=parse(code,data);s=parsed[0];n=len(s)
    if code=='dtpalorder':
        p=0
        for L in parsed[1]:
            while p+L<=n:
                t=s[p:p+L]
                if t==t[::-1]:break
                p+=1
            if p+L>n:return False
            p+=L
        return True
    if code=='dtpalcost':return int(run(HERE/'oracle_cost',data))
    if code=='dtpalcount':
        pairs=parsed[1];lengths=[L for L,c in pairs];counts=[c for L,c in pairs]
        if sum(L*c for L,c in pairs)>n:return False
    else:
        lengths=parsed[1];counts=[1]*len(lengths)
        if sum(lengths)>n or not acyclic(len(lengths),parsed[2]):return False
    # Uniform strings and alternating strings with only odd lengths are immediate.
    if len(set(s))==1 or (all(L%2 for L in lengths) and all(s[i]==s[i%2] for i in range(n))):return True
    tables={}
    for L in set(lengths):
        table=[n+1]*(n+1)
        for p in range(n-1,-1,-1):
            t=s[p:p+L]
            table[p]=p+L if p+L<=n and t==t[::-1] else table[p+1]
        tables[L]=table
    if code=='dtpalcount':
        @lru_cache(None)
        def solve(state):
            if not any(state):return 0
            best=n+1
            for i in range(len(state)):
                if state[i]:
                    previous=list(state);previous[i]-=1;p=solve(tuple(previous))
                    if p<=n:best=min(best,tables[lengths[i]][p])
            return best
        return solve(tuple(counts))<=n
    k=len(lengths);need=[0]*k
    for u,v in parsed[2]:need[v]|=1<<u
    dp=[n+1]*(1<<k);dp[0]=0
    for mask in range(1<<k):
        if dp[mask]>n:continue
        for i,L in enumerate(lengths):
            if not(mask>>i&1) and need[i]&mask==need[i]:
                new=mask|(1<<i);dp[new]=min(dp[new],tables[L][dp[mask]])
    return dp[-1]<=n


def plan_brute(code,data):
    parsed=parse(code,data)
    if code=='dtplanone':
        m,A,coeff=parsed
        @lru_cache(None)
        def solve(i,A):
            if i==m:return int(A==0)
            return sum(solve(i+1,A-x*coeff[i]) for x in range(A//coeff[i]+1))%MOD
        return solve(0,A)
    m,A,B,extra,pairs=parsed
    @lru_cache(None)
    def solve(i,A,B,remaining):
        if i==m:return int(A==B==0 and (remaining==0 or extra is None))
        a,b=pairs[i];answer=0
        for x in range(min(A//a,B//b)+1):
            if code=='dtplanbits' and x&(x>>1):continue
            cost=int(x>0) if code=='dtplankinds' else x if code=='dtplantotal' else 0
            if extra is not None and cost>remaining:continue
            answer+=solve(i+1,A-a*x,B-b*x,remaining-cost)
        return answer%MOD
    return solve(0,A,B,extra or 0)


def total_reference(data):
    m,A,B,C,pairs=parse('dtplantotal',data)
    groups=[pairs.count((a,b)) for a,b in ((1,1),(1,2),(2,1),(2,2))]
    base=[3*C-A-B,B-C,A-C,0];slope=[1,-1,-1,1]
    lo=max(0,A+B-3*C);hi=min(A-C,B-C)
    if lo>hi:return 0
    fixed=None
    for j,g in enumerate(groups):
        if not g:
            z=-base[j]//slope[j]
            if fixed is not None and fixed!=z:return 0
            fixed=z
    def value(z):
        result=1
        for j,g in enumerate(groups):
            y=base[j]+slope[j]*z
            if y<0 or (not g and y):return 0
            if g:result*=comb(y+g-1,g-1)
        return result
    if fixed is not None:return value(fixed)%MOD if lo<=fixed<=hi else 0
    degree=m-4;N=hi-lo+1
    if N<=degree+1:return sum(value(z) for z in range(lo,hi+1))%MOD
    values=[value(lo+t) for t in range(degree+1)];answer=0
    for r in range(degree+1):
        answer+=values[0]*comb(N,r+1)
        values=[values[i+1]-values[i] for i in range(len(values)-1)]
    return answer%MOD


def numeric_reference(code,data):
    if code=='dtplantotal':return total_reference(data)
    if code=='dtplanbits':return int(run(HERE/'oracle_bits',data))
    if code=='dtplankinds':return int(run(HERE/'oracle_kinds',data))
    m,A,coeff=parse(code,data)
    if len(set(coeff))==1:
        return comb(A//coeff[0]+m-1,m-1)%MOD if A%coeff[0]==0 else 0
    # Product of truncated geometric series, using fresh layers and explicit counts.
    f=[0]*(A+1);f[0]=1
    for a in coeff:
        g=[0]*(A+1)
        # A separate residue-prefix implementation avoids updating f in place.
        for r in range(min(a,A+1)):
            value=0
            for p in range(r,A+1,a):value=(value+f[p])%MOD;g[p]=value
        f=g
    return f[A]


def audit(problem):
    p=problem.basedir;code=p.name
    text=(p/'task.md').read_text();solution=(p/'solution.md').read_text()
    expected=['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc','Sample Input 1','Sample Output 1','Sample Input 2','Sample Output 2','Giải thích']
    assert text.startswith(f'# {code.upper()} — ')
    assert re.findall(r'^### (.*)$',text,re.M)==expected
    assert len(re.findall(r'^#+ ',text,re.M))==len(expected)+1
    assert not re.search(r'^# ',solution,re.M)
    assert not re.search(r'oracle|verifier|checker|benchmark|kiểm thử|kiểm chứng|bộ sinh|chạy test',solution,re.I)
    assert not list(p.glob('*.html'))
    assert problem.config['title']==text.splitlines()[0][2:]
    assert problem.check_all_solutions_used()
    upload=ProblemUpload(problem)
    count=sum(test['number'] for test in problem.config['tests'])
    scored=sum(test['number'] for test in problem.config['tests'] if not test['name'].endswith('.in'))
    cases=upload.manifest['cases'];assert len(cases)==count and sum(x['points'] for x in cases)==scored
    assert all(x['points']==(0 if x['input_file'].startswith('example') else 1) for x in cases)
    assert problem.config['upload']['points']==100
    assert ('custom'==problem.config['upload'].get('checker'))==(code in CODES[:2])
    for j in (1,2):
        match=re.search(rf'### Sample Input {j}\n\n```text\n(.*?)```',text,re.S)
        assert match and match[1]==(p/'gen'/f'example_{j-1:02}.in').read_text()


def checker_test(problem):
    p=problem.basedir;count=0
    with tempfile.TemporaryDirectory() as directory:
        actual=Path(directory)/'actual';expected=Path(directory)/'expected'
        for path in sorted((p/'in').glob('example*.in')):
            good=(p/'out'/path.with_suffix('.out').name).read_text();expected.write_text(good)
            bad=['','garbage\n',good+'0\n',good+'trailing\n']
            if p.name in CODES[:3]:bad+=['MAYBE\n','yes\n',('NO\n' if good.startswith('YES') else 'YES\n')]
            else:bad+=[str(int(good)+1)+'\n','1.0\n','9'*100+'\n']
            for data,accepted in [(good,True),(' \n'+good+' \t\n',True),*((x,False) for x in bad)]:
                actual.write_text(data)
                result=subprocess.run([str(p/'checker'),str(path),str(actual),str(expected)],capture_output=True)
                assert (result.returncode==0)==accepted,(p.name,path.name,data,result.stderr);count+=1
        if p.name in CODES[:2]:
            inp=Path(directory)/'in';inp.write_text('aaaaaa\n1\n2\n' if p.name==CODES[0] else 'aaaaaa\n1\n2 2\n')
            expected.write_text('YES\n1 2\n' if p.name==CODES[0] else 'YES\n1 2\n3 4\n')
            variants=[('YES\n5 6\n' if p.name==CODES[0] else 'YES\n1 2\n5 6\n',True),
                      ('YES\n0 2\n',False),('YES\n1 3\n',False),('YES\n2 1\n',False),('YES\n1 7\n',False)]
            if p.name==CODES[1]:variants+=[('YES\n1 2\n2 3\n',False),('YES\n3 4\n1 2\n',False)]
            for data,accepted in variants:
                actual.write_text(data);result=subprocess.run([str(p/'checker'),str(inp),str(actual),str(expected)],capture_output=True)
                assert (result.returncode==0)==accepted,(p.name,data,result.stderr);count+=1
    return count


def invalid_test(problem):
    p=problem.basedir;sample=(p/'gen/example_00.in').read_text()
    bad=['',sample+'0\n','\n'.join(sample.splitlines()[:-1])+'\n']
    code=p.name
    if code in CODES[:4]:
        bad += [sample.replace(sample.splitlines()[0],'A',1),sample.replace(sample.splitlines()[0],'a'*(problem.config['params']['N_MAX']+1),1)]
        specific={
            CODES[0]:['a\n0\n\n','a\n1\n0\n','a\n1\n200001\n'],
            CODES[1]:['a\n0\n','a\n2\n1 1\n1 1\n','a\n1\n1 21\n'],
            CODES[2]:['a\n19 0\n'+'1 '*18+'1\n','a\n1 1\n1\n1 1\n','aa\n2 2\n1 1\n1 2\n1 2\n'],
            CODES[3]:['a\n1\n1\n-1\n','a\n1\n1\n1000000001\n','a\n0\n\n1\n'],
        }
    else:
        specific={
            CODES[4]:['0 1\n','1 200001\n1\n','1 1\n0\n','1 1\n1001\n','1 -1\n1\n'],
            CODES[5]:['1 151 0 0\n1 1\n','1 0 0 2\n1 1\n','1 0 0 0\n6 1\n','1 0 -1 0\n1 1\n','21 0 0 0\n'],
            CODES[6]:['1 1000000000000000001 0 0\n1 1\n','9 0 0 0\n','1 0 0 -1\n1 1\n','1 0 0 0\n3 1\n','1 0 0 0\n0 1\n'],
            CODES[7]:['1 1000000000000000001 0\n1 1\n','9 0 0\n','1 0 -1\n1 1\n','1 0 0\n3 1\n','1 0 0\n0 1\n'],
        }
    bad+=specific[code]
    for data in bad:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(code,'accepted invalid input',data[:100])
    return len(bad)


def small_inputs(code):
    rng=random.Random(2026110300+CODES.index(code))
    for _ in range(100):
        if code in CODES[:4]:
            n=rng.randint(1,14);s=''.join(rng.choice('abc') for _ in range(n))
            if code==CODES[1]:
                d=rng.randint(1,3);pairs=[(L,rng.randint(1,2)) for L in rng.sample(range(1,6),d)]
                yield s+'\n'+str(d)+'\n'+''.join(f'{L} {c}\n' for L,c in pairs)
            else:
                k=rng.randint(1,5 if code!=CODES[3] else 4);lengths=[rng.randint(1,6) for _ in range(k)]
                if code==CODES[2]:
                    edges=[(u,v) for u in range(1,k+1) for v in range(1,k+1) if u!=v and rng.randrange(6)==0]
                    yield s+f'\n{k} {len(edges)}\n'+' '.join(map(str,lengths))+'\n'+''.join(f'{u} {v}\n' for u,v in edges)
                else:
                    data=s+f'\n{k}\n'+' '.join(map(str,lengths))+'\n'
                    if code==CODES[3]:data+=' '.join(str(rng.choice([0,1,10**9,rng.randint(1,50)])) for _ in range(n))+'\n'
                    yield data
        elif code==CODES[4]:
            m=rng.randint(1,6);A=rng.randint(0,35)
            yield f'{m} {A}\n'+''.join(f'{rng.randint(1,10)}\n' for _ in range(m))
        else:
            m=rng.randint(1,5);A=rng.randint(0,18);B=rng.randint(0,18)
            extra=rng.randint(0,m) if code==CODES[5] else rng.randint(0,18)
            pairs=[(rng.randint(1,2),rng.randint(1,2)) for _ in range(m)]
            header=f'{m} {A} {B}'+(f' {extra}' if code!=CODES[7] else '')
            yield header+'\n'+''.join(f'{a} {b}\n' for a,b in pairs)


def check_result(code,data,actual,expected):
    if code in CODES[:3]:assert (actual.split()[0]=='YES')==expected,(code,data[:100],actual,expected)
    else:assert int(actual)==expected,(code,data[:100],actual,expected)


def fixed_type_order(s,pairs):
    p=0
    for length,count in pairs:
        for _ in range(count):
            while p+length<=len(s) and s[p:p+length]!=s[p:p+length][::-1]:p+=1
            if p+length>len(s):return False
            p+=length
    return True


def order_trap_checks(problem):
    if problem.basedir.name!='dtpalcount':return {}
    p=problem.basedir;rejected=0;interleaved=0
    with tempfile.TemporaryDirectory() as directory:
        witness_path=Path(directory)/'witness';actual_path=Path(directory)/'actual'
        for seed in range(8):
            path=p/'in'/f'order_trap_{seed:02}.in';data=path.read_text();s,pairs=parse('dtpalcount',data)
            reference=p/'out'/path.with_suffix('.out').name
            assert reference.read_text().startswith('YES')
            # The generator supplies a direct, explicitly valid choice of segments.
            witness=run(p/'gen/order_trap','',seed,'witness');witness_path.write_text(witness)
            run(p/'checker','',path,witness_path,reference)
            actual=run(p/'tests/wrong_input_order',data,timeout=problem.config['upload']['time_limit'])
            assert actual.strip()=='NO',(seed,actual)
            actual_path.write_text(actual)
            judged=subprocess.run([str(p/'checker'),str(path),str(actual_path),str(reference)],capture_output=True)
            assert judged.returncode==1,(seed,judged.stderr)
            rejected+=1
            # Trying every permutation of whole groups must still fail on seeds 1..7.
            possible=any(fixed_type_order(s,order) for order in itertools.permutations(pairs))
            if seed==0:assert possible
            else:assert not possible;interleaved+=1
    return dict(submitted_code_rejected=rejected,all_group_orders_rejected=interleaved)


def check_problem(problem,args):
    p=problem.basedir;code=p.name
    problem.make_inputs();problem.verify_inputs();problem.make_outputs(True);audit(problem)
    maximum=0;small_official=0
    with tempfile.TemporaryDirectory() as directory:
        actual_path=Path(directory)/'actual'
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text();before=time.monotonic();actual=run(p/'sol/correct',data,timeout=problem.config['upload']['time_limit'])
            maximum=max(maximum,time.monotonic()-before)
            actual_path.write_text(actual);expected_path=p/'out'/path.with_suffix('.out').name
            run(p/'checker','',path,actual_path,expected_path)
            if code in CODES[:4]:
                expected=pal_reference(code,data)
                parsed=parse(code,data)
                if len(parsed[0])<=16:
                    assert pal_brute(code,data)==expected;small_official+=1
            else:
                expected=numeric_reference(code,data)
                parsed=parse(code,data)
                target=parsed[1]
                if target<=35 and (code==CODES[4] or parsed[2]<=35):
                    assert plan_brute(code,data)==expected;small_official+=1
            check_result(code,data,actual,expected)
            if not path.stem.startswith('example_'):
                name,seed=path.stem.rsplit('_',1);assert run(p/'gen'/name,'',int(seed))==data
            if path.stem.startswith('example_'):
                j=int(path.stem.split('_')[1])+1;text=(p/'task.md').read_text()
                sample=re.search(rf'### Sample Output {j}\n\n```text\n(.*?)```',text,re.S)[1]
                actual_path.write_text(sample);run(p/'checker','',path,actual_path,expected_path)
        count=0
        for data in small_inputs(code):
            run(p/'verifier',data)
            expected=pal_brute(code,data) if code in CODES[:4] else plan_brute(code,data)
            actual=run(p/'sol/correct',data);check_result(code,data,actual,expected)
            if code in CODES[:2]:
                # Validate the printed witness, not only its YES/NO status.
                inp=Path(directory)/'small.in';out=Path(directory)/'small.out';ans=Path(directory)/'small.ans'
                inp.write_text(data);out.write_text(actual);ans.write_text('YES\n' if expected else 'NO\n')
                run(p/'checker','',inp,out,ans)
            if code==CODES[6]:assert total_reference(data)==expected
            if code==CODES[7]:assert int(run(HERE/'oracle_bits',data))==expected
            count+=1
    invalid=invalid_test(problem);checkers=checker_test(problem);regression=order_trap_checks(problem)
    if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
    problem.assert_hashes()
    official=sum(test['number'] for test in problem.config['tests'])
    result=dict(official=official,small=count,small_official=small_official,invalid=invalid,checker=checkers,max_runtime_seconds=round(maximum,4),hashes=2*official,**regression)
    print(f'{code}: PASS; {result}',flush=True)
    return result


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--problem',choices=CODES,action='append');parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'dtqg'/code) for code in (args.problem or CODES)]
    sources=[HERE/'oracle_bits.cpp',HERE/'oracle_kinds.cpp',HERE/'oracle_cost.cpp']
    for p in problems:
        p.health_check();p.generate_params_h()
        sources += [p.basedir/'sol/correct.cpp',p.basedir/'verifier.cpp',p.basedir/'checker.cpp']
        sources += [p.basedir/'gen'/test['name'] for test in p.config['tests'] if test['name'].endswith('.cpp')]
        if p.basedir.name=='dtpalcount':sources.append(p.basedir/'tests/wrong_input_order.cpp')
    print(f'Compiling {len(sources)} programs...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(build,sources))
    results={}
    for p in problems:results[p.basedir.name]=check_problem(p,args)
    result_path=HERE/'results.json'
    if result_path.exists():results={**json.loads(result_path.read_text()),**results}
    result_path.write_text(json.dumps(results,indent=2,ensure_ascii=False)+'\n')
    print('All selected problems passed; inputs, outputs and hashes verified; no HTML generated.',flush=True)


if __name__=='__main__':main()
