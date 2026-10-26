# SEGTREE100 — Ô trống đầu tiên

### Đề bài

Có $N$ ô được đánh số từ $1$ đến $N$. Trạng thái ô $i$ là $A_i$: $0$ nghĩa là ô trống, $1$ nghĩa là ô đã được sử dụng.

Bạn cần thực hiện lần lượt $Q$ thao tác:

- `1 i`: đảo trạng thái ô $i$; ô trống trở thành đã sử dụng và ngược lại.
- `2`: tìm chỉ số nhỏ nhất của một ô đang trống trong cả dãy. Nếu không có ô trống, trả về $-1$.

Thao tác tìm kiếm không làm thay đổi trạng thái các ô.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả trạng thái ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i` hoặc `2`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa chỉ số ô trống đầu tiên hoặc $-1$ nếu không có. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $A_i\in\{0,1\}$.
- Với thao tác loại $1$: $1\le i\le N$.

### Sample Input 1

```text
5 7
1 0 1 0 1
2
1 2
2
1 4
2
1 1
2
```

### Sample Output 1

```text
2
4
-1
1
```

### Sample Input 2

```text
1 5
0
2
1 1
2
1 1
2
```

### Sample Output 2

```text
1
-1
1
```

### Giải thích

Ở ví dụ 1, ô trống đầu tiên lần lượt là ô $2$, rồi ô $4$ sau khi đảo ô $2$. Khi đảo tiếp ô $4$, tất cả ô đều đã sử dụng nên kết quả là $-1$. Đảo ô $1$ tạo ra ô trống đầu tiên ở vị trí $1$.

Ở ví dụ 2, ô duy nhất lần lượt trống, đã sử dụng rồi trống tại các thời điểm tìm kiếm.
