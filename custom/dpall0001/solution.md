## Ý tưởng

Gọi $D_s$ là giá trị lớn nhất khi chọn trong các món đã xét với tổng khối lượng đúng $s$. Ban đầu chỉ $D_0=0$ đạt được. Có thể dùng $-1$ để đánh dấu các trạng thái chưa đạt vì mọi giá trị món đều không âm.

Với món có khối lượng $w$ và giá trị $v$, duyệt $s$ từ $W$ giảm đến $w$. Nếu $D_{s-w}$ đạt được, cập nhật $D_s\gets\max(D_s,D_{s-w}+v)$.

## Chứng minh tính đúng đắn

Một cách đạt khối lượng $s$ sau khi xét món mới hoặc bỏ món này và giữ giá trị cũ, hoặc lấy nó và ghép vào một cách đạt khối lượng $s-w$ từ các món trước. Vì $w>0$ và duyệt giảm dần, $D_{s-w}$ vẫn thuộc lớp trước nên mỗi món được dùng tối đa một lần. Quy nạp theo số món đã xét cho thấy $D_W$ là kết quả cần in.

## Độ phức tạp

Thời gian $O(N(W+1))$, bộ nhớ $O(W+1)$. Dùng số nguyên 64 bit để lưu giá trị.
