# KHUNGSANG — Tổng diện tích các khung sáng

### Đề bài

Cho một bảng gồm $R$ hàng và $C$ cột, mỗi ô chứa $0$ hoặc $1$.

Một hình chữ nhật được xác định bằng cách chọn một đoạn hàng liên tiếp và một đoạn cột liên tiếp, rồi lấy mọi ô nằm trong hai đoạn đó. Hình chữ nhật hợp lệ nếu tất cả các ô của nó đều chứa $1$. Diện tích là số ô bên trong hình.

Hãy tính tổng diện tích của tất cả hình chữ nhật hợp lệ. Hai hình khác nhau nếu có ít nhất một biên hàng hoặc biên cột khác nhau. Hình chỉ gồm một ô cũng được tính.

### Dữ liệu vào

- Dòng đầu chứa hai số nguyên $R,C$.
- Trong $R$ dòng tiếp theo, mỗi dòng là một xâu có đúng $C$ ký tự `0` hoặc `1`, mô tả một hàng của bảng, không có dấu cách giữa các ký tự.

### Dữ liệu ra

In tổng diện tích của tất cả hình chữ nhật hợp lệ. Không lấy phần dư theo modulo.

### Ràng buộc

- $1\le R,C\le10^6$.
- $R\cdot C\le10^6$.
- Mỗi ký tự trong bảng là `0` hoặc `1`.
- Kết quả có thể vượt phạm vi số nguyên $32$ bit; dùng số nguyên có dấu $64$ bit.

### Sample Input 1

```text
2 2
11
11
```

### Sample Output 1

```text
16
```

### Sample Input 2

```text
2 3
101
111
```

### Sample Output 2

```text
16
```

### Sample Input 3

```text
2 3
000
000
```

### Sample Output 3

```text
0
```

### Giải thích

Ở ví dụ 1, có bốn hình diện tích $1$, bốn hình diện tích $2$ và một hình diện tích $4$. Tổng là $4+8+4=16$.

Ở ví dụ 2, năm ô chứa $1$ đóng góp $5$. Ba hình nằm hoàn toàn trong hàng cuối có chiều rộng lớn hơn $1$ đóng góp $2+2+3=7$. Hai hình đứng ở cột đầu và cột cuối, mỗi hình có diện tích $2$, đóng góp $4$. Tổng bằng $16$.

Ở ví dụ 3, không có hình chữ nhật hợp lệ.
