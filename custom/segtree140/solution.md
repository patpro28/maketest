# Lời giải — Phân phòng cho đoàn khách

### Thông tin trên cây

Lưu số phòng trống lớn nhất trong mỗi đoạn.

### Tìm kiếm trực tiếp

Nếu max ở gốc nhỏ hơn nhu cầu, trả về $-1$. Ngược lại, ưu tiên con trái nếu max của nó đủ nhu cầu; nếu không thì đi phải. Đến lá sẽ có khách sạn phù hợp đầu tiên. Sau khi chọn, trừ nhu cầu tại lá đó rồi cập nhật đường lên gốc.

### Cập nhật

Mỗi thay đổi chỉ ảnh hưởng một vị trí. Sửa thông tin ở lá rồi tính lại các nút trên đường lên gốc. Các truy vấn luôn dùng trạng thái sau tất cả thao tác trước đó.

### Tính đúng đắn

Thông tin ở mỗi nút đúng sau khi dựng cây và được duy trì bằng cập nhật điểm. Điều kiện bỏ qua một đoạn chỉ được dùng khi đoạn đó không chứa đáp án. Ở mỗi bước đi xuống, thông tin các đoạn con cho biết nhánh được ưu tiên có thể chứa đáp án hay không. Khi bỏ qua một đoạn, thứ tự hoặc mốc cần đạt được được điều chỉnh bằng đúng phần đã bỏ qua nếu cần. Thứ tự ưu tiên duyệt tương ứng với vị trí đầu tiên hoặc cuối cùng cần tìm. Do đó lá tìm được đúng là đáp án; điều kiện ở gốc nhận biết chính xác trường hợp không tồn tại. Sau khi phân phòng, chỉ lượng phòng của khách sạn được chọn giảm đúng nhu cầu, nên trạng thái cho đoàn tiếp theo cũng đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc tìm kiếm mất $O(\log N)$ thời gian, tổng thời gian $O(N+Q\log N)$ và bộ nhớ $O(N)$.
