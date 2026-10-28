# SEGTREE124 — Lời giải

### Ý tưởng

Quản lý tần suất thật ở ngoài cây. Lá lưu 1 nếu tần suất dương, ngược lại lưu 0; nút lưu tổng số giá trị hiện diện. Cập nhật lá khi thêm hoặc xóa. Nếu tổng ở gốc nhỏ hơn k thì thất bại, nếu không đi xuống theo số giá trị hiện diện trong con trái.

### Chứng minh tính đúng đắn

Dấu hiệu ở lá biểu diễn đúng việc một giá trị có xuất hiện, độc lập với số lần lặp. Do đó tổng trên nút là số giá trị phân biệt trong miền của nút. Đi xuống theo tổng con trái cho đúng giá trị phân biệt thứ k; thay đổi tần suất chưa qua 0 không làm mất hay thêm giá trị trong thứ tự này.

### Độ phức tạp

$O(M+Q\log M)$ thời gian và $O(M)$ bộ nhớ.
