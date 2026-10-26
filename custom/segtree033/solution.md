# Lời giải — Chu kỳ vượt giới hạn

### Thông tin tại mỗi nút

Mỗi nút lưu LCM của đoạn nếu LCM không vượt $B$; nếu vượt, lưu giá trị đại diện $B+1$. Lá chứa $x$ lưu $\min(x,B+1)$.

### Phép ghép

Nếu một trong hai giá trị lớn hơn $B$, trả về $B+1$. Nếu không, đặt $t=a/\gcd(a,b)$. Nếu $t>\lfloor B/b\rfloor$, trả về $B+1$; ngược lại trả về $t\cdot b$. Giá trị trung hòa là $1$.

### Xử lý thao tác

Phải kiểm tra phép chia giới hạn trước khi nhân để không tràn số. Một đoạn có LCM vượt $B$ thì mọi đoạn lớn hơn chứa nó cũng có LCM vượt $B$, nên giá trị đại diện không làm mất thông tin cần cho truy vấn. Với một lần cập nhật, các nút trên đường lên gốc được tính lại hoàn toàn và có thể trở về giá trị hợp lệ. Dùng số nguyên 64 bit cho $B$, giá trị đại diện và các phép tính.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Phép ghép tính đúng LCM khi không vượt giới hạn và trả về giá trị đại diện chính xác khi vượt giới hạn. Vì việc thêm phần tử không thể làm LCM nhỏ đi, giá trị đại diện vẫn đủ cho mọi lần ghép sau. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi cập nhật tính lại toàn bộ nút bị ảnh hưởng nên duy trì tính chất đó. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi. Kết hợp với công thức trả lời ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây cần $O(N)$ phép ghép; mỗi thao tác cần $O(\log N)$ phép ghép. Một phép GCD mất $O(\log V)$, với $V=\max(B,10^9)$. Tổng thời gian $O((N+Q\log N)\log V)$, bộ nhớ $O(N)$.
