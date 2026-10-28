# SEGTREE123 — Lời giải

### Ý tưởng

Lá giá trị x lưu số lần x xuất hiện trong cửa sổ hiện tại; nút lưu tổng tần suất. Khởi tạo cửa sổ đầu, sau đó mỗi lần trượt giảm tần suất phần tử rời đi và tăng tần suất phần tử mới. Tìm phần tử nhỏ thứ $\lfloor(W+1)/2\rfloor$ bằng cách so sánh thứ hạng với tổng con trái và trừ tổng đó khi sang phải.

### Chứng minh tính đúng đắn

Tần suất sau hai cập nhật chính xác là tần suất trong cửa sổ mới. Các giá trị ở nhánh trái nhỏ hơn mọi giá trị ở nhánh phải, nên quy tắc đi xuống tìm đúng phần tử theo thứ hạng, kể cả khi có phần tử trùng nhau. Thứ hạng được chọn đúng theo định nghĩa trung vị dưới.

### Độ phức tạp

$O(M+N\log M)$ thời gian và $O(M+N)$ bộ nhớ, gồm cả dãy đầu vào.
