## Trạng thái và chuyển

Đặt $F[i][j][t]$ là số cách chọn $j$ vị trí trong tiền tố nguồn dài $i$, có đúng $t$ sai lệch khi so với $B[1\ldots j]$. Khởi tạo $F[0][0][0]=1$.

Bỏ $A_i$ đóng góp $F[i-1][j][t]$. Đặt $e=[A_i\ne B_j]$. Nếu chọn $A_i$ và $t\ge e$, thêm $F[i-1][j-1][t-e]$. Vậy:

$$F[i][j][t]=F[i-1][j][t]+[t\ge e]F[i-1][j-1][t-e]\quad(j>0).$$

Chỉ giữ $0\le t\le K$. Đáp án là $\sum_{t=0}^K F[N][M][t]$ modulo $10^9+7$.

## Tính đúng đắn

Mỗi bộ chỉ số được phân loại duy nhất theo việc dùng vị trí hiện tại hay không. Khi dùng cho chữ thứ $j$, nó gây chính xác một sai lệch nếu hai chữ khác nhau, và không gây sai lệch nếu bằng nhau. Các lớp lưu số sai lệch chính xác nên không giao nhau. Công thức đếm đúng từng lớp theo quy nạp; cộng các lớp từ $0$ đến $K$ đếm đúng yêu cầu không quá $K$.

## Độ phức tạp và cài đặt

Nén chiều nguồn, duyệt $j$ giảm dần để mọi trạng thái đọc ở $j-1$ vẫn là hàng trước. Chỉ trạng thái chọn rỗng, sai lệch $0$, được khởi tạo bằng $1$. Không nhân thêm số cách thay chữ vì một bộ chỉ số chỉ được tính một lần. Thời gian $O(NM(K+1))$, bộ nhớ $O(M(K+1))$; tối đa $37.5\cdot10^6$ trạng thái chính.
