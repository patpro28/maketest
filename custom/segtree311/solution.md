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

### Cập nhật điểm

Với thao tác `0 x y`, đi xuống lá ứng với vị trí $x$ và thay cả bốn trường bằng $y$. Sau đó đi ngược về gốc, tính lại mỗi nút bằng cách ghép hai nút con. Chỉ các nút trên đường từ lá $x$ tới gốc có thể thay đổi.

### Truy vấn đoạn

Với thao tác `1 u v`, truy vấn đoạn $[u,v]$ theo cây đệ quy:

- Nếu đoạn của nút nằm hoàn toàn trong đoạn được hỏi, trả về thông tin của nút.
- Nếu đoạn được hỏi chỉ giao một nút con, tiếp tục truy vấn nút con đó.
- Nếu đoạn được hỏi giao cả hai nút con, truy vấn từng bên rồi ghép kết quả bên trái trước, bên phải sau.

Trả về trường `best` của kết quả. Phép ghép không có tính giao hoán nên phải giữ đúng thứ tự trái–phải. Cách truy vấn này chỉ gọi đệ quy vào các đoạn có giao, không cần tạo một nút rỗng làm kết quả trung hòa.

### Chứng minh tính đúng đắn

Tại lá, đoạn chỉ có một phần tử $x$; tổng toàn đoạn, tổng tiền tố, tổng hậu tố và tổng đoạn con lớn nhất đều bằng $x$. Thông tin tại lá vì thế đúng.

Giả sử thông tin của hai nút con $A,B$ đúng. Tổng đoạn ghép là tổng của hai đoạn. Mọi tiền tố của đoạn ghép thuộc đúng một trong hai trường hợp đã xét, nên công thức `prefix` lấy đúng giá trị lớn nhất; lập luận tương tự đúng với `suffix`.

Mọi đoạn con liên tiếp không rỗng của đoạn ghép hoặc nằm hoàn toàn trong $A$, hoặc nằm hoàn toàn trong $B$, hoặc chứa phần tử ở cả hai bên. Trường hợp thứ ba bắt buộc gồm một hậu tố của $A$ và một tiền tố của $B$; tổng lớn nhất là $A.suffix+B.prefix$. Công thức `best` lấy lớn nhất của ba trường hợp nên đúng.

Theo quy nạp, sau khi dựng cây, mọi nút đều lưu đúng bốn đại lượng. Một cập nhật gán đúng thông tin tại lá thay đổi rồi ghép lại các tổ tiên; những nút khác không chứa vị trí được cập nhật nên vẫn đúng. Do đó bất biến của cây được duy trì sau mọi lần gán.

Truy vấn ghép các đoạn kề nhau theo đúng thứ tự, nên kết quả cuối lưu đúng thông tin của $[u,v]$ trên dãy hiện tại. Trường `best` vì thế là trọng lượng cần tìm.

### Độ phức tạp

Dựng cây mất $O(n)$ thời gian. Mỗi cập nhật và mỗi truy vấn đều mất $O(\log n)$ thời gian, tổng cộng $O(n+m\log n)$. Bộ nhớ là $O(n)$.

### Lưu ý cài đặt

Dùng số nguyên 64 bit vì tổng có thể đạt độ lớn $200000\cdot10^9=2\cdot10^{14}$. Không khởi tạo đáp án của một đoạn thật bằng $0$, vì đoạn toàn số âm vẫn phải chọn ít nhất một phần tử. Giữ đúng thứ tự trái–phải khi ghép. Thao tác `0 x y` là gán giá trị mới, không phải cộng thêm $y$; chỉ thao tác loại `1` sinh kết quả.
