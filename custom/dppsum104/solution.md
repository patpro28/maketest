# PREFIX04 — Hướng dẫn giải

Gọi $S_i$ là tổng thay đổi năng lượng qua $i$ trạm, $S_0=0$. Với năng lượng ban đầu $E$, sau trạm $i$ còn $E+S_i$. Mọi điều kiện tương đương $E\ge-\min_{0\le i\le N}S_i$. Vì có $S_0=0$, đáp án chính là $-\min S_i$.

Tính đúng đắn: Năng lượng ban đầu nhỏ hơn đáp án sẽ âm tại một tiền tố đạt min; năng lượng bằng đáp án khiến mọi tiền tố đều không âm.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ: $O(1)$ (tính cả dữ liệu và danh sách kết quả nếu có).

Dùng số nguyên 64 bit cho tổng, năng lượng và số đoạn; tổng có thể đạt $2\cdot10^{14}$ và số đoạn có thể đạt $N(N+1)/2$.
