# PREFIX06 — Hướng dẫn giải

Tính $R_i=\min(A_i,\ldots,A_N)$ bằng một lượt duyệt ngược. Duyệt vị trí chia $i$ từ $1$ đến $N-1$, duy trì $L_i=\max(A_1,\ldots,A_i)$. Cách chia hợp lệ khi và chỉ khi $L_i\le R_{i+1}$.

Tính đúng đắn: Nếu max bên trái không vượt min bên phải thì mọi cặp thành viên thỏa điều kiện. Ngược lại, nếu bất đẳng thức sai thì cặp đạt max và min vi phạm điều kiện.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ: $O(N)$ (tính cả dữ liệu và danh sách kết quả nếu có).

Dùng số nguyên 64 bit cho tổng, năng lượng và số đoạn; tổng có thể đạt $2\cdot10^{14}$ và số đoạn có thể đạt $N(N+1)/2$.
