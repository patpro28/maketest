# TDIFF004 — Cộng vào cuối dãy

### Đề bài

Mảng hiệu $D$ của dãy $A$ được xác định bởi $D_1=A_1$ và $D_i=A_i-A_{i-1}$ với $2\le i\le N$.

Cho mảng hiệu $D$ của dãy $A$ và hai số $L,X$. Cộng $X$ vào mọi phần tử của dãy $A$ từ vị trí $L$ đến hết dãy. Hãy in mảng hiệu của dãy sau cập nhật.

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

**Ví dụ 1, bộ test thứ nhất**

1. Từ $D=(2,0,-1,3,0)$, cộng dồn từ trái sang phải được $A=(2,2,1,4,4)$.
2. Cộng $4$ vào các phần tử từ vị trí $3$ đến vị trí $5$, được $A=(2,2,5,8,8)$.
3. Lấy phần tử đầu và các hiệu giữa hai phần tử kề nhau, được $D=(2,2-2,5-2,8-5,8-8)=(2,0,3,3,0)$.

**Ví dụ 1, bộ test thứ hai**

1. Từ $D=(-5)$, khôi phục được $A=(-5)$.
2. Cộng $-2$ vào phần tử duy nhất, được $A=(-7)$.
3. Mảng hiệu chỉ có phần tử đầu, nên $D=(-7)$.

**Ví dụ 2**

1. Từ $D=(4,-1,2)$, cộng dồn được $A=(4,3,5)$.
2. Cộng $5$ vào các phần tử từ vị trí $1$ đến vị trí $3$, được $A=(9,8,10)$.
3. Lấy phần tử đầu và các hiệu giữa hai phần tử kề nhau, được $D=(9,8-9,10-8)=(9,-1,2)$.
