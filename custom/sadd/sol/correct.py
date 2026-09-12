mod = 10**9 + 7
def calc(n, l, r):
    if l == 1 and r == n: return (n*(n+1)//2 ) % mod
    mid = n//2
    if r <= mid: return (2*calc(n//2, l, r) - (r-l+1)) % mod
    if l > mid: return (2*calc(n//2, l - mid, r - mid))%mod
    ret = (2*calc(n//2, l, n//2) - (n//2 - l + 1)) % mod + (2*calc(n//2, 1, r - mid) % mod)
    return ret % mod

import sys
input = sys.stdin.readline
for _ in range(int(input())):
    n, l, r = map(int, input().split())
    print(calc(n, l, r))