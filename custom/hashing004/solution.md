# Lời giải — HASHING004

Chuẩn bị hash tiền tố kép. Với mỗi truy vấn, tìm kiếm nhị phân độ dài tiền tố chung $t$ trong khoảng từ $0$ đến độ dài đoạn ngắn hơn.

Nếu $t$ bằng độ dài đoạn ngắn hơn, so sánh hai độ dài: bằng nhau cho kết quả `=`, còn đoạn ngắn hơn đứng trước. Ngược lại, so sánh trực tiếp ký tự ở vị trí $t+1$ của hai đoạn. Đây chính là vị trí khác nhau đầu tiên, nên quyết định thứ tự từ điển.

Độ phức tạp $O(n+q\log(n+1))$, bộ nhớ $O(n)$.

Lời giải tham khảo dùng hai modulo khác nhau để giảm xác suất va chạm hash. Hash là kỹ thuật xác suất; chứng minh tính đúng đắn ở trên giả sử các đoạn được so sánh không va chạm.
