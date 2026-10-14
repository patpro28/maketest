# Lời giải — Ghép đoạn dây đạt đúng độ dài

`dp[s]` cho biết có ghép được đúng chiều dài $s$ từ các loại đã xét hay không. Khởi tạo `dp[0]=true`, các trạng thái khác bằng `false`.

Với chiều dài $A_i$, duyệt $s$ **tăng dần** từ $A_i$ tới $X$:

$$dp[s]=dp[s]\lor dp[s-A_i].$$

Một phương án hoặc không dùng loại mới, hoặc có ít nhất một đoạn loại mới. Bỏ một đoạn ở trường hợp thứ hai còn chiều dài $s-A_i$. Trạng thái nguồn đã xét loại mới tại tổng nhỏ hơn, nên phép chuyển cho phép sử dụng nó nhiều lần.

Bất biến về khả năng ghép đúng tổng được bảo toàn bằng quy nạp; đáp án là `dp[X]`. Với $X=0$, đáp án là `YES`. Các chiều dài dương bảo đảm không có vòng lặp tại cùng một tổng. Những loại trùng chiều dài không thay đổi khả năng ghép.

Điều kiện $\gcd(A_1,\ldots,A_N)\mid X$ chỉ là điều kiện cần, không đủ cho mọi $X$ nhỏ. Ví dụ $A=[4,6]$, $X=2$ vẫn không ghép được.

## Độ phức tạp

Thời gian $O(N(X+1))$, bộ nhớ $O(X+1)$.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Bao phủ mục tiêu $0$, không có nghiệm, dùng một loại nhiều lần, phần tử vượt mục tiêu, giá trị cực đại, dữ liệu đạt $N=100$ và mục tiêu $10000$. Bài đếm còn kiểm tra thứ tự mệnh giá và số cách vượt modulo. Test `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc tương ứng, các nhóm có thể chồng lấp.

Chạy `python3 custom/knapsack06/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải, verifier/checker, test độc lập và hash. Khi chủ động thay bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
