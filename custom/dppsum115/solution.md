# PREFIX15 — Hướng dẫn giải

Nhân đôi dãy: $C_i=A_{((i-1)\bmod N)+1}$ với $1\le i\le2N$. Tính tổng tiền tố $P$ của $C$. Truy vấn $(L,K)$ trả về $P_{L+K-1}-P_{L-1}$.

Tính đúng đắn: Khi đi qua cuối dãy ban đầu, các phần tử tiếp theo chính là bản sao thứ hai. Do K không vượt N, đoạn cần xét luôn nằm trong dãy đã nhân đôi và biểu diễn đúng hành trình.

Thời gian: $O(N+Q)$. Bộ nhớ: $O(N)$.

Dùng số nguyên 64 bit cho tổng và số cách.
