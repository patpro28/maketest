# SEGTREE161 — Bội số thứ k trong đoạn

### Đề bài

Cho dãy số nguyên $a_1,\ldots,a_N$ và số nguyên dương $D$ cố định. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2 l r k`: liệt kê theo thứ tự chỉ số tăng dần các phần tử trong $[l,r]$ chia hết cho $D$. In chỉ số của phần tử thứ $k$ trong danh sách, hoặc `-1` nếu danh sách có ít hơn $k$ phần tử.

Số $0$ và các bội âm của $D$ đều được tính. Đáp án là chỉ số trong dãy ban đầu.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $N,Q,D$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Các thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$; $1\le D\le10^9$.
- $-10^9\le a_i,x\le10^9$.
- $1\le i\le N$; $1\le l\le r\le N$; $1\le k\le N$.

### Sample Input 1

```text
6 6 3
-3 0 4 6 9 5
2 2 5 2
2 3 6 3
1 3 -6
2 2 5 2
2 1 6 5
2 6 6 1
```

### Sample Output 1

```text
4
-1
3
5
-1
```

### Sample Input 2

```text
3 4 1
-1 0 7
2 2 3 1
2 2 3 3
1 2 5
2 2 2 1
```

### Sample Output 2

```text
2
-1
2
```

### Giải thích

Ở ví dụ 1, các bội số trong đoạn $[2,5]$ ban đầu ở vị trí $2,4,5$ nên phần tử thứ hai ở vị trí $4$. Sau khi đổi $a_3$ thành $-6$, đáp án của truy vấn này thành $3$. Ở ví dụ 2, $D=1$ nên mọi phần tử đều được tính, kể cả sau cập nhật.
