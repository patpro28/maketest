# SEGTREE020 — Trạm đo nhiệt độ

### Đề bài

Có $N$ trạm đo nhiệt độ được đánh số từ $1$ đến $N$. Ban đầu, trạm thứ $i$ ghi nhận nhiệt độ $A_i$.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: sửa nhiệt độ tại trạm $i$ thành $x$.
- `2 l r`: xét các trạm từ $l$ đến $r$, in nhiệt độ thấp nhất, nhiệt độ cao nhất và độ chênh lệch giữa nhiệt độ cao nhất với nhiệt độ thấp nhất.

Mỗi truy vấn sử dụng các nhiệt độ sau tất cả thao tác sửa trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả nhiệt độ ban đầu của các trạm.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng gồm ba số nguyên theo thứ tự: nhiệt độ thấp nhất, nhiệt độ cao nhất và độ chênh lệch trong đoạn được hỏi. Các số cách nhau một dấu cách. Nếu không có thao tác loại $2$, không in gì.

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
5 6
3 -2 7 7 0
2 1 5
2 3 4
1 2 10
2 1 3
1 3 -5
2 2 5
```

### Sample Output 1

```text
-2 7 9
7 7 0
3 10 7
-5 10 15
```

### Sample Input 2

```text
1 4
-1000000000
2 1 1
1 1 1000000000
2 1 1
2 1 1
```

### Sample Output 2

```text
-1000000000 -1000000000 0
1000000000 1000000000 0
1000000000 1000000000 0
```

### Giải thích

Ở ví dụ 1, truy vấn đầu có nhiệt độ thấp nhất là $-2$, cao nhất là $7$ nên độ chênh lệch bằng $9$. Hai trạm trong truy vấn thứ hai đều có nhiệt độ $7$. Sau khi sửa trạm $2$, đoạn $[1,3]$ có các nhiệt độ $3,10,7$. Sau lần sửa tiếp theo, đoạn $[2,5]$ có các nhiệt độ $10,-5,7,0$.

Ở ví dụ 2, mọi đoạn được hỏi chỉ có một trạm nên độ chênh lệch luôn bằng $0$.
