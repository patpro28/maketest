# PREFIX009 — Hướng dẫn giải

Tách các chữ số; trả về đúng ngay khi gặp chữ số $7$. Kết quả kiểm tra chỉ là một giá trị đúng/sai nên phần tử chứa nhiều chữ số $7$ vẫn chỉ đóng góp $1$.

Đặt $B_i=1$ nếu $A_i$ thỏa điều kiện, ngược lại đặt $B_i=0$. Tính $P_0=0$, $P_i=P_{i-1}+B_i$. Mỗi truy vấn trả về $P_R-P_{L-1}$.

Tính đúng đắn: mỗi vị trí thỏa điều kiện đóng góp đúng một đơn vị. Hiệu hai tổng tiền tố loại các vị trí trước $L$ và giữ đúng các vị trí từ $L$ đến $R$, nên bằng số lượng cần tìm.

Thời gian $O(N\log A_{\max}+Q)$, bộ nhớ $O(N)$; mỗi phần tử có nhiều nhất $10$ chữ số.
