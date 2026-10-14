# KNAPSACK17 — Được phép sửa một món đồ

### Đề bài

Có $N$ món đồ, món $i$ có trọng lượng $W_i$ và giá trị $V_i$. Bạn chọn một tập các món đồ để cho vào túi có sức chứa $C$; mỗi món chỉ được chọn tối đa một lần.

Bạn bắt buộc sửa **đúng một món trong các món được chọn**. Món được sửa giữ nguyên giá trị nhưng có trọng lượng mới là $\lfloor W_i/2\rfloor$. Các món được chọn khác giữ nguyên trọng lượng.

Hãy tìm tổng giá trị lớn nhất có thể đạt được với tổng trọng lượng sau khi sửa không vượt $C$. Nếu không có phương án thỏa mãn yêu cầu sửa đúng một món, hãy báo không thể.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,C$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $W_i,V_i$.

### Dữ liệu ra

In tổng giá trị lớn nhất; in `-1` nếu không có phương án hợp lệ.

### Ràng buộc

- $1\le N\le200$; $0\le C\le20000$.
- $1\le W_i\le40000$; $1\le V_i\le10^9$.
- Khi $W_i=1$, món được sửa có trọng lượng bằng $0$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $C\le2000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3 5
6 10
4 8
2 5
```

### Sample Output 1

```text
15
```

### Sample Input 2

```text
1 0
2 7
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, chọn món thứ nhất sau khi sửa và món thứ ba giữ nguyên: trọng lượng $3+2=5$, giá trị $10+5=15$. Ở ví dụ 2, món duy nhất sau khi sửa vẫn nặng $1$, vượt sức chứa $0$.
