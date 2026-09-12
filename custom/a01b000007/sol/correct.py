import math

N = int(input())

# Câu 1
L = math.ceil((N - 1) / 2)
ans1 = N - L + 1

# Câu 2
ans2 = N * N - N

print(ans1)
print(ans2)
