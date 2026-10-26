# DPSTRING05 — Điền tín hiệu

### Đề bài

Cho xâu $S$ dài $N$ chỉ gồm `A`, `B` và `?`. Mỗi dấu `?` phải được thay bằng `A` hoặc `B`. Các ký tự `A`, `B` ban đầu phải giữ nguyên.

Sau khi điền, mỗi cặp ký tự liên tiếp `AB` có chi phí $X$, mỗi cặp `BA` có chi phí $Y$. Các cặp `AA` và `BB` có chi phí $0$. Tổng chi phí của xâu bằng tổng chi phí của tất cả $N-1$ cặp ký tự liên tiếp, kể cả khi các cặp dùng chung một vị trí.

Hãy tìm tổng chi phí nhỏ nhất có thể đạt được.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,X,Y$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.

### Dữ liệu ra

In tổng chi phí nhỏ nhất có thể đạt được.

### Ràng buộc

- $1\le N\le 50000$.
- Mỗi ký tự của $S$ thuộc tập `A`, `B`, `?`.
- $0\le X,Y\le10^9$.

### Sample Input 1

```text
4 4 1
A??B
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
5 7 2
B?A?B
```

### Sample Output 2

```text
9
```

### Giải thích

Ở ví dụ 1, điền thành `AAAB`, chỉ có một cặp `AB`, chi phí $4$. Do ký tự đầu là `A` và cuối là `B`, luôn phải có ít nhất một cặp `AB`. Ở ví dụ 2, điền thành `BAAAB`, có một cặp `BA` và một cặp `AB`, tổng chi phí $2+7=9$.
