N, Q = map(int, input().split())
S = list(input())
ans = 0
for i in range(N - 2):
    if S[i] == "A" and S[i + 1] == "B" and S[i + 2] == "C":
        ans += 1
for _ in range(Q):
    t, c = input().split()
    t = int(t) - 1
    for k in range(3):
        idx = t - k
        if 0 <= idx and idx + 2 < N:
            if S[idx] == "A" and S[idx + 1] == "B" and S[idx + 2] == "C":
                ans -= 1
    S[t] = c
    for k in range(3):
        idx = t - k
        if 0 <= idx and idx + 2 < N:
            if S[idx] == "A" and S[idx + 1] == "B" and S[idx + 2] == "C":
                ans += 1
    print(ans)
