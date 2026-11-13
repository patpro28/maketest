## Ý tưởng

Với mỗi khối lượng $s$, lưu giá trị tốt nhất và số cách đạt giá trị đó từ các dòng đã xét. Ban đầu khối lượng $0$ có giá trị $0$ và một cách. Những khối lượng khác chưa đạt được.

Xét dòng có khối lượng $w$ và giá trị $v$. Giữ trạng thái cũ để biểu diễn lựa chọn lấy $0$ món. Thử thêm một món từ trạng thái ở $s-w$ nếu trạng thái này đạt được. Nếu giá trị mới lớn hơn, thay giá trị và số cách. Nếu hai giá trị bằng nhau, cộng số cách modulo $10^9+7$.

- Nếu dòng chỉ có một món, duyệt $s$ giảm dần từ $W$ đến $w$, để trạng thái ở $s-w$ chưa dùng món đó.
- Nếu số lượng không giới hạn, duyệt $s$ tăng dần từ $w$ đến $W$, để trạng thái ở $s-w$ có thể đã lấy món của dòng này.

## Chứng minh tính đúng đắn

Sau mỗi dòng, các phương án chia thành hai nhóm rời nhau. Nhóm lấy $0$ món ở dòng hiện tại thuộc lớp trước. Với nhóm lấy ít nhất một món, bỏ đúng một món ở dòng hiện tại sẽ cho một phương án đạt $s-w$. Nếu chỉ có một món thì phương án còn lại thuộc lớp trước. Nếu số lượng không giới hạn thì nó thuộc lớp hiện tại ở khối lượng nhỏ hơn. Ngược lại, thêm một món vào phương án tương ứng khôi phục duy nhất bộ số lượng ban đầu. Do đó mỗi phương án được xét đúng một lần. Các cách có cùng khối lượng đóng góp cùng giá trị $v$ khi thêm một món, nên chỉ cần giữ các cách tốt nhất trước mỗi phép chuyển.

## Độ phức tạp

Thời gian $O(N(W+1))$, bộ nhớ $O(W+1)$. Dùng số nguyên 64 bit cho giá trị. Kiểm tra trạng thái đạt được bằng trường giá trị vì số cách theo modulo có thể bằng $0$.
