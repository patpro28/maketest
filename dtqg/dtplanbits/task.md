# DTPLANBITS — Kế hoạch có số lượng đặc biệt

### Đề bài

Một xí nghiệp có $m$ loại sản phẩm, dùng hai nguyên liệu P và Q. Sản phẩm loại $i$ tiêu thụ $a_i$ đơn vị P và $b_i$ đơn vị Q.

Cần chọn các số nguyên không âm $x_1,\ldots,x_m$ để dùng hết $A$ đơn vị P và $B$ đơn vị Q:

$$\sum_i a_ix_i=A,\qquad \sum_i b_ix_i=B.$$

Ngoài ra, biểu diễn nhị phân của **từng số $x_i$** không được chứa hai bit `1` liên tiếp. Chẳng hạn $5=101_2$ được phép, còn $6=110_2$ không được phép. Số $0$ được phép.

Hãy đếm số bộ số lượng hợp lệ modulo $10^9$. Hai bộ khác nhau được tính riêng; các loại có cùng cặp tiêu hao vẫn được phân biệt. Điều kiện bit áp dụng riêng cho từng loại, không áp dụng cho tổng số sản phẩm.

### Dữ liệu vào

- Dòng đầu chứa ba số nguyên $m,A,B$.
- Trong $m$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên $a_i,b_i$.

### Dữ liệu ra

In số phương án hợp lệ modulo $10^9$.

### Ràng buộc

- $1\le m\le8$.
- $0\le A,B\le10^{18}$.
- $1\le a_i,b_i\le2$.

### Sample Input 1

```text
1 5 5
1 1
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
1 6 6
1 1
```

### Sample Output 2

```text
0
```

### Giải thích

Ở ví dụ 1, phương án duy nhất là $x_1=5=101_2$, không có hai bit `1` liên tiếp.

Ở ví dụ 2, hai phương trình bắt buộc $x_1=6=110_2$, vi phạm điều kiện bit.
