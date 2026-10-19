# SEGTREE090 — Các cụm màu liên tiếp

### Đề bài

Có $N$ ô xếp thành một hàng, được đánh số từ $1$ đến $N$. Màu ban đầu của ô $i$ được biểu diễn bằng số nguyên $A_i$. Hai ô có cùng số biểu diễn thì có cùng màu.

Trong một đoạn, một **cụm màu** là một nhóm ô liên tiếp cùng màu và không thể mở rộng thêm sang trái hoặc sang phải trong đoạn đó mà vẫn giữ nguyên màu. Chẳng hạn, đoạn có các màu $1,1,2,2,1$ gồm $3$ cụm. Các cụm cùng màu nhưng không nằm liền nhau vẫn được tính riêng.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: đổi màu ô $i$ thành $x$.
- `2 l r`: đếm số cụm màu trong đoạn từ ô $l$ đến ô $r$. Chỉ xét các ô bên trong đoạn này.

Mỗi truy vấn sử dụng các màu sau tất cả thao tác đổi trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả màu ban đầu của các ô.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa số cụm màu trong đoạn được hỏi. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 100% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
7 7
1 1 2 2 1 3 3
2 1 7
2 2 5
1 5 2
2 1 7
1 6 2
2 3 7
2 4 4
```

### Sample Output 1

```text
4
3
3
2
1
```

### Sample Input 2

```text
3 5
8 9 8
2 1 3
1 2 8
2 1 3
1 1 9
2 2 3
```

### Sample Output 2

```text
3
1
1
```

### Giải thích

Ở ví dụ 1, ban đầu toàn hàng có các cụm $(1,1)$, $(2,2)$, $(1)$, $(3,3)$ nên đáp án đầu là $4$. Đoạn $[2,5]$ có các màu $1,2,2,1$ nên có $3$ cụm. Sau khi đổi màu ô $5$ thành $2$, toàn hàng còn $3$ cụm. Đổi tiếp màu ô $6$ thành $2$ làm đoạn $[3,7]$ có các màu $2,2,2,2,3$, gồm $2$ cụm. Đoạn chỉ có một ô luôn có $1$ cụm.

Ở ví dụ 2, ba ô ban đầu tạo thành $3$ cụm. Khi đổi màu ô giữa thành $8$, cả hàng hợp thành một cụm. Ở truy vấn cuối, đoạn $[2,3]$ vẫn chỉ có một cụm dù ô $1$ đã đổi màu.
