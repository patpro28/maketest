# DPSTR432 — Đoạn không trùng chữ

### Đề bài

Cho xâu $S$ và hai số $L,R$. Hãy chia toàn bộ $S$ thành ít đoạn liên tiếp nhất sao cho độ dài mỗi đoạn thuộc $[L,R]$ và các ký tự trong cùng đoạn đôi một khác nhau.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,L,R$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In số đoạn ít nhất, hoặc $-1$ nếu không thể chia.

### Ràng buộc

- $1\le N\le200000$ và $1\le L\le R\le N$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
6 2 4
abccde
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
4 2 3
aabc
```

### Sample Output 2

```text
-1
```

### Giải thích

Ví dụ 1 chia được thành `abc | cde`. Toàn xâu có hai chữ `c` nên cần ít nhất hai đoạn. Ở ví dụ 2, mọi mảnh đầu có độ dài ít nhất $2$ đều chứa hai chữ `a`.
