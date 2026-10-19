# Lời giải — Khu vườn có lợi nhuận lớn nhất

### Trạng thái và chuyển trạng thái

Chọn đỉnh $1$ làm gốc. Gọi $dp[u]$ là tổng lớn nhất của một tập đỉnh không rỗng, liên thông, nằm trong cây con của $u$ và chứa $u$.

Nếu lấy một đỉnh trong cây con của người con $v$, tính liên thông bắt buộc phải lấy $v$. Phần được lấy trong cây con đó phải liên thông và chứa $v$, nên giá trị tốt nhất là $dp[v]$. Cũng có thể bỏ hoàn toàn nhánh này. Do đó:

$$
dp[u]=A_u+\sum_{v\text{ là con của }u}\max(0,dp[v]).
$$

Tại lá, $dp[u]=A_u$. Không được thay $dp[u]$ bằng $\max(0,dp[u])$, vì tập đang xét phải chứa $u$ và không được rỗng.

### Đáp án và tính đúng đắn

Với một tập đỉnh liên thông không rỗng bất kỳ, tồn tại duy nhất một đỉnh $u$ có độ sâu nhỏ nhất trong tập. Nếu có hai đỉnh cùng đạt độ sâu nhỏ nhất thì đường đi nối chúng phải đi qua một tổ tiên có độ sâu nhỏ hơn, trái với tính liên thông. Vì vậy, tập đó nằm trong cây con của $u$ và chứa $u$.

Trong từng nhánh con của $u$, có thể bỏ toàn bộ nhánh hoặc chọn một tập liên thông chứa gốc nhánh. Các nhánh không có cạnh nối trực tiếp với nhau, và đều nối qua $u$, nên các lựa chọn tối ưu được kết hợp độc lập. Điều này chứng minh công thức chuyển theo quy nạp từ lá lên.

Mọi tập hợp lệ được xét trong trạng thái của đỉnh cao nhất của nó; ngược lại, mỗi trạng thái tạo được một tập hợp lệ. Đáp án là:

$$
\max_{1\le u\le N}dp[u].
$$

Nếu mọi giá trị đều âm, đáp án là giá trị lớn nhất trong các đỉnh. Khi cài đặt, khởi tạo đáp án bằng một giá trị của đỉnh, không khởi tạo bằng $0$.

### Cài đặt và độ phức tạp

Lưu cha và thứ tự duyệt bằng vòng lặp, rồi xử lý ngược thứ tự này. Cách làm tránh tràn ngăn xếp với cây dạng dây.

Thời gian $O(N)$, bộ nhớ $O(N)$. Tổng có thể đạt $2\cdot10^{14}$ nên cần số nguyên 64 bit.
