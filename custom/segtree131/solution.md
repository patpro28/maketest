# SEGTREE131 — Lời giải

### Ý tưởng

Lưu tổng dân số trên mỗi nút. Với truy vấn, lấy tổng $W$ trong $[l,r]$ và tổng $P$ trong $[1,l-1]$. Nếu $W=0$, trả về $l$. Ngược lại, tìm tiền tố toàn dãy đầu tiên có tổng ít nhất $P+\lceil W/2\rceil$ bằng cách đi xuống cây theo tổng con trái.

### Chứng minh tính đúng đắn

Vì dân số không âm, tổng tiền tố không giảm. Đích lớn hơn $P$ nên vị trí tìm được không nằm trước $l$, và tổng đến $r$ đủ đạt đích nên vị trí không vượt $r$. Điều kiện đạt đích tương đương tổng từ $l$ đạt ít nhất một nửa $W$; tìm tiền tố đầu tiên cho vị trí nhỏ nhất.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
