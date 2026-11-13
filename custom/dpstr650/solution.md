## Chi phí ghép hai đầu

Nếu giữ cả hai đầu, cần biến chúng thành cùng một chữ. Khi hai chữ đã bằng nhau, chi phí là $0$. Nếu khác nhau, chỉ cần thay một đầu thành chữ của đầu kia, với chi phí $C(L,R)=\min(R_L,R_R)$. Thay cả hai không thể rẻ hơn vì chi phí không âm.

## Trạng thái và chuyển

Đặt $F[L][R]$ là chi phí nhỏ nhất để xử lý đoạn $S[L\ldots R]$ thành đối xứng. Đoạn rỗng và một ký tự đều có giá trị $0$.

$$F[L][R]=\min\begin{cases}D_L+F[L+1][R],\\D_R+F[L][R-1],\\C(L,R)+F[L+1][R-1].\end{cases}$$

Đáp án là $F[1][N]$.

## Tính đúng đắn

Một phương án hợp lệ phải xóa một trong hai đầu hoặc giữ cả hai. Hai trường hợp xóa dẫn tới bài toán còn lại sau khi trả đúng chi phí ở vị trí ban đầu. Khi giữ cả hai, chúng là cặp ngoài cùng nên phải bằng nhau sau khi xử lý; chi phí nhỏ nhất cho cặp đã được tính độc lập, còn phần trong phải đối xứng. Ngược lại, ghép từng lựa chọn với một phương án hợp lệ ở đoạn con luôn tạo phương án hợp lệ cho đoạn lớn. Do đó lấy nhỏ nhất trong ba trường hợp cho đúng tối ưu theo quy nạp.

## Độ phức tạp và cài đặt

Thời gian $O(N^2)$, bộ nhớ $O(N)$ bằng cách nén một hàng. Có ba lựa chọn trên mỗi đoạn, tối đa $37507500$ lượt xét chính. Dùng số nguyên 64 bit; tổng chi phí xóa có thể tới $5\cdot10^{12}$. Vẫn xét xóa khi hai đầu có cùng chữ vì chi phí gắn với từng vị trí.
