### Ý tưởng

Câu lạc bộ có $c$ thành viên tạo ra $w(c)=c(c-1)/2$ trận. Xây segment tree theo chỉ số câu lạc bộ, lá $i$ lưu $w(c_i)$ và nút trong lưu tổng. Cập nhật $c_i$ chỉ thay trọng số của một lá.

Nếu tổng tại gốc nhỏ hơn $k$, không có trận cần tìm. Ngược lại, đi xuống theo trọng số: nếu tổng con trái là $L$ và $k\le L$ thì chọn con trái; nếu $k>L$ thì chọn con phải với thứ hạng mới $k-L$. Khi đến lá $i$, ta biết thứ hạng $r$ của trận trong riêng câu lạc bộ này.

### Xác định hai thành viên

Đặt $c=c_i$. Với mỗi thành viên đầu tiên $u$, có $c-u$ trận tương ứng $v=u+1,\dots,c$. Số trận có thành viên đầu tiên không vượt $t$ là

$$F(t)=\sum_{u=1}^{t}(c-u)=\frac{t(2c-t-1)}{2},\qquad F(0)=0.$$

Trên $1\le t\le c-1$, $F$ tăng nghiêm ngặt. Tìm nhị phân $u$ nhỏ nhất sao cho $F(u)\ge r$. Thứ hạng trong nhóm có thành viên đầu tiên $u$ là $d=r-F(u-1)$, do đó $v=u+d$.

### Chứng minh tính đúng đắn

Mỗi lá lưu đúng số trận của câu lạc bộ, nên tổng mỗi nút là số trận của các câu lạc bộ trong miền đó. Theo thứ tự đề bài, mọi trận của con trái đứng trước mọi trận của con phải. Việc đi xuống theo tổng con trái vì thế giữ đúng thứ hạng và xác định đúng câu lạc bộ cùng thứ hạng nội bộ $r$.

Trong câu lạc bộ đã chọn, các nhóm trận theo thành viên đầu tiên $u$ xuất hiện theo thứ tự tăng dần của $u$. Điều kiện $F(u-1)<r\le F(u)$ xác định duy nhất nhóm chứa trận cần tìm. Trong nhóm này, thành viên thứ hai tăng từ $u+1$ đến $c$, nên phần tử thứ $d$ có $v=u+d$. Vì vậy bộ ba được in đúng là trận thứ $k$ trong danh sách toàn cục.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật mất $O(\log N)$, mỗi truy vấn mất $O(\log N+\log C)$, với $C=10^4$. Bộ nhớ $O(N)$.

### Lưu ý cài đặt

Dùng số nguyên 64 bit cho thứ hạng, công thức và tổng số trận. Tổng có thể đạt $200000\binom{10000}{2}=9999000000000$. Câu lạc bộ có $0$ hoặc $1$ thành viên có trọng số $0$, nên không thể được chọn khi tìm trận hợp lệ. Không cần tạo danh sách các trận.
