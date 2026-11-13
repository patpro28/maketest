## Khi nào một đoạn phủ kín được?

Đoạn độ dài $1$ phủ kín được nếu phần tử duy nhất bằng $1$. Với đoạn dài hơn, điều kiện cần và đủ là có hai số $1$ cách nhau tối đa hai vị trí.

**Điều kiện đủ.** Hai số $1$ kề nhau đã tạo thành một khối toàn số $1$ có độ dài $2$. Nếu hai số $1$ cách nhau đúng hai vị trí, biến đoạn ba phần tử có hai số $1$ ở hai đầu thành toàn số $1$. Từ một khối toàn số $1$ có độ dài ít nhất $2$, có thể thêm một phần tử kề bên vào khối. Đoạn mới có ít nhất hai số $1$ và nhiều nhất một số $0$, nên phép biến đổi hợp lệ. Lặp lại cho đến khi phủ kín cả đoạn.

**Điều kiện cần.** Giả sử mọi cặp số $1$ trong đoạn đều cách nhau ít nhất ba vị trí. Một đoạn con chứa $k\ge2$ số $1$ phải chứa ít nhất $2(k-1)\ge k$ số $0$ giữa các số $1$. Nếu đoạn con chỉ chứa một số $1$ và có số $0$, số $1$ cũng không chiếm đa số. Vì vậy không thể thực hiện phép biến đổi nào làm đổi một số $0$ thành $1$. Đoạn ban đầu dài hơn $1$ và có ít nhất một số $0$, nên không phủ kín được.

## Đếm theo đầu phải

Duyệt đầu phải $r$ từ $1$ đến $N$. Lưu vị trí $p$ của số $1$ gần nhất đã gặp và giá trị $b$ là đầu trái lớn nhất của một cặp số $1$ cách nhau tối đa hai vị trí trong $A[1,r]$. Khởi tạo $p=b=0$ để đánh dấu chưa có vị trí tương ứng.

Nếu $A_r=1$, chỉ cần xét $p$ để cập nhật $b$. Nếu $p>0$ và $r-p\le2$, gán $b=p$, rồi lưu $p=r$ cho các lượt sau. Cặp kết thúc tại $r$ có đầu trái lớn nhất luôn dùng số $1$ liền trước nó, nên phép cập nhật duy trì đúng giá trị $b$.

Với đầu phải $r$ cố định, đoạn $[l,r]$ chứa một cặp hợp lệ đúng khi $1\le l\le b$. Vì thế có $b$ đoạn độ dài lớn hơn $1$ phủ kín được. Cộng thêm $A_r$ cho đoạn $[r,r]$ và lấy tổng qua mọi $r$.

## Độ phức tạp

Mỗi bộ test cần $O(N)$ thời gian và $O(1)$ bộ nhớ phụ. Có thể xử lý phần tử ngay khi đọc. Dùng số nguyên 64 bit cho đáp án vì nó có thể đạt $\frac{N(N+1)}2$.
