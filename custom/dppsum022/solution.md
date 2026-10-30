# PREFIX022 — Hướng dẫn giải

Tính $P_i$ là tổng các số dương và $M_i$ là tổng các số âm trong $i$ vị trí đầu. Số $0$ không làm thay đổi mảng nào. Truy vấn trả về $P_R-P_{L-1}$ và $M_R-M_{L-1}$.

Tính đúng đắn: Mỗi phần tử dương chỉ đóng góp vào $P$, mỗi phần tử âm chỉ đóng góp vào $M$. Hiệu hai tiền tố của từng nhóm là đúng tổng của nhóm đó trong đoạn, bao gồm cả dấu âm.

Thời gian $O(N+Q)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho các tổng. Trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$.
