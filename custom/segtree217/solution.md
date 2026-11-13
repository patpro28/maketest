### Ý tưởng

Gom các vị trí theo phần dư của $i-1$ khi chia cho $K$. Trong mỗi nhóm, giữ thứ tự chỉ số tăng dần. Nối các nhóm theo thứ tự phần dư từ $0$ đến $K-1$ để thu được một dãy mới.

Đặt $r=(i-1)mod K$. Mỗi nhóm có ít nhất $lfloor N/K
floor$ phần tử và $Nmod K$ nhóm đầu có thêm một phần tử. Vì thế, vị trí mới của $i$ tính từ $1$ là

$$rlfloor N/K
floor+min(r,Nmod K)+lfloor(i-1)/K
floor+1.$$

Tuyến bắt đầu tại $L$ nằm trong một nhóm và gồm $d=lfloor(R-L)/K
floor+1$ vị trí liên tiếp trong nhóm đó. Nếu $p$ là vị trí mới của $L$, mỗi thao tác trên tuyến trở thành một phép cộng đoạn hoặc hỏi tổng trên $[p,p+d-1]$.

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
