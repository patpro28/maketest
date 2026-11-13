## Nhận xét

Ký tự duy nhất của $S$ nằm ngay ở ô xuất phát, nên điều kiện chứa $S$ luôn đúng đối với mọi đường hợp lệ. Còn lại yêu cầu xâu đọc trên đường là đối xứng.

## Quy hoạch động từ hai đầu

Đặt $d=m+n-2$, là số bước của mỗi đường đi. Cho một con trỏ đi từ ô đầu theo hướng xuống hoặc phải, và con trỏ còn lại đi từ ô cuối theo hướng lên hoặc trái. Sau $t$ bước của mỗi con trỏ, vị trí có dạng $(x,t-x)$ và $(u,d-t-u)$ nếu dùng chỉ số từ $0$.

Chỉ giữ cặp vị trí có ký tự bằng nhau và không cấm. Điều này bảo đảm các ký tự đối xứng nhau của đường đi luôn bằng nhau. Mỗi lượt có bốn cặp lựa chọn bước di chuyển. Không để hai con trỏ vượt nhau theo hàng hay cột.

Khởi tạo tại hai đầu mút khi chúng không cấm và có ký tự giống nhau. Giá trị khởi tạo là $1\bmod D$. Thực hiện $\lfloor d/2\rfloor$ lượt. Khi kết thúc:

- Nếu $d$ chẵn, hai con trỏ phải ở cùng ô.
- Nếu $d$ lẻ, chúng phải ở hai ô kề nhau theo hàng hoặc cột.

Cộng các trạng thái kết thúc, lấy modulo $D$. Chỉ cần giữ hai lớp liên tiếp. Có thể chuyển vị bảng để số hàng bằng $r=\min(m,n)$.

## Chứng minh tính đúng đắn

Sau mỗi lượt, trạng thái đếm các cặp đoạn đường từ hai đầu đã ghép cùng số ký tự, và các cặp ký tự ở vị trí đối xứng đều bằng nhau. Bất biến đúng ở hai đầu mút. Thử bốn cặp bước đi liệt kê mọi cách mở rộng; điều kiện bằng ký tự giữ bất biến.

Ở trạng thái kết thúc, hai đoạn gặp nhau hoặc kề nhau và ghép thành đúng một đường hợp lệ. Các ký tự đã so sánh bao phủ toàn bộ xâu nên đường đó đối xứng. Ngược lại, mỗi đường đối xứng xác định duy nhất các cặp bước từ hai đầu và được đếm một lần. Vì thế tổng các trạng thái kết thúc là đáp án.

## Độ phức tạp

Thời gian $O((m+n)r^2)$ và bộ nhớ $O(r^2)$, với $r=\min(m,n)$. Số nguyên 32 bit đủ cho mỗi lần cộng hai số đã lấy dư vì $D\le10^9$.
