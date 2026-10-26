"""Reference solution using only the Python standard library."""
import sys


def solve(data):
    tokens = data.split()
    n = int(tokens[0])
    inf = 10**30
    s = tokens[1]
    w = list(map(int, tokens[2:]))
    dp = {'': 0}
    for original, cost in zip(s, w):
        nxt = {}
        for tail, score in dp.items():
            for color in 'ABCD':
                if color not in tail:
                    new = (tail + color)[-2:]
                    value = score + (0 if color == original else cost)
                    if value < nxt.get(new, inf):
                        nxt[new] = value
        dp = nxt
    return min(dp.values())


if __name__ == "__main__":
    print(solve(sys.stdin.read()))
