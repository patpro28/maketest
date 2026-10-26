# SEGTREE015 — Mã tổng kiểm tra

### Đề bài

Một hệ thống lưu dãy $N$ số nguyên không âm $A_1,A_2,\ldots,A_N$ và một môđun nguyên dương $M$ cố định. Mã tổng kiểm tra của đoạn $[l,r]$ là phần dư của tổng $A_l+A_{l+1}+\cdots+A_r$ khi chia cho $M$.

Bạn cần thực hiện lần lượt $Q$ thao tác thuộc hai loại:

- `1 i x`: gán $A_i=x$.
- `2 l r`: tính mã tổng kiểm tra của đoạn $[l,r]$.

Môđun $M$ không thay đổi. Mỗi truy vấn sử dụng dãy sau tất cả thao tác gán trước đó.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,M$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\ldots,A_N$, mô tả các phần tử ban đầu của dãy.
- Mỗi dòng trong $Q$ dòng tiếp theo mô tả một thao tác theo dạng `1 i x` hoặc `2 l r`.

### Dữ liệu ra

Với mỗi thao tác loại $2$, in một dòng chứa mã tổng kiểm tra của đoạn được hỏi, là số nguyên thuộc $[0,M-1]$. Nếu không có thao tác loại $2$, không in gì.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i,x\le10^9$; $1\le M\le10^9$.
- Với thao tác loại $1$: $1\le i\le N$.
- Với thao tác loại $2$: $1\le l\le r\le N$.

### Sample Input 1

```text
5 6 7
5 8 0 6 4
2 1 5
2 2 4
1 3 10
2 1 3
1 2 1
2 2 5
```

### Sample Output 1

```text
2
0
2
0
```

### Sample Input 2

```text
2 4 1
1000000000 0
2 1 2
1 1 5
2 1 1
2 2 2
```

### Sample Output 2

```text
0
0
0
```

### Giải thích

Ở ví dụ 1, tổng ban đầu là $23$, có phần dư $2$ khi chia cho $7$. Đoạn $[2,4]$ có tổng $14$ nên mã bằng $0$. Sau khi gán $A_3=10$, đoạn $[1,3]$ có tổng $23$, mã bằng $2$. Sau lần gán tiếp theo, đoạn $[2,5]$ có tổng $1+10+6+4=21$, mã bằng $0$.

Ở ví dụ 2, mọi số nguyên đều có phần dư $0$ khi chia cho $M=1$.
