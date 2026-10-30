# PREFIX030 — Hướng dẫn giải

Đặt $B_1=0$. Với $i\ge2$, nếu $A_i>A_{i-1}$ thì đặt $B_i=A_i-A_{i-1}$; ngược lại đặt $B_i=0$. Tính tổng tiền tố $P$ của $B$, mỗi truy vấn trả về $P_R-P_L$.

Tính đúng đắn: Mỗi $B_i$ chính là độ tăng ở bước kết thúc tại $i$, các bước giảm hoặc bằng nhau không đóng góp. Tổng từ $L+1$ đến $R$ xét đúng mọi bước bên trong đoạn, nên bằng tổng các độ tăng được yêu cầu.

Thời gian $O(N+Q)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho các tổng. Đổi sang số nguyên 64 bit trước khi trừ hai phần tử; độ lệch có thể bằng $2\cdot10^9$ và tổng có thể lớn hơn số nguyên 32 bit.
