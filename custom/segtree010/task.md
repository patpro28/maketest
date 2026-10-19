# SEGTREE010 — Bảng đèn

### Đề bài

Một bảng có $N$ bóng đèn xếp thành một hàng, được đánh số từ $1$ đến $N$. Trạng thái ban đầu của đèn $i$ là $A_i$: $0$ nghĩa là tắt, $1$ nghĩa là sáng.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i`: đảo trạng thái của đèn $i$; đèn đang tắt chuyển sang sáng, đèn đang sáng chuyển sang tắt.
- `2 l r`: đếm số đèn đang sáng trong các vị trí từ $l$ đến $r$.

Mỗi truy vấn sử dụng trạng thái sau tất cả thao tác đảo trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả trạng thái ban đầu của các đèn.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa số đèn đang sáng trong đoạn được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $A_i\in\{0,1\}$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5 7
0 1 0 1 1
2 1 5
1 3
2 2 4
1 2
2 1 3
1 3
2 3 3
```

### Sample Output 1

```text
3
3
1
0
```

### Sample Input 2

```text
1 5
0
2 1 1
1 1
2 1 1
1 1
2 1 1
```

### Sample Output 2

```text
0
1
0
```

### Giải thích

Ở ví dụ 1, ban đầu có $3$ đèn sáng. Sau khi đảo đèn $3$, cả ba đèn trong đoạn $[2,4]$ đều sáng. Sau khi đảo đèn $2$, chỉ đèn $3$ sáng trong đoạn $[1,3]$. Đảo đèn $3$ thêm một lần làm đèn này tắt.

Ở ví dụ 2, đèn duy nhất lần lượt ở trạng thái tắt, sáng rồi tắt tại ba thời điểm truy vấn.
