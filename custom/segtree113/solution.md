# SEGTREE113 — Lời giải

### Ý tưởng

Đặt dấu hiệu tại mỗi lá bằng 1 nếu vị trí đó là đỉnh, ngược lại bằng 0; hai đầu luôn bằng 0. Nút lưu tổng dấu hiệu. Khi thay đổi a_i, chỉ tính lại các dấu hiệu i−1, i, i+1 nằm trong dãy. Tìm lá có dấu hiệu 1 đầu tiên bằng cách ưu tiên con trái có tổng dương.

### Chứng minh tính đúng đắn

Một dấu hiệu chỉ phụ thuộc độ cao tại vị trí đó và hai hàng xóm. Vì vậy ba vị trí được xét là toàn bộ các dấu hiệu có thể thay đổi. Tổng dương chính xác khi nút chứa đỉnh; ưu tiên nhánh trái chứa đỉnh cho chỉ số nhỏ nhất.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
