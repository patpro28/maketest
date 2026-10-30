"""Generate and independently check five Sack problems without HTML export."""
import argparse
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
import heapq
import itertools
import logging
import math
import os
from pathlib import Path
import random
import re
import shlex
import subprocess
import sys
import tempfile
import time

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from problem import Problem
NAMES=['dtbasac','dttopmau','dthengap','dtcanbang','dtmatkhau']
ORACLE=Path(__file__).with_name('oracle')


def run(executable,data='',*args,timeout=120):
    return subprocess.run([str(executable),*map(str,args)],input=data,text=True,capture_output=True,check=True,timeout=timeout).stdout


def build(src):
    flags=shlex.split(os.getenv('CXXFLAGS','-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result'))
    subprocess.run([os.getenv('CXX','g++'),*flags,'-I',str(ROOT/'common'),'-o',str(src.with_suffix('')),str(src)],check=True)


def make(kind,attributes,edges,queries=None):
    n=len(attributes);queries=queries if queries is not None else [(1,0)]
    text=f'{n} {len(queries)}\n' if kind==2 else f'{n}\n'
    if kind==4:
        text+=''.join(f'{a} {w}\n' for a,w in attributes)
    else:
        text+=' '.join(map(str,attributes))+'\n'
    text+=''.join(' '.join(map(str,edge))+'\n' for edge in edges)
    if kind==2:
        text+=''.join(f'{u} {k}\n' for u,k in queries)
    return text


def labelled_tree(n,sequence):
    if n==1:return []
    degree=[1]*(n+1)
    for v in sequence:degree[v]+=1
    leaves=[v for v in range(1,n+1) if degree[v]==1];heapq.heapify(leaves);edges=[]
    for v in sequence:
        u=heapq.heappop(leaves);edges.append((u,v));degree[v]-=1
        if degree[v]==1:heapq.heappush(leaves,v)
    edges.append(tuple(leaves));return edges


def brute(kind,data):
    rows=[row.split() for row in data.splitlines()];n=int(rows[0][0]);attributes=[]
    if kind==4:
        attributes=[tuple(map(int,row)) for row in rows[1:n+1]];start=n+1
    else:
        attributes=list(map(int,rows[1]));start=2
    adj=[[] for _ in range(n)]
    for row in rows[start:start+n-1]:
        u,v=map(int,row[:2]);label=row[2] if kind==5 else ''
        adj[u-1].append((v-1,label));adj[v-1].append((u-1,label))
    parent=[-1]*n;depth=[0]*n;letters=['']*n;order=[0]
    for u in order:
        for v,label in adj[u]:
            if v!=parent[u]:parent[v]=u;depth[v]=depth[u]+1;letters[v]=label;order.append(v)
    descendants=[[u] for u in range(n)]
    for u in order[::-1]:
        if parent[u]!=-1:descendants[parent[u]]+=descendants[u]
    if kind==1:
        return [str(sum(len({attributes[x],attributes[y],attributes[z]})==3 for x,y,z in itertools.combinations(vertices,3))) for vertices in descendants]
    if kind==2:
        result=[]
        for row in rows[start+n-1:]:
            u,k=map(int,row);freq=Counter(attributes[v] for v in descendants[u-1])
            result.append(str(sum(sorted(freq.values(),reverse=True)[:k])))
        return result
    if kind==4:
        return [str(min(sum(attributes[v][1]*abs(attributes[v][0]-x) for v in vertices) for x in {attributes[v][0] for v in vertices})) for vertices in descendants]
    answer=[0]*n
    for x,y in itertools.combinations(range(n),2):
        a,b=x,y;distance=0;counts=Counter()
        while a!=b:
            if depth[a]<depth[b]:a,b=b,a
            if kind==5:counts[letters[a]]+=1
            a=parent[a];distance+=1
        if kind==3:
            answer[a]+=distance==attributes[a]
        else:
            answer[a]+=distance<=attributes[a] and sum(count%2 for count in counts.values())<=1
    return list(map(str,answer))


