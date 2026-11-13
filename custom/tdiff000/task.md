# TDIFF000 — Tính mảng hiệu

### Đề bài

Cho dãy số nguyên $A$ gồm $N$ phần tử. Mảng hiệu $D$ của dãy $A$ được xác định bởi $D_1=A_1$ và $D_i=A_i-A_{i-1}$ với $2\le i\le N$. Hãy tính mảng hiệu $D$.

### Dữ liệu vào

Dòng đầu chứa số nguyên $T$ là số bộ test. Dữ liệu của mỗi bộ test được ghi theo định dạng sau.

- Dòng thứ nhất chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In kết quả của các bộ test theo thứ tự đầu vào. Với mỗi bộ test, in trên một dòng $N$ phần tử của mảng hiệu $D$ theo thứ tự.

### Ràng buộc

- $1\le T\le 10^4$.
- $1\le N\le 2\cdot 10^5$.
- Tổng kích thước trên tất cả các bộ test thỏa $\sum_{i=1}^{T} N_i \le 2\cdot 10^5$.
- $|A_i|\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
2
5
3 3 -2 4 4
1
-5
```

### Sample Output 1

```text
3 0 -5 6 0
-5
```

### Sample Input 2

```text
1
3
-1000000000 1000000000 -1000000000
```

### Sample Output 2

```text
-1000000000 2000000000 -2000000000
```

### Giải thích

Trong ví dụ 1, ở bộ thứ nhất, hiệu tại vị trí $3$ là $-2-3=-5$ và tại vị trí $4$ là $4-(-2)=6$. Bộ thứ hai chỉ có một phần tử nên mảng hiệu là $(-5)$.

Trong ví dụ 2, hai phần tử kề nhau chênh lệch lần lượt $2\cdot10^9$ và $-2\cdot10^9$.
