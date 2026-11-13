"""Build, generate and audit group 4 without HTML or network access."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass, replace
import itertools
import json
import logging
import math
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile
import time

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from problem import Problem
from problem_upload import ProblemUpload

CODES=[0,1,2,3,30,31,32,50,51,52]
NAMES=[f'dpstr{300+x}' for x in CODES]
LIMITS={c:200000 if c<3 else 2500 if c in (31,51) else 2000 if c==50 else 5000 for c in CODES}
PATTERNS={0:'ab',1:'abc',2:'aba'}
MOD=1000000007
ORACLE=Path(__file__).with_name('oracle')

@dataclass
class Case:
    a:str
    b:str='a'
    k:int=0
    marked:str=''
    low:int=1
    high:int=1

def encode(code,c):
    head=str(len(c.a))
    if code>=3:head+=' '+str(len(c.b))
    if code in (31,50,51):head+=' '+str(c.k)
    if code==52:head+=f' {c.low} {c.high}'
    data=head+'\n'+c.a+'\n'
    if code>=3:data+=c.b+'\n'
    if code==31:data+=(c.marked or '0'*len(c.a))+'\n'
    return data

def decode(code,data):
    lines=data.splitlines();head=list(map(int,lines[0].split()))
    c=Case(lines[1],PATTERNS[code] if code<3 else lines[2])
    if code in (31,50,51):c.k=head[2]
    if code==31:c.marked=lines[3]
    if code==52:c.low,c.high=head[2:]
    return c

def brute(code,c):
    """Enumerate position sets; sum compatible full wildcard assignments."""
    answer=0
    for indices in itertools.combinations(range(len(c.a)),len(c.b)):
        if code==31 and sum(c.marked[i]=='1' for i in indices)!=c.k:continue
        if code==32 and any(y-x<2 for x,y in zip(indices,indices[1:])):continue
        if code==50 and 1+sum(y-x>1 for x,y in zip(indices,indices[1:]))!=c.k:continue
        if code==52 and any(not c.low<=y-x<=c.high for x,y in zip(indices,indices[1:])):continue
        selected=''.join(c.a[i] for i in indices)
        if code==51:
            if sum(x!=y for x,y in zip(selected,c.b))<=c.k:answer+=1
        elif code==30:
            if all(x=='?' or x==y for x,y in zip(selected,c.b)):
                unused=c.a.count('?')-selected.count('?')
                answer+=26**unused
        elif selected==c.b:answer+=1
    return str(answer if code<3 else answer%MOD)

def run(path,data,*args,timeout=5):
    start=time.perf_counter()
    result=subprocess.run([str(path),*map(str,args)],input=data,text=True,capture_output=True,timeout=timeout)
    assert result.returncode==0,(path,result.stderr)
    return result.stdout.strip(),time.perf_counter()-start

def compile_source(path):
    standard='c++11' if path.parent.name=='sol' else 'c++17'
    result=subprocess.run(['g++','-O2',f'-std={standard}','-Wall','-Wextra','-Werror',
                           '-Wno-unused-result','-I',str(ROOT/'common'),str(path),'-o',str(path.with_suffix(''))],
                          text=True,capture_output=True)
    assert result.returncode==0,(path,result.stderr)

def audit_statement(p,code):
    text=(p/'task.md').read_text()
    headings=re.findall(r'^#{1,6} .+$',text,re.M)
    assert headings[0].startswith('# '+p.name.upper()+' — ')
    assert headings[1:]==['### Đề bài','### Dữ liệu vào','### Dữ liệu ra','### Ràng buộc',
                          '### Sample Input 1','### Sample Output 1','### Sample Input 2','### Sample Output 2','### Giải thích']
    blocks=re.findall(r'```text\n(.*?)\n```',text,re.S)
    assert len(blocks)==4
    for i in range(2):
        data=(p/'gen'/f'example_{i:02}.in').read_text()
        assert blocks[2*i]+'\n'==data
        assert brute(code,decode(code,data))==blocks[2*i+1]
    solution=(p/'solution.md').read_text()
    for document in (text,solution):
        assert all(line.count('$')%2==0 for line in document.splitlines()),(p,'broken inline formula')
        assert not any(ord(c)<32 and c not in '\n\t' for c in document),(p,'control character in text')
    assert not re.search(r'^# ',solution,re.M)
    assert not re.search(r'kiểm thử|bộ sinh|oracle|verifier|checker|benchmark|chạy test',solution,re.I)
    assert not list(p.glob('*.html'))

def audit_config(problem,code):
    conf=problem.config
    assert conf['timelimit']==1
    assert conf['upload']==dict(time_limit=1,group='03',classes='C',types=['dp_string'],
                               allowed_languages=['PY3','CPP11','CPP14','CPP17','CPP20','JAVA8','C','PAS'],partial=True)
    assert conf['params']['N_MAX']==LIMITS[code]
    assert sum(t['number'] for t in conf['tests'])==34
    assert ProblemUpload(problem).manifest['checker']=='standard'
    n=LIMITS[code]
    work=3*n if code<3 else n*n*(12 if code==50 else 6 if code in (31,51) else 1)
    assert work<=50_000_000

def audit_verifier(p,code,sample):
    c=decode(code,sample);lines=sample.splitlines()
    invalid=['',sample+'0\n','\n'.join(lines[:-1])+'\n']
    for index in range(1 if code<3 else 2):
        for bad in (0,LIMITS[code]+1):
            rows=lines.copy();head=rows[0].split();head[index]=str(bad);rows[0]=' '.join(head)
            invalid.append('\n'.join(rows)+'\n')
    for index in range(1,2 if code<3 else 3):
        for bad in ('',lines[index]+'a','A','#'):
            rows=lines.copy();rows[index]=bad;invalid.append('\n'.join(rows)+'\n')
    if code!=30:invalid.append(encode(code,replace(c,a='?'+c.a[1:])))
    if code>=3:invalid.append(encode(code,replace(c,b='?'+c.b[1:])))
    if code in (31,50,51):
        for bad in (-1,6):invalid.append(encode(code,replace(c,k=bad)))
    if code==31:
        for mark in ('',c.marked+'0','2'*len(c.a)):invalid.append(encode(code,replace(c,marked=mark or '2')))
    if code==52:
        for low,high in [(0,1),(2,1),(1,len(c.a)+1)]:invalid.append(encode(code,replace(c,low=low,high=high)))
    for data in invalid:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(p,'accepted invalid input',data[:100])

def audit_checker(p,data,answer):
    value=int(answer)
    outputs=[(answer+'\n',True),(' \n'+answer+' \n',True),('',False),('x\n',False),
             (str(value+1)+'\n',False),(answer+' 0\n',False),(answer+' x\n',False),('-1\n',False)]
    with tempfile.TemporaryDirectory() as directory:
        inp,ans,out=[Path(directory)/name for name in ['in','ans','out']]
        inp.write_text(data);ans.write_text(answer+'\n')
        for output,valid in outputs:
            out.write_text(output)
            result=subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True)
            assert (result.returncode==0)==valid,(p,output,result.stderr)

def extra_cases(code):
    words=[''.join(x) for length in range(1,5) for x in itertools.product('ab',repeat=length)]
    if code<3:
        for n in range(1,8):
            for chars in itertools.product('abc',repeat=n):yield Case(''.join(chars),PATTERNS[code])
    else:
        targets=words[:6]
        for a,b in itertools.product(words,targets):
            for k in (0,1,2) if code in (31,50,51) else (0,):
                yield Case(a,b,k=k,marked=('01'*len(a))[:len(a)],low=1,high=min(2,len(a)))
    rng=random.Random(20261104+code)
    for _ in range(120):
        a=''.join(rng.choice('abc?' if code==30 else 'abc') for _ in range(rng.randint(1,12)))
        b=PATTERNS[code] if code<3 else ''.join(rng.choice('abc') for _ in range(rng.randint(1,6)))
        low=rng.randint(1,len(a));high=rng.randint(low,len(a))
        yield Case(a,b,k=rng.randint(0,5),marked=''.join(rng.choice('01') for _ in a),low=low,high=high)
    if code==30:
        for a in ['?','??','a?','?a?','???','a??b?']:
            for b in ['a','aa','ab','aaa']:yield Case(a,b)
    if code==52:
        for low in range(1,6):
            for high in range(low,6):yield Case('aaaaa','aa',low=low,high=high)

def assert_reproducible(problem):
    for test in problem.config['tests']:
        if not test['name'].endswith('.cpp'):continue
        for seed in range(test['number']):
            generator=problem.basedir/'gen'/Path(test['name']).stem
            output=run(generator,'',seed)[0]+'\n'
            expected=(problem.basedir/'in'/f'{generator.name}_{seed:02}.in').read_text()
            assert output==expected,(generator,seed)

def closed_form(code,c):
    n,m=len(c.a),len(c.b)
    if code>=3 and set(c.a)==set(c.b)=={'a'}:
        if code in (3,51):return math.comb(n,m)%MOD if n>=m else 0
        if code==30:return math.comb(n,m)%MOD if n>=m else 0
        if code==31:
            marked=c.marked.count('1');unmarked=n-marked
            return (math.comb(marked,c.k)*math.comb(unmarked,m-c.k))%MOD if c.k<=marked and 0<=m-c.k<=unmarked else 0
        if code==32:return math.comb(n-m+1,m)%MOD if n>=2*m-1 else 0
        if code==50:return math.comb(m-1,c.k-1)*math.comb(n-m+1,c.k)%MOD if 1<=c.k<=m and c.k<=n-m+1 else 0
        if code==52 and c.low==1 and c.high==n:return math.comb(n,m)%MOD if n>=m else 0
    if code==30 and set(c.a)=={'?'}:
        return math.comb(n,m)*pow(26,n-m,MOD)%MOD if n>=m else 0
    return None

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args();logging.basicConfig(level=logging.ERROR)
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem]
    sources=[ORACLE.with_suffix('.cpp')]
    for problem in problems:
        code=int(problem.basedir.name[5:])-300
        problem.health_check();problem.generate_params_h();audit_config(problem,code);audit_statement(problem.basedir,code)
        sources+=[problem.get_correct_filename(),problem.checker,problem.verifier]
        sources+=[problem.basedir/'gen'/t['name'] for t in problem.config['tests'] if t['name'].endswith('.cpp')]
    print(f'Compiling {len(sources)} sources...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source,sources):pass
    report=[]
    for problem in problems:
        p=problem.basedir;code=int(p.name[5:])-300;started=time.monotonic()
        problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
        assert problem.check_all_solutions_used()
        worst=0;worst_name='';brutes=0;formulas=0;maximum=False;wide=False
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text();c=decode(code,data)
            expected=(p/'out'/path.with_suffix('.out').name).read_text().strip()
            actual,elapsed=run(p/'sol/correct',data,timeout=problem.config['timelimit'])
            assert actual==expected,(path,'reference')
            if elapsed>worst:worst=elapsed;worst_name=path.name
            assert run(ORACLE,data,code)[0]==expected,(path,'independent oracle')
            if path.stem.startswith(('example','edge','small')):
                assert brute(code,c)==expected,(path,'position-set enumeration');brutes+=1
            formula=closed_form(code,c)
            if formula is not None:assert str(formula)==expected,(path,'closed form');formulas+=1
            maximum|=len(c.a)==LIMITS[code] and (code<3 or len(c.b)==LIMITS[code])
            wide|=int(expected)>2**31-1
        assert maximum,(p,'maximum sizes')
        if code<3:assert wide,(p,'64-bit answer')
        count=0
        for c in extra_cases(code):
            data=encode(code,c);expected=brute(code,c)
            assert run(p/'sol/correct',data)[0]==expected,(p,data,'brute mismatch')
            assert run(ORACLE,data,code)[0]==expected,(p,data,'oracle mismatch')
            count+=1
        sample=(p/'gen/example_00.in').read_text()
        audit_verifier(p,code,sample);audit_checker(p,sample,brute(code,decode(code,sample)))
        audit_checker(p,(p/'in/max_01.in').read_text(),(p/'out/max_01.out').read_text().strip())
        assert_reproducible(problem)
        if args.update_hashes:(p/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
        problem.assert_hashes()
        report.append((p.name,brutes,count,formulas,worst,worst_name))
        print(f'{p.name}: 34 pairs; {brutes} generated + {count} additional brute cases; {formulas} formulas; '
              f'oracle, verifier, checker, metadata, reproducibility, hashes OK; slowest {worst:.3f}s ({worst_name}); '
              f'total {time.monotonic()-started:.1f}s.',flush=True)
    lines=['# Kết quả kiểm tra nhóm 4','',
           'Lời giải C++11, 1 giây mỗi test trên máy cục bộ. Không xuất HTML hoặc upload.','',
           '| Mã | Cặp test | Vét cạn test đã sinh | Vét cạn bổ sung | Công thức | Chậm nhất (giây) | Test |',
           '| --- | --- | --- | --- | --- | --- | --- |']
    for name,brutes,count,formulas,worst,test in report:lines.append(f'| {name} | 34 | {brutes} | {count} | {formulas} | {worst:.4f} | {test} |')
    lines+=['',f'Tổng: {34*len(report)} cặp test; {sum(x[1] for x in report)} lượt vét cạn dữ liệu đã sinh; '
            f'{sum(x[2] for x in report)} trường hợp bổ sung.','',
            'Tất cả đối chiếu độc lập và kiểm tra cấu hình, công cụ, dữ liệu, tính tái lập, mã băm đều đạt.']
    destination=Path(__file__).with_name('results.md') if len(problems)==10 else problems[0].basedir/'tests/results.md'
    destination.write_text('\n'.join(lines)+'\n')
    print('All checks passed. No HTML or uploads.',flush=True)

if __name__=='__main__':main()
