# Lời giải — Nhịp chênh lệch

### Thông tin tại mỗi nút

Đặt $D_1=0$ và $D_i=|A_i-A_{i-1}|$ với $2\le i\le N$. Dựng segment tree lưu GCD trên mảng $D$. Mỗi lá lưu một phần tử $D_i$.

### Phép ghép

Ghép hai nút bằng phép GCD. Giá trị trung hòa là $0$ vì $\gcd(0,x)=x$.

### Xử lý thao tác

Dựng cây trên các giá trị ban đầu. Khi cập nhật một lá, tính lại các nút trên đường lên gốc. Truy vấn ghép thông tin của các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Nếu $l=r$, trả về $0$. Nếu $l<r$, lấy GCD của $D_{l+1},\ldots,D_r$. Khi gán $A_i=x$, chỉ cần tính lại $D_i$ nếu $i>1$ và $D_{i+1}$ nếu $i<N$, rồi cập nhật tối đa hai lá. Cách đặt $D_1=0$ giúp dựng cây thống nhất cả khi $N=1$. Dùng số nguyên 64 bit khi tính hiệu và trị tuyệt đối.

### Tính đúng đắn

Tại mỗi lá, thông tin đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng; vì vậy, bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi lần cập nhật tính lại mọi nút bị ảnh hưởng nên duy trì tính chất này. Một phép gán chỉ làm thay đổi tối đa hai chênh lệch kề vị trí đó, và thuật toán đã cập nhật đủ các chênh lệch này. Truy vấn ghép các đoạn con phủ đúng đoạn cần hỏi, còn nút rỗng không làm thay đổi kết quả. Các phần tử $D_{l+1},\ldots,D_r$ chính xác là các chênh lệch kề nhau bên trong $[l,r]$. Do đó đáp án được in là đúng.

### Độ phức tạp

Dựng cây cần $O(N)$ phép GCD; mỗi cập nhật hoặc truy vấn cần $O(\log N)$ phép GCD. Với $V=2\cdot10^9$ là chênh lệch lớn nhất, mỗi phép GCD mất $O(\log V)$ thời gian. Tổng thời gian $O((N+Q\log N)\log V)$, bộ nhớ $O(N)$.
