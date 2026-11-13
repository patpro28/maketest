# DPSTR503 — Bảng giá chỉnh sửa

### Đề bài

Cho hai xâu $A,B$. Bạn có thể chèn một chữ với chi phí $I$, xóa một chữ với chi phí $D$ hoặc thay một chữ bằng chữ khác với chi phí $R$. Chi phí chỉ phụ thuộc vào loại thao tác. Hãy tìm tổng chi phí nhỏ nhất để biến $A$ thành $B$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa ba số nguyên $I,D,R$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất.

### Ràng buộc

- $1\le N,M\le5000$.
- Hai xâu chỉ gồm chữ cái thường từ `a` đến `z`.
- $0\le I,D,R\le10^9$.

### Sample Input 1

```text
1 1
a
b
2 3 9
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
2 1
ab
a
7 0 4
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, xóa `a` rồi chèn `b` có chi phí $5$, rẻ hơn thay trực tiếp. Ở ví dụ 2, xóa `b` miễn phí.
