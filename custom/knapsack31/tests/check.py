"""Generate and verify KNAPSACK30 without HTML; --update-hashes for data changes."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from functools import lru_cache
import itertools
import json
import logging
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile
import time

ROOT=Path(__file__).resolve().parents[3]
sys.path.insert(0,str(ROOT/'custom/knapsack_tests'))
from check import Problem,compile_source,run
from check_basic import assert_reproducible
import toml
P=ROOT/'custom/knapsack30'

def encode(k,x,spells):
    return f'{len(spells)} {k} {x}\n'+''.join(f'{c} {d}\n' for c,d in spells)

def decode(data):
    a=list(map(int,data.split()))
    return a[1],a[2],list(zip(a[3::2],a[4::2]))

def brute(k,x,spells):
    # Enumerate multiplicities of each type, with exactly K uses. Do not cap damage.
    best=None
    def visit(index,left,damage,cost):
        nonlocal best
        if index==len(spells):
            if left==0 and damage>=x: best=cost if best is None else min(best,cost)
            return
        c,d=spells[index]
        for copies in range(left+1): visit(index+1,left-copies,damage+copies*d,cost+copies*c)
    visit(0,k,0,0)
    return str(-1 if best is None else best)

def full_sum(k,x,spells):
    # Small-case exact-sum DP keeps ALL original damage totals, including above 2*X.
    sums={0:0}
    for _ in range(k):
        next_sums={}
        for s,cost in sums.items():
            for c,d in spells:
                candidate=cost+c; target=s+d
                if candidate<next_sums.get(target,10**30): next_sums[target]=candidate
        sums=next_sums
    return str(min((c for s,c in sums.items() if s>=x),default=-1))

def at_most(k,x,spells):
    # Intentionally wrong early stopping: accepts using fewer than K spells.
    @lru_cache(None)
    def solve(remaining,need):
        if need<=0: return 0
        if remaining==0: return 10**30
        return min(c+solve(remaining-1,max(0,need-d)) for c,d in spells)
    answer=solve(k,x)
    return str(-1 if answer>=10**30 else answer)

def audit_statement():
    text=(P/'task.md').read_text()
    assert text.splitlines()[0]=='# KNAPSACK30 — Phá khiên trong đúng K lượt'
    headings=re.findall(r'^### (.*)$',text,re.M)
    expected=['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc']
    for i in range(1,4): expected.extend([f'Sample Input {i}',f'Sample Output {i}'])
    expected.append('Giải thích')
    assert headings==expected,headings
    assert '### Subtask' not in text
    inputs=re.findall(r'### Sample Input \d+\n\n```text\n(.*?)```',text,re.S)
    outputs=re.findall(r'### Sample Output \d+\n\n```text\n(.*?)```',text,re.S)
    assert len(inputs)==len(outputs)==3
    for i,(data,answer) in enumerate(zip(inputs,outputs)):
        assert data==(P/'gen'/f'example_{i:02}.in').read_text()
        assert answer==(P/'out'/f'example_{i:02}.out').read_text()
    assert re.findall(r'^#{1,6} ',text,re.M)==['# ']+['### ']*len(expected)

def check_tools():
    valid='2 3 16\n1 3\n4 10\n'
    invalid=[
        '0 1 1\n','51 1 1\n','1 0 1\n1 1\n','1 201 1\n1 1\n',
        '1 1 0\n1 1\n','1 1 2001\n1 1\n','1 1 1\n0 1\n',
        '1 1 1\n1 0\n','1 1 1\n1000000001 1\n','1 1 1\n1 1000000001\n',
        '1 1 1\n1\n',valid+'1\n',
    ]
    for data in invalid:
        assert subprocess.run([str(P/'verifier')],input=data.encode(),capture_output=True).returncode!=0,data
    assert subprocess.run([str(P/'verifier')],input=valid.encode(),capture_output=True).returncode==0
    with tempfile.TemporaryDirectory() as directory:
        directory=Path(directory); inp,ans,out=[directory/name for name in ('in','ans','out')]
        inp.write_text(valid); ans.write_text('6\n')
        for data,ok in [('6\n',True),(' 6 \n',True),('5\n',False),('-1\n',False),
                        ('6 0\n',False),('',False),('6.0\n',False),('x\n',False),
                        ('200000000001\n',False),('-2\n',False)]:
            out.write_text(data)
            result=subprocess.run([str(P/'checker'),str(inp),str(out),str(ans)],capture_output=True)
            assert (result.returncode==0)==ok,(data,result.stderr)
        for expected in ('-1','200000000000'):
            ans.write_text(expected+'\n'); out.write_text(expected+'\n')
            assert subprocess.run([str(P/'checker'),str(inp),str(out),str(ans)],capture_output=True).returncode==0

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--update-hashes',action='store_true'); args=parser.parse_args()
    logging.basicConfig(level=logging.WARNING,format='%(message)s')
    problem=Problem(ROOT,P)
    # Copy authorization refers to metadata only; nothing is uploaded by this script.
    source=toml.load(ROOT/'custom/knapsack19/info.toml')
    assert problem.config['upload']==source['upload'],'[upload] differs from knapsack19'
    problem.health_check(); problem.generate_params_h()
    sources=[P/'sol/correct.cpp',P/'verifier.cpp',P/'checker.cpp',P/'tests/oracle.cpp',P/'tests/wrong_cap.cpp']
    sources += [P/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp')]
    print('Compiling KNAPSACK30 sources...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source,sources): pass
    problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True)
    problem.judge(P/'sol/correct.cpp',{})
    assert problem.check_all_solutions_used()
    audit_statement()
    peak=False; huge_damage=False; huge_cost=False; formulas=0; cap_kills=[]; early_kills=[]; full_sum_count=0; max_time=0
    paths=sorted((P/'in').glob('*.in'))
    assert len(paths)==37
    for path in paths:
        data=path.read_text(); k,x,spells=decode(data)
        answer=(P/'out'/path.with_suffix('.out').name).read_text().strip()
        started=time.monotonic()
        assert run(P/'sol/correct',data,timeout=problem.config['upload']['time_limit'])==answer,path
        max_time=max(max_time,time.monotonic()-started)
        assert run(P/'tests/oracle',data)==answer,(path,'remaining-damage reference')
        peak |= len(spells)==50 and k==200 and x==2000
        huge_damage |= any(d==10**9 for _,d in spells)
        huge_cost |= answer=='200000000000'
        if max(d for _,d in spells)*k<x:
            assert answer=='-1'; formulas+=1
        elif len(set(d for _,d in spells))==1:
            expected=k*min(c for c,_ in spells)
            assert answer==str(expected); formulas+=1
        elif min(d for _,d in spells)*k>=x:
            assert answer==str(k*min(c for c,_ in spells)); formulas+=1
        if len(spells)<=4 and k<=6:
            assert brute(k,x,spells)==answer,path
            assert full_sum(k,x,spells)==answer,path
            full_sum_count+=1
        if path.stem.startswith(('edge','example')):
            if run(P/'tests/wrong_cap',data)!=answer: cap_kills.append(path.name)
            if at_most(k,x,spells)!=answer: early_kills.append(path.name)
    assert peak and huge_damage and huge_cost
    assert 'example_00.in' in cap_kills and 'example_00.in' in early_kills
    assert len(cap_kills)>=3 and len(early_kills)>=3
    cases=[]
    for spells in itertools.product(((1,1),(1,3),(4,1),(4,3)),repeat=2):
        for k,x in itertools.product(range(1,5),range(1,8)): cases.append((k,x,list(spells)))
    rng=random.Random(20261021)
    for _ in range(300):
        n=rng.randint(1,4); k=rng.randint(1,6); x=rng.randint(1,20)
        spells=[(rng.choice([1,2,7,10**9]),rng.choice([1,2,3,10,10**9])) for _ in range(n)]
        cases.append((k,x,spells))
    for k,x,spells in cases:
        data=encode(k,x,spells); expected=brute(k,x,spells)
        assert run(P/'sol/correct',data)==expected,data
        assert full_sum(k,x,spells)==expected,data
    check_tools(); assert_reproducible(problem)
    if args.update_hashes: (P/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
    problem.assert_hashes()
    assert not list(P.glob('*.html'))
    print(f'37 validated test pairs and independent references; {len(cases)} exhaustive/random cases; {full_sum_count} small files with full exact-sum DP; {formulas} formulas.',flush=True)
    print(f'Wrong 2X-cap rejected by {len(cap_kills)} edge/sample cases; early-stop rejected by {len(early_kills)}. Witnesses: {cap_kills}',flush=True)
    print(f'Checker/verifier, reproducibility, all 74 hashes, statement format and copied [upload] OK. Slowest main-solution run: {max_time:.3f}s (upload limit {problem.config["upload"]["time_limit"]}s). No HTML generated.',flush=True)

if __name__=='__main__': main()
