### Ý tưởng

Mỗi nút lưu số dư của tổng đoạn theo môđun $M$. Nhãn của nút cũng lưu dưới dạng số dư. Phép cộng và phép nhân với độ dài đoạn đều tương thích với lấy môđun, nên có thể chuẩn hóa sau mỗi phép tính.

Khi cộng $X$ vào một nút có $d$ phần tử, cộng $Xd$ vào tổng của nút và cộng $X$ vào nhãn. Chuẩn hóa cả hai kết quả về $[0,M-1]$. Nếu kết quả của phép lấy dư trong C++ là âm, cộng thêm $M$. Trường hợp $M=1$ cho số dư $0$ ở mọi nút.

### Lan truyền cập nhật

Mỗi nút lưu các tổng đã tính cho đoạn của nó và một nhãn cộng đang chờ truyền xuống con. Lưu nhãn dưới dạng số dư theo $M$.

- Nếu đoạn cập nhật phủ trọn nút, sửa các tổng theo công thức ở trên rồi cộng lượng cập nhật vào nhãn.
- Nếu phải đi xuống, áp dụng nhãn của cha cho cả hai con theo độ dài hoặc hệ số của từng con, sau đó đưa nhãn của cha về $0$.
- Sau khi cập nhật một phần, tính lại các tổng của cha từ hai con. Khi hỏi một đoạn, cộng các trường tương ứng của những nút phủ đoạn.

### Chứng minh tính đúng đắn

Sau khi dựng cây, mỗi lá lưu đúng đóng góp ban đầu của nó và mỗi nút trong bằng tổng hai con. Khi một cập nhật phủ trọn nút, từng số hạng của các tổng thay đổi theo lượng cộng và hệ số tương ứng, nên công thức sửa nút cho đúng tổng mới. Nhãn ghi chính xác phần thay đổi đồng đều đang chờ truyền xuống con.

Đẩy nhãn chuyển phần thay đổi đó xuống đúng các nút con, đồng thời giữ nguyên tổng của đoạn cha. Do đó có thể cập nhật hoặc truy vấn ở mức sâu hơn với dữ liệu đã tính đủ các lần cộng. Mỗi truy vấn ghép các đoạn rời nhau phủ đúng tập vị trí được hỏi, nên thu được các tổng cần thiết. Phép chuyển đổi kết quả ở phần ý tưởng cho đúng giá trị đề yêu cầu.

### Độ phức tạp

Dựng cây trong $O(N)$. Mỗi thao tác mất $O(log(N+1))$ thời gian. Bộ nhớ là $O(N)$.

Tính $X$ nhân độ dài đoạn bằng số nguyên 64 bit trước khi lấy dư. Lưu số dư ngay trên cây vì tổng nguyên chính xác có thể vượt miền số nguyên có dấu 64 bit.
