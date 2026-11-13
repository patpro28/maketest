# DTPLANKINDS — Sử dụng đúng số loại sản phẩm

### Đề bài

Một xí nghiệp có $m$ loại sản phẩm và hai nguyên liệu P, Q. Sản phẩm loại $i$ tiêu thụ $a_i$ đơn vị P và $b_i$ đơn vị Q.

Kho có $A$ đơn vị P và $B$ đơn vị Q. Hãy đếm các bộ số nguyên không âm $(x_1,\ldots,x_m)$ thỏa mãn:

$$\sum_i a_ix_i=A,\qquad \sum_i b_ix_i=B,$$

và có **đúng $K$ chỉ số $i$ thỏa mãn $x_i>0$**. Một loại được tính một lần dù sản xuất nhiều sản phẩm của loại đó.

Hai bộ số lượng khác nhau là hai phương án khác nhau. Các loại có cùng cặp tiêu hao vẫn được phân biệt. In số phương án modulo $10^9$.

### Dữ liệu vào

- Dòng đầu chứa bốn số nguyên $m,A,B,K$.
- Trong $m$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $a_i,b_i$.

### Dữ liệu ra

In số phương án thỏa mãn modulo $10^9$.

### Ràng buộc

- $1\le m\le20$.
- $0\le A,B\le150$.
- $0\le K\le m$.
- $1\le a_i,b_i\le5$.

### Sample Input 1

```text
3 3 3 2
1 1
2 2
3 3
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
2 0 0 0
1 1
2 2
```

### Sample Output 2

```text
1
```

### Giải thích

Ở ví dụ 1, chỉ có $(x_1,x_2,x_3)=(1,1,0)$ dùng hết hai nguyên liệu và sử dụng đúng hai loại. Phương án $(3,0,0)$ hoặc $(0,0,1)$ chỉ sử dụng một loại.

Ở ví dụ 2, phương án duy nhất là $(0,0)$, sử dụng đúng $0$ loại.
