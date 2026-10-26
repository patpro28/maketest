# Lời giải — HASHING002

Kiểm tra một độ dài $d$ bằng cách duyệt các cửa sổ từ trái sang phải. Với mỗi hash kép, chỉ lưu vị trí xuất hiện sớm nhất. Tại cửa sổ bắt đầu ở $j$, nếu vị trí sớm nhất cùng hash là $i$ và $j-i\ge d$ thì tìm được hai đoạn hợp lệ.

Lưu vị trí sớm nhất là đủ: nó có khoảng cách lớn nhất tới mọi vị trí đang xét. Nếu một cặp độ dài $d$ hợp lệ, cắt ngắn hai đoạn xuống cùng độ dài nhỏ hơn vẫn giữ được tính bằng nhau và không chồng lấn. Do đó tìm kiếm nhị phân đáp án trong khoảng từ $0$ đến $\lfloor n/2\rfloor$.

Độ phức tạp kỳ vọng $O(n\log n)$, bộ nhớ $O(n)$.

Lời giải tham khảo dùng hai modulo khác nhau để giảm xác suất va chạm hash. Hash là kỹ thuật xác suất; chứng minh tính đúng đắn ở trên giả sử các đoạn được so sánh không va chạm.
