# Lời giải — Ngăn dòng nước

### Trạng thái

Chọn điểm $1$ làm gốc. Các lá khác gốc chính là các đầu ra được xác định trong hệ thống ban đầu.

Gọi $dp[u]$ là chi phí nhỏ nhất khi chỉ được cắt các cạnh trong cây con của $u$, để $u$ không nối được đến bất kỳ đầu ra ban đầu nào thuộc cây con đó. Cạnh nối $u$ với cha không nằm trong trạng thái này.

Nếu $u$ là đầu ra, không thể tách $u$ khỏi chính nó bằng cách cắt cạnh phía dưới. Do đó $dp[u]=+\infty$.

### Chuyển trạng thái

Xét người con $v$ của $u$, với cạnh nối có chi phí $w_{uv}$. Có hai lựa chọn:

- Cắt cạnh $(u,v)$, tốn $w_{uv}$ và ngăn được mọi đầu ra trong nhánh.
- Giữ cạnh $(u,v)$ và xử lý bên trong cây con của $v$, tốn $dp[v]$.

Các nhánh con không dùng chung cạnh, nên với đỉnh không phải đầu ra:

$$
dp[u]=\sum_{v\text{ là con của }u}\min(w_{uv},dp[v]).
$$

Đáp án là $dp[1]$. Gốc không phải đầu ra kể cả khi bậc của nó bằng $1$.

### Tính đúng đắn

Trạng thái tại một đầu ra là bất khả thi đúng theo định nghĩa. Giả sử trạng thái ở các con đã đúng. Với từng nhánh, mọi phương án đều hoặc cắt cạnh đầu nhánh, hoặc giữ cạnh đó. Trong trường hợp giữ cạnh, nước đến được người con nên toàn bộ đầu ra trong cây con ấy phải được chặn bên dưới; chi phí tối ưu chính là $dp[v]$.

Hai lựa chọn bao phủ mọi phương án, và mỗi nhánh độc lập về cả tính khả thi lẫn chi phí. Vì vậy lấy giá trị nhỏ nhất từng nhánh rồi cộng là tối ưu. Theo quy nạp, $dp[1]$ là chi phí nhỏ nhất để chặn mọi đầu ra.

### Cài đặt và độ phức tạp

Duyệt cây không đệ quy, lưu cha và chi phí cạnh lên cha. Xử lý các đỉnh theo thứ tự ngược, cộng đóng góp của mỗi đỉnh vào cha. Khi nhận diện đầu ra, phải dùng bậc trong cây ban đầu và loại trừ gốc.

Thời gian $O(N)$, bộ nhớ $O(N)$. Đáp án có thể đạt $(N-1)\cdot10^9$, cần số nguyên 64 bit. Có thể dùng $2^{60}$ làm $+\infty$; luôn lấy min với chi phí cạnh trước khi cộng vào cha.
