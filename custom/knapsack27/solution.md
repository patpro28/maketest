# Lời giải — Dàn máy có bộ điều phối đủ mạnh

Sắp xếp và gom mẫu theo khả năng điều phối $A$. Duy trì `dp[s]` đếm các bộ số lượng của những mẫu đã xét có tải đúng $s$, modulo. Khởi tạo `dp[0]=1`.

Với nhóm có $A=a$, lưu tổng DP trên $0\le s\le a$ trước cập nhật. Thêm tất cả mẫu của nhóm bằng knapsack đếm vô hạn: vòng ngoài theo mẫu, tổng tăng. Lấy tổng trên cùng khoảng sau cập nhật. Hiệu sau-trước chính là số dàn có tải không vượt $a$ và dùng ít nhất một máy của nhóm hiện tại.

Mỗi dàn không rỗng có đúng một mức khả năng lớn nhất, nên được đếm trong đúng một nhóm. Phần trước cập nhật loại các dàn không dùng nhóm mới, bao gồm tập rỗng; vì vậy không đếm lặp khi nhiều mẫu có cùng $A$. Tải dương cho phép bỏ mọi trạng thái vượt $M=\max A_i$, và giới hạn tổng số máy ở $M$.

Thời gian $O(N\log N+NM)$, bộ nhớ $O(N+M)$. Phải chuẩn hóa phép trừ modulo. Các mẫu trùng thông số vẫn là loại độc lập khi đếm bộ số lượng.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Nhóm `max` chứa dữ liệu đạt giới hạn cùng các dạng đặc biệt; `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc, có thể chồng lấp.

Chạy `python3 custom/knapsack27/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải với thuật toán độc lập và vét cạn nhỏ, verifier/checker, tính tái lập và hash. Khi chủ động đổi bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
