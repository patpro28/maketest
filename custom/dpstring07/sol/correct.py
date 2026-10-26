"""Reference solution using only the Python standard library."""
import sys


def solve(data):
    tokens = data.split()
    n = int(tokens[0])
    inf = 10**30
    s = tokens[1]
    w = list(map(int, tokens[2:]))
    # Suffix DP: best future score for no open pair / open a / open b.
    dp = [0, -inf, -inf]
    for c, value in zip(reversed(s), reversed(w)):
        kind = ord(c) - ord('a')
        nxt = dp.copy()
        nxt[0] = max(dp[0], value + dp[kind + 1])
        nxt[2 - kind] = max(dp[2 - kind], value + dp[0])
        dp = nxt
    return dp[0]


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
