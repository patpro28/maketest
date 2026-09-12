import bisect

n, q = map(int, input().split())
a = list(map(int, input().split()))

a.sort()
d = [a[i + 1] - a[i] for i in range(n - 1)] + [10**9]
d.sort()
pref = [0] * (n + 1)
for i in range(1, n + 1):
    pref[i] = pref[i - 1] + d[i - 1]

for _ in range(q):
    x = int(input())
    pos = bisect.bisect_left(d, x)
    print((n - pos) * x + pref[pos])
