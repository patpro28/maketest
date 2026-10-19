# Lời giải — Các cụm màu liên tiếp

### Thông tin lưu tại mỗi nút

Mỗi nút lưu màu của ô đầu, màu của ô cuối và số cụm trong đoạn. Một lá có đúng $1$ cụm.

### Phép ghép

Khi ghép đoạn trái $L$ với đoạn phải $R$, màu đầu lấy từ $L$, màu cuối lấy từ $R$. Số cụm bằng tổng số cụm của hai đoạn, trừ $1$ nếu màu cuối của $L$ bằng màu đầu của $R$.

### Cập nhật và truy vấn

Dựng segment tree trên dãy ban đầu. Khi cập nhật một vị trí, sửa lá tương ứng rồi tính lại các nút trên đường từ lá đến gốc. Khi truy vấn đoạn $[l,r]$, ghép thông tin của các đoạn con được cây tách ra.

Phải ghép theo thứ tự từ trái sang phải vì thông tin màu đầu và màu cuối phụ thuộc thứ tự. Nút rỗng có $0$ cụm; ghép nó với nút nào thì trả lại nút đó. Đáp án là số cụm của nút kết quả.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Nếu thông tin của hai nút con đúng, phép ghép ở trên cho đúng thông tin của đoạn cha. Vì vậy, bằng quy nạp theo chiều cao cây, mọi nút đều lưu đúng thông tin sau khi dựng cây. Mỗi cập nhật tính lại tất cả nút bị ảnh hưởng nên duy trì tính chất này. Truy vấn ghép các đoạn con rời nhau theo đúng thứ tự để thu được thông tin của toàn bộ đoạn cần hỏi; do đó đáp án được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian là $O(N+Q\log N)$, bộ nhớ $O(N)$.
