"""Generate and audit the asymmetric LCS problem, without HTML or uploads."""
import argparse
from concurrent.futures import ThreadPoolExecutor
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

HERE=Path(__file__).resolve()
P=HERE.parents[1]
ROOT=HERE.parents[3]
sys.path.insert(0,str(ROOT))
from problem import Problem
from problem_upload import ProblemUpload


def encode(a,b):return f'{len(a)} {len(b)}\n{a}\n{b}\n'


def decode(data):
    n,m,a,b=data.split()
    assert int(n)==len(a) and int(m)==len(b)
    return a,b


def subsequence(word,s):
    it=iter(s)
    return all(c in it for c in word)


def brute(a,b):
    if len(a)>len(b):a,b=b,a
    return max((mask.bit_count() for mask in range(1<<len(a))
                if subsequence(''.join(c for i,c in enumerate(a) if mask>>i&1),b)),default=0)


def dense(a,b):
    dp=[0]*(len(b)+1)
    for c in a:
        diagonal=0
        for j,d in enumerate(b,1):
            old=dp[j]
            dp[j]=diagonal+1 if c==d else max(dp[j],dp[j-1])
            diagonal=old
    return dp[-1]


def run(executable,data,timeout=5):
    start=time.perf_counter()
    result=subprocess.run([str(executable)],input=data,text=True,capture_output=True,timeout=timeout)
    elapsed=time.perf_counter()-start
    assert result.returncode==0,(executable,result.stderr)
    return result.stdout.strip(),elapsed


def compile_source(path):
    standard='c++11' if path.parent.name=='sol' else 'c++17'
    result=subprocess.run(['g++','-O2',f'-std={standard}','-Wall','-Wextra','-Werror','-Wno-unused-result',
                           '-I',str(ROOT/'common'),str(path),'-o',str(path.with_suffix(''))],capture_output=True,text=True)
    assert result.returncode==0,(path,result.stderr)


def audit_statement():
    text=(P/'task.md').read_text()
    heads=re.findall(r'^#{1,6} .+$',text,re.M)
    expected=['### Đề bài','### Dữ liệu vào','### Dữ liệu ra','### Ràng buộc']
    for i in range(1,4):expected.extend([f'### Sample Input {i}',f'### Sample Output {i}'])
    expected.extend(['### Giải thích','### Nguồn'])
    assert heads[0].startswith('# DPCSTR154 — ') and heads[1:]==expected
    blocks=re.findall(r'```text\n(.*?)\n```',text,re.S)
    assert len(blocks)==6
    for i in range(3):
        data=(P/'gen'/f'example_{i:02}.in').read_text()
        assert blocks[2*i]+'\n'==data
        assert blocks[2*i+1]==str(brute(*decode(data)))
    solution=(P/'solution.md').read_text()
    assert 'f[i][len]' in solution and 'Đảo biến' in solution
    assert not re.search(r'kiểm thử|bộ sinh|oracle|verifier|checker|benchmark|chạy test',solution,re.I)
    assert not list(P.glob('*.html'))


def audit_config(problem):
    config=problem.config
    assert config['timelimit']==0.5
    assert config['params']==dict(N_MAX=5000,M_MAX=1000000)
    assert config['upload']==dict(time_limit=0.5,memory_limit=131072,group='03',classes='C',
                                 types=['dp_common_substring'],
                                 allowed_languages=['PY3','CPP11','CPP14','CPP17','CPP20','JAVA8','C','PAS'],partial=True)
    assert sum(test['number'] for test in config['tests'])==37
    assert ProblemUpload(problem).manifest['checker']=='standard'
    assert 26*1000000+5000*5001//2<50_000_000
    # Explicit arrays, strings and DP fit in 128 MiB with room for normal runtime overhead.
    assert 26*(1000000+1)*4+(5000+1)*4+1005000<110*1024**2


