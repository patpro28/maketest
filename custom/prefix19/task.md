# PREFIX19 — Chia thành ba phần bằng tổng

### Đề bài

Cho dãy $N$ số nguyên $A_1,A_2,\ldots,A_N$, có thể âm. Hãy đếm số cặp chỉ số $(i,j)$ thỏa $1\le i<j<N$ sao cho ba đoạn $[1,i]$, $[i+1,j]$, $[j+1,N]$ có tổng bằng nhau. Cả ba đoạn đều phải không rỗng. Hai cách chia khác nhau nếu chỉ số $i$ hoặc $j$ khác nhau. In số cách chia chính xác, không lấy phần dư.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $N$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$.

### Dữ liệu ra

In một số nguyên là số cách chia hợp lệ.

### Ràng buộc

- $3\le N\le200000$.
- $-10^9\le A_i\le10^9$.

### Sample Input 1

```text
5
1 2 3 0 3
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
4
0 0 0 0
```

### Sample Output 2

```text
3
```

### Giải thích

Ở ví dụ 1, hai cặp điểm cắt hợp lệ là $(2,3)$ và $(2,4)$; mỗi đoạn đều có tổng $3$. Ở ví dụ 2, mọi cặp $1\le i<j\le3$ đều hợp lệ, có $3$ cách.
