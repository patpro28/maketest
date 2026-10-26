# SEGTREE191 — Lời giải

### Ý tưởng

Lá của mỗi người lưu $1$ nếu còn ngồi, ngược lại lưu $0$; nút lưu tổng. Gọi $m$ là số người còn lại và $s$ là thứ hạng bắt đầu, đánh số từ $0$ trong danh sách người còn lại theo số tăng. Thứ hạng bị loại là $t=(s+(k-1)\bmod m)\bmod m$. Đi xuống cây tìm người thứ $t+1$, rồi cập nhật lá về $0$. Nếu còn người, đặt $s=t\bmod(m-1)$.

### Chứng minh tính đúng đắn

Đếm vòng tròn từ thứ hạng $s$ dịch thêm đúng $k-1$ bước, nên công thức modulo cho đúng thứ hạng bị loại. Tìm theo tổng con trái cho đúng người tại thứ hạng đó. Sau khi xóa, người kế tiếp có thứ hạng $t$ trong danh sách mới, hoặc thứ hạng $0$ nếu vừa xóa người cuối danh sách. Do đó vị trí bắt đầu được duy trì chính xác qua mọi lượt.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
