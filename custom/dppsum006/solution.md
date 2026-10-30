# PREFIX006 — Hướng dẫn giải

Sàng Eratosthenes tới $10^6$. Đánh dấu $0,1$ không nguyên tố; lần lượt gạch các bội của mỗi số nguyên tố, bắt đầu từ bình phương của nó. Những số còn lại đúng là các số nguyên tố.

Đặt $B_i=1$ nếu $A_i$ thỏa điều kiện, ngược lại đặt $B_i=0$. Tính $P_0=0$, $P_i=P_{i-1}+B_i$. Mỗi truy vấn trả về $P_R-P_{L-1}$.

Tính đúng đắn: mỗi vị trí thỏa điều kiện đóng góp đúng một đơn vị. Hiệu hai tổng tiền tố loại các vị trí trước $L$ và giữ đúng các vị trí từ $L$ đến $R$, nên bằng số lượng cần tìm.

Thời gian $O(M\log\log M+N+Q)$, bộ nhớ $O(M+N)$, với $M=10^6$.
