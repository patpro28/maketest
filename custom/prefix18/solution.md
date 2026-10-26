# PREFIX18 — Hướng dẫn giải

Tính $B_i=B_{i-1}+A_i$ với $B_0=0$, rồi tính $P_i=P_{i-1}+B_i$ với $P_0=0$. Mỗi truy vấn trả về $P_R-P_{L-1}$.

Tính đúng đắn: Lượt cộng dồn đầu tính đúng số dư cuối từng ngày từ ngày 1. Lượt cộng dồn thứ hai cho phép lấy tổng các số dư trong đoạn bằng hiệu hai tiền tố.

Thời gian: $O(N+Q)$. Bộ nhớ: $O(N)$.

Dùng số nguyên 64 bit cho tổng và số cách. Với giới hạn $A_i\le10^6$, tổng có trọng số hoặc tổng số dư không vượt $10^6N(N+1)/2\le20000100000000000$, nằm trong miền số nguyên 64 bit có dấu.
