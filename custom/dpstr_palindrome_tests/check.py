"""Generate and audit group 7, without HTML or uploads."""
import argparse
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass, field, replace
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

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from problem import Problem
from problem_upload import ProblemUpload

CODES=[600,601,602,603,630,631,632,650,651,652]
NAMES=[f'dpstr{c}' for c in CODES]
LIMITS={c:4000 if c==651 else 5000 for c in CODES}
ORACLE=Path(__file__).with_name('oracle')
MOD=1000000007

@dataclass
class Case:
    s:str
    queries:list=field(default_factory=list)
    delete:list=field(default_factory=list)
    change:list=field(default_factory=list)
    k:int=0

def encode(code,c):
    n=len(c.s);head=str(n)
    if code==600:head+=' '+str(len(c.queries))
    if code==651:head+=' '+str(c.k)
    data=head+'\n'+c.s+'\n'
    if code==600:data+=''.join(f'{l} {r}\n' for l,r in c.queries)
    if code==631:data+=' '.join(map(str,c.delete))+'\n'
    if code==650:data+=''.join(f'{x} {y}\n' for x,y in zip(c.delete,c.change))
    return data

def decode(code,data):
    lines=data.splitlines();head=list(map(int,lines[0].split()));c=Case(lines[1])
    if code==600:c.queries=[tuple(map(int,line.split())) for line in lines[2:]]
    if code==631:c.delete=list(map(int,lines[2].split()))
    if code==650:
        values=[tuple(map(int,line.split())) for line in lines[2:]]
        c.delete=[v[0] for v in values];c.change=[v[1] for v in values]
    if code==651:c.k=head[1]
    return c

