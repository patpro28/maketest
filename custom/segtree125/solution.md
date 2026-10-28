# SEGTREE125 — Lời giải

### Ý tưởng

Lá lưu số lần lặp của khối, nút lưu tổng độ dài bằng số nguyên 64 bit. Ký tự của từng khối được lưu riêng. Nếu tổng ở gốc nhỏ hơn k, trả về −1. Ngược lại đi xuống: nếu tổng con trái đủ k thì đi trái, nếu không trừ tổng con trái khỏi k rồi đi phải. Khi tới lá, k còn lại chính là thứ tự trong khối. Thao tác loại 1 cập nhật ký tự và độ dài tại một vị trí.

### Chứng minh tính đúng đắn

Các khối bên trái đứng trước mọi khối bên phải trong văn bản. Trừ tổng độ dài bên trái khi đi phải bảo toàn thứ hạng tương đối của ký tự đang tìm. Vì thế lá tìm được là đúng khối và thứ hạng còn lại là đúng vị trí trong khối. Các khối rỗng có tổng bằng 0 nên được bỏ qua tự nhiên; giữ ký tự riêng theo chỉ số xử lý đúng cả các khối kề nhau cùng ký tự.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ; không giải nén văn bản.
