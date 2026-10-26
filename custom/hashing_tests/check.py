"""Build, generate and independently verify HASHING000--009, without HTML."""
import argparse
from concurrent.futures import ThreadPoolExecutor
import itertools
import logging
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile
import time

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT))
from problem import Problem
NAMES = [f'hashing{k:03}' for k in range(10)]
ORACLE = HERE / 'oracle'


def run(exe, data, *args, timeout=30):
    result = subprocess.run([str(exe), *map(str, args)], input=data, text=True,
                            capture_output=True, timeout=timeout)
    if result.returncode:
        raise AssertionError((str(exe), result.returncode, result.stderr[:3000], data[:2000]))
    return result.stdout


def compile_one(source):
    command = ['g++', '-std=c++17', '-O2', '-Wall', '-Wextra', '-Werror',
               '-I', str(ROOT/'common'), '-I', str(ROOT/'atcoder'),
               str(source), '-o', str(source.with_suffix(''))]
    subprocess.run(command, check=True, capture_output=True, text=True)


def brute(k, data):
    lines = data.splitlines()
    h = list(map(int, lines[0].split()))
    if k == 0:
        n, count = h; s = lines[1]
        from collections import Counter
        return [str(max([0]+[d for d in range(1,n+1) if max(Counter(s[i:i+d] for i in range(n-d+1)).values())>=count]))]
    if k == 1:
        n,m=h; a=list(map(int,lines[1].split()));b=list(map(int,lines[2].split()))
        return [str(sum(all(a[i+j]-b[j]==a[i]-b[0] for j in range(m)) for i in range(n-m+1)))]
    if k == 2:
        n=h[0];s=lines[1];answer=0
        for i in range(n):
            for j in range(i+1,n):
                d=0
                while i+d<j and j+d<n and s[i+d]==s[j+d]:d+=1
                answer=max(answer,d)
        return [str(answer)]
    if k == 3:
        n,m=h;s,p=lines[1:3]
        return [str(sum(sum(a!=b for a,b in zip(s[i:i+m],p))==1 for i in range(n-m+1)))]
    if k == 4:
        s=lines[1];out=[]
        for line in lines[2:]:
            l,r,u,v=map(int,line.split());a,b=s[l-1:r],s[u-1:v]
            out.append('<' if a<b else '>' if a>b else '=')
        return out
    if k == 5:
        ss=lines[1:];s=min(ss,key=len)
        return [str(max([0]+[d for d in range(1,len(s)+1) if any(all(s[i:i+d] in t for t in ss) for i in range(len(s)-d+1))]))]
    if k == 6:
        return [str(len({min(s[i:]+s[:i] for i in range(len(s))) for s in lines[1:]}))]
    if k == 7:
        r,c,q=h;grid=lines[1:1+r];out=[]
        for line in lines[1+r:]:
            x,y,u,v,d=map(int,line.split());x-=1;y-=1;u-=1;v-=1
            a=tuple(row[y:y+d] for row in grid[x:x+d]);b=tuple(row[v:v+d] for row in grid[u:u+d]);ok=False
            for _ in range(4):
                ok|=a==b;b=tuple(''.join(row) for row in zip(*b[::-1]))
            out.append('YES' if ok else 'NO')
        return out
    if k == 8:
        s=list(lines[1]);out=[]
        for line in lines[2:]:
            t,a,b=line.split();a=int(a)-1
            if t=='1':s[a]=b
            else:
                part=s[a:int(b)];out.append('YES' if part==part[::-1] else 'NO')
        return out
    if k == 9:
        n,q=h;s=lines[1];g=[[] for _ in range(n)]
        for line in lines[2:n+1]:
            a,b=map(int,line.split());g[a-1].append(b-1);g[b-1].append(a-1)
        def path(u,v):
            parent=[-1]*n;parent[u]=u;queue=[u]
            for x in queue:
                if x==v:break
                for y in g[x]:
                    if parent[y]==-1:parent[y]=x;queue.append(y)
            out=[]
            while v!=u:out.append(s[v]);v=parent[v]
            out.append(s[u]);return ''.join(out[::-1])
        out=[]
        for line in lines[n+1:]:
            u,v,x,y=(int(t)-1 for t in line.split());out.append('YES' if path(u,v)==path(x,y) else 'NO')
        return out
    raise ValueError(k)


