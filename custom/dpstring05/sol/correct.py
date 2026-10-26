"""Reference solution using only the Python standard library."""
import sys


def solve(data):
    tokens = data.split()
    n = int(tokens[0])
    inf = 10**30
    x, y = int(tokens[1]), int(tokens[2])
    s = tokens[3]
    future = [0, 0]
    for i in range(len(s) - 1, -1, -1):
        choose = [future[k] if s[i] in ('?', color) else inf for k, color in enumerate('AB')]
        future = [min(choose[0], choose[1] + x), min(choose[0] + y, choose[1])]
    return min(choose)


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
