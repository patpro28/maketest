"""Generate, validate and independently check PREFIX00..09, without HTML."""
import argparse
from collections import Counter
from itertools import accumulate, product
import logging
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile

ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT))
from problem import Problem


def decode(k,text):
    t=list(map(int,text.split())); n=t[0]
    if k==9: return list(zip(t[1::2],t[2::2])),None
    off=2 if k in (0,7,8) else 1
    a=t[off:off+n]
    extra=list(zip(t[off+n::2],t[off+n+1::2])) if k==0 else t[1] if k in (7,8) else None
    return a,extra


def encode(k,a,extra=None):
    head=str(len(a))+((' '+str(len(extra))) if k==0 else (' '+str(extra)) if k in (7,8) else '')+'\n'
    if k==9: return head+''.join(f'{x} {y}\n' for x,y in a)
    return head+' '.join(map(str,a))+'\n'+(''.join(f'{l} {r}\n' for l,r in extra) if k==0 else '')


def format_indices(xs): return [len(xs)]+xs


def brute(k,a,e):
    n=len(a)
    if k==0: return [sum(a[l-1:r]) for l,r in e]
    if k==1: return [sum(a[i]<min(a[:i]) or a[i]>max(a[:i]) for i in range(1,n))]
    if k==2: return format_indices([i+1 for i in range(n) if sum(a[:i])==sum(a[i+1:])])
    if k==3: return [max([0]+[a[j]-a[i] for i in range(n) for j in range(i+1,n)])]
    if k==4:
        for energy in range(sum(abs(x) for x in a)+1):
            cur=energy
            for x in a:
                cur+=x
                if cur<0: break
            else: return [energy]
    if k in (5,7): return [max(sum(a[l:r]) for l in range(n) for r in range(l+(e if k==7 else 1),n+1))]
    if k==6: return [sum(max(a[:i])<=min(a[i:]) for i in range(1,n))]
    if k==8: return [sum(sum(a[l:r])%e==0 for l in range(n) for r in range(l+1,n+1))]
    if k==9:
        ans=[]
        for i in range(n):
            fuel=0
            for j in range(n):
                x,y=a[(i+j)%n]; fuel+=x-y
                if fuel<0: break
            else: ans.append(i+1)
        return format_indices(ans)
    raise ValueError(k)


