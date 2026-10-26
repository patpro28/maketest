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
        nxt = {last: value + cost for last, value in dp.items()}
        keep = min((value for last, value in dp.items() if last != c), default=inf)
        nxt[c] = min(nxt.get(c, inf), keep)
        dp = nxt
    return min(dp.values())


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
