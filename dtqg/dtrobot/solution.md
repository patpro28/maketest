## Hai vectơ hướng liên tiếp

Gọi $u=(x_i-x_{i-1},y_i-y_{i-1})$ và $v=(x_{i+1}-x_i,y_{i+1}-y_i)$. Mỗi vectơ là một trong bốn hướng đơn vị trên lưới.

Xét định thức

$$cross=u_xv_y-u_yv_x.$$

- $cross>0$: hướng mới quay ngược chiều kim đồng hồ, tức rẽ trái.
- $cross<0$: hướng mới quay theo chiều kim đồng hồ, tức rẽ phải.
- $cross=0$: hai hướng cùng phương; robot đi thẳng hoặc quay ngược, không tăng bộ đếm nào.

Đọc lần lượt từng điểm, chỉ giữ tọa độ trước đó và vectơ hướng trước đó. Bước đầu chưa có hướng trước để so sánh. In số lần rẽ phải trước, rẽ trái sau.

## Chứng minh đúng

Với hai vectơ đơn vị vuông góc, định thức nhận giá trị $1$ khi rẽ trái và $-1$ khi rẽ phải. Hai trường hợp cùng phương có định thức $0$. Đây là toàn bộ các bước di chuyển hợp lệ.

Thuật toán xét đúng một lần mỗi cặp bước liên tiếp, từ bước thứ hai đến bước cuối, và phân loại theo đúng định thức. Vì vậy hai bộ đếm chính xác.

## Độ phức tạp

Thời gian $O(n)$, bộ nhớ $O(1)$. Không cần lưu danh sách tọa độ. Tọa độ không vượt $n-1$ về trị tuyệt đối; tích trong định thức chỉ dùng các thành phần $-1,0,1$.
