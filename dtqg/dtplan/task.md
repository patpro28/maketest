# DTPLAN — Kế hoạch sản xuất

### Đề bài

Xí nghiệp Zeta chuyên sản xuất $m$ loại sản phẩm, sử dụng hai loại nguyên liệu chính là P và Q. Để sản xuất một sản phẩm loại $i$, xí nghiệp cần $a_i$ đơn vị nguyên liệu P và $b_i$ đơn vị nguyên liệu Q.

Hiện trong kho có $A$ đơn vị nguyên liệu P và $B$ đơn vị nguyên liệu Q. Ban giám đốc cần lập phương án sản xuất tận dụng hết cả hai loại nguyên liệu.

Một phương án được mô tả bởi dãy $x=(x_1,x_2,\ldots,x_m)$, trong đó $x_i$ là số lượng sản phẩm loại $i$ được sản xuất và là số nguyên không âm. Phương án hợp lệ phải thỏa mãn:

$$\sum_{i=1}^{m}a_ix_i=A,\qquad \sum_{i=1}^{m}b_ix_i=B.$$

Hai phương án $x$ và $y$ được coi là khác nhau nếu tồn tại ít nhất một chỉ số $k$ sao cho $x_k\ne y_k$. Các loại sản phẩm có mã khác nhau vẫn được phân biệt, ngay cả khi chúng cần cùng lượng nguyên liệu.

Hãy tính số phương án sản xuất khác nhau tận dụng hết cả hai loại nguyên liệu. Vì kết quả có thể rất lớn, hãy in phần dư khi chia số phương án cho $10^9$.

### Dữ liệu vào

Đọc từ tệp `PLAN.INP`:

- Dòng đầu chứa ba số nguyên dương $m,A,B$, lần lượt là số loại sản phẩm, lượng nguyên liệu P và lượng nguyên liệu Q có trong kho.
- Trong $m$ dòng tiếp theo, dòng thứ $i$ chứa hai số nguyên dương $a_i,b_i$, là lượng nguyên liệu P và Q cần để sản xuất một sản phẩm loại $i$.

Các số trên cùng một dòng được ngăn cách bởi ít nhất một dấu cách.

### Dữ liệu ra

Ghi ra tệp `PLAN.OUT` một số nguyên là phần dư của số phương án sản xuất hợp lệ khi chia cho $10^9$.

### Ràng buộc

- $1\le m\le20$.
- $1\le A,B\le10^9$.
- $1\le a_i,b_i\le5$ với mọi $1\le i\le m$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 10% | $A,B\le1000$ |
| 2 | 20% | $m\le3$ |
| 3 | 30% | $m\le10$ |
| 4 | 40% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3 3 3
1 1
2 2
3 3
```

### Sample Output 1

```text
3
```

### Giải thích

Ở ví dụ 1, cả hai điều kiện về nguyên liệu đều tương đương với:

$$x_1+2x_2+3x_3=3.$$

Có đúng ba phương án sản xuất:

- $(x_1,x_2,x_3)=(3,0,0)$.
- $(x_1,x_2,x_3)=(1,1,0)$.
- $(x_1,x_2,x_3)=(0,0,1)$.

Vì vậy kết quả là $3$.
