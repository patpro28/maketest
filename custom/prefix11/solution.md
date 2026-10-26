# PREFIX11 — Hướng dẫn giải

Đặt $C_i=A_i$ nếu $i$ lẻ, $C_i=-A_i$ nếu $i$ chẵn. Tính tổng tiền tố $P$ của $C$. Lấy $v=P_R-P_{L-1}$. Nếu $L$ lẻ trả $v$, nếu $L$ chẵn trả $-v$.

Tính đúng đắn: Các dấu trong mảng biến đổi luôn xen kẽ. Khi đầu đoạn có dấu âm, đổi dấu cả tổng sẽ khiến phần tử đầu mang dấu cộng và mọi dấu còn lại đúng yêu cầu.

Thời gian: $O(N+Q)$. Bộ nhớ: $O(N)$.

Dùng số nguyên 64 bit cho tổng và số cách.
