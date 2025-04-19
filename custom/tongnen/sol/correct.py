a, b = map(int, input().split())

def cal(n: int) -> int:
    s = [0, 1, 3, 6, 10, 15, 21, 28, 36, 45]
    return s[n % 9] + 45 * (n // 9)

print(cal(b) - cal(a - 1))