"""Reference solution using only the Python standard library."""
import sys


def solve(data):
    tokens = data.split()
    n = int(tokens[0])
    inf = 10**30
    s = tokens[1]
    dp = {'': 0}
    for c in s:
        nxt = {last: cost + 1 for last, cost in dp.items()}
        for last, cost in dp.items():
            if last != c:
                nxt[c] = min(nxt.get(c, inf), cost)
        dp = nxt
    return min(dp.values())


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
