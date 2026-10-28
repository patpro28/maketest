# SEGTREE104 — Thiết bị thiếu tính năng

### Đề bài

Có $N$ thiết bị. Mặt nạ bit $a_i$ biểu diễn các tính năng của thiết bị thứ $i$: bit bật nghĩa là có tính năng tương ứng. Thực hiện các thao tác:

- `1 i x`: gán mặt nạ của thiết bị $i$ bằng $x$.
- `2 M`: tìm vị trí nhỏ nhất $i$ của thiết bị thiếu ít nhất một tính năng được yêu cầu trong $M$, tức là $(a_i\mathbin{\mathrm{AND}}M)\ne M$. Nếu mọi thiết bị đều đủ tính năng, in `-1`.

Thiết bị được phép có thêm các tính năng ngoài yêu cầu. AND là phép toán AND trên bit.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le a_i,x<2^{20}$; $1\le M<2^{20}$; $1\le i\le N$.

### Sample Input 1

```text
4 6
7 3 5 7
2 3
2 1
2 4
1 1 0
2 1
2 7
```

### Sample Output 1

```text
3
-1
2
1
1
```

### Sample Input 2

```text
1 4
1048575
2 1048575
1 1 1048574
2 1
2 2
```

### Sample Output 2

```text
-1
1
-1
```

### Giải thích

Ở ví dụ 1, yêu cầu $3$ cần hai bit thấp nhất: hai thiết bị đầu đủ, thiết bị thứ $3$ thiếu một bit nên trả về $3$. Yêu cầu $1$ được mọi thiết bị đáp ứng, còn yêu cầu $4$ bị thiết bị thứ $2$ vi phạm đầu tiên. Sau cập nhật, thiết bị đầu tiên thiếu mọi tính năng được yêu cầu. Ở ví dụ 2, các đáp án là $-1,1,-1$.
