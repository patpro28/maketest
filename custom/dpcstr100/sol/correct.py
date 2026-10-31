"""Python 3 reference solution, using the standard library only."""
import sys


def solve(data):
    tokens = data.split()
    n, m = int(tokens[0]), int(tokens[1])
    a, b = tokens[2], tokens[3]
    dp = [0] * (m + 1)
    for c in reversed(a):
        cur = [0] * (m + 1)
        for j in range(m - 1, -1, -1):
            cur[j] = dp[j+1] + 1 if c == b[j] else max(dp[j], cur[j+1])
        dp = cur
    return str(dp[0])


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
