"""Generate, validate, score and independently check DTPALINCUT; no HTML export."""
import argparse
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from fractions import Fraction
import hashlib
import itertools
import logging
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
PACKAGE=HERE.parent
ROOT=PACKAGE.parents[1]
sys.path.insert(0,str(ROOT))
from problem import Problem
from problem_upload import ProblemUpload


def build(src):
    flags=shlex.split(os.getenv('CXXFLAGS','-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result'))
    subprocess.run([os.getenv('CXX','g++'),*flags,'-I',str(ROOT/'common'),'-o',str(src.with_suffix('')),str(src)],check=True)


def run(executable,data='',*args,cwd=None,timeout=30):
    return subprocess.run([str(executable),*map(str,args)],input=data,text=True,capture_output=True,check=True,cwd=cwd,timeout=timeout).stdout


def encode(s,queries):
    return s+'\n'+str(len(queries))+'\n'+''.join(str(len(q))+' '+' '.join(map(str,q))+'\n' for q in queries)


def decode(data):
    rows=data.splitlines();s=rows[0];t=int(rows[1]);queries=[]
    assert len(rows)==t+2
    for row in rows[2:]:
        words=row.split();k=int(words[0]);assert len(words)==k+1
        query=[]
        for word in words[1:]:
            v=0
            for c in word:v=min(len(s)+1,v*10+ord(c)-48)
            query.append(v)
        queries.append(query)
    return s,queries


def brute(s,lengths):
    n=len(s);k=len(lengths)
    if sum(lengths)>n:return False
    if all(x==1 for x in lengths):return True
    palindrome={(p,length):s[p:p+length]==s[p:p+length][::-1]
                for p in range(n) for length in set(lengths) if p+length<=n}
    reachable=[set() for _ in range(n+1)];reachable[0].add(0)
    for p in range(n):
        reachable[p+1].update(reachable[p])
        for mask in reachable[p]:
            for i,length in enumerate(lengths):
                if not(mask>>i&1) and p+length<=n and palindrome[p,length]:
                    reachable[p+length].add(mask|(1<<i))
    return (1<<k)-1 in reachable[n]


