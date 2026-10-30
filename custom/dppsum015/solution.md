# PREFIX015 — Hướng dẫn giải

Kiểm tra đồng thời $U\le A_i$ và $A_i\le V$; cả hai đầu mút đều được tính.

Đặt $B_i=A_i$ nếu phần tử $A_i$ thỏa điều kiện, ngược lại đặt $B_i=0$. Tính $P_0=0$, $P_i=P_{i-1}+B_i$. Mỗi truy vấn trả về $P_R-P_{L-1}$.

Tính đúng đắn: mỗi vị trí thỏa điều kiện đóng góp chính giá trị của nó, vị trí còn lại đóng góp $0$. Hiệu hai tổng tiền tố loại các vị trí trước $L$ và giữ đúng các vị trí từ $L$ đến $R$, nên bằng tổng cần tìm.

Thời gian $O(N+Q)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho mảng tổng tiền tố và kết quả. Trị tuyệt đối của tổng không vượt $N\cdot10^9\le2\cdot10^{14}$. Nếu tổng âm, in đúng giá trị âm đó.
