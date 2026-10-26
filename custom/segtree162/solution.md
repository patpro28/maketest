# SEGTREE162 — Lời giải

### Ý tưởng

Lưu GCD trên mỗi nút. Bỏ qua nút ngoài đoạn truy vấn hoặc có GCD chia hết cho D. Với nút còn lại, tìm con trái trước rồi con phải; cập nhật GCD trên đường đi khi thay đổi một phần tử.

### Chứng minh tính đúng đắn

GCD chia hết cho D tương đương mọi phần tử trong đoạn đều chia hết cho D: một chiều do mỗi phần tử là bội của GCD, chiều còn lại do D là ước chung. Vì thế các nút bị bỏ qua không chứa đáp án. Duyệt từ trái sang phải cho vị trí vi phạm nhỏ nhất.

### Độ phức tạp

$O(N\log V+Q\log N\log V)$ thời gian theo chặn trên của phép tính GCD, $V=10^9$; $O(N)$ bộ nhớ.
