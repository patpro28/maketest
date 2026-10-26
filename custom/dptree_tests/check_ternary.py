"""Build and verify DPTREE27--DPTREE31, including upload payloads, without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from functools import lru_cache
import hashlib
import itertools
import json
import logging
from pathlib import Path
import random
import subprocess
import sys
import time
import zipfile

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0,str(ROOT))
sys.path.insert(0,str(HERE))
import toml
from problem import Problem
from problem_upload import ProblemUpload
from check import build,run,labelled_tree,check_checker
from check_binary import audit_statement

NAMES = [f"dptree{k}" for k in range(27,32)]
ORACLE = HERE/"oracle_ternary"
MOD = 10**9+7


def encode(kind,n,edges,values=None):
    data = f"{n}\n"
    if kind in (27,29):
        data += " ".join(map(str,values))+"\n"
    data += "".join(" ".join(map(str,e if kind in (29,30) else e[:2]))+"\n" for e in edges)
    return data


def decode(kind,data):
    lines = data.splitlines()
    n = int(lines[0])
    values = list(map(int,lines[1].split())) if kind in (27,29) else []
    edges = [tuple(map(int,s.split())) for s in lines[2 if values else 1:]]
    assert len(edges) == n-1
    return n,edges,values


def encode_expr(nodes,target):
    return f"{len(nodes)} {target}\n"+"".join(" ".join(map(str,node))+"\n" for node in nodes)


def parse_expr(data):
    lines = data.splitlines()
    n,target = map(int,lines[0].split())
    nodes = [tuple(map(int,s.split())) for s in lines[1:]]
    assert len(nodes) == n
    return n,target,nodes


def check_case(p,kind,data):
    run(p/"verifier",data)
    expected = int(run(ORACLE,data,kind))
    actual = int(run(p/"sol/correct",data))
    assert actual == expected,(p.name,data,expected,actual)


@lru_cache(None)
def shapes(m):
    if m == 0:
        return (None,)
    return tuple((a,b) for left in range(m)
                 for a in shapes(left) for b in shapes(m-1-left))


def expression_nodes(shape,operators,costs,rng=None):
    operators,costs = iter(operators),iter(costs)
    nodes = []
    def visit(tree):
        u = len(nodes)
        nodes.append(None)
        if tree is None:
            nodes[u] = (0,*next(costs))
        else:
            op = next(operators)
            x,y = visit(tree[0]),visit(tree[1])
            nodes[u] = (op,x+1,y+1)
        return u
    visit(shape)
    if rng is None:
        return nodes
    n = len(nodes)
    rest = list(range(1,n))
    rng.shuffle(rest)
    labels = [0]+rest
    out = [None]*n
    for u,node in enumerate(nodes):
        out[labels[u]] = node if node[0] == 0 else (
            node[0],labels[node[1]-1]+1,labels[node[2]-1]+1)
    return out


def expression_checks(p):
    rng = random.Random(2026102528)
    count = 0
    for m in range(4):
        for shape in shapes(m):
            for ops in itertools.product([1,2],repeat=m):
                for variant in range(2):
                    costs = [(0,0,0)]*(m+1) if variant == 0 else [
                        tuple(rng.choice([0,1,9,10**9]) for _ in range(3)) for _ in range(m+1)]
                    nodes = expression_nodes(shape,ops,costs,rng)
                    for target in range(3):
                        check_case(p,28,encode_expr(nodes,target))
                        count += 1
    alphabet = list(itertools.product([0,1],repeat=3))
    for cost in alphabet:
        for target in range(3):
            check_case(p,28,encode_expr([(0,*cost)],target))
            count += 1
    for a,b in itertools.product(alphabet,repeat=2):
        for op in [1,2]:
            for target in range(3):
                check_case(p,28,encode_expr([(op,2,3),(0,*a),(0,*b)],target))
                count += 1
    for _ in range(240):
        m = rng.randrange(8)
        shape = rng.choice(shapes(m))
        ops = rng.choices([1,2],k=m)
        costs = [tuple(rng.choice([0,1,7,10**9]) for _ in range(3)) for _ in range(m+1)]
        nodes = expression_nodes(shape,ops,costs,rng)
        check_case(p,28,encode_expr(nodes,rng.randrange(3)))
        count += 1
    return count


def small_checks(p,kind):
    if kind == 28:
        return expression_checks(p)
    rng = random.Random(20261025+kind)
    count = 0
    for n in range(1,6):
        for seq in itertools.product(range(n),repeat=max(0,n-2)):
            raw = labelled_tree(n,seq)
            for variant in range(1 if kind == 31 else 2):
                edges = [(u,v,rng.choice([-10**9,-1,0,1,10**9]) if kind == 30
                          else rng.choice([0,1,9,10**9])) for u,v in raw]
                alphabet = [-10**9,-1,0,1,10**9] if kind == 27 else [0,1,2]
                values = rng.choices(alphabet,k=n)
                if variant == 0:
                    values = [0]*n if kind == 29 else [1]*n
                check_case(p,kind,encode(kind,n,edges,values))
                count += 1
    if kind in (27,29,30):
        limit = 3 if kind == 27 else 4
        for n in range(1,limit+1):
            for seq in itertools.product(range(n),repeat=max(0,n-2)):
                raw = labelled_tree(n,seq)
                alphabet = [0,1,2] if kind == 29 else [-1,0,1]
                for values in itertools.product(alphabet,repeat=n-1 if kind == 30 else n):
                    edges = [(u,v,values[i] if kind == 30 else rng.choice([0,1,9,10**9]))
                             for i,(u,v) in enumerate(raw)]
                    check_case(p,kind,encode(kind,n,edges,values))
                    count += 1
    for _ in range(240):
        n = rng.randint(1,16)
        raw = labelled_tree(n,[rng.randrange(n) for _ in range(max(0,n-2))])
        edges = [(u,v,rng.choice([-10**9,-2,0,1,10**9]) if kind == 30
                  else rng.choice([0,1,2,17,10**9])) for u,v in raw]
        edges = [(u,v,w) if rng.randrange(2) else (v,u,w) for u,v,w in edges]
        rng.shuffle(edges)
        values = rng.choices([-10**9,-7,-1,0,1,8,10**9] if kind == 27 else [0,1,2],k=n)
        check_case(p,kind,encode(kind,n,edges,values))
        count += 1
    return count


def simple_expr(data):
    n,target,nodes = parse_expr(data)
    leaves = [node[1:] for node in nodes if node[0] == 0]
    if all(a == b == c for a,b,c in leaves):
        return sum(c[0] for c in leaves)
    ops = {node[0] for node in nodes if node[0]}
    if len(ops) <= 1:
        op = next(iter(ops),1)
        inf = 10**30
        dp = [0,inf,inf] if op == 1 else [inf,0,inf]
        for costs in leaves:
            nxt = [inf]*3
            for a in range(3):
                for b in range(3):
                    r = (a+b if op == 1 else a*b)%3
                    nxt[r] = min(nxt[r],dp[a]+costs[b])
            dp = nxt
        return dp[target]
    order,value = [0],[0]*n
    for u in order:
        if nodes[u][0]:
            order.extend([nodes[u][1]-1,nodes[u][2]-1])
    total = 0
    for u in reversed(order):
        node = nodes[u]
        if node[0] == 0:
            value[u] = min(range(3),key=lambda r: node[r+1])
            total += node[value[u]+1]
        else:
            a,b = value[node[1]-1],value[node[2]-1]
            value[u] = (a+b if node[0] == 1 else a*b)%3
    return total if value[0] == target else None


def simple_expected(kind,n,edges,values):
    degree = [0]*n
    for u,v,*_ in edges:
        degree[u-1] += 1
        degree[v-1] += 1
    star = degree.index(n-1) if n > 1 and max(degree) == n-1 else None
    if kind == 27:
        if max(values) <= 0:
            return 0
        if n == 1:
            return max(0,values[0])
        if star is not None:
            if star == 0:
                return sum(max(0,a) for a in values)
            rest = sum(max(0,a) for i,a in enumerate(values) if i not in (0,star))
            return max(x*values[0]+y*values[star]+(0 if x and y else rest)
                       for x in (0,1) for y in (0,1))
        if max(degree) <= 2 and degree[0] == 1 and len(set(values)) == 1:
            return (n-n//3)*max(0,values[0])
    elif kind == 29:
        if not (1 in values and 2 in values):
            return 0
        if all(x != 0 for x in values):
            return sum(w for u,v,w in edges if values[u-1] != values[v-1])
        if star is not None:
            red = blue = 0
            for u,v,w in edges:
                leaf = v-1 if u-1 == star else u-1
                if values[leaf] == 1:
                    red += w
                elif values[leaf] == 2:
                    blue += w
            return blue if values[star] == 1 else red if values[star] == 2 else min(red,blue)
        if not any(w for _,_,w in edges):
            return 0
    elif kind == 30:
        positive = sorted((w for _,_,w in edges if w > 0),reverse=True)
        if max(degree) <= 2:
            return sum(positive)
        if star is not None:
            return sum(positive[:2])
        if not positive:
            return 0
    elif kind == 31:
        if max(degree) <= 2:
            m = n//3
            return (m*(n+1)-3*m*(m+1)//2)%MOD
        if star is not None:
            residues = [1,0,0]
            for _ in range(n-1):
                residues = [(residues[r]+residues[(r-1)%3])%MOD for r in range(3)]
            return residues[2]
    return None


def audit_generated(p,kind):
    paths = sorted((p/"in").glob("*.in"))
    assert len(paths) == 38
    sizes,brute_count,analytical = [],0,0
    for path in paths:
        data = path.read_text()
        answer = int((p/"out"/path.with_suffix(".out").name).read_text())
        if kind == 28:
            n,_,nodes = parse_expr(data)
            expected = simple_expr(data)
            leaves = [node[1:] for node in nodes if node[0] == 0]
            assert sum(min(c) for c in leaves) <= answer <= sum(max(c) for c in leaves)
        else:
            n,edges,values = decode(kind,data)
            expected = simple_expected(kind,n,edges,values)
            if kind == 27:
                assert 0 <= answer <= sum(max(0,a) for a in values)
            elif kind == 29:
                assert 0 <= answer <= sum(w for _,_,w in edges)
            elif kind == 30:
                assert 0 <= answer <= sum(max(0,w) for _,_,w in edges)
            else:
                assert 0 <= answer < MOD
        sizes.append(n)
        if n <= (25 if kind == 28 else 20):
            assert int(run(ORACLE,data,kind)) == answer,(path,"brute differs")
            brute_count += 1
        if expected is not None:
            assert answer == expected,(path,expected,answer)
            analytical += 1
    assert min(sizes) == 1 and sizes.count(199999 if kind == 28 else 200000) == 8
    return brute_count,analytical


def invalid_inputs(p,kind):
    sample = (p/"gen/example_00.in").read_text()
    bad = ["","0\n","200001\n",sample+"0\n",sample.rsplit("\n",2)[0]+"\n"]
    if kind == 28:
        bad += [
            "0 0\n","200001 0\n","2 0\n","1 3\n0 0 0 0\n","1 -1\n0 0 0 0\n",
            "1 0\n3 0 0 0\n","1 0\n0 -1 0 0\n","1 0\n0 0 1000000001 0\n",
            "1 0\n0 0 0\n","1 0\n0 0 0 0 0\n",
            "3 0\n1 2 2\n0 0 0 0\n0 0 0 0\n",
            "3 0\n1 1 2\n0 0 0 0\n0 0 0 0\n",
            "3 0\n1 0 3\n0 0 0 0\n0 0 0 0\n",
            "3 0\n1 2 4\n0 0 0 0\n0 0 0 0\n",
            "3 0\n0 0 0 0\n1 1 3\n0 0 0 0\n",
            "5 0\n1 2 3\n1 4 5\n1 4 5\n0 0 0 0\n0 0 0 0\n",
            "5 0\n0 0 0 0\n1 3 4\n2 2 5\n0 0 0 0\n0 0 0 0\n"]
    else:
        for raw in [
            [(1,1),(1,2),(2,3)],[(1,2),(2,1),(3,4)],
            [(1,2),(2,3),(3,1)],[(0,2),(2,3),(3,4)],
            [(1,5),(2,3),(3,4)]]:
            bad.append(encode(kind,4,[(u,v,1) for u,v in raw],[0]*4))
        if kind in (27,29):
            for x in ([-1000000001,1000000001] if kind == 27 else [-1,3]):
                bad.append(encode(kind,1,[],[x]))
            bad.append("2\n0\n1 2 1\n" if kind == 29 else "2\n0\n1 2\n")
        if kind in (29,30):
            for w in ([-1,1000000001] if kind == 29 else [-1000000001,1000000001]):
                bad.append(encode(kind,2,[(1,2,w)],[0,0]))
    for data in bad:
        result = subprocess.run([str(p/"verifier")],input=data,text=True,capture_output=True)
        assert result.returncode != 0,(p.name,"accepted malformed input",data)
    return len(bad)


def check_upload(problem):
    reference = dict(toml.load(ROOT/"custom/dptree22/info.toml")["upload"])
    reference.pop("approved",None)  # Not a supported Problem Import API field.
    assert problem.config["upload"] == reference
    assert problem.config["timelimit"] == reference["time_limit"]
    upload = ProblemUpload(problem)
    assert upload.code == problem.basedir.name and upload.editorial
    assert upload.payload["time_limit"] == 1.0
    assert upload.manifest["checker"] == "standard"
    hashes = json.loads((problem.basedir/"hash.json").read_text())
    calls = []
    class Capture:
        def json(self,method,path,payload,status):
            calls.append((method,path,status))
            if method == "POST":
                assert path == "/problems" and payload["code"] == upload.code
                assert payload["name"].startswith(upload.code.upper()+" — ")
            else:
                assert method == "PUT" and path.endswith("/editorial")
                assert payload["content"] == upload.editorial
        def testcases(self,path,archive,manifest):
            calls.append(("CASES",path,200))
            assert len(manifest["cases"]) == 38
            with zipfile.ZipFile(archive) as z:
                assert len(z.namelist()) == 76 and set(z.namelist()) == set(hashes)
                for name in z.namelist():
                    assert hashlib.sha256(z.read(name)).hexdigest() == hashes[name]
    upload.upload(Capture())
    assert len(calls) == 3


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
        sources.extend([p/"sol/correct.cpp",problem.checker,problem.verifier])
        sources.extend(p/"gen"/t["name"] for t in problem.config["tests"] if t["name"].endswith(".cpp"))
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
        brute_count,analytical = audit_generated(p,kind)
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
        with zipfile.ZipFile(p/(p.name+".zip")) as archive:
            assert len(archive.namelist()) == 76 and archive.testzip() is None
        check_upload(problem)
        print(f"{p.name}: 38 tests ({brute_count} brute, {analytical} analytical), "
              f"{count} exhaustive/random checks, {invalid} invalid inputs, "
              f"{checker_count} checker checks; samples, reproducibility, hashes, ZIP, upload payload OK "
              f"({time.monotonic()-started:.1f}s)",flush=True)
    print("All checks passed; no HTML or network upload performed.",flush=True)


if __name__ == "__main__":
    main()
