"""Generate and audit the K-string subsequence problem, without HTML or uploads."""
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


def encode(strings):
    return str(len(strings))+'\n'+'\n'.join(strings)+'\n'


def decode(data):
    words=data.split()
    assert len(words)==int(words[0])+1
    return words[1:]


def subsequence(word,s):
    it=iter(s)
    return all(c in it for c in word)


def brute(strings):
    base=min(strings,key=len)
    candidates={''.join(base[i] for i in range(len(base)) if mask>>i&1) for mask in range(1<<len(base))}
    return max(len(word) for word in candidates if all(subsequence(word,s) for s in strings))


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
    expected.append('### Giải thích')
    assert heads[0].startswith('# DPSTR153 — ') and heads[1:]==expected
    blocks=re.findall(r'```text\n(.*?)\n```',text,re.S)
    assert len(blocks)==6
    for i in range(3):
        data=(P/'gen'/f'example_{i:02}.in').read_text()
        assert blocks[2*i]+'\n'==data
        assert blocks[2*i+1]==str(brute(decode(data)))
    solution=(P/'solution.md').read_text()
    assert 'Đảo biến' in solution
    assert not re.search(r'kiểm thử|bộ sinh|oracle|verifier|checker|benchmark|chạy test',solution,re.I)
    assert not list(P.glob('*.html'))


def audit_config(problem):
    config=problem.config
    assert config['timelimit']==1.0
    assert config['params']==dict(K_MIN=2,K_MAX=40,TOTAL_MAX=100000,SHORT_MAX=20)
    assert config['upload']==dict(time_limit=1.0,group='03',classes='C',types=['dp_string','dp_common_substring'],
                                 allowed_languages=['PY3','CPP11','CPP14','CPP17','CPP20','JAVA8','C','PAS'],partial=True)
    assert sum(test['number'] for test in config['tests'])==35
    assert ProblemUpload(problem).manifest['checker']=='standard'
    assert 26*100000+39*2**20+2*2**20<50_000_000


def audit_verifier():
    invalid=['','1\na\n','41\n'+'a\n'*41,'2\na\n','2\na\nb\n0\n',
             '2\n\na\n','2\nA\na\n','2\na#\na\n',encode(['a'*21,'b'*21]),
             encode(['a'*100000,'a']),encode(['a'*100001,'a'])]
    for data in invalid:
        result=subprocess.run([str(P/'verifier')],input=data,text=True,capture_output=True)
        assert result.returncode!=0,('accepted invalid input',data[:100])
    for strings in [['a','a'],['z'*99980,'a'*20],['a'*20]*40]:
        result=subprocess.run([str(P/'verifier')],input=encode(strings),text=True,capture_output=True)
        assert result.returncode==0,result.stderr


def audit_checker(strings,answer):
    data=encode(strings)
    outputs=[(str(answer)+'\n',True),(' \n'+str(answer)+' \n',True),('',False),('x\n',False),
             (str(answer)+' 0\n',False),('-1\n',False),('21\n',False),
             (str((answer+1)%21)+'\n',False)]
    with tempfile.TemporaryDirectory() as directory:
        inp,ans,out=[Path(directory)/name for name in ['in','ans','out']]
        inp.write_text(data);ans.write_text(str(answer)+'\n')
        for output,valid in outputs:
            out.write_text(output)
            result=subprocess.run([str(P/'checker'),str(inp),str(out),str(ans)],capture_output=True)
            assert (result.returncode==0)==valid,(output,result.stderr)


def random_cases():
    rng=random.Random(20261101+153)
    for _ in range(120):
        strings=[''.join(rng.choice('abcx') for _ in range(rng.randint(1,9))) for _ in range(rng.randint(2,6))]
        yield strings
        if len(strings)>2:
            yield strings[::-1]


def exhaustive_cases():
    words=[''.join(bits) for n in range(1,4) for bits in itertools.product('ab',repeat=n)]
    yield from (list(strings) for strings in itertools.product(words,repeat=2))
    yield from (list(strings) for strings in itertools.product(words,repeat=3))


def targeted_cases():
    yield ['ab','ba','a'];yield ['ab','ba','b'];yield ['aa','a','aa']
    yield ['ab','bc','ca'];yield ['abc','acb','bac']
    yield ['xaybzc','abc','qabrc'];yield ['abcde','acebd','azced']
    for position in range(4):
        strings=['aabbcc','abcabc','cababc']
        strings.insert(position,'abc')
        yield strings


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
    print(f'Compiling {len(sources)} sources for DPSTR153...',flush=True)
    with ThreadPoolExecutor(max_workers=4) as pool:
        for _ in pool.map(compile_source,sources):pass
    problem.make_inputs();problem.verify_inputs();problem.make_outputs(True)
    assert problem.check_all_solutions_used()
    brutes=0;count=0;worst=(0,'');maximum_k=False;maximum_total=False;maximum_short=False
    max_answers=[20,20,1,0,10,20]
    for path in sorted((P/'in').glob('*.in')):
        data=path.read_text();strings=decode(data)
        expected=(P/'out'/path.with_suffix('.out').name).read_text().strip()
        actual,elapsed=run(P/'sol/correct',data,timeout=problem.config['timelimit'])
        assert actual==expected,(path,'correct solution')
        if elapsed>worst[0]:worst=(elapsed,path.name)
        assert run(P/'tests/oracle',data)[0]==expected,(path,'independent oracle')
        if path.stem.startswith(('example','edge','small')):
            assert brute(strings)==int(expected),(path,'brute force');brutes+=1
        if path.stem.startswith('max'):
            assert int(expected)==max_answers[int(path.stem[-2:])],path
        maximum_k|=len(strings)==40
        maximum_total|=sum(map(len,strings))==100000
        maximum_short|=min(map(len,strings))==20
    assert maximum_k and maximum_total and maximum_short
    for strings in itertools.chain(exhaustive_cases(),random_cases(),targeted_cases()):
        data=encode(strings);expected=str(brute(strings))
        assert run(P/'sol/correct',data)[0]==expected,(strings,'correct vs brute')
        assert run(P/'tests/oracle',data)[0]==expected,(strings,'oracle vs brute')
        count+=1
    audit_verifier()
    for strings,answer in [(['a','a'],1),(['a','b'],0),(['a'*20]*40,20),(['aa','a','aa'],1)]:
        audit_checker(strings,answer)
    assert_reproducible(problem)
    if args.update_hashes:(P/'hash.json').write_text(json.dumps(problem.calc_hashes(),indent=2,sort_keys=True)+'\n')
    problem.assert_hashes()
    print(f'DPSTR153: 35 pairs; {brutes} generated and {count} additional brute checks; '
          f'oracle, verifier, checker, metadata, reproducibility and hashes OK; '
          f'slowest {worst[0]:.3f}s ({worst[1]}).',flush=True)
    (P/'tests/results.md').write_text(f'# Kết quả kiểm tra DPSTR153\n\n'
        f'35 cặp test, {brutes} lượt vét cạn trên dữ liệu đã sinh và {count} trường hợp bổ sung đều đạt. '
        f'Lời giải C++11 được chạy với giới hạn 1 giây mỗi test; chậm nhất {worst[0]:.4f} giây ở `{worst[1]}` trên máy cục bộ.\n\n'
        'Oracle độc lập, verifier, checker, cấu trúc đề, cấu hình upload, test ở cận tối đa, tính tái lập và mã băm đều hợp lệ. '
        'Không xuất HTML hoặc upload.\n')


if __name__=='__main__':main()
