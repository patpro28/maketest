# Lời giải — Chọn ít thẻ nhất

## Trạng thái và khởi tạo

`dp[s]` là số thẻ ít nhất cần chọn từ các thẻ đã xét để đạt tổng **đúng bằng** $s$. Khởi tạo `dp[0]=0`, các trạng thái khác bằng `INF=N+1`; mọi nghiệm hợp lệ dùng không quá $N$ thẻ.

## Chuyển trạng thái

Với thẻ ghi $A_i$, duyệt $s$ từ $X$ giảm về $A_i$:

$$dp[s]=\min(dp[s],dp[s-A_i]+1).$$

Giữ nguyên trạng thái là không lấy thẻ; chuyển từ tổng $s-A_i$ là lấy thẻ. Khi nguồn bằng `INF`, ứng viên `INF+1` không cải thiện trạng thái, nên không tạo nghiệm giả.

## Chứng minh và kết quả

Mỗi phương án đạt tổng $s$ hoặc bỏ qua thẻ mới, hoặc dùng thẻ đó và một phương án đạt $s-A_i$. Với lựa chọn thứ hai, phương án ít thẻ nhất cho tổng còn lại luôn tốt nhất, nên phép lấy nhỏ nhất bảo toàn bất biến. Duyệt giảm đảm bảo mỗi thẻ chỉ được chọn một lần.

In `dp[X]`, hoặc `-1` nếu vẫn bằng `INF`. Với $X=0$, đáp án bằng $0$. Đây là bài chọn thẻ 0–1: không được dùng lại thẻ như bài đổi tiền với nguồn cung không giới hạn.

## Độ phức tạp

Thời gian $O(N(X+1))$, bộ nhớ $O(X+1)$.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Bao gồm mục tiêu bằng $0$, không có nghiệm, phần tử lớn hơn mục tiêu, phần tử trùng nhau, lỗi tái sử dụng một món, và dữ liệu đạt giới hạn. Các bài tối ưu giá trị có test vượt số nguyên 32 bit; bài đếm có test số cách vượt modulo.

Chạy `python3 custom/knapsack02/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải, verifier/checker và hash, không xuất HTML. Khi chủ động thay bộ dữ liệu, thêm `--update-hashes`. Subtask 1 gồm các test có $N\le20$; subtask 2 gồm các test có $X\le1000$; subtask 3 gồm toàn bộ test. Các nhóm có thể chồng lấp.
