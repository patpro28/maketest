"""Generate and verify ten direct-descent SEG1 problems without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import logging
from pathlib import Path
import random
import subprocess
import sys
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(ROOT))
import toml
from problem import Problem
from check import audit_statement, run
from check_foundations import checked_compile
from check_remaining import check_checker

NAMES = [f'segtree{k}' for k in range(100, 200, 10)]
ORACLE = HERE / 'oracle_search'
LIMITS = {100:(0,1),110:(1,10**9),120:(0,1),130:(0,10**9),140:(0,10**9),
          150:(0,10**9),160:(-10**9,10**9),170:(0,10**9),180:(0,10**9),190:(0,10**9)}


def encode(a, ops):
    return f'{len(a)} {len(ops)}\n' + ' '.join(map(str, a)) + '\n' + ''.join(' '.join(map(str, op)) + '\n' for op in ops)


def decode(data):
    lines = data.splitlines()
    n, q = map(int, lines[0].split())
    a = list(map(int, lines[1].split()))
    ops = [tuple(map(int, line.split())) for line in lines[2:]]
    assert len(a) == n and len(ops) == q
    return a, ops


def brute(kind, data):
    a, ops = decode(data)
    out = []
    for op in ops:
        if kind == 140:
            answer = next((i for i,x in enumerate(a) if x >= op[0]), -1)
            out.append(str(answer + 1 if answer != -1 else -1))
            if answer != -1: a[answer] -= op[0]
            continue
        if op[0] == 1:
            i = op[1] - 1
            a[i] = 1 - a[i] if kind in (100,120) else op[2]
            continue
        if kind == 100: answer = [next((i+1 for i,x in enumerate(a) if x == 0), -1)]
        elif kind == 110:
            candidates = [i+1 for i,x in enumerate(a) if x != op[1]]
            answer = [candidates[0], candidates[-1]] if candidates else [-1,-1]
        elif kind == 120 or (kind == 190 and op[0] == 4):
            candidates = [i+1 for i,x in enumerate(a) if x > 0]
            answer = [candidates[op[1]-1] if len(candidates) >= op[1] else -1]
        elif kind == 130 or (kind == 190 and op[0] == 3):
            total = 0; result = -1
            for i,x in enumerate(a):
                total += x
                if total >= op[1]: result = i+1; break
            answer = [result]
        elif kind == 150: answer = [next((i+1 for i,x in enumerate(a) if x <= op[1]), -1)]
        elif kind == 160:
            _,l,r,low,high = op
            answer = [next((i+1 for i in range(l-1,r) if a[i] < low or a[i] > high), -1)]
        elif kind in (170,180):
            l,budget = op[1:3]; total = 0; values = []; result = l-1
            for i in range(l-1,len(a)):
                values.append(a[i]); total += a[i]
                if total > budget: break
                if kind == 180 and max(values)-min(values) > op[3]: break
                result = i+1
            answer = [result]
        elif kind == 190: answer = [next((i+1 for i,x in enumerate(a) if x >= op[1]), -1)]
        else: raise ValueError(kind)
        out.extend(map(str, answer))
    return out


def check_case(p, kind, data):
    run(p/'verifier', data)
    expected = brute(kind, data)
    assert run(p/'sol/correct', data).split() == expected, (p,'solution',data,expected)
    assert run(ORACLE, data, kind).split() == expected, (p,'reference',data,expected)


def exhaustive_queries(kind, n):
    if kind == 100: return [(2,)]
    if kind == 110: return [(2,c) for c in [1,2,3,4]]
    if kind == 120: return [(2,k) for k in range(1,n+1)]
    if kind == 130: return [(2,s) for s in [1,2,3,4,2*n,2*n+1]]
    if kind == 140: return [(x,) for x in [1,1,2,2,3,1,3,2]]
    if kind == 150: return [(2,x) for x in [0,1,2,3,10**9]]
    if kind == 160: return [(2,l,r,u,v) for l in range(1,n+1) for r in range(l,n+1)
                            for u,v in [(-2,2),(-1,-1),(-1,0),(-1,1),(0,0),(0,1),(1,1)]]
    if kind == 170: return [(2,l,b) for l in range(1,n+1) for b in [0,1,2,3,2*n]]
    if kind == 180: return [(2,l,b,d) for l in range(1,n+1) for b in [0,1,2,2*n] for d in [0,1,2]]
    return [(2,x) for x in [1,2,3]] + [(3,s) for s in [1,2,3,2*n,2*n+1]] + [(4,k) for k in range(1,n+1)]


def small_checks(p, kind):
    alphabet = [0,1] if kind in (100,120) else [1,2,3] if kind == 110 else [-1,0,1] if kind == 160 else [0,1,2]
    count = 0
    for n in range(1,5):
        for a in itertools.product(alphabet, repeat=n):
            queries = exhaustive_queries(kind,n)
            ops = list(queries)
            if kind != 140:
                for i in range(1,n+1):
                    for x in alphabet:
                        ops.append((1,i) if kind in (100,120) else (1,i,x))
                        ops.extend(queries)
            check_case(p,kind,encode(a,ops)); count += 1
    rng = random.Random(20261020 + 2000000 + kind)
    low,high = LIMITS[kind]
    values = [x for x in [-10**9,-7,-1,0,1,2,3,7,10**9] if low <= x <= high]
    for _ in range(150):
        n = rng.randint(1,30); a = rng.choices(values,k=n); ops = []
        for _ in range(rng.randint(1,150)):
            if kind == 140: ops.append((rng.choice([1,2,3,7,10**9]),)); continue
            if rng.randrange(2):
                i=rng.randint(1,n); ops.append((1,i) if kind in (100,120) else (1,i,rng.choice(values))); continue
            if kind == 100: op=(2,)
            elif kind == 110: op=(2,rng.choice(values))
            elif kind == 120: op=(2,rng.randint(1,n))
            elif kind == 130: op=(2,rng.choice([1,2,7,10**9,3*10**9,10**18]))
            elif kind == 150: op=(2,rng.choice(values))
            elif kind == 160:
                l,r=sorted([rng.randint(1,n),rng.randint(1,n)]); u,v=sorted(rng.choices(values,k=2)); op=(2,l,r,u,v)
            elif kind == 170: op=(2,rng.randint(1,n),rng.choice([0,1,2,7,10**9,10**18]))
            elif kind == 180: op=(2,rng.randint(1,n),rng.choice([0,1,2,7,10**9,10**18]),rng.choice([0,1,2,7,10**9]))
            else:
                t=rng.randint(2,4); op=(t,rng.choice([1,2,7,10**9]) if t==2 else rng.choice([1,2,7,10**9,10**18]) if t==3 else rng.randint(1,n))
            ops.append(op)
        check_case(p,kind,encode(a,ops)); count += 1
    if kind in (160,170,180,190):
        a=[0]*1001
        if kind == 160: ops=[(1,500,10**9),(2,499,501,0,0),(1,500,0),(1,501,-10**9),(2,500,502,0,0),(2,502,1001,0,0)]
        elif kind == 170: ops=[(2,1,0),(1,500,10**9),(2,499,0),(2,501,0),(2,500,10**9),(1,501,1),(2,500,10**9)]
        elif kind == 180: ops=[(2,1,0,0),(1,500,10**9),(2,499,10**18,0),(2,500,10**18,0),(2,500,10**9,10**9),(1,501,10**9),(2,500,2*10**9,0)]
        else: ops=[(1,500,10),(1,501,1),(2,2),(3,2),(4,2),(1,500,0),(3,1),(4,1),(2,2)]
        check_case(p,kind,encode(a,ops)); count += 1
    if kind == 140:
        check_case(p,kind,encode([3,1],[(4,),(3,),(1,),(1,)])); count += 1
    return count


def valid_query(kind,n):
    return {100:(2,),110:(2,1),120:(2,1),130:(2,1),140:(1,),150:(2,0),
            160:(2,1,n,0,0),170:(2,1,0),180:(2,1,0,0),190:(2,1)}[kind]


def check_invalid_input(p,kind):
    low,high=LIMITS[kind]; base=1 if kind==110 else 0; a=[base]
    valid=encode(a,[valid_query(kind,1)])
    bad=[valid+'0\n',valid.rsplit('\n',2)[0]+'\n']
    bad += [f'{n} {q}\n' for n,q in [(0,1),(200001,1),(1,0),(1,200001)]]
    bad += [encode([x],[valid_query(kind,1)]) for x in [low-1,high+1]]
    if kind==140:
        bad += [encode(a,[(0,)]),encode(a,[(10**9+1,)]),encode(a,[(1,1)])]
    else:
        bad += [encode(a,[(5 if kind==190 else 3,1)]),encode(a,[(1,0)]),encode(a,[(1,2)])]
        if kind in (100,120): bad.append(encode(a,[(1,1,0)]))
        else:
            bad += [encode(a,[(1,1)]),encode(a,[(1,0,base)]),encode(a,[(1,2,base)])]
            bad += [encode(a,[(1,1,x)]) for x in [low-1,high+1]]
    extras={100:[(2,1)],110:[(2,0),(2,10**9+1),(2,)],120:[(2,0),(2,2),(2,)],
            130:[(2,0),(2,10**18+1),(2,)],150:[(2,-1),(2,10**9+1),(2,)],
            160:[(2,0,1,0,0),(2,1,2,0,0),(2,1,1,1,0),(2,1,1,-10**9-1,0),(2,1,1,0,10**9+1),(2,1,1)],
            170:[(2,0,0),(2,2,0),(2,1,-1),(2,1,10**18+1),(2,1)],
            180:[(2,0,0,0),(2,2,0,0),(2,1,-1,0),(2,1,10**18+1,0),(2,1,0,-1),(2,1,0,10**9+1),(2,1,0)],
            190:[(2,0),(2,10**9+1),(3,0),(3,10**18+1),(4,0),(4,2),(2,)]}
    bad += [encode(a,[op]) for op in extras.get(kind,[])]
    if kind==160: bad.append(encode([base,base],[(2,2,1,0,0)]))
    for data in bad:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(p,'accepted invalid input',data)
    return len(bad)


def audit_coverage(problem,kind):
    p=problem.basedir; files=sorted((p/'in').glob('*.in')); assert len(files)==36
    dimensions=[]; search_types=set()
    for path in files:
        a,ops=decode(path.read_text()); dimensions.append((len(a),len(ops)))
        if kind!=140: search_types.update(op[0] for op in ops if op[0]!=1)
    assert (200000,200000) in dimensions
    assert any(n==1 for n,_ in dimensions) and any(n&(n-1) for n,_ in dimensions)
    if kind!=140: assert (p/'out/edge_10.out').read_text()==''
    if kind==190: assert search_types=={2,3,4}
    if kind==130: assert '-1' in (p/'out/example_01.out').read_text().split()
    if kind==140:
        answer=(p/'out/max_01.out').read_text().split(); assert answer[0]=='1' and answer[-1]=='200000'
    if kind==180: assert '0' in (p/'out/edge_00.out').read_text().split()
    template=toml.load(ROOT/'custom/segtree012/info.toml')['upload']
    assert problem.config['upload']==template
    assert problem.config['timelimit']==template['time_limit']==1.0
    source=(p/'sol/correct.cpp').read_text()
    assert 'lower_bound' not in source and 'upper_bound' not in source and 'Node query(' not in source


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args(); logging.basicConfig(level=logging.ERROR,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem]
    sources=[HERE/'oracle_search.cpp']
    for problem in problems:
        problem.health_check(); problem.generate_params_h()
        sources.extend([problem.basedir/'sol/correct.cpp',problem.checker,problem.verifier])
        sources.extend(problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp'))
    print(f'Compiling {len(problems)} SEG1 problems...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(checked_compile,sources): pass
    total=0
    for problem in problems:
        started=time.monotonic(); p=problem.basedir; kind=int(p.name[7:])
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True); problem.judge(p/'sol/correct.cpp',{})
        assert problem.check_all_solutions_used()
        audit_statement(p,with_subtask=False); audit_coverage(problem,kind)
        for test in problem.config['tests']:
            if not test['name'].endswith('.cpp'): continue
            exe=p/'gen'/Path(test['name']).stem
            for seed in range(test['number']):
                assert run(exe,'',seed)==(p/'in'/f'{exe.name}_{seed:02}.in').read_text()
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text(); expected=(p/'out'/path.with_suffix('.out').name).read_text().split()
            assert run(ORACLE,data,kind).split()==expected,(path,'reference differs')
            if path.stem.startswith(('edge','small','example')): assert brute(kind,data)==expected,(path,'brute differs')
        count=small_checks(p,kind); total+=count
        invalid=check_invalid_input(p,kind); check_checker(p,kind)
        if args.update_hashes: problem.ignore_warning=True; problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: 36 generated tests, {count} exhaustive/random cases, {invalid} invalid inputs; 1s limit, checker, samples, upload, reproducibility, hashes OK ({time.monotonic()-started:.1f}s)',flush=True)
    print(f'All SEG1 checks passed: {36*len(problems)} generated tests and {total} additional cases; no Subtask or HTML.',flush=True)


if __name__=='__main__': main()
