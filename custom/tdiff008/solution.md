## Ý tưởng

Với mỗi câu hỏi, lấy $D_P$ từ mảng hiệu ban đầu. Nếu $P=L$, cộng thêm $X$. Nếu $P=R+1$, trừ đi $X$. In kết quả và giữ mảng hiệu ban đầu để dùng cho các câu hỏi sau.

## Chứng minh tính đúng đắn

Giá trị tại vị trí $P$ trong mảng hiệu là $A_P-A_{P-1}$ với $A_0=0$. Lượng cộng vào hai phần tử triệt tiêu khi cả hai cùng thuộc đoạn. Nếu chỉ $A_P$ thuộc đoạn thì $P=L$ và hiệu tăng $X$. Nếu chỉ $A_{P-1}$ thuộc đoạn thì $P=R+1$ và hiệu giảm $X$. Mọi trường hợp khác giữ nguyên hiệu. Vì mỗi câu hỏi lấy $D_P$ ban đầu, các phép cộng giả định độc lập.

## Độ phức tạp

Mỗi bộ test cần thời gian $O(N+Q)$ và bộ nhớ phụ $O(N)$.

## Lưu ý cài đặt

Vì $P\le N$, trường hợp $R=N$ sẽ không bao giờ khớp điều kiện $P=R+1$. Dùng số nguyên 64 bit cho giá trị được in.