def small_cases(kind):
    rng=random.Random(2026103000+kind)
    for n in range(1,5):
        for sequence in itertools.product(range(1,n+1),repeat=max(0,n-2)):
            edges=labelled_tree(n,sequence)
            if kind in (1,2,4):
                choices=(1,2,3) if kind==1 else (1,2) if kind==2 else ((0,1),(5,1),(5,3))
                for attrs in itertools.product(choices,repeat=n):
                    queries=[(u,k) for u in range(1,n+1) for k in range(n+1)] if kind==2 else None
                    yield make(kind,attrs,edges,queries)
            elif kind==3:
                for attrs in ([0]*n,[1]*n,[min(2,n)]*n,[n]*n,list(range(n)),list(range(n-1,-1,-1))):
                    yield make(kind,attrs,edges)
            else:
                for labels in itertools.product('ab',repeat=n-1):
                    decorated=[(*edge,c) for edge,c in zip(edges,labels)]
                    for attrs in ([0]*n,[1]*n,[min(2,n)]*n,[n]*n,[rng.randint(0,n) for _ in range(n)]):
                        yield make(kind,attrs,decorated)
    number={1:150,2:160,3:180,4:150,5:180}[kind]
    for case in range(number):
        n=rng.randint(1,24)
        edges=labelled_tree(n,[rng.randint(1,n) for _ in range(max(0,n-2))]);rng.shuffle(edges)
        edges=[(v,u) if rng.randrange(2) else (u,v) for u,v in edges]
        if kind in (1,2):
            attrs=rng.choices([1,2,3,7,10**9],k=n)
        elif kind==4:
            attrs=[(rng.choice([0,1,5,10**9,rng.randint(0,100)]),rng.choice([1,2,1000])) for _ in range(n)]
        else:
            attrs=[rng.randint(0,n) for _ in range(n)]
        if kind==5:edges=[(*edge,rng.choice('ab' if case%2 else 'abcdefghij')) for edge in edges]
        queries=[(rng.randint(1,n),rng.randint(0,n)) for _ in range(40)] if kind==2 else None
        yield make(kind,attrs,edges,queries)
    if kind==3:
        for n in (1,2,5,10,20):
            for attrs in ([1]*n,[n]*n):yield make(kind,attrs,[(u,u+1) for u in range(1,n)])
    if kind==5:
        for n in (5,10,20):
            for threshold in (2,n):yield make(kind,[threshold]*n,[(u,u+1,'j') for u in range(1,n)])


def audit_statement(p):
    text=(p/'task.md').read_text();assert text.splitlines()[0].startswith(f'# {p.name.upper()} — ')
    expected=['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc']
    for i in range(1,4):expected += [f'Sample Input {i}',f'Sample Output {i}']
    expected.append('Giải thích')
    assert re.findall(r'^### (.+)$',text,re.M)==expected
    assert len(re.findall(r'^#+ ',text,re.M))==len(expected)+1
    assert 'Subtask' not in text and not list(p.rglob('*.html'))
    for i in range(3):
        for label,folder,ext in [('Input','in','in'),('Output','out','out')]:
            match=re.search(rf'### Sample {label} {i+1}\n\n```text\n(.*?)```',text,re.S)
            assert match and match[1]==(p/folder/f'example_{i:02}.{ext}').read_text(),(p.name,label,i)
    assert not re.search(r'oracle|verifier|checker|benchmark|kiểm thử|kiểm chứng|bộ sinh|chạy test',(p/'solution.md').read_text(),re.I)


def invalid_checks(p,kind):
    sample=(p/'gen/example_00.in').read_text();maxn=100000 if kind==5 else 200000
    cases=['',sample+'0\n',sample.rsplit('\n',2)[0]+'\n','0\n',f'{maxn+1}\n']
    def attrs(n):return [(0,1)]*n if kind==4 else [1]*n if kind<=2 else [0]*n
    def edges(rows):return [(*e,'a') for e in rows] if kind==5 else rows
    cases += [make(kind,attrs(2),edges([(1,1)])),make(kind,attrs(2),edges([(1,3)])),
              make(kind,attrs(2),edges([(0,2)])),make(kind,attrs(3),edges([(1,2),(2,1)])),
              make(kind,attrs(4),edges([(1,2),(2,3),(3,1)]))]
    if kind<=2:
        cases += [make(kind,[0],[]),make(kind,[-1],[]),make(kind,[10**9+1],[])]
    if kind==2:
        cases += ['1 0\n1\n','1 200001\n1\n',make(kind,[1],[],[(0,0)]),make(kind,[1],[],[(2,0)]),
                  make(kind,[1],[],[(1,-1)]),make(kind,[1],[],[(1,2)])]
    if kind in (3,5):cases += [make(kind,[-1],[]),make(kind,[2],[])]
    if kind==4:
        cases += [make(kind,[(-1,1)],[]),make(kind,[(10**9+1,1)],[]),make(kind,[(0,0)],[]),make(kind,[(0,-1)],[]),make(kind,[(0,1001)],[])]
    if kind==5:
        cases += [make(kind,[0,0],[(1,2,'k')]),make(kind,[0,0],[(1,2,'A')]),make(kind,[0,0],[(1,2,'aa')]),'2\n0 0\n1 2\n']
    for data in cases:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(p.name,'Accepted invalid input',data)
    return len(cases)