def audit_verifier():
    invalid=['','0 1\n\na\n','5001 1\n'+'a'*5001+'\na\n',
             '1 1000001\na\n'+'a'*1000001+'\n','1 1\na\n','1 1\na\nb\n0\n',
             '1 1\nA\na\n','1 1\n#\na\n','1 1\na\naa\n','1 1\n\na\n']
    for data in invalid:
        result=subprocess.run([str(P/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,('accepted invalid input',data[:80])
    for a,b in [('a','a'),('a'*5000,'a'),('z','a'*1000000)]:
        result=subprocess.run([str(P/'verifier')],input=encode(a,b),text=True,capture_output=True)
        assert result.returncode==0,result.stderr


def audit_checker(a,b,answer,wrong=None):
    data=encode(a,b)
    other=(answer+1)%(min(len(a),len(b))+1)
    outputs=[(str(answer)+'\n',True),(' \n'+str(answer)+' \n',True),('',False),('x\n',False),
             (str(answer)+' 0\n',False),('-1\n',False),(str(min(len(a),len(b))+1)+'\n',False),
             (str(other)+'\n',False)]
    if wrong is not None:outputs.append((str(wrong)+'\n',False))
    with tempfile.TemporaryDirectory() as directory:
        inp,ans,out=[Path(directory)/name for name in ['in','ans','out']]
        inp.write_text(data);ans.write_text(str(answer)+'\n')
        for output,valid in outputs:
            out.write_text(output)
            result=subprocess.run([str(P/'checker'),str(inp),str(out),str(ans)],capture_output=True)
            assert (result.returncode==0)==valid,(output,result.stderr)


def random_cases():
    rng=random.Random(20261101+154)
    for _ in range(120):
        yield (''.join(rng.choice('abcxz') for _ in range(rng.randint(1,10))),
               ''.join(rng.choice('abcxz') for _ in range(rng.randint(1,20))))


def exhaustive_cases():
    words=[''.join(bits) for n in range(1,5) for bits in itertools.product('ab',repeat=n)]
    yield from itertools.product(words,repeat=2)


def boundary_cases():
    rng=random.Random(154)
    for n in [1,2,63,64,65,127,128,129,255,256,257,500]:
        a=''.join(rng.choice('abc') for _ in range(n))
        b=''.join(rng.choice('abc') for _ in range(700))
        yield a,b
        yield 'a'*n,'b'*100+'a'*min(n,70)


def assert_reproducible(problem):
    for test in problem.config['tests']:
        if not test['name'].endswith('.cpp'):continue
        for seed in range(test['number']):
            result=subprocess.run([str(P/'gen'/Path(test['name']).stem),str(seed)],capture_output=True,text=True,check=True)
            assert result.stdout==(P/'in'/f'{Path(test["name"]).stem}_{seed:02}.in').read_text()


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--update-hashes',action='store_true')
    args=parser.parse_args()
    logging.basicConfig(level=logging.ERROR)
    problem=Problem(ROOT,P)
    problem.health_check();problem.generate_params_h();audit_config(problem);audit_statement()
    sources=[P/'sol/correct.cpp',P/'verifier.cpp',P/'checker.cpp',P/'tests/oracle.cpp']
    sources+=[P/'gen'/test['name'] for test in problem.config['tests'] if test['name'].endswith('.cpp')]
    print(f'Compiling {len(sources)} sources for DPCSTR154...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source,sources):pass
    problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
    assert problem.check_all_solutions_used()
    brutes=0;count=0;worst=(0,'');maximum=False
    max_answers=[5000,5000,0,5000,2500,1,2,1]
    for path in sorted((P/'in').glob('*.in')):
        data=path.read_text();a,b=decode(data)
        expected=(P/'out'/path.with_suffix('.out').name).read_text().strip()
        actual,elapsed=run(P/'sol/correct',data,timeout=0.5)
        assert actual==expected,(path,'correct solution')
        if elapsed>worst[0]:worst=(elapsed,path.name)
        assert run(P/'tests/oracle',data)[0]==expected,(path,'bit-parallel oracle')
        if path.stem.startswith(('example','edge','small')):
            assert brute(a,b)==int(expected),(path,'brute force');brutes+=1
        if path.stem.startswith('max'):
            assert int(expected)==max_answers[int(path.stem[-2:])],path
        maximum|=len(a)==5000 and len(b)==1000000
    assert maximum
    for a,b in itertools.chain(exhaustive_cases(),random_cases()):
        data=encode(a,b);expected=str(brute(a,b))
        assert str(dense(a,b))==expected
        assert run(P/'sol/correct',data)[0]==expected,(a,b,'correct vs brute')
        assert run(P/'tests/oracle',data)[0]==expected,(a,b,'oracle vs brute')
        count+=1
    boundaries=0
    for a,b in boundary_cases():
        expected=str(dense(a,b));data=encode(a,b)
        assert run(P/'tests/oracle',data)[0]==expected,('oracle word boundary',len(a))
        assert run(P/'sol/correct',data)[0]==expected,('correct word boundary',len(a))
        boundaries+=1
    audit_verifier()
    for a,b,answer in [('a','a',1),('a','b',0),('ab','bb',1),('aa','ab',1),('a'*5000,'a'*5000,5000)]:
        audit_checker(a,b,answer,wrong=2 if (a,b) in [('ab','bb'),('aa','ab')] else None)
    assert_reproducible(problem)
    if args.update_hashes:(P/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
    problem.assert_hashes()
    print(f'DPCSTR154: 37 pairs; {brutes} generated and {count} additional brute checks; '
          f'{boundaries} dense-DP boundary checks; oracle, verifier, checker, metadata, '
          f'reproducibility and hashes OK; slowest {worst[0]:.3f}s ({worst[1]}).',flush=True)
    (P/'tests/results.md').write_text(f'# Kết quả kiểm tra DPCSTR154\n\n'
        f'37 cặp test, {brutes} lượt vét cạn trên dữ liệu đã sinh và {count} trường hợp vét cạn bổ sung đều đạt. '
        f'Có thêm {boundaries} trường hợp ở biên độ dài từ/khối bit được đối chiếu với DP LCS thông thường.\n\n'
        f'Lời giải C++11 được chạy với giới hạn 0,5 giây mỗi test; chậm nhất {worst[0]:.4f} giây ở `{worst[1]}` trên máy cục bộ. '
        'Oracle bit-parallel độc lập, verifier, checker, cấu trúc đề, cấu hình upload, các test cận lớn, tính tái lập và mã băm đều hợp lệ. '
        'Không xuất HTML hoặc upload.\n')


if __name__=='__main__':main()
