# KNAPSACK01 — Chọn các số có tổng cho trước

### Đề bài

Cho $N$ số nguyên dương $A_1,A_2,\ldots,A_N$ và một số nguyên không âm $X$.

Bạn được chọn một tập các vị trí trong dãy, mỗi vị trí chỉ được chọn tối đa một lần. Hãy xác định có thể làm cho tổng các số ở những vị trí được chọn **đúng bằng** $X$ hay không.

Các vị trí có cùng giá trị vẫn có thể được chọn độc lập. Bạn được phép chọn tập rỗng, có tổng bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,X$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In `YES` nếu có thể đạt đúng tổng $X$, ngược lại in `NO`.

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
4 9
2 3 4 7
```

### Sample Output 1

```text
YES
```

### Sample Input 2

```text
3 7
2 4 6
```

### Sample Output 2

```text
NO
```

### Giải thích

Ở ví dụ 1, chọn các vị trí $1,4$ có tổng $2+7=9$. Ở ví dụ 2, mọi tổng có thể tạo đều chẵn nên không thể bằng $7$.
