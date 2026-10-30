# Lời giải CACHBA — Chọn các vị trí cách ba

## DP trên một đoạn

Nếu chưa có cập nhật, gọi $F_i$ là tổng tốt nhất trên các vị trí từ $L$ tới $i$. Khi xét $i$, hoặc bỏ nó, hoặc chọn nó và không chọn hai vị trí trước:

$$F_i=\max(F_{i-1},F_{i-3}+A_i),$$

với các giá trị trước biên trái bằng $0$. Cách này mất thời gian tuyến tính theo độ dài mỗi truy vấn. Để ghép được các đoạn, cần lưu ảnh hưởng của chúng với mọi trạng thái ở biên.

## Ba trạng thái thời gian chờ

Trước khi xét một vị trí, trạng thái $s\in\{0,1,2\}$ cho biết còn bao nhiêu vị trí bắt buộc phải bỏ qua vì lựa chọn trước đó.

- $s=0$: có thể bỏ, giữ trạng thái $0$; hoặc chọn giá trị $w$, chuyển sang $2$ và nhận $w$.
- $s=1$: bắt buộc bỏ, chuyển sang $0$.
- $s=2$: bắt buộc bỏ, chuyển sang $1$.

Dùng vector hàng với giá trị DP là tổng tốt nhất ở mỗi trạng thái. Ma trận của vị trí có giá trị $w$ là

$$T(w)=\begin{pmatrix}0&-\infty&w\\0&-\infty&-\infty\\-\infty&0&-\infty\end{pmatrix}.$$

Hàng là trạng thái trước khi đọc vị trí, cột là trạng thái sau khi đọc. Khi chọn một vị trí, hai vị trí tiếp theo bị bỏ, nên vị trí được chọn tiếp theo cách ít nhất $3$.

## Segment tree lưu tích ma trận

Định nghĩa $(B\otimes C)[i][j]=\max_k(B[i][k]+C[k][j])$. Một nút quản lý đoạn $[l,r]$ lưu

$$M_{l,r}=T(A_l)\otimes T(A_{l+1})\otimes\cdots\otimes T(A_r).$$

Khi ghép hai con, nhân ma trận con trái trước rồi con phải. Cập nhật một vị trí thay ma trận lá và tính lại các tổ tiên.

Với truy vấn $[L,R]$, lấy tích theo đúng thứ tự từ trái sang phải. Trước $L$ không có vị trí nào đã chọn, nên vector đầu là $(0,-\infty,-\infty)$. Sau $R$ được phép còn thời gian chờ vì không xét vị trí bên ngoài. Đáp án là

$$\max_{j=0}^{2}M_{L,R}[0][j].$$

Khả năng bỏ toàn bộ đoạn luôn tồn tại, nên đáp án không âm. Không ép trạng thái cuối về $0$; làm vậy sẽ loại nhầm phương án chọn gần cuối đoạn.

## Thứ tự tích trong truy vấn

Phép nhân có tính kết hợp nhưng không giao hoán. Khi dùng segment tree lặp, giữ hai tích `left`, `right`, đều khởi tạo bằng ma trận đơn vị. Các nút lấy từ biên trái được nối vào sau `left`; các nút lấy từ biên phải được nối vào trước `right`. Cuối cùng lấy `left` nhân `right`.

Ma trận đơn vị có đường chéo bằng $0$, ngoài đường chéo bằng $-\infty$; không dùng ma trận toàn số $0$ cho đoạn rỗng.

## Chứng minh đúng và độ phức tạp

Trạng thái chờ phản ánh đúng toàn bộ điều kiện mà lựa chọn trước áp đặt lên vị trí tiếp theo. Mỗi tập hợp lệ tương ứng với một đường chuyển trạng thái và có cùng tổng trọng số. Ma trận lá mô tả đúng một vị trí; phép nhân tối ưu trên trạng thái ở điểm nối, nên theo quy nạp ma trận mỗi nút biểu diễn đúng cả đoạn. Khởi tạo trạng thái đầu và lấy max trạng thái cuối đúng với quy định truy vấn.

Kích thước ma trận bằng $3$. Xây cây mất $O(3^3N)$, mỗi cập nhật hoặc truy vấn mất $O(3^3\log N)$; bộ nhớ $O(3^2N)$. Dùng số nguyên có dấu $64$ bit; trạng thái $-\infty$ không được tham gia phép cộng.
