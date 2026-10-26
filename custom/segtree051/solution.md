# Lời giải — Đếm bội số

### Thông tin tại mỗi nút

Mỗi lá lưu $1$ nếu phần tử tương ứng chia hết cho $K$, ngược lại lưu $0$. Mỗi nút lưu tổng các giá trị lá trong đoạn.

### Phép ghép

Ghép hai nút bằng phép cộng. Giá trị trung hòa là $0$.

### Xử lý thao tác

Khi gán một phần tử, tính lại điều kiện `x % K == 0` rồi cập nhật lá. Điều kiện này đúng cả với số âm và số $0$; không cần lưu giá trị của phần tử trong các nút trên cây.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi cập nhật tính lại toàn bộ nút bị ảnh hưởng nên duy trì tính chất đó. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi. Kết hợp với công thức trả lời ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
