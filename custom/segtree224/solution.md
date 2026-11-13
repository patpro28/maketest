### Thông tin lưu tại mỗi nút

Mỗi nút của segment tree lưu cặp $(M,c)$ gồm giá trị lớn nhất của đoạn và số lần xuất hiện của giá trị đó. Lá $i$ lưu $(a_i,1)$.

Khi ghép hai nút, nếu hai giá trị lớn nhất khác nhau thì lấy cặp có giá trị lớn hơn. Nếu cả hai bằng $M$, kết quả là $(M,c_1+c_2)$.

### Cập nhật và truy vấn

Khi toàn đoạn được cộng cùng $x$, sửa $M$ thành $M+x$. Những người cùng đạt điểm cao nhất vẫn cùng đạt điểm cao nhất, nên giữ $c$. Dùng lazy propagation để cộng dồn nhãn chờ. Đẩy nhãn xuống hai con trước khi xử lý một phần đoạn. Sau khi cập nhật một phần, tính lại cặp $(M,c)$ từ hai con.

Truy vấn lấy cặp của các nút phủ đoạn được hỏi rồi ghép bằng cùng quy tắc.

### Chứng minh tính đúng đắn

Khi hai đoạn có giá trị lớn nhất khác nhau, chỉ các phần tử ở đoạn có giá trị lớn hơn có thể đạt max của đoạn ghép. Khi hai giá trị bằng nhau, mọi lần xuất hiện ở hai đoạn đều đóng góp và không có vị trí nào bị đếm hai lần. Do đó phép ghép tính đúng cả $M$ và $c$. Phép cộng đồng đều bảo toàn tập các vị trí đạt max trong một nút. Khi đi xuống, đẩy nhãn bảo đảm giá trị của các nút con đã nhận đầy đủ những thay đổi chung. Vì vậy, truy vấn trả về đúng điểm cao nhất và số lần xuất hiện của nó.

### Độ phức tạp

Dựng cây tốn $O(n)$ thời gian. Mỗi thao tác tốn $O(\log(n+1))$ thời gian. Bộ nhớ là $O(n)$. Dùng số nguyên 64 bit cho điểm và nhãn cộng.