def brute(code,c):
    s=c.s;n=len(s)
    if code==600:return '\n'.join('YES' if s[l-1:r]==s[l-1:r][::-1] else 'NO' for l,r in c.queries)
    if code in (601,602):
        segments=[(r-l+1,l+1) for l in range(n) for r in range(l,n) if s[l:r+1]==s[l:r+1][::-1]]
        if code==602:return str(len(segments))
        length,start=min(segments,key=lambda x:(-x[0],x[1]));return f'{length} {start}'
    best=0 if code not in (631,650) else sum(c.delete)
    count=0;contents=set()
    for mask in range(1<<n):
        indices=[i for i in range(n) if mask>>i&1];word=''.join(s[i] for i in indices)
        pal=word==word[::-1]
        if code in (603,630) and pal:best=max(best,len(word))
        if code==631 and pal:best=min(best,sum(c.delete[i] for i in range(n) if not mask>>i&1))
        if code==632 and mask and pal:count+=1
        if code==652 and mask and pal:contents.add(word)
        if code in (650,651):
            errors=0;price=sum(c.delete[i] for i in range(n) if not mask>>i&1) if code==650 else 0
            for j in range(len(indices)//2):
                x,y=indices[j],indices[-j-1]
                if s[x]!=s[y]:
                    errors+=1
                    if code==650:price+=min(c.change[x],c.change[y])
            if code==650:best=min(best,price)
            elif errors<=c.k:best=max(best,len(indices))
    if code==630:return str(n-best)
    if code==632:return str(count%MOD)
    if code==652:return str(len(contents)%MOD)
    return str(best)

def run(executable,data,*args,timeout=15):
    started=time.perf_counter()
    result=subprocess.run([str(executable),*map(str,args)],input=data,text=True,capture_output=True,timeout=timeout)
    assert result.returncode==0,(executable,result.stderr)
    return result.stdout.strip(),time.perf_counter()-started

def compile_source(path):
    standard='c++11' if path.parent.name=='sol' else 'c++17'
    result=subprocess.run(['g++','-O2',f'-std={standard}','-Wall','-Wextra','-Werror','-Wno-unused-result',
                           '-I',str(ROOT/'common'),str(path),'-o',str(path.with_suffix(''))],text=True,capture_output=True)
    assert result.returncode==0,(path,result.stderr)

def audit_config(problem,code):
    conf=problem.config
    assert conf['timelimit']==1.0 and isinstance(conf['timelimit'],float)
    assert conf['upload']==dict(time_limit=1.0,memory_limit=131072,group='03',classes='C',
                               types=['dp_string','dp_palindrome'],
                               allowed_languages=['PY3','CPP11','CPP14','CPP17','CPP20','JAVA8','C','PAS'],partial=True)
    assert isinstance(conf['upload']['time_limit'],float)
    assert conf['params']['N_MAX']==LIMITS[code]
    assert conf['params']['K_MAX']==(5 if code==651 else 0)
    if code==600:assert conf['params']['Q_MAX']==500000
    assert sum(t['number'] for t in conf['tests'])==34
    upload=ProblemUpload(problem)
    assert upload.manifest['checker']=='standard'
    assert upload.payload['types']==['dp_string','dp_palindrome'] and upload.payload['time_limit']==1.0
    n=LIMITS[code];work=n*(n+1)//2*(6 if code==651 else 3 if code in (631,650) else 1)
    if code==600:work+=500000
    assert work<=50_000_000
    memory=n*n*4 if code==652 else n*n if code==600 else 6*n*8
    assert memory<120*1024**2

def audit_statement(p,code):
    task=(p/'task.md').read_text();solution=(p/'solution.md').read_text()
    headings=re.findall(r'^#{1,6} .+$',task,re.M)
    assert headings[0].startswith('# '+p.name.upper()+' — ')
    assert headings[1:]==['### Đề bài','### Dữ liệu vào','### Dữ liệu ra','### Ràng buộc',
                          '### Sample Input 1','### Sample Output 1','### Sample Input 2','### Sample Output 2','### Giải thích']
    blocks=re.findall(r'```text\n(.*?)\n```',task,re.S);assert len(blocks)==4
    for i in range(2):
        data=(p/'gen'/f'example_{i:02}.in').read_text()
        assert data==blocks[2*i]+'\n'
        assert brute(code,decode(code,data))==blocks[2*i+1]
    for document in (task,solution):
        assert all(line.count('$')%2==0 for line in document.splitlines())
        assert not any(ord(c)<32 and c not in '\n\t' for c in document)
    assert not re.search(r'^# ',solution,re.M)
    assert not re.search(r'kiểm thử|bộ sinh|oracle|verifier|checker|benchmark|chạy test',solution,re.I)
    assert not list(p.glob('*.html'))

def audit_verifier(p,code,sample):
    c=decode(code,sample);lines=sample.splitlines()
    invalid=['',sample+'0\n','\n'.join(lines[:-1])+'\n']
    for bad in (0,LIMITS[code]+1):
        rows=lines.copy();head=rows[0].split();head[0]=str(bad);rows[0]=' '.join(head);invalid.append('\n'.join(rows)+'\n')
    for word in ('',c.s+'a','A','#','?'):
        rows=lines.copy();rows[1]=word;invalid.append('\n'.join(rows)+'\n')
    if code==600:
        for q in (0,500001):
            rows=lines.copy();rows[0]=f'{len(c.s)} {q}';invalid.append('\n'.join(rows)+'\n')
        for pair in [(0,1),(1,len(c.s)+1),(2,1)]:invalid.append(encode(code,replace(c,queries=[pair])))
    if code==651:
        for k in (-1,6):invalid.append(encode(code,replace(c,k=k)))
    if code in (631,650):
        for bad in (-1,10**9+1):
            invalid.append(encode(code,replace(c,delete=[bad]+c.delete[1:])))
            if code==650:invalid.append(encode(code,replace(c,change=[bad]+c.change[1:])))
    for data in invalid:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(p,'accepted invalid input',data[:200])

def audit_checker(p,data,answer):
    tokens=answer.split();wrong=tokens.copy()
    wrong[0]='NO' if tokens[0]=='YES' else 'YES' if tokens[0]=='NO' else str(int(tokens[0])+1)
    outputs=[(answer+'\n',True),(' \n'+' \n'.join(tokens)+' \n',True),('',False),('x\n',False),
             (' '.join(wrong)+'\n',False),(answer+' 0\n',False),(answer+' x\n',False)]
    if len(tokens)>1:
        outputs.append((' '.join(tokens[:-1])+'\n',False))
        wrong=tokens.copy();wrong[-1]='NO' if tokens[-1]=='YES' else 'YES' if tokens[-1]=='NO' else str(int(tokens[-1])+1)
        outputs.append((' '.join(wrong)+'\n',False))
    with tempfile.TemporaryDirectory() as directory:
        inp,out,ans=[Path(directory)/x for x in ['in','out','ans']]
        inp.write_text(data);ans.write_text(answer+'\n')
        for output,expected in outputs:
            out.write_text(output)
            result=subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True)
            assert (result.returncode==0)==expected,(p,output[:200],result.stderr)

