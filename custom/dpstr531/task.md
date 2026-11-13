# DPSTR531 — Chi phí theo từng vị trí

### Đề bài

Cho xâu nguồn $A$ và xâu đích $B$.

Một phương án được mô tả bằng cách duyệt hai xâu từ trái sang phải. Ở mỗi bước, chọn một trong ba thao tác:

- Xóa ký tự nguồn kế tiếp, chỉ tiến trong $A$.
- Chèn ký tự đích kế tiếp, chỉ tiến trong $B$.
- Ghép hai ký tự kế tiếp rồi tiến trong cả hai xâu. Giữ nguyên nếu chúng bằng nhau, hoặc thay chữ nguồn thành chữ đích nếu khác nhau.

Phương án kết thúc khi đã duyệt hết cả hai xâu.

Xóa vị trí $i$ của $A$ tốn $D_i$. Chèn vị trí $j$ của $B$ tốn $I_j$. Ghép hai chữ khác nhau tốn $R$, còn giữ chữ giống nhau miễn phí. Hãy tìm tổng chi phí nhỏ nhất.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa số nguyên $R$.
- Dòng thứ năm chứa $N$ số nguyên $D_1,\ldots,D_N$.
- Dòng thứ sáu chứa $M$ số nguyên $I_1,\ldots,I_M$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất.

### Ràng buộc

- $1\le N,M\le5000$.
- Hai xâu chỉ gồm chữ cái thường từ `a` đến `z`.
- $0\le D_i,I_j,R\le10^9$.

### Sample Input 1

```text
2 1
aa
a
5
9 1
4
```

### Sample Output 1

```text
1
```

### Sample Input 2

```text
1 1
a
b
10
2
3
```

### Sample Output 2

```text
5
```

### Giải thích

Ví dụ 1 giữ chữ `a` đầu tiên và xóa chữ thứ hai với giá $1$. Ví dụ 2 xóa rồi chèn tốn $5$.
