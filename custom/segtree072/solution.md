# Lời giải — Đóng gói hàng hóa

### Thông tin tại mỗi nút

Mỗi nút lưu GCD $g$ và tổng $S$ của các lượng hàng trên đoạn. Lá chứa $x$ lưu $(x,x)$.

### Phép ghép

Ghép GCD bằng phép lấy GCD và ghép tổng bằng phép cộng. Nút trung hòa là $(0,0)$.

### Xử lý thao tác

Mỗi lần gán sửa lá tương ứng và tính lại các nút trên đường lên gốc. Mỗi truy vấn ghép các đoạn con rời nhau theo thứ tự trái sang phải để thu được thông tin của đoạn cần hỏi.

Kích thước gói lớn nhất là $g$, vì nó phải chia hết lượng hàng của từng kho. Tổng số gói bằng $\sum A_i/g=S/g$. Mọi lượng hàng đều dương nên $g>0$ trên đoạn truy vấn. Dùng số nguyên 64 bit để lưu tổng và số gói.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Cập nhật tính lại tất cả nút bị ảnh hưởng nên duy trì tính chất đó. Truy vấn ghép đúng các đoạn con phủ đoạn cần hỏi; kết hợp với công thức tính đáp án ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây cần $O(N)$ phép ghép; mỗi thao tác cần $O(\log N)$ phép ghép. Mỗi phép GCD mất $O(\log V)$ với $V=10^9$. Tổng thời gian $O((N+Q\log N)\log V)$, bộ nhớ $O(N)$.
