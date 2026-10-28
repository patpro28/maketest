# SEGTREE114 — Lời giải

### Ý tưởng

Lá i lưu [s_i khác t_i], nút lưu tổng số vị trí khác nhau. Sau cập nhật một ký tự, tính lại đúng lá đó. Nếu tổng ở gốc bằng 0, trả về N; nếu không, đi xuống nhánh trái có tổng dương để tìm vị trí khác nhau đầu tiên p, rồi trả về p−1.

### Chứng minh tính đúng đắn

Các ký tự trước vị trí khác nhau đầu tiên đều bằng nhau, còn tiền tố chứa vị trí đó không thể chung. Vì vậy độ dài cần tìm bằng p−1. Tổng dấu hiệu và việc cập nhật đúng vị trí duy trì chính xác tập vị trí khác nhau; đi xuống trái trước tìm được p nhỏ nhất.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
