# Lời giải — Sai số bình phương

### Thông tin tại mỗi nút

Mỗi nút lưu tổng $S=\sum A_i$ và tổng bình phương $T=\sum A_i^2$. Một lá chứa $x$ lưu $(x,x^2)$.

### Phép ghép

Cộng riêng hai tổng. Nút trung hòa là $(0,0)$.

### Xử lý thao tác

Mỗi lần gán sửa lá tương ứng và tính lại các nút trên đường lên gốc. Mỗi truy vấn ghép các đoạn con rời nhau theo thứ tự trái sang phải để thu được thông tin của đoạn cần hỏi.

Khai triển $\sum(A_i-c)^2=T-2cS+(r-l+1)c^2$. Chỉ cần truy vấn hai tổng rồi áp dụng công thức. Dùng số nguyên 64 bit cho các phép nhân và kết quả; đáp án tối đa là $200000\cdot20000^2=8\cdot10^{13}$.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Cập nhật tính lại tất cả nút bị ảnh hưởng nên duy trì tính chất đó. Truy vấn ghép đúng các đoạn con phủ đoạn cần hỏi; kết hợp với công thức tính đáp án ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian; mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
