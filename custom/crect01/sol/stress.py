"""Compare compiled solutions with exhaustive rectangle enumeration."""
from itertools import product
from pathlib import Path
import random
import subprocess

base=Path(__file__).resolve().parent

def brute(a):
    m,n=len(a),len(a[0])
    ps=[[0]*(n+1) for _ in range(m+1)]
    for i in range(m):
        for j in range(n):
            ps[i+1][j+1]=ps[i][j+1]+ps[i+1][j]-ps[i][j]+a[i][j]
    answer=0
    for top in range(m):
        for bottom in range(top+1,m+1):
            for left in range(n):
                for right in range(left+1,n+1):
                    total=ps[bottom][right]-ps[top][right]-ps[bottom][left]+ps[top][left]
                    answer+=total==(bottom-top)*(right-left)
    return answer

cases=[]
for m,n in [(1,1),(1,5),(5,1),(2,3),(3,2),(3,3)]:
    for bits in product(range(2),repeat=m*n):
        cases.append([list(bits[i*n:(i+1)*n]) for i in range(m)])
rng=random.Random(101)
for _ in range(150):
    m,n=rng.randint(1,8),rng.randint(1,8)
    cases.append([[rng.randrange(2) for _ in range(n)] for _ in range(m)])
for a in cases:
    expected=brute(a)
    data=f'{len(a)} {len(a[0])}\n'+''.join(' '.join(map(str,row))+'\n' for row in a)
    for name in ('correct','boundaries'):
        actual=int(subprocess.check_output([str(base/name)],input=data.encode()))
        assert actual==expected,(name,a,expected,actual)
print(f'PASS: {len(cases)} cases against exhaustive rectangle enumeration')
