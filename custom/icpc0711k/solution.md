## Thông tin cần nhớ của một tiền tố

Với ít nhất ba phần tử dương, mọi bộ ba thỏa bất đẳng thức tam giác khi và chỉ khi tổng **hai phần tử nhỏ nhất ở hai vị trí khác nhau** lớn hơn phần tử lớn nhất. Phần tử bằng nhau vẫn được tính đủ số lần xuất hiện.

Dùng trạng thái $F(r,a,b,h)$: số cách điền thêm $r$ phần tử, khi hai phần tử nhỏ nhất của tiền tố là $a\le b$ và phần tử lớn nhất là $h$. Ban đầu đặt $a=b=N+1,h=0$; giá trị lính canh giúp các tiền tố ít hơn ba phần tử luôn hợp lệ.

Nếu $a+b\le h$, trả về $0$. Nếu $r=0$ và điều kiện hợp lệ, trả về $1$. Với mỗi giá trị $v\in[1,N]$, cập nhật hai cực tiểu và cực đại rồi cộng số cách của trạng thái còn $r-1$ phần tử. Ghi nhớ kết quả để tránh tính lại.

Tổng số dãy là $F(N,N+1,N+1,0)$.

## Tìm dãy thứ T

Tại mỗi vị trí, thử giá trị $v$ tăng dần. Gọi $c$ là số cách hoàn thành khi chọn $v$. Nếu $T>c$, bỏ qua cả nhóm đó và giảm $T$ đi $c$; ngược lại chọn $v$ và tiếp tục. Các nhóm xếp liên tiếp đúng thứ tự từ điển.

## Tìm thứ tự của dãy A

Bắt đầu từ thứ hạng $1$. Tại mỗi vị trí, với tiền tố đã cố định bằng $A$, cộng số cách hoàn thành của mọi giá trị nhỏ hơn phần tử hiện tại của $A$. Sau đó cập nhật trạng thái bằng chính phần tử của $A$.

## Tính đúng đắn

Hai cực tiểu và cực đại xác định chính xác việc xuất hiện một bộ ba vi phạm. Một tiền tố đã vi phạm không thể được sửa bằng cách nối thêm phần tử. Vì thế công thức truy hồi phân hoạch đầy đủ các dãy hợp lệ theo giá trị tiếp theo.

Phương pháp tìm dãy bỏ qua đúng các nhóm liên tiếp trước nhóm chứa thứ hạng cần tìm. Phương pháp tính thứ hạng đếm mỗi dãy nhỏ hơn $A$ tại duy nhất vị trí khác nhau đầu tiên. Cả hai do đó cho kết quả chính xác.

## Độ phức tạp và kiểu số

Có $O(N^4)$ trạng thái, mỗi trạng thái thử $N$ giá trị: thời gian $O(N^5)$, bộ nhớ $O(N^4)$. Hai thao tác thứ hạng dùng thêm $O(N^2)$ lời gọi đã ghi nhớ.

Cận trên thô $N^N\le18^{18}$ vượt phạm vi 64 bit nhưng nằm trong số nguyên 128 bit. Dùng `__int128` và tự đọc, in dạng thập phân; không lấy modulo.
