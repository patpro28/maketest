# DPSTR532 — Đếm kịch bản chỉnh sửa tối ưu

### Đề bài

Cho xâu nguồn $A$ và xâu đích $B$.

Một phương án được mô tả bằng cách duyệt hai xâu từ trái sang phải. Ở mỗi bước, chọn một trong ba thao tác:

- Xóa ký tự nguồn kế tiếp, chỉ tiến trong $A$.
- Chèn ký tự đích kế tiếp, chỉ tiến trong $B$.
- Ghép hai ký tự kế tiếp rồi tiến trong cả hai xâu. Giữ nguyên nếu chúng bằng nhau, hoặc thay chữ nguồn thành chữ đích nếu khác nhau.

Phương án kết thúc khi đã duyệt hết cả hai xâu.

Mỗi lần chèn, xóa hoặc thay tốn $1$. Giữ chữ giống nhau tốn $0$. Hai kịch bản khác nhau nếu dãy loại bước khác nhau, với ba loại là xóa, chèn và ghép. Hãy tìm chi phí nhỏ nhất và số kịch bản đạt chi phí đó.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $N,M$.
- Dòng thứ hai chứa xâu nguồn $A$ có đúng $N$ ký tự.
- Dòng thứ ba chứa xâu đích $B$ có đúng $M$ ký tự.

### Dữ liệu ra

In hai số nguyên là chi phí nhỏ nhất và số kịch bản tối ưu lấy modulo $10^9+7$.

### Ràng buộc

- $1\le N,M\le5000$.
- Hai xâu chỉ gồm chữ cái thường từ `a` đến `z`.

### Sample Input 1

```text
2 1
aa
a
```

### Sample Output 1

```text
1 2
```

### Sample Input 2

```text
1 1
a
b
```

### Sample Output 2

```text
1 1
```

### Giải thích

Ở ví dụ 1, có thể xóa rồi ghép hoặc ghép rồi xóa. Ở ví dụ 2, chỉ thay trực tiếp đạt chi phí $1$.
