# Lời giải — DPSTRING03

Tối đa hóa tổng chi phí được giữ lại. Lưu $dp[c][k]$: điểm tốt nhất của dãy kết thúc bằng một đoạn gồm đúng $k$ chữ $c$, với $k\in\{1,2\}$. Các trạng thái chưa tồn tại mang giá trị âm vô cùng.

Với chữ $c$ có điểm $w$, bắt đầu đoạn cuối mới bằng cách nối vào dãy rỗng hoặc dãy kết thúc bằng chữ khác $c$. Để đoạn cuối có độ dài $2$, chỉ được nối vào trạng thái cũ $dp[c][1]$. Ngoài ra có thể bỏ ký tự, giữ nguyên các trạng thái.

Phải tính cả hai phương án từ trạng thái trước khi xét vị trí hiện tại, tránh sử dụng một ký tự hai lần. Đáp án là tổng chi phí ban đầu trừ điểm giữ lại lớn nhất, kể cả phương án rỗng.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ phụ của phần DP: $O(1)$; mã C++ lưu thêm mảng điểm/chi phí đầu vào ở các bài có mảng này.

Dùng số nguyên 64 bit cho điểm và chi phí. Khi cập nhật nhiều trạng thái, chỉ sử dụng giá trị của tiền tố trước đó.