def small_cases():
    for n in range(1,8):
        queries=[]
        for k in range(1,5):
            queries += list(itertools.combinations_with_replacement(range(1,min(5,n+1)+1),k))
        assert len(queries)<=200
        for chars in itertools.product('ab',repeat=n):yield encode(''.join(chars),queries)
    rng=random.Random(2026110210)
    for case in range(180):
        n=rng.randint(1,35);s=''.join(rng.choice('ab' if case%3==0 else 'abc' if case%3==1 else 'abcdefghijklmnopqrstuvwxyz') for _ in range(n))
        queries=[]
        for _ in range(20):
            k=rng.randint(1,6)
            q=[rng.randint(1,max(1,n//max(1,k))) for _ in range(k)]
            if rng.randrange(5)==0:q[0]=n+1
            rng.shuffle(q);queries.append(q)
        yield encode(s,queries)
    yield encode('a'*26,[[2]*13,[2]*12+[3],[1]*13])
    yield encode('ababax',[[3,3],[3,1],[1,3],[1,1,1,1,1,1]])
    yield encode('abcda',[[3],[1],[1,1,1],[5]])
    yield encode('abba',[[2,2],[4],[2],[1,2,1],['0002'],['9'*100]])


def audit():
    text=(PACKAGE/'task.md').read_text()
    expected=['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc','Subtask']
    for i in range(1,3):expected += [f'Sample Input {i}',f'Sample Output {i}']
    expected.append('Giải thích')
    assert text.splitlines()[0]=='# DTPALINCUT — Cắt chuỗi đối xứng'
    assert re.findall(r'^### (.+)$',text,re.M)==expected
    assert len(re.findall(r'^#+ ',text,re.M))==len(expected)+1
    assert re.findall(r'^\| ([1-3]) \| (\d+)% \|',text,re.M)==[('1','25'),('2','25'),('3','50')]
    assert not list(PACKAGE.rglob('*.html'))
    for i in range(2):
        for label,folder,ext in [('Input','in','in'),('Output','out','out')]:
            match=re.search(rf'### Sample {label} {i+1}\n\n```text\n(.*?)```',text,re.S)
            assert match and match[1]==(PACKAGE/folder/f'example_{i:02}.{ext}').read_text()
    solution=(PACKAGE/'solution.md').read_text();assert not re.search(r'(?m)^ {0,3}#(?:[ \t]|$)', solution)
    assert all(f'## Subtask {i} —' in solution for i in range(1,4))
    assert not re.search(r'oracle|verifier|checker|benchmark|kiểm thử|kiểm chứng|bộ sinh|chạy test',solution,re.I)


def score_checks(problem):
    upload=ProblemUpload(problem);assert 'manifest' not in problem.config['upload']
    assert problem.config['upload']['points']==100
    cases=upload.manifest['cases'];assert len(cases)==42
    points={case['input_file'][:-3]:case['points'] for case in cases}
    assert set(points)=={path.stem for path in (PACKAGE/'in').glob('*.in')}
    assert points['example_00']==points['example_01']==0
    assert all('type' not in case for case in cases)
    assert sum(points.values())==40
    totals={}
    for group,number,total in ((1,10,10),(2,10,10),(3,20,20)):
        names=[name for name in points if name.startswith(f'sub{group}_')]
        assert len(names)==number and all(points[name]==1 for name in names)
        totals[group]=sum(points[name] for name in names);assert totals[group]==total
        assert Fraction(total,sum(points.values()))==Fraction(1,4) if group<3 else Fraction(total,sum(points.values()))==Fraction(1,2)
        for name in names:
            s,queries=decode((PACKAGE/'in'/f'{name}.in').read_text())
            actual=1 if all(len(q)==1 for q in queries) else 2 if len(s)<=200 and len(queries)<=3 else 3
            assert actual==group,(name,actual)
    return totals


def greedy(s,lengths):
    p=0
    for length in lengths:
        for start in range(p,len(s)-length+1):
            part=s[start:start+length]
            if part==part[::-1]:p=start+length;break
        else:return False
    return True


def heuristic_checks():
    failures={name:False for name in ('given_order','ascending','descending','overlap','deduplicate','cover_all')}
    for i in range(2):
        s,queries=decode((PACKAGE/'in'/f'example_{i:02}.in').read_text())
        expected=(PACKAGE/'out'/f'example_{i:02}.out').read_text().split()
        for q,answer in zip(queries,expected):
            good=answer=='YES'
            failures['given_order'] |= greedy(s,q)!=good
            failures['ascending'] |= greedy(s,sorted(q))!=good
            failures['descending'] |= greedy(s,sorted(q,reverse=True))!=good
            independent=all(any(s[p:p+length]==s[p:p+length][::-1] for p in range(len(s)-length+1)) for length in q)
            failures['overlap'] |= independent!=good
            failures['deduplicate'] |= greedy(s,sorted(set(q)))!=good
            failures['cover_all'] |= good and sum(q)!=len(s)
    assert all(failures.values()),failures
    return len(failures)


def invalid_checks():
    sample=(PACKAGE/'gen/example_00.in').read_text()
    cases=['',sample+'0\n',sample.rsplit('\n',2)[0]+'\n','\n1\n1 1\n',
           encode('A',[[1]]),encode('a1',[[1]]),encode('a'*10001,[[1]]),
           'a\n0\n','a\n201\n','a\n-1\n','a\n1\n0\n','a\n1\n14 '+'1 '*13+'1\n',
           'a\n1\n1 0\n','a\n1\n1 000\n','a\n1\n1 -1\n','a\n1\n1 1.0\n','a\n1\n1 x\n',
           'a\n1\n2 1\n','a\n1\n1 1 1\n']
    for data in cases:
        result=subprocess.run([str(PACKAGE/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,('Accepted invalid input',data[:100])
    run(PACKAGE/'verifier',sample.replace(' ','   '))
    run(PACKAGE/'verifier',encode('abba',[['0002'],['9'*100]]))
    return len(cases)


def checker_checks():
    count=0
    with tempfile.TemporaryDirectory() as directory:
        actual=Path(directory)/'actual';answer=Path(directory)/'answer'
        for case in ('example_00','example_01','sub3_17'):
            inp=PACKAGE/'in'/f'{case}.in';good=(PACKAGE/'out'/f'{case}.out').read_text();words=good.split();answer.write_text(good)
            variants=[(good,True),(' \n\t'+'   '.join(words)+' \n',True),('',False),(good+'YES\n',False),
                      (good+'garbage\n',False),('1\n',False),('yes\n',False),('MAYBE\n',False)]
            for i in sorted({0,len(words)-1}):
                wrong=words.copy();wrong[i]='NO' if wrong[i]=='YES' else 'YES';variants.append(('\n'.join(wrong)+'\n',False))
            variants.append(('\n'.join(words[:-1])+'\n',False))
            for data,accepted in variants:
                actual.write_text(data);result=subprocess.run([str(PACKAGE/'checker'),str(inp),str(actual),str(answer)],capture_output=True)
                assert (result.returncode==0)==accepted,(case,data[:80],result.stderr);count+=1
    return count


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format='%(message)s');problem=Problem(ROOT,PACKAGE)
    problem.health_check();problem.generate_params_h()
    sources=[PACKAGE/'sol/correct.cpp',PACKAGE/'verifier.cpp',PACKAGE/'checker.cpp',HERE/'oracle.cpp']
    sources += [PACKAGE/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp')]
    print(f'Compiling {len(sources)} programs...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(build,sources))
    problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
    problem.judge(problem.get_correct_filename(),{});assert problem.check_all_solutions_used();audit()
    started=time.monotonic();maximum=0;totals=score_checks(problem)
    print(f'DTPALINCUT: score weights {totals}, ratios 25/25/50%, problem points 100',flush=True)
    with tempfile.TemporaryDirectory() as directory:
        files=sorted((PACKAGE/'in').glob('*.in'));assert len(files)==42
        for i,path in enumerate(files,1):
            data=path.read_text();s,queries=decode(data)
            expected=(PACKAGE/'out'/path.with_suffix('.out').name).read_text().split()
            assert run(HERE/'oracle',data,cwd=directory).split()==expected,path.name
            if len(s)<=30:
                assert [('YES' if brute(s,q) else 'NO') for q in queries]==expected,path.name
            if len(set(s))==1:
                assert [('YES' if sum(q)<=len(s) else 'NO') for q in queries]==expected,path.name
            if len(s)>=2 and s[0]!=s[1] and all(s[j]==s[j%2] for j in range(len(s))):
                assert [('YES' if sum(q)<=len(s) and all(length%2 for length in q) else 'NO') for q in queries]==expected,path.name
            before=time.monotonic();assert run(PACKAGE/'sol/correct',data,cwd=directory,timeout=1).split()==expected
            maximum=max(maximum,time.monotonic()-before)
            if i%10==0:print(f'DTPALINCUT: independently checked {i}/{len(files)} official tests',flush=True)
        for test in problem.config['tests']:
            if test['name'].endswith('.cpp'):
                stem=Path(test['name']).stem
                for seed in range(test['number']):
                    assert run(PACKAGE/'gen'/stem,'',seed)==(PACKAGE/'in'/f'{stem}_{seed:02}.in').read_text()
        s,queries=decode((PACKAGE/'in/sub3_17.in').read_text())
        needed=set(length for q in queries if len(q)>1 and sum(q)<=len(s) for length in q)
        assert len(s)==10000 and len(queries)==200 and len(needed)==1990
        planted=(PACKAGE/'out/sub3_19.out').read_text().split();assert all(planted[q]=='YES' for q in range(0,200,5))
        print('DTPALINCUT: checking small cases against prefix/position DP...',flush=True)
        small=0
        for data in small_cases():
            run(PACKAGE/'verifier',data);s,queries=decode(data)
            expected=['YES' if brute(s,q) else 'NO' for q in queries]
            assert run(PACKAGE/'sol/correct',data,cwd=directory).split()==expected,(s,queries,expected)
            assert run(HERE/'oracle',data,cwd=directory).split()==expected
            small+=1
        rng=random.Random(2026110211);metamorphic=0
        for _ in range(30):
            n=rng.randint(1,50);s=''.join(rng.choice('abc') for _ in range(n))
            queries=[[rng.randint(1,10) for _ in range(rng.randint(1,6))] for _ in range(12)]
            expected=['YES' if brute(s,q) else 'NO' for q in queries]
            shuffled=[q.copy() for q in queries]
            for q in shuffled:rng.shuffle(q)
            for transformed in (encode(s,shuffled),encode(s[::-1],queries)):
                assert run(PACKAGE/'sol/correct',transformed,cwd=directory).split()==expected;metamorphic+=1
        for name in ('example_00','example_01','sub3_17'):
            (Path(directory)/'PALINCUT.INP').write_text((PACKAGE/'in'/f'{name}.in').read_text())
            assert run(PACKAGE/'sol/correct','',cwd=directory)==''
            assert (Path(directory)/'PALINCUT.OUT').read_text()==(PACKAGE/'out'/f'{name}.out').read_text()
        (Path(directory)/'PALINCUT.INP').unlink()
    rejected=heuristic_checks();invalid=invalid_checks();checker=checker_checks()
    if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
    problem.assert_hashes()
    print(f'DTPALINCUT: PASS; 42 official; {small} small; {metamorphic} symmetry checks; {rejected} wrong heuristics; '
          f'3 file-I/O; {invalid} invalid-input; {checker} checker checks; hashes verified; '
          f'max reference runtime {maximum:.4f}s; {time.monotonic()-started:.1f}s',flush=True)


if __name__=='__main__':main()
