# PREFIX023 — Hướng dẫn giải

Tính $C_i$ là số phần tử chia hết cho $K$ trong $i$ vị trí đầu và $S_i$ là tổng của chúng. Nếu $A_i\bmod K=0$, tăng $C$ thêm $1$ và $S$ thêm $A_i$. Truy vấn trả về $C_R-C_{L-1}$ và $S_R-S_{L-1}$.

Tính đúng đắn: Mỗi phần tử được chọn đóng góp $1$ vào số lượng và chính giá trị của nó vào tổng. Trừ tiền tố trước $L$ giữ đúng hai đại lượng trên đoạn. Số $0$ tăng số lượng nhưng không tăng tổng.

Thời gian $O(N+Q)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho các tổng. Trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$.
