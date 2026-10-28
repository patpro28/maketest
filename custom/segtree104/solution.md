# SEGTREE104 — Lời giải

### Ý tưởng

Lưu AND của các mặt nạ trên mỗi nút. Với yêu cầu M, bỏ qua nút nếu AND của nút chứa đủ mọi bit của M. Nếu không, tìm trong con trái trước, rồi con phải. Cập nhật điểm khi thay đổi mặt nạ.

### Chứng minh tính đúng đắn

AND của một đoạn chứa một bit đúng khi mọi phần tử của đoạn đều chứa bit đó. Do đó điều kiện bỏ qua tương đương mọi thiết bị trong đoạn đủ yêu cầu. Trong các nút chưa bỏ qua, đi trái trước cho vị trí thiếu tính năng nhỏ nhất.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
