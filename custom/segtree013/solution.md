# Lời giải — Tổng đan dấu

### Thông tin tại mỗi nút

Đặt $B_i=A_i$ nếu $i$ lẻ và $B_i=-A_i$ nếu $i$ chẵn. Mỗi nút lưu tổng $B_i$ trên đoạn.

### Phép ghép

Ghép bằng phép cộng, giá trị trung hòa là $0$. Khi gán $A_i=x$, lá tương ứng nhận $x$ nếu $i$ lẻ và $-x$ nếu $i$ chẵn.

### Xử lý thao tác

Dựng cây trên các giá trị ban đầu. Khi cập nhật một lá, tính lại các nút trên đường lên gốc. Truy vấn ghép thông tin của các đoạn con rời nhau phủ đúng đoạn cần hỏi.

Gọi $S$ là tổng $B_i$ trên đoạn $[l,r]$. Nếu $l$ lẻ thì đáp án là $S$; nếu $l$ chẵn thì đáp án là $-S$. Cách đổi dấu này bảo đảm phần tử đầu đoạn luôn mang dấu cộng. Dùng số nguyên 64 bit.

### Tính đúng đắn

Tại mỗi lá, thông tin đúng theo định nghĩa. Phép ghép cho đúng thông tin của đoạn cha khi hai nút con đúng; vì vậy, bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Mỗi lần cập nhật tính lại mọi nút bị ảnh hưởng nên duy trì tính chất này. Truy vấn ghép các đoạn con phủ đúng đoạn cần hỏi, còn nút rỗng không làm thay đổi kết quả. Tổng các $B_i$ có hệ dấu cố định theo chỉ số, và đổi dấu khi $l$ chẵn đưa hệ dấu về bắt đầu bằng dấu cộng tại $l$. Do đó đáp án được in là đúng.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian, mỗi cập nhật hoặc truy vấn mất $O(\log N)$ thời gian. Tổng thời gian $O(N+Q\log N)$, bộ nhớ $O(N)$.
