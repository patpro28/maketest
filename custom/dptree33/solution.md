# Lời giải — Nhánh cây dài nhất

### Ba câu hỏi để xây dựng lời giải

**Cần tính gì tại đỉnh $u$?** Gọi $dp[u]$ là độ dài đường đi xuống dài nhất từ $u$ đến một lá trong cây con, tính theo số cạnh.

**Một lá trả về gì?** Từ lá đến chính nó không đi qua cạnh nào, nên $dp[u]=0$.

**Cha dùng kết quả các con thế nào?** Nếu $u$ có con, một đường đi xuống phải chọn đúng một người con $v$. Nó đi qua cạnh $(u,v)$ rồi tiếp tục đường đi xuống tốt nhất từ $v$:

$$
dp[u]=1+\max_{v\text{ là con của }u}dp[v].
$$

Lấy lớn nhất vì chỉ đi theo một nhánh. Không cộng độ dài của các nhánh khác nhau.

### Thứ tự tính

Tính các lá trước, rồi những đỉnh ngay phía trên chúng, tiếp tục đến gốc.

Trong ví dụ đầu, các lá $2,4,5$ có kết quả $0$. Đỉnh $3$ có $dp[3]=1+\max(0,0)=1$. Đỉnh $1$ có $dp[1]=1+\max(dp[2],dp[3])=2$.

In kết quả của mọi đỉnh theo thứ tự nhãn. $dp[u]$ đo khoảng cách đi xuống từ $u$, không phải khoảng cách từ gốc đến $u$.

### Chứng minh tính đúng đắn

Trạng thái tại lá đúng theo định nghĩa độ dài.

Giả sử kết quả ở mọi người con của $u$ đã đúng. Mọi đường đi xuống từ $u$ phải bắt đầu qua đúng một cạnh $(u,v)$, sau đó là một đường từ $v$ xuống lá. Với người con đã chọn, phần tốt nhất có độ dài $dp[v]$. Thử tất cả các con và lấy lớn nhất vì thế cho đúng đường đi dài nhất từ $u$. Quy nạp từ lá lên chứng minh kết quả tại mọi đỉnh.

### Độ phức tạp và lưu ý cài đặt

Thời gian $O(N)$, bộ nhớ $O(N)$. Kết quả lớn nhất bằng $N-1$.

Có thể khởi tạo tất cả $dp[u]=0$. Khi một người con $v$ đã có kết quả, cập nhật $dp[u]=\max(dp[u],1+dp[v])$. Lá không nhận cập nhật nào nên tự giữ giá trị $0$.

Lưu cha khi duyệt để không đi ngược lên cha như thể đó là con. Xử lý danh sách duyệt theo thứ tự ngược để các kết quả ở con luôn sẵn sàng. Cách làm không đệ quy xử lý được cây dây dài.
