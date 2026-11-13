"""Generate and verify BANK3/WGAMEPN ladders without exporting HTML."""
import argparse
from collections import Counter
from concurrent.futures import ThreadPoolExecutor
from functools import lru_cache
import itertools
import json
import logging
from math import comb, factorial
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
ROOT=HERE.parents[1]
sys.path.insert(0,str(ROOT))
from problem import Problem
from problem_upload import ProblemUpload
CODES=['dtbankone','dtbanktwo','dtbanksmall','dtbank3','dtwgamepath','dtwgamepal','dtwgamechar','dtwgamepn']
MOD=10**9+7

def run(path,data='',*args,timeout=30):
    return subprocess.run([str(path),*map(str,args)],input=data,text=True,capture_output=True,check=True,timeout=timeout).stdout

def build(path):
    flags=shlex.split(os.getenv('CXXFLAGS','-O2 -std=c++17 -Wall -Wextra -Wno-sign-compare -Wno-unused-result'))
    subprocess.run([os.getenv('CXX','g++'),*flags,'-I',str(ROOT/'common'),'-I',str(HERE/'compat'),str(path),'-o',str(path.with_suffix(''))],check=True)

def parse_bank(data):
    values=iter(map(int,data.split()));t=next(values);result=[]
    for _ in range(t):
        n,m=next(values),next(values)
        result.append(([next(values) for _ in range(n)],[next(values) for _ in range(m)]))
    return result

def bank_brute(a,b):
    # Process each package once, assigning it to a labelled project or discarding it.
    suffix=[0]*(len(b)+1)
    for j in range(len(b)-1,-1,-1):suffix[j]=suffix[j+1]+b[j]
    @lru_cache(None)
    def solve(j,remaining):
        if sum(remaining)>suffix[j]:return 0
        if j==len(b):return int(not any(remaining))
        ways=solve(j+1,remaining)
        for i,value in enumerate(remaining):
            if value>=b[j]:
                r=list(remaining);r[i]-=b[j]
                ways+=solve(j+1,tuple(r))
        return ways%MOD
    return solve(0,tuple(a))

