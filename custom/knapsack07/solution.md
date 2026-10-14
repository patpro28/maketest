# Lời giải — Đổi tiền với ít đồng nhất

`dp[s]` là số đồng tiền ít nhất để đổi đúng $s$ bằng các mệnh giá đã xét. Khởi tạo `dp[0]=0`, các trạng thái khác bằng `INF=X+1`. Vì mỗi đồng có giá trị ít nhất $1$, một phương án đạt $s\le X$ không dùng quá $X$ đồng.

Với mệnh giá $A_i$, duyệt $s$ **tăng dần** từ $A_i$ tới $X$:

$$dp[s]=\min(dp[s],dp[s-A_i]+1).$$

Nhánh giữ nguyên không dùng mệnh giá mới. Nhánh thứ hai dùng một đồng mới và phương án tốt nhất cho số tiền còn lại; trạng thái nguồn đã cho phép dùng mệnh giá hiện tại nhiều lần. Nếu nguồn không đạt được, `INF+1` không cải thiện trạng thái.

Mọi phương án có dùng mệnh giá mới đều tách được một đồng như trên, nên phép lấy nhỏ nhất bảo toàn tối ưu. In `dp[X]`, hoặc `-1` nếu vẫn bằng `INF`. Với $X=0$, đáp án bằng $0$.

Không thể dùng `INF=N+1` như bài chọn thẻ 0–1: số đồng cần dùng có thể lớn hơn số mệnh giá. Ví dụ chỉ có mệnh giá $1$, đổi $10000$ cần $10000$ đồng. Tham lam lấy đồng lớn nhất cũng sai với mệnh giá tùy ý, như $[1,3,4]$ và $X=6$.

## Độ phức tạp

Thời gian $O(N(X+1))$, bộ nhớ $O(X+1)$.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Bao phủ mục tiêu $0$, không có nghiệm, dùng một loại nhiều lần, phần tử vượt mục tiêu, giá trị cực đại, dữ liệu đạt $N=100$ và mục tiêu $10000$. Bài đếm còn kiểm tra thứ tự mệnh giá và số cách vượt modulo. Test `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc tương ứng, các nhóm có thể chồng lấp.

Chạy `python3 custom/knapsack07/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải, verifier/checker, test độc lập và hash. Khi chủ động thay bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
