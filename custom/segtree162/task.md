# SEGTREE162 — Kiện hàng sai quy cách

### Đề bài

Cho dãy số nguyên dương $a_1,\ldots,a_N$. Thực hiện các thao tác:

- `1 i x`: gán $a_i=x$.
- `2 l r D`: tìm vị trí nhỏ nhất $i\in[l,r]$ sao cho $a_i$ không chia hết cho $D$. Nếu mọi phần tử trong đoạn đều chia hết cho $D$, in `-1`.

Số $D$ được cung cấp riêng cho từng truy vấn và có thể thay đổi.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $a_1,\ldots,a_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa một thao tác.

### Dữ liệu ra

Với mỗi thao tác loại `2`, in đáp án trên một dòng. Thao tác loại `1` không tạo đầu ra.

### Ràng buộc

- $1\le N,Q\le200000$.
- $1\le a_i,x,D\le10^9$.
- $1\le i\le N$; $1\le l\le r\le N$.

### Sample Input 1

```text
5 6
6 12 18 7 24
2 1 5 6
2 2 3 3
1 4 30
2 1 5 6
2 3 5 4
2 1 5 1
```

### Sample Output 1

```text
4
-1
-1
3
-1
```

### Sample Input 2

```text
1 4
1000000000
2 1 1 1000000000
2 1 1 3
1 1 9
2 1 1 3
```

### Sample Output 2

```text
-1
1
-1
```

### Giải thích

Ở ví dụ 1, kiện thứ $4$ ban đầu không chia hết cho $6$. Sau khi thay nó bằng $30$, mọi kiện đều chia hết cho $6$. Trong đoạn $[3,5]$, phần tử đầu tiên không chia hết cho $4$ là $18$ ở vị trí $3$. Với $D=1$, không có kiện sai quy cách. Ở ví dụ 2, các đáp án là $-1,1,-1$.
