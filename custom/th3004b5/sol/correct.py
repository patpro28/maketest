n = int(input())
s = "HOABINHDEPLAM"

r = int((n - 1) ** 0.5)
c = n - r * r
r += 1
if r & 1:
    c = 2 * r - c
print(r + c)
print(s[(n - 1) % 13])