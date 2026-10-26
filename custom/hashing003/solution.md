# Lời giải — HASHING003

Với mỗi cửa sổ dài $m$, tìm độ dài $t$ của tiền tố chung dài nhất giữa cửa sổ và mẫu bằng tìm kiếm nhị phân kết hợp hash kép.

Nếu $t=m$, hai xâu bằng hoàn toàn nên không tính. Nếu $t<m$, vị trí kế tiếp là vị trí khác nhau đầu tiên. Bỏ qua đúng vị trí đó và so sánh hai hậu tố còn lại bằng hash. Chỉ đếm cửa sổ khi hai hậu tố bằng nhau.

Điều kiện này vừa cần vừa đủ: tiền tố đã bằng nhau, một ký tự được xác định là khác nhau, và toàn bộ phần còn lại bằng nhau. Hậu tố rỗng được xem là bằng nhau, bao gồm trường hợp sai ở ký tự cuối.

Độ phức tạp $O(n+m+n\log(m+1))$, bộ nhớ $O(n+m)$.

Lời giải tham khảo dùng hai modulo khác nhau để giảm xác suất va chạm hash. Hash là kỹ thuật xác suất; chứng minh tính đúng đắn ở trên giả sử các đoạn được so sánh không va chạm.
