"""Python 3 reference solution, using the standard library only."""
import sys


def solve(data):
    tokens = data.split()
    n, m = int(tokens[0]), int(tokens[1])
    a, b = tokens[2], tokens[3]
    # Direct minimum-deletion DP.
    dp = list(range(m + 1))
    for i, c in enumerate(a, 1):
        cur = [i] + [0] * m
        for j, d in enumerate(b, 1):
            cur[j] = dp[j-1] if c == d else min(dp[j], cur[j-1]) + 1
        dp = cur
    return str(dp[m])


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