def extra_cases(code):
    rng=random.Random(20261106+code)
    for n in range(1,7):
        for bits in itertools.product('ab',repeat=n):
            s=''.join(bits)
            queries=[(l+1,r+1) for l in range(n) for r in range(l,n)] if code==600 else []
            for k in (0,1,2) if code==651 else (0,):
                yield Case(s,queries,[1+i%3 for i in range(n)],[3-i%3 for i in range(n)],k)
    for _ in range(120):
        n=rng.randint(1,12);s=''.join(rng.choice('abcd') for _ in range(n))
        queries=[(l+1,r+1) for l in range(n) for r in range(l,n)] if code==600 else []
        yield Case(s,queries,[rng.choice([0,1,7,10**9]) for _ in s],
                   [rng.choice([0,1,5,10**9]) for _ in s],rng.randint(0,5))
    for s in ['aaba','abba','abca','aaab','bccb','abcd','abacaba','aaaaaa','aabbcc','bbabcbcab']:
        n=len(s)
        yield Case(s,[(1,n),(1,1),(n,n)],list(range(1,n+1)),[10**9]*n,1)
    if code in (631,650):
        for first in (0,1):yield Case('aaba',delete=[first,100,1000,1],change=[10**9]*4)
    if code==651:
        for k in range(6):yield Case('abcdefghi',k=k)

