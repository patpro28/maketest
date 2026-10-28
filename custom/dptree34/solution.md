# Lời giải — Hành trình thu thập phần thưởng

### Ba câu hỏi để xây dựng lời giải

**Cần tính gì tại đỉnh $u$?** Gọi $dp[u]$ là tổng phần thưởng lớn nhất của một hành trình bắt đầu tại $u$ và kết thúc tại một lá trong cây con của $u$. Tổng bao gồm phần thưởng tại $u$.

**Một lá trả về gì?** Hành trình chỉ gồm chính lá đó, nên $dp[u]=A_u$, kể cả khi $A_u$ âm.

**Cha dùng kết quả các con thế nào?** Nếu $u$ có con, phải tiếp tục đi xuống đúng một người con:

$$
dp[u]=A_u+\max_{v\text{ là con của }u}dp[v].
$$

Đáp án là $dp[1]$.

### Hiểu điều kiện bắt buộc đến lá

Tại một đỉnh có con, không được tự chọn dừng lại. Vì thế công thức không chứa lựa chọn $0$ thay cho kết quả của con.

Ví dụ với đường $1\to2\to3$ có giá trị $10,-20,-3$, lần lượt nhận được $dp[3]=-3$, $dp[2]=-23$, $dp[1]=-13$. Giá trị $10$ tại gốc không phải một hành trình hợp lệ vì gốc còn có con.

Khi tìm kết quả lớn nhất ở các con, khởi tạo bằng $-\infty$ hoặc bằng kết quả của người con đầu tiên. Khởi tạo bằng $0$ sẽ sai nếu mọi lựa chọn đều âm.

### Chứng minh tính đúng đắn

Tại lá, hành trình duy nhất gồm lá đó nên khởi tạo đúng.

Giả sử trạng thái tại các con của $u$ đều đúng. Mỗi hành trình hợp lệ từ $u$ phải chọn đúng một con $v$, nhận $A_u$ rồi thực hiện một hành trình hợp lệ từ $v$ xuống lá. Giá trị tốt nhất với người con này là $A_u+dp[v]$. Chọn lớn nhất giữa tất cả các con xét đủ mọi hành trình và thu được giá trị tối ưu. Quy nạp đến gốc chứng minh $dp[1]$ là đáp án.

### Độ phức tạp và lưu ý cài đặt

Thời gian $O(N)$, bộ nhớ $O(N)$. Tổng có thể nằm trong khoảng $[-2\cdot10^{14},2\cdot10^{14}]$, cần số nguyên 64 bit.

Phân biệt rõ lá với đỉnh có con: lá giữ $A_u$, còn đỉnh có con bắt buộc cộng kết quả từ một con. Lưu cha và thứ tự duyệt bằng vòng lặp rồi xử lý ngược thứ tự để tránh tràn ngăn xếp trên cây dây.
