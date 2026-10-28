# SEGTREE103 — Lời giải

### Ý tưởng

Nút lưu tần suất lớn nhất trong miền giá trị của nó. Sau mỗi thêm hoặc xóa, cập nhật tần suất ở lá tương ứng. Nếu cực đại ở gốc bằng 0 thì đa tập rỗng. Ngược lại, đi xuống con trái nếu cực đại con trái bằng cực đại hiện tại; nếu không thì đi xuống con phải.

### Chứng minh tính đúng đắn

Cực đại ở gốc chính là tần suất lớn nhất. Tại mỗi nút chứa giá trị đạt cực đại, chọn con trái khi có ứng viên sẽ giữ lại giá trị nhỏ nhất trong số các ứng viên; nếu không có thì mọi ứng viên đều nằm bên phải. Quy nạp đến lá cho giá trị cần tìm.

### Độ phức tạp

$O(M+Q\log M)$ thời gian và $O(M)$ bộ nhớ.
