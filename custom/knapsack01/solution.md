# Lời giải — Chọn các số có tổng cho trước

## Trạng thái và khởi tạo

`dp[s]` đúng khi chọn được một tập các vị trí đã xét có tổng **đúng bằng** $s$. Khởi tạo `dp[0]=true`, các tổng khác bằng `false`.

## Chuyển trạng thái

Với phần tử $A_i$, duyệt tổng từ $X$ giảm về $A_i$:

$$dp[s]=dp[s]\lor dp[s-A_i].$$

Nhánh giữ nguyên ứng với không chọn vị trí $i$; nhánh thứ hai ứng với chọn vị trí $i$. Duyệt giảm để trạng thái nguồn chưa dùng vị trí mới.

## Chứng minh và kết quả

Mỗi tập con của các vị trí đã xét hoặc không chứa vị trí mới, hoặc chứa vị trí mới và phần còn lại có tổng $s-A_i$. Bất biến đúng ban đầu và được bảo toàn bởi hai nhánh này, nên đáp án là `dp[X]`.

Các phần tử lớn hơn $X$ không thể thuộc một phương án hợp lệ vì mọi phần tử đều dương. Với $X=0$, chỉ tập rỗng hợp lệ, đáp án là `YES`. Những vị trí có cùng giá trị vẫn phải được xử lý riêng.

## Độ phức tạp

Thời gian $O(N(X+1))$, bộ nhớ $O(X+1)$.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Bao gồm mục tiêu bằng $0$, không có nghiệm, phần tử lớn hơn mục tiêu, phần tử trùng nhau, lỗi tái sử dụng một món, và dữ liệu đạt giới hạn. Các bài tối ưu giá trị có test vượt số nguyên 32 bit; bài đếm có test số cách vượt modulo.

Chạy `python3 custom/knapsack01/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải, verifier/checker và hash, không xuất HTML. Khi chủ động thay bộ dữ liệu, thêm `--update-hashes`. Subtask 1 gồm các test có $N\le20$; subtask 2 gồm các test có $X\le1000$; subtask 3 gồm toàn bộ test. Các nhóm có thể chồng lấp.
