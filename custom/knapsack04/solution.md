# Lời giải — Chọn đồ lấp đầy túi

## Trạng thái và khởi tạo

`dp[s]` là tổng giá trị lớn nhất của các món đã xét có tổng trọng lượng **đúng bằng** $s$. Khởi tạo `dp[0]=0`, các trạng thái khác bằng âm vô cùng để phân biệt tổng không đạt được với giá trị bằng $0$.

## Chuyển trạng thái

Với món $(W_i,V_i)$, duyệt $s$ từ $C$ giảm về $W_i$. Chỉ khi `dp[s-W_i]` đạt được mới cập nhật:

$$dp[s]=\max(dp[s],dp[s-W_i]+V_i).$$

Nhánh giữ nguyên bỏ món; nhánh còn lại lấy món. Duyệt giảm để không chọn lại món mới. Không cộng giá trị vào trạng thái không đạt được.

## Chứng minh và kết quả

Một phương án có tổng trọng lượng $s$ hoặc không lấy món mới, hoặc lấy nó và có phần còn lại nặng đúng $s-W_i$. Giữ phương án giá trị lớn nhất của phần còn lại đủ để tối ưu nhánh thứ hai. Bởi vậy DP ghi nhận đúng tối ưu cho từng trọng lượng chính xác.

Đáp án chỉ là `dp[C]`, không lấy lớn nhất trên các trọng lượng nhỏ hơn $C$. In `-1` nếu trạng thái này không đạt được. Với $C=0$, tập rỗng cho kết quả $0$.

Không khởi tạo toàn bộ DP bằng $0$: cách đó biến trạng thái thành "không vượt sức chứa", là bài KNAPSACK00 chứ không phải bài này.

## Độ phức tạp

Thời gian $O(N(C+1))$, bộ nhớ $O(C+1)$. Tổng giá trị có thể tới $2\cdot10^{11}$, nên dùng số nguyên 64 bit.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Bao gồm mục tiêu bằng $0$, không có nghiệm, phần tử lớn hơn mục tiêu, phần tử trùng nhau, lỗi tái sử dụng một món, và dữ liệu đạt giới hạn. Các bài tối ưu giá trị có test vượt số nguyên 32 bit; bài đếm có test số cách vượt modulo.

Chạy `python3 custom/knapsack04/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải, verifier/checker và hash, không xuất HTML. Khi chủ động thay bộ dữ liệu, thêm `--update-hashes`. Subtask 1 gồm các test có $N\le20$; subtask 2 gồm các test có $C\le1000$; subtask 3 gồm toàn bộ test. Các nhóm có thể chồng lấp.
