# Lời giải — Vị trí thấp nhất

### Thông tin tại mỗi nút

Mỗi nút lưu cặp `(value, pos)`: giá trị nhỏ nhất và chỉ số nhỏ nhất đạt giá trị đó. Lá ở vị trí $i$ lưu $(A_i,i)$.

### Phép ghép

So sánh hai cặp theo giá trị trước, chỉ số sau. Cặp nhỏ hơn chính là kết quả của đoạn ghép. Nút rỗng dùng $(+\infty,+\infty)$ làm giá trị trung hòa.

### Xử lý truy vấn

Dựng segment tree trên dãy ban đầu. Khi gán một vị trí, sửa lá tương ứng rồi tính lại các nút trên đường lên gốc. Khi truy vấn $[l,r]$, ghép thông tin của các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Thông tin chỉ số được lưu và ghép ngay tại mỗi nút, nên không cần tìm kiếm thêm trên cây sau khi biết giá trị nhỏ nhất.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Khi hai nút con đúng, phép ghép cho đúng thông tin của đoạn cha. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi cập nhật tính lại toàn bộ các nút bị ảnh hưởng, nên tính chất này được duy trì. Truy vấn ghép các đoạn con rời nhau phủ đúng đoạn cần hỏi; phép ghép bảo toàn ý nghĩa thông tin và giá trị trung hòa không làm thay đổi kết quả. Vì vậy đáp án của mỗi truy vấn là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
