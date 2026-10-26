# SEGTREE193 — Lời giải

### Ý tưởng

Xây cây trên miền sức chứa từ 0 đến C. Lá lưu số hộp tại mức sức chứa đó, nút lưu tổng số hộp. Tìm lá có số đếm dương đầu tiên trong [w,C]. Khi tìm được mức c, giảm đếm tại c và tăng đếm tại c−w; thêm hộp là tăng đếm tại một lá.

### Chứng minh tính đúng đắn

Tìm lá dương đầu tiên trong miền [w,C] chính xác là chọn mức sức chứa nhỏ nhất đủ chứa món. Hai cập nhật chuyển đúng một hộp từ mức c sang c−w và bảo toàn tổng số hộp. Vì các hộp cùng mức là tương đương, biểu diễn bằng tần suất đủ mô phỏng mọi thao tác.

### Độ phức tạp

$O(C+N+Q\log(C+1))$ thời gian và $O(C)$ bộ nhớ.
