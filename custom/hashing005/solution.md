# Lời giải — HASHING005

Đặt $L$ là tổng độ dài và $s$ là độ dài xâu ngắn nhất. Đưa một xâu ngắn nhất lên đầu danh sách và xây dựng hash tiền tố kép cho mọi xâu.

Để kiểm tra độ dài $d$, lấy tập hash các đoạn dài $d$ trong xâu đầu làm tập ứng viên. Với mỗi xâu tiếp theo, tạo tập mới gồm những hash vừa xuất hiện trong xâu đó, vừa nằm trong tập ứng viên hiện tại. Thay tập ứng viên bằng tập mới. Dùng tập hợp thay vì đếm từng lần xuất hiện để một xâu không đóng góp nhiều lần cho cùng ứng viên.

Sau khi xử lý tất cả các xâu, tập còn phần tử khi và chỉ khi tồn tại đoạn chung độ dài $d$, dưới giả thiết không có va chạm hash. Tính khả thi đơn điệu theo độ dài, nên tìm kiếm nhị phân từ $0$ đến $s$.

Độ phức tạp kỳ vọng $O(L\log(s+1))$, bộ nhớ $O(L)$.

Lời giải tham khảo dùng hai modulo khác nhau để giảm xác suất va chạm hash. Hash là kỹ thuật xác suất; chứng minh tính đúng đắn ở trên giả sử các đoạn được so sánh không va chạm.
