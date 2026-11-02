### Ý tưởng

Để tìm tổng đoạn con lớn nhất, chỉ biết tổng các phần tử của một đoạn là chưa đủ. Khi ghép hai đoạn kề nhau, đoạn con tốt nhất có thể nằm trọn ở một bên hoặc đi qua ranh giới giữa hai bên.

Mỗi nút của segment tree lưu bốn đại lượng:

- `sum`: tổng mọi phần tử trong đoạn.
- `prefix`: tổng lớn nhất của một tiền tố không rỗng của đoạn.
- `suffix`: tổng lớn nhất của một hậu tố không rỗng của đoạn.
- `best`: tổng lớn nhất của một đoạn con liên tiếp không rỗng trong đoạn.

Với lá chứa giá trị $x$, cả bốn đại lượng đều bằng $x$, kể cả khi $x$ âm.

### Ghép hai nút

Gọi $A$ là đoạn bên trái, $B$ là đoạn bên phải và $C$ là đoạn sau khi ghép. Khi đó:

$$C.sum=A.sum+B.sum.$$

Một tiền tố của $C$ hoặc nằm trọn trong $A$, hoặc gồm toàn bộ $A$ và một tiền tố của $B$:

$$C.prefix=\max(A.prefix,\ A.sum+B.prefix).$$

Tương tự, một hậu tố của $C$ hoặc nằm trọn trong $B$, hoặc gồm một hậu tố của $A$ và toàn bộ $B$:

$$C.suffix=\max(B.suffix,\ B.sum+A.suffix).$$

Đoạn con tốt nhất có ba khả năng: nằm trong $A$, nằm trong $B$, hoặc đi qua ranh giới. Trong trường hợp cuối, nó gồm một hậu tố không rỗng của $A$ và một tiền tố không rỗng của $B$. Vì thế:

$$C.best=\max(A.best,\ B.best,\ A.suffix+B.prefix).$$

### Truy vấn

Dựng cây bằng phép ghép trên. Với mỗi đoạn $[u,v]$, ghép các nút phủ đoạn theo đúng thứ tự từ trái sang phải và trả về trường `best` của kết quả.

Phép ghép có tính kết hợp do luôn biểu diễn đúng thông tin của đoạn ghép, nhưng không có tính giao hoán. Trong cây dạng lặp, dùng hai biến tích lũy: thêm nút được lấy từ phía trái vào cuối biến trái, thêm nút được lấy từ phía phải vào đầu biến phải, rồi ghép biến trái với biến phải.

Dùng thêm dấu hiệu `empty` cho kết quả rỗng khi bắt đầu tích lũy. Ghép một kết quả rỗng với nút khác thì trả nguyên nút còn lại. Đây chỉ là trạng thái hỗ trợ tính toán, không cho phép chọn đoạn con rỗng làm đáp án.

### Chứng minh tính đúng đắn

Tại lá, đoạn chỉ có một phần tử $x$; tổng toàn đoạn, tổng tiền tố, tổng hậu tố và tổng đoạn con lớn nhất đều bằng $x$. Thông tin tại lá vì thế đúng.

Giả sử thông tin của hai nút con $A,B$ đúng. Tổng đoạn ghép là tổng của hai đoạn. Mọi tiền tố của đoạn ghép thuộc đúng một trong hai trường hợp đã xét, nên công thức `prefix` lấy đúng giá trị lớn nhất; lập luận tương tự đúng với `suffix`.

Mọi đoạn con liên tiếp không rỗng của đoạn ghép hoặc nằm hoàn toàn trong $A$, hoặc nằm hoàn toàn trong $B$, hoặc chứa phần tử ở cả hai bên. Trường hợp thứ ba bắt buộc gồm một hậu tố của $A$ và một tiền tố của $B$; tổng lớn nhất là $A.suffix+B.prefix$. Công thức `best` lấy lớn nhất của ba trường hợp nên đúng.

Theo quy nạp, mọi nút đều lưu đúng bốn đại lượng. Truy vấn ghép các đoạn kề nhau theo đúng thứ tự, nên kết quả cuối lưu đúng thông tin của $[u,v]$. Trường `best` vì thế là trọng lượng cần tìm.

### Độ phức tạp

Dựng cây mất $O(n)$ thời gian. Mỗi truy vấn mất $O(\log n)$ thời gian, tổng cộng $O(n+m\log n)$. Bộ nhớ là $O(n)$.

### Lưu ý cài đặt

Dùng số nguyên 64 bit vì tổng có thể đạt độ lớn $50000\cdot10^9=5\cdot10^{13}$. Không khởi tạo đáp án của một đoạn thật bằng $0$, vì đoạn toàn số âm vẫn phải chọn ít nhất một phần tử. Giữ đúng thứ tự trái–phải khi ghép, đặc biệt trong truy vấn dạng lặp.
