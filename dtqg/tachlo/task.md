# TACHLO — Chia lô tránh xung đột

### Đề bài

Có $N$ kiện hàng xếp thành một dãy theo thứ tự từ $1$ đến $N$. Kiện thứ $i$ thuộc loại $A_i$.

Bạn phải chia toàn bộ dãy thành đúng $K$ đoạn liên tiếp không rỗng. Mỗi đoạn là một lô hàng; mỗi kiện thuộc đúng một lô. Không được thay đổi thứ tự các kiện.

Chi phí của một lô gồm các kiện từ $l$ đến $r$ là số cặp vị trí $(i,j)$ thỏa mãn

$$l\le i<j\le r,\qquad A_i=A_j.$$

Một cặp được tính một lần, dù hai kiện đứng cạnh nhau hay không. Hai kiện cùng loại nhưng thuộc hai lô khác nhau không gây chi phí.

Hãy tìm tổng chi phí nhỏ nhất khi chia dãy thành đúng $K$ lô.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,K$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất có thể đạt được.

### Ràng buộc

- $1\le N\le10^5$.
- $1\le K\le\min(20,N)$.
- $1\le A_i\le N$.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 30% | $N\le200$ |
| 2 | 30% | $N\le3000$ |
| 3 | 40% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5 2
1 1 2 1 2
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
6 3
4 4 4 4 4 4
```

### Sample Output 2

```text
3
```

### Sample Input 3

```text
4 4
2 2 2 2
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, chia thành $[1,1,2]$ và $[1,2]$. Lô đầu có một cặp cùng loại, lô sau không có cặp nào, tổng chi phí bằng $1$.

Ở ví dụ 2, chia thành ba lô, mỗi lô chứa hai kiện. Mỗi lô có một cặp cùng loại, tổng chi phí bằng $3$.

Ở ví dụ 3, mỗi kiện phải nằm trong một lô riêng, nên chi phí bằng $0$.
