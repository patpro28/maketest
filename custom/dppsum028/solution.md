# PREFIX028 — Hướng dẫn giải

Đặt $B_1=0$ và $B_i=|A_i-A_{i-1}|$ với $i\ge2$. Tính tổng tiền tố $P$ của $B$. Truy vấn trả về $P_R-P_L$.

Tính đúng đắn: Mỗi độ lệch cần cộng ứng với đúng một chỉ số bên phải từ $L+1$ đến $R$. Hiệu hai tổng tiền tố giữ đúng các độ lệch này, và tự trả $0$ khi $L=R$.

Thời gian $O(N+Q)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho các tổng. Đổi sang số nguyên 64 bit trước khi trừ hai phần tử; độ lệch có thể bằng $2\cdot10^9$ và tổng có thể lớn hơn số nguyên 32 bit.
