# Lời giải — DPSTRING02

Đổi mục tiêu thành giữ lại tổng chi phí lớn nhất. Gọi $dp[c]$ là tổng chi phí lớn nhất của dãy hợp lệ kết thúc bằng chữ $c$; có thể khởi tạo bằng $0$ vì mọi chi phí không âm.

Khi gặp chữ $c$ có chi phí $w$, tính $best=\max(0,\max_{d\ne c}dp[d])$ trước khi cập nhật, rồi gán $dp[c]\gets\max(dp[c],best+w)$.

Đáp án bằng tổng mọi chi phí trừ đi giá trị giữ lại lớn nhất. Mọi dãy hợp lệ kết thúc bằng $c$ hoặc không dùng vị trí hiện tại, hoặc trước đó kết thúc bằng chữ khác $c$; do đó phép chuyển xét đủ các khả năng.

Độ phức tạp thời gian: $O(26N)$. Bộ nhớ phụ của phần DP: $O(26)$; mã C++ lưu thêm mảng điểm/chi phí đầu vào ở các bài có mảng này.

Dùng số nguyên 64 bit cho điểm và chi phí. Khi cập nhật nhiều trạng thái, chỉ sử dụng giá trị của tiền tố trước đó.
