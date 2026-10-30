# PREFIX029 — Hướng dẫn giải

Đặt $B_1=0$. Với $i\ge2$, đặt $B_i=1$ khi một trong $A_{i-1},A_i$ chẵn và số còn lại lẻ, ngược lại bằng $0$. Tính tổng tiền tố $P$ rồi trả $P_R-P_L$. So sánh hai điều kiện chia hết cho $2$, tránh so sánh trực tiếp phần dư của số âm và số dương.

Tính đúng đắn: Mỗi lần đổi chẵn lẻ được đánh dấu đúng một lần tại vị trí bên phải. Chỉ giữ các vị trí $L+1$ đến $R$ là đủ để cả hai đầu của mỗi cặp nằm trong đoạn.

Thời gian $O(N+Q)$, bộ nhớ $O(N)$.

Các bộ đếm không vượt quá $N$.
