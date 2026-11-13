### Thông tin lưu tại mỗi nút

Dùng segment tree lưu cặp $(m,M)$ gồm giá trị nhỏ nhất và lớn nhất của đoạn. Một lá mang cặp $(a_i,a_i)$. Khi ghép hai nút con, lấy min của hai giá trị nhỏ nhất và max của hai giá trị lớn nhất.

### Cập nhật và truy vấn

Khi cả đoạn của nút được cộng cùng $x$, cặp $(m,M)$ trở thành $(m+x,M+x)$. Cộng thêm $x$ vào nhãn chờ của nút. Nếu thao tác cần đi vào một phần đoạn, truyền lượng cộng đang chờ xuống cả hai con trước khi đi tiếp. Sau khi cập nhật ở các nút con, ghép lại cặp cực trị của nút cha.

Để trả lời truy vấn, ghép cặp cực trị của các nút phủ đúng đoạn được hỏi và in $M-m$.

### Chứng minh tính đúng đắn

Giá trị nhỏ nhất của hai đoạn ghép bằng min của hai giá trị nhỏ nhất, và giá trị lớn nhất bằng max của hai giá trị lớn nhất. Phép cộng đều tăng cả hai cực trị đúng bằng lượng cộng. Nhãn chờ chỉ trì hoãn việc sửa thông tin ở nút con, nên đẩy nhãn trước khi đi xuống cung cấp các cực trị đã tính đủ cập nhật. Vì các nút dùng trong truy vấn phủ đúng đoạn hỏi, hai cực trị ghép được là cực trị của toàn đoạn đó, và hiệu của chúng là biên độ cần tìm.

### Độ phức tạp

Dựng cây tốn $O(n)$ thời gian. Mỗi cập nhật hoặc truy vấn tốn $O(\log(n+1))$ thời gian. Bộ nhớ là $O(n)$. Dùng số nguyên 64 bit cho cực trị, nhãn chờ và hiệu hai cực trị.
