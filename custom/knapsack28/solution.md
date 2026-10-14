# Lời giải — Xây số lớn nhất chia hết

Với số dương không có số $0$ ở đầu, ưu tiên độ dài rồi thứ tự từ trái sang phải. Dùng `f[b][r]` là độ dài lớn nhất của phần có thể viết **thêm**, tốn đúng $b$ đồng, khi tiền tố hiện tại có dư $r$, để kết thúc với dư $0$.

Khởi tạo `f[0][0]=0`, các trạng thái còn lại không đạt được. Nếu viết chữ số $d$, dư mới là $(10r+d)\bmod M$, nên chuyển từ `f[b-C_d][dư mới]+1`. Duyệt ngân sách tăng vì chi phí dương. Trạng thái này cho phép số $0$ đầu hậu tố, phù hợp khi đã có tiền tố.

Thử riêng chữ số đầu $1,\ldots,9$ để tìm độ dài hợp lệ lớn nhất. Nếu không có số dương, chỉ số `0` hợp lệ khi $B=C_0$. Với độ dài tối ưu, truy vết từ trái sang phải: thử chữ số giảm dần và giữ chữ số cho phép hậu tố đạt đúng số vị trí còn lại.

Phép chuyển liệt kê mọi hậu tố và đảm bảo trạng thái cuối đúng dư $0$. Chọn chữ số lớn nhất vẫn hoàn thành được giữ tiền tố lớn nhất, nên cho số tối ưu trong độ dài lớn nhất. Không cần thêm chiều độ dài cho số dư vì DP được định nghĩa theo dư của **tiền tố hiện tại**, không phải dư của một hậu tố đứng độc lập.

Thời gian $O(10BM)$, bộ nhớ $O(BM)$ và chuỗi đáp án. Độ dài không vượt $B$; không lưu đáp án trong kiểu số nguyên cố định.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Nhóm `max` chứa dữ liệu đạt giới hạn cùng các dạng đặc biệt; `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc, có thể chồng lấp.

Chạy `python3 custom/knapsack28/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải với thuật toán độc lập và vét cạn nhỏ, verifier/checker, tính tái lập và hash. Khi chủ động đổi bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
