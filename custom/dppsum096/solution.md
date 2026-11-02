Đặt tổng tiền tố $P$. Độ dài đoạn là $r-j$, nên chỉ số tiền tố hợp lệ thỏa $r-R\le j\le r-L$ và $j\ge0$. Ban đầu bảng rỗng. Tại bước $r$, thêm $P_{r-L}$ nếu $r\ge L$; loại $P_{r-R-1}$ nếu chỉ số không âm. Sau đó hỏi tần suất của $P_r-T$. Việc thêm và loại theo chỉ số, mỗi lần thay đổi đúng một đơn vị tần suất.

Tính đúng đắn: Đẳng thức hiệu hai tổng tiền tố chuyển điều kiện của đoạn thành điều kiện của một tiền tố đứng trước. Bảng tần suất chứa đúng các tiền tố được phép ghép với đầu phải hiện tại, nên giá trị truy vấn đếm chính xác mọi đầu trái hợp lệ. Mỗi đoạn được đếm đúng một lần tại đầu phải của nó. Giới hạn chỉ số tiền tố tương đương đúng với giới hạn độ dài. Mỗi chỉ số được thêm và loại theo đúng thời điểm, kể cả khi nhiều chỉ số có cùng giá trị tổng.

Dùng bảng ánh xạ có thứ tự cho tần suất. Thời gian $O(N\log N)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho tổng tiền tố, khóa của bảng tần suất và đáp án. Trị tuyệt đối của tổng có thể đạt $2\cdot10^{14}$; số đoạn có thể đạt $N(N+1)/2=20000100000$.
