# Lời giải — Chọn đồ vào túi

`dp[c]` là giá trị lớn nhất khi dùng các loại đã xét và trọng lượng không vượt $c$. Khởi tạo tất cả trạng thái bằng $0$, vì không lấy đồ vật nào luôn hợp lệ.

Với loại $(W_i,V_i)$, duyệt $c$ **tăng dần** từ $W_i$ tới $C$:

$$dp[c]=\max(dp[c],dp[c-W_i]+V_i).$$

Trạng thái giữ nguyên là không lấy loại mới. Khi lấy ít nhất một đồ vật loại mới, bỏ đi một đồ vật đó để được phương án có sức chứa $c-W_i$. Vì $W_i>0$ và duyệt tăng, trạng thái nguồn đã được cập nhật cho loại hiện tại, cho phép lấy loại đó nhiều lần.

Quy nạp theo loại và theo sức chứa chứng minh hai nhánh bao phủ mọi phương án, đồng thời chỉ tạo phương án hợp lệ. Đáp án là `dp[C]`. Duyệt giảm sẽ chỉ cho lấy mỗi loại một lần, thành bài knapsack 0–1. Chọn theo tỉ lệ giá trị/trọng lượng cũng không luôn đúng vì đồ vật không được chia nhỏ.

## Độ phức tạp

Thời gian $O(N(C+1))$, bộ nhớ $O(C+1)$. Vì mỗi trọng lượng ít nhất $1$, chọn được tối đa $C$ đồ vật; tổng giá trị có thể tới $10^{13}$, phải dùng số nguyên 64 bit.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Bao phủ mục tiêu $0$, không có nghiệm, dùng một loại nhiều lần, phần tử vượt mục tiêu, giá trị cực đại, dữ liệu đạt $N=100$ và mục tiêu $10000$. Bài đếm còn kiểm tra thứ tự mệnh giá và số cách vượt modulo. Test `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc tương ứng, các nhóm có thể chồng lấp.

Chạy `python3 custom/knapsack05/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải, verifier/checker, test độc lập và hash. Khi chủ động thay bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
