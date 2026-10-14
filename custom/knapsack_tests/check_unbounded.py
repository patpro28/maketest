"""Generate and independently check knapsack05..09, without exporting HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import json
import logging
from pathlib import Path
import random
import subprocess
import sys
import tempfile
import time

sys.path.insert(0,str(Path(__file__).resolve().parent))
from check import ROOT,Problem,compile_source,run,audit_statement
from check_basic import assert_reproducible

NAMES=[f'knapsack{i:02}' for i in range(5,10)]
MOD=10**9+7

def decode(num,data):
    tokens=list(map(int,data.split()))
    return (tokens[1],list(zip(tokens[2::2],tokens[3::2]))) if num in (5,9) else (tokens[1],tokens[2:])

def encode(num,case):
    target,a=case; head=f'{len(a)} {target}\n'
    if num in (5,9): return head+''.join(f'{w} {v}\n' for w,v in a)
    return head+' '.join(map(str,a))+'\n'

def brute(num,case):
    # Enumerate all vectors of multiplicities, without a DP recurrence.
    target,a=case; paired=num in (5,9)
    weights=[w for w,_ in a] if paired else a
    best=-1; ways=0
    def visit(index,remaining,value,count):
        nonlocal best,ways
        if index==len(weights):
            if num==5: best=max(best,value)
            elif remaining==0:
                ways+=1
                if num==9: best=max(best,value)
                elif num==7: best=count if best<0 else min(best,count)
            return
        weight=weights[index]
        for copies in range(remaining//weight+1):
            visit(index+1,remaining-copies*weight,value+(copies*a[index][1] if paired else 0),count+copies)
    visit(0,target,0,0)
    if num==6: return 'YES' if ways else 'NO'
    if num==8: return str(ways%MOD)
    return str(best)

def exhaustive_cases(num):
    if num in (5,9):
        for weights in itertools.product((1,2),repeat=3):
            for values in itertools.product((1,5),repeat=3):
                for target in range(7): yield target,list(zip(weights,values))
    elif num==8:
        for n in range(1,4):
            for a in itertools.combinations(range(1,6),n):
                for target in range(11): yield target,list(a)
    else:
        for n in range(1,4):
            for a in itertools.product((1,2,3),repeat=n):
                for target in range(11): yield target,list(a)

def random_case(num,rng):
    n=rng.randint(1,4); target=rng.randint(0,20)
    if num in (5,9): return target,[(rng.randint(1,10),rng.choice([1,2,3,10**9])) for _ in range(n)]
    if num==8: return target,rng.sample(range(1,16),n)
    return target,[rng.randint(1,10) for _ in range(n)]

def closed_form(num,case):
    target,a=case
    if num in (5,9):
        if len(set(w for w,_ in a))!=1: return None
        weight=a[0][0]
        if num==9 and target%weight: return '-1'
        return str((target//weight)*max(v for _,v in a))
    if len(set(a))!=1: return None
    reachable=target%a[0]==0
    if num==6: return 'YES' if reachable else 'NO'
    if num==7: return str(target//a[0]) if reachable else '-1'
    # The counting problem has distinct denominations, so this case has N=1.
    assert len(a)==1
    return '1' if reachable else '0'

def audit_coverage(p,num):
    memberships=[0,0,0]; max_dimensions=False; max_input=False; max_value=False
    for path in (p/'in').glob('*.in'):
        target,a=decode(num,path.read_text())
        memberships[0]+=len(a)<=5 and target<=20; memberships[1]+=target<=1000; memberships[2]+=1
        max_dimensions |= len(a)==100 and target==10000
        weights=[w for w,_ in a] if num in (5,9) else a
        max_input |= 10000 in weights
        if num==8: assert len(set(a))==len(a),path
        if num in (5,9): max_value |= target==10000 and (1,10**9) in a
    assert memberships[2]==32 and min(memberships)>0 and max_dimensions and max_input,(p,memberships)
    if num in (5,9): assert max_value,(p,'missing 64-bit answer boundary')
    return memberships

def check_io(p,num):
    sample=(p/'gen/example_00.in').read_text(); good=(p/'out/example_00.out').read_text().strip()
    if num in (5,9):
        invalid=['0 0\n','101 0\n','1 -1\n1 1\n','1 10001\n1 1\n','1 0\n0 1\n','1 0\n10001 1\n','1 0\n1 0\n','1 0\n1 1000000001\n']
    else:
        invalid=['0 0\n\n','101 0\n','1 -1\n1\n','1 10001\n1\n','1 0\n0\n','1 0\n10001\n']
        if num==8: invalid += ['2 3\n1 1\n']
    invalid += [sample+'0\n',sample.rsplit('\n',2)[0]+'\n']
    for data in invalid:
        assert subprocess.run([str(p/'verifier')],input=data.encode(),capture_output=True).returncode!=0,(p,data)
    # Accept duplicates where the problem permits them, and unsorted distinct coins.
    valid_case=(6,[(2,3),(2,4)]) if num in (5,9) else (3,[2,1]) if num==8 else (6,[2,2])
    assert subprocess.run([str(p/'verifier')],input=encode(num,valid_case).encode(),capture_output=True).returncode==0,p
    with tempfile.TemporaryDirectory() as directory:
        directory=Path(directory); inp,ans,out=[directory/name for name in ('in','ans','out')]
        inp.write_text(sample); ans.write_text(good+'\n')
        wrong='NO' if good=='YES' else 'YES' if good=='NO' else str(int(good)+1)
        for text,ok in [(good+'\n',True),(' \n'+good+' \n',True),(wrong+'\n',False),('',False),('x\n',False),(good+' 0\n',False)]:
            out.write_text(text)
            result=subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True)
            assert (result.returncode==0)==ok,(p,text,result.stderr)
        if num in (5,9): cases=[((0,[(1,1)]),'0'),((10000,[(1,10**9)]),'10000000000000')]
        elif num==6: cases=[((0,[1]),'YES'),((6,[2]),'YES'),((2,[4,6]),'NO')]
        elif num==7: cases=[((0,[1]),'0'),((10000,[1]),'10000'),((5,[4,6]),'-1')]
        else: cases=[((0,[1]),'1'),((3,[1,2]),'2'),((10000,[1,2]),'5001')]
        if num==9: cases.append(((3,[(2,7)]),'-1'))
        for case,expected in cases:
            data=encode(num,case); inp.write_text(data)
            assert run(p/'sol/correct',data)==expected,(p,case)
            ans.write_text(expected+'\n'); out.write_text(expected+'\n')
            assert subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True).returncode==0

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args(); logging.basicConfig(level=logging.WARNING,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem]
    sources=[Path(__file__).with_name('oracle_unbounded.cpp')]
    for problem in problems:
        problem.health_check(); problem.generate_params_h()
        sources.extend([problem.basedir/'sol/correct.cpp',problem.checker,problem.verifier])
        sources.extend(problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} unbounded problems...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source,sources): pass
    for problem in problems:
        started=time.monotonic(); p=problem.basedir; num=int(p.name[8:])
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True); problem.judge(p/'sol/correct.cpp',{})
        assert problem.check_all_solutions_used()
        audit_statement(p); coverage=audit_coverage(p,num); formulas=0
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text(); case=decode(num,data); expected=(p/'out'/path.with_suffix('.out').name).read_text().strip()
            actual=run(Path(__file__).with_name('oracle_unbounded'),data,num,timeout=30)
            assert actual==expected,(path,actual,expected)
            if path.stem.startswith(('edge','small','example')): assert brute(num,case)==expected,(path,'enumeration differs')
            formula=closed_form(num,case)
            if formula is not None:
                assert formula==expected,(path,'formula differs'); formulas+=1
        if num==8:
            # Python exact counts validate a case whose answer exceeds the modulus.
            case=decode(num,(p/'in/max_01.in').read_text()); target,a=case
            counts=[1]+[0]*target
            for coin in a:
                for s in range(coin,target+1): counts[s]+=counts[s-coin]
            assert counts[target]>MOD
            assert str(counts[target]%MOD)==(p/'out/max_01.out').read_text().strip()
        count=0; rng=random.Random(20261013+num)
        for case in itertools.chain(exhaustive_cases(num),(random_case(num,rng) for _ in range(200))):
            data=encode(num,case)
            assert run(p/'sol/correct',data)==brute(num,case),(p,data)
            count+=1
        check_io(p,num); assert_reproducible(problem)
        if args.update_hashes: (p/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
        problem.assert_hashes(); assert not list(p.glob('*.html'))
        print(f'{p.name}: 32 validated pairs; independent reference and {count} exhaustive/random cases; {formulas} formulas; subtask coverage {coverage}; verifier/checker, reproducibility and hashes OK ({time.monotonic()-started:.1f}s).',flush=True)
    print('All unbounded checks passed. No HTML generated.',flush=True)

if __name__=='__main__': main()
