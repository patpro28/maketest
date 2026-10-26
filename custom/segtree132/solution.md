# SEGTREE132 — Lời giải

### Ý tưởng

Nút lưu tổng. Gọi tổng toàn dãy là $T$. Nếu $T=0$, trả về $(1,2)$; nếu $T$ không chia hết cho $3$, thất bại. Với $T>0$, đi xuống cây tìm tiền tố đầu tiên có tổng ít nhất $T/3$ và $2T/3$. Kiểm tra tổng tại hai vị trí phải bằng đúng ngưỡng và vị trí thứ hai nhỏ hơn $N$. Có thể kiểm tra bằng truy vấn tổng tiền tố hoặc kiểm tra lượng còn thiếu ngay tại lá tìm được.

### Chứng minh tính đúng đắn

Vì các phần tử không âm, tổng tiền tố không giảm. Mọi cách chia đều cần hai tổng tiền tố bằng chính xác hai ngưỡng. Hai vị trí đầu tiên đạt các ngưỡng, nếu đạt đúng, là các lựa chọn nhỏ nhất. Với ngưỡng dương khác nhau, vị trí thứ nhất luôn đứng trước vị trí thứ hai. Kiểm tra vị trí thứ hai chưa tới cuối bảo đảm cả ba đoạn không rỗng. Khi tổng bằng 0, mọi phần tử đều bằng 0 nên cặp (1,2) là tối ưu.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.
