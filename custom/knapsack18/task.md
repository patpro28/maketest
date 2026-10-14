# KNAPSACK18 — Ba bếp

### Đề bài

Có $N$ món ăn, món $i$ cần $T_i$ phút để nấu trên một bếp.

Bạn có ba bếp giống nhau, đều sẵn sàng tại thời điểm $0$. Mỗi món phải được nấu trọn vẹn trên đúng một bếp, không được chia nhỏ hoặc chuyển bếp. Mỗi bếp chỉ nấu được một món tại một thời điểm; các bếp có thể hoạt động song song. Một bếp có thể không được giao món nào.

Hãy tìm thời điểm sớm nhất mà tất cả các món đã nấu xong.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $T_1,T_2,\ldots,T_N$.

### Dữ liệu ra

In thời điểm hoàn thành nhỏ nhất.

### Ràng buộc

- $1\le N\le60$.
- $1\le T_i\le600$; $\sum T_i\le600$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le10$ |
| 2 | 30% | $\sum T_i\le100$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
4
2 3 4 5
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
1
7
```

### Sample Output 2

```text
7
```

### Giải thích

Ở ví dụ 1, bếp thứ nhất nấu các món cần $2,3$ phút, bếp thứ hai nấu món cần $4$ phút và bếp thứ ba nấu món cần $5$ phút. Tất cả xong sau $5$ phút. Ở ví dụ 2, món duy nhất vẫn cần $7$ phút.
