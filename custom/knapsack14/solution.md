# Lời giải — Chia hai đội cân bằng

Gọi $T=\sum A_i$, $K=\lfloor N/2\rfloor$. Có thể đặt tên đội thứ nhất là đội có $K$ thành viên. Nếu tổng sức mạnh đội này bằng $s$, độ chênh lệch là $|T-2s|$.

Khác bài chia hai xe buýt, ở đây phải nhớ cả số học sinh. Dùng `dp[k][s]` biểu diễn chọn được đúng $k$ học sinh có tổng sức mạnh $s$. Khởi tạo `dp[0][0]=true`. Với mỗi $A_i$, duyệt $k$ giảm rồi duyệt $s$ giảm và cập nhật từ `dp[k-1][s-A_i]`.

Phép chuyển phân biệt chọn/không chọn học sinh mới, nên bất biến về cả số lượng và tổng được bảo toàn. Mọi cách chia hợp lệ có một đội $K$ thành viên, và mọi tập $K$ học sinh cho một cách chia hợp lệ. Lấy nhỏ nhất $|T-2s|$ trên các trạng thái `dp[K][s]` cho đúng kết quả.

Phải xét **tất cả** $0\le s\le T$: khi $N$ lẻ, đội ít người hơn vẫn có thể mạnh hơn. Thời gian $O(NKT)=O(N^2T)$, bộ nhớ $O(KT)$.

## Kiểm thử

32 file: 2 ví dụ, 10 trường hợp biên, 6 trường hợp nhỏ, 8 ngẫu nhiên và 6 trường hợp lớn. Nhóm `max` chứa test đạt giới hạn, cùng các dạng đặc biệt ở kích thước lớn. Các subtask có thể chồng lấp; điểm chỉ nhận khi đúng tất cả test thỏa ràng buộc subtask tương ứng.

Chạy `python3 custom/knapsack14/tests/check.py` từ thư mục gốc để sinh và kiểm tra test, đối chiếu lời giải với vét cạn độc lập, kiểm tra verifier/checker và đối chiếu `hash.json`. Khi chủ động đổi dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
