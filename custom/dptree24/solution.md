# Lời giải — Sơn các ngôi làng

### Trạng thái

Chọn đỉnh $1$ làm gốc. Gọi $dp[u][c]$ là chi phí nhỏ nhất trong cây con gốc $u$ khi sơn $u$ màu $c$, với $c\in\{0,1\}$.

Chi phí bao gồm sơn các đỉnh và phụ phí của các cạnh nằm hoàn toàn trong cây con, chưa gồm cạnh nối $u$ với cha.

### Chuyển trạng thái

Khi biết màu của $u$, với mỗi người con $v$ có hai lựa chọn: sơn cùng màu với $u$, hoặc sơn khác màu và chịu phụ phí $w_{uv}$. Do đó:

$$
dp[u][0]=A_u+\sum_{v\text{ là con của }u}\min(dp[v][0],dp[v][1]+w_{uv}),
$$

$$
dp[u][1]=B_u+\sum_{v\text{ là con của }u}\min(dp[v][1],dp[v][0]+w_{uv}).
$$

Tại lá, hai giá trị lần lượt là $A_u$ và $B_u$. Đáp án là $\min(dp[1][0],dp[1][1])$.

### Tính đúng đắn

Tại lá, công thức chỉ tính chi phí sơn, đúng theo định nghĩa. Giả sử các trạng thái ở các con đã đúng. Khi cố định màu $c$ của $u$, mọi cách sơn cây con của $v$ đều thuộc một trong hai trường hợp: $v$ mang màu $c$ hoặc $1-c$. Trường hợp thứ nhất không trả phụ phí trên cạnh $(u,v)$, trường hợp thứ hai trả đúng $w_{uv}$.

Sau khi cố định màu $u$, các nhánh con độc lập, vì mọi cạnh nối chúng với phần còn lại đều đi qua $u$. Chọn phương án tốt nhất của từng nhánh rồi cộng chi phí sơn $u$ cho giá trị tối ưu. Quy nạp đến gốc chứng minh hai trạng thái đúng. Lấy min giữa hai màu của gốc cho đáp án toàn cây.

### Độ phức tạp và lưu ý

Thời gian $O(N)$, bộ nhớ $O(N)$. Mỗi cạnh đóng góp một lần, không được cộng phụ phí ở cả hai đầu.

Chi phí và phụ phí có thể bằng $0$. Dùng số nguyên 64 bit; chi phí của một phương án không vượt $(2N-1)\cdot10^9$.

Duyệt cây bằng vòng lặp để lưu cha, cạnh lên cha và thứ tự thăm; xử lý các đỉnh theo thứ tự ngược để các con được tính trước cha.
