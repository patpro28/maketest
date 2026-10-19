# STRINGA1 — Đoạn số ngắn nhất

### Đề bài

Cho một số nguyên dương $K$ và một xâu $S$ chỉ gồm các chữ cái tiếng Anh (chữ hoa, chữ thường) và chữ số.

Một **đoạn số** là một dãy không rỗng gồm các chữ số liên tiếp trong $S$ và không thể kéo dài thêm sang trái hoặc sang phải bằng một chữ số. Nói cách khác, ký tự ngay trước và ngay sau đoạn (nếu có) đều phải là chữ cái. Không được chọn một phần bên trong một đoạn số.

Giá trị của một đoạn số là số nguyên không âm được biểu diễn bởi các chữ số của đoạn đó. Các chữ số $0$ ở đầu không làm thay đổi giá trị nhưng **vẫn được tính vào độ dài**. Đoạn chỉ gồm chữ số $0$ có giá trị bằng $0$ và chia hết cho mọi số nguyên dương $K$.

Hãy tìm độ dài **nhỏ nhất** trong các đoạn số có giá trị chia hết cho $K$. Nếu không có đoạn số nào thỏa mãn, kết quả là $0$.

### Dữ liệu vào

- Dòng đầu chứa số nguyên $K$.
- Dòng thứ hai chứa xâu $S$.

### Dữ liệu ra

In một số nguyên là độ dài nhỏ nhất trong các đoạn số có giá trị chia hết cho $K$; in $0$ nếu không có đoạn số nào thỏa mãn.

### Ràng buộc

- $1\le K\le9$.
- $1\le |S|\le10^5$, trong đó $|S|$ là độ dài của xâu $S$.
- Mỗi ký tự của $S$ là một chữ cái tiếng Anh hoặc một chữ số từ $0$ đến $9$.

### Subtask

| Subtask | Tỉ lệ | Ràng buộc bổ sung |
| --- | --- | --- |
| 1 | 50% | $K=1$ |
| 2 | 30% | Giá trị của mọi đoạn số trong $S$ không vượt quá $10^{12}$ |
| 3 | 20% | Không có ràng buộc bổ sung |

### Sample Input 1

```text
3
ab12cd0036ef12345
```

### Sample Output 1

```text
2
```

### Sample Input 2

```text
7
abc13XYZ25
```

### Sample Output 2

```text
0
```

### Sample Input 3

```text
8
A0000b1232C16
```

### Sample Output 3

```text
2
```

### Giải thích

Ở ví dụ 1, có ba đoạn số là `12`, `0036`, `12345`, có độ dài lần lượt là $2,4,5$. Cả ba đều có giá trị chia hết cho $3$, nên độ dài nhỏ nhất là $2$.

Ở ví dụ 2, có hai đoạn số là `13` và `25`. Không đoạn nào có giá trị chia hết cho $7$, nên kết quả là $0$.

Ở ví dụ 3, có ba đoạn số là `0000`, `1232`, `16`, có độ dài lần lượt là $4,4,2$. Giá trị của chúng lần lượt là $0,1232,16$ và đều chia hết cho $8$, nên độ dài nhỏ nhất là $2$.
