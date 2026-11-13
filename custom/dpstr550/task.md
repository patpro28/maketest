# DPSTR550 — Phí mở đợt chỉnh sửa

### Đề bài

Cho xâu nguồn $A$ và xâu đích $B$.

Một phương án được mô tả bằng cách duyệt hai xâu từ trái sang phải. Ở mỗi bước, chọn một trong ba thao tác:

- Xóa ký tự nguồn kế tiếp, chỉ tiến trong $A$.
- Chèn ký tự đích kế tiếp, chỉ tiến trong $B$.
- Ghép hai ký tự kế tiếp rồi tiến trong cả hai xâu. Giữ nguyên nếu chúng bằng nhau, hoặc thay chữ nguồn thành chữ đích nếu khác nhau.

Phương án kết thúc khi đã duyệt hết cả hai xâu.

Một đợt là một dãy tối đại các bước chèn liên tiếp hoặc các bước xóa liên tiếp. Đợt có $t$ bước tốn $O+tE$. Hai loại chèn và xóa tạo đợt riêng, kể cả khi đứng cạnh nhau. Bước ghép ngắt đợt. Ghép hai chữ bằng nhau miễn phí, còn ghép hai chữ khác nhau tốn $R$. Hãy tìm tổng chi phí nhỏ nhất.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.
- Dòng thứ tư chứa ba số nguyên $O,E,R$.

### Dữ liệu ra

In tổng chi phí nhỏ nhất.

### Ràng buộc

- $1\le N,M\le4000$.
- Hai xâu chỉ gồm chữ cái thường từ `a` đến `z`.
- $0\le O,E,R\le10^9$.

### Sample Input 1

```text
4 1
axxb
a
5 2 9
```

### Sample Output 1

```text
11
```

### Sample Input 2

```text
1 1
a
b
0 2 9
```

### Sample Output 2

```text
4
```

### Giải thích

Ví dụ 1 ghép `a`, sau đó xóa ba chữ liên tiếp trong một đợt, tốn $5+3\cdot2=11$. Ví dụ 2 xóa rồi chèn thành hai đợt với tổng giá $4$.
