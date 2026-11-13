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

**Ví dụ 1, bộ test thứ nhất**

1. Cộng dồn $D=(2,3,-1,4,0)$ được $A=(2,5,4,8,8)$.
2. Thay phần tử ở vị trí $3$ bằng $7$, được $A=(2,5,7,8,8)$.
3. Tính lại mảng hiệu, được $D=(2,5-2,7-5,8-7,8-8)=(2,3,2,1,0)$.

**Ví dụ 1, bộ test thứ hai**

1. Cộng dồn $D=(1,-2)$ được $A=(1,-1)$.
2. Thay phần tử ở vị trí $2$ bằng $0$, được $A=(1,0)$.
3. Tính lại mảng hiệu, được $D=(1,0-1)=(1,-1)$.

**Ví dụ 2**

1. Cộng dồn $D=(10^9,10^9,10^9,10^9)$ được $A=(10^9,2\cdot10^9,3\cdot10^9,4\cdot10^9)$.
2. Thay phần tử ở vị trí $3$ bằng $-10^9$, được $A=(10^9,2\cdot10^9,-10^9,4\cdot10^9)$.
3. Tính lại mảng hiệu, được $D=(10^9,10^9,-3\cdot10^9,5\cdot10^9)$. Hai hiệu cuối lần lượt là $-10^9-2\cdot10^9$ và $4\cdot10^9-(-10^9)$.
