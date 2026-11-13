# DPSTR431 — Đúng số đoạn chia hết

### Đề bài

Cho một xâu chữ số $S$. Hãy đếm số cách chia toàn bộ xâu thành đúng $K$ đoạn liên tiếp không rỗng, sao cho tổng các chữ số trong từng đoạn chia hết cho $D$. Đoạn có thể bắt đầu bằng `0`. Tổng bằng $0$ được xem là chia hết cho $D$.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,K,D$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ chữ số.

### Dữ liệu ra

In số cách chia, lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N\le50000$.
- $1\le K\le\min(N,100)$ và $1\le D\le5000$.
- $S$ chỉ gồm các chữ số từ `0` đến `9`.

### Sample Input 1

```text
4 2 3
1203
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
3 2 2
111
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, hai cách chia là `12 | 03` và `120 | 3`. Ở ví dụ 2, tổng toàn xâu bằng $3$, không thể là tổng của hai tổng chẵn.
