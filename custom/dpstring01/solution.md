# Lời giải — DPSTRING01

Gọi $dp[0],dp[1]$ là điểm lớn nhất của dãy hợp lệ kết thúc lần lượt bằng phụ âm và nguyên âm. Khởi tạo cả hai bằng $0$ để cho phép bắt đầu bằng bất kỳ loại nào.

Với ký tự loại $t$ có điểm $w$, chỉ cập nhật:

$$dp[t]\gets\max(dp[t],dp[1-t]+w).$$

Nhánh đầu bỏ ký tự hiện tại; nhánh sau giữ nó và nối vào một dãy kết thúc bằng loại đối diện, hoặc bắt đầu dãy mới. Đáp án là giá trị lớn nhất trong hai trạng thái.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ phụ của phần DP: $O(1)$; mã C++ lưu thêm mảng điểm/chi phí đầu vào ở các bài có mảng này.

Dùng số nguyên 64 bit cho điểm và chi phí. Khi cập nhật nhiều trạng thái, chỉ sử dụng giá trị của tiền tố trước đó.
