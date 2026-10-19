# STRINGA3 — Tổng mã hàng

### Đề bài

Cho một xâu $S$ chỉ gồm chữ cái tiếng Anh (chữ hoa, chữ thường) và chữ số.

Một mã hàng là một đoạn không rỗng gồm các chữ số liên tiếp và không thể kéo dài thêm sang trái hoặc sang phải bằng một chữ số. Ký tự ngay trước và ngay sau đoạn, nếu có, đều là chữ cái. Không được chọn một phần bên trong một đoạn chữ số làm một mã hàng riêng.

Giá trị của mã hàng là số nguyên không âm được biểu diễn bởi đoạn chữ số đó. Các chữ số $0$ ở đầu không làm thay đổi giá trị. Mỗi lần xuất hiện của một mã hàng đều được tính riêng, kể cả khi có cùng giá trị.

Cho số nguyên dương $K$. Hãy tính phần dư của tổng giá trị tất cả mã hàng trong $S$ khi chia cho $K$. Nếu không có mã hàng nào, tổng được quy ước bằng $0$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $K$.
- Dòng thứ hai chứa xâu $S$.

### Dữ liệu ra

In một số nguyên trong đoạn $[0,K-1]$, là phần dư cần tìm.

### Ràng buộc

- $1\le K\le10^9$.
- $1\le |S|\le10^5$, trong đó $|S|$ là độ dài xâu $S$.
- Mỗi ký tự của $S$ là chữ cái tiếng Anh hoặc chữ số từ $0$ đến $9$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 50% | $K=1$ |
| 2 | 30% | Giá trị của mọi mã hàng trong $S$ không vượt quá $10^{12}$ |
| 3 | 20% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
7
a12b003c45
```

### Sample Output 1

```text
4
```

### Sample Input 2

```text
100
0005a5B00090
```

### Sample Output 2

```text
0
```

### Sample Input 3

```text
9
abcXYZ
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, có ba mã hàng với giá trị $12,3,45$. Tổng bằng $60$, chia cho $7$ dư $4$.

Ở ví dụ 2, ba mã hàng có giá trị $5,5,90$. Hai mã cùng giá trị $5$ được tính riêng. Tổng bằng $100$, chia hết cho $100$.

Ở ví dụ 3, xâu không chứa chữ số nên kết quả bằng $0$.
