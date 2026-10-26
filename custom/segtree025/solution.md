# Lời giải — Bậc thang cao nhất

### Thông tin tại mỗi nút

Đặt $D_1=0$ và $D_i=|A_i-A_{i-1}|$ với $2\le i\le N$. Mỗi nút lưu giá trị lớn nhất trên đoạn tương ứng của mảng $D$.

### Phép ghép

Ghép hai nút bằng phép lấy max. Giá trị trung hòa là $0$ vì mọi $D_i$ đều không âm.

### Xử lý thao tác

Nếu $l=r$, trả về $0$. Nếu $l<r$, truy vấn max trên đoạn $D_{l+1},\ldots,D_r$. Khi sửa $A_i$, chỉ cần tính lại $D_i$ nếu $i>1$ và $D_{i+1}$ nếu $i<N$, rồi cập nhật tối đa hai lá. Dùng số nguyên 64 bit khi tính hiệu và trị tuyệt đối.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi cập nhật tính lại toàn bộ nút bị ảnh hưởng nên duy trì tính chất đó. Một lần sửa độ cao chỉ ảnh hưởng tối đa hai chênh lệch kề nó, và thuật toán đã cập nhật đủ hai chênh lệch này. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi. Kết hợp với công thức trả lời ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
