# SEGTREE173 — Lời giải

### Ý tưởng

Đặt $L=10^{18}$ và dùng dấu vượt giới hạn $C=L+1$. Mỗi nút lưu LCM đã chặn tại $C$. Nếu một đầu vào đã là $C$, kết quả ghép cũng là $C$. Với các giá trị chưa chặn, đặt $u=a/\gcd(a,b)$; nếu $u>L/b$ thì trả về $C$, nếu không trả về $u\cdot b$. Khi tìm kiếm, tích lũy LCM từ giá trị trung hòa $1$, nhận cả nút nếu LCM sau ghép không vượt $B$, còn lại đi xuống tìm phần tử đầu tiên làm vượt ngưỡng.

### Chứng minh tính đúng đắn

LCM không giảm khi thêm số nguyên dương. Giá trị lớn hơn L có thể coi là một trạng thái vượt ngưỡng vì mọi truy vấn đều có B không vượt L, và ghép thêm không thể làm LCM giảm. Phép chia trước khi nhân tránh tràn số. Mỗi nút được nhận có mọi tiền tố bên trong hợp lệ; nút đầu tiên không nhận được chứa ranh giới đầu tiên vượt ngưỡng. Vị trí ngay trước ranh giới là đáp án lớn nhất.

### Độ phức tạp

$O(N\log L+Q\log N\log L)$ thời gian theo chặn trên của phép tính GCD, $L=10^{18}$; $O(N)$ bộ nhớ.