def case(p,k,data,expected=None):
    run(p/'verifier',data)
    want=brute(k,data)
    if expected is not None:assert want==list(map(str,expected)),(p,'brute',data,want,expected)
    got=run(p/'sol/correct',data).split()
    assert got==want,(p,'solution',data,want,got)
    got=run(ORACLE,data,k).split()
    assert got==want,(p,'independent oracle',data,want,got)


def encode(k,s,ops=(),extra=None):
    if k==0:return f'{len(s)} {extra}\n{s}\n'
    if k==1:return f'{len(s)} {len(extra)}\n'+ ' '.join(map(str,s))+'\n'+' '.join(map(str,extra))+'\n'
    if k==2:return f'{len(s)}\n{s}\n'
    if k==3:return f'{len(s)} {len(extra)}\n{s}\n{extra}\n'
    if k==5:return f'{len(s)}\n'+'\n'.join(s)+'\n'
    if k==6:return f'{len(s)} {len(s[0])}\n'+'\n'.join(s)+'\n'
    if k==7:head=f'{len(s)} {len(s[0])} {len(ops)}\n'+'\n'.join(s)+'\n'
    else:head=f'{len(s)} {len(ops)}\n{s}\n'
    if k==9:head+=''.join(f'{u} {v}\n' for u,v in extra)
    return head+''.join(' '.join(map(str,op))+'\n' for op in ops)


def intervals(n):return [(l,r) for l in range(1,n+1) for r in range(l,n+1)]


