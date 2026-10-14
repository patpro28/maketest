# KNAPSACK20 — Phá khiên quái vật

### Đề bài

Có $N$ loại phép thuật. Một lần sử dụng phép loại $i$ tốn $C_i$ năng lượng và gây $D_i$ sát thương. Mỗi loại phép có thể được sử dụng không giới hạn số lần.

Quái vật có lớp khiên chịu được $H$ sát thương. Hãy tìm tổng năng lượng ít nhất cần sử dụng để gây **ít nhất** $H$ sát thương. Nếu $H=0$, không cần dùng phép nào.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,H$.
- Trong $N$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $C_i,D_i$.

### Dữ liệu ra

In tổng năng lượng ít nhất.

### Ràng buộc

- $1\le N\le100$; $0\le H\le20000$.
- $1\le C_i,D_i\le10^9$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le5$, $H\le20$ |
| 2 | 30% | $H\le2000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
2 10
5 6
8 10
```

### Sample Output 1

```text
8
```

### Sample Input 2

```text
1 5
3 2
```

### Sample Output 2

```text
9
```

### Giải thích

Ở ví dụ 1, dùng một phép loại thứ hai tốn $8$ năng lượng. Ở ví dụ 2, dùng phép duy nhất ba lần, gây $6\ge5$ sát thương và tốn $9$ năng lượng.
