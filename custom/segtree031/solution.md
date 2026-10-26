# Lời giải — Chu kỳ đồng bộ

### Thông tin tại mỗi nút

Đáp án là bội chung nhỏ nhất (LCM) của các chu kỳ trong đoạn. Mỗi nút lưu LCM của đoạn mà nó quản lý.

### Phép ghép

Với hai giá trị dương $a,b$, dùng $\operatorname{lcm}(a,b)=a/\gcd(a,b)\cdot b$. Giá trị trung hòa là $1$.

### Xử lý truy vấn

Dựng segment tree trên dãy ban đầu. Khi gán một vị trí, sửa lá tương ứng rồi tính lại các nút trên đường lên gốc. Khi truy vấn $[l,r]$, ghép thông tin của các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Mọi giá trị ban đầu và giá trị sau cập nhật đều là ước của $2520$, nên LCM của bất kỳ đoạn nào cũng là ước của $2520$. Vì vậy các kết quả đều không vượt quá $2520$. Chia trước khi nhân trong công thức LCM.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Khi hai nút con đúng, phép ghép cho đúng thông tin của đoạn cha. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi cập nhật tính lại toàn bộ các nút bị ảnh hưởng, nên tính chất này được duy trì. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi; phép ghép bảo toàn ý nghĩa thông tin và giá trị trung hòa không làm thay đổi kết quả. Vì vậy đáp án của mỗi truy vấn là đúng.

### Độ phức tạp

Cây có $O(N)$ phép ghép khi dựng và $O(\log N)$ phép ghép mỗi thao tác. Một phép GCD mất $O(\log V)$ thời gian với $V$ là giá trị lớn nhất có thể lưu ở nút; ở bài này $V=2520$. Tổng thời gian $O((N+Q\log N)\log V)$, bộ nhớ $O(N)$.
