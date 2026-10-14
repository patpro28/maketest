# KNAPSACK03 — Đếm số cách chọn đạt đúng tổng

### Đề bài

Cho $N$ số nguyên dương $A_1,A_2,\ldots,A_N$ và một số nguyên không âm $X$.

Hãy đếm số tập chỉ số $S\subseteq\{1,2,\ldots,N\}$ thỏa mãn:

$$\sum_{i\in S} A_i=X.$$

Mỗi vị trí chỉ được chọn tối đa một lần. Hai cách chọn khác nhau nếu tập chỉ số được chọn khác nhau, kể cả khi các số có cùng giá trị. Không phân biệt thứ tự chọn các phần tử.

Tập rỗng có tổng bằng $0$ và được tính là một cách chọn. Vì kết quả có thể rất lớn, hãy lấy kết quả theo modulo $10^9+7$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,X$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In số cách chọn đạt đúng tổng $X$, lấy modulo $10^9+7$.

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
3 2
2 2 3
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3 0
1 2 3
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, hai cách chọn là tập chỉ số $\{1\}$ và $\{2\}$; không thể gộp hai số $2$ thành một lựa chọn. Ở ví dụ 2, chỉ có tập rỗng đạt tổng $0$.
