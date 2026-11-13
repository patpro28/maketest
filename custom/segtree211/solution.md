### Ý tưởng

Dùng segment tree lưu tổng trên dãy theo thứ tự $1,dots,N$. Mỗi nút quản lý $d$ vị trí và tổng của nó tăng $Xd$ khi cộng $X$ trên cả nút.

Nếu $Lle R$, thực hiện một thao tác trên đoạn $[L,R]$. Nếu $L>R$, tách thao tác thành hai đoạn $[L,N]$ và $[1,R]$. Hai đoạn rời nhau và phủ đúng các kho trên cung được hỏi. Với cập nhật, cộng $X$ cho cả hai đoạn. Với truy vấn, cộng hai kết quả. Trường hợp $L=R$ nằm trong nhánh đầu và chỉ xử lý một kho.

### Lan truyền cập nhật

Mỗi nút lưu các tổng đã tính cho đoạn của nó và một nhãn cộng đang chờ truyền xuống con. Lưu nhãn dưới dạng tổng các lượng cộng chưa truyền.

- Nếu đoạn cập nhật phủ trọn nút, sửa các tổng theo công thức ở trên rồi cộng lượng cập nhật vào nhãn.
- Nếu phải đi xuống, áp dụng nhãn của cha cho cả hai con theo độ dài hoặc hệ số của từng con, sau đó đưa nhãn của cha về $0$.
- Sau khi cập nhật một phần, tính lại các tổng của cha từ hai con. Khi hỏi một đoạn, cộng các trường tương ứng của những nút phủ đoạn.

### Chứng minh tính đúng đắn

Sau khi dựng cây, mỗi lá lưu đúng đóng góp ban đầu của nó và mỗi nút trong bằng tổng hai con. Khi một cập nhật phủ trọn nút, từng số hạng của các tổng thay đổi theo lượng cộng và hệ số tương ứng, nên công thức sửa nút cho đúng tổng mới. Nhãn ghi chính xác phần thay đổi đồng đều đang chờ truyền xuống con.

Đẩy nhãn chuyển phần thay đổi đó xuống đúng các nút con, đồng thời giữ nguyên tổng của đoạn cha. Do đó có thể cập nhật hoặc truy vấn ở mức sâu hơn với dữ liệu đã tính đủ các lần cộng. Mỗi truy vấn ghép các đoạn rời nhau phủ đúng tập vị trí được hỏi, nên thu được các tổng cần thiết. Phép chuyển đổi kết quả ở phần ý tưởng cho đúng giá trị đề yêu cầu.

### Độ phức tạp

Dựng cây trong $O(N)$. Mỗi thao tác mất $O(log(N+1))$ thời gian. Bộ nhớ là $O(N)$.

Tổng đoạn có trị tuyệt đối không vượt quá $N(Q+1)10^8$. Dùng số nguyên 64 bit cho tổng, nhãn và tích.
