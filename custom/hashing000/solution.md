# Lời giải — HASHING000

Gọi $H(l,r)$ là hash kép của đoạn nửa mở $S[l..r)$. Hash tiền tố và bảng lũy thừa cho phép lấy mỗi hash trong $O(1)$.

Với độ dài $d$, đếm tần suất hash của tất cả $n-d+1$ cửa sổ. Độ dài này hợp lệ khi có tần suất ít nhất $k$. Việc đếm theo vị trí bắt đầu tự động bao gồm các lần xuất hiện chồng lấn.

Nếu một xâu độ dài $d$ xuất hiện ít nhất $k$ lần, tiền tố độ dài nhỏ hơn của nó cũng xuất hiện tại ít nhất $k$ vị trí. Vì vậy có thể tìm kiếm nhị phân trên độ dài, với đáp án ban đầu bằng $0$.

Độ phức tạp kỳ vọng $O(n\log n)$, bộ nhớ $O(n)$. Trường hợp $k=1$ cho đáp án $n$.

Lời giải tham khảo dùng hai modulo khác nhau để giảm xác suất va chạm hash. Hash là kỹ thuật xác suất; chứng minh tính đúng đắn ở trên giả sử các đoạn được so sánh không va chạm.
