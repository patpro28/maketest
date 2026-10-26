# Lời giải — Nhóm liên thông chia hết cho ba

### Trạng thái

Chọn đỉnh $1$ làm gốc. Gọi $dp[u][r]$ là số tập đỉnh không rỗng, liên thông, nằm hoàn toàn trong cây con của $u$, chứa $u$ và có số đỉnh dư $r$ khi chia cho $3$.

Khởi tạo trước khi gộp con: $dp[u]=(0,1,0)$, tương ứng tập chỉ chứa $u$. Mọi phép đếm lấy dư cho $M=10^9+7$.

### Gộp cây con

Với người con $v$, một tập liên thông chứa $u$ có hai khả năng ở nhánh này:

- Không lấy đỉnh nào: giữ nguyên trạng thái cũ.
- Có lấy đỉnh: bắt buộc lấy $v$, và phần được lấy phải là một tập liên thông chứa $v$.

Khởi tạo $next=dp[u]$ cho khả năng thứ nhất. Với $a,b\in\{0,1,2\}$, thêm:

$$
next[(a+b)\bmod3]\mathrel{+}=dp[u][a]\cdot dp[v][b]\pmod M.
$$

Sau khi gộp một con, thay $dp[u]$ bằng $next$. Trạng thái dư $0$ của con vẫn là một tập không rỗng; không được gộp nó với lựa chọn bỏ nhánh thành cùng một cách.

### Tính đáp án

Mỗi tập liên thông không rỗng có duy nhất một đỉnh có độ sâu nhỏ nhất. Gọi đỉnh này là $u$. Tập đó nằm hoàn toàn trong cây con của $u$ và chứa $u$, nên được tính tại $dp[u]$.

Tập không thể được tính tại trạng thái của đỉnh khác: một tổ tiên nằm ngoài tập không thỏa điều kiện chứa gốc trạng thái; một đỉnh thấp hơn không có cả tập nằm trong cây con của mình. Vì vậy đáp án là:

$$
\sum_{u=1}^N dp[u][0]\pmod M.
$$

### Tính đúng đắn

Khởi tạo đếm đúng tập một đỉnh. Với mỗi nhánh con, điều kiện liên thông buộc phần giao với nhánh hoặc rỗng, hoặc liên thông và chứa người con. Hai khả năng rời nhau. Các nhánh độc lập sau khi đã chọn $u$, nên số cách kết hợp được nhân; kích thước được cộng theo modulo $3$.

Quy nạp qua các con chứng minh các trạng thái đếm đủ và không lặp. Lập luận về đỉnh cao nhất chứng minh phép cộng trên mọi đỉnh cho đúng số tập toàn cây. Tập rỗng không xuất hiện trong bất kỳ trạng thái nào.

### Độ phức tạp

Mỗi cạnh thực hiện chín phép ghép, thời gian $O(N)$ và bộ nhớ $O(N)$. Dùng số nguyên 64 bit khi nhân hai số dư, lấy modulo sau mỗi cập nhật. Duyệt cây không đệ quy để tránh tràn ngăn xếp.
