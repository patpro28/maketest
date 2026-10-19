# Lời giải — Bảng đèn

### Thông tin lưu tại mỗi nút

Mỗi nút lưu số đèn sáng trong đoạn. Tại lá, giá trị là trạng thái $0$ hoặc $1$ của đèn.

### Phép ghép

Giá trị của nút cha bằng tổng giá trị của hai nút con.

### Cập nhật và truy vấn

Dựng segment tree trên dãy ban đầu. Khi cập nhật một vị trí, sửa lá tương ứng rồi tính lại các nút trên đường từ lá đến gốc. Khi truy vấn đoạn $[l,r]$, ghép thông tin của các đoạn con được cây tách ra.

Khi đảo đèn, thay giá trị của lá từ $v$ thành $1-v$. Đáp án truy vấn là tổng trên đoạn; giá trị trung hòa bằng $0$.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Nếu thông tin của hai nút con đúng, phép ghép ở trên cho đúng thông tin của đoạn cha. Vì vậy, bằng quy nạp theo chiều cao cây, mọi nút đều lưu đúng thông tin sau khi dựng cây. Mỗi cập nhật tính lại tất cả nút bị ảnh hưởng nên duy trì tính chất này. Truy vấn ghép các đoạn con rời nhau theo đúng thứ tự để thu được thông tin của toàn bộ đoạn cần hỏi; do đó đáp án được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian là $O(N+Q\log N)$, bộ nhớ $O(N)$.
