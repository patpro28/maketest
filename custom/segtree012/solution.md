# Lời giải — Thu và chi

### Thông tin tại mỗi nút

Mỗi nút lưu tổng thu `income` và tổng chi không âm `expense`. Một lá chứa giá trị $x$ lưu $(\max(x,0),\max(-x,0))$.

### Phép ghép

Cộng riêng hai tổng thu và hai tổng chi. Nút trung hòa là $(0,0)$.

### Xử lý thao tác

Dựng cây trên các giá trị ban đầu. Khi cập nhật một lá, tính lại các nút trên đường lên gốc. Truy vấn ghép thông tin của các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Cập nhật là phép gán; khoản thu có thể đổi thành khoản chi hoặc ngược lại. Dùng số nguyên 64 bit vì mỗi tổng có thể đạt $2\cdot10^{14}$.

### Tính đúng đắn

Tại mỗi lá, thông tin đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng; vì vậy, bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi lần cập nhật tính lại mọi nút bị ảnh hưởng nên duy trì tính chất này. Truy vấn ghép các đoạn con phủ đúng đoạn cần hỏi, còn nút rỗng không làm thay đổi kết quả. Do đó đáp án được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian, mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
