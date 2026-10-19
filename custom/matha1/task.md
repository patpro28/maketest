# MATHA1 — Chia hết và không chia hết

### Đề bài

Cho ba số nguyên dương $L,R,A$. Hãy đếm số nguyên $x$ trong đoạn $[L,R]$ (tính cả hai đầu mút) thỏa mãn đồng thời các điều kiện sau:

- $x$ chia hết cho $A$.
- $x$ không chia hết cho $2A$.

Bạn cần trả lời $T$ bộ dữ liệu độc lập.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $T$, là số bộ dữ liệu.
- Mỗi dòng trong $T$ dòng tiếp theo chứa ba số nguyên $L,R,A$ mô tả một bộ dữ liệu.

### Dữ liệu ra

In $T$ dòng. Dòng thứ $i$ chứa một số nguyên là số lượng số thỏa mãn yêu cầu trong bộ dữ liệu thứ $i$. Nếu không có số nào thỏa mãn, in $0$.

### Ràng buộc

- $1\le T\le10^5$.
- $1\le L\le R\le10^{18}$.
- $1\le A\le10^6$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 60% | $T=1$, $L,R\le10^6$ |
| 2 | 30% | $A=1$ |
| 3 | 10% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5
1 10 3
4 16 4
7 7 7
1 5 10
6 6 3
```

### Sample Output 1

```text
2
2
1
0
0
```

### Sample Input 2

```text
4
1 1000000000000000000 1
1000000000000000000 1000000000000000000 1
999999999999999999 1000000000000000000 1
1 1000000000000000000 1000000
```

### Sample Output 2

```text
500000000000000000
0
1
500000000000
```

### Giải thích

Ở ví dụ 1:

- Bộ dữ liệu 1: các số thỏa mãn là $3,9$, nên đáp án là $2$.
- Bộ dữ liệu 2: các số thỏa mãn là $4,12$, nên đáp án là $2$.
- Bộ dữ liệu 3: số $7$ chia hết cho $7$ nhưng không chia hết cho $14$, nên đáp án là $1$.
- Bộ dữ liệu 4: không có bội nào của $10$ trong đoạn $[1,5]$, nên đáp án là $0$.
- Bộ dữ liệu 5: số $6$ chia hết cho $2A=6$, nên không được tính.
