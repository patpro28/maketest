# KNAPSACK07 — Đổi tiền với ít đồng nhất

### Đề bài

Có $N$ mệnh giá tiền $A_1,A_2,\ldots,A_N$. Mỗi mệnh giá có số đồng tiền **không giới hạn**.

Bạn cần chọn các đồng tiền có tổng giá trị **đúng bằng** $X$. Hãy tìm số đồng tiền ít nhất phải sử dụng. Nếu không thể đổi đúng số tiền cần thiết, hãy báo không thể.

Bạn được phép lấy nhiều đồng cùng mệnh giá. Khi $X=0$, không cần lấy đồng nào. Các mệnh giá được cho có thể trùng nhau; việc trùng mệnh giá không làm thay đổi số lượng tiền có thể sử dụng.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,X$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In số đồng tiền ít nhất cần sử dụng; in `-1` nếu không thể đổi đúng $X$ đồng.

### Ràng buộc

- $1\le N\le100$; $0\le X\le10000$.
- $1\le A_i\le10000$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le5$, $X\le20$ |
| 2 | 30% | $X\le1000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3 6
1 3 4
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
2 5
4 6
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, lấy hai đồng mệnh giá $3$ để được $3+3=6$. Cách tham lam lấy đồng $4$ trước sẽ phải dùng thêm hai đồng $1$, tổng cộng ba đồng. Ở ví dụ 2, mọi tổng tạo được đều chẵn nên không thể bằng $5$.
