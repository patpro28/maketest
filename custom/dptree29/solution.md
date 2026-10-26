# Lời giải — Tách hai nhóm đối địch

### Trạng thái

Chọn đỉnh $1$ làm gốc. Sau khi cắt các cạnh trong cây con của $u$, gọi thành phần chứa $u$ là thành phần đang mở. Các thành phần khác phải hợp lệ.

Gọi $dp[u][t]$ là chi phí nhỏ nhất với trạng thái của thành phần đang mở:

- $t=0$: không có đỉnh được đánh dấu.
- $t=1$: có đỉnh đỏ, không có đỉnh xanh.
- $t=2$: có đỉnh xanh, không có đỉnh đỏ.

Khởi tạo trước khi xử lý các con: $dp[u][T_u]=0$, hai trạng thái còn lại bằng $+\infty$.

### Gộp một nhánh con

Giả sử nhánh con $v$ nối bằng cạnh có chi phí $w$. Dùng mảng mới để tránh dùng lại một nhánh nhiều lần.

Nếu cắt cạnh $(u,v)$, thành phần đang mở tại $u$ không đổi. Phía $v$ trở thành một thành phần riêng và được dùng trạng thái rẻ nhất:

$$
next[a]=\min\left(next[a],dp[u][a]+w+\min_b dp[v][b]\right).
$$

Nếu giữ cạnh, thành phần của $u$ và $v$ nhập lại. Hai trạng thái tương thích khi $a=0$, hoặc $b=0$, hoặc $a=b$. Trạng thái hợp nhất là $\max(a,b)$:

$$
next[\max(a,b)]=\min(next[\max(a,b)],dp[u][a]+dp[v][b]).
$$

Không được hợp nhất hai trạng thái $1$ và $2$. Sau mỗi con, thay mảng cũ bằng mảng mới. Đáp án là $\min_t dp[1][t]$.

### Tính đúng đắn

Khởi tạo chỉ chứa đỉnh $u$, nên đúng theo màu của nó. Với một nhánh con, mọi phương án hoặc cắt cạnh đầu nhánh, hoặc giữ cạnh đó. Trường hợp cắt tách hẳn nhánh và cho phép chọn bất kỳ trạng thái hợp lệ nào của con. Trường hợp giữ nhập hai thành phần; quy tắc tương thích kiểm tra chính xác việc có đồng thời hai màu hay không.

Các chi phí thuộc những cạnh khác nhau được cộng, còn mọi thành phần đã đóng trong các nhánh con đều được bảo đảm hợp lệ. Theo quy nạp qua các con và từ lá lên, mảng luôn lưu chi phí nhỏ nhất đúng theo định nghĩa. Tại gốc không cần tiếp tục ghép lên cha, nên lấy min của cả ba trạng thái cho đáp án.

### Độ phức tạp

Mỗi cạnh xét số trường hợp hằng số, thời gian $O(N)$ và bộ nhớ $O(N)$. Dùng số nguyên 64 bit, lấy $INF=2^{60}$ và bỏ qua trạng thái bất khả thi trước khi cộng. Duyệt không đệ quy để xử lý cây dây dài.
