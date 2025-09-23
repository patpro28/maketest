n = int(input())
s = ["1", "2", "3", "4", "5", "6", "7", "8", "9"]

dem = 0

for i in range(1, 10):
    for c in s:
        if int(c * i) <= n:
            dem += 1

print(dem)