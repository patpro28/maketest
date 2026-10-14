# Lời giải — Một phiếu giảm giá

Dùng `unused[s]` và `used[s]` là điểm lớn nhất ở chi phí **đúng** $s$, tương ứng chưa dùng phiếu và đã dùng đúng một phiếu. Khởi tạo chỉ `unused[0]=0`.

Duyệt chi phí $s$ tăng. Từ chưa dùng, có thể mua sản phẩm đủ giá và giữ cờ, hoặc mua với giá một nửa và chuyển sang đã dùng. Từ đã dùng, chỉ được mua đủ giá. Mỗi lần mua đủ giá tăng chi phí vì $C_i>0$. Khi giảm giá về $0$, cạnh vẫn chuyển cờ từ $0$ sang $1$; xử lý trạng thái chưa dùng trước đã dùng tại cùng $s$ là thứ tự topo hợp lệ.

Các đường đi biểu diễn đầy đủ mọi phương án mua; thứ tự mua không ảnh hưởng tổng điểm nên chỉ cần giữ giá trị lớn nhất. Cờ chuyển đúng một lần đảm bảo phiếu được áp dụng cho một sản phẩm thực sự mua. Đáp án chỉ lấy từ `used` trên mọi $s\le W$, hoặc `-1` nếu không đạt được.

Có thể mua nhiều sản phẩm cùng loại. Không được áp dụng giá giảm cho tất cả bản sao. Thời gian $O(N(W+1))$, bộ nhớ $O(N+W+1)$. Nhiều nhất $W$ sản phẩm trả đủ giá và một sản phẩm dùng phiếu, nên điểm không vượt $(W+1)10^9$; dùng 64 bit.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Nhóm `max` chứa dữ liệu đạt giới hạn cùng các dạng đặc biệt; `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc, có thể chồng lấp.

Chạy `python3 custom/knapsack24/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải với thuật toán độc lập và vét cạn nhỏ, verifier/checker, tính tái lập và hash. Khi chủ động đổi bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
