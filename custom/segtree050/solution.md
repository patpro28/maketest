# Lời giải — Thống kê chẵn lẻ

### Thông tin lưu tại mỗi nút

Mỗi nút lưu số phần tử chẵn và số phần tử lẻ trong đoạn. Một lá có giá trị $(1,0)$ nếu phần tử chẵn và $(0,1)$ nếu phần tử lẻ.

### Phép ghép

Ghép hai nút bằng cách cộng riêng số phần tử chẵn và số phần tử lẻ.

### Cập nhật và truy vấn

Dựng segment tree trên dãy ban đầu. Khi cập nhật một vị trí, sửa lá tương ứng rồi tính lại các nút trên đường từ lá đến gốc. Khi truy vấn đoạn $[l,r]$, ghép thông tin của các đoạn con được cây tách ra.

Đáp án là cặp số đếm của nút kết quả; nút trung hòa là $(0,0)$. Khi kiểm tra số âm, dùng `x % 2 == 0` để nhận biết số chẵn.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Nếu thông tin của hai nút con đúng, phép ghép ở trên cho đúng thông tin của đoạn cha. Vì vậy, bằng quy nạp theo chiều cao cây, mọi nút đều lưu đúng thông tin sau khi dựng cây. Mỗi cập nhật tính lại tất cả nút bị ảnh hưởng nên duy trì tính chất này. Truy vấn ghép các đoạn con rời nhau theo đúng thứ tự để thu được thông tin của toàn bộ đoạn cần hỏi; do đó đáp án được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian là $O(N+Q\log N)$, bộ nhớ $O(N)$.
