Đặt tổng tiền tố $P$. Với đầu phải $r$, chỉ số tiền tố hợp lệ nằm trong $[\max(0,r-K),r-1]$. Khởi tạo bảng chứa $P_0$ một lần. Trước khi hỏi ở bước $r$, loại tiền tố chỉ số $r-K-1$ nếu chỉ số này không âm. Cộng tần suất của $P_r-T$, rồi thêm $P_r$ cho bước kế tiếp. Khi loại một giá trị, chỉ giảm tần suất đi $1$ vì các chỉ số khác có thể có cùng giá trị.

Tính đúng đắn: Đẳng thức hiệu hai tổng tiền tố chuyển điều kiện của đoạn thành điều kiện của một tiền tố đứng trước. Bảng tần suất chứa đúng các tiền tố được phép ghép với đầu phải hiện tại, nên giá trị truy vấn đếm chính xác mọi đầu trái hợp lệ. Mỗi đoạn được đếm đúng một lần tại đầu phải của nó. Giới hạn chỉ số tiền tố tương đương đúng với giới hạn độ dài. Mỗi chỉ số được thêm và loại theo đúng thời điểm, kể cả khi nhiều chỉ số có cùng giá trị tổng. Trả lời trước khi thêm tiền tố hiện tại bảo đảm không đếm đoạn rỗng.

Dùng bảng ánh xạ có thứ tự cho tần suất. Thời gian $O(N\log N)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho tổng tiền tố, khóa của bảng tần suất và đáp án. Trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$; số đoạn có thể đạt $N(N+1)/2=20000100000$.
