"""Generate and verify the five one-state tree-DP starter problems without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import hashlib
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
import zipfile

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0,str(ROOT))
sys.path.insert(0,str(HERE))
from problem import Problem
from check import build,run,labelled_tree
from check_binary import audit_statement
from check_ternary import check_upload

NAMES = [f"dptree{k}" for k in range(32,37)]
ORACLE = HERE/"oracle_basic"
MOD = 10**9+7


def encode(kind,n,edges,values=None):
    data = f"{n}\n"
    if kind in (32,34,35):
        data += " ".join(map(str,values))+"\n"
    return data+"".join(f"{u} {v}\n" for u,v in edges)


def decode(kind,data):
    lines = data.splitlines()
    n = int(lines[0])
    values = list(map(int,lines[1].split())) if kind in (32,34,35) else []
    edges = [tuple(map(int,line.split())) for line in lines[2 if values else 1:]]
    assert len(edges) == n-1
    return n,edges,values


def numbers(executable,data,*args):
    return list(map(int,run(executable,data,*args).split()))


def check_case(p,kind,data,expected=None):
    run(p/"verifier",data)
    if expected is None:
        expected = numbers(ORACLE,data,kind)
    actual = numbers(p/"sol/correct",data)
    assert actual == expected,(p.name,data,expected,actual)
    if kind in (32,33,35):
        assert numbers(ORACLE,data,kind,"full") == expected,(p.name,"full oracle",data)


def exact_connected_tree(target):
    """Build a rooted tree with exactly target connected sets containing its root."""
    steps = []
    while target > 2:
        if target%2:
            steps.append("inc")
            target -= 1
        else:
            steps.append("double_inc2")
            target = target//2-1
    assert target in (1,2)
    n,root = target,0
    edges = [(0,1)] if target == 2 else []
    for step in reversed(steps):
        edges.append((n,root))
        root = n
        n += 1
        if step == "double_inc2":
            edges.append((root,n))
            n += 1
    mapping = {root:1}
    mapping.update({u:i+2 for i,u in enumerate(v for v in range(n) if v != root)})
    return n,[(mapping[u],mapping[v]) for u,v in edges]


def small_checks(p,kind):
    rng = random.Random(20261028+kind)
    weighted = kind in (32,34,35)
    count = 0
    for n in range(1,6):
        for seq in itertools.product(range(n),repeat=max(0,n-2)):
            raw = labelled_tree(n,seq)
            for variant in range(2 if weighted else 1):
                alphabet = [-10**9,-1,0,1,10**9] if kind == 34 else [0,1,7,10**9]
                values = rng.choices(alphabet,k=n)
                if variant == 0:
                    values = [0]*n
                check_case(p,kind,encode(kind,n,raw,values))
                count += 1
    if weighted:
        for n in range(1,4):
            for seq in itertools.product(range(n),repeat=max(0,n-2)):
                edges = labelled_tree(n,seq)
                for values in itertools.product([-1,0,1] if kind == 34 else [0,1,2],repeat=n):
                    check_case(p,kind,encode(kind,n,edges,values))
                    count += 1
    for _ in range(240):
        n = rng.randint(1,16)
        raw = labelled_tree(n,[rng.randrange(n) for _ in range(max(0,n-2))])
        edges = [(u,v) if rng.randrange(2) else (v,u) for u,v in raw]
        rng.shuffle(edges)
        values = rng.choices([-10**9,-7,-1,0,1,8,10**9] if kind == 34 else [0,1,7,10**9],k=n)
        check_case(p,kind,encode(kind,n,edges,values))
        count += 1
    if kind == 36:
        for target in [MOD-1,MOD,MOD+1]:
            n,edges = exact_connected_tree(target)
            check_case(p,kind,encode(kind,n,edges),[target%MOD])
            count += 1
    return count


def connected_formula(n,edges):
    adj = [[] for _ in range(n)]
    for u,v in edges:
        adj[u-1].append(v-1)
        adj[v-1].append(u-1)
    degree = list(map(len,adj))
    if max(degree) <= 2:
        answer = 1
        for start in adj[0]:
            previous,u,length = 0,start,1
            while len(adj[u]) == 2:
                v = adj[u][0] if adj[u][0] != previous else adj[u][1]
                previous,u,length = u,v,length+1
            answer = answer*(length+1)%MOD
        return answer
    if max(degree) == n-1:
        return pow(2,n-1,MOD) if degree[0] == n-1 else (1+pow(2,n-2,MOD))%MOD
    return None


def audit_generated(p,kind):
    paths = sorted((p/"in").glob("*.in"))
    assert len(paths) == 38
    sizes,direct,full,analytical = [],0,0,0
    for path in paths:
        data = path.read_text()
        n,edges,values = decode(kind,data)
        sizes.append(n)
        answer = list(map(int,(p/"out"/path.with_suffix(".out").name).read_text().split()))
        assert len(answer) == (n if kind in (32,33) else 1),path
        if n <= 20:
            assert numbers(ORACLE,data,kind) == answer,(path,"direct oracle")
            direct += 1
        if kind != 36:
            assert numbers(ORACLE,data,kind,"full") == answer,(path,"full oracle")
            full += 1
        else:
            expected = connected_formula(n,edges)
            if expected is not None:
                assert answer == [expected],(path,expected,answer)
                analytical += 1
        if kind == 32:
            assert answer[0] == sum(values)
            assert all(a <= result <= sum(values) for a,result in zip(values,answer)) if n <= 20 else True
        elif kind == 33:
            assert all(0 <= x < n for x in answer)
        elif kind == 35:
            assert 0 <= answer[0] <= values[0]
        elif kind == 36:
            assert 0 <= answer[0] < MOD
    assert min(sizes) == 1 and sizes.count(200000) == 8
    return direct,full,analytical


def invalid_inputs(p,kind):
    sample = (p/"gen/example_00.in").read_text()
    bad = ["","0\n","200001\n",sample+"0\n",sample.rsplit("\n",2)[0]+"\n"]
    for edges in [
        [(1,1),(1,2),(2,3)],[(1,2),(2,1),(3,4)],[(1,2),(2,3),(3,1)],
        [(0,2),(2,3),(3,4)],[(1,5),(2,3),(3,4)]]:
        bad.append(encode(kind,4,edges,[0]*4))
    if kind in (32,34,35):
        for x in ([-1000000001,1000000001] if kind == 34 else [-1,1000000001]):
            bad.append(encode(kind,1,[],[x]))
        bad += ["2\n0\n1 2\n","1\n0 0\n"]
    for data in bad:
        result = subprocess.run([str(p/"verifier")],input=data,text=True,capture_output=True)
        assert result.returncode != 0,(p.name,"accepted invalid input",data)
    return len(bad)


def check_checker(p):
    count = 0
    with tempfile.TemporaryDirectory() as folder:
        folder = Path(folder)
        inp,actual,expected = [folder/name for name in ("input","actual","expected")]
        for case in ("example_00","example_01","max_00"):
            inp.write_bytes((p/"in"/f"{case}.in").read_bytes())
            good = (p/"out"/f"{case}.out").read_text()
            expected.write_text(good)
            tokens = good.split()
            wrong_first,wrong_last = list(tokens),list(tokens)
            wrong_first[0] = str(int(tokens[0])+1)
            wrong_last[-1] = str(int(tokens[-1])+1)
            checks = [
                (good,True),(" \n\t"+"\n\t".join(tokens)+" \n",True),
                ("",False),(" ".join(wrong_first),False),(" ".join(wrong_last),False),
                (" ".join(tokens[:-1]),False),(good+"0\n",False),
                (good+"garbage\n",False),("1.0\n",False),
                ("999999999999999999999999\n",False)]
            if len(tokens) > 2:
                middle = list(tokens)
                i = len(tokens)//2
                middle[i] = str(int(tokens[i])+1)
                checks.append((" ".join(middle),False))
            if len(tokens) > 1 and tokens[0] != tokens[-1]:
                swap = list(tokens)
                swap[0],swap[-1] = swap[-1],swap[0]
                checks.append((" ".join(swap),False))
            for text,accepted in checks:
                actual.write_text(text)
                result = subprocess.run([str(p/"checker"),str(inp),str(actual),str(expected)],
                                        capture_output=True)
                assert (result.returncode == 0) == accepted,(p.name,case,result.stderr)
                count += 1
    return count


def audit_package(p):
    hashes = json.loads((p/"hash.json").read_text())
    files = list((p/"in").glob("*.in"))+list((p/"out").glob("*.out"))
    actual = {f.name:hashlib.sha256(f.read_bytes()).hexdigest() for f in files}
    assert len(actual) == 76 and actual == hashes
    with zipfile.ZipFile(p/(p.name+".zip")) as z:
        assert len(z.namelist()) == 76 and set(z.namelist()) == set(hashes)
        assert z.testzip() is None
        for name in z.namelist():
            assert hashlib.sha256(z.read(name)).hexdigest() == hashes[name]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--problem",nargs="+",choices=NAMES,default=NAMES)
    parser.add_argument("--update-hashes",action="store_true")
    args = parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format="%(message)s")
    problems = [Problem(ROOT,ROOT/"custom"/name) for name in args.problem]
    sources = [ORACLE.with_suffix(".cpp")]
    for problem in problems:
        problem.health_check()
        problem.generate_params_h()
        p = problem.basedir
        sources += [p/"sol/correct.cpp",problem.checker,problem.verifier]
        sources += [p/"gen"/t["name"] for t in problem.config["tests"] if t["name"].endswith(".cpp")]
    print(f"Compiling {len(sources)} programs...",flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        list(pool.map(build,sources))
    for problem in problems:
        started = time.monotonic()
        p,kind = problem.basedir,int(problem.basedir.name[6:])
        problem.make_inputs()
        problem.verify_inputs()
        problem.make_outputs(True)
        problem.judge(p/"sol/correct.cpp",{})
        assert problem.check_all_solutions_used()
        audit_statement(p)
        editorial = (p/"solution.md").read_text()
        assert not re.search(r"kiểm thử|oracle|verifier|checker|benchmark|bộ sinh",editorial,re.I)
        direct,full,analytical = audit_generated(p,kind)
        for test in problem.config["tests"]:
            if test["name"].endswith(".cpp"):
                exe = p/"gen"/Path(test["name"]).stem
                for seed in range(test["number"]):
                    assert run(exe,"",seed) == (p/"in"/f"{exe.name}_{seed:02}.in").read_text()
        count = small_checks(p,kind)
        invalid = invalid_inputs(p,kind)
        checker_count = check_checker(p)
        if args.update_hashes:
            problem.ignore_warning = True
            problem.write_hashes()
        problem.assert_hashes()
        problem.zip()
        audit_package(p)
        check_upload(problem)
        print(f"{p.name}: 38 tests ({direct} direct, {full} full-reference, {analytical} formula), "
              f"{count} exhaustive/random/special checks, {invalid} invalid inputs, "
              f"{checker_count} checker checks; samples, editorial, reproducibility, hashes, ZIP, "
              f"upload payload OK ({time.monotonic()-started:.1f}s)",flush=True)
    print("All checks passed; no HTML or network upload performed.",flush=True)


if __name__ == "__main__":
    main()
