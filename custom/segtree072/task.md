# SEGTREE072 — Đóng gói hàng hóa

### Đề bài

Có $N$ kho được đánh số từ $1$ đến $N$. Ban đầu, kho $i$ có $A_i$ sản phẩm.

Để đóng gói các kho trên đoạn $[l,r]$, bạn chọn một số nguyên dương $d$ và chia **từng kho riêng biệt** thành các gói, mỗi gói chứa đúng $d$ sản phẩm. Phải dùng hết sản phẩm của từng kho; không được chuyển sản phẩm giữa các kho.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: đặt số sản phẩm tại kho $i$ thành $x$.
- `2 l r`: tìm kích thước gói $d$ lớn nhất có thể dùng cho các kho từ $l$ đến $r$, đồng thời tính tổng số gói tạo ra nếu dùng kích thước đó.

Truy vấn chỉ yêu cầu tính kết quả, không làm thay đổi lượng hàng. Mỗi truy vấn sử dụng các lượng hàng sau tất cả thao tác cập nhật trước đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả số sản phẩm ban đầu của từng kho.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng gồm hai số nguyên: kích thước gói lớn nhất rồi đến tổng số gói tạo ra khi dùng kích thước đó. Hai số cách nhau một dấu cách. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N\le200000$; $1\le Q\le200000$.
- $1\le A_i,x\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
4 6
12 18 24 7
2 1 3
2 1 4
1 4 30
2 1 4
1 2 12
2 1 2
```

### Sample Output 1

```text
6 9
1 61
6 14
12 2
```

### Sample Input 2

```text
1 3
1000000000
2 1 1
1 1 1
2 1 1
```

### Sample Output 2

```text
1000000000 1
1 1
```

### Giải thích

Ở ví dụ 1, ba kho đầu có $12,18,24$ sản phẩm. Kích thước gói lớn nhất là $6$, tạo $2+3+4=9$ gói. Khi xét thêm kho có $7$ sản phẩm, chỉ có thể dùng gói kích thước $1$, tạo $61$ gói. Sau khi sửa kho cuối thành $30$, cả bốn kho dùng được gói kích thước $6$, tạo $14$ gói. Sau lần sửa tiếp theo, hai kho đầu đều có $12$ sản phẩm, mỗi kho tạo một gói.

Ở ví dụ 2, đoạn chỉ có một kho nên kích thước gói lớn nhất bằng toàn bộ lượng hàng trong kho và luôn tạo đúng một gói.
