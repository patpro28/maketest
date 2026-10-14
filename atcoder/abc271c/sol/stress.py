"""Run after compiling correct.cpp and greedy.cpp; no external packages."""
from functools import lru_cache
from itertools import combinations_with_replacement
from pathlib import Path
import random
import subprocess

@lru_cache(None)
def brute(state):
    owned = set(state)
    answer = 0
    while answer + 1 in owned:
        answer += 1
    # Every operation reduces the book count by one. A purchased volume
    # above the remaining count cannot improve the final readable prefix.
    for i in range(len(state)):
        for j in range(i + 1, len(state)):
            rest = state[:i] + state[i + 1:j] + state[j + 1:]
            for volume in range(1, len(state)):
                answer = max(answer, brute(tuple(sorted(rest + (volume,)))))
    return answer

base = Path(__file__).resolve().parent
cases = [a for n in range(1, 6)
         for a in combinations_with_replacement(range(1, 8), n)]
rng = random.Random(271)
cases += [tuple(sorted(rng.randint(1, 9) for _ in range(7)))
          for _ in range(100)]
for a in cases:
    expected = brute(a)
    shuffled = list(a)
    rng.shuffle(shuffled)
    data = f'{len(a)}\n' + ' '.join(map(str, shuffled)) + '\n'
    for name in ('correct', 'greedy'):
        actual = int(subprocess.check_output([str(base/name)], input=data.encode()))
        assert actual == expected, (name, a, expected, actual)
print(f'PASS: {len(cases)} cases against exhaustive exchange search')
