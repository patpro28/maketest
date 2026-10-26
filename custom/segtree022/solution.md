# Lời giải — Hai vận động viên mạnh nhất

### Thông tin tại mỗi nút

Mỗi nút lưu hai giá trị lớn nhất `first`, `second` trong đoạn, có tính cả các lần xuất hiện trùng nhau. Lá chứa $x$ lưu $(x,-\infty)$; nút rỗng lưu $(-\infty,-\infty)$.

### Phép ghép

Nếu `a.first >= b.first`, giá trị lớn nhất của đoạn ghép là `a.first`, giá trị lớn thứ hai là `max(a.second, b.first)`. Trường hợp ngược lại lấy `b.first` và `max(b.second, a.first)`.

### Xử lý thao tác

Dựng cây trên các giá trị ban đầu. Khi cập nhật một lá, tính lại các nút trên đường lên gốc. Truy vấn ghép thông tin của các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Hai giá trị trong kết quả tương ứng với hai lần xuất hiện khác nhau. Đoạn truy vấn luôn có ít nhất hai người nên chỉ cộng `first + second` sau khi truy vấn xong; không cộng các giá trị đại diện cho $-\infty$ trong quá trình ghép.

### Tính đúng đắn

Tại mỗi lá, thông tin đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng; vì vậy, bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi lần cập nhật tính lại mọi nút bị ảnh hưởng nên duy trì tính chất này. Truy vấn ghép các đoạn con phủ đúng đoạn cần hỏi, còn nút rỗng không làm thay đổi kết quả. Giữ hai lần xuất hiện lớn nhất là đủ, vì một giá trị không thuộc hai giá trị lớn nhất của một đoạn con không thể cải thiện cặp tốt nhất sau khi ghép. Do đó đáp án được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian, mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
