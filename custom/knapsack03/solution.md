# Lời giải — Đếm số cách chọn đạt đúng tổng

## Trạng thái và khởi tạo

`dp[s]` là số tập chỉ số của các vị trí đã xét có tổng **đúng bằng** $s$, lấy modulo $10^9+7$. Khởi tạo `dp[0]=1` cho tập rỗng; các tổng khác bằng $0$.

## Chuyển trạng thái

Với phần tử $A_i$, duyệt $s$ từ $X$ giảm về $A_i$:

$$dp[s]=(dp[s]+dp[s-A_i])\bmod(10^9+7).$$

Hai nhóm được cộng là các tập không chứa vị trí $i$ và các tập chứa vị trí $i$. Chúng rời nhau. Duyệt giảm bảo đảm trạng thái nguồn chưa dùng vị trí $i$.

## Chứng minh và kết quả

Bỏ vị trí $i$ khỏi một tập thuộc nhóm thứ hai cho đúng một tập cũ có tổng $s-A_i$, và thêm vị trí $i$ là phép biến đổi ngược. Do đó hai nhóm được đếm đầy đủ, không trùng. Bất biến về số cách được bảo toàn; đáp án là `dp[X]`.

Không gộp các vị trí có cùng giá trị thành một phần tử: ví dụ $[2,2,3]$ có hai tập đạt tổng $2$. Không đếm thứ tự chọn. Với $X=0$, mọi số đều dương nên chỉ tập rỗng hợp lệ và đáp án là $1$.

Số cách có thể vượt modulo. Một số dư bằng $0$ không đồng nghĩa tổng đó không thể đạt được. Khi cộng hai số dư, giá trị nhỏ hơn $2\cdot10^9+14$, vẫn vừa số nguyên 32 bit có dấu.

## Độ phức tạp

Thời gian $O(N(X+1))$, bộ nhớ $O(X+1)$.

## Kiểm thử

32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Bao gồm mục tiêu bằng $0$, không có nghiệm, phần tử lớn hơn mục tiêu, phần tử trùng nhau, lỗi tái sử dụng một món, và dữ liệu đạt giới hạn. Các bài tối ưu giá trị có test vượt số nguyên 32 bit; bài đếm có test số cách vượt modulo.

Chạy `python3 custom/knapsack03/tests/check.py` từ thư mục gốc để sinh và kiểm tra dữ liệu, lời giải, verifier/checker và hash, không xuất HTML. Khi chủ động thay bộ dữ liệu, thêm `--update-hashes`. Subtask 1 gồm các test có $N\le20$; subtask 2 gồm các test có $X\le1000$; subtask 3 gồm toàn bộ test. Các nhóm có thể chồng lấp.
