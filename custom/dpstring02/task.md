# DPSTRING02 — Biển hiệu không lặp

### Đề bài

Một biển hiệu được biểu diễn bởi xâu chữ thường $S$ gồm $N$ ký tự. Chi phí xóa ký tự ở vị trí $i$ là $W_i$.

Hãy xóa một số ký tự với tổng chi phí nhỏ nhất để hai ký tự liên tiếp bất kỳ trong xâu còn lại luôn khác nhau. Các ký tự còn lại giữ nguyên thứ tự. Được phép xóa hết xâu hoặc không xóa ký tự nào; xâu có không quá một ký tự luôn hợp lệ.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.
- Dòng thứ ba chứa $N$ số nguyên $W_1,W_2,\ldots,W_N$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất có thể đạt được.

### Ràng buộc

- $1\le N\le 50000$.
- $S$ chỉ gồm các chữ cái thường từ `a` đến `z`.
- $0\le W_i\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
5
aabcc
3 7 2 8 4
```

### Sample Output 1

```text
7
```

### Sample Input 2

```text
3
zzz
1000000000 1000000000 1000000000
```

### Sample Output 2

```text
2000000000
```

### Giải thích

Ở ví dụ 1, xóa vị trí $1$ và $5$, mất $3+4=7$, còn `abc`. Ở ví dụ 2, chỉ giữ được một chữ `z`, nên phải xóa hai ký tự với tổng chi phí $2\cdot10^9$.
