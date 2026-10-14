# Lời giải — Đổi tiền tối ưu có bao nhiêu cách?

Mỗi tổng lưu cặp `(best,ways)`: số đồng ít nhất và số cách đạt nó. Khởi tạo tổng $0$ bằng $(0,1)$, các tổng khác bằng $(X+1,0)$.

Duyệt mệnh giá ở vòng ngoài và tổng tăng dần. Ứng viên dùng thêm một đồng $A_i$ có số đồng `best[s-A_i]+1` và số cách `ways[s-A_i]`. Nếu tốt hơn, thay cả cặp; nếu bằng, cộng số cách modulo.

Các phương án chia thành không dùng $A_i$ và dùng ít nhất một đồng $A_i$. Hai nhóm rời nhau. Bỏ một đồng $A_i$ từ nhóm thứ hai cho một bộ số lượng ở tổng nhỏ hơn; dùng phương án ít đồng nhất ở nguồn luôn đủ vì mỗi lần thêm chỉ cộng một đồng. Duyệt tăng cho dùng lại mệnh giá hiện tại; vòng ngoài theo mệnh giá tránh đếm thứ tự.

Dùng `best==INF` để kiểm tra không đạt được, không dùng `ways==0`, vì số cách có thể chia hết cho modulo. Thời gian $O(N(X+1))$, bộ nhớ $O(X+1)$.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Nhóm `max` chứa dữ liệu đạt giới hạn cùng các dạng đặc biệt; `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc, có thể chồng lấp.

Chạy `python3 custom/knapsack21/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải với thuật toán độc lập và vét cạn nhỏ, verifier/checker, tính tái lập và hash. Khi chủ động đổi bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
