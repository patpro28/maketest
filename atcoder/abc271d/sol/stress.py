"""Compare compiled solutions with enumeration of all face assignments."""
from itertools import product
from pathlib import Path
import random
import subprocess

base = Path(__file__).resolve().parent
rng = random.Random(271)
cases = []
for a in range(1, 5):
    for b in range(1, 5):
        for s in range(1, 6):
            cases.append(([(a,b)], s))
for _ in range(320):
    cards = [(rng.randint(1,100), rng.randint(1,100))
             for _ in range(rng.randint(1,12))]
    s = (sum(rng.choice(pair) for pair in cards) if rng.randrange(2)
         else rng.randint(1, min(10000, 100*len(cards)+1)))
    cases.append((cards, s))
for cards, s in cases:
    feasible = any(sum(values) == s for values in product(*cards))
    data = f'{len(cards)} {s}\n' + ''.join(f'{a} {b}\n' for a,b in cards)
    for name in ('correct', 'suffix'):
        output = subprocess.check_output([str(base/name)], input=data.encode()).decode().split()
        if not feasible:
            assert output == ['No'], (name,cards,s,output)
        else:
            assert len(output) == 2 and output[0] == 'Yes', (name,cards,s,output)
            choices = output[1]
            assert len(choices) == len(cards) and set(choices) <= {'A','B'}
            assert sum(cards[i][c == 'B'] for i,c in enumerate(choices)) == s
print(f'PASS: {len(cases)} cases against exhaustive enumeration')
