Mỗi ô $(i,j)$ giữ ba chi phí tùy bước cuối là ghép, chèn hay xóa. Bước ghép lấy nhỏ nhất của ba trạng thái chéo rồi cộng phí thay nếu hai chữ khác nhau. Bước chèn đọc ô bên trái, cộng $E$ nếu tiếp tục đợt chèn hoặc $O+E$ nếu bắt đầu đợt mới. Bước xóa đọc ô bên trên theo quy tắc tương tự. Cho trạng thái ghép ở gốc bằng $0$ để biểu diễn chưa có đợt nào, còn các trạng thái không thể đạt bằng vô cực.

Phí của bước tiếp theo chỉ phụ thuộc vào loại bước cuối. Mọi phương án có đúng một bước cuối và chi phí đợt bằng phí mở ở bước đầu cộng phí kéo dài ở tất cả bước của đợt. Vì vậy truy hồi tính đúng giá và tối ưu trên mọi phương án.

Thời gian $O(NM)$ với ba trạng thái trên mỗi cặp vị trí và bộ nhớ $O(M)$. Dùng 64 bit, khởi tạo trục rỗng bằng giá một đợt nếu đã xử lý ít nhất một ký tự.
