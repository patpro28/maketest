# PREFIX03 — Hướng dẫn giải

Duyệt ngày bán từ $2$ đến $N$, duy trì giá nhỏ nhất của các ngày trước đó. Lợi nhuận tốt nhất cho ngày bán hiện tại bằng giá hôm nay trừ giá nhỏ nhất đó. Lấy max với đáp án ban đầu bằng $0$, rồi cập nhật giá nhỏ nhất. Nếu $N=1$, đáp án là $0$.

Tính đúng đắn: Mỗi giao dịch có một ngày bán; ở ngày đó giá mua nhỏ nhất trong các ngày trước cho lợi nhuận tối ưu. Lấy lớn nhất qua mọi ngày và phương án không giao dịch là đủ.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ: $O(1)$ (tính cả dữ liệu và danh sách kết quả nếu có).

Dùng số nguyên 64 bit cho tổng, năng lượng và số đoạn; tổng có thể đạt $2\cdot10^{14}$ và số đoạn có thể đạt $N(N+1)/2$.
