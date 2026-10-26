# SEGTREE102 — Lời giải

### Ý tưởng

Lưu OR của đoạn trên mỗi nút. Với mặt nạ $M$, bỏ qua nút nếu OR của nút AND với $M$ bằng $0$. Nếu không, đi xuống con trái trước để tìm lá tương thích đầu tiên. Cập nhật điểm khi thay đổi mặt nạ.

### Chứng minh tính đúng đắn

OR của đoạn có một bit bật đúng khi ít nhất một phần tử trong đoạn bật bit đó. Vì vậy điều kiện bỏ qua tương đương không có phần tử tương thích. Ưu tiên con trái trong các nhánh còn ứng viên cho chỉ số nhỏ nhất.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
