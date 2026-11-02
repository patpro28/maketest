### Ý tưởng

Mỗi nút lưu hai giá trị nhỏ nhất **khác nhau** trong đoạn: `first` và `second`. Nếu thiếu một giá trị, dùng ký hiệu $+\infty$. Lá chứa $x$ lưu $(x,+\infty)$.

Để ghép hai nút, xét tối đa bốn giá trị ứng viên từ hai nút con. Giữ lại hai giá trị hữu hạn nhỏ nhất khác nhau; các giá trị trùng nhau chỉ được tính một lần. Đây là phép ghép thời gian hằng số.

Dựng segment tree và truy vấn thông tin trên $[L,R]$. Nếu trường `second` là $+\infty$, in $-1$; ngược lại in `second`.

### Chứng minh tính đúng đắn

Trong một đoạn con, mọi giá trị khác ngoài hai giá trị nhỏ nhất đều có ít nhất hai giá trị khác nhau nhỏ hơn nó ngay trong đoạn con đó. Vì vậy giá trị này không thể thuộc hai giá trị nhỏ nhất khác nhau của đoạn hợp.

Do đó hai giá trị cần giữ của đoạn hợp phải nằm trong tối đa bốn ứng viên từ hai nút con. Loại trùng và chọn hai giá trị nhỏ nhất cho đúng kết quả. Các lá đúng theo định nghĩa, nên theo quy nạp mọi nút và kết quả truy vấn đều đúng. Trường `second` chính là mức giá cần tìm.

### Độ phức tạp

Dựng cây mất $O(N)$, mỗi truy vấn mất $O(\log N)$. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.

### Lưu ý cài đặt

Dùng $10^9+1$ làm giá trị vô cùng vì lớn hơn mọi mức giá hợp lệ. Hai sản phẩm cùng mức giá không tạo thành hai mức giá khác nhau. Đoạn một phần tử và đoạn có mọi phần tử bằng nhau đều trả về $-1$.

### Vì sao không dùng hiệu tổng tiền tố

Tổng đoạn không xác định được mức giá nhỏ thứ hai: hai đoạn $[0,2,4]$ và $[1,1,4]$ cùng có độ dài $3$, tổng $6$, nhưng đáp án lần lượt là $2$ và $4$. Tương tự, hai mức giá nhỏ nhất của một tiền tố không thể được loại bỏ chỉ bằng phép trừ để thu được thông tin của đoạn còn lại.
