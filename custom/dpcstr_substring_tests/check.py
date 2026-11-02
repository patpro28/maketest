"""Generate and audit dpcstr2xx substring problems without HTML or uploads."""
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

CODES=[200,201,202,203,230,231,232,250,251,252]
NAMES=[f'dpcstr{x}' for x in CODES]
ORACLE=Path(__file__).with_name('oracle')
LIMITS={code:350 if code==250 else 4000 if code==251 else 2500 if code in (231,252) else 5000 for code in CODES}


@dataclass
class Case:
    a:str
    b:str
    d:str='a'
    target:str='a'
    k:int=0
    penalty:int=0
    weights:list=field(default_factory=lambda:[1]*26)


def decode(code,data):
    lines=data.splitlines()
    head=list(map(int,lines[0].split()))
    case=Case(lines[1],lines[2])
    if code==250:case.d=lines[3]
    if code==202:case.target=lines[3]
    if code in (231,252):case.k=head[2]
    if code==252:case.penalty=head[3]
    if code in (230,252):case.weights=list(map(int,lines[3].split()))
    return case


def encode(code,c):
    head=f'{len(c.a)} {len(c.b)}'
    if code==250:head+=f' {len(c.d)}'
    if code in (231,252):head+=f' {c.k}'
    if code==252:head+=f' {c.penalty}'
    data=head+f'\n{c.a}\n{c.b}\n'
    if code==250:data+=c.d+'\n'
    if code==202:data+=c.target+'\n'
    if code in (230,252):data+=' '.join(map(str,c.weights))+'\n'
    return data


def brute(code,c):
    a,b=c.a,c.b
    if code==203:b=b[::-1]
    if code==250:
        return str(max((length for i in range(len(a)) for length in range(1,len(a)-i+1)
                        if a[i:i+length] in b and a[i:i+length] in c.d),default=0))
    best=0;where=(0,0);count=0;blocks=[]
    for i in range(len(a)):
        for j in range(len(b)):
            errors=0;score=0
            for length in range(1,min(len(a)-i,len(b)-j)+1):
                x,y=a[i+length-1],b[j+length-1]
                errors+=x!=y
                if code in (231,252):
                    if errors>c.k:break
                    score+=c.weights[ord(x)-97] if x==y else -c.penalty
                    best=max(best,length if code==231 else score)
                    continue
                if x!=y:break
                if code==232:count+=1
                elif code==230:
                    score+=c.weights[ord(x)-97];best=max(best,score)
                elif code==202:
                    if c.target in a[i:i+length]:best=max(best,length)
                elif code==201:
                    if length>best or (length==best and (i+1,j+1)<where):best=length;where=(i+1,j+1)
                elif code==251:blocks.append((i,j,length))
                else:best=max(best,length)
    if code==251:
        return str(max((l+h for i,j,l in blocks for u,v,h in blocks if i+l<=u and j+l<=v),default=-1))
    if code==201:return f'{best} {where[0]} {where[1]}'
    if code==232:return str(count)
    if code==202:return str(best or -1)
    return str(best)


def run(executable,data,*args,timeout=5):
    start=time.perf_counter()
    result=subprocess.run([str(executable),*map(str,args)],input=data,text=True,capture_output=True,timeout=timeout)
    elapsed=time.perf_counter()-start
    assert result.returncode==0,(executable,result.stderr)
    return result.stdout.strip(),elapsed


def compile_source(path):
    standard='c++11' if path.parent.name=='sol' else 'c++17'
    result=subprocess.run(['g++','-O2',f'-std={standard}','-Wall','-Wextra','-Werror','-Wno-unused-result',
                           '-I',str(ROOT/'common'),str(path),'-o',str(path.with_suffix(''))],capture_output=True,text=True)
    assert result.returncode==0,(path,result.stderr)


