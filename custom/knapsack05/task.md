# KNAPSACK05 — Chọn đồ vào túi

### Đề bài

Có $N$ loại đồ vật. Mỗi đồ vật thuộc loại $i$ có trọng lượng $W_i$ và giá trị $V_i$. Mỗi loại có số lượng **không giới hạn**, nên bạn được lấy nhiều đồ vật cùng loại.

Bạn có một chiếc túi chịu được tổng trọng lượng tối đa $C$. Hãy tìm tổng giá trị lớn nhất của các đồ vật được chọn, sao cho tổng trọng lượng **không vượt quá** $C$.

Bạn được phép không lấy đồ vật nào, khi đó tổng trọng lượng và tổng giá trị đều bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,C$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $W_i,V_i$.

### Dữ liệu ra

In tổng giá trị lớn nhất có thể đạt được.

### Ràng buộc

- $1\le N\le100$; $0\le C\le10000$.
- $1\le W_i\le10000$; $1\le V_i\le10^9$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le5$, $C\le20$ |
| 2 | 30% | $C\le1000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
2 5
2 5
3 1
```

### Sample Output 1

```text
10
```

### Sample Input 2

```text
1 0
1 9
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, lấy hai đồ vật loại thứ nhất: tổng trọng lượng $2+2=4\le5$, tổng giá trị $5+5=10$. Không bắt buộc lấp đầy túi. Ở ví dụ 2, sức chứa bằng $0$ nên không lấy đồ vật nào.
