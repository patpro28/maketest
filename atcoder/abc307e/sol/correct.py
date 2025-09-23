MOD = 998244353
N, M = map(int, input().split())

fact = [1]*(N+1)
invfact = [1]*(N+1)
for i in range(2, N+1):
    fact[i] = fact[i-1]*i % MOD
invfact[N] = pow(fact[N], MOD-2, MOD)
for i in range(N-1, -1, -1):
    invfact[i] = invfact[i+1]*(i+1) % MOD


def choose(n, r): return fact[n]*invfact[r] % MOD*invfact[n-r] % MOD

ans = 0
for k in range(N+1):
    ans += (-1 if k % 2 else 1)*pow(M, max(1, N-k), MOD)*choose(N, k) % MOD

print(ans % MOD)
