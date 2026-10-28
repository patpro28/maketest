# PREFIX005 — Hướng dẫn giải

Loại số âm. Với số không âm, lấy căn bậc hai gần đúng rồi điều chỉnh bằng phép nhân số nguyên trước khi kiểm tra bình phương bằng số ban đầu. Dùng số nguyên 64 bit cho phép nhân để tránh tràn.

Đặt $B_i=1$ nếu $A_i$ thỏa điều kiện, ngược lại đặt $B_i=0$. Tính $P_0=0$, $P_i=P_{i-1}+B_i$. Mỗi truy vấn trả về $P_R-P_{L-1}$.

Tính đúng đắn: mỗi vị trí thỏa điều kiện đóng góp đúng một đơn vị. Hiệu hai tổng tiền tố loại các vị trí trước $L$ và giữ đúng các vị trí từ $L$ đến $R$, nên bằng số lượng cần tìm.

Thời gian $O(N+Q)$, bộ nhớ $O(N)$; việc điều chỉnh căn bậc hai của các giá trị trong giới hạn chỉ cần số bước hằng số.
