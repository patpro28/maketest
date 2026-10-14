# KNAPSACK02 — Chọn ít thẻ nhất

### Đề bài

Có $N$ tấm thẻ, thẻ thứ $i$ ghi số nguyên dương $A_i$. Bạn cần chọn một tập các thẻ sao cho tổng các số ghi trên thẻ **đúng bằng** $X$.

Mỗi thẻ chỉ được chọn tối đa một lần. Những thẻ ghi cùng số vẫn là các thẻ riêng biệt.

Hãy tìm số thẻ ít nhất cần chọn. Nếu không thể đạt đúng tổng $X$, hãy báo không thể. Bạn được phép không chọn thẻ nào khi $X=0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,X$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In số thẻ ít nhất cần chọn; in `-1` nếu không có phương án hợp lệ.

### Ràng buộc

- $1\le N\le200$; $0\le X\le10000$.
- $1\le A_i\le10000$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $X\le1000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
4 10
2 3 5 10
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
3 7
2 4 6
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, chỉ cần chọn thẻ thứ tư ghi số $10$. Ở ví dụ 2, không có tập thẻ nào có tổng bằng $7$.
