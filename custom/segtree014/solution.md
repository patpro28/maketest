# Lời giải — Ghi nhận doanh số

### Thông tin tại mỗi nút

Mỗi nút lưu tổng doanh số của đoạn. Lá ở vị trí $i$ lưu doanh số hiện tại của cửa hàng đó.

### Phép ghép

Ghép hai nút bằng phép cộng. Giá trị trung hòa là $0$.

### Xử lý thao tác

Khi nhận `1 i x`, cộng $x$ vào giá trị của lá rồi tính lại các nút trên đường lên gốc. Không thay giá trị của lá bằng $x$. Dùng số nguyên 64 bit: tổng doanh số không vượt $(N+Q)\cdot10^9\le4\cdot10^{14}$.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi cập nhật tính lại toàn bộ nút bị ảnh hưởng nên duy trì tính chất đó. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi. Kết hợp với công thức trả lời ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
