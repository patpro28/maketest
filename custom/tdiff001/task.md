# TDIFF001 — Khôi phục dãy số

### Đề bài

Mảng hiệu $D$ của dãy $A$ được xác định bởi $D_1=A_1$ và $D_i=A_i-A_{i-1}$ với $2\le i\le N$. Cho mảng hiệu $D$ gồm $N$ phần tử, hãy khôi phục dãy $A$.

### Dữ liệu vào

Dòng đầu chứa số nguyên $T$ là số bộ test. Dữ liệu của mỗi bộ test được ghi theo định dạng sau.

- Dòng thứ nhất chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $D_1,D_2,\ldots,D_N$.

### Dữ liệu ra

In kết quả của các bộ test theo thứ tự đầu vào. Với mỗi bộ test, in trên một dòng $N$ phần tử của dãy $A$ theo thứ tự.

### Ràng buộc

- $1\le T\le 10^4$.
- $1\le N\le 2\cdot 10^5$.
- Tổng kích thước trên tất cả các bộ test thỏa $\sum_{i=1}^{T} N_i \le 2\cdot 10^5$.
- $|D_i|\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
2
5
3 0 -5 6 0
1
-5
```

### Sample Output 1

```text
3 3 -2 4 4
-5
```

### Sample Input 2

```text
1
4
1000000000 1000000000 1000000000 -1000000000
```

### Sample Output 2

```text
1000000000 2000000000 3000000000 2000000000
```

### Giải thích

Trong ví dụ 1, cộng lần lượt các phần tử của mảng hiệu ở bộ thứ nhất cho các tổng $3,3,-2,4,4$. Bộ thứ hai cho dãy $(-5)$.

Trong ví dụ 2, ba phần tử đầu làm tổng tăng lên $3\cdot10^9$. Phần tử cuối của mảng hiệu làm tổng giảm xuống $2\cdot10^9$.
