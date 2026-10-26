# SEGTREE181 — Lời giải

### Ý tưởng

Mỗi nút lưu tổng kinh phí và tổng dấu hiệu. Duy trì hai tổng đã nhận kể từ $l$. Nếu nhận cả một nút mà vẫn có ít nhất một ngưỡng chưa đạt, nhận nút rồi tiếp tục. Nếu nhận nút sẽ đạt cả hai ngưỡng, đi xuống để tìm lá đầu tiên làm cả hai điều kiện đúng. Dùng số nguyên 64 bit cho kinh phí.

### Chứng minh tính đúng đắn

Cả hai tổng đều không giảm khi kéo dài đoạn. Khi toàn bộ nút vẫn chưa đạt ít nhất một ngưỡng, không tiền tố nào của nút có thể đạt cả hai. Vì vậy bỏ qua nút là an toàn. Đi xuống nút đầu tiên làm cả hai điều kiện đúng, ưu tiên trái, cho điểm kết thúc nhỏ nhất.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
