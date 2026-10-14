# KNAPSACK13 — Mua vé đạt đủ điểm

### Đề bài

Một lễ hội có $N$ hoạt động. Vé tham gia hoạt động $i$ có giá $C_i$ đồng và đem lại $P_i$ điểm thưởng.

Mỗi hoạt động chỉ được tham gia tối đa một lần. Bạn cần tích lũy **ít nhất** $X$ điểm thưởng. Hãy tìm tổng số tiền nhỏ nhất cần trả. Nếu không thể đạt đủ điểm dù mua tất cả vé, hãy báo không thể.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,X$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $C_i,P_i$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất; in `-1` nếu không thể đạt ít nhất $X$ điểm.

### Ràng buộc

- $1\le N\le200$; $1\le X\le20000$.
- $1\le C_i\le10^9$; $1\le P_i\le20000$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $X\le2000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3 10
5 6
4 4
8 10
```

### Sample Output 1

```text
8
```

### Sample Input 2

```text
2 10
1 3
2 4
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, mua vé hoạt động thứ ba tốn $8$ đồng và nhận đúng $10$ điểm. Mua hai vé đầu tốn $9$ đồng. Ở ví dụ 2, tổng điểm của cả hai hoạt động chỉ bằng $7$.
