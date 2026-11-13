"""Python 3 reference solution, using the standard library only."""
import sys


def solve(data):
    tokens = data.split()
    n, m = int(tokens[0]), int(tokens[1])
    a, b = tokens[2], tokens[3]
    weights = list(map(int, tokens[4:]))
    score = {chr(97+i): value for i, value in enumerate(weights)}
    dp = [0] * (m + 1)
    for c in reversed(a):
        cur = [0] * (m + 1)
        for j in range(m - 1, -1, -1):
            value = max(dp[j], cur[j+1])
            if c == b[j]:
                value = max(value, dp[j+1] + score[c])
            cur[j] = value
        dp = cur
    return str(dp[0])


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
