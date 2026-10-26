# Lời giải — Ô trống đầu tiên

### Thông tin trên cây

Lưu số ô trống trong mỗi đoạn. Lá chứa trạng thái $x$ lưu $1-x$; nút cha cộng hai số đếm.

### Tìm kiếm trực tiếp

Nếu gốc có số đếm $0$, trả về $-1$. Ngược lại, đi xuống nút trái nếu nó có ít nhất một ô trống; nếu không, đi xuống nút phải. Khi đến lá, trả về chỉ số lá.

### Cập nhật

Mỗi thay đổi chỉ ảnh hưởng một vị trí. Sửa thông tin ở lá rồi tính lại các nút trên đường lên gốc. Các truy vấn luôn dùng trạng thái sau tất cả thao tác trước đó.

### Tính đúng đắn

Thông tin ở mỗi nút đúng sau khi dựng cây và được duy trì bằng cập nhật điểm. Điều kiện bỏ qua một đoạn chỉ được dùng khi đoạn đó không chứa đáp án. Ở mỗi bước đi xuống, thông tin các đoạn con cho biết nhánh được ưu tiên có thể chứa đáp án hay không. Khi bỏ qua một đoạn, thứ tự hoặc mốc cần đạt được được điều chỉnh bằng đúng phần đã bỏ qua nếu cần. Thứ tự ưu tiên duyệt tương ứng với vị trí đầu tiên hoặc cuối cùng cần tìm. Do đó lá tìm được đúng là đáp án; điều kiện ở gốc nhận biết chính xác trường hợp không tồn tại.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc tìm kiếm mất $O(\log N)$ thời gian, tổng thời gian $O(N+Q\log N)$ và bộ nhớ $O(N)$.
