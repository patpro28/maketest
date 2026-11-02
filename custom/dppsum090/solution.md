Đặt $P_0=0$, $P_i=P_{i-1}+A_i$. Tổng đoạn $[l,r]$ bằng $0$ khi và chỉ khi $P_{l-1}=P_r$. Duy trì tần suất các tổng tiền tố trước vị trí hiện tại. Khởi tạo tần suất của $P_0=0$ bằng $1$. Với mỗi $P_r$, cộng tần suất của $P_r$ vào đáp án rồi mới tăng tần suất đó.

Tính đúng đắn: Đẳng thức hiệu hai tổng tiền tố chuyển điều kiện của đoạn thành điều kiện của một tiền tố đứng trước. Bảng tần suất chứa đúng các tiền tố được phép ghép với đầu phải hiện tại, nên giá trị truy vấn đếm chính xác mọi đầu trái hợp lệ. Mỗi đoạn được đếm đúng một lần tại đầu phải của nó. Trả lời trước khi thêm tiền tố hiện tại bảo đảm không đếm đoạn rỗng.

Dùng bảng ánh xạ có thứ tự cho tần suất. Thời gian $O(N\log N)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho tổng tiền tố, khóa của bảng tần suất và đáp án. Trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$; số đoạn có thể đạt $N(N+1)/2=20000100000$.
