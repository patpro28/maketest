# TDIFF004 — Cộng vào cuối dãy

### Đề bài

Mảng hiệu $D$ của dãy $A$ được xác định bởi $D_1=A_1$ và $D_i=A_i-A_{i-1}$ với $2\le i\le N$.

Cho mảng hiệu $D$ của dãy $A$ và hai số $L,X$. Cộng $X$ vào mọi phần tử từ vị trí $L$ đến hết dãy. Hãy in mảng hiệu của dãy sau cập nhật.

### Dữ liệu vào

Dòng đầu chứa số nguyên $T$ là số bộ test. Dữ liệu của mỗi bộ test được ghi theo định dạng sau.

- Dòng thứ nhất chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $D_1,D_2,\ldots,D_N$.
- Dòng thứ ba chứa hai số nguyên $L,X$.

### Dữ liệu ra

In kết quả của các bộ test theo thứ tự đầu vào. Với mỗi bộ test, in trên một dòng $N$ phần tử của mảng hiệu sau cập nhật theo thứ tự.

### Ràng buộc

- $1\le T\le 10^4$.
- $1\le N\le 2\cdot 10^5$.
- Tổng kích thước trên tất cả các bộ test thỏa $\sum_{i=1}^{T} N_i \le 2\cdot 10^5$.
- $|D_i|\le10^9$ với mọi $1\le i\le N$.
- $1\le L\le N$, $|X|\le10^9$.

### Sample Input 1

```text
2
5
2 0 -1 3 0
3 4
1
-5
1 -2
```

### Sample Output 1

```text
2 0 3 3 0
-7
```

### Sample Input 2

```text
1
3
4 -1 2
1 5
```

### Sample Output 2

```text
9 -1 2
```

### Giải thích

Trong ví dụ 1, ở bộ thứ nhất, cộng $4$ từ vị trí $3$ làm $D_3$ đổi từ $-1$ thành $3$. Ở bộ thứ hai, $D_1$ giảm từ $-5$ xuống $-7$.

Trong ví dụ 2, cộng $5$ vào cả dãy chỉ làm phần tử đầu của mảng hiệu tăng thêm $5$.
