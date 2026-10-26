# SEGTREE011 — Kho hàng

### Đề bài

Có $N$ kho hàng được đánh số từ $1$ đến $N$. Ban đầu, kho $i$ có $A_i$ đơn vị hàng.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: đặt lượng hàng tại kho $i$ thành $x$. Lượng hàng cũ được thay thế hoàn toàn.
- `2 l r`: tính tổng lượng hàng trong các kho từ $l$ đến $r$.

Mỗi truy vấn sử dụng lượng hàng sau tất cả thao tác cập nhật trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả lượng hàng ban đầu của từng kho.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa tổng lượng hàng trong đoạn được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
5 6
2 0 7 3 4
2 1 5
1 2 6
2 2 4
1 3 0
2 1 3
2 3 3
```

### Sample Output 1

```text
16
16
8
0
```

### Sample Input 2

```text
2 5
1000000000 1000000000
2 1 2
1 1 0
2 1 2
1 2 1000000000
2 2 2
```

### Sample Output 2

```text
2000000000
1000000000
1000000000
```

### Giải thích

Ở ví dụ 1, tổng lượng hàng ban đầu là $16$. Sau khi đặt lượng hàng ở kho $2$ thành $6$, đoạn $[2,4]$ có tổng $6+7+3=16$. Khi kho $3$ được đặt về $0$, đoạn $[1,3]$ có tổng $2+6+0=8$. Kho $3$ không còn hàng.

Ở ví dụ 2, lần cập nhật kho $2$ giữ nguyên lượng hàng của kho này; đây là phép gán, không phải cộng thêm.
