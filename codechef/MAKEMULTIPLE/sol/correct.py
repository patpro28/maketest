for _ in range(int(input())):
    a, b = map(int, input().split())
    d = b - a
    print('YES' if d == 0 or a <= d else 'NO')