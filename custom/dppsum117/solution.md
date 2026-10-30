# PREFIX17 — Hướng dẫn giải

Đặt $C_1=0$, $C_i=1$ khi $S_i\ne S_{i-1}$ và $C_i=0$ nếu bằng nhau. Tính tổng tiền tố $P$ của $C$. Đáp án là $1+P_R-P_L$, không phải $1+P_R-P_{L-1}$.

Tính đúng đắn: Đoạn không rỗng có một nhóm ban đầu. Mỗi lần đổi ký tự tại vị trí từ L+1 đến R tạo thêm đúng một nhóm; ký tự trước L không thuộc chuỗi con nên không được xét.

Thời gian: $O(N+Q)$. Bộ nhớ: $O(N)$.

Dùng số nguyên 64 bit cho tổng và số cách.
