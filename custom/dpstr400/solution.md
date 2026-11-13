Đặt $F[i]$ cho biết tiền tố dài $i$ có chia được hay không. Khởi tạo $F[0]=1$. Với mỗi $i$, thử mảnh cuối dài $1$ hoặc $2$. Nếu mảnh nằm trong danh sách và tiền tố phía trước chia được thì đặt $F[i]=1$.

Mọi cách chia hợp lệ có một mảnh cuối duy nhất thuộc danh sách. Bỏ mảnh cuối thu được cách chia tiền tố đã biết. Ngược lại, nối một mảnh hợp lệ vào tiền tố chia được sẽ phủ đúng tiền tố mới. Vì vậy $F[N]$ cho kết quả cần tìm.

Thời gian $O(N)$ và bộ nhớ $O(N)$. Có thể nén xuống $O(1)$ bằng cách giữ hai giá trị trước.
