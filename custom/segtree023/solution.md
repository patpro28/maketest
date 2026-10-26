# Lời giải — Kiểm định chất lượng

### Thông tin tại mỗi nút

Mỗi nút lưu số đo nhỏ nhất `mn` và lớn nhất `mx` của đoạn. Lá chứa $x$ lưu $(x,x)$.

### Phép ghép

Ghép bằng min của hai `mn` và max của hai `mx`. Nút rỗng dùng $(+\infty,-\infty)$.

### Xử lý thao tác

Dựng cây trên các giá trị ban đầu. Khi cập nhật một lá, tính lại các nút trên đường lên gốc. Truy vấn ghép thông tin của các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Mọi số đo trong đoạn thuộc $[u,v]$ khi và chỉ khi `mn >= u` và `mx <= v`. Vì vậy mỗi truy vấn chỉ cần lấy min và max, rồi kiểm tra hai bất đẳng thức có dấu bằng.

### Tính đúng đắn

Tại mỗi lá, thông tin đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng; vì vậy, bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi lần cập nhật tính lại mọi nút bị ảnh hưởng nên duy trì tính chất này. Truy vấn ghép các đoạn con phủ đúng đoạn cần hỏi, còn nút rỗng không làm thay đổi kết quả. Điều kiện về min và max tương đương với mọi phần tử đều nằm trong hai biên cho phép. Do đó đáp án được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian, mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
