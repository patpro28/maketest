# DPSTR403 — Hai đầu cùng chữ

### Đề bài

Cho xâu $S$ và số nguyên $K$. Chia $S$ thành các đoạn liên tiếp, mỗi đoạn có độ dài từ $1$ đến $K$ và ký tự đầu bằng ký tự cuối. Đoạn một ký tự luôn hợp lệ. Hãy đếm số cách đặt điểm cắt.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,K$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In số cách chia, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N\le200000$ và $1\le K\le50$.
- $S$ chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
3 3
aba
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3 2
aaa
```

### Sample Output 2

```text
3
```

### Giải thích

Ví dụ 1 có `a | b | a` và `aba`. Ví dụ 2 có `a | a | a`, `a | aa` và `aa | a`.
