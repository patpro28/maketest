# KNAPSACK11 — Hai tuyến xe buýt

### Đề bài

Có $N$ nhóm học sinh đang chờ lên xe. Nhóm $i$ cần $T_i$ phút để hoàn tất việc lên xe.

Hai xe buýt bắt đầu phục vụ cùng lúc tại thời điểm $0$. Mỗi xe phục vụ lần lượt các nhóm được giao cho mình; hai xe có thể phục vụ song song. Mỗi nhóm phải được giao hoàn toàn cho đúng một xe. Có thể không giao nhóm nào cho một xe, khi đó xe ấy hoàn thành ở thời điểm $0$.

Hãy tìm thời điểm sớm nhất mà tất cả các nhóm đã lên xe.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $T_1,T_2,\ldots,T_N$.

### Dữ liệu ra

In một số nguyên: thời điểm hoàn thành nhỏ nhất.

### Ràng buộc

- $1\le N\le200$.
- $1\le T_i\le20000$; $\sum T_i\le20000$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $\sum T_i\le2000$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
4
2 3 7 8
```

### Sample Output 1

```text
10
```

### Sample Input 2

```text
1
9
```

### Sample Output 2

```text
9
```

### Giải thích

Ở ví dụ 1, giao các nhóm cần $2,8$ phút cho xe thứ nhất và các nhóm cần $3,7$ phút cho xe thứ hai. Cả hai xe hoàn thành ở thời điểm $10$. Ở ví dụ 2, nhóm duy nhất cần $9$ phút.
