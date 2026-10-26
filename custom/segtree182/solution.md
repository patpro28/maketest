# SEGTREE182 — Lời giải

### Ý tưởng

Nút lưu tổng và GCD. Tích lũy hai đại lượng của phần đã đi qua, ban đầu tổng bằng 0 và GCD bằng 0. Nếu nhận toàn bộ nút mà vẫn thiếu tổng hoặc GCD còn lớn hơn G, nhận nút rồi tiếp tục. Nếu cả hai điều kiện đúng, đi xuống nút để tìm lá đầu tiên làm chúng cùng đúng. Dùng số nguyên 64 bit cho tổng.

### Chứng minh tính đúng đắn

Trên các đoạn không rỗng bắt đầu tại l, tổng tăng còn GCD không tăng khi mở rộng. Vì vậy một khi cả hai điều kiện đúng thì mọi phần mở rộng cũng đúng. Nếu nhận cả nút vẫn chưa đạt một điều kiện, không tiền tố nào trong nút có thể đạt cả hai. Tìm trong nút đầu tiên đạt cả hai, ưu tiên trái, cho điểm kết thúc nhỏ nhất.

### Độ phức tạp

$O(N\log V+Q\log N\log V)$ thời gian theo chặn trên của phép tính GCD, $V=10^9$; $O(N)$ bộ nhớ.
