# TDIFF007 — Dãy sau một lần cộng

### Đề bài

Mảng hiệu $D$ của dãy $A$ được xác định bởi $D_1=A_1$ và $D_i=A_i-A_{i-1}$ với $2\le i\le N$.

Cho mảng hiệu $D$ của dãy $A$ và một phép cộng $X$ vào mọi phần tử của đoạn $[L,R]$. Hãy in các phần tử của dãy $A$ sau cập nhật.

### Dữ liệu vào

Dòng đầu chứa số nguyên $T$ là số bộ test. Dữ liệu của mỗi bộ test được ghi theo định dạng sau.

- Dòng thứ nhất chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $D_1,D_2,\ldots,D_N$.
- Dòng thứ ba chứa ba số nguyên $L,R,X$.

### Dữ liệu ra

In kết quả của các bộ test theo thứ tự đầu vào. Với mỗi bộ test, in trên một dòng $N$ phần tử của dãy $A$ sau cập nhật theo thứ tự.

### Ràng buộc

- $1\le T\le 10^4$.
- $1\le N\le 2\cdot 10^5$.
- Tổng kích thước trên tất cả các bộ test thỏa $\sum_{i=1}^{T} N_i \le 2\cdot 10^5$.
- $|D_i|\le10^9$ với mọi $1\le i\le N$.
- $1\le L\le R\le N$, $|X|\le10^9$.

### Sample Input 1

```text
2
5
3 -1 2 0 -4
2 4 5
1
8
1 1 -3
```

### Sample Output 1

```text
3 7 9 9 0
5
```

### Sample Input 2

```text
1
4
1000000000 1000000000 1000000000 1000000000
1 4 1000000000
```

### Sample Output 2

```text
2000000000 3000000000 4000000000 5000000000
```

### Giải thích

Trong ví dụ 1, dãy gốc ở bộ thứ nhất là $(3,2,4,4,0)$. Cộng $5$ vào $[2,4]$ thu được $(3,7,9,9,0)$. Ở bộ thứ hai, phần tử duy nhất giảm từ $8$ xuống $5$.

Trong ví dụ 2, dãy gốc có các giá trị $10^9,2\cdot10^9,3\cdot10^9,4\cdot10^9$. Mỗi giá trị tăng thêm $10^9$.
