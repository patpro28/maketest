# SEGTREE112 — Lời giải

### Ý tưởng

Lưu số trạm hoạt động trên mỗi nút. Tìm trạm hoạt động cuối cùng trong $[1,p]$ bằng cách ưu tiên con phải, và trạm hoạt động đầu tiên trong $[p,N]$ bằng cách ưu tiên con trái. Bỏ qua các nút có tổng bằng $0$. So sánh hai ứng viên, chọn bên trái khi hòa.

### Chứng minh tính đúng đắn

Trong các trạm không vượt $p$, trạm có chỉ số lớn nhất gần $p$ nhất. Tương tự, ứng viên gần nhất bên phải có chỉ số nhỏ nhất. Do đó đáp án thuộc hai ứng viên tìm được, và phép so sánh khoảng cách cùng quy tắc phá hòa cho kết quả đúng.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
