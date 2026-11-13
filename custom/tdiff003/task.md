# TDIFF003 — Các đoạn bằng nhau

### Đề bài

Mảng hiệu $D$ của dãy $A$ được xác định bởi $D_1=A_1$ và $D_i=A_i-A_{i-1}$ với $2\le i\le N$.

Cho mảng hiệu $D$ gồm $N$ phần tử. Hãy liệt kê các đoạn liên tiếp tối đại của $A$ mà mọi phần tử trong mỗi đoạn đều bằng nhau. Một đoạn là tối đại nếu mở rộng sang trái hoặc sang phải trong phạm vi dãy sẽ làm đoạn chứa hai giá trị khác nhau.

### Dữ liệu vào

Dòng đầu chứa số nguyên $T$ là số bộ test. Dữ liệu của mỗi bộ test được ghi theo định dạng sau.

- Dòng thứ nhất chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $D_1,D_2,\ldots,D_N$.

### Dữ liệu ra

In kết quả của các bộ test theo thứ tự đầu vào. Với mỗi bộ test, in số đoạn trên một dòng. Sau đó, với mỗi đoạn $[L,R]$, in $L$ và $R$ trên một dòng. Liệt kê các đoạn theo thứ tự tăng dần của $L$.

### Ràng buộc

- $1\le T\le 10^4$.
- $1\le N\le 2\cdot 10^5$.
- Tổng kích thước trên tất cả các bộ test thỏa $\sum_{i=1}^{T} N_i \le 2\cdot 10^5$.
- $|D_i|\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
2
6
4 0 -2 0 0 2
1
0
```

### Sample Output 1

```text
3
1 2
3 5
6 6
1
1 1
```

### Sample Input 2

```text
1
4
-3 0 0 0
```

### Sample Output 2

```text
1
1 4
```

### Giải thích

Trong ví dụ 1, bộ thứ nhất khôi phục thành dãy $(4,4,2,2,2,4)$. Ba đoạn tối đại là $[1,2]$, $[3,5]$ và $[6,6]$. Bộ thứ hai chỉ có đoạn $[1,1]$.

Trong ví dụ 2, mọi phần tử của dãy đều bằng $-3$, nên cả dãy là một đoạn.
