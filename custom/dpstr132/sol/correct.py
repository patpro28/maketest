"""Python 3 reference solution, using the standard library only."""
import sys


def solve(data):
    tokens = data.split()
    n, m = int(tokens[0]), int(tokens[1])
    a, b = tokens[2], tokens[3]
    target = tokens[4]
    # Reversing converts "ends in target" to "begins in target".
    dp = [-1] * (m + 1)
    b = b[::-1]
    for c in reversed(a):
        cur = [-1] * (m + 1)
        for j, d in enumerate(b, 1):
            value = max(dp[j], cur[j-1])
            if c == d:
                if c == target:
                    value = max(value, 1)
                if dp[j-1] >= 0:
                    value = max(value, dp[j-1] + 1)
            cur[j] = value
        dp = cur
    return str(dp[m])


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
