# Lời giải — Các vị trí đạt chuẩn

### Thông tin tại mỗi nút

Đặt $B_i=1$ nếu $A_i\ge K$ và $B_i=0$ nếu ngược lại. Mỗi nút lưu tổng $B_i$ trên đoạn của nó.

### Phép ghép

Ghép hai nút bằng phép cộng. Giá trị trung hòa là $0$.

### Xử lý truy vấn

Dựng segment tree một lần trên dãy ban đầu. Với truy vấn $[l,r]$, ghép thông tin của các nút đại diện cho các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Ngưỡng $K$ cố định nên chỉ cần phân loại từng phần tử một lần khi đọc dữ liệu. Chú ý điều kiện có dấu bằng.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Khi hai nút con đúng, phép ghép cho đúng thông tin của đoạn cha. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi; phép ghép bảo toàn ý nghĩa thông tin và giá trị trung hòa không làm thay đổi kết quả. Vì vậy đáp án của mỗi truy vấn là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian, mỗi truy vấn mất $O(\log N)$. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
