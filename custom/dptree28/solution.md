# Lời giải — Điều chỉnh cây biểu thức

### Trạng thái

Gọi $dp[u][r]$ là tổng chi phí nhỏ nhất ở các lá thuộc cây con của $u$ để giá trị tại $u$ bằng $r$, với $r\in\{0,1,2\}$.

Tại lá, $dp[u][r]=C_{u,r}$.

### Ghép hai người con

Nếu $u$ có hai con $x,y$, khởi tạo cả ba giá trị bằng $+\infty$ rồi thử mọi cặp $a,b\in\{0,1,2\}$:

- Nếu $u$ là phép cộng, đặt $r=(a+b)\bmod3$.
- Nếu $u$ là phép nhân, đặt $r=(ab)\bmod3$.

Cập nhật:

$$
dp[u][r]=\min(dp[u][r],dp[x][a]+dp[y][b]).
$$

Mỗi đỉnh trong chỉ cần thử chín cặp. Đáp án là $dp[1][R]$.

### Tính đúng đắn

Tại lá, trạng thái chính là chi phí của lựa chọn bắt buộc. Với một đỉnh trong, mọi cách gán các lá xác định duy nhất giá trị $a,b$ tại hai người con. Giá trị của đỉnh cha được tính đúng bằng phép toán cố định và lấy dư.

Hai cây con không dùng chung lá, nên sau khi cố định $a,b$, tổng chi phí nhỏ nhất bằng tổng hai trạng thái. Thử đủ chín cặp bao phủ mọi khả năng; lấy min cho từng số dư cho kết quả tối ưu. Quy nạp theo cây chứng minh trạng thái đúng tại mọi đỉnh, đặc biệt tại gốc.

Mỗi cây con có thể đạt cả ba số dư. Điều này đúng tại lá; phép cộng có thể tạo $r$ từ $(0,r)$, phép nhân có thể tạo $r$ từ $(1,r)$. Vì vậy đáp án luôn hữu hạn.

### Độ phức tạp và cài đặt

Thời gian $O(N)$, bộ nhớ $O(N)$. Dùng số nguyên 64 bit; tổng chi phí không vượt số lá nhân $10^9$.

Đọc toàn bộ mô tả trước khi tính. Nhãn con có thể nhỏ hơn nhãn cha, nên không thể chỉ xử lý theo thứ tự nhãn giảm dần. Duyệt từ gốc bằng danh sách, sau đó xử lý ngược thứ tự thăm. Cách này cũng xử lý được cây nhị phân có độ sâu gần $N/2$ mà không cần đệ quy.
