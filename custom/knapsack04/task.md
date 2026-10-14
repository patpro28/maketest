# KNAPSACK04 — Chọn đồ lấp đầy túi

### Đề bài

Có $N$ món đồ, món thứ $i$ có trọng lượng $W_i$ và giá trị $V_i$. Bạn cần chọn một tập các món đồ để cho vào túi, sao cho tổng trọng lượng **đúng bằng** $C$.

Mỗi món chỉ được chọn tối đa một lần. Hai món có thông số giống nhau vẫn là hai món riêng biệt.

Trong các phương án đạt đúng trọng lượng yêu cầu, hãy tìm tổng giá trị lớn nhất. Nếu không có phương án như vậy, hãy báo không thể. Bạn được phép chọn tập rỗng; phương án này có trọng lượng và giá trị bằng $0$, chỉ thỏa yêu cầu khi $C=0$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,C$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $W_i,V_i$.

### Dữ liệu ra

In tổng giá trị lớn nhất với tổng trọng lượng đúng bằng $C$; in `-1` nếu không có phương án hợp lệ.

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
7
```

### Sample Input 2

```text
2 3
2 7
4 20
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, chọn hai món đầu đạt trọng lượng $2+3=5$ và giá trị $3+4=7$. Món thứ ba tuy có giá trị $10$ nhưng chỉ nặng $4$, không lấp đầy đúng túi. Ở ví dụ 2, mọi tổng trọng lượng đều chẵn nên không thể bằng $3$.
