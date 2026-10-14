# Lời giải — Mở dây chuyền rồi sản xuất

`previous[s]` là lợi nhuận tối đa trong ngân sách $s$ chỉ dùng các dây chuyền trước. Khi xét dây chuyền mới, tạo `opened[s]` cho phương án đã làm ít nhất một sản phẩm ở dây chuyền này.

Có hai cách đến `opened[s]`: mở và làm sản phẩm đầu, từ `previous[s-F_i-C_i]+V_i`; hoặc làm thêm một sản phẩm, từ `opened[s-C_i]+V_i`. Duyệt $s$ tăng để cho sản xuất thêm nhiều lần. Sau đó gộp `dp[s]=max(previous[s],opened[s])`.

Một phương án dùng dây chuyền mới có đúng một sản phẩm đầu phải trả phí mở; các sản phẩm còn lại chỉ trả $C_i$. Hai chuyển mô tả mọi số lượng dương. Nguồn `previous` được chụp trước khi xét dây chuyền, nên không thể mở lặp hoặc trộn cập nhật mới vào bước trả phí. Phương án không dùng dây chuyền mới giữ nguyên `previous`.

Không cộng $F_i$ vào giá của mọi sản phẩm, cũng không cho bỏ qua phí mở. Thời gian $O(N(W+1))$, bộ nhớ $O(W+1)$. Chi phí mỗi sản phẩm ít nhất $1$, lợi nhuận không vượt $2\cdot10^{13}$; dùng 64 bit.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Nhóm `max` chứa dữ liệu đạt giới hạn cùng các dạng đặc biệt; `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc, có thể chồng lấp.

Chạy `python3 custom/knapsack26/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải với thuật toán độc lập và vét cạn nhỏ, verifier/checker, tính tái lập và hash. Khi chủ động đổi bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
