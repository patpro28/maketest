# Lời giải — HASHING009

Dùng Heavy-Light Decomposition (HLD) để phân rã một đường đi thành $O(\log n)$ đoạn trên các chuỗi nặng. Sắp các đỉnh theo thứ tự trong chuỗi nặng và dựng segment tree lưu độ dài, hash xuôi, hash ngược theo hai modulo.

Khi lấy thông điệp $u\to v$, duy trì hai kết quả: phần đã đọc từ phía $u$ và phần sẽ đọc ở phía $v$. Nếu xử lý một đoạn ở phía $u$, lấy hash đoạn từ đầu chuỗi đến $u$, đảo chiều bằng cách đổi hash xuôi với hash ngược, rồi nối vào cuối kết quả bên trái. Nếu xử lý phía $v$, lấy đoạn theo chiều xuôi và nối vào đầu kết quả bên phải.

Khi hai đỉnh còn lại nằm trên cùng chuỗi, lấy đoạn giữa chúng, đổi chiều nếu cần, rồi nối phần trái, đoạn giữa và phần phải. Đỉnh chung được lấy đúng một lần. So sánh cả độ dài và hash xuôi của hai thông điệp.

Phép ghép $AB$ dùng công thức $H(AB)=H(A)\cdot B_0^{|B|}+H(B)$. Chiều ngược phải ghép theo thứ tự đảo lại. Vì phép nối không giao hoán, việc giữ thứ tự là bắt buộc.

Dựng HLD và segment tree trong $O(n)$; mỗi truy vấn $O(\log^2 n)$; bộ nhớ $O(n)$. Duyệt cây bằng ngăn xếp hoặc thứ tự duyệt lặp để tránh tràn ngăn xếp với cây dạng đường thẳng.

Lời giải tham khảo dùng hai modulo khác nhau để giảm xác suất va chạm hash. Hash là kỹ thuật xác suất; chứng minh tính đúng đắn ở trên giả sử các đoạn được so sánh không va chạm.
