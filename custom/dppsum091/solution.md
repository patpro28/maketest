Đặt $P_0=0$, $P_i=P_{i-1}+A_i$. Đoạn $[l,r]$ có tổng $T$ khi và chỉ khi $P_{l-1}=P_r-T$. Khởi tạo bảng tần suất chứa $P_0=0$ một lần. Với mỗi $r$, cộng tần suất của $P_r-T$ rồi mới thêm $P_r$ vào bảng.

Tính đúng đắn: Đẳng thức hiệu hai tổng tiền tố chuyển điều kiện của đoạn thành điều kiện của một tiền tố đứng trước. Bảng tần suất chứa đúng các tiền tố được phép ghép với đầu phải hiện tại, nên giá trị truy vấn đếm chính xác mọi đầu trái hợp lệ. Mỗi đoạn được đếm đúng một lần tại đầu phải của nó. Trả lời trước khi thêm tiền tố hiện tại bảo đảm không đếm đoạn rỗng.

Dùng bảng ánh xạ có thứ tự cho tần suất. Thời gian $O(N\log N)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho tổng tiền tố, khóa của bảng tần suất và đáp án. Trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$; số đoạn có thể đạt $N(N+1)/2=20000100000$.
