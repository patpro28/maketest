### Đề bài

Cho một lưới vuông kích thước $H\times W$ gồm $H$ hàng ngang và $W$ cột dọc. Kí hiệu $(i, j)$ là ô ở hàng thứ $i$ tính từ trên xuống và cột thứ $j$ tính từ trái sang.

Trên lưới có một quân xe (rook), ban đầu đặt tại ô $(x_1, y_1)$. Quân sẽ thực hiện $K$ thao tác sau đây:

- Mỗi thao tác, di chuyển quân xe sang một ô khác nằm cùng hàng hoặc cùng cột với ô hiện tại (tức là phải đổi ô, không được đứng yên).

Hỏi có bao nhiêu cách thực hiện đúng $K$ thao tác để kết thúc quân xe ở ô $(x_2, y_2)$? Vì đáp án có thể rất lớn, hãy in ra kết quả theo modulo $998244353$.

### Dữ liệu vào

- Dòng đầu chứa 3 số nguyên $H, W, K$.
- Dòng hai chứa 4 số nguyên $x_1, y_1, x_2, y_2$.

### Dữ liệu ra

In ra một số nguyên: số cách thực hiện đúng $K$ thao tác để từ $(x_1,y_1)$ đến $(x_2,y_2)$, lấy modulo $998244353$.

### Giới hạn

- $2 \le H, W \le 10^9$.
- $1 \le K \le 10^6$.
- $1 \le x_1, x_2 \le H$.
- $1 \le y_1, y_2 \le W$.

### Sample Input 1
    2 2 2
    1 2 2 1

### Sample Output 1
    2

### Sample Input 2
    3 3 3
    1 3 3 3

### Sample Output 2
    9

### Giải thích

Trong ví dụ đầu tiên, có hai cách di chuyển là:

- $(1, 2) \to (2, 2) \to (2, 1)$
- $(1, 2) \to (1, 1) \to (2, 1)$