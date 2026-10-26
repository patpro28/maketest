# Lời giải — HASHING007

Xây dựng bốn bảng, lần lượt là bảng gốc và các bảng xoay $90$, $180$, $270$ độ theo chiều kim đồng hồ. Với mỗi bảng, lưu hash tiền tố hai chiều theo hai modulo, dùng cơ số hàng và cột riêng biệt.

Với một modulo, công thức dựng là $F[i][j]=a[i][j]+X F[i-1][j]+Y F[i][j-1]-XY F[i-1][j-1]$. Công thức bao hàm loại trừ cho phép lấy hash hình chữ nhật đã chuẩn hóa trong $O(1)$.

Dùng tọa độ bắt đầu từ $0$. Một hình vuông cạnh $d$ có góc trên trái $(u,v)$ trong bảng cao $H$, rộng $W$ sẽ chuyển thành hình vuông góc trên trái $(v,H-u-d)$ trong bảng xoay cao $W$, rộng $H$. Sau mỗi lần chuyển phải hoán đổi hai kích thước.

Giữ nguyên hash của mảnh thứ nhất trong bảng gốc. Lấy hash mảnh thứ hai tại tọa độ tương ứng trong cả bốn bảng, trả lời `YES` nếu có hash bằng nhau. Các mảnh đều cùng kích thước nên cách chuẩn hóa tương thích.

Độ phức tạp $O(RC+q)$, bộ nhớ $O(RC)$. Cần kiểm tra cả bảng không vuông và phép xoay $270$ độ để tránh sai công thức tọa độ.

Lời giải tham khảo dùng hai modulo khác nhau để giảm xác suất va chạm hash. Hash là kỹ thuật xác suất; chứng minh tính đúng đắn ở trên giả sử các đoạn được so sánh không va chạm.
