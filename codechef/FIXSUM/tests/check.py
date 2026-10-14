"""Run after generating and compiling fixsum with the repository pipeline."""
from pathlib import Path
import subprocess
import tempfile

BASE = Path(__file__).resolve().parents[1]

# Independent DP: (sum, bitwise AND) -> smallest possible maximum.
limit = 100
states = {(0, 127): 0}
cases, expected = [], []
for n in range(1, 9):
    nxt = {}
    for (total, mask), best in states.items():
        for value in range(limit - total + 1):
            key = (total + value, mask & value)
            cost = max(best, value)
            if cost < nxt.get(key, limit + 1):
                nxt[key] = cost
    states = nxt
    if n >= 2:
        for s in range(1, limit + 1):
            cases.append((n, s))
            expected.append(states[s, 0])

# For two elements, disjoint bits mean no carries: answer = highest bit of S.
for path in sorted((BASE / 'in').glob('*.in')):
    values = list(map(int, path.read_text().split()))
    for n, s in zip(values[1::2], values[2::2]):
        answer = None
        if n == 2:
            answer = 1 << (s.bit_length() - 1)
        elif n > s:
            answer = 1
        elif n == s:
            answer = 2
        if answer is not None:
            cases.append((n, s))
            expected.append(answer)
for start in range(0, len(cases), 10000):
    batch = cases[start:start + 10000]
    data = str(len(batch)) + '\n' + ''.join(f'{n} {s}\n' for n, s in batch)
    result = subprocess.run([str(BASE / 'sol/correct')], input=data, text=True,
                            capture_output=True, check=True)
    assert list(map(int, result.stdout.split())) == expected[start:start + len(batch)]
print(f'Independent checks passed: {len(cases)} cases (700 exhaustive DP cases)')

with tempfile.TemporaryDirectory() as tmp:
    out = Path(tmp) / 'answer.out'
    for data, valid in [('4\n3\n5\n2570\n', True), ('5\n3\n5\n2570\n', False),
                        ('4\n3\n5\n', False), ('4\n3\n5\n2570\n1\n', False),
                        ('oops\n', False), ('0\n3\n5\n2570\n', False)]:
        out.write_text(data)
        result = subprocess.run([str(BASE / 'checker'), str(BASE / 'in/example_00.in'),
                                 str(out), str(BASE / 'out/example_00.out')], capture_output=True)
        assert (result.returncode == 0) == valid, result.stderr

for data in ['0\n', '10001\n', '1\n1 1\n', '1\n1000000001 1\n',
             '1\n2 0\n', '1\n2 1000000001\n', '2\n2 1\n', '1\n2 1\nextra\n']:
    result = subprocess.run([str(BASE / 'verifier')], input=data, text=True, capture_output=True)
    assert result.returncode != 0, data
print('Checker and validator negative checks passed')
