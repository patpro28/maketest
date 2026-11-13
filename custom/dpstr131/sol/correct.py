"""Python 3 reference solution, using the standard library only."""
import sys


def solve(data):
    tokens = data.split()
    n, m = int(tokens[0]), int(tokens[1])
    a, b = tokens[2], tokens[3]
    u = list(map(int, tokens[4:4+n]))
    v = list(map(int, tokens[4+n:]))
    # Maximize the costs saved by keeping a common subsequence.
    dp = [0] * (m + 1)
    for i in range(n - 1, -1, -1):
        cur = [0] * (m + 1)
        for j in range(m - 1, -1, -1):
            value = max(dp[j], cur[j+1])
            if a[i] == b[j]:
                value = max(value, dp[j+1] + u[i] + v[j])
            cur[j] = value
        dp = cur
    return str(sum(u) + sum(v) - dp[0])


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
