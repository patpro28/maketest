# ICPC0711C — Số lập phương đối xứng

### Đề bài

Cho số nguyên dương $N$. Tìm số nguyên dương $K$ lớn nhất sao cho $K\le N$, biểu diễn thập phân của $K$ là một xâu đối xứng và tồn tại số nguyên dương $X$ với $X^3=K$.

### Dữ liệu vào

- Dòng duy nhất chứa số nguyên $N$.

### Dữ liệu ra

In số $K$ tìm được.

### Ràng buộc

- $1\le N\le10^{18}$.

### Sample Input 1

```text
375
```

### Sample Output 1

```text
343
```

### Sample Input 2

```text
9
```

### Sample Output 2

```text
8
```

### Sample Input 3

```text
1012345
```

### Sample Output 3

```text
1331
```

### Giải thích

Ở ví dụ 1, $7^3=343$ đối xứng, còn $8^3=512>375$. Ở ví dụ 2, $2^3=8\le9<3^3$. Ở ví dụ 3, số lập phương đối xứng lớn nhất không vượt $1012345$ là $1331=11^3$.