def closed_form(code,c):
    s=c.s;n=len(s)
    if len(set(s))==1:
        if code==600:return '\n'.join('YES' for _ in c.queries)
        if code==601:return f'{n} 1'
        if code==602:return str(n*(n+1)//2)
        if code in (603,651):return str(n)
        if code in (630,631,650):return '0'
        if code==632:return str((pow(2,n,MOD)-1)%MOD)
        if code==652:return str(n)
    if code in (631,650) and not any(c.delete):return '0'
    if code==650 and not any(c.change):return '0'
    return None

def assert_reproducible(problem):
    p=problem.basedir
    for test in problem.config['tests']:
        if not test['name'].endswith('.cpp'):continue
        for seed in range(test['number']):
            generator=p/'gen'/Path(test['name']).stem
            assert run(generator,'',seed)[0]+'\n'==(p/'in'/f'{generator.name}_{seed:02}.in').read_text()

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true');args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR)
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem]
    sources=[ORACLE.with_suffix('.cpp')]
    for problem in problems:
        p=problem.basedir;code=int(p.name[5:]);problem.health_check();problem.generate_params_h()
        audit_config(problem,code);audit_statement(p,code)
        sources+=[problem.get_correct_filename(),problem.checker,problem.verifier]
        sources+=[p/'gen'/t['name'] for t in problem.config['tests'] if t['name'].endswith('.cpp')]
    print(f'Compiling {len(sources)} sources...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source,sources):pass
    report=[]
    for problem in problems:
        p=problem.basedir;code=int(p.name[5:]);started=time.monotonic()
        problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
        assert problem.check_all_solutions_used()
        maximum=False;full_budget=False;full_queries=False;wide=False;brutes=0;formulas=0;worst=0;worst_name=''
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text();c=decode(code,data)
            expected=(p/'out'/path.with_suffix('.out').name).read_text().strip()
            actual,elapsed=run(p/'sol/correct',data,timeout=problem.config['timelimit'])
            assert actual==expected,(path,'reference')
            if elapsed>worst:worst=elapsed;worst_name=path.name
            assert run(ORACLE,data,code)[0]==expected,(path,'independent oracle')
            if path.stem.startswith(('example','edge','small')):
                assert brute(code,c)==expected,(path,'brute force');brutes+=1
            formula=closed_form(code,c)
            if formula is not None:assert formula==expected,(path,'closed form');formulas+=1
            maximum|=len(c.s)==LIMITS[code]
            full_budget|=len(c.s)==LIMITS[code] and c.k==5
            full_queries|=len(c.s)==LIMITS[code] and len(c.queries)==500000
            if code==600 and len(c.s)==LIMITS[code] and len(c.queries)==500000:
                assert sum(r-l+1 for l,r in c.queries)>=2_000_000_000,(path,'queries are too short')
            if code in (631,650):wide|=int(expected)>2**31-1
        assert maximum
        if code==600:assert full_queries
        if code==651:assert full_budget
        if code in (631,650):assert wide
        count=0
        for c in extra_cases(code):
            data=encode(code,c);expected=brute(code,c)
            assert run(p/'sol/correct',data)[0]==expected,(p,data,'brute mismatch')
            assert run(ORACLE,data,code)[0]==expected,(p,data,'oracle mismatch')
            count+=1
        sample=(p/'gen/example_00.in').read_text()
        audit_verifier(p,code,sample);audit_checker(p,sample,brute(code,decode(code,sample)))
        large=(p/'in/max_01.in').read_text();audit_checker(p,large,(p/'out/max_01.out').read_text().strip())
        assert_reproducible(problem)
        if args.update_hashes:(p/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
        problem.assert_hashes()
        report.append((p.name,brutes,count,formulas,worst,worst_name))
        print(f'{p.name}: 34 pairs; {brutes} generated + {count} additional brute cases; {formulas} formulas; '
              f'oracle, verifier, checker, metadata, reproducibility, hashes OK; slowest {worst:.3f}s ({worst_name}); '
              f'total {time.monotonic()-started:.1f}s.',flush=True)
    lines=['# Kết quả kiểm tra nhóm 7','',
           'Lời giải C++11, giới hạn 1 giây mỗi test trên máy cục bộ. Không xuất HTML hoặc upload.','',
           '| Mã | Cặp test | Vét cạn test đã sinh | Vét cạn bổ sung | Công thức | Chậm nhất (giây) | Test |',
           '| --- | --- | --- | --- | --- | --- | --- |']
    for name,brutes,count,formulas,worst,test in report:lines.append(f'| {name} | 34 | {brutes} | {count} | {formulas} | {worst:.4f} | {test} |')
    lines+=['',f'Tổng: {34*len(report)} cặp test; {sum(x[1] for x in report)} lượt vét cạn dữ liệu đã sinh; '
            f'{sum(x[2] for x in report)} trường hợp bổ sung.','',
            'Đối chiếu oracle, verifier, checker, cấu hình, cấu trúc đề, tính tái lập và mã băm đều đạt.']
    path=Path(__file__).with_name('results.md') if len(problems)==len(CODES) else problems[0].basedir/'tests/results.md'
    path.write_text('\n'.join(lines)+'\n');print('All checks passed. No HTML or uploads.',flush=True)

if __name__=='__main__':main()
