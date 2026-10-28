# Lời giải — Hoàn thành nhiệm vụ

### Ba câu hỏi để xây dựng lời giải

**Cần tính gì tại đỉnh $u$?** Gọi $dp[u]$ là chi phí nhỏ nhất để hoàn thành nhiệm vụ $u$.

**Một lá trả về gì?** Lá không có phương án giao cho các con, nên $dp[u]=C_u$.

**Cha dùng kết quả các con thế nào?** Với đỉnh có con, có đúng hai phương án:

- Thuê trọn gói tại $u$, tốn $C_u$.
- Hoàn thành tất cả nhiệm vụ con, tốn tổng chi phí tối ưu của chúng.

Vì thế, chỉ với đỉnh có con:

$$
dp[u]=\min\left(C_u,\sum_{v\text{ là con của }u}dp[v]\right).
$$

Đáp án là $dp[1]$.

### Phân biệt phép cộng với phép lấy nhỏ nhất

Trong phương án làm các nhiệm vụ con, tất cả các con đều phải được hoàn thành, nên cộng các chi phí.

Giữa phương án làm các con và phương án thuê trọn gói, chỉ cần chọn một, nên lấy nhỏ nhất.

Không cộng thêm $C_u$ vào phương án làm các con. Cũng không áp dụng tổng rỗng bằng $0$ cho lá, vì đề không cho phép hoàn thành miễn phí một nhiệm vụ lá.

Trong ví dụ đầu, $dp[3]=\min(15,4+5)=9$. Sau đó $dp[1]=\min(20,6+9)=15$.

### Chứng minh tính đúng đắn

Tại lá, thuê trọn gói là phương án duy nhất nên trạng thái đúng.

Giả sử kết quả ở các con của $u$ đã tối ưu. Mọi phương án hoàn thành $u$ hoặc thuê ngay tại $u$, hoặc hoàn thành tất cả các con. Trong trường hợp thứ hai, các cây nhiệm vụ con không dùng chung nhiệm vụ và chi phí được cộng độc lập; vì vậy tổng nhỏ nhất chính là tổng các $dp[v]$. Lấy nhỏ nhất giữa hai phương án bao phủ mọi cách hoàn thành hợp lệ. Quy nạp từ lá lên gốc chứng minh đáp án.

### Độ phức tạp và lưu ý cài đặt

Thời gian $O(N)$, bộ nhớ $O(N)$. Duyệt không đệ quy để lưu cha, sau đó xử lý ngược thứ tự thăm.

Mặc dù đáp án tại gốc không vượt $C_1\le10^9$, tổng chi phí các con trước khi lấy min có thể lớn hơn giới hạn 32 bit. Cần dùng số nguyên 64 bit cho cả tổng trung gian.
