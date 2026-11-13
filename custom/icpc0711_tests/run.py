#!/usr/bin/env python3
"""Rebuild, validate and check ICPC0711 A–L without HTML export."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import shutil
import subprocess
import sys
import tempfile
import time
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from problem import Problem

def execute(exe,data,timeout=1):
    result=subprocess.run([str(exe)],input=data,text=True,capture_output=True,timeout=timeout)
    assert result.returncode==0,(exe,result.stderr)
    return result.stdout

def main():
    parser=argparse.ArgumentParser()
    parser.add_argument('--update-hashes',action='store_true')
    parser.add_argument('--letters',default='abcdefghijkl')
    parser.add_argument('--reuse-build',action='store_true',help='Reuse binaries newer than all local/common C++ sources')
    args=parser.parse_args()
    cxx=os.environ.get('CXX') or shutil.which('g++-16') or shutil.which('g++')
    report=[]
    report_path=ROOT/'custom/icpc0711_tests/results.md'
    previous={}
    if report_path.exists():
        previous={c.lower():(c.lower(),int(num),float(t)) for c,num,t in re.findall(r'\| ICPC0711([A-L]) \| (\d+) \| ([0-9.]+) \|',report_path.read_text())}
    for c in args.letters:
        base=ROOT/'custom'/f'icpc0711{c}'
        p=Problem(ROOT,base);p.health_check();p.generate_params_h()
        newest_source=max(x.stat().st_mtime for folder in [base,ROOT/'common'] for x in folder.rglob('*') if x.is_file() and x.name!='params.h' and x.suffix in ['.cpp','.h','.hpp','.toml'])
        for src in [base/'sol/correct.cpp',base/'verifier.cpp',base/'checker.cpp',base/'gen/cases.cpp']:
            if args.reuse_build and src.with_suffix('').exists() and src.with_suffix('').stat().st_mtime>=newest_source:
                continue
            subprocess.run([cxx,'-std=c++17','-O2','-Wall','-Wextra','-Werror','-I',str(ROOT/'common'),str(src),'-o',str(src.with_suffix(''))],check=True)
        p.make_inputs();p.verify_inputs()
        (base/'out').mkdir(exist_ok=True)
        times=[]
        for inp in sorted((base/'in').glob('*.in')):
            start=time.perf_counter();out=execute(base/'sol/correct',inp.read_text());times.append(time.perf_counter()-start)
            target=base/'out'/f'{inp.stem}.out';target.write_text(out)
            subprocess.run([str(base/'checker'),str(inp),str(target),str(target)],check=True,capture_output=True)
        task=(base/'task.md').read_text()
        samples=re.findall(r'### Sample Input \d+\n\n```text\n(.*?)```\n\n### Sample Output \d+\n\n```text\n(.*?)```',task,re.S)
        for i,(si,so) in enumerate(samples):
            assert si==(base/'gen'/f'example_{i:02}.in').read_text()
            assert so.split()==(base/'out'/f'example_{i:02}.out').read_text().split(),(c,i)
        headings=['### Đề bài','### Dữ liệu vào','### Dữ liệu ra','### Ràng buộc']
        for i in range(1,len(samples)+1):headings.extend([f'### Sample Input {i}',f'### Sample Output {i}'])
        headings+=['### Giải thích']
        assert [x for x in task.splitlines() if x.startswith('### ')]==headings
        assert task.splitlines()[0].startswith(f'# ICPC0711{c.upper()} — ')
        assert '### Subtask' not in task and task.count('```text')==2*len(samples)
        solution=(base/'solution.md').read_text()
        assert not any(line.startswith('# ') for line in solution.splitlines())
        assert '```' not in solution and 'Mã tham khảo' not in solution
        assert p.config['timelimit']==p.config['upload']['time_limit']==1.0
        # Every checker must reject wrong, truncated and extra answers.
        with tempfile.TemporaryDirectory() as tmp:
            inp=base/'in/example_00.in';ans=base/'out/example_00.out';bad=Path(tmp)/'bad.out'
            for output in ['',ans.read_text()+' 999999\n','999999999999999999999999999999999\n']:
                bad.write_text(output)
                assert subprocess.run([str(base/'checker'),str(inp),str(bad),str(ans)],capture_output=True).returncode!=0
        hashes=p.calc_hashes()
        if args.update_hashes:(base/'hash.json').write_text(json.dumps(hashes,indent=2,sort_keys=True)+'\n')
        p.assert_hashes()
        report.append((c,len(times),max(times)))
        print(f'{c.upper()}: {len(times)} cases PASS, max {max(times):.3f}s',flush=True)
    previous.update({row[0]:row for row in report})
    report=sorted(previous.values())
    report_path.write_text('## Kết quả kiểm thử\n\nGiới hạn mỗi lần chạy: 1.0 giây. Thời gian dưới đây đo trên máy hiện tại, bao gồm khởi chạy tiến trình.\n\n| Bài | Số test | Thời gian lớn nhất (giây) |\n| --- | ---: | ---: |\n'+''.join(f'| ICPC0711{c.upper()} | {num} | {t:.3f} |\n' for c,num,t in report))
if __name__=='__main__':main()
