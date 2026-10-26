# SEGTREE174 — Lời giải

### Ý tưởng

Lá lưu mặt nạ 26 bit với bit của ký tự tại vị trí đó bật. Nút lưu OR các mặt nạ. Tích lũy mặt nạ từ l sang phải, nhận toàn bộ một nút nếu số bit bật sau ghép không vượt K. Nếu vượt, đi xuống tìm ký tự đầu tiên làm số loại vượt K rồi trả về vị trí trước nó.

### Chứng minh tính đúng đắn

OR biểu diễn chính xác tập ký tự xuất hiện. Khi kéo dài đoạn, tập này chỉ mở rộng nên số loại không giảm. Vì vậy có thể nhận cả nút hợp lệ và dừng tại lần vượt đầu tiên; vị trí ngay trước đó là điểm kết thúc lớn nhất.

### Độ phức tạp

$O(N+Q\log N)$ thời gian khi đếm bit trong một từ máy; $O(N)$ bộ nhớ.
