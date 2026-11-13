# DTPLANONE — Một kho nguyên liệu

### Đề bài

Một xí nghiệp có $m$ loại sản phẩm và $A$ đơn vị nguyên liệu. Để sản xuất một sản phẩm loại $i$, cần $a_i$ đơn vị nguyên liệu.

Một phương án là bộ số nguyên không âm $(x_1,\ldots,x_m)$, trong đó $x_i$ là số sản phẩm loại $i$. Phương án hợp lệ phải dùng hết nguyên liệu:

$$\sum_{i=1}^{m}a_ix_i=A.$$

Hãy đếm số phương án hợp lệ, lấy phần dư khi chia cho $10^9$. Hai phương án khác nhau nếu có ít nhất một số lượng $x_i$ khác nhau. Các loại sản phẩm có mã khác nhau vẫn được phân biệt, kể cả khi có cùng mức tiêu hao nguyên liệu. Thứ tự sản xuất không tạo ra phương án mới.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $m,A$.
- Trong $m$ dòng tiếp theo, dòng thứ $i$ chứa số nguyên $a_i$.

### Dữ liệu ra

In số phương án hợp lệ modulo $10^9$.

### Ràng buộc

- $1\le m\le30$.
- $0\le A\le200000$.
- $1\le a_i\le1000$.

### Sample Input 1

```text
3 4
1
2
3
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
2 3
2
4
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, bốn phương án là $(4,0,0)$, $(2,1,0)$, $(0,2,0)$ và $(1,0,1)$.

Ở ví dụ 2, mọi phương án đều tiêu thụ một lượng nguyên liệu chẵn, nên không thể dùng đúng $3$ đơn vị.
