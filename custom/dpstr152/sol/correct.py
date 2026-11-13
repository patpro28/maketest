"""Python 3 reference solution, using the standard library only."""
import sys


def solve(data):
    tokens = data.split()
    n, m = int(tokens[0]), int(tokens[1])
    a, b = tokens[2], tokens[3]
    from functools import lru_cache

    def next_positions(s):
        table = [[len(s)] * 3 for _ in range(len(s) + 1)]
        for i in range(len(s) - 1, -1, -1):
            table[i] = table[i+1].copy()
            table[i][ord(s[i])-97] = i
        return table

    na, nb = next_positions(a), next_positions(b)

    @lru_cache(None)
    def best(i, j, last):
        result = 0
        for c in range(3):
            if c != last:
                p, q = na[i][c], nb[j][c]
                if p < n and q < m:
                    result = max(result, 1 + best(p+1, q+1, c))
        return result

    return str(best(0, 0, 3))


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
