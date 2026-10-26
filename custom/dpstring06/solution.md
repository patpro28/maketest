# Lời giải — DPSTRING06

Chỉ cần ba trạng thái: kết thúc bằng một nguyên âm ($V$), một phụ âm ($C_1$), hoặc hai phụ âm liên tiếp ($C_2$). Dãy rỗng có điểm $0$; các trạng thái chưa có dãy mang giá trị âm vô cùng.

Gặp nguyên âm có điểm $w$, có thể nối sau dãy rỗng, $C_1$ hoặc $C_2$ để cập nhật $V$. Gặp phụ âm, có thể nối sau dãy rỗng hoặc $V$ để cập nhật $C_1$, hoặc nối sau $C_1$ cũ để cập nhật $C_2$. Luôn có thêm phương án bỏ ký tự và giữ nguyên trạng thái.

Không cho phép nối nguyên âm sau $V$ hoặc phụ âm sau $C_2$. Các chuyển còn lại đều hợp lệ và bao phủ mọi cách chọn. Đáp án là giá trị lớn nhất của ba trạng thái và $0$.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ phụ của phần DP: $O(1)$; mã C++ lưu thêm mảng điểm/chi phí đầu vào ở các bài có mảng này.

Dùng số nguyên 64 bit cho điểm và chi phí. Khi cập nhật nhiều trạng thái, chỉ sử dụng giá trị của tiền tố trước đó.
