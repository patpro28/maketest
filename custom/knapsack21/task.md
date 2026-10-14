# KNAPSACK21 — Đổi tiền tối ưu có bao nhiêu cách?

### Đề bài

Có $N$ mệnh giá tiền đôi một khác nhau $A_1,\ldots,A_N$, mỗi mệnh giá có số đồng tiền không giới hạn.

Bạn cần đổi **đúng** $X$ đồng bằng số đồng tiền ít nhất. Hãy tìm số đồng tiền ít nhất và số cách đổi đạt số lượng ít nhất đó.

Một cách đổi được xác định bởi số đồng tiền dùng ở từng mệnh giá, không phân biệt thứ tự. Số cách được lấy modulo $10^9+7$. Khi $X=0$, có đúng một cách không dùng đồng nào.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,X$.
- Dòng thứ hai chứa $N$ mệnh giá $A_1,\ldots,A_N$.

### Dữ liệu ra

In hai số: số đồng tiền ít nhất và số cách đạt số lượng đó modulo $10^9+7$. Nếu không thể đổi, in `-1 0`.

### Ràng buộc

- $1\le N\le100$; $0\le X\le20000$.
- $1\le A_i\le20000$; các mệnh giá đôi một khác nhau.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le5$, $X\le20$ |
| 2 | 30% | $X\le2000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
4 6
1 2 3 4
```

### Sample Output 1

```text
2 2
```

### Sample Input 2

```text
2 5
4 6
```

### Sample Output 2

```text
-1 0
```

### Giải thích

Ở ví dụ 1, hai cách tối ưu là $2+4$ và $3+3$, đều dùng hai đồng. $4+2$ không là cách mới. Ở ví dụ 2, mọi tổng đổi được đều chẵn.
