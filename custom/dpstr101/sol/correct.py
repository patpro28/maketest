"""Python 3 reference solution, using the standard library only."""
import sys


def solve(data):
    tokens = data.split()
    n, m = int(tokens[0]), int(tokens[1])
    a, b = tokens[2], tokens[3]
    dp = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(n - 1, -1, -1):
        row, below = dp[i], dp[i+1]
        for j in range(m - 1, -1, -1):
            row[j] = below[j+1] + 1 if a[i] == b[j] else max(below[j], row[j+1])
    i = j = 0
    answer = []
    while i < n and j < m:
        if a[i] == b[j]:
            answer.append(a[i])
            i += 1
            j += 1
        elif dp[i+1][j] >= dp[i][j+1]:
            i += 1
        else:
            j += 1
    return str(len(answer)) + ('\n' + ''.join(answer) if answer else '')


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
