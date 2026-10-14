# KNAPSACK14 — Chia hai đội cân bằng

### Đề bài

Có $N$ học sinh, học sinh $i$ có sức mạnh $A_i$.

Bạn cần chia tất cả học sinh thành hai đội, mỗi học sinh thuộc đúng một đội. Số thành viên của hai đội phải chênh lệch không quá $1$.

Sức mạnh của một đội là tổng sức mạnh các thành viên. Hãy tìm chênh lệch nhỏ nhất giữa sức mạnh của hai đội.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In giá trị nhỏ nhất của chênh lệch tuyệt đối giữa sức mạnh hai đội.

### Ràng buộc

- $2\le N\le60$.
- $1\le A_i\le6000$; $\sum A_i\le6000$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 20% | $N\le20$ |
| 2 | 30% | $\sum A_i\le600$ |
| 3 | 50% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5
1 2 3 4 10
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
4
5 5 5 5
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, một đội gồm các học sinh có sức mạnh $1,10$, đội còn lại có sức mạnh $2,3,4$. Hai tổng bằng $11$ và $9$, chênh lệch $2$. Ở ví dụ 2, mỗi đội nhận hai học sinh.
