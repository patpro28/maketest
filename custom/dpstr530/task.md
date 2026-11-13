# DPSTR530 — Khớp mẫu có dấu hỏi

### Đề bài

Cho xâu nguồn $A$ và mẫu $B$. Trong mẫu, mỗi dấu `?` đại diện cho đúng một chữ cái thường và được điền độc lập với các dấu khác. Bạn có thể chèn, xóa hoặc thay một chữ của xâu nguồn, mỗi thao tác tốn một lần. Hãy tìm số thao tác ít nhất để xâu kết quả khớp với một cách điền mẫu $B$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa mẫu $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In số thao tác ít nhất.

### Ràng buộc

- $1\le N,M\le5000$.
- $A$ chỉ gồm chữ cái thường. $B$ gồm chữ cái thường và ký tự `?`.

### Sample Input 1

```text
3 3
abc
a?c
```

### Sample Output 1

```text
0
```

### Sample Input 2

```text
2 3
ab
?ca
```

### Sample Output 2

```text
2
```

### Giải thích

Ở ví dụ 1, điền dấu hỏi bằng `b`. Ở ví dụ 2, có thể điền thành `aca`, thay `b` bằng `c` rồi chèn `a`. Chỉ chèn một chữ không đủ vì mẫu buộc xâu kết quả có cả `c` và chữ `a` cuối.