def bank_mitm(a,b):
    # Independent ternary choices for two projects; binary for a single project.
    A=a[0];B=a[1] if len(a)>1 else 0
    def halves(part):
        states=Counter({(0,0):1})
        for value in part:
            new=states.copy()
            for (x,y),count in states.items():
                if x+value<=A:new[x+value,y]+=count
                if len(a)>1 and y+value<=B:new[x,y+value]+=count
            states=new
        return states
    first=halves(b[:len(b)//2]);second=halves(b[len(b)//2:])
    return sum(count*second[A-x,B-y] for (x,y),count in first.items())%MOD

def parse_game(data):
    lines=data.splitlines();m,n,D=map(int,lines[0].split());return m,n,D,lines[1],lines[2:]

def game_brute(data):
    m,n,D,s,g=parse_game(data);answer=0;winning=[]
    def visit(i,j,word):
        nonlocal answer
        if i>=m or j>=n or g[i][j]=='#':return
        word+=g[i][j]
        if (i,j)==(m-1,n-1):
            if word==word[::-1] and s in word:answer+=1;winning.append(word)
            return
        visit(i+1,j,word);visit(i,j+1,word)
    visit(0,0,'')
    return answer%D,winning

def game_layers(data):
    # If every anti-diagonal has a single letter, every path reads the same word.
    m,n,D,s,g=parse_game(data);layers=[set() for _ in range(m+n-1)]
    for i in range(m):
        for j in range(n):
            if g[i][j]!='#':layers[i+j].add(g[i][j])
    if any(len(layer)>1 for layer in layers):return None
    if any(not layer for layer in layers):return 0
    word=''.join(next(iter(layer)) for layer in layers)
    if word!=word[::-1] or s not in word:return 0
    dp=[0]*n;dp[0]=1
    for i in range(m):
        for j in range(n):
            if g[i][j]=='#':dp[j]=0
            elif j:dp[j]=(dp[j]+dp[j-1])%D
    return dp[-1]%D

def audit(p):
    code=p.basedir.name;text=(p.basedir/'task.md').read_text();solution=(p.basedir/'solution.md').read_text()
    samples=p.config['tests'][0]['number']
    headings=['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc']
    for i in range(1,samples+1):headings += [f'Sample Input {i}',f'Sample Output {i}']
    headings += ['Giải thích','Nguồn']
    assert text.startswith(f'# {code.upper()} — ')
    assert re.findall(r'^### (.*)$',text,re.M)==headings
    assert len(re.findall(r'^#+ ',text,re.M))==len(headings)+1
    assert not re.search(r'^# ',solution,re.M)
    assert not re.search(r'oracle|verifier|checker|benchmark|kiểm thử|kiểm chứng|bộ sinh|chạy test',solution,re.I)
    assert p.config['title']==text.splitlines()[0][2:]
    assert p.check_all_solutions_used() and not list(p.basedir.glob('*.html'))
    upload=ProblemUpload(p)
    assert len(upload.manifest['cases'])==28+samples
    assert sum(x['points'] for x in upload.manifest['cases'])==28
    assert p.config['upload']['points']==100
    assert p.config['timelimit']==p.config['upload']['time_limit']==1.0
    for j in range(1,samples+1):
        sample=re.search(rf'### Sample Input {j}\n\n```text\n(.*?)```',text,re.S)[1]
        assert sample==(p.basedir/'gen'/f'example_{j-1:02}.in').read_text()

def small_inputs(code):
    rng=random.Random(2026110600+CODES.index(code))
    for z in range(120):
        if CODES.index(code)<4:
            m=rng.randint(1,8);n=1 if code=='dtbankone' else rng.randint(1,min(m,2 if code=='dtbanktwo' else 4))
            b=[rng.randint(1,7) for _ in range(m)];a=[rng.randint(1,12) for _ in range(n)]
            yield '1\n'+f'{n} {m}\n'+' '.join(map(str,a))+'\n'+' '.join(map(str,b))+'\n'
        else:
            m=rng.randint(1,6);n=rng.randint(1,6);D=rng.choice([1,2,3,100,10**9])
            g=[''.join(rng.choices('abc#',weights=[5,3,2,1],k=n)) for _ in range(m)]
            if code=='dtwgamepath':
                s='a';g=[''.join('#' if c=='#' else 'a' for c in row) for row in g];g[0]='a'+g[0][1:]
            elif code=='dtwgamepal':s='a';g[0]='a'+g[0][1:]
            else:s=''.join(rng.choice('abc') for _ in range(rng.randint(1,8) if code=='dtwgamepn' else 1))
            yield f'{m} {n} {D}\n{s}\n'+'\n'.join(g)+'\n'

def invalid_inputs(p):
    code=p.basedir.name;sample=(p.basedir/'gen/example_00.in').read_text()
    bad=['',sample+'0\n','\n'.join(sample.splitlines()[:-1])+'\n']
    if CODES.index(code)<4:
        limits=p.config['params'];bad += ['0\n','4\n','1\n0 1\n1\n1\n','1\n2 1\n1 1\n1\n','1\n1 1\n0\n1\n','1\n1 1\n1\n0\n',f'1\n1 1\n{limits["VALUE_MAX"]+1}\n1\n',f'1\n1 {limits["M_MAX"]+1}\n1\n'+' '.join(['1']*(limits['M_MAX']+1))+'\n']
        if limits['N_MAX']<20:
            n=limits['N_MAX']+1;bad += [f'1\n{n} {n}\n'+' '.join(['1']*n)+'\n'+' '.join(['1']*n)+'\n']
    else:
        bad += ['0 1 100\na\n','1 0 100\na\n','151 1 100\na\n'+'a\n'*151,'1 1 0\na\na\n','1 1 1000000001\na\na\n','1 1 100\nA\na\n','1 1 100\na\nA\n','1 1 100\na\naa\n',f'1 1 100\n'+('a'*(p.config['params']['S_MAX']+1))+'\na\n']
        if code=='dtwgamepath':bad += ['1 2 100\na\nab\n','1 1 100\na\n#\n']
        if code=='dtwgamepal':bad += ['1 1 100\na\nb\n']
    for data in bad:
        result=subprocess.run([str(p.basedir/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(code,'invalid input accepted',data[:100])
    return len(bad)

def checker_tests(p,directory):
    count=0
    for path in sorted((p.basedir/'in').glob('example*.in')):
        expected=p.basedir/'out'/path.with_suffix('.out').name;good=expected.read_text();values=good.split()
        wrong=values.copy();wrong[-1]=str(int(wrong[-1])+1)
        bad=['','garbage\n',good+'0\n',good+'trailing\n',' '.join(wrong)+'\n','1.0\n','9'*100+'\n',' '.join(values[:-1])+'\n']
        for data,accepted in [(good,True),(' \n'+good+' \t\n',True),*((x,False) for x in bad)]:
            actual=directory/'actual';actual.write_text(data)
            r=subprocess.run([str(p.basedir/'checker'),str(path),str(actual),str(expected)],capture_output=True)
            assert (r.returncode==0)==accepted,(p.basedir.name,data,r.stderr)
            count+=1
    return count

def targeted_game(p):
    if p.basedir.name != 'dtwgamepn':return 0
    count=0
    rng=random.Random(2026110620)
    halves=['a'*25,'ab'*13,'abcde'*6,'abacaba'*4,
            ''.join(rng.choice('abc') for _ in range(30))]
    for half in halves:
        for odd in (False,True):
            word=half+(half[:-1] if odd else half)[::-1]
            center=len(half)
            patterns=[word[center-10:center+10],word[:20][::-1],'z']
            for pattern in patterns:
                for transpose in (False,True):
                    data=(f'{len(word)} 1 1000000000\n{pattern}\n'+'\n'.join(word)+'\n') if transpose else f'1 {len(word)} 1000000000\n{pattern}\n{word}\n'
                    run(p.basedir/'verifier',data)
                    assert int(run(p.basedir/'sol/correct',data,timeout=p.config['upload']['time_limit']))==int(pattern in word),(pattern,word)
                    count+=1
    cases=[('1 1 1\na\na\n',0),('1 1 100\na\n#\n',0),
           ('2 2 100\na\n#a\na#\n',0),('1 3 100\nac\naca\n',1),
           ('1 5 100\naaa\naaaaa\n',1),('1 5 100\naba\nabcba\n',0),
           ('1 1 100\naa\na\n',0)]
    for data,expected in cases:
        run(p.basedir/'verifier',data)
        assert int(run(p.basedir/'sol/correct',data,timeout=p.config['upload']['time_limit']))==expected
        count+=1
    return count


def check_problem(p,args):
    code=p.basedir.name;bank=CODES.index(code)<4
    p.make_inputs();p.verify_inputs();p.make_outputs(True);audit(p)
    largest=0;independent=0;source_count=0;source_raw_discrepancies=0;small_official=0
    with tempfile.TemporaryDirectory() as directory:
        directory=Path(directory)
        for path in sorted((p.basedir/'in').glob('*.in')):
            data=path.read_text();before=time.monotonic()
            actual=run(p.basedir/'sol/correct',data,timeout=p.config['upload']['time_limit'])
            largest=max(largest,time.monotonic()-before)
            values=list(map(int,actual.split()))
            expected=p.basedir/'out'/path.with_suffix('.out').name
            tmp=directory/'actual';tmp.write_text(actual);run(p.basedir/'checker','',path,tmp,expected)
            if bank:
                source=list(map(int,run(HERE/'sources/bank3',data,timeout=30).split()));assert source==values,(code,path,values,source);source_count+=1
                for (a,b),v in zip(parse_bank(data),values):
                    if len(a)<=2:assert bank_mitm(a,b)==v;independent+=1
                    elif len(b)<=10:assert bank_brute(a,b)==v;independent+=1
                    elif len(set(b))==1:
                        unit=b[0];r=[x//unit for x in a]
                        expected=0
                        if all(x%unit==0 for x in a) and sum(r)<=len(b):
                            expected=factorial(len(b))//factorial(len(b)-sum(r))
                            for k in r:expected//=factorial(k)
                        assert expected%MOD==v;independent+=1
            else:
                m,n,D,s,g=parse_game(data)
                if m+n<=13:
                    answer,winning=game_brute(data);assert values==[answer],(code,path,actual,answer);small_official+=1;independent+=1
                    if code=='dtwgamepn' and path.name=='example_01.in':assert set(winning)=={'aabcbaa'}
                else:
                    answer=game_layers(data)
                    if answer is not None:assert values==[answer],(code,path,actual,answer);independent+=1
                # Source code uses a large fixed table; run serially and only
                # when both endpoints are letters (it does not guard '#').
                if g[0][0]!='#' and g[-1][-1]!='#' and D>1:
                    raw=int(run(HERE/'sources/wgamepn',data,timeout=45))
                    assert raw%D==values[0],(code,path,raw,values);source_count+=1
                    source_raw_discrepancies+=int(raw!=values[0])
            if path.stem.startswith('cases_'):
                seed=int(path.stem.rsplit('_',1)[1]);assert run(p.basedir/'gen/cases','',seed)==data
            else:
                j=int(path.stem.rsplit('_',1)[1])+1
                sample=re.search(rf'### Sample Output {j}\n\n```text\n(.*?)```',(p.basedir/'task.md').read_text(),re.S)[1]
                tmp.write_text(sample);run(p.basedir/'checker','',path,tmp,p.basedir/'out'/path.with_suffix('.out').name)
        for data in small_inputs(code):
            run(p.basedir/'verifier',data);actual=list(map(int,run(p.basedir/'sol/correct',data,timeout=p.config['upload']['time_limit']).split()))
            wanted=[bank_brute(a,b) for a,b in parse_bank(data)] if bank else [game_brute(data)[0]]
            assert actual==wanted,(code,data,actual,wanted)
        invalid=invalid_inputs(p);checkers=checker_tests(p,directory);targeted=targeted_game(p)
    if args.update_hashes:p.ignore_warning=True;p.write_hashes()
    p.assert_hashes()
    result=dict(targeted=targeted,official=sum(x['number'] for x in p.config['tests']),small=120,independent_official=independent,source_comparisons=source_count,source_raw_discrepancies=source_raw_discrepancies,small_official=small_official,invalid=invalid,checker=checkers,max_runtime_seconds=round(largest,4),hashes=2*sum(x['number'] for x in p.config['tests']))
    print(f'{code}: PASS; {result}',flush=True)
    return result

def main():
    parser=argparse.ArgumentParser();parser.add_argument('--problem',choices=CODES,action='append');parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'dtqg'/code) for code in (args.problem or CODES)]
    sources=[HERE/'sources/bank3.cpp',HERE/'sources/wgamepn.cpp']
    for p in problems:
        p.health_check();p.generate_params_h()
        sources += [p.basedir/'sol/correct.cpp',p.basedir/'verifier.cpp',p.basedir/'checker.cpp',p.basedir/'gen/cases.cpp']
    print(f'Compiling {len(sources)} programs...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(build,sources))
    # The supplied WGAMEPN source returns an unreduced base-case value here.
    assert int(run(HERE/'sources/wgamepn','1 1 1\na\na\n'))==1
    results={}
    for p in problems:results[p.basedir.name]=check_problem(p,args)
    target=HERE/'results.json'
    if target.exists():results={**json.loads(target.read_text()),**results}
    target.write_text(json.dumps(results,indent=2,ensure_ascii=False)+'\n')
    print('All selected problems passed; hashes verified; no HTML generated.',flush=True)

if __name__=='__main__':main()
