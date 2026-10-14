# Lời giải — Đặt dấu cộng hoặc trừ

Đặt $T=\sum A_i$ và gọi $P$ là tổng các số mang dấu cộng. Giá trị biểu thức là $P-(T-P)=2P-T$, do đó cần $P=(T+X)/2$.

Nếu $X\notin[-T,T]$ hoặc $T+X$ lẻ, đáp án là `NO`. Ngược lại, dùng `dp[s]` biểu diễn có thể chọn một tập chỉ số có tổng $s$ hay không. Khởi tạo `dp[0]=true`; với mỗi $A_i$, duyệt $s$ giảm dần và cập nhật `dp[s] |= dp[s-A_i]`.

Duyệt giảm bảo đảm mỗi số được dùng tối đa một lần. Mỗi cách đặt dấu tương ứng với đúng một tập các vị trí mang dấu cộng; vì vậy phép biến đổi và quy hoạch động đều bao phủ đúng các phương án. Đáp án là `dp[(T+X)/2]`.

Thời gian $O(NT)$, bộ nhớ $O(T)$. Dùng số nguyên 64 bit khi tính $T+X$.

## Kiểm thử

32 file: 2 ví dụ, 10 trường hợp biên, 6 trường hợp nhỏ, 8 ngẫu nhiên và 6 trường hợp lớn. Nhóm `max` chứa test đạt giới hạn, cùng các dạng đặc biệt ở kích thước lớn. Các subtask có thể chồng lấp; điểm chỉ nhận khi đúng tất cả test thỏa ràng buộc subtask tương ứng.

Chạy `python3 custom/knapsack10/tests/check.py` từ thư mục gốc để sinh và kiểm tra test, đối chiếu lời giải với vét cạn độc lập, kiểm tra verifier/checker và đối chiếu `hash.json`. Khi chủ động đổi dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
