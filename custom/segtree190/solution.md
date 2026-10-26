# Lời giải — Bảng điều phối

### Thông tin trên cây

Mỗi nút lưu ba đại lượng: tổng lượng hàng, lượng hàng lớn nhất và số kho có hàng. Một lần cập nhật sửa cả ba tại lá rồi ghép lên gốc.

### Tìm kiếm trực tiếp

Với loại $2$, đi xuống theo max để tìm vị trí đầu tiên đủ hàng. Với loại $3$, đi xuống theo tổng, trừ tổng con trái khi phải đi phải. Với loại $4$, đi xuống theo số kho có hàng và giảm $k$ tương ứng. Trước mỗi tìm kiếm, kiểm tra đại lượng ở gốc để biết kết quả có tồn tại hay không.

### Cập nhật

Mỗi thay đổi chỉ ảnh hưởng một vị trí. Sửa thông tin ở lá rồi tính lại các nút trên đường lên gốc. Các truy vấn luôn dùng trạng thái sau tất cả thao tác trước đó.

### Tính đúng đắn

Thông tin ở mỗi nút đúng sau khi dựng cây và được duy trì bằng cập nhật điểm. Điều kiện bỏ qua một đoạn chỉ được dùng khi đoạn đó không chứa đáp án. Ở mỗi bước đi xuống, thông tin các đoạn con cho biết nhánh được ưu tiên có thể chứa đáp án hay không. Khi bỏ qua một đoạn, thứ tự hoặc mốc cần đạt được được điều chỉnh bằng đúng phần đã bỏ qua nếu cần. Thứ tự ưu tiên duyệt tương ứng với vị trí đầu tiên hoặc cuối cùng cần tìm. Do đó lá tìm được đúng là đáp án; điều kiện ở gốc nhận biết chính xác trường hợp không tồn tại.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc tìm kiếm mất $O(\log N)$ thời gian, tổng thời gian $O(N+Q\log N)$ và bộ nhớ $O(N)$.
