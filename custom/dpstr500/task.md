# DPSTR500 — Số lần chỉnh sửa ít nhất

### Đề bài

Cho hai xâu $A,B$. Trong một thao tác, bạn có thể xóa một ký tự của xâu hiện tại, chèn một chữ cái thường ở vị trí bất kỳ hoặc thay một ký tự bằng một chữ cái thường khác. Hãy tìm số thao tác ít nhất để biến $A$ thành $B$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In số thao tác ít nhất.

### Ràng buộc

- $1\le N,M\le5000$.
- Hai xâu chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
3 4
abc
axcd
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3 3
abc
abc
```

### Sample Output 2

```text
0
```

### Giải thích

Ví dụ 1 thay `b` bằng `x` rồi chèn `d`. Hai xâu khác độ dài nên phải chèn ít nhất một lần, và chỉ chèn một chữ không thể đổi `b` thành `x`. Ví dụ 2 đã có hai xâu bằng nhau.
