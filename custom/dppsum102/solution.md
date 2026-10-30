# PREFIX02 — Hướng dẫn giải

Tính tổng toàn dãy $T$. Khi xét vị trí $i$, gọi $L$ là tổng các phần tử trước đó. Tổng bên phải là $T-L-A_i$. Ghi nhận $i$ nếu hai tổng bằng nhau, rồi cộng $A_i$ vào $L$.

Tính đúng đắn: Mỗi vị trí được kiểm tra bằng chính hai tổng trong định nghĩa, nên danh sách thu được chứa đúng mọi điểm cân bằng.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ: $O(N)$ (tính cả dữ liệu và danh sách kết quả nếu có).

Dùng số nguyên 64 bit cho tổng, năng lượng và số đoạn; tổng có thể đạt $2\cdot10^{14}$ và số đoạn có thể đạt $N(N+1)/2$.
