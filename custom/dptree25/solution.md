# Lời giải — Chọn người đại diện

### Trạng thái

Gốc của cây là đỉnh $1$. Trong cây con gốc $u$, đặt:

- $dp[u][0]$: số cách chọn hợp lệ khi không chọn $u$.
- $dp[u][1]$: số cách chọn hợp lệ khi chọn $u$.

Các trạng thái xét riêng cây con, với giả thiết không có tổ tiên nào ngoài cây con đã được chọn.

### Chuyển trạng thái

Khi chọn $u$, không được chọn bất kỳ hậu duệ nào. Chỉ có một lựa chọn là tập $\{u\}$:

$$
dp[u][1]=1.
$$

Khi không chọn $u$, có thể kết hợp tùy ý các cách hợp lệ từ những cây con:

$$
dp[u][0]=\prod_{v\text{ là con của }u}(dp[v][0]+dp[v][1])\pmod{10^9+7}.
$$

Tại lá, tích rỗng bằng $1$, nên hai trạng thái đều bằng $1$. Đáp án là $(dp[1][0]+dp[1][1])\bmod(10^9+7)$.

### Tính đúng đắn

Nếu chọn $u$, mọi đỉnh còn lại trong cây con đều là hậu duệ của $u$ và bị cấm chọn. Vì vậy trạng thái chọn $u$ có đúng một cách.

Nếu không chọn $u$, hai đỉnh thuộc hai nhánh con khác nhau không thể là tổ tiên của nhau. Tính hợp lệ vì thế chỉ phụ thuộc các lựa chọn bên trong từng cây con. Mỗi cách chọn được tách duy nhất thành các tập ở những cây con, nên tổng hai trạng thái ở con cho đủ lựa chọn, còn tích giữa các con kết hợp chúng không đếm lặp.

Theo quy nạp từ lá lên gốc, các trạng thái đều đúng. Hai trạng thái tại gốc phân hoạch toàn bộ cách chọn, kể cả tập rỗng.

### Độ phức tạp và lưu ý

Thời gian $O(N)$, bộ nhớ $O(N)$. Duyệt cây không đệ quy và xử lý ngược thứ tự thăm.

Dùng số nguyên 64 bit khi nhân hai số dư và lấy modulo ngay sau mỗi phép nhân. Không dùng công thức của tập độc lập trên cây: chọn $u$ cấm mọi hậu duệ, không chỉ các con trực tiếp.
