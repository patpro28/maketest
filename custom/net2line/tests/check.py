"""Full package validation without HTML; --update-hashes records intentional test changes."""
import itertools
import json
import logging
import os
import shutil
from pathlib import Path
import random
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT))
from problem import Problem, compile as compile_cpp

# Respect an explicit compiler; fall back to the system C++ compiler.
if 'CXX' not in os.environ and shutil.which('g++-15') is None:
    os.environ['CXX'] = 'c++'

P = ROOT / 'custom/net2line'
logging.basicConfig(level=logging.INFO, format='%(message)s')
problem = Problem(ROOT, P)
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
problem.judge(P / 'sol/correct.cpp', {})
assert problem.check_all_solutions_used()
assert (P / 'out/example_00.out').read_text() == '18\n24\n'
compile_cpp(P / 'tests/oracle.cpp', ROOT)

def run(exe, data):
    return subprocess.check_output([str(exe)], input=data.encode()).decode()

def pack(cases):
    return str(len(cases)) + '\n' + ''.join(str(len(w))+'\n'+'\n'.join(' '.join(map(str,a)) for a in (u,v,w))+'\n' for u,v,w in cases)

cases = [([], [], [w]) for w in (1, 2, 9999, 10000)]
cases += [([a], [b], [c,d]) for a,b,c,d in itertools.product(range(1,6), repeat=4)]
rng = random.Random(20260913)
for _ in range(1500):
    n = rng.randint(1,5)
    cases.append(tuple([rng.randint(1, 20) for _ in range(k)] for k in (n-1,n-1,n)))
for start in range(0, len(cases), 20):
    data = pack(cases[start:start+20])
    assert run(P/'sol/correct', data) == run(P/'tests/oracle', data), data
for path in sorted((P/'in').glob('small_*.in')):
    assert run(P/'tests/oracle', path.read_text()) == (P/'out'/path.with_suffix('.out').name).read_text()
print(f'Brute-force comparison passed: {len(cases)} extra cases and all small files.', flush=True)

# Independent Kruskal oracle for the even-weight group.
for path in sorted((P/'in').glob('even_*.in')):
    nums = iter(map(int,path.read_text().split()))
    answers = []
    for _ in range(next(nums)):
        n = next(nums)
        edges = []
        for row in range(2):
            for i in range(n-1): edges.append((next(nums), row*n+i, row*n+i+1))
        for i in range(n): edges.append((next(nums), i, n+i))
        assert all(w % 2 == 0 for w,a,b in edges)
        par = list(range(2*n))
        size = [1]*(2*n)
        def root(x):
            while par[x] != x:
                par[x] = par[par[x]]
                x = par[x]
            return x
        total = 0
        for w,a,b in sorted(edges):
            a,b = root(a),root(b)
            if a != b:
                if size[a] < size[b]: a,b = b,a
                par[b] = a
                size[a] += size[b]
                total += w
        answers.append(total)
    assert answers == list(map(int,(P/'out'/path.with_suffix('.out').name).read_text().split()))
print('Independent MST comparison passed for all even-weight files.', flush=True)

# Validator rejects bounds violations, missing values and trailing data.
valid = '1\n2\n1\n1\n1 1\n'
invalid = ['0\n', '21\n', '1\n0\n', '1\n100001\n',
           valid.replace('1 1\n','0 1\n'), valid.replace('1 1\n','10001 1\n'),
           valid.replace('1 1\n','1\n'), valid+'7\n']
for data in invalid:
    assert subprocess.run([str(P/'verifier')], input=data.encode(), capture_output=True).returncode != 0
with tempfile.TemporaryDirectory() as tmp:
    tmp = Path(tmp)
    inp,ans,out = (tmp/x for x in ('in','ans','out'))
    inp.write_text(valid)
    ans.write_text('4\n')
    for data, accepted in [('4\n',True), (' 4 \n',True), ('3\n',False), ('-1\n',False), ('',False), ('4\n0\n',False), ('x\n',False), ('4.0\n',False), ('999999999999999999999\n',False)]:
        out.write_text(data)
        result = subprocess.run([str(P/'checker'),str(inp),str(out),str(ans)],capture_output=True)
        assert (result.returncode == 0) == accepted, (data,result.stderr)
    inp.write_text('1\n1\n\n\n1\n')
    ans.write_text('-1\n'); out.write_text('-1\n')
    assert subprocess.run([str(P/'checker'),str(inp),str(out),str(ans)],capture_output=True).returncode == 0
print('Validator and checker rejection/acceptance checks passed.', flush=True)
if '--update-hashes' in sys.argv:
    (P/'hash.json').write_text(json.dumps(problem.calc_hashes(), indent=2, sort_keys=True)+'\n')
problem.assert_hashes()
print('All 40 input/output hashes verified. No HTML generated.', flush=True)
