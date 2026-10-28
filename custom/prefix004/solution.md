# PREFIX004 — Hướng dẫn giải

Kiểm tra đồng thời $U\le A_i$ và $A_i\le V$; cả hai đầu mút đều được tính.

Đặt $B_i=1$ nếu $A_i$ thỏa điều kiện, ngược lại đặt $B_i=0$. Tính $P_0=0$, $P_i=P_{i-1}+B_i$. Mỗi truy vấn trả về $P_R-P_{L-1}$.

Tính đúng đắn: mỗi vị trí thỏa điều kiện đóng góp đúng một đơn vị. Hiệu hai tổng tiền tố loại các vị trí trước $L$ và giữ đúng các vị trí từ $L$ đến $R$, nên bằng số lượng cần tìm.

Thời gian $O(N+Q)$, bộ nhớ $O(N)$.
