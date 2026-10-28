# PREFIX000 — Hướng dẫn giải

Đặt $S_0=0$ và $S_i=S_{i-1}+A_i$. Các ngày trước $L$ có trong cả $S_R$ và $S_{L-1}$ nên tổng cần tìm là $S_R-S_{L-1}$.

Tính đúng đắn: Công thức hiệu hai tổng tiền tố giữ đúng và đủ các phần tử trong đoạn truy vấn.

Độ phức tạp thời gian: $O(N+Q)$. Bộ nhớ: $O(N)$ (tính cả dữ liệu và danh sách kết quả nếu có).

Dùng số nguyên 64 bit cho tổng, năng lượng và số đoạn; tổng có thể đạt $2\cdot10^{14}$ và số đoạn có thể đạt $N(N+1)/2$.
