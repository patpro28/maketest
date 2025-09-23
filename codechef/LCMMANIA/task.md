Cho một số nguyên dương $N$, hãy tìm ba số nguyên dương $A, B, C$ sao cho $N = \text{lcm}(A, B) + \text{lcm}(B, C) + \text{lcm}(C, A)$.

### Dữ liệu vào

- Dòng đầu tiên chứa một số nguyên dương $T$ ($1 \leq T \leq 10^5$) là số lượng bộ test.
- Mỗi bộ test là một số nguyên dương $N$ ($1 \leq N \leq 10^{9}$).

### Dữ liệu ra

- Với mỗi bộ test, in ra một dòng chứa ba số nguyên dương $A, B, C$ nếu tồn tại, hoặc in ra `-1 -1 -1` nếu không tồn tại.
- Nếu có nhiều kết quả, in ra một kết quả bất kỳ.

### Sample Input

```
3
1
6
15
```

### Sample Output

```
-1 -1 -1
2 2 2
5 5 1
```