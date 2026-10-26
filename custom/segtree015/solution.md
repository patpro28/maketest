# Lời giải — Mã tổng kiểm tra

### Thông tin tại mỗi nút

Mỗi nút chỉ lưu tổng các phần tử trong đoạn lấy dư cho môđun $M$. Một lá chứa $x$ lưu $x\bmod M$.

### Phép ghép

Ghép hai giá trị bằng $(a+b)\bmod M$. Giá trị trung hòa là $0$.

### Xử lý thao tác

Vì phép cộng modulo có tính kết hợp, lấy dư ở từng nút vẫn thu được đúng phần dư của tổng cả đoạn. Khi cập nhật, gán lại giá trị của lá thành $x\bmod M$. Không cần lưu thêm đại lượng nào khác.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi cập nhật tính lại toàn bộ nút bị ảnh hưởng nên duy trì tính chất đó. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi. Kết hợp với công thức trả lời ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
