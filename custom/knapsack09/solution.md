# Lời giải — Chọn đồ lấp đầy túi

`dp[s]` là giá trị lớn nhất khi trọng lượng **đúng bằng** $s$ với các loại đã xét. Khởi tạo `dp[0]=0`, các trạng thái khác bằng âm vô cùng để đánh dấu không đạt được.

Với loại $(W_i,V_i)$, duyệt $s$ **tăng dần** từ $W_i$ tới $C$. Chỉ khi trạng thái nguồn đạt được mới cập nhật:

$$dp[s]=\max(dp[s],dp[s-W_i]+V_i).$$

Một phương án hoặc không dùng loại mới, hoặc dùng ít nhất một đồ vật loại mới. Bỏ một đồ vật loại này còn tổng trọng lượng $s-W_i$. Trạng thái nguồn đã cho phép lấy loại mới nhiều lần, nên lấy thêm một đồ vật là hợp lệ. Hai nhánh đầy đủ và phép lấy lớn nhất giữ phương án tốt nhất ở từng tổng chính xác.

Chỉ trả về `dp[C]`, không lấy lớn nhất trên các trọng lượng nhỏ hơn $C$. Nếu `dp[C]` không đạt được, in `-1`. Khi $C=0$, tập rỗng cho giá trị $0$.

Không khởi tạo mọi trạng thái bằng $0$: làm vậy sẽ giải bài không vượt sức chứa thay vì bài đạt đúng sức chứa. Trọng lượng dương bảo đảm tổng số đồ vật hữu hạn dù số lượng mỗi loại không giới hạn.

## Độ phức tạp

Thời gian $O(N(C+1))$, bộ nhớ $O(C+1)$. Vì mỗi trọng lượng ít nhất $1$, chọn được tối đa $C$ đồ vật; tổng giá trị có thể tới $10^{13}$, phải dùng số nguyên 64 bit.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Bao phủ mục tiêu $0$, không có nghiệm, dùng một loại nhiều lần, phần tử vượt mục tiêu, giá trị cực đại, dữ liệu đạt $N=100$ và mục tiêu $10000$. Bài đếm còn kiểm tra thứ tự mệnh giá và số cách vượt modulo. Test `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc tương ứng, các nhóm có thể chồng lấp.

Chạy `python3 custom/knapsack09/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải, verifier/checker, test độc lập và hash. Khi chủ động thay bộ dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
