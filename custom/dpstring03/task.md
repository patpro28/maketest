# DPSTRING03 — Không có bộ ba

### Đề bài

Cho xâu $S$ chỉ gồm `a` và `b`, gồm $N$ ký tự. Chi phí xóa ký tự ở vị trí $i$ là $W_i$.

Hãy tìm tổng chi phí xóa nhỏ nhất để xâu còn lại không chứa ba ký tự giống nhau liên tiếp. Nói cách khác, không có đoạn liên tiếp `aaa` hoặc `bbb` trong xâu sau khi xóa. Các ký tự còn lại giữ nguyên thứ tự. Được phép xóa hết xâu hoặc không xóa ký tự nào.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa xâu $S$ có đúng $N$ ký tự.
- Dòng thứ ba chứa $N$ số nguyên $W_1,W_2,\ldots,W_N$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất có thể đạt được.

### Ràng buộc

- $1\le N\le 50000$.
- Mỗi ký tự của $S$ thuộc tập `a`, `b`.
- $0\le W_i\le10^9$ với mọi $1\le i\le N$.

### Sample Input 1

```text
4
aaaa
1 9 2 8
```

### Sample Output 1

```text
3
```

### Sample Input 2

```text
6
aabbaa
1 2 3 4 5 6
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, giữ hai ký tự tại vị trí $2,4$ được `aa`, xóa hai ký tự còn lại với chi phí $1+2=3$. Ở ví dụ 2, xâu không có ba ký tự giống nhau liên tiếp, nên không cần xóa.
