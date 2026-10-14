# Lời giải — Xưởng robot hàng loạt

Tính trước `dist[b]`, số thao tác ít nhất để tăng từ $1$ lên đúng $b$. Chỉ cần thử $1\le x\le u$: $x>u$ không làm tăng sức mạnh và không hữu ích. Mọi cạnh hữu ích đi từ $u$ tới một giá trị lớn hơn, nên duyệt $u$ tăng dần là thứ tự topo. Bỏ cạnh vượt $1000$ vì sức mạnh không giảm, không thể quay về một mục tiêu nhỏ hơn.

Chi phí ít nhất cho một robot mẫu $i$ là $1+dist[B_i]$, bao gồm tạo khung. Các robot độc lập; thay mọi quá trình nâng cấp bằng quá trình ngắn nhất không giảm tiền bán và chỉ tiết kiệm năng lượng. Vì vậy bài toán trở thành knapsack vô hạn theo các chi phí này và giá bán $V_i$.

Dùng DP sức chứa tối đa, khởi tạo $0$, duyệt năng lượng tăng với mỗi mẫu. Chi phí luôn ít nhất $1$, kể cả $B_i=1$, nên không có lợi nhuận vô hạn. Thời gian $O(B_{\max}^2+NK)$, bộ nhớ $O(B_{\max}+K+1)$. Tiền bán có thể tới $2\cdot10^{13}$, dùng 64 bit.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Nhóm `max` chứa dữ liệu đạt giới hạn cùng các dạng đặc biệt; `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc, có thể chồng lấp.

Chạy `python3 custom/knapsack23/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải với thuật toán độc lập và vét cạn nhỏ, verifier/checker, tính tái lập và hash. Khi chủ động đổi bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
