# Lời giải — Xây số lớn nhất

Với số không có chữ số $0$ ở đầu, số có nhiều chữ số hơn luôn lớn hơn; nếu độ dài bằng nhau thì so sánh từ trái sang phải.

Dùng `dp[s]` là số chữ số nhiều nhất có thể viết với **đúng** $s$ đồng, tạm cho phép chữ số đầu bằng $0$ để dùng làm hậu tố. Khởi tạo `dp[0]=0`, tổng không thể tạo bằng `-1`. Với $s$ tăng dần, thử tất cả chữ số: `dp[s]=max(dp[s],1+dp[s-C[d]])` từ trạng thái đạt được. Duyệt tăng cho phép dùng một chữ số nhiều lần.

Thử riêng chữ số đầu $d=1,\ldots,9$. Độ dài hợp lệ lớn nhất là $L=\max(1+dp[N-C_d])$. Nếu không có chữ số đầu nào hợp lệ, chỉ còn số `0` khi $N=C_0$; các trường hợp khác in `-1`.

Truy vết từ trái sang phải: thử chữ số lớn xuống nhỏ và chỉ chọn $d$ nếu `dp[rest-C[d]]` đúng bằng số vị trí còn lại. Riêng vị trí đầu không thử $0$. Điều kiện này bảo đảm có hậu tố đạt độ dài tối ưu, nên lựa chọn chữ số lớn nhất tạo tiền tố lớn nhất mà vẫn hoàn thành được. Nếu hậu tố dài hơn số vị trí còn lại thì sẽ tạo một số hợp lệ dài hơn $L$, mâu thuẫn; do đó kiểm tra bằng nhau là đầy đủ.

Thời gian $O(10N)$, bộ nhớ $O(N)$, bao gồm chuỗi kết quả. Không chuyển đáp án sang kiểu số nguyên.

## Kiểm thử

32 file: 2 ví dụ, 10 trường hợp biên, 6 trường hợp nhỏ, 8 ngẫu nhiên và 6 trường hợp lớn. Nhóm `max` chứa test đạt giới hạn, cùng các dạng đặc biệt ở kích thước lớn. Các subtask có thể chồng lấp; điểm chỉ nhận khi đúng tất cả test thỏa ràng buộc subtask tương ứng.

Chạy `python3 custom/knapsack15/tests/check.py` từ thư mục gốc để sinh và kiểm tra test, đối chiếu lời giải với vét cạn độc lập, kiểm tra verifier/checker và đối chiếu `hash.json`. Khi chủ động đổi dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
