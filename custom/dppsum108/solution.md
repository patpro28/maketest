# PREFIX08 — Hướng dẫn giải

Đoạn $[l,r]$ có tổng chia hết cho $M$ khi và chỉ khi hai tổng tiền tố $S_{l-1},S_r$ có cùng phần dư. Khởi tạo tần suất phần dư $0$ bằng $1$ cho tiền tố rỗng. Mỗi phần tử mới: chuẩn hóa phần dư về $[0,M-1]$, cộng tần suất hiện có vào đáp án rồi tăng tần suất. Dùng công thức $((x\bmod M)+M)\bmod M$ khi có số âm.

Tính đúng đắn: Hai tiền tố cùng phần dư có hiệu chia hết cho M. Tại mỗi đầu phải, tần suất đếm đúng mọi đầu trái đứng trước, nên mỗi đoạn hợp lệ được đếm đúng một lần.

Độ phức tạp thời gian: $O(N+M)$. Bộ nhớ: $O(M)$ (tính cả dữ liệu và danh sách kết quả nếu có).

Dùng số nguyên 64 bit cho tổng, năng lượng và số đoạn; tổng có thể đạt $2\cdot10^{14}$ và số đoạn có thể đạt $N(N+1)/2$.
