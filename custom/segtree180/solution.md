# Lời giải — Đoạn ổn định

### Thông tin trên cây

Mỗi nút lưu tổng, min và max. Đồng thời giữ một nút tích lũy mô tả đoạn đã nhận từ điểm bắt đầu.

### Tìm kiếm trực tiếp

Duyệt các đoạn từ trái sang phải và chỉ xét phần từ $l$ trở đi. Thử ghép cả nút vào đoạn tích lũy: nếu tổng mới không vượt $B$ và max–min mới không vượt $D$, nhận cả nút. Nếu không, đi xuống tìm phần tử đầu tiên làm một trong hai điều kiện sai. Trả về chỉ số ngay trước phần tử đó, hoặc $N$ nếu nhận hết.

### Cập nhật

Mỗi thay đổi chỉ ảnh hưởng một vị trí. Sửa thông tin ở lá rồi tính lại các nút trên đường lên gốc. Các truy vấn luôn dùng trạng thái sau tất cả thao tác trước đó.

### Tính đúng đắn

Thông tin ở mỗi nút đúng sau khi dựng cây và được duy trì bằng cập nhật điểm. Khi mở rộng đoạn sang phải, tổng không giảm và chênh lệch max–min không giảm. Vì vậy, một khi điều kiện sai thì không thể đúng trở lại khi nhận thêm phần tử. Các nút được nhận toàn bộ đều bảo toàn điều kiện, và thứ tự duyệt bảo đảm không bỏ qua phần tử nào từ vị trí bắt đầu. Lá bị từ chối đầu tiên chính là phần tử đầu tiên làm đoạn không hợp lệ, nên vị trí ngay trước nó là điểm cuối xa nhất.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc tìm kiếm mất $O(\log N)$ thời gian, tổng thời gian $O(N+Q\log N)$ và bộ nhớ $O(N)$. Khi tìm biên, mỗi nút được nhận trọn vẹn không bị đi xuống nữa; chỉ các đường biên và đường đến vị trí bị từ chối được mở, nên không cần duyệt từng phần tử.
