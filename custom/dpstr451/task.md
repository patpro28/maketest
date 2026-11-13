# DPSTR451 — Dãy đoạn số tăng dần

### Đề bài

Cho xâu chữ số $S$. Hãy đếm số cách chia toàn bộ xâu thành các số nguyên dương tăng nghiêm ngặt từ trái sang phải. Mỗi số là một đoạn liên tiếp không rỗng và chữ số đầu tiên phải khác `0`. Các số có thể dài hơn miền biểu diễn của kiểu số nguyên thông thường.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In số cách chia, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N\le4000$.
- $S$ chỉ gồm các chữ số từ `0` đến `9`.

### Sample Input 1

```text
4
1234
```

### Sample Output 1

```text
5
```

### Sample Input 2

```text
3
101
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, các cách là `1234`, `1 | 234`, `12 | 34`, `1 | 2 | 34` và `1 | 2 | 3 | 4`. Ở ví dụ 2, chỉ có cách giữ toàn bộ `101`.
