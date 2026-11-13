### Ý tưởng

Mỗi nút lưu tổng đoạn. Khi cộng $X$ vào cả nút có $d$ phần tử, tổng của nó tăng $Xd$.

Với truy vấn $[L,R]$, lấy tổng $S$ từ cây rồi đặt $d=R-L+1$. Trung bình chính xác là $S/d$. Đặt $g=gcd(|S|,d)$ và in $S/g$ cùng $d/g$. Vì $d>0$ nên $g>0$ và mẫu số sau rút gọn vẫn dương. Nếu $S=0$ thì $g=d$, cho kết quả $0/1$.

### Lan truyền cập nhật

Mỗi nút lưu các tổng đã tính cho đoạn của nó và một nhãn cộng đang chờ truyền xuống con. Lưu nhãn dưới dạng tổng các lượng cộng chưa truyền.

- Nếu đoạn cập nhật phủ trọn nút, sửa các tổng theo công thức ở trên rồi cộng lượng cập nhật vào nhãn.
- Nếu phải đi xuống, áp dụng nhãn của cha cho cả hai con theo độ dài hoặc hệ số của từng con, sau đó đưa nhãn của cha về $0$.
- Sau khi cập nhật một phần, tính lại các tổng của cha từ hai con. Khi hỏi một đoạn, cộng các trường tương ứng của những nút phủ đoạn.

### Chứng minh tính đúng đắn

Sau khi dựng cây, mỗi lá lưu đúng đóng góp ban đầu của nó và mỗi nút trong bằng tổng hai con. Khi một cập nhật phủ trọn nút, từng số hạng của các tổng thay đổi theo lượng cộng và hệ số tương ứng, nên công thức sửa nút cho đúng tổng mới. Nhãn ghi chính xác phần thay đổi đồng đều đang chờ truyền xuống con.

Đẩy nhãn chuyển phần thay đổi đó xuống đúng các nút con, đồng thời giữ nguyên tổng của đoạn cha. Do đó có thể cập nhật hoặc truy vấn ở mức sâu hơn với dữ liệu đã tính đủ các lần cộng. Mỗi truy vấn ghép các đoạn rời nhau phủ đúng tập vị trí được hỏi, nên thu được các tổng cần thiết. Phép chuyển đổi kết quả ở phần ý tưởng cho đúng giá trị đề yêu cầu.

### Độ phức tạp

Dựng cây trong $O(N)$. Mỗi thao tác mất $O(log(N+1))$ thời gian. Bộ nhớ là $O(N)$. Truy vấn còn dùng thuật toán Euclid, mất thêm $O(log(N+1))$ bước.

Tổng đoạn có trị tuyệt đối không vượt quá $N(Q+1)10^8$. Dùng số nguyên 64 bit cho tổng, nhãn và tích.
