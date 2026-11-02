Đặt tổng tiền tố $P$. Khi xét đầu phải $r$, đầu tiền tố $j=l-1$ hợp lệ khi $0\le j\le r-K$. Duy trì bảng tần suất ban đầu rỗng. Nếu $r\ge K$, thêm $P_{r-K}$ vào bảng trước khi hỏi tần suất của $P_r-T$. Các tiền tố đã thêm tiếp tục hợp lệ ở mọi bước sau.

Tính đúng đắn: Đẳng thức hiệu hai tổng tiền tố chuyển điều kiện của đoạn thành điều kiện của một tiền tố đứng trước. Bảng tần suất chứa đúng các tiền tố được phép ghép với đầu phải hiện tại, nên giá trị truy vấn đếm chính xác mọi đầu trái hợp lệ. Mỗi đoạn được đếm đúng một lần tại đầu phải của nó. Giới hạn chỉ số tiền tố tương đương đúng với giới hạn độ dài. Mỗi chỉ số được thêm và loại theo đúng thời điểm, kể cả khi nhiều chỉ số có cùng giá trị tổng.

Dùng bảng ánh xạ có thứ tự cho tần suất. Thời gian $O(N\log N)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho tổng tiền tố, khóa của bảng tần suất và đáp án. Trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$; số đoạn có thể đạt $N(N+1)/2=20000100000$.
