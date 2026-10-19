# Lời giải — Dấu của tích

### Thông tin lưu tại mỗi nút

Thay mỗi phần tử bằng dấu của nó: $-1$ nếu âm, $0$ nếu bằng $0$, $1$ nếu dương. Mỗi nút lưu tích các dấu trong đoạn.

### Phép ghép

Ghép hai nút bằng phép nhân. Mọi giá trị được lưu đều thuộc tập $\{-1,0,1\}$ nên không tràn số.

### Cập nhật và truy vấn

Dựng segment tree trên dãy ban đầu. Khi cập nhật một vị trí, sửa lá tương ứng rồi tính lại các nút trên đường từ lá đến gốc. Khi truy vấn đoạn $[l,r]$, ghép thông tin của các đoạn con được cây tách ra.

Giá trị trung hòa là $1$. Đổi kết quả $-1,0,1$ thành các ký tự `-`, `0`, `+` tương ứng. Không nhân trực tiếp các giá trị ban đầu.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Nếu thông tin của hai nút con đúng, phép ghép ở trên cho đúng thông tin của đoạn cha. Vì vậy, bằng quy nạp theo chiều cao cây, mọi nút đều lưu đúng thông tin sau khi dựng cây. Mỗi cập nhật tính lại tất cả nút bị ảnh hưởng nên duy trì tính chất này. Truy vấn ghép các đoạn con rời nhau theo đúng thứ tự để thu được thông tin của toàn bộ đoạn cần hỏi; do đó đáp án được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian là $O(N+Q\log N)$, bộ nhớ $O(N)$.
