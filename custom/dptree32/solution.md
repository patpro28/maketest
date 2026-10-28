# Lời giải — Kho tài nguyên của một nhánh

### Ba câu hỏi để xây dựng lời giải

**Cần tính gì tại đỉnh $u$?** Gọi $dp[u]$ là tổng tài nguyên trong cây con gốc $u$, bao gồm chính $u$.

**Một lá trả về gì?** Lá không có đỉnh nào phía dưới, nên $dp[u]=A_u$.

**Cha dùng kết quả các con thế nào?** Cây con của $u$ gồm chính $u$ và các cây con của những người con. Vì thế:

$$
dp[u]=A_u+\sum_{v\text{ là con của }u}dp[v].
$$

Phải cộng $dp[v]$, không chỉ cộng $A_v$, vì một người con có thể quản lý cả một nhánh nhiều đỉnh.

### Thứ tự tính

Để tính $dp[u]$, trước hết tính xong các người con. Có thể hình dung quá trình như sau:

1. Đi xuống để xử lý từng cây con.
2. Nhận tổng tài nguyên của mỗi cây con.
3. Cộng các tổng đó với tài nguyên tại $u$.

Trong ví dụ đầu của đề, các lá trả về $dp[2]=3$, $dp[4]=7$, $dp[5]=11$. Khi đó $dp[3]=5+7+11=23$, rồi $dp[1]=2+3+23=28$.

Cần in $dp[1],dp[2],\ldots,dp[N]$ theo nhãn đỉnh, không theo thứ tự duyệt.

### Chứng minh tính đúng đắn

Tại lá, công thức trả về đúng tài nguyên của đỉnh đó.

Giả sử các kết quả ở con đều đúng. Những cây con của các con không có đỉnh chung. Chúng cùng với đỉnh $u$ tạo thành toàn bộ cây con của $u$. Do đó cộng tài nguyên tại $u$ với các tổng của con sẽ tính đủ mỗi đỉnh đúng một lần. Theo quy nạp từ lá lên gốc, mọi giá trị $dp[u]$ đều đúng.

### Độ phức tạp và lưu ý cài đặt

Mỗi đỉnh đóng góp vào cha đúng một lần, nên thời gian $O(N)$ và bộ nhớ $O(N)$.

Tổng có thể đạt $2\cdot10^{14}$, cần số nguyên 64 bit. Khởi tạo $dp[u]=A_u$ để không quên tài nguyên của chính đỉnh.

Với cây sâu, có thể duyệt bằng vòng lặp để lưu cha và một danh sách thứ tự thăm. Cha luôn đứng trước con trong danh sách; xử lý ngược danh sách sẽ bảo đảm các con xong trước cha, đồng thời tránh phụ thuộc ngăn xếp đệ quy.
