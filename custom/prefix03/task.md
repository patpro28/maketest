# PREFIX03 — Mua rồi bán

### Đề bài

Giá của một món hàng trong ngày $i$ là $A_i$. Bạn được thực hiện tối đa một giao dịch: mua một món trong ngày $i$, sau đó bán trong ngày $j$ với $i<j$. Lợi nhuận là $A_j-A_i$.

Hãy tìm lợi nhuận lớn nhất. Bạn được phép không giao dịch, khi đó lợi nhuận bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là lợi nhuận lớn nhất có thể đạt được.

### Ràng buộc

- $1\le N\le200000$.
- $0\le A_i\le10^9$.

### Sample Input 1

```text
6
7 1 5 3 6 4
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
4
9 7 7 2
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, mua ngày $2$ với giá $1$, bán ngày $5$ với giá $6$ để lãi $5$. Ở ví dụ 2, không giao dịch cho lợi nhuận lớn nhất bằng $0$.
