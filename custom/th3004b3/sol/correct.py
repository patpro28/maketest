# last digit of 4^n
n = int(input())
if n == 0:
    print(1)
elif n & 1:
    print(4)
else:
    print(6)
