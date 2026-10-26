# SEGTREE120 — Người thứ k

### Đề bài

Có $N$ người được đánh số từ $1$ đến $N$. Trạng thái $A_i=1$ nghĩa là người $i$ đang hoạt động; $A_i=0$ nghĩa là người đó tạm nghỉ.

Bạn cần thực hiện lần lượt $Q$ thao tác:

- `1 i`: đảo trạng thái người $i$.
- `2 k`: liệt kê những người đang hoạt động theo chỉ số tăng dần và tìm chỉ số của người thứ $k$ trong danh sách đó. Nếu có ít hơn $k$ người hoạt động, trả về $-1$.

Tìm kiếm không làm thay đổi trạng thái người được tìm thấy.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả trạng thái ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i` hoặc `2 k`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa chỉ số người đang hoạt động thứ $k$ hoặc $-1$ nếu không tồn tại. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $A_i\in\{0,1\}$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le k\le N$.

### Sample Input 1

```text
6 7
1 0 1 1 0 1
2 3
2 5
1 3
2 3
1 2
2 2
2 4
```

### Sample Output 1

```text
4
-1
6
2
6
```

### Sample Input 2

```text
1 5
0
2 1
1 1
2 1
1 1
2 1
```

### Sample Output 2

```text
-1
1
-1
```

### Giải thích

Ở ví dụ 1, danh sách ban đầu là $1,3,4,6$, nên người thứ $3$ ở vị trí $4$ và người thứ $5$ không tồn tại. Cho người $3$ nghỉ làm danh sách còn $1,4,6$. Khi người $2$ hoạt động, danh sách là $1,2,4,6$.

Ở ví dụ 2, chỉ khi người duy nhất hoạt động thì truy vấn tìm người hoạt động thứ $1$ mới có kết quả $1$.
