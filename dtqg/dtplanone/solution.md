## DP theo lượng nguyên liệu

Đặt $f_i[p]$ là số phương án dùng $i$ loại đầu tiên để tiêu thụ đúng $p$ đơn vị. Ban đầu $f_0[0]=1$, các giá trị khác bằng $0$.

Với loại $i$, chia phương án thành không dùng loại đó và dùng ít nhất một sản phẩm của loại đó. Bỏ một sản phẩm trong nhóm thứ hai cho song ánh với các phương án tiêu thụ $p-a_i$ đơn vị bằng $i$ loại đầu tiên:

$$f_i[p]=f_{i-1}[p]+f_i[p-a_i],$$

bỏ số hạng thứ hai nếu $p<a_i$. Mọi phép cộng lấy modulo $10^9$.

## Cài đặt một chiều

Khởi tạo $f[0]=1$. Duyệt từng loại ở vòng ngoài, rồi duyệt $p$ tăng từ $a_i$ đến $A$:

$$f[p]\mathrel{+}=f[p-a_i].$$

Duyệt tăng cho phép dùng một loại nhiều lần. Đặt loại ở vòng ngoài bảo đảm đếm theo bộ số lượng, không đếm các thứ tự sản xuất. Các loại trùng mức tiêu hao vẫn phải được xét riêng.

## Chứng minh đúng

Hai nhóm không dùng và có dùng loại $i$ rời nhau, bao phủ mọi phương án. Phép bỏ một sản phẩm loại $i$ là thuận nghịch, nên công thức tính đúng số phương án. Khi cập nhật tại chỗ theo $p$ tăng, ô bên trái chưa cập nhật chứa giá trị lớp trước, còn ô $p-a_i$ đã chứa giá trị lớp hiện tại, đúng theo công thức. Quy nạp theo số loại chứng minh kết quả $f[A]$ đúng.

Với $A=0$, phương án duy nhất là không sản xuất gì, nên kết quả bằng $1$.

## Độ phức tạp

Thời gian $O(mA)$, bộ nhớ $O(A)$.
