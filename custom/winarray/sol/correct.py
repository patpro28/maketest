
def solve():
    n = int(input())
    a = list(map(int, input().split()))

    # for subarray of len 1
    ans = a.count(1)    
    
    # prev point to last 11, 101 found in array
    prev = -1
    for i in range(n):
        # 11
        if i+1<n and a[i] and a[i+1]:
            ans += (i - prev) * (n-1 - i)
            prev = i
        # 101
        elif i+2<n and a[i] and a[i+2]:
            ans += (i - prev) * (n-1 - i - 1)
            prev = i
    
    print(ans)      
        
t = int(input())
for _ in range(t):
    solve()
