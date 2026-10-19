# Lời giải — Điểm cao nhất

### Thông tin lưu tại mỗi nút

Mỗi nút lưu cặp `(mx, cnt)`: điểm cao nhất trong đoạn và số lần điểm đó xuất hiện. Tại lá, `cnt = 1`.

### Phép ghép

Nếu hai nút có `mx` khác nhau, lấy toàn bộ cặp của nút có `mx` lớn hơn. Nếu bằng nhau, giữ `mx` và cộng hai số đếm.

### Cập nhật và truy vấn

Dựng segment tree trên dãy ban đầu. Khi cập nhật một vị trí, sửa lá tương ứng rồi tính lại các nút trên đường từ lá đến gốc. Khi truy vấn đoạn $[l,r]$, ghép thông tin của các đoạn con được cây tách ra.

Đáp án là cặp `(mx, cnt)` của đoạn. Nút rỗng có `mx = -∞`, `cnt = 0`; không dùng $0$ làm điểm lớn nhất mặc định vì điểm có thể âm.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Nếu thông tin của hai nút con đúng, phép ghép ở trên cho đúng thông tin của đoạn cha. Vì vậy, bằng quy nạp theo chiều cao cây, mọi nút đều lưu đúng thông tin sau khi dựng cây. Mỗi cập nhật tính lại tất cả nút bị ảnh hưởng nên duy trì tính chất này. Truy vấn ghép các đoạn con rời nhau theo đúng thứ tự để thu được thông tin của toàn bộ đoạn cần hỏi; do đó đáp án được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian là $O(N+Q\log N)$, bộ nhớ $O(N)$.
