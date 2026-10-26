# Lời giải — DPSTRING04

Gọi $dp[c]$ là chi phí nhỏ nhất để tô xong tiền tố đã xét và bóng cuối có màu $c$.

Khi xét vị trí $i$, thử màu mới $c$ và màu trước đó $p\ne c$:

$$new[c]=\min_{p\ne c}dp[p]+[S_i\ne c]\,W_i.$$

Ký hiệu $[P]$ bằng $1$ nếu mệnh đề $P$ đúng và bằng $0$ nếu sai. Khởi tạo ba trạng thái trước vị trí đầu bằng $0$; cách này cho phép bóng đầu nhận màu bất kỳ. Sau mỗi vị trí thay toàn bộ mảng cũ bằng mảng mới. Đáp án là giá trị nhỏ nhất sau vị trí cuối.

Độ phức tạp thời gian: $O(3^2N)$. Bộ nhớ phụ của phần DP: $O(3)$; mã C++ lưu thêm mảng điểm/chi phí đầu vào ở các bài có mảng này.

Dùng số nguyên 64 bit cho điểm và chi phí. Khi cập nhật nhiều trạng thái, chỉ sử dụng giá trị của tiền tố trước đó.
