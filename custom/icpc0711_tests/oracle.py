#!/usr/bin/env python3
"""Independent small-instance oracles, adversarial input validation, and regressions."""
from collections import deque
from functools import lru_cache
from itertools import permutations,product
from pathlib import Path
import random
import subprocess
import sys
import tempfile
ROOT=Path(__file__).resolve().parents[2]
sys.path.insert(0,str(Path(__file__).parent))
from run import execute
R=ROOT/'custom';rng=random.Random(711)

def oracle(c,data):
    tok=data.split();it=iter(tok)
    def num():return int(next(it))
    if c=='a':
        n,q=num(),num();s=list(next(it));res=[]
        for _ in range(q):
            x=num()-1;s[x]=next(it);res.append(sum(s[i:i+3]==list('ABC') for i in range(n-2)))
        return res
    if c=='b':
        n=num();a=[num() for _ in range(n)];b=[]
        for l in range(n):
            for r in range(l+1,n+1):b.append(sorted(a[l:r])[(r-l)//2])
        return [sorted(b)[len(b)//2]]
    if c=='c':
        n=num();return [max(x for x in palcubes if x<=n)]
    if c=='d':
        n=num();a=tuple(num() for _ in range(n));b=tuple(num() for _ in range(n));q=deque([(a,0)]);seen={a}
        while q:
            u,d=q.popleft()
            if u==b:return [d]
            v=0
            for x in u:v^=x
            for i in range(n):
                z=u[:i]+(v,)+u[i+1:]
                if z not in seen:seen.add(z);q.append((z,d+1))
        return [-1]
    if c=='e':
        n,m=num(),num();adj=[set() for _ in range(n)]
        for _ in range(m):u,v=num()-1,num()-1;adj[u].add(v);adj[v].add(u)
        seen=set();count=0
        for start in product(range(n),repeat=2):
            if start in seen:continue
            count+=1;seen.add(start);st=[start]
            while st:
                u,v=st.pop()
                for x,y in product(adj[u],adj[v]):
                    if (x,y) not in seen:seen.add((x,y));st.append((x,y))
        return [count]
    if c=='f':
        n=num();return [sum(x<=n for x in nums357)]
    if c=='g':
        n,k=num(),num();s=[next(it) for _ in range(n)];x=next(it)
        return [sorted(''.join(z) for z in permutations(s,k)).index(x)+1]
    if c=='h':
        n=num();a=[num() for _ in range(n)];b=[num() for _ in range(n)];best=None
        for p in permutations(range(n)):
            val=[(b if (i-j)%2 else a)[j] for i,j in enumerate(p)]
            if val==sorted(val):
                cost=sum(p[i]>p[j] for i in range(n) for j in range(i+1,n))
                best=cost if best is None else min(best,cost)
        return [-1 if best is None else best]
    if c=='i':
        n,X=num(),num();pts=[(num(),num(),num()) for _ in range(n)];res=[]
        def cross(a,b,c):return (b[0]-a[0])*(c[1]-a[1])-(b[1]-a[1])*(c[0]-a[0])
        for x,y,_ in pts:
            triangle=[(0,0),(X,0),(x,y)]
            res.append(sum(w for xx,yy,w in pts if all(cross(triangle[i],triangle[(i+1)%3],(xx,yy))>0 for i in range(3))))
        return res
    if c=='j':
        n=num();a=[num() for _ in range(n)]
        return [sum(sum(map(int,str(x+y))) for x in a for y in a)]
    if c=='k':
        n,T=num(),num();a=tuple(num() for _ in range(n));seq=triseq(n)
        return [len(seq),*seq[T-1],seq.index(a)+1]
    if c=='l':
        n=num();colors=list(next(it));g=[[] for _ in range(n)]
        for _ in range(n-1):u,v,w=num()-1,num()-1,num();g[u].append((v,w));g[v].append((u,w))
        par=[-1]*n;order=[0]
        for u in order:
            for v,w in g[u]:
                if v!=par[u]:par[v]=u;order.append(v)
        descendants=[{i} for i in range(n)]
        for u in order[::-1]:
            if par[u]>=0:descendants[par[u]]|=descendants[u]
        dist=[[0]*n for _ in range(n)]
        for source in range(n):
            st=[(source,-1)]
            for u,p in st:
                for v,w in g[u]:
                    if v!=p:dist[source][v]=dist[source][u]+w;st.append((v,u))
        res=[]
        for _ in range(num()):
            t,u=num(),num()-1
            if t==1:colors[u]='0' if colors[u]=='1' else '1';continue
            nodes=[v for v in descendants[u] if colors[v]=='1'];k=len(nodes)
            # Held–Karp on the complete metric, independent of the tree formula.
            starts=[0] if t==2 else range(k);best=10**30
            for start in starts:
                dp={(1<<start,start):0}
                for mask in range(1,1<<k):
                    for last in range(k):
                        if (mask,last) not in dp:continue
                        value=dp[mask,last]
                        for j in range(k):
                            if not mask>>j&1:
                                key=(mask|1<<j,j);dp[key]=min(dp.get(key,10**30),value+dist[nodes[last]][nodes[j]])
                for last in range(k):
                    if ((1<<k)-1,last) in dp:best=min(best,dp[(1<<k)-1,last]+(dist[nodes[last]][nodes[start]] if t==2 else 0))
            res.append(best)
        return res
    raise ValueError(c)

@lru_cache(None)
def triseq(n):
    return [a for a in product(range(1,n+1),repeat=n) if n<3 or sorted(a)[0]+sorted(a)[1]>max(a)]

# Independent enumeration by decimal strings, not the solution's recursion/numeric reverse.
palcubes=[x**3 for x in range(1,1000001) if str(x**3)==str(x**3)[::-1]]
nums357=[int(''.join(z)) for length in range(3,10) for z in product('357',repeat=length) if len(set(z))==3]

def main():
    counts={c:0 for c in 'abcdefghijkl'}
    def check(c,data,expected=None,validate=True):
        base=R/f'icpc0711{c}'
        if validate:execute(base/'verifier',data,timeout=10)
        got=list(map(int,execute(base/'sol/correct',data).split()))
        want=oracle(c,data) if expected is None else expected
        assert got==want,(c,data[:500],got,want)
        counts[c]+=1
    for c in counts:
        base=R/f'icpc0711{c}'
        for inp in sorted((base/'in').glob('*.in')):
            seed=int(inp.stem.rsplit('_',1)[1])
            if inp.stem.startswith('example') or seed<11 or c in 'cf':check(c,inp.read_text())
    # Deterministic random differential runs for the algorithms with richer state.
    for _ in range(120):
        n=rng.randint(2,6);a=[rng.randrange(4) for _ in range(n)];b=[rng.randrange(4) for _ in range(n)]
        check('d',f'{n}\n'+ ' '.join(map(str,a))+'\n'+' '.join(map(str,b))+'\n')
        a=[rng.randrange(10) for _ in range(n)];b=[rng.randrange(10) for _ in range(n)]
        data=f'{n}\n'+' '.join(map(str,a))+'\n'+' '.join(map(str,b))+'\n'
        expected=oracle('h',data)
        if expected!=[-1]:check('h',data,expected)
        else:
            assert subprocess.run([str(R/'icpc0711h/verifier')],input=data,text=True,capture_output=True).returncode!=0
    for n in range(1,5):
        seq=triseq(n)
        for t in sorted(set([1,len(seq),max(1,len(seq)//2)])):
            check('k',f'{n}\n{t}\n'+' '.join(map(str,seq[-t]))+'\n')
    # Maximal ranks: combinatorial sum over multisets, independent of prefix DP.
    # For minimum a and second minimum b, distinguish a<b (unique a) and a=b.
    from math import comb
    def total(n):
        if n<3:return n**n
        result=0
        for a in range(1,n+1):
            for b in range(a,n+1):
                hi=min(n,a+b-1);choices=hi-b+1
                if choices<=0:continue
                if a<b:result+=n*(choices**(n-1)-(choices-1)**(n-1))
                else:result+=choices**n-(choices-1)**n-n*(choices-1)**(n-1)
        return result
    for n in [6,10,18]:
        t=total(n);check('k',f'{n}\n{t}\n'+(' '.join([str(n)]*n))+'\n',[t,*([n]*n),t])
    # Large analytically determined answers.
    for n in [1,100000]:check('b',f'{n}\n'+' '.join(['1000000000']*n)+'\n',[1000000000])
    check('e','100000 0\n',[10000000000])
    for x in [1,10**15,10**15-1]:
        n=200000;check('j',f'{n}\n'+' '.join([str(x)]*n)+'\n',[n*n*sum(map(int,str(2*x)))])
    check('h',(R/'icpc0711h/in/cases_11.in').read_text(),[153])
    # Additional malformed inputs and semantic violations.
    bad={
      'a':['1 1\na\n1 A\n','1 1\nA\n2 B\n'],
      'b':['0\n','1\n1000000001\n'],
      'c':['0\n','1000000000000000001\n'],
      'd':['1\n0\n0\n','2\n0 1073741824\n0 0\n'],
      'e':['2 -1\n','2 1\n1 3\n'],
      'f':['0\n','1000000001\n'],
      'g':['2 1\na\nab\na\n','2 2\na\nb\naa\n','2 1\na\nb\nc\n'],
      'h':['2\n2 1\n1 2\n','2\n51 1\n1 2\n'],
      'i':['2 4\n1 1 1\n2 2 1\n','2 4\n1 1 1\n1 1 2\n'],
      'j':['1\n0\n','1\n1000000000000001\n'],
      'k':['3\n16\n2 1 2\n','3\n1\n1 1 3\n'],
      'l':['2\n00\n1 2 1\n2\n2 1\n3 1\n','3\n111\n1 2 1\n1 2 1\n2\n2 1\n3 1\n'],
    }
    rejected=0
    for c,inputs in bad.items():
        sample=(R/f'icpc0711{c}/gen/example_00.in').read_text()
        for data in inputs+[sample+'123\n','\n'.join(sample.splitlines()[:-1])+'\n']:
            result=subprocess.run([str(R/f'icpc0711{c}/verifier')],input=data,text=True,capture_output=True,timeout=10)
            assert result.returncode!=0,(c,data);rejected+=1
    report='\n## Đối chiếu độc lập\n\n'+''.join(f'- {c.upper()}: {v} trường hợp khớp đáp án độc lập.\n' for c,v in counts.items())+f'\nTừ chối đúng {rejected} dữ liệu sai định dạng hoặc vi phạm điều kiện (ngoài các bộ bài H vô nghiệm ngẫu nhiên).\n'
    result=R/'icpc0711_tests/results.md';result.write_text(result.read_text()+report)
    print(report,flush=True)
if __name__=='__main__':main()
