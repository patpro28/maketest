# PREFIX16 — Hướng dẫn giải

Đặt $P_1=0$, $P_i=P_{i-1}+|H_i-H_{i-1}|$ với $i\ge2$. Truy vấn trả về $|P_R-P_L|$.

Tính đúng đắn: Mọi đường đi từ L đến R đi qua đúng các cạnh nằm giữa hai trạm, mỗi cạnh một lần. Hiệu hai tổng tiền tố lấy đúng tổng chi phí các cạnh này, còn trị tuyệt đối xử lý cả hai hướng.

Thời gian: $O(N+Q)$. Bộ nhớ: $O(N)$.

Dùng số nguyên 64 bit cho tổng và số cách.
