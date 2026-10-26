# Lời giải — Chia các bao kẹo

### Thông tin tại mỗi nút

Điều kiện chia hết từng bao tương đương với $d$ là ước chung của mọi $A_i$ trong đoạn. Do đó đáp án là ước chung lớn nhất (GCD) của đoạn. Mỗi nút lưu GCD trên đoạn của nó.

### Phép ghép

Ghép hai nút bằng phép lấy GCD. Giá trị trung hòa là $0$ vì $\gcd(0,x)=x$.

### Xử lý truy vấn

Dựng segment tree trên dãy ban đầu. Khi gán một vị trí, sửa lá tương ứng rồi tính lại các nút trên đường lên gốc. Khi truy vấn $[l,r]$, ghép thông tin của các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Tất cả số kẹo đều dương. Phép ghép dùng `std::gcd` trong C++17.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Khi hai nút con đúng, phép ghép cho đúng thông tin của đoạn cha. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi cập nhật tính lại toàn bộ các nút bị ảnh hưởng, nên tính chất này được duy trì. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi; phép ghép bảo toàn ý nghĩa thông tin và giá trị trung hòa không làm thay đổi kết quả. Vì vậy đáp án của mỗi truy vấn là đúng.

### Độ phức tạp

Cây có $O(N)$ phép ghép khi dựng và $O(\log N)$ phép ghép mỗi thao tác. Một phép GCD mất $O(\log V)$ thời gian với $V$ là giá trị lớn nhất có thể lưu ở nút; ở bài này $V=10^9$. Tổng thời gian $O((N+Q\log N)\log V)$, bộ nhớ $O(N)$.
