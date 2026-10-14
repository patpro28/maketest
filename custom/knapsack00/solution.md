# Lời giải — Chọn đồ vào túi

## Trạng thái và khởi tạo

`dp[c]` là tổng giá trị lớn nhất khi chỉ dùng các món đã xét và tổng trọng lượng **không vượt** $c$. Khởi tạo tất cả trạng thái bằng $0$, vì tập rỗng hợp lệ với mọi sức chứa.

## Chuyển trạng thái

Với món $(W_i,V_i)$, duyệt $c$ từ $C$ giảm về $W_i$:

$$dp[c]=\max(dp[c],dp[c-W_i]+V_i).$$

Nhánh thứ nhất không lấy món, nhánh thứ hai lấy món đúng một lần. Do $W_i>0$ và duyệt giảm, `dp[c-W_i]` vẫn là trạng thái trước khi xét món hiện tại. Các sức chứa nhỏ hơn $W_i$ giữ nguyên.

## Chứng minh và kết quả

Theo quy nạp, trước khi xét món mới, DP chứa tối ưu cho các món cũ. Mỗi phương án mới hoặc bỏ món mới, hoặc lấy nó và phần còn lại vừa sức chứa $c-W_i$. Hai nhánh bao phủ mọi phương án, nên phép lấy lớn nhất bảo toàn bất biến. Đáp án là `dp[C]`.

Không dùng lựa chọn tham lam theo giá trị hoặc tỉ lệ giá trị/trọng lượng: một lựa chọn cục bộ có thể chặn tổ hợp tốt hơn. Duyệt sức chứa tăng sẽ cho phép lấy lại một món nhiều lần, sai với knapsack 0–1.

## Độ phức tạp

Thời gian $O(N(C+1))$, bộ nhớ $O(C+1)$. Tổng giá trị có thể tới $2\cdot10^{11}$, nên dùng số nguyên 64 bit.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Bao gồm mục tiêu bằng $0$, không có nghiệm, phần tử lớn hơn mục tiêu, phần tử trùng nhau, lỗi tái sử dụng một món, và dữ liệu đạt giới hạn. Các bài tối ưu giá trị có test vượt số nguyên 32 bit; bài đếm có test số cách vượt modulo.

Chạy `python3 custom/knapsack00/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải, verifier/checker và hash, không xuất HTML. Khi chủ động thay bộ dữ liệu, thêm `--update-hashes`. Subtask 1 gồm các test có $N\le20$; subtask 2 gồm các test có $C\le1000$; subtask 3 gồm toàn bộ test. Các nhóm có thể chồng lấp.
