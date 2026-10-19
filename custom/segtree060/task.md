# SEGTREE060 — Điểm cao nhất

### Đề bài

Có $N$ học sinh được đánh số từ $1$ đến $N$. Học sinh thứ $i$ đang có điểm $A_i$; điểm có thể âm do bị trừ điểm.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: sửa điểm của học sinh $i$ thành $x$.
- `2 l r`: trong các học sinh từ $l$ đến $r$, tìm điểm cao nhất và đếm số học sinh đạt điểm đó.

Các học sinh được tính riêng biệt dù có cùng điểm. Mỗi truy vấn sử dụng các điểm sau tất cả thao tác sửa trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả điểm ban đầu của các học sinh.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng gồm hai số nguyên: điểm cao nhất và số học sinh đạt điểm đó trong đoạn được hỏi. Hai số cách nhau một dấu cách. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $-10^9\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
6 7
5 9 9 3 9 1
2 1 6
2 3 4
1 4 9
2 2 5
1 2 -4
2 1 3
2 6 6
```

### Sample Output 1

```text
9 3
9 1
9 4
9 1
1 1
```

### Sample Input 2

```text
3 5
-5 -2 -2
2 1 3
1 2 -7
2 1 2
1 3 -5
2 1 3
```

### Sample Output 2

```text
-2 2
-5 1
-5 2
```

### Giải thích

Ở ví dụ 1, ban đầu ba học sinh $2,3,5$ cùng đạt điểm cao nhất là $9$. Sau khi sửa điểm học sinh $4$ thành $9$, cả bốn học sinh trong đoạn $[2,5]$ đều đạt $9$. Khi điểm học sinh $2$ đổi thành $-4$, trong đoạn $[1,3]$ chỉ học sinh $3$ đạt điểm cao nhất. Truy vấn cuối chỉ xét một học sinh.

Ở ví dụ 2, truy vấn đầu có điểm cao nhất $-2$ xuất hiện hai lần. Sau các lần sửa, hai truy vấn còn lại lần lượt có điểm cao nhất $-5$ xuất hiện một lần và hai lần.
