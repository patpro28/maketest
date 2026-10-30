# PREFIX010 — Hướng dẫn giải

Đặt $C_i=1$ nếu $A_i$ chẵn và $C_i=0$ nếu ngược lại. Tính $P_0=0$, $P_i=P_{i-1}+C_i$. Mỗi truy vấn trả về $P_R-P_{L-1}$.

Tính đúng đắn: Mỗi phần tử chẵn đóng góp đúng $1$, phần tử lẻ đóng góp $0$. Hiệu hai tổng tiền tố chỉ giữ các phần tử thuộc đoạn cần đếm.

Thời gian: $O(N+Q)$. Bộ nhớ: $O(N)$.

Dùng số nguyên 64 bit cho tổng và số cách.