def checker_checks(p):
    count=0
    with tempfile.TemporaryDirectory() as directory:
        actual,answer=Path(directory)/'actual',Path(directory)/'answer'
        for case in ('example_00','example_01','max_00'):
            inp=p/'in'/f'{case}.in';good=(p/'out'/f'{case}.out').read_text();words=good.split();answer.write_text(good)
            variants=[(good,True),(' \n\t'+good.strip()+' \n',True),('',False),(good+'0\n',False),
                      (good+'garbage\n',False),('x\n',False),('1.0\n',False),('9'*50+'\n',False)]
            for i in sorted({0,len(words)-1}):
                wrong=words.copy();wrong[i]=str(int(wrong[i])+1);variants.append(('\n'.join(wrong)+'\n',False))
            if len(words)>1:variants.append(('\n'.join(words[:-1])+'\n',False))
            for data,accepted in variants:
                actual.write_text(data);result=subprocess.run([str(p/'checker'),str(inp),str(actual),str(answer)],capture_output=True)
                assert (result.returncode==0)==accepted,(p.name,data[:80],result.stderr)
                count+=1
    return count


def official_checks(problem,kind):
    p=problem.basedir;files=sorted((p/'in').glob('*.in'));assert len(files)==sum(t['number'] for t in problem.config['tests'])==30
    for i,path in enumerate(files,1):
        try:expected=run(ORACLE,path.read_text(),kind).split()
        except subprocess.CalledProcessError as error:raise AssertionError((str(path),error.stderr)) from error
        actual=(p/'out'/path.with_suffix('.out').name).read_text().split()
        assert actual==expected,(str(path),actual[:10],expected[:10])
        if i%5==0:print(f'{p.name}: independently checked {i}/{len(files)} official tests',flush=True)
    for test in problem.config['tests']:
        if test['name'].endswith('.cpp'):
            stem=Path(test['name']).stem
            assert run(p/'gen'/stem,'',0)==(p/'in'/f'{stem}_00.in').read_text()
    nmax=100000 if kind==5 else 200000
    for i in range(8):
        header=list(map(int,(p/'in'/f'max_{i:02}.in').open().readline().split()))
        assert header==([nmax,200000] if kind==2 else [nmax])
    first=list(map(int,(p/'out/max_00.out').read_text().split()))
    if kind==1:
        assert first==[math.comb(length,3) for length in range(nmax,0,-1)]
        assert set((p/'out/max_01.out').read_text().split())=={'0'}
    elif kind==2:
        rows=(p/'in/max_00.in').read_text().splitlines()
        queries=[tuple(map(int,row.split())) for row in rows[nmax+1:]]
        assert first==[min(k,nmax-u+1) for u,k in queries]
    elif kind==3:
        assert first==[1]*(nmax-1)+[0]
        star=list(map(int,(p/'out/max_01.out').read_text().split()));assert star==[math.comb(nmax-1,2)]+[0]*(nmax-1)
    elif kind==4:
        assert first==[length*length//4 for length in range(nmax,0,-1)]
        assert set((p/'out/max_04.out').read_text().split())=={'0'}
    else:
        assert first==list(range(nmax-1,-1,-1))
        star=list(map(int,(p/'out/max_01.out').read_text().split()));assert star==[math.comb(nmax,2)]+[0]*(nmax-1)
    return len(files)


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format='%(message)s');problems=[Problem(ROOT,ROOT/'dtqg'/name) for name in args.problem]
    sources=[ORACLE.with_suffix('.cpp')]
    for problem in problems:
        problem.health_check();problem.generate_params_h();sources += [problem.get_correct_filename(),problem.verifier,problem.checker]
        sources += [problem.basedir/'gen'/t['name'] for t in problem.config['tests'] if t['name'].endswith('.cpp')]
    print(f'Compiling {len(sources)} programs...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(build,sources))
    for problem in problems:
        p=problem.basedir;started=time.monotonic();kind=NAMES.index(p.name)+1
        print(f'{p.name}: generating and validating official tests...',flush=True)
        problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
        problem.judge(problem.get_correct_filename(),{});assert problem.check_all_solutions_used();audit_statement(p)
        official=official_checks(problem,kind);print(f'{p.name}: checking small cases against enumeration...',flush=True);count=0
        for data in small_cases(kind):
            expected=brute(kind,data);run(p/'verifier',data)
            actual=run(p/'sol/correct',data).split();oracle=run(ORACLE,data,kind).split()
            assert actual==oracle==expected,(p.name,data,expected[:15],actual[:15],oracle[:15]);count+=1
        invalid=invalid_checks(p,kind);checker=checker_checks(p)
        if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
        problem.assert_hashes()
        print(f'{p.name}: PASS; {official} official; {count} small; {invalid} invalid-input; {checker} checker tests; hashes verified; {time.monotonic()-started:.1f}s',flush=True)


if __name__=='__main__':main()
