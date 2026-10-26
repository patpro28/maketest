# Lời giải — HASHING008

Mỗi nút segment tree lưu độ dài, hash xuôi và hash ngược của đoạn. Với hai đoạn liên tiếp $A,B$, hash xuôi của $AB$ là $H(A)\cdot B_0^{|B|}+H(B)$; hash ngược là $H_{rev}(B)\cdot B_0^{|A|}+H_{rev}(A)$. Thực hiện công thức trên cho hai modulo.

Đây là phép ghép có tính kết hợp vì mô tả đúng phép nối xâu. Nút rỗng có độ dài và hai hash bằng $0$, là phần tử trung hòa. Khi truy vấn, phải giữ đúng thứ tự các đoạn; không thể ghép tùy ý như phép cộng.

Cập nhật thay một nút lá rồi tính lại các tổ tiên. Với truy vấn, ghép các nút phủ đoạn và so sánh hash xuôi với hash ngược. Hai hash bằng nhau cho biết đoạn đối xứng, dưới giả thiết không có va chạm.

Dựng cây $O(n)$, mỗi thao tác $O(\log n)$, bộ nhớ $O(n)$.

Lời giải tham khảo dùng hai modulo khác nhau để giảm xác suất va chạm hash. Hash là kỹ thuật xác suất; chứng minh tính đúng đắn ở trên giả sử các đoạn được so sánh không va chạm.
