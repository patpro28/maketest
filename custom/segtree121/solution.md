# SEGTREE121 — Lời giải

### Ý tưởng

Mỗi lá lưu tồn kho ở một mức giá, mỗi nút lưu tổng tồn kho. Nếu tổng ở gốc nhỏ hơn $k$, trả về $-1$ và không cập nhật. Ngược lại, nếu con trái có ít nhất $k$ món thì đi trái; nếu không, trừ số món bên trái khỏi $k$ và đi phải. Tại lá, giảm tồn kho một đơn vị. Dùng số nguyên 64 bit cho tổng và thứ hạng.

### Chứng minh tính đúng đắn

Tất cả món ở con trái có giá thấp hơn mọi món ở con phải. Vì vậy món thứ $k$ hoặc nằm bên trái, hoặc có thứ hạng $k$ trừ tổng bên trái trong con phải. Suy luận này duy trì tới lá, cho đúng mức giá cần bán. Chỉ cập nhật sau khi kiểm tra đủ hàng nên lần bán thất bại không làm thay đổi dữ liệu.

### Độ phức tạp

$O(M+Q\log M)$ thời gian và $O(M)$ bộ nhớ.
