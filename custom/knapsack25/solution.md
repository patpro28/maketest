# Lời giải — Sản xuất bằng hai nguyên liệu

`dp[x][y]` là lợi nhuận lớn nhất khi tiêu thụ không vượt $x$ kim loại và $y$ nhựa với các loại đã xét. Khởi tạo mọi trạng thái bằng $0$.

Với sản phẩm $(A_i,B_i,V_i)$, duyệt cả hai nguồn tăng, cập nhật từ `dp[x-A_i][y-B_i]+V_i`. Nguồn đã cho phép dùng loại hiện tại, nên có thể sản xuất lại. Trọng lượng mỗi nguồn đều dương, đảm bảo nguồn ở trước đích trong thứ tự duyệt và số sản phẩm hữu hạn.

Một phương án hoặc không sản xuất loại mới, hoặc bỏ đi một sản phẩm loại này và còn một phương án vừa hai ngân sách nhỏ hơn. Quy nạp theo loại và tài nguyên cho thấy phép lấy lớn nhất giữ đúng tối ưu. Trả về `dp[X][Y]`, không bắt buộc tiêu thụ hết cả hai nguyên liệu.

Thời gian $O(N(X+1)(Y+1))$, bộ nhớ $O((X+1)(Y+1))$. Lợi nhuận không vượt $200\cdot10^9=2\cdot10^{11}$, dùng 64 bit.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Nhóm `max` chứa dữ liệu đạt giới hạn cùng các dạng đặc biệt; `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc, có thể chồng lấp.

Chạy `python3 custom/knapsack25/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải với thuật toán độc lập và vét cạn nhỏ, verifier/checker, tính tái lập và hash. Khi chủ động đổi bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
