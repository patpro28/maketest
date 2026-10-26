# SEGTREE171 — Lời giải

### Ý tưởng

Lưu GCD trên mỗi nút. Duy trì GCD $g$ của phần đã nhận, ban đầu bằng $0$. Duyệt các nút từ trái sang phải kể từ $l$. Với nút nằm hoàn toàn trong phần cần xét, thử $g\prime=\gcd(g,\mathrm{gcd}_{node})$. Nếu $g\prime\ge G$, nhận toàn bộ nút. Nếu không, đi xuống để tìm phần tử đầu tiên khiến điều kiện sai. Trả về vị trí trước phần tử đó, hoặc $N$ nếu không gặp.

### Chứng minh tính đúng đắn

GCD của một đoạn không rỗng chỉ giữ nguyên hoặc giảm khi thêm phần tử. Do đó sau khi điều kiện sai, kéo dài thêm cũng không thể đúng lại. Nút được nhận có GCD sau ghép đạt ngưỡng nên toàn bộ tiền tố bên trong cũng đạt. Đi xuống nút đầu tiên không nhận được tìm chính xác ranh giới cần trả về.

### Độ phức tạp

$O(N\log V+Q\log N\log V)$ thời gian theo chặn trên của phép tính GCD, với $V=10^9$; $O(N)$ bộ nhớ.
