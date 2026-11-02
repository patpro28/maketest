### Ý tưởng

Lưu tần suất thật $f_x$ ngoài cây. Lá $x$ của segment tree lưu $b_x=[f_x=0]$, còn nút trong lưu tổng các lá thuộc miền của nó. Tổng tại gốc là số giá trị còn thiếu trong $[1,M]$.

Khi thêm hoặc xóa số $x$, cập nhật tần suất. Chỉ cần sửa lá khi tần suất chuyển từ $0$ sang dương hoặc ngược lại.

Để tìm giá trị còn thiếu thứ $k$, trước hết kiểm tra tổng tại gốc. Nếu không đủ, trả lời $-1$. Nếu đủ, đi xuống theo tổng con trái: chọn trái khi tổng này ít nhất bằng $k$; nếu không, trừ tổng đó khỏi $k$ rồi chọn phải.

### Chứng minh tính đúng đắn

Một giá trị còn thiếu đúng khi tần suất bằng $0$, nên ý nghĩa của lá đúng ở trạng thái ban đầu và sau mỗi lần cập nhật tần suất. Tổng trên mỗi nút luôn là số giá trị còn thiếu trong miền của nút.

Các giá trị ở con trái đều nhỏ hơn các giá trị ở con phải. Vì vậy nếu con trái chứa $L$ giá trị còn thiếu thì $L$ thứ hạng đầu tiên thuộc con trái; những thứ hạng còn lại thuộc con phải sau khi trừ $L$. Lặp lại quy tắc này tìm đúng giá trị còn thiếu thứ $k$. Nếu tổng ở gốc nhỏ hơn $k$ thì thứ hạng đó không tồn tại.

### Độ phức tạp

$O(M+Q\log M)$ thời gian và $O(M)$ bộ nhớ.

### Lưu ý cài đặt

Tần suất có thể vượt $10^9$ sau các lần thêm; dùng số nguyên 64 bit. Xóa một bản sao khi vẫn còn bản sao khác không làm giá trị trở thành còn thiếu. Không tính các giá trị ngoài $[1,M]$.
