# PREFIX05 — Hướng dẫn giải

Tổng đoạn $[l,r]$ là $S_r-S_{l-1}$. Với mỗi $r$, chọn tổng tiền tố nhỏ nhất trong $S_0,\ldots,S_{r-1}$. Cập nhật đáp án trước khi đưa $S_r$ vào min để loại đoạn rỗng. Khởi tạo đáp án bằng âm vô cùng để xử lý dãy toàn âm.

Tính đúng đắn: Mỗi đoạn không rỗng có một đầu phải và một tiền tố đứng trước nó. Chọn tiền tố nhỏ nhất cho từng đầu phải rồi lấy max xét đủ mọi đoạn.

Độ phức tạp thời gian: $O(N)$. Bộ nhớ: $O(1)$ (tính cả dữ liệu và danh sách kết quả nếu có).

Dùng số nguyên 64 bit cho tổng, năng lượng và số đoạn; tổng có thể đạt $2\cdot10^{14}$ và số đoạn có thể đạt $N(N+1)/2$.
