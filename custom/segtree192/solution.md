# SEGTREE192 — Lời giải

### Ý tưởng

Nút lưu số chỗ trống. Với xe đến từ p, tìm chỗ trống đầu tiên trong [p,N]; nếu không có thì tìm trong [1,p−1]. Mỗi lần tìm bỏ qua nút ngoài đoạn hoặc có số chỗ trống bằng 0. Đánh dấu chỗ tìm được có xe bằng cập nhật điểm; thao tác trả chỗ gán lá về trạng thái trống.

### Chứng minh tính đúng đắn

Thứ tự tìm kiếm của xe là hai đoạn chỉ số tăng liên tiếp đã nêu. Vị trí trống đầu tiên trong đoạn thứ nhất luôn được ưu tiên hơn mọi vị trí trong đoạn thứ hai. Tìm từ trái sang phải trong từng đoạn rồi cập nhật đúng lá mô phỏng chính xác từng thao tác, kể cả thất bại và trả chỗ đã trống.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
