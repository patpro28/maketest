# Lời giải — Độ cao địa hình

### Thông tin tại mỗi nút

Mỗi nút lưu cặp `mn`, `mx`: độ cao thấp nhất và cao nhất của đoạn. Lá ở vị trí $i$ lưu $(A_i,A_i)$.

### Phép ghép

Lấy min của hai giá trị `mn` và max của hai giá trị `mx`. Nút rỗng có `mn = +∞`, `mx = -∞`.

### Xử lý thao tác

Dựng cây một lần trên dãy ban đầu. Truy vấn ghép thông tin của các nút đại diện cho các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Dựng cây một lần; không có thao tác cập nhật. Với nút kết quả của một truy vấn, in `mn`, `mx`, `mx - mn`.

### Tính đúng đắn

Tại mỗi lá, thông tin đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng; vì vậy, bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Truy vấn ghép các đoạn con phủ đúng đoạn cần hỏi, còn nút rỗng không làm thay đổi kết quả. Do đó đáp án được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian, mỗi truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
