"""Python 3 reference solution, using the standard library only."""
import sys


def solve(data):
    tokens = data.split()
    n, m = int(tokens[0]), int(tokens[1])
    a, b = tokens[2], tokens[3]
    target = tokens[4]
    prefix = [[0] * (m + 1) for _ in range(n + 1)]
    suffix = [[0] * (m + 1) for _ in range(n + 1)]
    for i in range(n):
        row, old = prefix[i+1], prefix[i]
        for j in range(m):
            row[j+1] = old[j] + 1 if a[i] == b[j] else max(old[j+1], row[j])
    for i in range(n - 1, -1, -1):
        row, old = suffix[i], suffix[i+1]
        for j in range(m - 1, -1, -1):
            row[j] = old[j+1] + 1 if a[i] == b[j] else max(old[j], row[j+1])
    answer = -1
    for i, c in enumerate(a):
        if c == target:
            for j, d in enumerate(b):
                if d == target:
                    answer = max(answer, prefix[i][j] + 1 + suffix[i+1][j+1])
    return str(answer)


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
