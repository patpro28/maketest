# TDIFF005 — Đổi một phần tử

### Đề bài

Mảng hiệu $D$ của dãy $A$ được xác định bởi $D_1=A_1$ và $D_i=A_i-A_{i-1}$ với $2\le i\le N$.

Cho mảng hiệu $D$ của dãy $A$ và hai số $P,X$. Thay giá trị tại vị trí $P$ bằng $X$. Hãy in mảng hiệu của dãy sau cập nhật.

### Dữ liệu vào

Dòng đầu chứa số nguyên $T$ là số bộ test. Dữ liệu của mỗi bộ test được ghi theo định dạng sau.

- Dòng thứ nhất chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $D_1,D_2,\ldots,D_N$.
- Dòng thứ ba chứa hai số nguyên $P,X$.

### Dữ liệu ra

In kết quả của các bộ test theo thứ tự đầu vào. Với mỗi bộ test, in trên một dòng $N$ phần tử của mảng hiệu sau cập nhật theo thứ tự.

### Ràng buộc

- $1\le T\le 10^4$.
- $1\le N\le 2\cdot 10^5$.
- Tổng kích thước trên tất cả các bộ test thỏa $\sum_{i=1}^{T} N_i \le 2\cdot 10^5$.
- $|D_i|\le10^9$ với mọi $1\le i\le N$.
- $1\le P\le N$, $|X|\le10^9$.

### Sample Input 1

```text
2
5
2 3 -1 4 0
3 7
2
1 -2
2 0
```

### Sample Output 1

```text
2 3 2 1 0
1 -1
```

### Sample Input 2

```text
1
4
1000000000 1000000000 1000000000 1000000000
3 -1000000000
```

### Sample Output 2

```text
1000000000 1000000000 -3000000000 5000000000
```

### Giải thích

Trong ví dụ 1, ở bộ thứ nhất, $A_3=4$ được đổi thành $7$, nên $D_3$ tăng $3$ và $D_4$ giảm $3$. Ở bộ thứ hai, phần tử cuối được đổi từ $-1$ thành $0$, nên $D_2$ tăng $1$.

Trong ví dụ 2, $A_3=3\cdot10^9$ được đổi thành $-10^9$. Do đó $D_3$ giảm $4\cdot10^9$ và $D_4$ tăng $4\cdot10^9$.
