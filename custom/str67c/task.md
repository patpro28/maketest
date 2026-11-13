# STR67C — Bàn phím bị hỏng

### Đề bài

Bàn phím của An chỉ gồm $26$ phím tương ứng với các chữ cái in thường trong bảng chữ cái Latinh. Một số phím hoạt động bình thường, số còn lại bị hỏng.

Để kiểm tra bàn phím, An nhấn một số phím theo một trình tự nhất định, **không nhấn cùng một phím hai lần liên tiếp**. Mỗi lần nhấn phím tương ứng với ký tự $K$:

- Nếu phím hoạt động bình thường, một ký tự $K$ xuất hiện trên màn hình.
- Nếu phím bị hỏng, hai ký tự $K$ xuất hiện trên màn hình.

Ví dụ, nếu các phím `a`, `c` hoạt động bình thường và phím `b` bị hỏng, khi An nhấn các phím theo thứ tự `a`, `b`, `a`, `c`, `a`, `b`, `a`, chuỗi trên màn hình lần lượt là:

`a` → `abb` → `abba` → `abbac` → `abbaca` → `abbacabb` → `abbacabba`.

Cho chuỗi $S$ xuất hiện trên màn hình sau khi An nhấn các phím. Hãy xác định các phím hoạt động bình thường. Theo quy ước của bài toán, phím có ký tự không xuất hiện trong $S$ được xem là phím bị hỏng.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $t$ là số bộ dữ liệu.
- Trong $t$ dòng tiếp theo, mỗi dòng chứa một chuỗi $S$ mô tả một bộ dữ liệu.

### Dữ liệu ra

Với mỗi bộ dữ liệu, in trên một dòng chuỗi $X$ chứa các ký tự tương ứng với những phím hoạt động bình thường. Các ký tự trong $X$ phải phân biệt và được sắp xếp theo thứ tự bảng chữ cái.

Nếu tất cả các phím đều bị hỏng, in một dòng rỗng cho bộ dữ liệu đó.

### Ràng buộc

- $1 \le t \le 100$.
- $1 \le |S| \le 500$.
- $S$ chỉ chứa các chữ cái in thường từ `a` đến `z`.
- $S$ được tạo ra theo đúng quá trình nhấn phím đã mô tả; trạng thái của mỗi phím không thay đổi trong một bộ dữ liệu.

### Sample Input 1

```text
4
a
yyaaz
ccff
cbddb
```

### Sample Output 1

```text
a
z

bc
```

### Giải thích

Trong ví dụ 1:

- Với `a`, phím `a` hoạt động bình thường nên kết quả là `a`.
- Với `yyaaz`, các phím `y`, `a` bị hỏng, phím `z` hoạt động bình thường nên kết quả là `z`.
- Với `ccff`, các phím `c`, `f` bị hỏng. Các phím không xuất hiện cũng được xem là bị hỏng, nên dòng kết quả thứ ba rỗng.
- Với `cbddb`, An đã nhấn lần lượt các phím `c`, `b`, `d`, `b`. Các phím `b`, `c` hoạt động bình thường, phím `d` bị hỏng nên kết quả là `bc`.
