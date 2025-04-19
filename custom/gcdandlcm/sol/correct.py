from math import sqrt
from sys import stdin

input = stdin.readline
def lcm(a, b):
    return a//gcd(a, b) * b
def gcd(a, b):
    if b == 0:
        return a
    return gcd(b, a%b)

def solve():
	n = int(input())
	mx = int(sqrt(n) + 5)
	ans = 0
	s = set()
	for A in range(1, mx):
		for L in range(A, mx, A):
			# A^2 + B^2 + G^2 + L^2 = N
			# B^2(1 + A^2/L^2) = N - A^2 - L^2
			# B^2 = L^2(N - A^2 - L^2) / (A^2 + L^2)
			num = L**2 * (n - A**2 - L**2)
			den = A**2 + L**2
			if num <= 0:
				continue
			if num % den != 0:
				continue
			x = num // den
			B = int(sqrt(x) + 0.1)
			if B*B == x and B >= 1 and B <= n and A**2 + B**2 + lcm(A, B)**2 + gcd(A, B)**2 == n:
				s.add((A, B))
	print(len(s))
	for A, B in sorted(s):
		print(A, B)

solve()