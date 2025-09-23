Cho một số **nguyên không âm chẵn** $N$. Hãy tìm $3$ số nguyên tố phân biệt $A, B, C$ sao cho $A^2 + B^2 + C^2 = N$.

### Dữ liệu vào

- Dòng đầu tiên chứa một số nguyên dương $T$ ($1 \leq T \leq 500$) là số lượng bộ test.
- Mỗi bộ test là một số nguyên không âm chẵn $N$ ($0 \leq N \leq 10^{10}$).

### Dữ liệu ra

- Với mỗi bộ test, in ra `Yes` nếu tìm được $A, B, C$ thoả mãn điều kiện, ngược lại in ra `No`.

### Sample Input

```
3
6
38
78
```

### Sample Output

```
No
Yes
Yes
```

### Giải thích

- Với $N = 6$, không có ba số nguyên tố phân biệt nào thoả mãn $A^2 + B^2 + C^2 = 6$.
- Với $N = 38$, ta có $A = 2, B = 3, C = 5$ vì $2^2 + 3^2 + 5^2 = 4 + 9 + 25 = 38$.