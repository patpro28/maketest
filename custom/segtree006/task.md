# SEGTREE006 — Mức giá nhỏ thứ hai

### Đề bài

Có $N$ sản phẩm xếp thành một hàng. Sản phẩm thứ $i$ có giá $A_i$.

Với mỗi đoạn $[L,R]$, hãy xét các **mức giá khác nhau** xuất hiện trong đoạn và sắp chúng theo thứ tự tăng dần. Bạn cần tìm mức giá đứng thứ hai trong danh sách đó. Nếu đoạn có ít hơn hai mức giá khác nhau, trả lời $-1$.

Ví dụ, đoạn có các giá $[4,1,1,7,4]$ có ba mức giá khác nhau là $1,4,7$, nên mức giá nhỏ thứ hai là $4$, không phải $1$.

Có $Q$ truy vấn; mỗi truy vấn cho một đoạn $[L,R]$. Dãy giá không thay đổi trong suốt các truy vấn.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,Q$.
- Dòng thứ hai chứa $N$ số nguyên $A_1,A_2,\dots,A_N$.
- Mỗi dòng trong $Q$ dòng tiếp theo chứa hai số nguyên $L,R$, mô tả một truy vấn.

### Dữ liệu ra

Với mỗi truy vấn, in mức giá nhỏ thứ hai trong các mức giá khác nhau của đoạn, hoặc $-1$ nếu không tồn tại. Mỗi câu trả lời nằm trên một dòng.

### Ràng buộc

- $1\le N,Q\le200000$.
- $0\le A_i\le10^9$.
- Với mỗi truy vấn: $1\le L\le R\le N$.

### Sample Input 1

```text
6 5
4 1 1 7 4 0
1 5
2 3
3 6
4 4
1 2
```

### Sample Output 1

```text
4
-1
1
-1
4
```

### Sample Input 2

```text
4 4
1000000000 0 1000000000 0
1 4
2 2
1 3
3 4
```

### Sample Output 2

```text
1000000000
-1
1000000000
1000000000
```

### Giải thích

Ở ví dụ 1, đoạn $[1,5]$ có các mức giá $1,4,7$, nên trả lời $4$. Đoạn $[2,3]$ chỉ có mức giá $1$, nên trả lời $-1$. Đoạn $[3,6]$ có các mức giá $0,1,4,7$, nên trả lời $1$. Đoạn một phần tử $[4,4]$ trả lời $-1$. Đoạn $[1,2]$ có hai mức giá $1,4$, nên trả lời $4$.

Ở ví dụ 2, mọi đoạn có cả hai mức giá $0$ và $1000000000$ đều trả lời $1000000000$. Đoạn $[2,2]$ chỉ có một mức giá nên trả lời $-1$.
