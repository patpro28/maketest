### Ý tưởng

Vì các con đường có thể đi theo cả hai chiều, mỗi đặc khu kinh tế chính là một thành phần liên thông.

Gọi $C$ là thành phần liên thông chứa thành phố $1$. Một con đường mới chỉ có thể nối hai thành phần liên thông. Để tăng số thành phố trong $C$, ta nối một thành phố của $C$ với một thành phố thuộc thành phần khác.

Do đó, chọn thành phần lớn nhất khác $C$. Đáp án là kích thước của $C$ cộng kích thước thành phần được chọn. Nếu đồ thị đã liên thông thì đáp án là $N$.

### Thuật toán

1. Khởi tạo DSU với $N$ tập hợp, mỗi tập hợp chứa một thành phố.
2. Với mỗi con đường $(u, v)$, hợp nhất hai tập hợp chứa $u$ và $v$.
3. Tìm đại diện của thành phố $1$, rồi duyệt các đại diện khác để lấy kích thước lớn nhất.
4. In tổng hai kích thước; kích thước lớn nhất bên ngoài được khởi tạo bằng $0$.

### Chứng minh tính đúng đắn

Sau khi xử lý mọi con đường, hai thành phố thuộc cùng một tập hợp DSU khi và chỉ khi chúng liên thông. Vì vậy, các tập hợp DSU chính là các đặc khu kinh tế ban đầu.

Nếu con đường mới không nối $C$ với một thành phần khác, kích thước của $C$ không tăng. Nếu nối $C$ với thành phần $D$, đặc khu mới chứa thành phố $1$ có đúng $|C| + |D|$ thành phố. Một con đường không thể nhập thêm thành phần thứ ba vào $C$.

Chọn $D$ lớn nhất sẽ đạt giá trị lớn nhất trong tất cả các cách xây đường. Khi không có thành phần khác, mọi thành phố đã nằm trong $C$, nên kết quả là $N$.

### Độ phức tạp

DSU dùng nén đường đi và hợp nhất theo kích thước:

- Thời gian: $O((N + M)\alpha(N))$, với $\alpha$ là hàm Ackermann ngược.
- Bộ nhớ: $O(N)$; không cần lưu toàn bộ các con đường.

### Bộ kiểm thử

26 test gồm hai ví dụ, tám trường hợp đặc biệt, sáu đồ thị nhỏ, bốn đồ thị ngẫu nhiên gồm nhiều thành phần và sáu test lớn. Các test bao phủ thành phố $1$ cô lập, thành phần chứa $1$ lớn nhất, nhiều thành phần bằng nhau, đồ thị đã liên thông, đường dây dài, $N = 10^5$ và $M = 2 \times 10^5$.

Đề gốc không cấm $u = v$ hoặc các cặp đầu mút lặp lại. Bộ kiểm tra dữ liệu giữ nguyên các ràng buộc này; các test đặc biệt có cả hai trường hợp. Các cạnh như vậy không làm thay đổi thành phần liên thông.
