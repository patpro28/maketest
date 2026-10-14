# Lời giải — Phá khiên quái vật

`dp[s]` là năng lượng ít nhất khi tổng sát thương đã chặn ở $H$: $s<H$ là đúng $s$, còn $s=H$ là ít nhất $H$. Khởi tạo `dp[0]=0`, các trạng thái khác vô cùng.

Với mỗi phép, duyệt $s$ tăng từ $0$ tới $H-1$, chuyển đến $\min(H,s+D_i)$ với năng lượng cộng $C_i$. Vì $D_i>0$, trạng thái nguồn nhỏ hơn đích, cho phép dùng lại loại hiện tại. Không cần mở rộng từ trạng thái $H$ vì chi phí dương và đã đạt yêu cầu.

Mọi tổng từ $H$ trở lên tương đương cho mục tiêu tối ưu. Mỗi phương án dùng loại mới hoặc không dùng nó, hoặc bỏ một lần dùng để được trạng thái nguồn. Duyệt tăng bảo toàn tối ưu cho số lần dùng tùy ý. Mọi đầu vào đều có nghiệm vì có ít nhất một phép với sát thương dương.

Thời gian $O(N(H+1))$, bộ nhớ $O(H+1)$. Không DP đến tổng tất cả $D_i$. Năng lượng có thể tới $20000\cdot10^9=2\cdot10^{13}$; dùng 64 bit.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Nhóm `max` chứa dữ liệu đạt giới hạn cùng các dạng đặc biệt; `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc, có thể chồng lấp.

Chạy `python3 custom/knapsack20/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải với thuật toán độc lập và vét cạn nhỏ, verifier/checker, tính tái lập và hash. Khi chủ động đổi bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
