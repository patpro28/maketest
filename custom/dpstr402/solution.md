Đặt $F[i]$ là số đoạn ít nhất để chia tiền tố dài $i$, với $F[0]=0$ và vô cực cho tiền tố chưa chia được. Từ một tiền tố chia được, lần lượt nối từ một đến mười chữ số để tạo mảnh mới. Bỏ điểm bắt đầu có chữ số `0`. Nếu giá trị mới trong $[L,R]$, cập nhật tiền tố mở rộng với chi phí $F[i]+1$. Có thể dừng khi giá trị vượt $R$.

Mỗi mảnh hợp lệ có nhiều nhất mười chữ số. Mỗi cạnh cập nhật nối đúng một mảnh hợp lệ. Ngược lại, mỗi cách chia đi qua đúng các tiền tố tương ứng với những điểm cắt, nên thứ tự tăng của tiền tố xét đủ các phương án.

Thời gian $O(10N)$, bộ nhớ $O(N)$. Dùng 64 bit để ghép chữ số trước khi so sánh với $R$.
