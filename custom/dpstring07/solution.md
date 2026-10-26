# Lời giải — DPSTRING07

Lưu $E$: điểm tốt nhất sau một số cặp đã hoàn tất; $P_a,P_b$: điểm tốt nhất khi đã hoàn tất một số cặp và giữ thêm ký tự đầu của cặp mới là `a` hoặc `b`.

Ban đầu $E=0$, hai trạng thái chờ là âm vô cùng. Với ký tự $c$ có điểm $w$, có thể bỏ qua; mở cặp mới từ $E$ cũ để cập nhật $P_c$; hoặc đóng cặp từ $P_d$ với $d\ne c$ để cập nhật $E$.

Các phép chuyển phải dùng giá trị trước vị trí hiện tại. Không được dùng ngay $E$ vừa cập nhật để mở thêm cặp bằng chính ký tự đó. Đáp án chỉ là $E$, vì trạng thái chờ còn một ký tự chưa được ghép.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ phụ của phần DP: $O(1)$; mã C++ lưu thêm mảng điểm/chi phí đầu vào ở các bài có mảng này.

Dùng số nguyên 64 bit cho điểm và chi phí. Khi cập nhật nhiều trạng thái, chỉ sử dụng giá trị của tiền tố trước đó.
