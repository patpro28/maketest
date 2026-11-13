# DPSTR401 — Giải mã dãy số

### Đề bài

Cho một xâu chữ số $S$. Chia xâu thành các đoạn liên tiếp không rỗng. Mỗi đoạn phải là biểu diễn thập phân của một số từ $1$ đến $26$ và không được có chữ số $0$ ở đầu. Hãy đếm số cách đặt các điểm cắt hợp lệ. Hai cách khác nhau khi có ít nhất một điểm cắt khác nhau.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In số cách chia, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N\le200000$.
- $S$ chỉ gồm các chữ số từ `0` đến `9`.

### Sample Input 1

```text
3
226
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
3
100
```

### Sample Output 2

```text
0
```

### Giải thích

Ví dụ 1 có ba cách `2 | 2 | 6`, `22 | 6` và `2 | 26`. Trong ví dụ 2, sau khi lấy `10` vẫn còn một chữ số `0` không thể đứng riêng.
