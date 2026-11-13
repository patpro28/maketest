## Ý tưởng

Dùng quy hoạch động từ hai đầu để bảo đảm xâu đối xứng. Thêm một bit $q$ cho biết ký tự duy nhất của $S$ đã xuất hiện trong các ô được xử lý hay chưa.

## Quy hoạch động từ hai đầu

Đặt $d=m+n-2$, là số bước của mỗi đường đi. Cho một con trỏ đi từ ô đầu theo hướng xuống hoặc phải, và con trỏ còn lại đi từ ô cuối theo hướng lên hoặc trái. Sau $t$ bước của mỗi con trỏ, vị trí có dạng $(x,t-x)$ và $(u,d-t-u)$ nếu dùng chỉ số từ $0$.

Chỉ giữ cặp vị trí có ký tự bằng nhau và không cấm. Điều này bảo đảm các ký tự đối xứng nhau của đường đi luôn bằng nhau. Mỗi lượt có bốn cặp lựa chọn bước di chuyển. Không để hai con trỏ vượt nhau theo hàng hay cột.

Khởi tạo tại hai đầu mút khi chúng không cấm và có ký tự giống nhau. Giá trị khởi tạo là $1\bmod D$. Thực hiện $\lfloor d/2\rfloor$ lượt. Khi kết thúc:

- Nếu $d$ chẵn, hai con trỏ phải ở cùng ô.
- Nếu $d$ lẻ, chúng phải ở hai ô kề nhau theo hàng hoặc cột.

Cộng các trạng thái kết thúc, lấy modulo $D$. Chỉ cần giữ hai lớp liên tiếp. Có thể chuyển vị bảng để số hàng bằng $r=\min(m,n)$.

## Theo dõi ký tự bắt buộc

Đặt trạng thái $dp[x][u][q]$ ở lớp $t$. Ban đầu $q$ bằng $1$ nếu ký tự ở ô xuất phát bằng $S$, ngược lại bằng $0$. Khi thêm cặp ô có cùng ký tự $c$, cập nhật

$$q'=q\lor[c=S].$$

Nếu hai con trỏ gặp ở ô giữa thì ô đó vẫn được ghi nhận, dù không có ô đối xứng riêng biệt. Sau cùng chỉ cộng các trạng thái có $q=1$.

## Chứng minh tính đúng đắn

Bất biến của quy hoạch động từ hai đầu bảo đảm trạng thái đếm đúng các cặp đoạn có các ký tự đối xứng bằng nhau. Bit $q$ ban đầu ghi đúng sự xuất hiện ở hai đầu và phép lấy OR ghi đúng việc xuất hiện thêm ở cặp ô mới. Bởi hai ô mới có cùng ký tự, chỉ cần xét một trong hai.

Khi hai đoạn ghép được, chúng bao phủ toàn bộ đường đi, nên $q=1$ tương đương xâu chứa ký tự $S$. Mỗi đường có một cách tách thành các cặp đoạn theo lớp, do đó không bị đếm lặp. Chỉ cộng trạng thái kết thúc có bit $1$ cho đúng số đường thắng cuộc.

## Độ phức tạp

Thời gian $O((m+n)r^2)$, bộ nhớ $O(r^2)$ với $r=\min(m,n)$; chiều bit chỉ có hai giá trị.
