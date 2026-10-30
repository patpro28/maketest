# PREFIX14 — Hướng dẫn giải

Tính $P_{i,j}=A_{i,j}+P_{i-1,j}+P_{i,j-1}-P_{i-1,j-1}$, hàng $0$ và cột $0$ bằng $0$. Đáp án là $P_{X_2,Y_2}-P_{X_1-1,Y_2}-P_{X_2,Y_1-1}+P_{X_1-1,Y_1-1}$.

Tính đúng đắn: Từ hình chữ nhật tiền tố lớn, loại các hàng nằm phía trên và cột nằm bên trái. Phần góc trên trái bị trừ hai lần nên cần cộng lại một lần.

Thời gian: $O(NM+Q)$. Bộ nhớ: $O(NM)$.

Dùng số nguyên 64 bit cho tổng và số cách.
