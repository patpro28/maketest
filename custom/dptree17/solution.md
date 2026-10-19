# Lời giải — Đếm tập độc lập

### Trạng thái

Chọn đỉnh $1$ làm gốc. Với cây con gốc $u$, đặt:

- $dp_0[u]$: số tập độc lập không chứa $u$.
- $dp_1[u]$: số tập độc lập chứa $u$.

Mọi phép toán đếm đều lấy dư cho $M=10^9+7$.

### Chuyển trạng thái

Nếu không chọn $u$, mỗi người con $v$ có thể được chọn hoặc không. Nếu chọn $u$, bắt buộc không chọn mọi người con trực tiếp. Do đó:

$$
dp_0[u]=\prod_{v\text{ là con của }u}(dp_0[v]+dp_1[v])\pmod M,
$$

$$
dp_1[u]=\prod_{v\text{ là con của }u}dp_0[v]\pmod M.
$$

Tích rỗng bằng $1$. Tại lá, hai trạng thái đều bằng $1$: chọn tập rỗng hoặc chọn riêng lá.

Đáp án là $(dp_0[1]+dp_1[1])\bmod M$. Tập rỗng đã được tính đúng một lần trong trạng thái không chọn gốc.

### Tính đúng đắn

Tại lá, khởi tạo liệt kê đủ hai lựa chọn. Giả sử các trạng thái ở những người con đều đúng. Khi cố định việc chọn $u$, điều kiện giữa $u$ và mỗi con chính là điều kiện trong công thức. Giữa hai cây con khác nhau không có cạnh, nên có thể kết hợp độc lập bằng phép nhân. Hai lựa chọn ở mỗi con là rời nhau nên được cộng. Mỗi tập hợp lệ được tách duy nhất theo các cây con, vì vậy không có cách nào bị bỏ sót hoặc đếm lặp.

Theo quy nạp từ lá lên gốc, các trạng thái đều đúng. Hai trạng thái tại gốc phân hoạch toàn bộ tập độc lập, nên tổng của chúng là đáp án.

### Cài đặt và độ phức tạp

Duyệt cây bằng một danh sách thứ tự thăm và lưu cha của mỗi đỉnh. Xử lý danh sách theo thứ tự ngược để các con được tính trước cha; không cần DFS đệ quy.

Thời gian $O(N)$, bộ nhớ $O(N)$. Dùng số nguyên 64 bit khi nhân hai số dư trước khi lấy modulo; tích nhỏ hơn $(10^9+7)^2$, nằm trong miền giá trị của kiểu này.