def small_checks(p,k):
    count=0
    def check(data,expected=None):
        nonlocal count
        case(p,k,data,expected);count+=1
    if k in (0,2):
        for n in range(1,7):
            for a in itertools.product('ab',repeat=n):
                s=''.join(a)
                for c in (range(1,n+1) if k==0 else [None]):check(encode(k,s,extra=c))
    if k==1:
        seq=[a for n in range(1,4) for a in itertools.product([-1,0,1],repeat=n)]
        for a in seq:
            for b in seq:check(encode(k,a,extra=b))
        for a,b in [([-10**9,10**9,-10**9],[-10**9,10**9]),([10**9,-10**9],[10**9,-10**9]),([0],[10**9]),([1,2],[1,2,3])]:check(encode(k,a,extra=b))
    if k==3:
        seq=[''.join(a) for n in range(1,5) for a in itertools.product('ab',repeat=n)]
        for a in seq:
            for b in seq:check(encode(k,a,extra=b))
    if k==4:
        for n in range(1,6):
            ops=[a+b for a in intervals(n) for b in intervals(n)]
            for a in itertools.product('ab',repeat=n):check(encode(k,''.join(a),ops))
    if k==5:
        seq=[''.join(a) for n in range(1,4) for a in itertools.product('ab',repeat=n)]
        for a in seq:
            check(encode(k,[a]))
            for b in seq:check(encode(k,[a,b]))
        for ss in [['abc','bc','c'],['banana','ananas','bandana'],['a','a','b'],['aaaa','aa','aaa']]:check(encode(k,ss))
    if k==6:
        for m in range(1,5):
            seq=[''.join(a) for a in itertools.product('ab',repeat=m)]
            for a in seq:
                for b in seq:check(encode(k,[a,b]))
        check(encode(k,['abc','bca','cab','acb','cba','bac']),['2'])
    if k==7:
        seq=[''.join(a) for a in itertools.product('ab',repeat=4)]
        for a in seq:
            for b in seq:
                grid=[a[:2]+b[:2],a[2:]+b[2:]]
                check(encode(k,grid,[(1,1,1,3,2),(1,3,1,1,2),(1,1,1,2,2),(1,1,2,4,1)]))
        # Four asymmetric turns must pass; a reflection must fail.
        for b in [('ab','cd'),('ca','db'),('dc','ba'),('bd','ac')]:check(encode(k,['ab'+b[0],'cd'+b[1]],[(1,1,1,3,2)]),['YES'])
        check(encode(k,['abac','cdbd'],[(1,1,1,3,2)]),['NO'])
    if k==8:
        for n in range(1,6):
            for chars in itertools.product('ab',repeat=n):
                ops=[(2,l,r) for l,r in intervals(n)]
                for i in range(1,n+1):
                    for c in 'abz':ops.append((1,i,c));ops.extend((2,l,r) for l,r in intervals(n))
                check(encode(k,''.join(chars),ops))
        check(encode(k,'abc',[(1,1,'z'),(1,3,'a')]),[])
    if k==9:
        for n in range(1,5):
            # Every labelled tree via Prüfer sequences, with every binary labelling through n=3.
            sequences=itertools.product(range(1,n+1),repeat=max(0,n-2))
            for seq in sequences:
                degree=[0]+[1]*n
                for x in seq:degree[x]+=1
                edges=[]
                for x in seq:
                    y=next(v for v in range(1,n+1) if degree[v]==1);edges.append((x,y));degree[x]-=1;degree[y]-=1
                left=[v for v in range(1,n+1) if degree[v]==1]
                if len(left)==2:edges.append(tuple(left))
                chars=itertools.product('ab',repeat=n) if n<=3 else [tuple('abca'),tuple('aaaa')]
                ops=list(itertools.product(range(1,n+1),repeat=4))
                for a in chars:check(encode(k,''.join(a),ops,edges))
    rng=random.Random(20261022+k)
    for _ in range(100):
        n=rng.randint(1,30);s=''.join(rng.choices('abcxyz',k=n));m=rng.randint(1,35)
        if k==0:data=encode(k,s,extra=rng.randint(1,n))
        elif k==1:data=encode(k,rng.choices([-10**9,-7,0,7,10**9],k=n),extra=rng.choices([-10**9,-7,0,7,10**9],k=m))
        elif k==2:data=encode(k,s)
        elif k==3:data=encode(k,s,extra=''.join(rng.choices('abcxyz',k=m)))
        elif k==4:data=encode(k,s,[tuple(sorted(rng.choices(range(1,n+1),k=2)))+tuple(sorted(rng.choices(range(1,n+1),k=2))) for _ in range(80)])
        elif k==5:data=encode(k,[''.join(rng.choices('abc',k=rng.randint(1,20))) for _ in range(rng.randint(1,8))])
        elif k==6:data=encode(k,[''.join(rng.choices('abc',k=n)) for _ in range(rng.randint(1,10))])
        elif k==7:
            r,c=rng.randint(1,7),rng.randint(1,8);grid=[''.join(rng.choices('abc',k=c)) for _ in range(r)];ops=[]
            for _ in range(80):
                d=rng.randint(1,min(r,c));ops.append((rng.randint(1,r-d+1),rng.randint(1,c-d+1),rng.randint(1,r-d+1),rng.randint(1,c-d+1),d))
            data=encode(k,grid,ops)
        elif k==8:
            ops=[]
            for _ in range(80):
                if rng.randrange(2):ops.append((1,rng.randint(1,n),rng.choice('abcxyz')))
                else:ops.append((2,*sorted(rng.choices(range(1,n+1),k=2))))
            data=encode(k,s,ops)
        else:
            edges=[(i,rng.randint(1,i-1)) for i in range(2,n+1)];rng.shuffle(edges)
            ops=[tuple(rng.choices(range(1,n+1),k=4)) for _ in range(80)]
            data=encode(k,s,ops,edges)
        check(data)
    return count


