# Lời giải — DPSTRING00

Gọi $dp[c]$ là độ dài lớn nhất của một dãy con hợp lệ kết thúc bằng chữ $c$ trong phần xâu đã xét. Ban đầu hai giá trị đều bằng $0$, biểu diễn khả năng bắt đầu dãy mới.

Khi gặp chữ $c$, có thể bỏ qua hoặc nối nó vào dãy kết thúc bằng chữ còn lại:

$$dp[c]\gets\max(dp[c],dp[1-c]+1).$$

Chỉ cập nhật trạng thái của chữ hiện tại. Đáp án là $N-\max(dp[0],dp[1])$. Mỗi dãy giữ lại tương ứng với việc xóa các vị trí còn lại, nên tối đa hóa độ dài giữ lại chính là tối thiểu hóa số lần xóa.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ phụ của phần DP: $O(1)$; mã C++ lưu thêm mảng điểm/chi phí đầu vào ở các bài có mảng này.

