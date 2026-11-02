Tính $H[i][j]$, độ dài một đoạn chung tốt nhất nằm trọn trong hai tiền tố dài $i,j$. Trong lượt duyệt xuôi, tính độ dài đoạn khớp kết thúc $E[i][j]$ rồi đặt:

$$H[i][j]=\max(H[i-1][j],H[i][j-1],E[i][j]).$$

Tiếp theo duyệt ngược để tính $S[i][j]$, độ dài đoạn khớp dài nhất **bắt đầu** tại vị trí $i,j$. Khi hai chữ bằng nhau, $S[i][j]=S[i+1][j+1]+1$; ngược lại bằng $0$.

Nếu $H[i-1][j-1]>0$ và $S[i][j]>0$, xét tổng $H[i-1][j-1]+S[i][j]$. Mảnh đầu nằm hoàn toàn trước vị trí bắt đầu mảnh thứ hai ở cả hai xâu, nên hai mảnh không giao nhau và đúng thứ tự. Hai số hạng dương bảo đảm cả hai mảnh không rỗng.

Ngược lại, xét một phương án tối ưu có mảnh thứ hai bắt đầu tại $i,j$. Mảnh đầu không dài hơn $H[i-1][j-1]$ và mảnh thứ hai không dài hơn $S[i][j]$. Thay bằng hai phương án tốt nhất này vẫn hợp lệ, nên phép lấy lớn nhất không bỏ sót đáp án tối ưu. Nếu không có tổng hợp lệ, trả về $-1$.

Lưu toàn bộ $H$, nhưng nén $E$ và $S$ còn một hàng. Giá trị $H$ không vượt $4000$ nên có thể dùng `uint16_t` cho bảng, khoảng 32 MB. Hai lượt duyệt đều $O(NM)$; số ô xử lý không vượt cận thiết kế $3NM\le4,8\cdot10^7$.

Độ phức tạp thời gian $O(NM)$, bộ nhớ phụ của DP $O(NM)$.
