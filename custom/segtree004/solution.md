# Lời giải — Chia thanh gỗ

### Thông tin tại mỗi nút

Mỗi nút lưu GCD các độ dài trong đoạn. Lá ở vị trí $i$ lưu $A_i$.

### Phép ghép

Ghép hai nút bằng phép lấy GCD. Giá trị trung hòa là $0$, vì $\gcd(0,x)=x$.

### Xử lý thao tác

Độ dài khúc $d$ phải là ước chung của mọi thanh trong đoạn, nên đáp án là GCD của đoạn. Dựng cây một lần rồi trả lời các truy vấn tĩnh.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi. Kết hợp với công thức trả lời ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây cần $O(N)$ phép ghép; mỗi thao tác cần $O(\log N)$ phép ghép. Một phép GCD mất $O(\log V)$, với $V=10^9$. Tổng thời gian $O((N+Q\log N)\log V)$, bộ nhớ $O(N)$.
