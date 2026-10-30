# PREFIX026 — Hướng dẫn giải

Đặt $B_1=0$. Với $i\ge2$, đặt $B_i=1$ nếu $A_{i-1}=A_i$, ngược lại bằng $0$. Tính tổng tiền tố $P$ của $B$. Truy vấn trả về $P_R-P_L$.

Tính đúng đắn: Một cặp nằm hoàn toàn trong đoạn khi chỉ số bên phải của cặp nằm từ $L+1$ đến $R$. Hiệu $P_R-P_L$ lấy đúng các chỉ số đó. Các cặp chung vị trí được tính riêng theo chỉ số bên phải.

Thời gian $O(N+Q)$, bộ nhớ $O(N)$.

Các bộ đếm không vượt quá $N$.
