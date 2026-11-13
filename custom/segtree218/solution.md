### Ý tưởng

Đọc các thao tác và lấy mọi mốc $L$ và $R+1$ của cả cập nhật lẫn truy vấn. Sắp xếp, loại mốc trùng và gọi dãy mốc là $p_0<p_1<dots<p_t$. Khối thứ $i$ là khoảng nửa mở $[p_{i-1},p_i)$, chứa $p_i-p_{i-1}$ vị trí nguyên.

Mọi đoạn thao tác phủ nguyên các khối vì hai đầu đều là mốc. Ban đầu các vị trí trong cùng khối có tải $0$. Sau mỗi lần cộng, chúng vẫn có cùng tải vì cập nhật tác động đến cả khối hoặc bỏ qua cả khối. Lá của cây đại diện cho một khối và lưu **tổng tải của các vị trí** trong khối. Với một nút phủ $d$ vị trí nguyên, cộng $X$ làm tổng tăng $Xd$. Tính $d$ bằng hiệu hai mốc ngoài cùng của nút.

Với mỗi thao tác, tìm mốc $L$ và $R+1$ bằng tìm kiếm nhị phân. Các khối nằm giữa hai mốc tạo thành một đoạn trên cây. Xử lý các thao tác theo đúng thứ tự đọc.

### Lan truyền cập nhật

Mỗi nút lưu các tổng đã tính cho đoạn của nó và một nhãn cộng đang chờ truyền xuống con. Lưu nhãn dưới dạng tổng các lượng cộng chưa truyền.

- Nếu đoạn cập nhật phủ trọn nút, sửa các tổng theo công thức ở trên rồi cộng lượng cập nhật vào nhãn.
- Nếu phải đi xuống, áp dụng nhãn của cha cho cả hai con theo độ dài hoặc hệ số của từng con, sau đó đưa nhãn của cha về $0$.
- Sau khi cập nhật một phần, tính lại các tổng của cha từ hai con. Khi hỏi một đoạn, cộng các trường tương ứng của những nút phủ đoạn.

### Chứng minh tính đúng đắn

Sau khi dựng cây, mỗi lá lưu đúng đóng góp ban đầu của nó và mỗi nút trong bằng tổng hai con. Khi một cập nhật phủ trọn nút, từng số hạng của các tổng thay đổi theo lượng cộng và hệ số tương ứng, nên công thức sửa nút cho đúng tổng mới. Nhãn ghi chính xác phần thay đổi đồng đều đang chờ truyền xuống con.

Đẩy nhãn chuyển phần thay đổi đó xuống đúng các nút con, đồng thời giữ nguyên tổng của đoạn cha. Do đó có thể cập nhật hoặc truy vấn ở mức sâu hơn với dữ liệu đã tính đủ các lần cộng. Mỗi truy vấn ghép các đoạn rời nhau phủ đúng tập vị trí được hỏi, nên thu được các tổng cần thiết. Phép chuyển đổi kết quả ở phần ý tưởng cho đúng giá trị đề yêu cầu.

### Độ phức tạp

Có tối đa $2Q$ mốc. Sắp xếp các mốc và xử lý các thao tác mất $O(Qlog(Q+1))$ thời gian. Bộ nhớ là $O(Q)$.

Tổng tải có trị tuyệt đối không vượt quá $10^9 Qcdot10000le2cdot10^{18}$. Dùng số nguyên 64 bit khi nhân với độ dài. Mốc $R+1$ có thể bằng $10^9+1$.
