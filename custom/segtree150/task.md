# SEGTREE150 — Cửa hàng trong ngân sách

### Đề bài

Có $N$ cửa hàng được đánh số từ $1$ đến $N$. Cửa hàng $i$ đang bán sản phẩm với giá không âm $A_i$.

Bạn cần thực hiện lần lượt $Q$ thao tác:

- `1 i x`: sửa giá tại cửa hàng $i$ thành $x$.
- `2 x`: với ngân sách $x$, tìm cửa hàng có chỉ số nhỏ nhất có giá không vượt quá $x$. Nếu không có cửa hàng phù hợp, trả về $-1$.

Truy vấn chỉ tìm cửa hàng, không mua hàng và không làm thay đổi giá. Sản phẩm có giá $0$ cũng có thể được chọn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các giá trị ban đầu.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 x`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa chỉ số cửa hàng phù hợp đầu tiên hoặc $-1$ nếu không tồn tại. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.

### Sample Input 1

```text
5 6
8 3 6 0 5
2 4
2 0
1 2 9
2 4
1 4 7
2 4
```

### Sample Output 1

```text
2
4
4
-1
```

### Sample Input 2

```text
1 4
1000000000
2 999999999
2 1000000000
1 1 0
2 0
```

### Sample Output 2

```text
-1
1
1
```

### Giải thích

Ở ví dụ 1, với ngân sách $4$ thì cửa hàng $2$ là nơi đầu tiên đủ điều kiện, còn với ngân sách $0$ phải chọn cửa hàng $4$. Sau khi cửa hàng $2$ tăng giá lên $9$, ngân sách $4$ vẫn chọn được cửa hàng $4$. Khi cửa hàng này tăng giá lên $7$, không còn cửa hàng nào có giá không vượt $4$.

Ở ví dụ 2, giá đúng bằng ngân sách vẫn hợp lệ, kể cả khi cả hai bằng $0$.
