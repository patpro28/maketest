# Lời giải — Pha đồ uống đúng độ ngọt

Trung bình bằng $T$ khi tổng độ ngọt bằng $KT$, với đúng $K$ cốc. Dùng `dp[k][s]` đếm bộ số lượng tạo $k$ cốc có tổng độ ngọt $s$. Khởi tạo `dp[0][0]=1`.

Với công thức có độ ngọt $a$, duyệt số cốc tăng rồi tổng tăng, cập nhật từ `dp[k-1][s-a]`. Nguồn đã cho phép dùng công thức hiện tại, nên số lần dùng không giới hạn. Vòng ngoài theo công thức đếm mỗi bộ số lượng một lần.

Một phương án hoặc không dùng công thức mới, hoặc bỏ một cốc thuộc công thức mới để được đúng một phương án nguồn. Hai nhóm rời nhau, nên phép cộng bảo toàn số cách. Đáp án là `dp[K][KT]`. Cố định $K$ là thiết yếu: chỉ yêu cầu trung bình mà không chặn số cốc có thể tạo vô hạn phương án.

Thời gian $O(NK\cdot KT)$, bộ nhớ $O(K\cdot KT)$. Giới hạn tổng ở $KT$ hợp lệ vì độ ngọt dương.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Nhóm `max` chứa dữ liệu đạt giới hạn cùng các dạng đặc biệt; `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc, có thể chồng lấp.

Chạy `python3 custom/knapsack22/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải với thuật toán độc lập và vét cạn nhỏ, verifier/checker, tính tái lập và hash. Khi chủ động đổi bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
