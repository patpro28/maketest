# PREFIX01 — Hướng dẫn giải

Khởi tạo giá trị nhỏ nhất và lớn nhất bằng $A_1$. Xét từng ngày từ $2$: kiểm tra giá trị hiện tại với min và max của các ngày trước, tăng đáp án nếu nhỏ hơn min hoặc lớn hơn max, rồi mới cập nhật hai giá trị. Phép so sánh phải nghiêm ngặt.

Tính đúng đắn: Trước mỗi ngày, hai giá trị duy trì đúng cực trị của toàn bộ các ngày trước. Do đó điều kiện kiểm tra tương đương định nghĩa kỷ lục.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ: $O(1)$ (tính cả dữ liệu và danh sách kết quả nếu có).

Dùng số nguyên 64 bit cho tổng, năng lượng và số đoạn; tổng có thể đạt $2\cdot10^{14}$ và số đoạn có thể đạt $N(N+1)/2$.
