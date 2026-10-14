# KNAPSACK08 — Đếm số cách đổi tiền

### Đề bài

Có $N$ mệnh giá tiền **đôi một khác nhau** $A_1,A_2,\ldots,A_N$. Mỗi mệnh giá có số đồng tiền **không giới hạn**.

Hãy đếm số cách đổi **đúng** $X$ đồng. Một cách đổi được xác định bởi số lượng đồng tiền sử dụng ở từng mệnh giá. Hai cách khác nhau nếu có ít nhất một mệnh giá được sử dụng với số lượng khác nhau. **Không phân biệt thứ tự** các đồng tiền.

Tương đương, đếm số bộ số nguyên không âm $(k_1,k_2,\ldots,k_N)$ thỏa mãn:

$$k_1A_1+k_2A_2+\cdots+k_NA_N=X.$$

Khi $X=0$, có đúng một cách là không lấy đồng tiền nào. Vì số cách có thể rất lớn, hãy lấy kết quả theo modulo $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,X$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In số cách đổi đúng $X$ đồng, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N\le100$; $0\le X\le10000$.
- $1\le A_i\le10000$.
- Các mệnh giá đôi một khác nhau.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le5$, $X\le20$ |
| 2 | 30% | $X\le1000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
2 3
1 2
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
2 0
2 5
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, hai cách là dùng ba đồng $1$, hoặc dùng một đồng $1$ và một đồng $2$. Viết $1+2$ hay $2+1$ vẫn là cùng một cách đổi. Ở ví dụ 2, chỉ có cách không lấy đồng nào.
