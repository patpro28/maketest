"""Reference solution using only the Python standard library."""
import sys


def solve(data):
    tokens = data.split()
    n = int(tokens[0])
    inf = 10**30
    s = tokens[1]
    w = list(map(int, tokens[2:]))
    dp = {'': 0}
    for c, value in zip(s, w):
        kind = 'v' if c in 'aeiou' else 'c'
        nxt = dp.copy()
        for tail, score in dp.items():
            new = tail + kind if tail.endswith(kind) else kind
            if new not in ('vv', 'ccc'):
                nxt[new] = max(nxt.get(new, -inf), score + value)
        dp = nxt
    return max(dp.values())


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
