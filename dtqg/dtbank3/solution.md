## Ý tưởng

Xử lý công trình theo một thứ tự cố định. Trong mỗi công trình, quét các gói theo chỉ số tăng dần. Với mỗi gói, chỉ quyết định cấp gói đó cho công trình hiện tại hoặc bỏ qua để xét gói tiếp theo. Nhờ vậy, mỗi tập gói được xét đúng một lần, không đếm thêm các hoán vị của nó.

Mã mẫu sắp xếp nhu cầu giảm dần và giá trị các gói tăng dần trước khi xử lý. Việc đổi thứ tự chỉ là đổi tên chỉ số theo một hoán vị cố định, không gộp các công trình hay gói bằng giá trị, nên bảo toàn số phương án. Thuật toán cũng đúng nếu giữ nguyên thứ tự đầu vào.

## Trạng thái và chuyển tiếp

Đánh số công trình và gói từ $0$. Xét hàm $F(mask,p,k,s)$: đã dùng các gói trong $mask$, đã hoàn thành $k$ công trình; công trình hiện tại đang nhận $s$ và chỉ được chọn thêm gói có chỉ số từ $p$ trở đi. Hàm trả về số cách hoàn thành phần phân bổ còn lại.

- Nếu $k=n$, trả về $1$; các gói chưa chọn đều không dùng.
- Nếu $s=a_k$, chuyển sang $F(mask,0,k+1,0)$.
- Nếu chưa đủ tiền và $p=m$, trả về $0$.
- Trường hợp còn lại, chỉ xét gói thứ $p$, với tối đa hai lựa chọn:
  - **Bỏ qua gói:** cộng $F(mask,p+1,k,s)$.
  - **Cấp gói:** nếu $p\notin mask$ và $s+b_p\le a_k$, cộng $F(mask\cup\{p\},p+1,k,s+b_p)$.

Các phép cộng lấy modulo $10^9+7$. Bỏ qua một gói chỉ có nghĩa là không cấp nó cho công trình hiện tại; gói chưa dùng vẫn có thể được cấp cho công trình sau khi đặt lại $p=0$. Gói đã nằm trong $mask$ chỉ có nhánh bỏ qua.

Phải kiểm tra trường hợp $s=a_k$ trước trường hợp $p=m$, vì gói cuối cùng có thể vừa hoàn thành công trình. Do $b_j>0$, khi đã đủ tiền thì không thể cấp thêm gói nào cho công trình đó.

## Vì sao chỉ cần nhớ hai chiều?

Đặt $P_0=0$, $P_k=a_0+\cdots+a_{k-1}$. Các nhu cầu dương nên $P_k$ tăng nghiêm ngặt. Sau khi xử lý các trường hợp vừa đủ tiền ở đầu hàm, tổng giá trị $V$ của các gói trong $mask$ thỏa

$$P_k\le V<P_{k+1},\qquad s=V-P_k.$$

Vì vậy $mask$ xác định duy nhất $k$ và $s$ trong mọi trạng thái cần lưu. Chỉ cần bảng nhớ $memo[mask][p]$. Truyền $k,s$ trong lời gọi giúp tránh tính lại chúng.

Nếu tổng nhu cầu lớn hơn tổng giá trị các gói, có thể trả về $0$ ngay. Tổng tiền và nhu cầu tiền tố cần số nguyên 64 bit.

## Chứng minh tính đúng đắn

Với một phương án hợp lệ, xử lý các công trình theo thứ tự cố định. Khi quét gói $p$ cho một công trình, quyết định cấp gói nếu nó thuộc công trình đó trong phương án, và bỏ qua nếu không. Dãy quyết định này là duy nhất. Do mọi gói có giá trị dương, tổng tiền trên dãy đó không vượt nhu cầu; khi vừa đủ tiền, tất cả gói cần cấp cho công trình hiện tại đã được chọn nên có thể chuyển ngay sang công trình tiếp theo. Vì vậy mọi phương án hợp lệ đều được xét.

Ngược lại, mỗi nhánh kết thúc ở $k=n$ cấp đủ tiền cho từng công trình. Điều kiện mặt nạ ngăn dùng lại gói; mỗi chỉ số chỉ được xét một lần trong một công trình. Hai nhánh thành công khác nhau phải có một quyết định cấp hoặc bỏ qua khác nhau, nên tạo hai phương án phân bổ khác nhau. Vì thế các nhánh thành công tương ứng một-một với các phương án hợp lệ.

Cuối cùng, với cùng $mask,p$, hai đại lượng $k,s$ trùng nhau theo lập luận ở trên. Các gói còn có thể cấp cũng giống nhau: chúng chưa nằm trong $mask$ và có chỉ số từ $p$ trở đi. Do đó các trạng thái được gộp có cùng số cách hoàn thành; dùng bảng nhớ không thay đổi kết quả.

## Độ phức tạp

Có $2^m$ mặt nạ và $m$ giá trị $p$ cần lưu, nên có tối đa $m2^m$ ô trong bảng nhớ. Mỗi ô được tính một lần và chỉ có tối đa hai chuyển tiếp chọn hoặc bỏ qua, tốn $O(1)$ ngoài các lời gọi tới trạng thái khác.

Các lời gọi ở điều kiện dừng cũng chỉ tốn $O(1)$. Nếu $s=a_k$, hàm đặt $s=0$ và tăng $k$; vì nhu cầu công trình tiếp theo dương, không thể tiếp tục chuyển công trình ngay lập tức. Vì vậy mỗi chuyển tiếp chỉ phát sinh thêm một số hằng lời gọi như vậy, không có thêm hệ số $n$.

Khởi tạo bảng nhớ tốn $O(m2^m)$; sắp xếp tốn $O(m\log m)$ vì $n\le m$. Tổng cộng, mỗi bộ dữ liệu tốn **$O(m2^m)$ thời gian** và **$O(m2^m)$ bộ nhớ**. Với $m=20$, bảng số nguyên 32 bit chiếm khoảng $80$ MiB; xử lý lần lượt các bộ dữ liệu để tái sử dụng bộ nhớ. Với $T$ bộ dữ liệu đều có tối đa $m$ gói, tổng thời gian là $O(Tm2^m)$.
