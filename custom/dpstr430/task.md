# DPSTR430 — Tách từ theo bảng giá

### Đề bài

Cho xâu $S$ và một từ điển. Mỗi mục gồm một từ và chi phí sử dụng từ đó một lần. Hãy chia toàn bộ $S$ thành các đoạn liên tiếp không rỗng thuộc từ điển sao cho tổng chi phí nhỏ nhất. Có thể sử dụng lại một mục bất kỳ số lần. Nếu một từ xuất hiện ở nhiều mục, mỗi lần dùng từ được chọn mục trả phí.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,D$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.
- Trong $D$ dòng tiếp theo, mỗi dòng chứa một từ $W_i$ và chi phí $C_i$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất. In $-1$ nếu không có cách chia.

### Ràng buộc

- $1\le N\le50000$ và $1\le D\le10000$.
- $1\le |W_i|\le100$ và tổng độ dài các từ không quá $50000$.
- $0\le C_i\le10^9$.
- Xâu $S$ và các từ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
4 3
abab
a 3
b 2
ab 4
```

### Sample Output 1

```text
8
```

### Sample Input 2

```text
3 2
aab
a 1
aa 0
```

### Sample Output 2

```text
-1
```

### Giải thích

Ở ví dụ 1, dùng `ab | ab` tốn $8$, rẻ hơn tách từng chữ. Trong ví dụ 2, không có từ nào phủ chữ `b` cuối.
