# Lời giải — Nhật ký lượng mưa

### Thông tin tại mỗi nút

Mỗi nút lưu tổng lượng mưa trong đoạn mà nút quản lý. Lá ở vị trí $i$ lưu $A_i$.

### Phép ghép

Tổng của một đoạn bằng tổng của hai đoạn con. Giá trị trung hòa khi không có phần tử là $0$.

### Xử lý truy vấn

Dựng segment tree một lần trên dãy ban đầu. Với truy vấn $[l,r]$, ghép thông tin của các nút đại diện cho các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Dùng số nguyên 64 bit vì đáp án có thể đạt $N\cdot10^9=2\cdot10^{14}$.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Khi hai nút con đúng, phép ghép cho đúng thông tin của đoạn cha. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi; phép ghép bảo toàn ý nghĩa thông tin và giá trị trung hòa không làm thay đổi kết quả. Vì vậy đáp án của mỗi truy vấn là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian, mỗi truy vấn mất $O(\log N)$. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
