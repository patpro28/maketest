# KNAPSACK09 — Chọn đồ lấp đầy túi

### Đề bài

Có $N$ loại đồ vật. Mỗi đồ vật thuộc loại $i$ có trọng lượng $W_i$ và giá trị $V_i$. Mỗi loại có số lượng **không giới hạn**, nên bạn được lấy nhiều đồ vật cùng loại.

Bạn cần chọn các đồ vật có tổng trọng lượng **đúng bằng** $C$. Trong các phương án thỏa mãn điều kiện này, hãy tìm tổng giá trị lớn nhất. Nếu không thể đạt đúng trọng lượng yêu cầu, hãy báo không thể.

Bạn được phép không lấy đồ vật nào. Phương án này có trọng lượng và giá trị bằng $0$, chỉ thỏa yêu cầu khi $C=0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,C$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $W_i,V_i$.

### Dữ liệu ra

In tổng giá trị lớn nhất khi tổng trọng lượng đúng bằng $C$; in `-1` nếu không có phương án hợp lệ.

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
6
```

### Sample Input 2

```text
1 3
2 7
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, lấy một đồ vật mỗi loại: trọng lượng $2+3=5$, giá trị $5+1=6$. Hai đồ vật loại thứ nhất có giá trị $10$ nhưng trọng lượng chỉ bằng $4$, không đạt đúng yêu cầu. Ở ví dụ 2, mọi trọng lượng tạo được đều chẵn nên không thể bằng $3$.
