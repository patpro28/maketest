"""Generate and verify knapsack00..04, independently of the advanced suite."""
import argparse
from concurrent.futures import ThreadPoolExecutor
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

# Reuse compilation and repository mechanics without changing knapsack10..19.
sys.path.insert(0,str(Path(__file__).resolve().parent))
from check import ROOT,Problem,compile_source,run,subset_sums,audit_statement

MOD=10**9+7
NAMES=[f'knapsack{i:02}' for i in range(5)]

def decode(num,data):
    tokens=list(map(int,data.split()))
    if num in (0,4): return tokens[1],list(zip(tokens[2::2],tokens[3::2]))
    return tokens[1],tokens[2:]

def encode(num,case):
    target,a=case; head=f'{len(a)} {target}\n'
    if num in (0,4): return head+''.join(f'{w} {v}\n' for w,v in a)
    return head+' '.join(map(str,a))+'\n'

def brute(num,case):
    target,a=case
    if num in (0,4):
        weights=subset_sums([w for w,_ in a]); values=subset_sums([v for _,v in a])
        return str(max((value for weight,value in zip(weights,values) if (weight==target if num==4 else weight<=target)),default=-1))
    sums=subset_sums(a)
    if num==1: return 'YES' if target in sums else 'NO'
    if num==2: return str(min((mask.bit_count() for mask,total in enumerate(sums) if total==target),default=-1))
    if num==3: return str(sums.count(target)%MOD)
    raise ValueError(num)

def reference(num,case):
    target,a=case; mask=(1<<(target+1))-1
    if num==1:
        possible=1
        for v in a: possible=(possible | possible<<v)&mask
        return 'YES' if possible>>target & 1 else 'NO'
    if num==2:
        possible=[1]+[0]*len(a)
        for i,v in enumerate(a):
            for k in range(i+1,0,-1): possible[k]=(possible[k] | possible[k-1]<<v)&mask
        return str(next((k for k,bits in enumerate(possible) if bits>>target & 1),-1))
    return run(Path(__file__).with_name('oracle_basic'),encode(num,case),num)

def random_case(num,rng):
    n=rng.randint(1,12); target=rng.randint(0,100)
    if num in (0,4): return target,[(rng.randint(1,100),rng.choice([1,2,3,10**9])) for _ in range(n)]
    a=[rng.randint(1,25) for _ in range(n)]
    if rng.randrange(2): target=sum(rng.sample(a,rng.randint(0,n)))
    return target,a

def exhaustive_cases(num):
    if num in (0,4):
        for weights in itertools.product((1,2),repeat=3):
            for values in itertools.product((1,5),repeat=3):
                for target in range(7): yield target,list(zip(weights,values))
    else:
        for n in range(1,4):
            for a in itertools.product((1,2,3),repeat=n):
                for target in range(11): yield target,list(a)

