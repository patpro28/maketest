Đặt tổng tiền tố $P$ và phần dư chuẩn hóa $d_i=((P_i\bmod M)+M)\bmod M$. Điều kiện tổng đoạn có phần dư $C$ tương đương phần dư của tiền tố trước đó bằng $(d_r-C+M)\bmod M$. Khởi tạo tần suất phần dư $0$ bằng $1$. Mỗi bước hỏi phần dư cần tìm, rồi mới thêm phần dư hiện tại.

Tính đúng đắn: Đẳng thức hiệu hai tổng tiền tố chuyển điều kiện của đoạn thành điều kiện của một tiền tố đứng trước. Bảng tần suất chứa đúng các tiền tố được phép ghép với đầu phải hiện tại, nên giá trị truy vấn đếm chính xác mọi đầu trái hợp lệ. Mỗi đoạn được đếm đúng một lần tại đầu phải của nó. Trả lời trước khi thêm tiền tố hiện tại bảo đảm không đếm đoạn rỗng.

Thời gian $O(N+M)$, bộ nhớ $O(M)$ cho mảng tần suất phần dư.

Dùng số nguyên 64 bit cho tổng tiền tố, khóa của bảng tần suất và đáp án. Trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$; số đoạn có thể đạt $N(N+1)/2=20000100000$. Chuẩn hóa phần dư khi tổng âm; không dùng trực tiếp phần dư âm làm chỉ số mảng.