def invalid_checks(p,k):
    sample=(p/'gen/example_00.in').read_text();lines=sample.splitlines()
    bad=[sample+'0\n','\n'.join(lines[:-1])+'\n',sample.replace(lines[0], '0'+(' '+ ' '.join(lines[0].split()[1:]) if len(lines[0].split())>1 else ''),1)]
    if k in (0,2,3,4,8,9):bad.extend([sample.replace(lines[1],'A'+lines[1][1:],1),sample.replace(lines[1],lines[1]+'a',1)])
    if k==0:bad.extend(['1 0\na\n','1 2\na\n','200001 1\na\n'])
    if k==1:bad.extend(['1 1\n1000000001\n0\n','1 1\n0\n-1000000001\n','1 0\n0\n\n'])
    if k==3:bad.append('1 1\na\naa\n')
    if k==4:bad.extend(encode(k,'abc',[op]) for op in [(0,1,1,1),(1,4,1,1),(2,1,1,1),(1,1,0,1),(1,1,2,1)])
    if k==5:bad.extend(['1\n\n','2\na\nA\n',encode(k,['a'*200001])])
    if k==6:bad.extend(['2 2\naa\na\n','1 1\nA\n',encode(k,['a'*100001]*2)])
    if k==7:
        bad.extend(encode(k,['ab','cd'],[op]) for op in [(1,1,1,1,0),(1,1,1,1,3),(2,1,1,1,2),(1,2,1,1,2),(1,1,2,1,2),(1,1,1,2,2)])
        bad.extend(['1001 1 1\n','1 1001 1\n','1 1 1\nA\n1 1 1 1 1\n'])
    if k==8:bad.extend(encode(k,'abc',[op]) for op in [(0,1,1),(3,1,1),(1,0,'a'),(1,4,'a'),(1,1,'aa'),(1,1,'A'),(2,2,1),(2,1,4)])
    if k==9:
        bad.extend([encode(k,'abc',[(1,1,1,1)],[(1,2),(2,1)]),encode(k,'abc',[(1,1,1,1)],[(1,1),(2,3)]),encode(k,'abc',[(0,1,1,1)],[(1,2),(2,3)])])
    if k in (4,7,8,9):
        h=list(map(int,lines[0].split()));h[-1]=200001;bad.append(' '.join(map(str,h))+'\n'+'\n'.join(lines[1:])+'\n')
    for data in bad:
        result=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,(p,'accepted invalid input',data[:1000])
    return len(bad)


def checker_checks(p):
    def check(infile,answer):
        count=0
        with tempfile.TemporaryDirectory() as folder:
            folder=Path(folder);ans=folder/'answer';out=folder/'actual';ans.write_text(answer)
            variants=[(answer,True),(' \n'+'  \n'.join(answer.split())+'\n',True),(answer+' EXTRA\n',False)]
            if answer.split():
                tokens=answer.split();wrong=tokens.copy();wrong[0]='WRONG'
                variants.extend([('',False),(' '.join(wrong)+'\n',False),(' '.join(tokens[:-1])+'\n',False)])
            else:variants.append(('YES\n',False))
            for text,accepted in variants:
                out.write_text(text)
                result=subprocess.run([str(p/'checker'),str(infile),str(out),str(ans)],capture_output=True,text=True)
                assert (result.returncode==0)==accepted,(p,'checker',text,accepted,result.stderr)
                count+=1
        return count
    count=check(p/'in/example_00.in',(p/'out/example_00.out').read_text())
    if p.name=='hashing008':count+=check(p/'in/edge_09.in','')
    return count


