# Lời giải — Ba bếp

Gọi $T=\sum T_i$. Khi biết tổng thời gian của bếp 1 là $x$ và bếp 2 là $y$, bếp 3 có tổng $T-x-y$.

Dùng `dp[x][y]` cho biết có thể phân công các món đã xét để hai bếp đầu có tổng $x,y$ hay không. Khởi tạo `dp[0][0]=true`. Khi xét món cần $t$ phút, tạo mảng mới và chuyển mỗi trạng thái cũ sang $(x+t,y)$, $(x,y+t)$ hoặc $(x,y)$, tương ứng giao món cho bếp 1, 2 hoặc 3.

Tổng thời gian của các món đã xét là $P$, nên chỉ duyệt $x+y\le P$. Ba phép chuyển là toàn bộ cách giao món mới; quy nạp cho thấy DP ghi nhận đúng các cách phân công. Khi xét xong, đáp án là nhỏ nhất của $\max(x,y,T-x-y)$ trên các trạng thái đạt được. Mảng mới bảo đảm một món chỉ được giao cho một bếp.

Thời gian $O(NT^2)$, bộ nhớ $O(T^2)$. Chỉ lấy $\lceil T/3\rceil$ làm đáp án là sai vì mỗi món không thể bị chia nhỏ.

## Kiểm thử

32 file: 2 ví dụ, 10 trường hợp biên, 6 trường hợp nhỏ, 8 ngẫu nhiên và 6 trường hợp lớn. Nhóm `max` chứa test đạt giới hạn, cùng các dạng đặc biệt ở kích thước lớn. Các subtask có thể chồng lấp; điểm chỉ nhận khi đúng tất cả test thỏa ràng buộc subtask tương ứng.

Chạy `python3 custom/knapsack18/tests/check.py` từ thư mục gốc để sinh và kiểm tra test, đối chiếu lời giải với vét cạn độc lập, kiểm tra verifier/checker và đối chiếu `hash.json`. Khi chủ động đổi dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
