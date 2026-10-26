# SEGTREE172 — Lời giải

### Ý tưởng

Lưu OR trên mỗi nút. Duy trì OR $t$ của các phần đã đi qua, ban đầu bằng $0$. Duyệt từ $l$ sang phải. Nếu ghép toàn bộ nút vẫn chưa đủ các bit của $M$, nhận nút và cập nhật $t$. Nếu đủ, đi xuống nút đó, ưu tiên con trái, để tìm vị trí đầu tiên đạt yêu cầu.

### Chứng minh tính đúng đắn

OR chỉ có thể thêm bit khi kéo dài đoạn. Nếu ghép toàn bộ một nút còn thiếu bit thì mọi tiền tố bên trong nút đó cũng thiếu, nên có thể bỏ qua cả nút. Nút đầu tiên làm đủ bit chứa đáp án; tiếp tục cùng lập luận đến lá sẽ tìm được điểm kết thúc nhỏ nhất.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
