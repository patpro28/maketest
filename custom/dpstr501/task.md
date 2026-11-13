# DPSTR501 — Xóa và thay để khớp

### Đề bài

Cho hai xâu $A,B$. Bạn chỉ được xóa một ký tự của xâu hiện tại hoặc thay một ký tự bằng chữ cái thường khác. Mỗi thao tác tốn một lần. Hãy tìm số thao tác ít nhất để biến $A$ thành $B$.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In số thao tác ít nhất, hoặc $-1$ nếu không thể biến đổi.

### Ràng buộc

- $1\le N,M\le5000$.
- Hai xâu chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
4 2
axby
ac
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
1 2
a
aa
```

### Sample Output 2

```text
-1
```

### Giải thích

Ví dụ 1 có thể giữ hai vị trí của `a`, `b`, xóa hai chữ còn lại và thay `b` bằng `c`. Ví dụ 2 cần tăng độ dài, điều không thể làm bằng hai thao tác cho phép.
