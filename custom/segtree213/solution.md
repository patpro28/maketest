### Ý tưởng

Mỗi nút lưu $S=sum A_i$ và $T=sum iA_i$ trên đoạn của nó. Cả hai trường đều ghép được bằng phép cộng.

Với nút $[l,r]$, cộng $X$ trên cả đoạn làm $S$ tăng $X(r-l+1)$ và làm $T$ tăng $Xsum_{i=l}^{r}i$. Tính tổng chỉ số bằng hiệu hai số tam giác $F(r)-F(l-1)$ với $F(t)=t(t+1)/2$.

Sau khi lấy $S,T$ trên đoạn hỏi $[L,R]$, in $T-(L-1)S$. Công thức này đổi hệ số tuyệt đối $i$ thành hệ số $i-L+1$.

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

Đặt $U=(Q+1)1000$. Trị tuyệt đối của $T$ không vượt quá $U N(N+1)/2$ và trị tuyệt đối của $(L-1)S$ không vượt quá $U N(N-1)$. Hai cận này đều nằm trong miền số nguyên có dấu 64 bit.
