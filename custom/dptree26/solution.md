# Lời giải — Đếm cách ghép đôi

### Trạng thái

Chọn đỉnh $1$ làm gốc. Chỉ xét các cạnh có cả hai đầu trong cây con của $u$:

- $dp[u][0]$: số cách ghép đôi khi $u$ không ghép với người con nào.
- $dp[u][1]$: số cách ghép đôi khi $u$ ghép với đúng một người con.

Cạnh nối $u$ với cha chưa được xét. Nếu sau đó chọn cạnh này thì phải dùng trạng thái $0$ của $u$.

### Gộp từng người con

Ban đầu chưa xử lý người con nào, đặt $f_0=1$ và $f_1=0$. Với người con tiếp theo $v$, đặt:

$$
T=(dp[v][0]+dp[v][1])\bmod M,\qquad M=10^9+7.
$$

Nếu không chọn cạnh $(u,v)$, có thể kết hợp cả hai trạng thái ở $v$. Nếu chọn cạnh $(u,v)$, cả $u$ lẫn $v$ phải chưa ghép với con nào. Công thức gộp là:

$$
f'_0=f_0T\pmod M,
$$

$$
f'_1=(f_1T+f_0dp[v][0])\pmod M.
$$

Phải tính cả hai giá trị mới từ các giá trị cũ trước khi cập nhật. Sau khi gộp hết con, đặt $dp[u][0]=f_0$ và $dp[u][1]=f_1$.

Tại lá, hai trạng thái là $1$ và $0$. Đáp án là $(dp[1][0]+dp[1][1])\bmod M$.

### Tính đúng đắn

Với tập con các nhánh đã xử lý, giả sử $f_0,f_1$ đếm đúng các cách tương ứng. Khi thêm nhánh $v$, mọi cách ghép đôi đều thuộc chính xác một trong hai trường hợp có hoặc không chọn cạnh $(u,v)$.

Nếu không chọn cạnh này, nhánh $v$ độc lập với các nhánh trước nên nhân với $T$. Nếu chọn cạnh, $u$ phải chưa ghép với nhánh nào và $v$ phải chưa ghép với con nào; số cách là $f_0dp[v][0]$. Kết quả thuộc trạng thái $1$. Hai trường hợp rời nhau và bao phủ mọi lựa chọn hợp lệ, chứng minh bước gộp.

Theo quy nạp qua các người con và từ lá lên gốc, cả hai trạng thái đều đúng. Mọi cách ghép đôi ở toàn cây thuộc đúng một trạng thái tại gốc, nên tổng của chúng là đáp án.

### Độ phức tạp và lưu ý

Mỗi cạnh được gộp đúng một lần, thời gian $O(N)$ và bộ nhớ $O(N)$. Lưu cha và thứ tự duyệt bằng vòng lặp để xử lý cây dây dài.

Không cần chia modulo hoặc nghịch đảo modulo. Việc gộp lần lượt vẫn đúng nếu tổng số cách ở một nhánh bằng $0$ theo modulo. Dùng số nguyên 64 bit cho các tích và tổng hai tích trước khi lấy modulo.

Tập cạnh rỗng luôn được tính. Khi $N=1$, đáp án bằng $1$.
