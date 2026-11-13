### Thông tin lưu tại mỗi nút

Mỗi nút của segment tree lưu cặp $(m,p)$, trong đó $m$ là số dư nhỏ nhất và $p$ là chỉ số nhỏ nhất trong các kho có số dư $m$. Lá $i$ lưu $(a_i,i)$. Để ghép hai đoạn, chọn cặp nhỏ hơn theo thứ tự từ điển. So sánh số dư trước, sau đó so sánh chỉ số nếu số dư bằng nhau.

### Cập nhật và truy vấn

Cộng cùng $x$ vào toàn bộ một nút làm số dư nhỏ nhất đổi từ $m$ thành $m+x$. Thứ tự số dư giữa các kho trong nút được giữ nguyên, nên $p$ vẫn đúng. Dùng lazy propagation để ghi lại các lượng cộng chờ và truyền chúng xuống trước khi thao tác đi vào một nút con.

Khi cập nhật một phần của nút, ghép lại hai cặp sau khi cập nhật con. Khi truy vấn, chọn cặp nhỏ nhất trong các nút phủ đúng đoạn hỏi.

### Chứng minh tính đúng đắn

Mỗi cặp lá biểu diễn đúng số dư và chỉ số của kho đó. Phép ghép chọn đúng kho có số dư thấp nhất và xử lý hòa bằng chỉ số nhỏ hơn. Phép cộng đều bảo toàn mọi so sánh giữa các kho trong cùng đoạn, nên phép cập nhật tại nút thay đổi đúng số dư trong cặp đã lưu. Đẩy nhãn bảo đảm các lần cập nhật tiếp theo ở nút con nhận đủ lượng cộng. Phép ghép của các nút trong truy vấn vì thế trả về kho đúng trên toàn đoạn.

### Độ phức tạp

Dựng cây tốn $O(n)$ thời gian. Mỗi thao tác tốn $O(\log(n+1))$ thời gian. Bộ nhớ là $O(n)$. Dùng số nguyên 64 bit cho số dư và nhãn cộng.
