# TDIFF006 — Hai đầu mút

### Đề bài

Mảng hiệu $D$ của dãy $A$ được xác định bởi $D_1=A_1$ và $D_i=A_i-A_{i-1}$ với $2\le i\le N$.

Cho mảng hiệu $D$ của dãy $A$ và một phép cộng $X$ vào mọi phần tử của đoạn $[L,R]$. Hãy in mảng hiệu của dãy sau cập nhật.

### Dữ liệu vào

Dòng đầu chứa số nguyên $T$ là số bộ test. Dữ liệu của mỗi bộ test được ghi theo định dạng sau.

- Dòng thứ nhất chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $D_1,D_2,\ldots,D_N$.
- Dòng thứ ba chứa ba số nguyên $L,R,X$.

### Dữ liệu ra

In kết quả của các bộ test theo thứ tự đầu vào. Với mỗi bộ test, in trên một dòng $N$ phần tử của mảng hiệu sau cập nhật theo thứ tự.

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
3 4 2 0 -9
5
```

### Sample Input 2

```text
1
4
2 1 -1 4
3 4 -2
```

### Sample Output 2

```text
2 1 -3 4
```

### Giải thích

**Ví dụ 1, bộ test thứ nhất**

1. Cộng dồn $D=(3,-1,2,0,-4)$ được $A=(3,2,4,4,0)$.
2. Cộng $5$ vào các phần tử từ vị trí $2$ đến vị trí $4$, được $A=(3,7,9,9,0)$.
3. Tính lại mảng hiệu, được $D=(3,7-3,9-7,9-9,0-9)=(3,4,2,0,-9)$.

**Ví dụ 1, bộ test thứ hai**

1. Từ $D=(8)$, khôi phục được $A=(8)$.
2. Cộng $-3$ vào phần tử duy nhất, được $A=(5)$.
3. Mảng hiệu chỉ có phần tử đầu, nên $D=(5)$.

**Ví dụ 2**

1. Cộng dồn $D=(2,1,-1,4)$ được $A=(2,3,2,6)$.
2. Cộng $-2$ vào các phần tử ở vị trí $3$ và $4$, được $A=(2,3,0,4)$.
3. Tính lại mảng hiệu, được $D=(2,3-2,0-3,4-0)=(2,1,-3,4)$.