def audit_statement(p):
    text=(p/'task.md').read_text()
    assert text.startswith(f'# {p.name.upper()} — ')
    expected=['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc','Sample Input 1','Sample Output 1','Sample Input 2','Sample Output 2','Giải thích']
    assert re.findall(r'^### (.+)$',text,re.M)==expected
    assert len(re.findall(r'^#+ ',text,re.M))==len(expected)+1
    for i in range(2):
        for label,folder,ext in [('Input','in','in'),('Output','out','out')]:
            found=re.search(rf'### Sample {label} {i+1}\n\n```text\n(.*?)```',text,re.S)
            assert found and found[1]==(p/f'{folder}/example_{i:02}.{ext}').read_text(),(p,label,i)
    assert not list(p.rglob('*.html'))
    for path in p.glob('*.md'):assert all(c>=32 or c in (9,10) for c in path.read_bytes()),path


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--problem',nargs='+',choices=NAMES,default=NAMES)
    parser.add_argument('--update-hashes',action='store_true')
    parser.add_argument('--skip-compile',action='store_true',help='Reuse existing binaries while developing')
    args=parser.parse_args();logging.basicConfig(level=logging.ERROR)
    problems=[Problem(ROOT,ROOT/'custom'/name) for name in args.problem]
    sources=[HERE/'oracle.cpp']
    for problem in problems:
        problem.health_check();problem.generate_params_h()
        sources.extend(problem.basedir.rglob('*.cpp'))
    if not args.skip_compile:
        print(f'Compiling {len(sources)} sources...',flush=True)
        with ThreadPoolExecutor(max_workers=4) as pool:
            for _ in pool.map(compile_one,sources):pass
    total=0;summary=[]
    for problem in problems:
        started=time.monotonic();p=problem.basedir;k=int(p.name[-3:])
        problem.make_inputs();problem.verify_inputs();problem.make_outputs(True);problem.judge(p/'sol/correct.cpp',{})
        assert problem.check_all_solutions_used()
        files=sorted((p/'in').glob('*.in'));assert len(files)==30
        audit_statement(p)
        for test in problem.config['tests']:
            if not test['name'].endswith('.cpp'):continue
            exe=p/'gen'/Path(test['name']).stem
            for seed in range(test['number']):assert run(exe,'',seed)==(p/'in'/f'{exe.name}_{seed:02}.in').read_text(),(p,'reproducibility',seed)
        worst=0
        for path in files:
            data=path.read_text();want=(p/'out'/path.with_suffix('.out').name).read_text().split()
            begin=time.monotonic();got=run(p/'sol/correct',data,timeout=problem.config['timelimit']).split();worst=max(worst,time.monotonic()-begin)
            assert got==want,(path,'repeat solution')
            assert run(ORACLE,data,k).split()==want,(path,'independent oracle')
            if path.stem.startswith(('edge','small','example')):assert brute(k,data)==want,(path,'brute')
        count=small_checks(p,k);total+=count
        invalid=invalid_checks(p,k);checker=checker_checks(p)
        if args.update_hashes:problem.ignore_warning=True;problem.write_hashes()
        problem.assert_hashes()
        elapsed=time.monotonic()-started
        row={'problem':p.name,'official_tests':len(files),'additional_cases':count,'invalid_inputs':invalid,'checker_checks':checker,'slowest_seconds':round(worst,3),'elapsed_seconds':round(elapsed,1)}
        summary.append(row)
        print(f'{p.name}: 30 tests, {count} exhaustive/random cases, {invalid} invalid inputs, {checker} checker probes; slowest {worst:.3f}s; hashes OK ({elapsed:.1f}s)',flush=True)
    print(f'PASS: {len(problems)*30} official tests, {total} additional cases. No HTML.',flush=True)
    # Keep a reviewable text report without timing-dependent hashes in problem folders.
    report=['# Kết quả kiểm thử bộ hashing','', '| Bài | Test chính thức | Ca đối chiếu thêm | Đầu vào sai bị từ chối | Kiểm tra checker | Thời gian chậm nhất |', '| --- | ---: | ---: | ---: | ---: | ---: |']
    report.extend(f"| {r['problem']} | {r['official_tests']} | {r['additional_cases']} | {r['invalid_inputs']} | {r['checker_checks']} | {r['slowest_seconds']:.3f} s |" for r in summary)
    report.extend(['','Mọi test chính thức đã qua verifier, lời giải, checker, đối chiếu lời giải độc lập và kiểm tra tái lập bộ sinh. Các test nhỏ được đối chiếu thêm bằng vét cạn trực tiếp. Thời gian đo trên máy chạy kiểm thử, đã bao gồm khởi động tiến trình.','', 'Đề đã được kiểm tra thứ tự heading và đối chiếu cả hai ví dụ với đầu vào/đầu ra thực tế; không có Subtask và không xuất HTML. Hash SHA-256 của mọi đầu vào/đầu ra đã được đối chiếu với `hash.json`.',''])
    if len(problems)==10:(HERE/'REPORT.md').write_text('\n'.join(report))


if __name__=='__main__':main()
