# DPUPSTAIR03C — Hướng dẫn giải

Đặt $dp[i][j]$ là số cách xử lý $i$ ô đầu và dùng đúng $j$ viên gạch dài $2$ ô. Khởi tạo $dp[0][0]=1$, các trạng thái còn lại bằng $0$.

Nếu ô $i$ có chậu cây thì chỉ bỏ qua ô đó: $dp[i][j]=dp[i-1][j]$.

Nếu ô $i$ trống, có thể lát riêng ô này bằng gạch dài $1$ ô, đóng góp $dp[i-1][j]$. Nếu $i\ge2$, ô $i-1$ cũng trống và $j\ge1$, có thể kết thúc bằng một viên gạch phủ $(i-1,i)$, đóng góp thêm $dp[i-2][j-1]$.

Hai trường hợp kết thúc bằng gạch dài $1$ và dài $2$ không trùng nhau và bao phủ mọi cách lát hợp lệ. Bước bỏ qua ô đặt chậu cây không đặt gạch lên ô đó; điều kiện hai ô trống ngăn gạch đi xuyên qua chậu cây. Vì vậy quy hoạch động đếm đúng số cách cần tìm.

Lấy mọi phép cộng theo modulo $10^9+7$. Đáp án là $dp[N][M]$. Độ phức tạp $O(N(M+1))$; chỉ cần giữ hai hàng trước để dùng $O(M+1)$ bộ nhớ cho DP, cộng $O(N)$ cho đánh dấu ô.

Lời giải đối chiếu tách thành các đoạn trống. Đoạn dài $L$ dùng đúng $j$ viên gạch dài $2$ ô có $\binom{L-j}{j}$ cách: xem mỗi viên gạch như một phần tử, có tổng $L-j$ phần tử và chọn $j$ vị trí cho gạch dài $2$. Nhân các đa thức của các đoạn, chỉ giữ hệ số đến bậc $M$. Tính tổ hợp bằng giai thừa và nghịch đảo modulo. Cách này cho một phép kiểm tra độc lập với chuyển trạng thái theo từng ô.

### Theo subtask

- Subtask 1 (30%): $N\le20$, có thể quay lui theo ô chưa xử lý đầu tiên: bỏ qua ô đặt chậu cây, hoặc thử lát bằng một viên gạch dài $1$ hay $2$ ô nếu hợp lệ. Đếm những cách kết thúc dùng đúng $M$ viên gạch dài $2$ ô.
- Subtask 2 (20%): $M=0$, chỉ dùng gạch dài $1$ ô nên luôn có đúng một cách lát, kể cả khi mọi ô đều đặt chậu cây.
- Subtask 3 (50%): dùng quy hoạch động $O(N(M+1))$ như trên.
