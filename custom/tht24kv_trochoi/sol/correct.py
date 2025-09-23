n = int(input())
k = int(input())

if n < 10:
    print(n // 2 + 1)
elif k - 10 >= 0:
    print(0)
else:
    day = 5
    n -= 10
    times, n = divmod(n, 10 - k)
    day += times * 5
    n += k
    day += n // 2
    print(day + 1)