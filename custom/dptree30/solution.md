# Lời giải — Giữ lại các tuyến đường

### Trạng thái

Chọn đỉnh $1$ làm gốc. $dp[u][k]$ là tổng giá trị lớn nhất của các cạnh được giữ trong cây con, khi có đúng $k$ cạnh từ $u$ đến các con được giữ, với $k=0,1,2$.

Cạnh nối $u$ lên cha chưa được xét. Nếu sau đó giữ cạnh này thì chỉ được dùng trạng thái $0$ hoặc $1$ tại $u$.

Khởi tạo trước khi gộp các con: $dp[u][0]=0$, $dp[u][1]=dp[u][2]=-\infty$.

### Ghép người con

Với cạnh $(u,v)$ có giá trị $w$:

- Không giữ cạnh: lấy $S=\max(dp[v][0],dp[v][1],dp[v][2])$.
- Giữ cạnh: lấy $T=w+\max(dp[v][0],dp[v][1])$.

Khi giữ cạnh, người con $v$ có thêm một cạnh nối lên cha, nên không được dùng trạng thái $2$ của nó.

Với mỗi trạng thái khả thi $k$, cập nhật mảng mới:

$$
next[k]=\max(next[k],dp[u][k]+S).
$$

Nếu $k<2$, còn có thể giữ cạnh mới:

$$
next[k+1]=\max(next[k+1],dp[u][k]+T).
$$

Đáp án là $\max_k dp[1][k]$.

### Tính đúng đắn

Mảng khởi tạo biểu diễn duy nhất việc chưa giữ cạnh nào. Khi thêm nhánh con, mọi phương án được chia thành hai trường hợp giữ hoặc bỏ cạnh nối nhánh. Bỏ cạnh không làm tăng bậc tại $u$ và không hạn chế bậc của $v$ từ phía cha. Giữ cạnh tăng bậc tại cả hai đầu, được cho phép chính xác bởi các giới hạn trên.

Các nhánh không có cạnh nối với nhau, nên tổng tốt nhất được kết hợp bằng phép cộng. Quy nạp qua các nhánh và theo cây chứng minh mọi trạng thái đều tối ưu. Gốc không có cạnh lên cha, do đó có thể lấy lớn nhất trong cả ba trạng thái.

Vì đồ thị ban đầu là cây, tập cạnh giữ lại không có chu trình. Giới hạn bậc không quá $2$ vì thế bảo đảm mỗi thành phần là một đường đi hoặc một đỉnh cô lập.

### Độ phức tạp và lưu ý

Thời gian $O(N)$, bộ nhớ $O(N)$. Dùng số nguyên 64 bit và duyệt cây bằng vòng lặp.

Giá trị cạnh có thể âm; giữ cạnh không phải nghĩa vụ. Trạng thái bỏ mọi cạnh có giá trị $0$, nên đáp án luôn không âm. Không gộp trực tiếp vào mảng cũ vì có thể vô tình giữ một cạnh nhiều lần.
