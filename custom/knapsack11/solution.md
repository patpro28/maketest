# Lời giải — Hai tuyến xe buýt

Gọi $T=\sum T_i$. Nếu một xe nhận các nhóm có tổng thời gian $s$, xe còn lại mất $T-s$ phút. Thời điểm hoàn thành là $\max(s,T-s)$.

Có thể đổi tên hai xe để $s\le T/2$. Khi đó mục tiêu trở thành tìm tổng $s$ lớn nhất không vượt $\lfloor T/2\rfloor$ có thể tạo bởi một tập nhóm; đáp án là $T-s$.

Dùng quy hoạch động tập con `dp[s]`, khởi tạo `dp[0]=true` và duyệt tổng giảm khi xét mỗi nhóm. Bất biến là `dp[s]` đúng khi và chỉ khi có tập các nhóm đã xét có tổng $s$. Vì mọi cách phân công tương ứng với một tập nhóm của xe thứ nhất, chọn tổng đạt được lớn nhất trong nửa dưới cho kết quả tối ưu.

Thời gian $O(NT)$, bộ nhớ $O(T)$.

## Kiểm thử

32 file: 2 ví dụ, 10 trường hợp biên, 6 trường hợp nhỏ, 8 ngẫu nhiên và 6 trường hợp lớn. Nhóm `max` chứa test đạt giới hạn, cùng các dạng đặc biệt ở kích thước lớn. Các subtask có thể chồng lấp; điểm chỉ nhận khi đúng tất cả test thỏa ràng buộc subtask tương ứng.

Chạy `python3 custom/knapsack11/tests/check.py` từ thư mục gốc để sinh và kiểm tra test, đối chiếu lời giải với vét cạn độc lập, kiểm tra verifier/checker và đối chiếu `hash.json`. Khi chủ động đổi dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
