Đổi mỗi số dương thành $1$, số âm thành $-1$, số $0$ thành $0$. Khi đó tổng trên đoạn bằng số phần tử dương trừ số phần tử âm. Đoạn cân bằng khi và chỉ khi hai tổng tiền tố ở hai đầu bằng nhau. Khởi tạo tần suất tiền tố $0$ bằng $1$, hỏi tần suất tổng hiện tại trước khi tăng tần suất của nó.

Tính đúng đắn: Đẳng thức hiệu hai tổng tiền tố chuyển điều kiện của đoạn thành điều kiện của một tiền tố đứng trước. Bảng tần suất chứa đúng các tiền tố được phép ghép với đầu phải hiện tại, nên giá trị truy vấn đếm chính xác mọi đầu trái hợp lệ. Mỗi đoạn được đếm đúng một lần tại đầu phải của nó. Trả lời trước khi thêm tiền tố hiện tại bảo đảm không đếm đoạn rỗng.

Dùng bảng ánh xạ có thứ tự cho tần suất. Thời gian $O(N\log N)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho tổng tiền tố, khóa của bảng tần suất và đáp án. Trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$; số đoạn có thể đạt $N(N+1)/2=20000100000$.
