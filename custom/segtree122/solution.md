# SEGTREE122 — Lời giải

### Ý tưởng

Ban đầu các giá trị $1,\ldots,N$ đều chưa được dùng, mỗi lá lưu $1$. Xử lý $i$ từ $N$ về $1$. Trong $i$ giá trị còn lại, chọn giá trị nhỏ thứ $i-e_i$ bằng cách đi xuống cây theo tổng con trái; đặt giá trị đó vào $a_i$ rồi cập nhật lá thành $0$.

### Chứng minh tính đúng đắn

Khi xử lý vị trí $i$, các giá trị còn lại chính là các giá trị sẽ nằm tại vị trí $1$ đến $i$. Cần có đúng $e_i$ giá trị lớn hơn $a_i$ trong số này, nên thứ hạng tăng dần của $a_i$ phải là $i-e_i$. Lựa chọn đó duy nhất và bảo toàn tính chất cho bước tiếp theo. Quy nạp cho hoán vị duy nhất thỏa mọi số nghịch thế.

### Độ phức tạp

$O(N\log N)$ thời gian và $O(N)$ bộ nhớ.
