# Lời giải — Ghép đường ray dài tới 10^18

Đặt $m=\min A_i$. Xây đồ thị ngầm có $m$ đỉnh là các số dư. Thêm một đoạn dài $A_i$ tạo cạnh từ $r$ tới $(r+A_i)\bmod m$, trọng số $A_i$. Các cạnh dương nên dùng Dijkstra từ dư $0$ để tìm `dist[r]`, tổng chiều dài nhỏ nhất ghép được có dư $r$.

Nếu ghép được $X$, tổng này là một đường đi đến dư $X\bmod m$, nên `dist[X%m] <= X`. Ngược lại, nếu bất đẳng thức đúng, hiệu $X-dist[X%m]$ là số không âm chia hết cho $m$; thêm đúng số đoạn dài $m$ tương ứng để đạt $X$. Vì $m$ là một chiều dài thực sự có trong đầu vào, phép bổ sung luôn hợp lệ.

Dư không đạt được có khoảng cách vô cùng. Với $X=0$, khoảng cách dư $0$ bằng $0$, trả lời `YES`. Không chỉ kiểm tra gcd: ví dụ các đoạn $4,6$ chưa ghép được $2$ dù gcd chia hết $2$.

Thời gian $O(Nm\log(m+1)+Q)$, bộ nhớ $O(N+m)$ ngoài hàng đợi. Cài đặt dùng heap có thể có $O(Nm)$ bản ghi tạm; không cần lưu truy vấn. Khoảng cách hữu hạn có đường đi đơn không quá $m-1$ cạnh, nhỏ hơn $5\cdot10^9$, nhưng truy vấn tới $10^{18}$ nên dùng 64 bit. Không DP tới chiều dài truy vấn.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Nhóm `max` chứa dữ liệu đạt giới hạn cùng các dạng đặc biệt; `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc, có thể chồng lấp.

Chạy `python3 custom/knapsack29/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải với thuật toán độc lập và vét cạn nhỏ, verifier/checker, tính tái lập và hash. Khi chủ động đổi bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
