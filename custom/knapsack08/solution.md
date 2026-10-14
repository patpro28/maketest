# Lời giải — Đếm số cách đổi tiền

`dp[s]` là số cách đổi đúng $s$ bằng các mệnh giá đã xét, modulo $10^9+7$. Khởi tạo `dp[0]=1` cho cách không lấy đồng nào.

Duyệt **mệnh giá ở vòng ngoài**. Với mệnh giá $A_i$, duyệt $s$ **tăng dần** từ $A_i$ tới $X$:

$$dp[s]=(dp[s]+dp[s-A_i])\bmod(10^9+7).$$

Các cách đổi tổng $s$ chia thành hai nhóm rời nhau: không dùng mệnh giá $A_i$, và dùng ít nhất một đồng mệnh giá $A_i$. Nhóm thứ nhất nằm trong giá trị cũ. Với nhóm thứ hai, bỏ đi một đồng mệnh giá $A_i$ cho đúng một bộ số lượng ở tổng $s-A_i$ có thể vẫn dùng mệnh giá này. Duyệt tăng bảo đảm nguồn đã chứa các cách đó.

Quy nạp cho thấy mỗi bộ số lượng được đếm đúng một lần. Nếu đảo thành tổng ở vòng ngoài rồi thử mọi mệnh giá, ta có thể đếm các thứ tự khác nhau như $1+2$ và $2+1$ thành hai cách, trái với đề. Các mệnh giá phải đôi một khác nhau để mỗi loại đồng tiền được xử lý một lần.

Đáp án là `dp[X]`; khi $X=0$ là $1$. Một số dư bằng $0$ không đồng nghĩa không có cách đổi. Khi cộng hai số dư, giá trị vẫn vừa số nguyên 32 bit có dấu.

## Độ phức tạp

Thời gian $O(N(X+1))$, bộ nhớ $O(X+1)$.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Bao phủ mục tiêu $0$, không có nghiệm, dùng một loại nhiều lần, phần tử vượt mục tiêu, giá trị cực đại, dữ liệu đạt $N=100$ và mục tiêu $10000$. Bài đếm còn kiểm tra thứ tự mệnh giá và số cách vượt modulo. Test `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc tương ứng, các nhóm có thể chồng lấp.

Chạy `python3 custom/knapsack08/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải, verifier/checker, test độc lập và hash. Khi chủ động thay bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
