# Lời giải — DPSTRING05

Gọi $dp[A],dp[B]$ là chi phí nhỏ nhất sau khi điền tiền tố, biết ký tự cuối là `A` hoặc `B`. Trạng thái không thể đạt có giá trị vô cùng.

Tại vị trí đầu, các chữ được phép điền có chi phí $0$. Tại vị trí tiếp theo, thử mỗi chữ được phép $c$ và mỗi chữ cuối cũ $p$, cộng thêm chi phí của cặp $(p,c)$: $X$ cho `AB`, $Y$ cho `BA`, còn lại là $0$.

Một vị trí là `?` cho phép cả hai chữ; ký tự cố định chỉ cho phép đúng chữ đó. Mỗi cặp được cộng đúng một lần khi xử lý ký tự thứ hai, nên lấy trạng thái nhỏ nhất ở cuối sẽ được đáp án.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ phụ của phần DP: $O(1)$; mã C++ lưu thêm mảng điểm/chi phí đầu vào ở các bài có mảng này.

Dùng số nguyên 64 bit cho điểm và chi phí. Khi cập nhật nhiều trạng thái, chỉ sử dụng giá trị của tiền tố trước đó.
