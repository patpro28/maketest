# SEGTREE071 — Sai số bình phương

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$. Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: gán $A_i=x$.
- `2 l r c`: tính tổng sai số bình phương so với mốc $c$ trên đoạn $[l,r]$, bằng $\displaystyle\sum_{i=l}^{r}(A_i-c)^2$.

Mốc $c$ có thể khác nhau ở mỗi truy vấn. Mỗi truy vấn sử dụng dãy sau tất cả thao tác gán trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các phần tử ban đầu của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r c`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa tổng sai số bình phương của đoạn được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N\le200000$; $1\le Q\le200000$.
- $-10^4\le A_i,x,c\le10^4$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
4 6
1 -2 3 0
2 1 4 0
2 1 3 2
1 2 2
2 1 3 2
1 4 -1
2 3 4 1
```

### Sample Output 1

```text
14
18
2
8
```

### Sample Input 2

```text
2 3
-10000 -10000
2 1 2 10000
1 1 10000
2 1 2 10000
```

### Sample Output 2

```text
800000000
400000000
```

### Giải thích

Ở ví dụ 1, truy vấn đầu tính $1^2+(-2)^2+3^2+0^2=14$. Với mốc $2$, ba phần tử đầu có tổng sai số $(1-2)^2+(-2-2)^2+(3-2)^2=18$. Sửa phần tử thứ $2$ thành $2$ làm tổng này còn $2$. Sau lần sửa tiếp theo, hai phần tử cuối là $3,-1$ và có tổng sai số so với mốc $1$ là $4+4=8$.

Ở ví dụ 2, mỗi giá trị $-10000$ lệch mốc $10000$ một lượng $20000$, có bình phương bằng $400000000$.
