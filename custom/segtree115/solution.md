# SEGTREE115 — Lời giải

### Ý tưởng

Nút chỉ lưu điểm lớn nhất trong đoạn. Lấy điểm lớn nhất từ gốc. Để tìm vị trí đầu, đi trái nếu maximum con trái bằng maximum hiện tại, nếu không đi phải. Để tìm vị trí cuối, làm tương tự nhưng ưu tiên con phải.

### Chứng minh tính đúng đắn

Mỗi nút được đi vào chứa ít nhất một vị trí đạt cực đại của toàn dãy. Chọn con trái có cực đại đó bảo đảm lấy vị trí nhỏ nhất; đối xứng, ưu tiên con phải lấy vị trí lớn nhất. Cập nhật maximum sau mỗi thay đổi duy trì đúng thông tin.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
