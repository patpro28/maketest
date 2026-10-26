# SEGTREE101 — Lời giải

### Ý tưởng

Mỗi lá ứng với một giá trị $x$, lưu $[c_x=0]$. Mỗi nút lưu tổng số giá trị bị thiếu. Sau khi thay đổi tần suất, cập nhật lá tương ứng. Nếu tổng ở gốc bằng $0$, trả về $N+1$. Ngược lại, đi sang con trái nếu con trái còn giá trị bị thiếu, và sang con phải trong trường hợp còn lại.

### Chứng minh tính đúng đắn

Tổng bằng $0$ chính xác khi mọi giá trị trong đoạn đều có mặt. Khi còn giá trị thiếu, chọn con trái có tổng dương luôn giữ lại giá trị thiếu nhỏ nhất; nếu con trái có tổng $0$ thì đáp án buộc nằm bên phải. Vì vậy lá tìm được chính là MEX.

### Độ phức tạp

$O(N+Q\log(N+1))$ thời gian và $O(N)$ bộ nhớ.
