# Lời giải — DPSTR152

Đặt $dp[i][j][c]$ là độ dài lớn nhất của một dãy chung hợp lệ của hai tiền tố, kết thúc bằng chữ $c\in\{a,b,c\}$. Trạng thái chưa tồn tại có giá trị âm vô cùng. Dãy rỗng được xử lý riêng với độ dài $0$.

Với mỗi chữ kết thúc, thử bỏ một trong hai vị trí cuối. Nếu $A_i=B_j=c$, có thể bắt đầu dãy mới bằng $c$ hoặc nối $c$ sau một dãy kết thúc bằng chữ khác:

$$dp[i][j][c]\gets\max\left(dp[i][j][c],1+\max\left(0,\max_{d\ne c}dp[i-1][j-1][d]\right)\right).$$

Chỉ dùng trạng thái ở hai tiền tố ngắn hơn khi nối ký tự. Mọi chuyển giữ điều kiện hai chữ kề nhau khác nhau. Ngược lại, một dãy tối ưu hoặc bỏ một vị trí cuối, hoặc ghép cả hai; khi ghép, phần trước rỗng hoặc phải kết thúc bằng chữ khác. Quy nạp cho thấy đã xét đủ mọi đáp án.

Đáp án là giá trị lớn nhất của $0$ và ba trạng thái tại $(N,M)$. Có thể nén theo hàng; không cần lưu xâu đã chọn.

Độ phức tạp thời gian $O(3^2NM)$, bộ nhớ của phần DP $O(3M)$.
