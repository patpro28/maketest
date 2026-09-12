### Đề bài

Cho một bảng hình chữ nhật kích thước $n \times n$, ban đầu tất cả các ô đều có màu trắng trừ ô ở vị trí $(x, y)$ có màu đen. 

Bạn cần thực hiện $n^2$ thao tác, mỗi thao tác yêu cầu bạn tính khoảng cách nhỏ nhất từ một ô trắng $(i, j)$ đến một ô đen trong bảng. Sau khi tính khoảng cách, bạn sẽ tô ô trắng $(i, j)$ thành màu đen.

Khoảng cách giữa hai ô $(a, b)$ và $(c, d)$ được tính bằng công thức $|a - c| + |b - d|$.

### Dữ liệu vào

- Dòng đầu tiên chứa ba số nguyên dương $n$, $x$, $y$ ($1 \le n \le 500$, $1 \le x, y \le n$) - kích thước bảng và vị trí của ô đen ban đầu.
- Tiếp theo là $n^2$ dòng, mỗi dòng chứa hai số nguyên dương $i$, $j$ ($1 \le i, j \le n$) - vị trí của ô trắng cần tính khoảng cách và tô thành đen.
- Các ô trắng được yêu cầu trong các thao tác là duy nhất và không bao gồm ô đen ban đầu.

### Dữ liệu ra

In ra một dòng chứa $n^2$ số nguyên - khoảng cách nhỏ nhất từ ô trắng được yêu cầu trong thao tác đó đến một ô đen trong bảng trước khi tô nó thành đen.

### Sample Input

```
3 3 1
3 3
2 3
1 3
1 1
1 2
2 1
3 2
2 2
```

### Sample Output

```
2 1 1 2 1 1 1 1 
```
