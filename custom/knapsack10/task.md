# KNAPSACK10 — Đặt dấu cộng hoặc trừ

### Đề bài

Cho $N$ số nguyên dương $A_1,A_2,\ldots,A_N$ và một số nguyên $X$.

Bạn phải đặt đúng một dấu `+` hoặc `-` trước **mỗi** số, kể cả số đầu tiên. Không được bỏ số nào hay thay đổi thứ tự các số.

Hãy xác định có thể thu được biểu thức có giá trị đúng bằng $X$ hay không.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,X$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In `YES` nếu tồn tại cách đặt dấu thỏa mãn, ngược lại in `NO`.

### Ràng buộc

- $1\le N\le200$.
- $1\le A_i\le20000$; $\sum A_i\le20000$.
- $-10^9\le X\le10^9$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $\sum A_i\le2000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3 0
1 2 3
```

### Sample Output 1

```text
YES
```

### Sample Input 2

```text
3 1
1 2 3
```

### Sample Output 2

```text
NO
```

### Giải thích

Ở ví dụ 1, $+1+2-3=0$. Ở ví dụ 2, mọi kết quả đều chẵn nên không thể bằng $1$.