def reference(k,a,e):
    n=len(a)
    if k==0:
        s=[0]+list(accumulate(a)); return [s[r]-s[l-1] for l,r in e]
    if k==1:
        lo=list(accumulate(a,min)); hi=list(accumulate(a,max))
        return [sum(a[i]<lo[i-1] or a[i]>hi[i-1] for i in range(1,n))]
    if k==2:
        left=[0]+list(accumulate(a)); right=list(accumulate(reversed(a)))
        return format_indices([i+1 for i in range(n) if left[i]==(right[n-i-2] if i<n-1 else 0)])
    if k==3:
        mx=list(accumulate(reversed(a),max))[::-1]
        return [max([0]+[mx[i+1]-a[i] for i in range(n-1)])]
    if k==4: return [-min([0]+list(accumulate(a)))]
    if k==5:
        best=cur=a[0]
        for x in a[1:]: cur=max(x,cur+x); best=max(best,cur)
        return [best]
    if k==6:
        left=list(accumulate(a,max)); right=list(accumulate(reversed(a),min))[::-1]
        return [sum(left[i-1]<=right[i] for i in range(1,n))]
    if k==7:
        s=[0]+list(accumulate(a)); mx=list(accumulate(reversed(s),max))[::-1]
        return [max(mx[i+e]-s[i] for i in range(n-e+1))]
    if k==8:
        counts=Counter(x%e for x in [0]+list(accumulate(a)))
        return [sum(c*(c-1)//2 for c in counts.values())]
    if k==9:
        # Split each circular walk at N; compare suffix and wrapped prefix minima.
        s=[0]+list(accumulate(x-y for x,y in a))
        suffix=list(accumulate(reversed(s[1:]),min))[::-1]
        pm=float('inf'); ans=[]
        for i in range(n):
            if suffix[i]>=s[i] and s[-1]+pm>=s[i]: ans.append(i+1)
            pm=min(pm,s[i+1])
        return format_indices(ans)
    raise ValueError(k)


def run(exe,data):
    p=subprocess.run([str(exe)],input=data,text=True,capture_output=True,timeout=5)
    assert p.returncode==0,(exe,p.stderr)
    return list(map(int,p.stdout.split()))


def audit(p,k):
    text=(p/'task.md').read_text()
    expected=['Đề bài','Dữ liệu vào','Dữ liệu ra','Ràng buộc','Sample Input 1','Sample Output 1','Sample Input 2','Sample Output 2','Giải thích']
    assert re.findall(r'^### (.+)$',text,re.M)==expected,p
    assert text.startswith(f'# PREFIX{k:02} — ')
    assert '### Subtask' not in text
    blocks=re.findall(r'```text\n(.*?)```',text,re.S)
    assert len(blocks)==4
    for i in range(2):
        assert blocks[i*2]==(p/'gen'/f'example_{i:02}.in').read_text()
        a,e=decode(k,blocks[i*2])
        assert list(map(int,blocks[i*2+1].split()))==brute(k,a,e),(p,i,'sample')
    assert not (p/'task.html').exists()


def adversarial(p,k):
    sample=(p/'gen/example_00.in').read_text()
    invalid=[sample+'0\n',sample.split('\n',1)[0]+'\n',sample.replace(' ','  ',1)]
    a,e=decode(k,sample)
    # Invalid size, value and supplementary parameter boundaries.
    invalid.append(encode(k,[(0,0)] if k==9 else [0],e if k in (7,8) else [(1,1)] if k==0 else None).replace('1','0',1))
    if k==9:
        invalid+=['1\n-1 0\n','1\n0 1000000001\n']
    else:
        v=-1 if k in (0,3) else -1000000001
        invalid += [encode(k,[v,v] if k==6 else [v],[(1,1)] if k==0 else 1 if k in (7,8) else None)]
        invalid += [encode(k,[1000000001]* (2 if k==6 else 1),[(1,1)] if k==0 else 1 if k in (7,8) else None)]
    if k==0: invalid+=['1 1\n0\n1 2\n','1 0\n0\n']
    if k==7: invalid+=['1 2\n0\n','1 0\n0\n']
    if k==8: invalid+=['1 0\n0\n','1 200001\n0\n']
    for data in invalid:
        r=subprocess.run([str(p/'verifier')],input=data,text=True,capture_output=True)
        assert r.returncode!=0,(p,'accepted invalid',data)
    good=(p/'out/example_00.out').read_text()
    tokens=good.split()
    wrong=[str(int(tokens[0])+1)]+tokens[1:]
    with tempfile.TemporaryDirectory() as td:
        path=Path(td)/'candidate.out'
        for content,ok in [(good,True),('  \n'+'\t'.join(tokens)+'\n',True),(' '.join(wrong),False),(' '.join(tokens[:-1]),False),(good+' 42\n',False),('oops\n',False)]:
            path.write_text(content)
            r=subprocess.run([str(p/'checker'),str(p/'in/example_00.in'),str(path),str(p/'out/example_00.out')],capture_output=True)
            assert (r.returncode==0)==ok,(p,content,r.stderr)
    return len(invalid)+6


def check(k,generate):
    p=ROOT/'custom'/f'prefix{k:02}'; audit(p,k)
    problem=Problem(ROOT,p)
    if generate:
        problem.health_check(); problem.generate_params_h()
        problem.compile_correct(); problem.compile_gens(); problem.compile_verifier(); problem.compile_checker()
        problem.make_inputs(); problem.verify_inputs(); problem.make_outputs(True)
    count=0
    for inp in sorted((p/'in').glob('*.in')):
        a,e=decode(k,inp.read_text()); actual=list(map(int,(p/'out'/(inp.stem+'.out')).read_text().split()))
        assert actual==reference(k,a,e),(p,inp,'independent reference')
        count+=1
    assert count==26,(p,count)
    # Small exhaustive signed arrays, then larger randomized cases with independent brute force.
    small=0
    for n in range(2 if k==6 else 1,5):
        for vals in product((-1,0,1),repeat=n):
            a=[(max(x,0),max(-x,0)) for x in vals] if k==9 else [abs(x) for x in vals] if k in (0,3) else list(vals)
            extras=[[(l,r) for l in range(1,n+1) for r in range(l,n+1)]] if k==0 else list(range(1,n+1)) if k==7 else [1,2,3] if k==8 else [None]
            for e in extras:
                expected=brute(k,a,e)
                assert reference(k,a,e)==expected,(k,a,e,'oracle')
                assert run(p/'sol/correct',encode(k,a,e))==expected,(k,a,e)
                small+=1
    rng=random.Random(2800+k)
    for _ in range(200):
        n=rng.randint(2 if k==6 else 1,18)
        a=[(rng.randint(0,12),rng.randint(0,12)) for _ in range(n)] if k==9 else [rng.randint(0 if k in (0,3) else -12,12) for _ in range(n)]
        e=[(1,n),(n,n),(1,1)] if k==0 else rng.randint(1,n) if k==7 else rng.randint(1,20) if k==8 else None
        expected=brute(k,a,e)
        assert reference(k,a,e)==expected,(k,a,e,'oracle')
        assert run(p/'sol/correct',encode(k,a,e))==expected,(k,a,e)
        small+=1
    attacks=adversarial(p,k)
    if generate:
        problem.ignore_warning=True; problem.write_hashes()
        # Regenerate with the same seeds and compare hashes of both input and output.
        problem.make_inputs(); problem.verify_inputs(); problem.assert_hashes()
    else: problem.assert_hashes()
    print(f'{p.name}: {count} generated tests, {small} brute comparisons, {attacks} negative/format checks; hashes OK',flush=True)


def main():
    ap=argparse.ArgumentParser(); ap.add_argument('--problem',choices=[f'prefix{i:02}' for i in range(10)]); ap.add_argument('--generate',action='store_true'); args=ap.parse_args()
    logging.basicConfig(level=logging.ERROR)
    for k in range(10):
        if args.problem is None or args.problem==f'prefix{k:02}': check(k,args.generate)

if __name__=='__main__': main()
