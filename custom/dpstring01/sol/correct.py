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
        for last, score in dp.items():
            if last != kind:
                nxt[kind] = max(nxt.get(kind, -inf), score + value)
        dp = nxt
    return max(dp.values())


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
