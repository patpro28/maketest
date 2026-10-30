# PREFIX021 — Hướng dẫn giải

Tính hai mảng tổng tiền tố: $E_i$ là tổng các phần tử chẵn trong $i$ vị trí đầu, $O_i$ là tổng các phần tử lẻ. Khởi tạo $E_0=O_0=0$. Mỗi vị trí chỉ cộng vào mảng tương ứng. Truy vấn trả về $E_R-E_{L-1}$ và $O_R-O_{L-1}$.

Tính đúng đắn: Mỗi mảng chỉ chứa đóng góp của đúng nhóm cần tính. Lấy hiệu hai tiền tố loại các vị trí trước $L$ và giữ đúng các vị trí trong đoạn. Kiểm tra số lẻ bằng phần dư khác $0$ để xử lý đúng số âm.

Thời gian $O(N+Q)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho các tổng. Trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$.
