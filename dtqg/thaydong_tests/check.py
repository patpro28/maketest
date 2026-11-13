"""Generate, validate and independently check seven source problems; no HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from functools import lru_cache
import io
import itertools
import json
import logging
from pathlib import Path
import random
import re
import shlex
import os
import subprocess
import sys
import tempfile
import time

HERE=Path(__file__).resolve().parent
ROOT=HERE.parents[1]
sys.path.insert(0,str(ROOT))
from problem import Problem
from problem_upload import ProblemUpload
CODES=['dtrobot','dtrebuss','dtsp','dtfactor','dtbtnk','dtdna','dtnumset']
IO_NAMES=['ROBOT','REBUSS','SP','factor','BTNK','DNA','NUMSET']
INPUT_MAX=1000000
MOD=111539786


def build(src):
    flags=shlex.split(os.getenv('CXXFLAGS','-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result'))
    subprocess.run([os.getenv('CXX','g++'),*flags,'-I',str(ROOT/'common'),str(src),'-o',str(src.with_suffix(''))],check=True)


def run(exe,data='',*args,timeout=30,cwd=None):
    return subprocess.run([str(exe),*map(str,args)],input=data,text=True,capture_output=True,check=True,timeout=timeout,cwd=cwd).stdout


def turns(data):
    rows=io.StringIO(data);n=int(next(rows));x,y=map(int,next(rows).split());old=None;right=left=0
    directions={(1,0):0,(0,1):1,(-1,0):2,(0,-1):3}
    for line in rows:
        nx,ny=map(int,line.split());direction=directions[nx-x,ny-y]
        if old is not None:
            difference=(direction-old)%4;left+=difference==1;right+=difference==3
        old=direction;x=nx;y=ny
    return f'{right} {left}'


def digit_mask(pattern,column):
    if column>=len(pattern):return 1
    index=len(pattern)-1-column;c=pattern[index]
    mask=1023 if c=='*' else 1<<int(c)
    return mask&~1 if index==0 else mask


@lru_cache(None)
def carry_transitions(a,b,c,carry):
    # Choose a result digit and the first summand; derive the other summand.
    result=0
    for z in range(10):
        if not(c>>z&1):continue
        for x in range(10):
            if not(a>>x&1):continue
            for new_carry in (0,1):
                y=z+10*new_carry-x-carry
                if 0<=y<=9 and b>>y&1:result |= 1<<new_carry
    return result


def rebuss_exists(data):
    patterns=data.split();reachable=1
    for column in range(max(map(len,patterns))):
        a,b,c=[digit_mask(s,column) for s in patterns];following=0
        for carry in (0,1):
            if reachable>>carry&1:following |= carry_transitions(a,b,c,carry)
        reachable=following
        if not reachable:return False
    return bool(reachable&1)


def bracket_brute(s,k):
    words=set()
    for mask in range(1,1<<len(s)):
        word=''.join(c for i,c in enumerate(s) if mask>>i&1);balance=0;maximum=0
        for c in word:
            balance+=1 if c=='(' else -1;maximum=max(maximum,balance)
            if balance<0:break
        else:
            if balance==0 and maximum==k:words.add(word)
    return len(words)%MOD


def bracket_reference(s,k):
    n=len(s);next_open=[n]*(n+1);next_close=[n]*(n+1)
    for i in range(n-1,-1,-1):
        next_open[i]=i if s[i]=='(' else next_open[i+1]
        next_close[i]=i if s[i]==')' else next_close[i+1]
    # Greedy first occurrence gives one canonical embedding per distinct word.
    dp=[[0]*(k+1) for _ in range(n+1)];hit=[[0]*(k+1) for _ in range(n+1)];dp[0][0]=1
    answer=0
    for p in range(n+1):
        answer=(answer+hit[p][0])%MOD
        for b in range(k+1):
            for reached,table in ((False,dp),(True,hit)):
                value=table[p][b]
                if not value:continue
                if b<k and next_open[p]<n:
                    following=hit if reached or b+1==k else dp
                    q=next_open[p]+1;following[q][b+1]=(following[q][b+1]+value)%MOD
                if b and next_close[p]<n:
                    q=next_close[p]+1;table[q][b-1]=(table[q][b-1]+value)%MOD
    return answer


def dna_reference(a,b):
    if sorted(a)!=sorted(b):return False
    if a==b:return True
    ranges=[(l,r) for l in range(len(a)) for r in range(l+2,len(a)+1)]
    def reverse(s,l,r):return s[:l]+s[l:r][::-1]+s[r:]
    first={a};first.update(reverse(a,l,r) for l,r in ranges)
    if b in first:return True
    seen=set(first)
    for s in first:seen.update(reverse(s,l,r) for l,r in ranges)
    if b in seen:return True
    first={b};first.update(reverse(b,l,r) for l,r in ranges)
    for s in first:
        if s in seen:return True
        if any(reverse(s,l,r) in seen for l,r in ranges):return True
    return False


def dna_brute(a,b):
    if sorted(a)!=sorted(b):return False
    frontier={a};seen={a}
    for _ in range(5):
        if b in frontier:return True
        following=set()
        for s in frontier:
            for l in range(len(s)):
                for r in range(l+2,len(s)+1):
                    t=s[:l]+s[l:r][::-1]+s[r:]
                    if t not in seen:seen.add(t);following.add(t)
        frontier=following
    return False


def subsequence(s,t):
    p=0
    for c in t:
        p=s.find(c,p)
        if p<0:return False
        p+=1
    return True


def number_brute(data):
    s,A,B=data.split();A=int(A);B=int(B);values=set()
    for mask in range(1,1<<len(s)):
        t=''.join(c for i,c in enumerate(s) if mask>>i&1);value=int(t)
        if A<=value<=B:values.add(value)
    return len(values)


def all_numbers(s):
    # Distinct canonical positive subsequences, without fixing their lengths.
    total=0;last=[0]*10
    for c in s:
        d=int(c);new=total+(d!=0);total+=new-last[d];last[d]=new
    return total+('0' in s)


def narrow_number_reference(s,A,B):
    if len(A)!=len(B):
        # The generated case crosses a power of ten by exactly one.
        assert A=='9'*len(A) and B=='1'+'0'*len(A)
        return int(subsequence(s,A))+int(subsequence(s,B))
    common=0
    while common<len(A) and A[common]==B[common]:common+=1
    p=0
    for c in A[:common]:
        p=s.find(c,p)
        if p<0:return 0
        p+=1
    if common==len(A):return 1
    lo=A[common:];hi=B[common:]
    @lru_cache(None)
    def solve(i,p,tight_lo,tight_hi):
        if i==len(lo):return 1
        answer=0
        for d in range(int(lo[i]) if tight_lo else 0,(int(hi[i]) if tight_hi else 9)+1):
            j=s.find(str(d),p)
            if j>=0:answer+=solve(i+1,j+1,tight_lo and d==int(lo[i]),tight_hi and d==int(hi[i]))
        return answer
    return solve(0,p,True,True)


def number_reference(data):
    s,A,B=data.split()
    if len(s)<=18:return number_brute(data)
    if max(map(len,(s,A,B)))>1000:return narrow_number_reference(s,A,B)
    if A=='0' and set(B)=={'9'} and len(B)>=len(s):return all_numbers(s)
    if len(A)==len(B)==len(s):return int(A<=s<=B)
    # Independent automaton DP for small bounds, with fixed output length.
    @lru_cache(None)
    def fixed(bound,length):
        @lru_cache(None)
        def solve(i,p,tight):
            if i==length:return 1
            answer=0;high=int(bound[i]) if tight else 9
            for d in range(1 if i==0 else 0,high+1):
                j=s.find(str(d),p)
                if j>=0:answer+=solve(i+1,j+1,tight and d==high)
            return answer
        return solve(0,0,True)
    def count(bound):
        if bound<0:return 0
        text=str(bound);answer=int('0' in s)
        for length in range(1,len(text)):answer+=fixed('9'*length,length)
        if bound:answer+=fixed(text,len(text))
        return answer
    return count(int(B))-count(int(A)-1)


def check_answer(code,data,actual,expected):
    if code=='dtrebuss':assert (not actual.startswith('No'))==expected,(code,data[:100],actual[:100],expected)
    elif code=='dtrobot':assert actual.split()==expected.split()
    elif code=='dtdna':assert actual.strip()==('Similar' if expected else 'Different'),(data,actual,expected)
    elif code=='dtfactor':assert list(map(int,actual.split()))==expected
    else:assert int(actual)==expected,(code,data[:100],actual[:100],expected)


def reference(code,data):
    if code=='dtrobot':return turns(data)
    if code=='dtrebuss':return rebuss_exists(data)
    if code=='dtsp':return int(run(HERE/'oracle_sp',data,timeout=120))
    if code=='dtfactor':return list(map(int,run(HERE/'oracle_factor',data,timeout=120).split()))
    if code=='dtbtnk':
        s,k=data.split();return bracket_brute(s,int(k)) if len(s)<=16 else bracket_reference(s,int(k))
    if code=='dtdna':return dna_reference(*data.split())
    return number_reference(data)


def audit(problem):
    p=problem.basedir;code=p.name;text=(p/'task.md').read_text();solution=(p/'solution.md').read_text()
    examples=next(t['number'] for t in problem.config['tests'] if t['name']=='example.in')
    headings=['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc']
    for i in range(1,examples+1):headings.extend([f'Sample Input {i}',f'Sample Output {i}'])
    headings.extend(['Giải thích','Nguồn'])
    assert re.findall(r'^### (.+)$',text,re.M)==headings
    assert len(re.findall(r'^#+ ',text,re.M))==len(headings)+1
    assert text.startswith(f'# {code.upper()} — ') and problem.config['title']==text.splitlines()[0][2:]
    assert not re.search(r'^# ',solution,re.M)
    assert not re.search(r'oracle|verifier|checker|benchmark|kiểm thử|kiểm chứng|bộ sinh|chạy test',solution,re.I)
    assert not list(p.rglob('*.html')) and problem.check_all_solutions_used()
    count=sum(test['number'] for test in problem.config['tests'])
    upload=ProblemUpload(problem);cases=upload.manifest['cases'];assert len(cases)==count
    assert all(c['points']==(0 if c['input_file'].startswith('example_') else 1) for c in cases)
    assert problem.config['upload']['points']==100 and 'manifest' not in problem.config['upload']
    assert (problem.config['upload'].get('checker')=='custom')==(code=='dtrebuss')
    for i in range(1,examples+1):
        for label,folder,extension in [('Input','in','in'),('Output','out','out')]:
            value=re.search(rf'### Sample {label} {i}\n\n```text\n(.*?)```',text,re.S)[1]
            if label=='Input':assert value==(p/folder/f'example_{i-1:02}.{extension}').read_text()
            else:
                with tempfile.TemporaryDirectory() as directory:
                    actual=Path(directory)/'actual';actual.write_text(value)
                    run(p/'checker','',p/'in'/f'example_{i-1:02}.in',actual,p/'out'/f'example_{i-1:02}.out')


def invalid_checks(problem):
    p=problem.basedir;code=p.name;sample=(p/'gen/example_00.in').read_text()
    bad=['',sample+'0\n','\n'.join(sample.splitlines()[:-1])+'\n']
    extra={
      'dtrobot':['1\n0 0\n','70001\n','2\n1 0\n2 0\n','2\n0 0\n1 1\n','2\n0 0\n0 0\n'],
      'dtrebuss':['a\n1\n2\n','*'*100001+'\n1\n2\n','1\n\n2\n','1\n1\n+2\n'],
      'dtsp':['-1 0 0 1\n','271 0 0 1\n','0 0 0 0\n','0 0 0 1000001\n'],
      'dtfactor':['0\n','151\n','1\n1\n','1\n1000000000001\n','1\n12\n'],
      'dtbtnk':['()\n0\n','()\n2\n','(x)\n1\n','(\n1\n','('*4001+'\n1\n'],
      'dtdna':['A\nAA\n','AC\nAC\n','A'*46+'\n'+'A'*46+'\n','a\na\n'],
      'dtnumset':['01\n0\n1\n','1\n2\n1\n','1'*200001+'\n0\n0\n','1'*1001+'\n0\n1000001\n','1\n00\n1\n'],
    }
    bad+=extra[code]
    for data in bad:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(code,'accepted invalid',data[:100])
    return len(bad)


def checker_checks(problem):
    p=problem.basedir;code=p.name;count=0
    with tempfile.TemporaryDirectory() as directory:
        actual=Path(directory)/'actual'
        for path in sorted((p/'in').glob('example*.in')):
            answer=p/'out'/path.with_suffix('.out').name;good=answer.read_text()
            bad=['',good+'extra\n','garbage\n',good+'0\n']
            if code=='dtrebuss':bad+=['No Solution\n','0\n1\n1\n','1\n1\n2\n']
            elif code=='dtdna':bad+=['Similar\n' if good.strip()=='Different' else 'Different\n','similar\n']
            else:bad+=['-1\n','9'*500+'\n']
            for value,accepted in [(good,True),(' \n'+good+' \t\n',True),*((value,False) for value in bad)]:
                actual.write_text(value);result=subprocess.run([str(p/'checker'),str(path),str(actual),str(answer)],capture_output=True)
                assert (result.returncode==0)==accepted,(code,path.name,value[:100],result.stderr);count+=1
        if code=='dtrebuss':
            inp=Path(directory)/'in';ans=Path(directory)/'ans';inp.write_text('*\n*\n*\n');ans.write_text('1\n1\n2\n')
            for value,accepted in [('2\n3\n5\n',True),('0\n1\n1\n',False),('1\n1\n3\n',False),('1\n1\n2\n0\n',False)]:
                actual.write_text(value);result=subprocess.run([str(p/'checker'),str(inp),str(actual),str(ans)],capture_output=True)
                assert (result.returncode==0)==accepted;count+=1
    return count


def small_inputs(code):
    rng=random.Random(2026110400+CODES.index(code))
    for _ in range(80):
        if code=='dtrobot':
            n=rng.randint(2,40);x=y=0;rows=[str(n),'0 0']
            for _ in range(n-1):
                dx,dy=rng.choice([(1,0),(0,1),(-1,0),(0,-1)]);x+=dx;y+=dy;rows.append(f'{x} {y}')
            yield '\n'.join(rows)+'\n'
        elif code=='dtrebuss':
            a=rng.randint(1,999);b=rng.randint(1,999);patterns=[str(a),str(b),str(a+b)]
            if rng.randrange(3)==0:patterns[2]=str(rng.randint(1,1998))
            yield '\n'.join(''.join('*' if rng.randrange(3)==0 else c for c in p) for p in patterns)+'\n'
        elif code=='dtsp':yield f'{rng.randint(0,5)} {rng.randint(0,5)} {rng.randint(0,5)} {rng.randint(1,20)}\n'
        elif code=='dtfactor':
            values=[n for n in range(2,300) if all_exponents_equal(n)]
            yield '5\n'+'\n'.join(map(str,rng.sample(values,5)))+'\n'
        elif code=='dtbtnk':
            n=rng.randint(2,12);yield ''.join(rng.choice('()') for _ in range(n))+f'\n{rng.randint(1,n//2)}\n'
        elif code=='dtdna':
            n=rng.randint(1,7);a=''.join(rng.choice('ADGT') for _ in range(n));b=list(a);rng.shuffle(b)
            if rng.randrange(4)==0:b[0]=rng.choice('ADGT')
            yield a+'\n'+''.join(b)+'\n'
        else:
            n=rng.randint(1,14);s=''.join(rng.choice('0123') for _ in range(n));s=s.lstrip('0') or '0';A=rng.randint(0,500);B=A+rng.randint(0,1000)
            yield f'{s}\n{A}\n{B}\n'


def all_exponents_equal(n):
    exponents=[];p=2
    while p*p<=n:
        if n%p==0:
            e=0
            while n%p==0:n//=p;e+=1
            exponents.append(e)
        p+=1
    if n>1:exponents.append(1)
    return len(set(exponents))==1


def greedy_regression(problem):
    if problem.basedir.name!='dtsp':return {}
    p=problem.basedir;rejected=0;details=[]
    with tempfile.TemporaryDirectory() as directory:
        actual_path=Path(directory)/'actual'
        for path in sorted((p/'in').glob('greedy_trap_*.in')):
            data=path.read_text();actual=run(p/'tests/wrong_greedy',data,cwd=directory)
            answer=p/'out'/path.with_suffix('.out').name
            assert int(actual)<int(answer.read_text()),(path.name,actual,answer.read_text())
            actual_path.write_text(actual)
            judged=subprocess.run([str(p/'checker'),str(path),str(actual_path),str(answer)],capture_output=True)
            assert judged.returncode==1,(path.name,judged.stderr)
            details.append(dict(test=path.stem,input=data.strip(),submitted=int(actual),expected=int(answer.read_text())))
            rejected+=1
    assert rejected==8
    print('dtsp: submitted greedy rejected: '+json.dumps(details),flush=True)
    return dict(submitted_greedy_rejected=rejected)


def check_problem(problem,args):
    p=problem.basedir;code=p.name
    problem.make_inputs()
    paths=sorted((p/'in').glob('*.in'))
    max_input=max(path.stat().st_size for path in paths)
    assert max_input<=INPUT_MAX,(code,max_input)
    problem.verify_inputs();problem.make_outputs(True);audit(problem)
    maximum=0
    with tempfile.TemporaryDirectory() as directory:
        actual_path=Path(directory)/'actual'
        for j,path in enumerate(paths):
            data=path.read_text();before=time.monotonic()
            actual=run(p/'sol/correct',data,timeout=problem.config['upload']['time_limit'],cwd=directory)
            maximum=max(maximum,time.monotonic()-before);actual_path.write_text(actual)
            run(p/'checker','',path,actual_path,p/'out'/path.with_suffix('.out').name)
            expected=reference(code,data);check_answer(code,data,actual,expected)
            if not path.stem.startswith('example_'):
                name,seed=path.stem.rsplit('_',1)
                assert run(p/'gen'/name,'',int(seed))==data
            if j%5==4:print(f'{code}: checked {j+1}/{len(paths)} official cases',flush=True)
        small=0
        for data in small_inputs(code):
            run(p/'verifier',data);actual=run(p/'sol/correct',data,cwd=directory)
            expected=reference(code,data);check_answer(code,data,actual,expected)
            if code=='dtbtnk':
                s,k=data.split();assert bracket_reference(s,int(k))==expected
            if code=='dtdna':assert dna_brute(*data.split())==expected
            if code=='dtrebuss':
                inp=Path(directory)/'small.in';ans=Path(directory)/'small.ans';inp.write_text(data);ans.write_text('1\n1\n2\n' if expected else 'No Solution\n');actual_path.write_text(actual)
                run(p/'checker','',inp,actual_path,ans)
            small+=1
        # Exercise the source file input/output convention.
        name=IO_NAMES[CODES.index(code)];data=(p/'in/example_00.in').read_text();(Path(directory)/(name+'.INP')).write_text(data)
        assert run(p/'sol/correct','',cwd=directory)==''
        actual_path.write_text((Path(directory)/(name+'.OUT')).read_text())
        run(p/'checker','',p/'in/example_00.in',actual_path,p/'out/example_00.out')
    invalid=invalid_checks(problem);checker=checker_checks(problem);regression=greedy_regression(problem)
    if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
    problem.assert_hashes()
    result=dict(official=len(paths),small=small,invalid=invalid,checker=checker,file_io=1,max_input_bytes=max_input,max_runtime_seconds=round(maximum,4),hashes=2*len(paths),**regression)
    print(f'{code}: PASS; {result}',flush=True);return result


def main():
    parser=argparse.ArgumentParser();parser.add_argument('--problem',choices=CODES,action='append');parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR,format='%(message)s')
    problems=[Problem(ROOT,ROOT/'dtqg'/code) for code in (args.problem or CODES)]
    sources=[HERE/'oracle_sp.cpp',HERE/'oracle_factor.cpp']
    for p in problems:
        p.health_check();p.generate_params_h()
        sources += [p.basedir/x for x in ('sol/correct.cpp','verifier.cpp','checker.cpp')]
        sources += [p.basedir/'gen'/test['name'] for test in p.config['tests'] if test['name'].endswith('.cpp')]
        if p.basedir.name=='dtsp':sources.append(p.basedir/'tests/wrong_greedy.cpp')
    print(f'Compiling {len(sources)} programs...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:list(pool.map(build,sources))
    results={}
    for p in problems:results[p.basedir.name]=check_problem(p,args)
    result_path=HERE/'results.json'
    if result_path.exists():results={**json.loads(result_path.read_text()),**results}
    result_path.write_text(json.dumps(results,indent=2,ensure_ascii=False)+'\n')
    print('All selected packages passed; every input <= 1000000 bytes; hashes verified; no HTML generated.',flush=True)


if __name__=='__main__':main()
