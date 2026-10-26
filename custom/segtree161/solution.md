# SEGTREE161 — Lời giải

### Ý tưởng

Lưu $[a_i\bmod D=0]$ ở lá và tổng trên mỗi nút. Với truy vấn, tính số bội $C$ trong $[l,r]$ và số bội $P$ trước $l$. Nếu $C<k$, trả về $-1$. Ngược lại, đi xuống cây tìm bội thứ $P+k$ của toàn dãy theo tổng ở con trái.

### Chứng minh tính đúng đắn

Có đúng $P$ bội đứng trước $l$. Vì $[l,r]$ có ít nhất $k$ bội, bội thứ $P+k$ của toàn dãy nằm trong đoạn này và chính là bội thứ $k$ cần tìm. Cập nhật dấu hiệu chia hết bảo đảm số đếm luôn đúng.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
