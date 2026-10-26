# Lời giải — Bảo vệ các con đường

### Trạng thái

Chọn đỉnh $1$ làm gốc. Xét các cạnh có cả hai đầu nằm trong cây con gốc $u$:

- $dp[u][0]$: chi phí nhỏ nhất để bảo vệ các cạnh này khi không đặt chốt tại $u$.
- $dp[u][1]$: chi phí nhỏ nhất khi đặt chốt tại $u$.

Cạnh nối $u$ với cha được xử lý ở trạng thái của cha.

### Chuyển trạng thái

Nếu không chọn $u$, phải chọn mọi người con $v$ để bảo vệ cạnh $(u,v)$. Nếu chọn $u$, cạnh đó đã được bảo vệ nên có thể chọn hoặc không chọn $v$:

$$
dp[u][0]=\sum_{v\text{ là con của }u}dp[v][1],
$$

$$
dp[u][1]=C_u+\sum_{v\text{ là con của }u}\min(dp[v][0],dp[v][1]).
$$

Tại lá, $dp[u][0]=0$ và $dp[u][1]=C_u$. Đáp án là $\min(dp[1][0],dp[1][1])$.

### Tính đúng đắn

Khởi tạo tại lá đúng vì cây con không có cạnh. Giả sử các trạng thái ở con đều đúng. Mỗi cạnh từ $u$ đến con phải có ít nhất một đầu mút được chọn. Khi cố định việc chọn $u$, các lựa chọn được phép ở con chính xác như hai công thức trên.

Các cây con khác nhau không dùng chung đỉnh và không có cạnh nối với nhau, nên có thể tối ưu độc lập và cộng chi phí. Theo quy nạp từ lá lên, mọi trạng thái đều cho chi phí tối ưu. Tại gốc, hai khả năng đặt hoặc không đặt chốt bao phủ mọi phương án, nên giá trị nhỏ hơn là đáp án.

### Độ phức tạp và lưu ý

Thời gian $O(N)$, bộ nhớ $O(N)$. Tổng chi phí có thể vượt giới hạn 32 bit, cần dùng số nguyên 64 bit.

Lời giải lưu cha và thứ tự duyệt bằng vòng lặp, sau đó xử lý ngược thứ tự. Cây dây dài $200000$ đỉnh không gây tràn ngăn xếp. Với $N=1$, đáp án là $0$.
