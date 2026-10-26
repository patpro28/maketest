# PREFIX13 — Hướng dẫn giải

Tính $P_i=\sum_{j=1}^i A_j$ và $W_i=\sum_{j=1}^i jA_j$. Đáp án là $(W_R-W_{L-1})-(L-1)(P_R-P_{L-1})$.

Tính đúng đắn: Với mỗi vị trí i trong đoạn, hệ số còn lại là i-(L-1)=i-L+1, đúng bằng trọng số yêu cầu.

Thời gian: $O(N+Q)$. Bộ nhớ: $O(N)$.

Dùng số nguyên 64 bit cho tổng và số cách. Với giới hạn $A_i\le10^6$, tổng có trọng số hoặc tổng số dư không vượt $10^6N(N+1)/2\le20000100000000000$, nằm trong miền số nguyên 64 bit có dấu.
