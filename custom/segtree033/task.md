# SEGTREE033 — Chu kỳ vượt giới hạn

### Đề bài

Có $N$ thiết bị được đánh số từ $1$ đến $N$. Chu kỳ ban đầu của thiết bị $i$ là số nguyên dương $A_i$. Cho trước một giới hạn nguyên dương $B$ cố định.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: đổi chu kỳ của thiết bị $i$ thành $x$.
- `2 l r`: tính bội chung nhỏ nhất (LCM) của các chu kỳ từ $l$ đến $r$. Nếu LCM không vượt quá $B$, in giá trị đó; nếu LCM lớn hơn $B$, in `-1`.

Giới hạn $B$ không thay đổi. Giá trị một chu kỳ có thể lớn hơn $B$. Mỗi truy vấn sử dụng các chu kỳ sau tất cả thao tác đổi trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$ và số nguyên $B$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả chu kỳ ban đầu của các thiết bị.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa LCM của đoạn được hỏi nếu giá trị đó không vượt quá $B$; ngược lại in `-1`. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le A_i,x\le10^9$; $1\le B\le10^{18}$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
4 6 30
4 6 5 7
2 1 2
2 2 3
2 1 3
1 1 3
2 1 3
2 4 4
```

### Sample Output 1

```text
12
30
-1
30
7
```

### Sample Input 2

```text
2 5 1
1 2
2 1 1
2 1 2
1 2 1
2 1 2
2 2 2
```

### Sample Output 2

```text
1
-1
1
1
```

### Giải thích

Ở ví dụ 1, LCM của $4,6$ là $12$ nên được in ra. LCM của $6,5$ là $30$, đúng bằng giới hạn và vẫn hợp lệ. LCM của $4,6,5$ là $60>30$ nên in `-1`. Đổi chu kỳ đầu thành $3$ làm LCM của ba chu kỳ đầu còn $30$. Thiết bị cuối có chu kỳ $7$, không vượt giới hạn.

Ở ví dụ 2, giới hạn là $1$. Chu kỳ $2$ tự nó đã vượt giới hạn. Khi sửa chu kỳ này về $1$, LCM của cả hai thiết bị lại hợp lệ.
