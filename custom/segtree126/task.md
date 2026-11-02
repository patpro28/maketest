# SEGTREE126 — Cụm màu thứ k

### Đề bài

Có $N$ ô nằm trên một hàng, ô thứ $i$ có màu $a_i$. Một **cụm màu** là một đoạn liên tiếp không rỗng có cùng màu và không thể mở rộng sang trái hoặc sang phải mà vẫn giữ cùng màu. Các cụm được đánh số từ trái sang phải, bắt đầu từ $1$.

Thực hiện $Q$ thao tác:

- `1 i c`: đổi màu ô $i$ thành $c$.
- `2 k`: tìm vị trí bắt đầu của cụm màu thứ $k$. Nếu hiện có ít hơn $k$ cụm thì trả lời $-1$.

Các cụm ở xa nhau được tính riêng, kể cả khi có cùng màu.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,a_2,\dots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo định dạng trên.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in vị trí bắt đầu của cụm được hỏi, đánh số từ $1$, hoặc $-1$ nếu không có cụm đó.

### Ràng buộc

- $1\le N,Q\le2\cdot10^5$.
- $1\le a_i\le10^9$.
- Với thao tác loại `1`: $1\le i\le N$, $1\le c\le10^9$.
- Với thao tác loại `2`: $1\le k\le N$.

### Sample Input 1

```text
7 8
1 1 2 2 1 3 3
2 3
1 3 1
2 2
1 4 1
2 2
2 3
1 6 1
2 2
```

### Sample Output 1

```text
5
4
6
-1
7
```

### Sample Input 2

```text
1 3
9
2 1
1 1 2
2 1
```

### Sample Output 2

```text
1
1
```

### Giải thích

Ở ví dụ 1, các cụm ban đầu bắt đầu tại $1,3,5,6$, nên cụm thứ ba bắt đầu tại $5$. Sau khi đổi ô $3$ thành màu $1$, các vị trí bắt đầu là $1,4,5,6$, nên câu trả lời tiếp theo là $4$. Đổi tiếp ô $4$ thành màu $1$ làm năm ô đầu cùng màu: các cụm bắt đầu tại $1,6$, do đó hai truy vấn kế tiếp trả lời $6$ và $-1$. Sau khi đổi ô $6$ thành màu $1$, cụm thứ hai bắt đầu tại $7$.

Ở ví dụ 2, luôn chỉ có một cụm và cụm đó bắt đầu tại ô $1$.
