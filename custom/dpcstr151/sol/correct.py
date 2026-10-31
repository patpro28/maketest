"""Python 3 reference solution, using the standard library only."""
import sys


def solve(data):
    tokens = data.split()
    n, m = int(tokens[0]), int(tokens[1])
    k = int(tokens[2])
    a, b = tokens[3], tokens[4]
    # Each layer uses exactly t vowels; maximize over the feasible layers.
    neg = -10**6
    previous_layer = None
    answer = 0
    for t in range(k + 1):
        dp = [[0 if t == 0 else neg] * (m + 1) for _ in range(n + 1)]
        for i, c in enumerate(a, 1):
            row, old = dp[i], dp[i-1]
            vowel = c in 'aeiou'
            for j, d in enumerate(b, 1):
                value = max(old[j], row[j-1])
                if c == d:
                    before = previous_layer[i-1][j-1] if vowel and t > 0 else neg if vowel else old[j-1]
                    if before >= 0:
                        value = max(value, before + 1)
                row[j] = value
        answer = max(answer, dp[n][m])
        previous_layer = dp
    return str(answer)


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
