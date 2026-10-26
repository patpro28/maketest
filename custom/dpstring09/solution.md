# Lời giải — DPSTRING09

Vì màu mới phải khác hai ô trước, lưu $dp[a][b]$: chi phí nhỏ nhất khi hai màu cuối là $a,b$. Thêm màu giả $4$ cho các vị trí trước đầu xâu; khởi tạo $dp[4][4]=0$.

Khi xét vị trí $i$, thử màu $c$ khác cả $a$ và $b$:

$$new[b][c]=\min\bigl(new[b][c],dp[a][b]+[S_i\ne c]\,W_i\bigr).$$

Không chuyển từ trạng thái vô cùng. Sau khi xử lý hết xâu, lấy giá trị nhỏ nhất trong mọi trạng thái. Màu giả không được chọn cho ô thực. Mỗi lần chuyển kiểm tra đúng các cặp mới có khoảng cách một hoặc hai, nên xâu tạo ra luôn hợp lệ; mọi xâu hợp lệ đều được xét.

Độ phức tạp thời gian: $O(4^3N)$. Bộ nhớ phụ của phần DP: $O(4^2)$; mã C++ lưu thêm mảng điểm/chi phí đầu vào ở các bài có mảng này.

Dùng số nguyên 64 bit cho điểm và chi phí. Khi cập nhật nhiều trạng thái, chỉ sử dụng giá trị của tiền tố trước đó.
