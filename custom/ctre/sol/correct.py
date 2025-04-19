n = int(input())
deg = [0]*n
for i in range(n-1):
    u, v = map(int, input().split())
    deg[u-1] += 1
    deg[v-1] += 1
leaves = 0
for i in range(n): leaves += deg[i] == 1
print(3*leaves + 2*(n - leaves))