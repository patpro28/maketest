### Thông tin lưu tại mỗi nút

Dùng segment tree có lazy propagation. Mỗi nút lưu mực nước thấp nhất của đoạn và lượng cộng đang chờ truyền xuống các nút con. Ghép hai đoạn liền nhau bằng cách lấy giá trị nhỏ hơn giữa hai kết quả.

### Cập nhật và truy vấn

Cộng cùng $x$ vào cả đoạn làm giá trị nhỏ nhất tăng đúng $x$. Nếu đoạn cập nhật phủ trọn một nút, tăng giá trị nhỏ nhất và nhãn chờ của nút đó thêm $x$.

Khi cần đi xuống, cộng nhãn đang chờ vào hai nút con rồi đặt nhãn của nút cha về $0$. Sau khi cập nhật một phần đoạn, ghép hai kết quả con để khôi phục giá trị nhỏ nhất ở nút cha.

Truy vấn tách đoạn cần hỏi thành các đoạn do những nút của cây quản lý, sau đó lấy giá trị nhỏ nhất trong các kết quả. Khi dùng kết quả trung hòa cho đoạn rỗng, chọn $+\infty$.

### Chứng minh tính đúng đắn

Tại lá, giá trị nhỏ nhất là mực nước của hồ tương ứng. Phép ghép lấy đúng giá trị nhỏ nhất của hợp hai đoạn. Khi cập nhật phủ trọn một nút, cộng $x$ vào giá trị nhỏ nhất phản ánh đúng thay đổi của cả đoạn. Đẩy nhãn xuống duy trì giá trị của từng hồ khi các thao tác tiếp theo cần đi vào một nút con. Do đó, các nút được dùng để trả lời luôn cung cấp đúng giá trị nhỏ nhất trên đoạn của chúng. Những đoạn này phủ đúng đoạn truy vấn, nên lấy min của chúng cho kết quả cần tìm.

### Độ phức tạp

Dựng cây trong $O(n)$ thời gian. Mỗi thao tác tốn $O(\log(n+1))$ thời gian. Bộ nhớ là $O(n)$. Dùng số nguyên 64 bit cho giá trị và nhãn cộng vì nhiều cập nhật có thể tích lũy tại một vị trí.
