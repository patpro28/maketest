# SEGTREE151 — Lời giải

### Ý tưởng

Mỗi nút lưu giá nhỏ nhất. Với truy vấn từ $p$, tìm từ trái sang phải trong $[p+1,N]$. Bỏ qua nút nằm trước đoạn tìm kiếm hoặc có minimum không nhỏ hơn $a_p$. Cập nhật điểm khi giá thay đổi.

### Chứng minh tính đúng đắn

Nút có minimum không nhỏ hơn $a_p$ không chứa giá giảm nghiêm ngặt. Những nút còn lại có thể chứa đáp án; ưu tiên con trái và chỉ xét phần sau $p$ sẽ tìm đúng vị trí hợp lệ nhỏ nhất.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
