# KNAPSACK00 — Chọn đồ vào túi

### Đề bài

Có $N$ món đồ, món thứ $i$ có trọng lượng $W_i$ và giá trị $V_i$. Bạn có một chiếc túi chịu được tổng trọng lượng tối đa $C$.

Bạn được chọn một tập các món đồ để cho vào túi. Mỗi món chỉ được chọn tối đa một lần. Hai món có thông số giống nhau vẫn là hai món riêng biệt.

Hãy tìm tổng giá trị lớn nhất của các món được chọn, sao cho tổng trọng lượng **không vượt quá** $C$. Bạn được phép không chọn món nào, khi đó tổng trọng lượng và tổng giá trị đều bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,C$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $W_i,V_i$.

### Dữ liệu ra

In tổng giá trị lớn nhất có thể đạt được.

### Ràng buộc

- $1\le N\le200$; $0\le C\le10000$.
- $1\le W_i\le10000$; $1\le V_i\le10^9$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $C\le1000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3 5
2 3
3 4
4 10
```

### Sample Output 1

```text
10
```

### Sample Input 2

```text
2 1
2 7
4 20
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, chọn món thứ ba có trọng lượng $4\le5$ và giá trị $10$. Chọn hai món đầu chỉ được giá trị $7$. Ở ví dụ 2, mọi món đều nặng hơn sức chứa của túi nên chỉ có thể không chọn món nào.
