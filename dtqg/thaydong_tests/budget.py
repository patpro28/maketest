"""Reproduce the declared bounds on principal loops, not CPU instructions."""
import json
import math
from pathlib import Path

ROOT=Path(__file__).resolve().parents[2]
LIMIT=20000000


def calculate():
    # Sieve marking operations and primes for FACTOR.
    composite=bytearray(1000001);primes=[];markings=0
    for p in range(2,1000001):
        if not composite[p]:
            primes.append(p)
            if p*p<=1000000:
                for j in range(p*p,1000001,p):composite[j]=1;markings+=1
    product=1;pair_loops=0;types=[]
    for m,p in enumerate(primes[:11],1):
        product*=p;k=2
        while product**k<=10**12:
            d=(k+1)**m
            # factors 1..d-2, target=factor..d-1, using 0-based indices.
            loops=d*(d+1)//2-d-1
            pair_loops+=loops;types.append((m,k,d));k+=1
    # Arithmetic limb bound: each distinct length-r subsequence count <= C(L,r).
    limbs=0
    for length in range(1,1001):
        logarithm=0.0
        for r in range(1,length+1):
            logarithm+=math.log10(length-r+1)-math.log10(r)
            limbs+=max(1,int(max(0.0,logarithm)/9)+2)
    dna_n=45;ranges=dna_n*(dna_n-1)//2
    swaps=sum((dna_n-length+1)*(length//2) for length in range(2,dna_n+1))
    # Include generation of the first layer as well as the two nested layers.
    dna_work=2*(ranges+2)*swaps+2*(ranges+1)**2
    factor_work=150*len(primes)+pair_loops+markings+1000000
    # At most 4*10*n big-integer additions for both bound queries, 34 limbs each.
    number_work=2*limbs+4*10*1000*34
    result={
      'dtrobot':dict(measure='triples of consecutive points',upper=69998),
      'dtrebuss':dict(measure='candidate digit pairs',upper=2*100000*100),
      'dtsp':dict(measure='DP cells, each with at most 3 constant-time transitions',upper=271**3),
      'dtfactor':dict(measure='trial divisions + cached divisor-pair candidates + sieve',upper=factor_work,divisor_pairs=pair_loops,prime_count=len(primes)),
      'dtbtnk':dict(measure='balance cells across both bounded-depth passes',upper=2*4000*2001),
      'dtdna':dict(measure='character-pair swaps + generated states, both sides',upper=dna_work),
      'dtnumset':dict(measure='base-10^9 additions/subtractions including bound queries',upper=number_work,narrow_main_lookups_upper=4000000),
    }
    assert all(value['upper']<=LIMIT for value in result.values()),result
    return result


if __name__=='__main__':
    data=calculate();path=Path(__file__).with_name('budget.json')
    path.write_text(json.dumps(data,indent=2)+'\n')
    for code,value in data.items():print(code,value['upper'],value['measure'])
