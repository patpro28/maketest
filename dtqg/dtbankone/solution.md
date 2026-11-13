## Ý tưởng và thuật toán

Chỉ có một công trình, nên một phương án được xác định duy nhất bởi tập các gói được sử dụng. Biểu diễn tập đó bằng mặt nạ $mask$ có $m$ bit, bit $j$ bằng $1$ khi dùng gói thứ $j$.

Đặt $sum[0]=0$. Với mỗi mặt nạ khác $0$, lấy một bit bật $j$ rồi tính

$$sum[mask]=sum[mask\setminus\{j\}]+b_j.$$

Đếm các mặt nạ có tổng bằng $a_1$. Không cần xét tập rỗng vì $a_1>0$. Các gói có cùng giá trị vẫn có các bit khác nhau. Số phương án tối đa $2^{20}$ nên trong phiên bản này kết quả chưa vượt modulo.

## Chứng minh tính đúng đắn

Mỗi phương án chọn một tập gói duy nhất, và mỗi mặt nạ xác định một tập gói duy nhất. Truy hồi tính đúng tổng của tập vì bỏ bit $j$ chính là bỏ đúng gói thứ $j$. Vì thế điều kiện $sum[mask]=a_1$ tương đương việc công trình được nhận đúng số tiền, và phép đếm xét mỗi phương án đúng một lần.

## Độ phức tạp

Mỗi bộ dữ liệu tốn $O(2^m)$ thời gian và $O(2^m)$ bộ nhớ. Tổng các gói có thể đến $2\cdot10^{10}$, nên dùng số nguyên 64 bit cho tổng.
