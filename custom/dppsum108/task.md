# PREFIX08 — Nhật ký chia hết

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$ và số nguyên dương $M$. Hãy đếm số đoạn liên tiếp không rỗng có tổng chia hết cho $M$.

Hai đoạn khác nhau nếu có chỉ số đầu hoặc chỉ số cuối khác nhau. Các phần tử của dãy có thể âm.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là số đoạn liên tiếp không rỗng có tổng chia hết cho $M$.

### Ràng buộc

- $1\le N\le200000$.
- $1\le M\le200000$.
- $-10^9\le A_i\le10^9$.

### Sample Input 1

```text
5 3
1 2 3 -3 1
```

### Sample Output 1

```text
7
```

### Sample Input 2

```text
3 1
-5 0 8
```

### Sample Output 2

```text
6
```

### Giải thích

Ở ví dụ 1, bảy đoạn hợp lệ có cặp chỉ số đầu và cuối là $(1,2),(1,3),(1,4),(2,5),(3,3),(3,4),(4,4)$. Ở ví dụ 2, mọi đoạn đều có tổng chia hết cho $1$, có $3\cdot4/2=6$ đoạn.
