# Lời giải — Hai đầu khác màu

### Thông tin trên cây

Lưu màu nhỏ nhất và lớn nhất trong đoạn. Một đoạn chỉ có màu $c$ khi và chỉ khi min và max của nó đều bằng $c$.

### Tìm kiếm trực tiếp

Bỏ qua nút có min và max đều bằng $c$. Để tìm vị trí đầu tiên, xét con trái trước; để tìm vị trí cuối cùng, xét con phải trước. Dừng ở lá đầu tiên không bị bỏ qua. Nếu cả cây bị bỏ qua, trả về $-1$.

### Cập nhật

Mỗi thay đổi chỉ ảnh hưởng một vị trí. Sửa thông tin ở lá rồi tính lại các nút trên đường lên gốc. Các truy vấn luôn dùng trạng thái sau tất cả thao tác trước đó.

### Tính đúng đắn

Thông tin ở mỗi nút đúng sau khi dựng cây và được duy trì bằng cập nhật điểm. Điều kiện bỏ qua một đoạn chỉ được dùng khi đoạn đó không chứa đáp án. Ở mỗi bước đi xuống, thông tin các đoạn con cho biết nhánh được ưu tiên có thể chứa đáp án hay không. Khi bỏ qua một đoạn, thứ tự hoặc mốc cần đạt được được điều chỉnh bằng đúng phần đã bỏ qua nếu cần. Thứ tự ưu tiên duyệt tương ứng với vị trí đầu tiên hoặc cuối cùng cần tìm. Do đó lá tìm được đúng là đáp án; điều kiện ở gốc nhận biết chính xác trường hợp không tồn tại.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc tìm kiếm mất $O(\log N)$ thời gian, tổng thời gian $O(N+Q\log N)$ và bộ nhớ $O(N)$.
