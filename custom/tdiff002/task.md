# TDIFF002 — Khôi phục từ một mốc

### Đề bài

Dãy số nguyên $A$ gồm $N$ phần tử chưa được biết đầy đủ. Bạn biết giá trị $A_K$ tại vị trí $K$ và các chênh lệch $D_i=A_i-A_{i-1}$ với $2\le i\le N$.

Hãy khôi phục toàn bộ dãy $A$.

### Dữ liệu vào

Dòng đầu chứa số nguyên $T$ là số bộ test. Dữ liệu của mỗi bộ test được ghi theo định dạng sau.

- Dòng thứ nhất chứa ba số nguyên $N,K,A_K$.
- Nếu $N>1$, dòng thứ hai chứa $N-1$ số nguyên $D_2,D_3,\ldots,D_N$. Nếu $N=1$, bộ test chỉ có dòng thứ nhất.

### Dữ liệu ra

In kết quả của các bộ test theo thứ tự đầu vào. Với mỗi bộ test, in trên một dòng $N$ phần tử của dãy $A$ theo thứ tự.

### Ràng buộc

- $1\le T\le 10^4$.
- $1\le N\le 2\cdot 10^5$.
- Tổng kích thước trên tất cả các bộ test thỏa $\sum_{i=1}^{T} N_i \le 2\cdot 10^5$.
- $1\le K\le N$, $|A_K|\le10^9$. Nếu $N>1$, $|D_i|\le10^9$ với mọi $2\le i\le N$.

### Sample Input 1

```text
2
5 3 4
2 -3 0 7
1 1 -8
```

### Sample Output 1

```text
5 7 4 4 11
-8
```

### Sample Input 2

```text
1
4 4 -2
3 -4 2
```

### Sample Output 2

```text
-3 0 -4 -2
```

### Giải thích

Trong ví dụ 1, ở bộ thứ nhất, từ $A_3=4$ suy ra $A_2=4-(-3)=7$ và $A_1=7-2=5$. Đi sang phải thu được $A_4=4$ và $A_5=11$. Bộ thứ hai cho trực tiếp phần tử duy nhất là $-8$.

Trong ví dụ 2, từ $A_4=-2$ lần lượt suy ra $A_3=-4$, $A_2=0$ và $A_1=-3$.
