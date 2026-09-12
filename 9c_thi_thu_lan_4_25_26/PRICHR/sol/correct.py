import sys

input = sys.stdin.readline
for f in range(int(input())):
    n, s = int(input()), input()
    d = set([*input().split()][1:])
    p = r = 0
    for i in range(n):
        if s[i] in d:
            r = max(r, i - p)
            p = i
    print(r)
