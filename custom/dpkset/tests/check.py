"""Full checks without HTML. Use --update-hashes for intentional data changes."""
import itertools
import json
import logging
import math
import os
from pathlib import Path
import random
import shutil
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))
from problem import Problem, compile as compile_cpp
if 'CXX' not in os.environ and shutil.which('g++-15') is None:
    os.environ['CXX'] = 'c++'
P = ROOT / 'custom/dpkset'
MOD = 10**9+7
logging.basicConfig(level=logging.INFO, format='%(message)s')
problem = Problem(ROOT,P)
problem.ignore_warning = False
problem.health_check()
problem.generate_params_h()
problem.compile_correct()
problem.compile_checker()
problem.compile_verifier()
problem.compile_gens()
problem.make_inputs()
problem.verify_inputs()
problem.make_outputs(True)
problem.judge(P/'sol/correct.cpp',{})
assert problem.check_all_solutions_used()
assert (P/'out/example_00.out').read_text() == '45 1\n'
compile_cpp(P/'tests/oracle.cpp',ROOT)

def run(exe,data):
    return tuple(map(int,subprocess.check_output([str(exe)],input=data.encode()).split()))

def pack(a,x):
    return f'{len(x)} {len(a)}\n'+' '.join(map(str,a))+'\n'+' '.join(map(str,x))+'\n'

def brute(a,x):
    best,ways = None,0
    for d in range(len(a)):
        b = a[:d]+a[d+1:]
        for idx in itertools.combinations(range(len(x)),len(b)):
            value = sum(v*x[i] for v,i in zip(b,idx))
            if best is None or value > best: best,ways=value,1
            elif value == best: ways += 1
    return best, ways % MOD

cases = []
# Exhaust all tiny signed inputs for n=3, all valid k.
for k in range(1,4):
    for a in itertools.product((-1,0,1),repeat=k):
        for x in itertools.product((-1,0,1),repeat=3): cases.append((list(a),list(x)))
rng = random.Random(20260913)
for _ in range(700):
    n = rng.randint(1,10); k = rng.randint(1,n)
    vals = [-1000000000,-3,-1,0,1,3,1000000000]
    cases.append(([rng.randint(-3,3) for _ in range(k)], [rng.choice(vals) for _ in range(n)]))
for a,x in cases:
    data = pack(a,x)
    assert run(P/'sol/correct',data) == brute(a,x), data
print(f'Exhaustive enumeration passed for {len(cases)} cases.',flush=True)
for prefix in ('example','sub01','sub02','sub03'):
    for path in sorted((P/'in').glob(prefix+'_*.in')):
        actual = run(P/'tests/oracle',path.read_text())
        expected = tuple(map(int,(P/'out'/path.with_suffix('.out').name).read_text().split()))
        assert actual == expected, path
print('Independent fixed-deletion DP passed on all 30 files of subtasks 1-3.',flush=True)

# Subtask membership, closed-form counts, and large special cases.
formula_checks = 0
for path in sorted((P/'in').glob('*.in')):
    nums = list(map(int,path.read_text().split()))
    n,k = nums[:2]; a=nums[2:2+k]; x=nums[2+k:]
    assert len(x)==n and k<=n and k<=100
    if path.stem.startswith('sub01') or path.stem.startswith('example'): assert n<=20
    if path.stem.startswith('sub02'): assert n<=200
    if path.stem.startswith('sub03'): assert n<=5000
    if path.stem.startswith('sub04'): assert len(set(a))==k
    expected = tuple(map(int,(P/'out'/path.with_suffix('.out').name).read_text().split()))
    if k==1:
        actual=(0,1)
    elif len(set(x))==1:
        scores=[(sum(a)-v)*x[0] for v in a]
        best=max(scores)
        actual=(best,scores.count(best)*math.comb(n,k-1)%MOD)
    elif all(v==0 for v in a):
        actual=(0,k*math.comb(n,k-1)%MOD)
    else:
        continue
    assert actual==expected,path
    formula_checks += 1
print(f'All subtask constraints checked; {formula_checks} closed-form checks passed.',flush=True)

# Bad input and deliberately wrong output must be rejected.
valid=pack([1,1],[1,2,3])
invalid=['0 1\n0\n\n','200001 1\n0\n','2 3\n1 2 3\n1 2\n',
         '101 101\n','1 0\n\n0\n','1 1\n101\n0\n','1 1\n-101\n0\n',
         '1 1\n0\n1000000001\n','1 1\n0\n-1000000001\n',
         '2 1\n0\n1\n',valid+'4\n']
for data in invalid:
    assert subprocess.run([str(P/'verifier')],input=data.encode(),capture_output=True).returncode!=0
with tempfile.TemporaryDirectory() as tmp:
    tmp=Path(tmp)
    inp,ans,out=(tmp/name for name in ('in','ans','out'))
    inp.write_text(valid); ans.write_text('3 2\n')
    for data,ok in [('3 2\n',True),(' 3 2 \n',True),('2 2\n',False),('3 1\n',False),
                    ('3\n',False),('3 2 0\n',False),('3 -1\n',False),('3 1000000007\n',False),
                    ('3.0 2\n',False),('x 2\n',False),('',False)]:
        out.write_text(data)
        result=subprocess.run([str(P/'checker'),str(inp),str(out),str(ans)],capture_output=True)
        assert (result.returncode==0)==ok,(data,result.stderr)
    for a,x in [([100]*100,[-10**9]*100),([100]*100,[10**9]*100),([0],[0])]:
        inp.write_text(pack(a,x))
        result=run(P/'sol/correct',inp.read_text())
        ans.write_text(' '.join(map(str,result))+'\n');out.write_text(ans.read_text())
        assert subprocess.run([str(P/'checker'),str(inp),str(out),str(ans)],capture_output=True).returncode==0
print('Validator and checker acceptance/rejection tests passed.',flush=True)
if '--update-hashes' in sys.argv:
    (P/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
problem.assert_hashes()
print('All 50 input/output hashes verified. No HTML generated.',flush=True)
