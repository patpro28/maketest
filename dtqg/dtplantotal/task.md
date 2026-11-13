# DTPLANTOTAL — Sản xuất đúng tổng số sản phẩm

### Đề bài

Một xí nghiệp có $m$ loại sản phẩm, dùng hai nguyên liệu P và Q. Sản phẩm loại $i$ cần $a_i$ đơn vị P và $b_i$ đơn vị Q.

Hãy đếm các bộ số nguyên không âm $(x_1,\ldots,x_m)$ vừa sử dụng hết $A$ đơn vị P và $B$ đơn vị Q, vừa sản xuất **đúng $C$ sản phẩm**:

$$\sum_i a_ix_i=A,\qquad \sum_i b_ix_i=B,\qquad \sum_i x_i=C.$$

Hai bộ số lượng khác nhau được tính riêng. Các loại sản phẩm khác mã vẫn được phân biệt khi có cùng cặp tiêu hao. In số phương án modulo $10^9$.

### Dữ liệu vào

- Dòng đầu chứa bốn số nguyên $m,A,B,C$.
- Trong $m$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $a_i,b_i$.

### Dữ liệu ra

In số phương án hợp lệ modulo $10^9$.

### Ràng buộc

- $1\le m\le8$.
- $0\le A,B,C\le10^{18}$.
- $1\le a_i,b_i\le2$.

### Sample Input 1

```text
3 3 3 2
1 1
1 1
2 2
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
1 4 4 3
1 1
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, hai phương án là $(1,0,1)$ và $(0,1,1)$. Mỗi phương án tạo đúng hai sản phẩm và dùng ba đơn vị mỗi nguyên liệu.

Ở ví dụ 2, tạo đúng ba sản phẩm chỉ tiêu thụ ba đơn vị mỗi nguyên liệu, không thể tiêu thụ bốn đơn vị.
