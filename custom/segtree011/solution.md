# Lời giải — Kho hàng

### Thông tin tại mỗi nút

Mỗi nút lưu tổng lượng hàng trên đoạn. Lá ở vị trí $i$ lưu $A_i$.

### Phép ghép

Ghép hai nút bằng phép cộng. Giá trị trung hòa là $0$.

### Xử lý truy vấn

Dựng segment tree trên dãy ban đầu. Khi gán một vị trí, sửa lá tương ứng rồi tính lại các nút trên đường lên gốc. Khi truy vấn $[l,r]$, ghép thông tin của các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Khi cập nhật, thay giá trị tại lá bằng $x$, không cộng $x$ vào giá trị cũ. Dùng số nguyên 64 bit vì tổng có thể đạt $2\cdot10^{14}$.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Khi hai nút con đúng, phép ghép cho đúng thông tin của đoạn cha. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi cập nhật tính lại toàn bộ các nút bị ảnh hưởng, nên tính chất này được duy trì. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi; phép ghép bảo toàn ý nghĩa thông tin và giá trị trung hòa không làm thay đổi kết quả. Vì vậy đáp án của mỗi truy vấn là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
