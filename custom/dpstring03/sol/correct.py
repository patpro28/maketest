"""Reference solution using only the Python standard library."""
import sys


def solve(data):
    tokens = data.split()
    n = int(tokens[0])
    inf = 10**30
    s = tokens[1]
    w = list(map(int, tokens[2:]))
    dp = {'': 0}
    for c, cost in zip(s, w):
        nxt = {tail: value + cost for tail, value in dp.items()}
        for tail, value in dp.items():
            if tail != c * 2:
                new = tail + c if tail == c else c
                nxt[new] = min(nxt.get(new, inf), value)
        dp = nxt
    return min(dp.values())


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