def audit_config(problem,code):
    conf=problem.config
    assert conf['timelimit']==0.5
    assert conf['upload']==dict(time_limit=0.5,group='03',classes='C',types=['dp_common_substring'],
                               allowed_languages=['PY3','CPP11','CPP14','CPP17','CPP20','JAVA8','C','PAS'],partial=True)
    assert conf['params']['N_MAX']==LIMITS[code]
    assert sum(t['number'] for t in conf['tests'])==(35 if code==230 else 34)
    assert len(conf['solutions'])==1
    assert ProblemUpload(problem).manifest['checker']=='standard'
    size=LIMITS[code]
    work=size**3 if code==250 else 3*size**2 if code==251 else 6*size**2 if code in (231,252) else size**2
    assert work<=50_000_000,(code,work)


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
        assert brute(code,decode(code,data))==blocks[2*i+1],(p,'sample',i)
    solution=(p/'solution.md').read_text()
    assert not re.search(r'kiểm thử|bộ sinh|oracle|verifier|checker|benchmark|chạy test',solution,re.I)
    assert not list(p.glob('*.html'))


def audit_verifier(p,code,sample):
    c=decode(code,sample);lines=sample.splitlines()
    invalid=['',sample+'0\n',sample.rsplit('\n',2)[0]+'\n']
    for index in range(3 if code==250 else 2):
        for bad in (-1,0,LIMITS[code]+1):
            head=lines[0].split();head[index]=str(bad)
            invalid.append(' '.join(head)+'\n'+'\n'.join(lines[1:])+'\n')
    for index in range(1,4 if code==250 else 3):
        for bad in ('',lines[index]+'a','#','A'):
            rows=lines.copy();rows[index]=bad;invalid.append('\n'.join(rows)+'\n')
    if code==202:
        for target in ('aa','A','#'):invalid.append(encode(code,replace(c,target=target)))
    if code in (231,252):
        for k in (-1,6):invalid.append(encode(code,replace(c,k=k)))
    if code==252:
        for penalty in (-1,10**9+1):invalid.append(encode(code,replace(c,penalty=penalty)))
    if code in (230,252):
        for bad in (-10**9-1,10**9+1):invalid.append(encode(code,replace(c,weights=[bad]+c.weights[1:])))
        invalid.append(encode(code,replace(c,weights=c.weights[:-1])))
    for data in invalid:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(p,'accepted invalid input',data)


def audit_checker(p,data,answer,extra_wrong=()):
    tokens=answer.split();bad=tokens.copy();bad[0]=str(int(bad[0])+1)
    outputs=[(answer+'\n',True),(' \n'+answer+' \n',True),(' '.join(bad)+'\n',False),
             ('',False),('x\n',False),(answer+' 0\n',False),(answer+' junk\n',False)]
    outputs.extend((str(value)+'\n',False) for value in extra_wrong)
    if len(tokens)>1:
        outputs.append((tokens[0]+'\n',False))
        for index in (1,2):
            changed=tokens.copy();changed[index]=str(int(changed[index])+1)
            outputs.append((' '.join(changed)+'\n',False))
    with tempfile.TemporaryDirectory() as directory:
        inp,ans,out=[Path(directory)/name for name in ['in','ans','out']]
        inp.write_text(data);ans.write_text(answer+'\n')
        for output,valid in outputs:
            out.write_text(output)
            result=subprocess.run([str(p/'checker'),str(inp),str(out),str(ans)],capture_output=True)
            assert (result.returncode==0)==valid,(p,output,result.stderr)


def random_cases(code):
    rng=random.Random(20261101+code)
    for _ in range(100):
        words=[''.join(rng.choice('abcx') for _ in range(rng.randint(1,8))) for _ in range(3)]
        yield Case(*words,target=rng.choice('abxz'),k=rng.randint(0,5),penalty=rng.choice([0,1,10**9]),
                   weights=[rng.choice([-10**9,-3,0,2,10**9]) for _ in range(26)])


