# Lời giải — Không chọn ba người liên tiếp

### Trạng thái

Gốc cố định là đỉnh $1$. Gọi $dp[u][t]$ là tổng giá trị lớn nhất trong cây con của $u$, biết rằng ngay trước $u$ có đúng $t$ tổ tiên liên tiếp đã được chọn, với $t=0,1,2$. Các lựa chọn ngoài cây con được giả thiết hợp lệ.

Đây là thông tin đi vào cây con; không phải số con được chọn.

### Chuyển trạng thái

Đặt $S_t=\sum_{v\text{ là con của }u}dp[v][t]$.

Nếu không chọn $u$, chuỗi liên tiếp bị ngắt, nên mọi con đều nhận trạng thái $0$. Nếu chọn $u$, chuỗi tăng thêm một; lựa chọn này chỉ được phép khi $t<2$:

$$
dp[u][0]=\max(S_0,A_u+S_1),
$$
$$
dp[u][1]=\max(S_0,A_u+S_2),
$$
$$
dp[u][2]=S_0.
$$

Tại lá, mọi $S_t$ bằng $0$. Đáp án là $dp[1][0]$ vì gốc không có tổ tiên. Tập rỗng được cho phép nên đáp án không âm.

### Tính đúng đắn

Khi trạng thái đi vào đã cố định, có đúng hai lựa chọn tại $u$: chọn hoặc bỏ. Bỏ $u$ khiến mọi đường qua $u$ bắt đầu lại chuỗi chọn ở các con. Chọn $u$ tăng độ dài chuỗi lên một; khi chuỗi trước đó dài $2$ thì chọn tiếp sẽ tạo ba đỉnh liên tiếp, nên bị cấm.

Các nhánh con không tạo đường từ gốc đến lá đi qua nhau. Vì vậy sau khi cố định lựa chọn tại $u$, có thể tối ưu các cây con độc lập rồi cộng. Giả sử các trạng thái ở con đều đúng, ba công thức xét đủ mọi lựa chọn hợp lệ và chọn giá trị lớn nhất. Quy nạp từ lá lên gốc chứng minh thuật toán.

### Độ phức tạp

Thời gian $O(N)$, bộ nhớ $O(N)$. Dùng số nguyên 64 bit vì tổng có thể đạt $2\cdot10^{14}$. Duyệt cây bằng vòng lặp, lưu cha và thứ tự thăm rồi xử lý ngược, tránh tràn ngăn xếp trên cây dây.

Không áp dụng điều kiện cho đường đi qua hai nhánh khác nhau. Ví dụ trên cây sao có gốc ở tâm, mọi đỉnh có giá trị dương đều có thể được chọn.
