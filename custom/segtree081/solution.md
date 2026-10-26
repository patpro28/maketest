# Lời giải — Mức tăng tốt nhất

### Thông tin tại mỗi nút

Mỗi nút lưu min, max và hiệu lớn nhất `best` của một cặp có thứ tự trong đoạn. Một lá chứa $x$ lưu `mn = mx = x`, `best = -∞` vì chưa có đủ hai vị trí.

### Phép ghép

Khi ghép đoạn trái $L$ với đoạn phải $R$, lấy min và max như thông thường. Đáp án tốt nhất là `max(L.best, R.best, R.mx - L.mn)`: cặp nằm bên trái, bên phải hoặc đi qua chỗ ghép.

### Xử lý thao tác

Mỗi lần gán sửa lá tương ứng và tính lại các nút trên đường lên gốc. Mỗi truy vấn ghép các đoạn con rời nhau theo thứ tự trái sang phải để thu được thông tin của đoạn cần hỏi.

Nút rỗng được nhận biết bởi `mn = +∞`; khi ghép với nút rỗng thì trả lại nút còn lại. Không thực hiện phép trừ với các giá trị vô cực. Giữ đúng thứ tự trái rồi phải và không khởi tạo `best = 0`, vì đoạn giảm có đáp án âm.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Một cặp có thứ tự nằm hoàn toàn trong một đoạn con hoặc có vị trí đầu bên trái và vị trí sau bên phải. Ở trường hợp cuối, hiệu lớn nhất là max bên phải trừ min bên trái, nên công thức xét đủ các trường hợp. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Cập nhật tính lại tất cả nút bị ảnh hưởng nên duy trì tính chất đó. Truy vấn ghép đúng các đoạn con phủ đoạn cần hỏi; kết hợp với công thức tính đáp án ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian; mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