def exhaustive_cases(code):
    words=[''.join(x) for length in range(1,4) for x in itertools.product('ab',repeat=length)]
    third=['a','b','ab','ba'] if code==250 else ['a']
    for a,b,d in itertools.product(words,words,third):
        yield Case(a,b,d,k=1,penalty=2,weights=[-2,5]+[0]*24)


def targeted_cases(code):
    pairs=[('abcde','abzde'),('abc','abc'),('aaa','bbb'),('aaaa','aaa'),('ab','ab'),('ab','ba'),
           ('axbc','abcd'),('xab','abx'),('abxcd','abycd'),('ababa','babab'),('abab','zzabababab'),
           ('aabaa','aacaa'),('zaaz','zaaz'),('xabc','abcy')]
    for a,b in pairs:
        yield Case(a,b,'abc',target='x',k=1,penalty=1,weights=[5,-20,7]+[0]*23)
    if code in (231,252):
        for k in range(6):
            yield Case('aaaaaa','bbbbbb',k=k,penalty=0)
            yield Case('aabbaa','aaccaa',k=k,penalty=3,weights=[5,-1,-1]+[0]*23)
    if code==202:
        for a,b,c in [('axbc','aybc','x'),('abca','abca','b'),('a','a','a'),('abc','abc','z')]:
            yield Case(a,b,target=c)
    if code in (230,252):
        yield Case('abc','abc',weights=[-1]*26)
        yield Case('abc','abc',weights=[0]*26)
        yield Case('aaaa','aaaa',weights=[10**9]*26)
    if code==250:
        yield Case('abx','aby','xcd')
        yield Case('xxabc','abczz','qabcq')
    if code==251:
        for a,b in [('a','a'),('ab','ba'),('ab','ab'),('aaaa','aaaa'),('abxcd','abycd')]:yield Case(a,b)


def assert_reproducible(problem):
    for test in problem.config['tests']:
        if test['name'].endswith('.cpp'):
            exe=problem.basedir/'gen'/Path(test['name']).stem
            for seed in range(test['number']):
                expected=(problem.basedir/'in'/f'{exe.name}_{seed:02}.in').read_text().strip()
                assert run(exe,'',seed)[0]==expected


