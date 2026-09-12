for _ in range(int(input())):
    n = int(input())
    a = [0, 0, 0] + list(map(int, input().split()))
    dp = [0]*len(a)
    dp[3] = a[3]
    for i in range(4, len(a)):
        dp[i] = a[i] + dp[i-1]
        dp[i] = min(dp[i], abs(a[i] - a[i-1]) + a[i-2] + dp[i-3])
    print(dp[-1])
