"""Reference solution using only the Python standard library."""
import sys


def solve(data):
    tokens = data.split()
    n = int(tokens[0])
    inf = 10**30
    s = tokens[1]
    w = list(map(int, tokens[2:]))
    future = [0, 0, 0]
    for c, cost in zip(reversed(s), reversed(w)):
        choose = [future[k] + (0 if color == c else cost) for k, color in enumerate('RGB')]
        future = [min(choose[k] for k in range(3) if k != prev) for prev in range(3)]
    return min(choose)


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
