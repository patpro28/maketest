# ICPC0711J — Tổng các chữ số

### Đề bài

Với số nguyên dương $x$, gọi $f(x)$ là tổng các chữ số thập phân của $x$. Ví dụ, $f(10)=1$ và $f(123)=6$.

Cho dãy $A$ gồm $N$ số nguyên dương. Hãy tính

$$\sum_{i=1}^{N}\sum_{j=1}^{N}f(A_i+A_j).$$

Các cặp $(i,j)$ có thứ tự, và bao gồm cả trường hợp $i=j$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là giá trị tổng cần tìm.

### Ràng buộc

- $1\le N\le2\cdot10^5$.
- $1\le A_i\le10^{15}$.

### Sample Input 1

```text
2
58 23
```

### Sample Output 1

```text
36
```

### Sample Input 2

```text
5
12 23 34 45 56
```

### Sample Output 2

```text
269
```

### Sample Input 3

```text
1
999
```

### Sample Output 3

```text
27
```

### Giải thích

Ở ví dụ 1, bốn số hạng là $f(116)=8$, $f(81)=9$, $f(81)=9$ và $f(46)=10$, tổng bằng $36$. Ví dụ 2 có kết quả $269$. Ở ví dụ 3, $f(999+999)=f(1998)=27$.