def audit_formulas(code,c,answer):
    if code in (230,252,232) and len(set(c.a+c.b))==1:
        n,m=len(c.a),len(c.b)
        if code==232:
            expected=sum((n-length+1)*(m-length+1) for length in range(1,min(n,m)+1))
        else:expected=min(n,m)*max(0,c.weights[ord(c.a[0])-97])
        assert answer==str(expected),(code,'closed form',answer,expected)
        return True
    return False


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR)
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem]
    sources=[ORACLE.with_suffix('.cpp')]
    for problem in problems:
        code=int(problem.basedir.name[6:])
        problem.health_check();problem.generate_params_h();audit_config(problem,code)
        sources+=[problem.get_correct_filename(),problem.checker,problem.verifier]
        sources+=[problem.basedir/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp')]
    print(f'Compiling {len(sources)} sources for {len(problems)} problems...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source,sources):pass
    report=[]
    for problem in problems:
        p=problem.basedir;code=int(p.name[6:]);started=time.monotonic()
        audit_statement(p,code)
        problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
        assert problem.check_all_solutions_used()
        maximum=False;wide=False;full_k=False;worst=0;worst_name='';brutes=0;formulas=0
        for path in sorted((p/'in').glob('*.in')):
            data=path.read_text();c=decode(code,data);expected=(p/'out'/path.with_suffix('.out').name).read_text().strip()
            actual,elapsed=run(p/'sol/correct',data,timeout=problem.config['timelimit'])
            assert actual==expected,(path,'correct solution')
            if elapsed>worst:worst=elapsed;worst_name=path.name
            assert run(ORACLE,data,code)[0]==expected,(path,'independent oracle')
            if path.stem.startswith(('example','edge','small','regression')):
                assert brute(code,c)==expected,(path,'brute force');brutes+=1
            formulas+=audit_formulas(code,c,expected)
            large=len(c.a)==len(c.b)==LIMITS[code] and (code!=250 or len(c.d)==LIMITS[code])
            maximum|=large;full_k|=large and c.k==5
            wide|=int(expected.split()[0])>2**31-1
        assert maximum,(code,'maximum lengths')
        if code in (231,252):assert full_k
        if code in (230,232,252):assert wide,(code,'64-bit answer')
        count=0
        for c in itertools.chain(exhaustive_cases(code),random_cases(code),targeted_cases(code)):
            data=encode(code,c);expected=brute(code,c)
            assert run(p/'sol/correct',data)[0]==expected,(p,data,'C++ disagrees with brute')
            assert run(ORACLE,data,code)[0]==expected,(p,data,'oracle disagrees with brute')
            count+=1
        sample=(p/'gen/example_00.in').read_text()
        audit_verifier(p,code,sample);audit_checker(p,sample,brute(code,decode(code,sample)))
        if code==230:
            data=(p/'in/regression_00.in').read_text()
            c=decode(code,data)
            assert c.a==c.b=='ab' and c.weights[:2]==[-3,5]
            # Omitting max(0, ...) incorrectly carries the negative first character.
            wrong_dp=[0]*(len(c.b)+1);wrong=0
            for x in c.a:
                for j in range(len(c.b),0,-1):
                    wrong_dp[j]=wrong_dp[j-1]+c.weights[ord(x)-97] if x==c.b[j-1] else 0
                    wrong=max(wrong,wrong_dp[j])
            assert wrong==2 and brute(code,c)=='5'
            audit_checker(p,data,'5',extra_wrong=[wrong])
        if code in (230,232,252):
            path=p/'in/max_01.in';data=path.read_text()
            audit_checker(p,data,(p/'out/max_01.out').read_text().strip())
        assert_reproducible(problem)
        if args.update_hashes:(p/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
        problem.assert_hashes()
        pairs=sum(test['number'] for test in problem.config['tests'])
        report.append(dict(code=p.name,pairs=pairs,generated_brute=brutes,additional_brute=count,formulas=formulas,
                           slowest_seconds=round(worst,4),slowest_test=worst_name))
        print(f'{p.name}: {pairs} pairs; {brutes} generated + {count} additional brute checks; '
              f'oracle, checker, verifier, metadata, reproducibility and hashes OK; '
              f'slowest {worst:.3f}s ({worst_name}); total {time.monotonic()-started:.1f}s.',flush=True)
    lines=['# Kết quả kiểm tra DPCSTR2xx','',
           'Chạy trên máy cục bộ; lời giải C++11, giới hạn mỗi test 0,5 giây. Không xuất HTML hoặc upload.','',
           '| Mã | Cặp test | Vét cạn test đã sinh | Vét cạn bổ sung | Chậm nhất (giây) | Test chậm nhất |',
           '| --- | --- | --- | --- | --- | --- |']
    for item in report:
        lines.append(f'| {item["code"]} | {item["pairs"]} | {item["generated_brute"]} | '
                     f'{item["additional_brute"]} | {item["slowest_seconds"]:.4f} | {item["slowest_test"]} |')
    lines+=['',f'Tổng: {sum(x["pairs"] for x in report)} cặp test, '
            f'{sum(x["generated_brute"] for x in report)} lượt vét cạn trên dữ liệu đã sinh và '
            f'{sum(x["additional_brute"] for x in report)} trường hợp vét cạn bổ sung.','',
            'Oracle độc lập, checker, verifier, cấu hình upload, cấu trúc đề, tính tái lập và mã băm đều hợp lệ.']
    report_path=Path(__file__).with_name('results.md') if len(problems)==len(CODES) else problems[0].basedir/'tests/results.md'
    report_path.write_text('\n'.join(lines)+'\n')
    print('All checks passed. No HTML or uploads.',flush=True)


if __name__=='__main__':main()
