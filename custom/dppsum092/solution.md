Đặt tổng tiền tố $P$. Đoạn từ $j+1$ đến $r$ có độ dài chẵn khi và chỉ khi $j$ và $r$ cùng tính chẵn lẻ. Dùng hai bảng tần suất theo tính chẵn lẻ của chỉ số tiền tố. Khởi tạo tiền tố chỉ số $0$ ở bảng chẵn. Với $r$, hỏi giá trị $P_r-T$ ở bảng có cùng tính chẵn lẻ với $r$, rồi thêm $P_r$ vào bảng của $r$.

Tính đúng đắn: Đẳng thức hiệu hai tổng tiền tố chuyển điều kiện của đoạn thành điều kiện của một tiền tố đứng trước. Bảng tần suất chứa đúng các tiền tố được phép ghép với đầu phải hiện tại, nên giá trị truy vấn đếm chính xác mọi đầu trái hợp lệ. Mỗi đoạn được đếm đúng một lần tại đầu phải của nó. Việc chọn bảng theo tính chẵn lẻ bảo đảm đúng điều kiện độ dài. Trả lời trước khi thêm tiền tố hiện tại bảo đảm không đếm đoạn rỗng.

Dùng bảng ánh xạ có thứ tự cho tần suất. Thời gian $O(N\log N)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho tổng tiền tố, khóa của bảng tần suất và đáp án. Trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$; số đoạn có thể đạt $N(N+1)/2=20000100000$.
