# PREFIX007 — Hướng dẫn giải

Đảo chữ số rồi so với số ban đầu. Dùng số nguyên 64 bit cho số đảo vì số đảo của một giá trị không vượt $10^9$ có thể lớn hơn miền số nguyên 32 bit. Số $0$ vẫn được nhận đúng.

Đặt $B_i=1$ nếu $A_i$ thỏa điều kiện, ngược lại đặt $B_i=0$. Tính $P_0=0$, $P_i=P_{i-1}+B_i$. Mỗi truy vấn trả về $P_R-P_{L-1}$.

Tính đúng đắn: mỗi vị trí thỏa điều kiện đóng góp đúng một đơn vị. Hiệu hai tổng tiền tố loại các vị trí trước $L$ và giữ đúng các vị trí từ $L$ đến $R$, nên bằng số lượng cần tìm.

Thời gian $O(N\log A_{\max}+Q)$, bộ nhớ $O(N)$; mỗi phần tử có nhiều nhất $10$ chữ số.