def check_formula(num,case):
    target,a=case
    if num in (0,4):
        if len(set(w for w,_ in a))!=1: return None
        weight=a[0][0]
        if num==4 and (target%weight or target//weight>len(a)): return '-1'
        k=min(len(a),target//weight)
        return str(sum(sorted((v for _,v in a),reverse=True)[:k]))
    if len(set(a))!=1: return None
    valid=target%a[0]==0 and target//a[0]<=len(a)
    if num==1: return 'YES' if valid else 'NO'
    if num==2: return str(target//a[0]) if valid else '-1'
    return str(math.comb(len(a),target//a[0])%MOD) if valid else '0'

def audit_coverage(p,num):
    counts=[0,0,0]; maximum=False
    for path in (p/'in').glob('*.in'):
        target,a=decode(num,path.read_text()); counts[0]+=len(a)<=20; counts[1]+=target<=1000; counts[2]+=1
        maximum |= len(a)==200 and target==10000
    assert counts[2]==32 and min(counts)>0 and maximum,(p,counts,maximum)
    return counts

def check_validator_and_checker(p,num):
    sample=(p/'gen/example_00.in').read_text(); good=(p/'out/example_00.out').read_text().strip()
    if num in (0,4):
        bad=['0 0\n','201 0\n','1 -1\n1 1\n','1 10001\n1 1\n','1 0\n0 1\n','1 0\n10001 1\n','1 0\n1 0\n','1 0\n1 1000000001\n']
    else:
        bad=['0 0\n\n','201 0\n','1 -1\n1\n','1 10001\n1\n','1 0\n0\n','1 0\n10001\n']
    bad += [sample+'0\n',sample.rsplit('\n',2)[0]+'\n']
    for data in bad:
        assert subprocess.run([str(p/'verifier')],input=data.encode(),capture_output=True).returncode!=0,(p,data)
    with tempfile.TemporaryDirectory() as directory:
        directory=Path(directory); inp,ans,out=[directory/name for name in ('in','ans','out')]
        inp.write_text(sample); ans.write_text(good+'\n')
        wrong='NO' if good=='YES' else 'YES' if good=='NO' else str(int(good)+1)
        for data,valid in [(good+'\n',True),(' \n'+good+' \n',True),(wrong+'\n',False),('',False),('x\n',False),(good+' 0\n',False)]:
            out.write_text(data)
            result=subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True)
            assert (result.returncode==0)==valid,(p,data,result.stderr)
        # Exercise boundary output tokens: zero, impossibility, modulo and 64-bit values.
        if num==1: special=[((0,[1]),'YES'),((1,[2]),'NO')]
        elif num in (0,4): special=[((0,[(1,1)]),'0'),((200,[(1,10**9)]*200),'200000000000')]
        elif num==2: special=[((0,[1]),'0'),((1,[2]),'-1')]
        else: special=[((0,[1]),'1'),((100,[1]*200),str(math.comb(200,100)%MOD))]
        if num==4: special.append(((1,[(2,1)]),'-1'))
        for case,expected in special:
            data=encode(num,case); inp.write_text(data)
            assert run(p/'sol/correct',data)==expected,(p,case)
            ans.write_text(expected+'\n'); out.write_text(expected+'\n')
            assert subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True).returncode==0

def assert_reproducible(problem):
    p=problem.basedir
    for test in problem.config['tests']:
        if not test['name'].endswith('.cpp'): continue
        exe=p/'gen'/Path(test['name']).stem
        for seed in range(test['number']):
            expected=(p/'in'/f'{exe.name}_{seed:02}.in').read_text()
            assert run(exe,'',seed)+'\n'==expected,(p,test,seed)

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args()
    logging.basicConfig(level=logging.WARNING,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem]
    sources=[Path(__file__).with_name('oracle_basic.cpp')]
    for problem in problems:
        problem.health_check(); problem.generate_params_h()
        sources.extend([problem.basedir/'sol/correct.cpp',problem.checker,problem.verifier])
        sources.extend(problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} basic problems...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source,sources): pass
    for problem in problems:
        started=time.monotonic(); p=problem.basedir; num=int(p.name[8:])
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True); problem.judge(p/'sol/correct.cpp',{})
        assert problem.check_all_solutions_used()
        audit_statement(p); coverage=audit_coverage(p,num)
        formulas=0
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text(); case=decode(num,data); expected=(p/'out'/path.with_suffix('.out').name).read_text().strip()
            assert reference(num,case)==expected,(path,'independent reference differs')
            if path.stem.startswith(('edge','small','example')): assert brute(num,case)==expected,(path,'enumeration differs')
            formula=check_formula(num,case)
            if formula is not None:
                assert formula==expected,(path,'closed form differs'); formulas+=1
        count=0; rng=random.Random(20261009+num)
        for case in itertools.chain(exhaustive_cases(num),(random_case(num,rng) for _ in range(200))):
            data=encode(num,case)
            assert run(p/'sol/correct',data)==brute(num,case),(p,data)
            count+=1
        check_validator_and_checker(p,num); assert_reproducible(problem)
        if args.update_hashes: (p/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
        problem.assert_hashes(); assert not list(p.glob('*.html'))
        print(f'{p.name}: 32 validated pairs with independent references; {count} exhaustive/random cases; {formulas} formulas; subtask coverage {coverage}; checker, verifier, reproducibility and hashes OK ({time.monotonic()-started:.1f}s).',flush=True)
    print('All basic checks passed. No HTML generated.',flush=True)

if __name__=='__main__': main()
