t = int(input())
for _ in range(t):
    a, b = map(int, input().split())
    print("YES" if pow(a, 60, b) == 0 else "NO")
