## Ý tưởng

Lưu chi phí thấp nhất tại mỗi ô theo số lần đổi hướng đã dùng và hướng của bước cuối. Ô cấm không có trạng thái đạt được.

Bước đầu từ ô xuất phát đến ô kề bên có số lần đổi hướng bằng $0$. Sau đó, khi sang phải hoặc đi xuống, cộng chi phí của ô mới. Số lần đổi hướng tăng thêm $1$ đúng khi hướng bước mới khác hướng đã lưu. Xử lý từ trên xuống dưới, trong mỗi hàng từ trái sang phải.

Ở đích, lấy chi phí nhỏ nhất trong hai hướng với đúng $K$ lần đổi hướng. Nếu ô xuất phát trùng ô đích, đường không có bước nào hợp lệ khi ô đó mở và $K=0$.

## Chứng minh tính đúng đắn

Một đường đi có ít nhất hai bước được tạo bằng cách nối bước cuối vào một đường đi ngắn hơn. Ô trước đó, hướng cũ và hướng mới xác định chính xác số lần đổi hướng tăng thêm. Các trạng thái cho bước đầu đã tính phí ô xuất phát và ô kế tiếp. Quy nạp theo số bước cho thấy các phép chuyển xét mọi đường đi hợp lệ và giữ phí thấp nhất cho từng trạng thái. Lấy kết quả tại đích với đúng $K$ lần đổi hướng cho đáp án.

## Độ phức tạp

Thời gian $O(RC(K+1))$. Bộ nhớ phụ $O(C(K+1))$ khi chỉ lưu hai hàng trạng thái, ngoài bảng đầu vào.
