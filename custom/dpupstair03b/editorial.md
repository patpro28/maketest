# DPUPSTAIR03B — Hướng dẫn giải

## Subtask 1: Liệt kê các cách đi

Với $n\le20$, dùng đệ quy thử từng bước $1$ hoặc $2$ bậc. Không thử bước $2$ từ bậc trơn và không đi quá bậc $n$. Theo dõi đại lượng cần đếm; khi đến bậc $n$, chỉ nhận cách có bộ đếm bằng $m$. Khởi tạo bộ đếm bằng $0$ tại bậc $1$.

## Subtask 2: Không có sự kiện được đếm

Khi $m=0$, không được đặt chân lên bậc trơn nào sau khi xuất phát. Dùng DP một chiều: khởi tạo $f[1]=1$; khi chuyển sang bậc mới, chỉ chuyển nếu bậc đến không trơn và bước đi hợp lệ. Bậc $1$ trơn vẫn cho phép bước lên $1$ bậc, nhưng không cho phép nhảy $2$ bậc.

## Subtask 3: Quy hoạch động

Đặt $dp[i][j]$ là số cách đi từ bậc $1$ đến bậc $i$ và đã đặt chân lên đúng $j$ bậc trơn, không tính bậc xuất phát $1$.

Khởi tạo $dp[1][0]=1$; các trạng thái khác bằng $0$. Duyệt $i$ tăng dần, với mỗi $0\le j\le m$:

Đặt $b[t]=1$ nếu bậc $t$ bị trơn, ngược lại $b[t]=0$.

- Đi $1$ bậc: cộng $dp[i][j]$ vào $dp[i+1][j+b[i+1]]$ nếu $i+1\le n$ và chỉ số đếm mới không vượt $m$.
- Nhảy $2$ bậc: cộng $dp[i][j]$ vào $dp[i+2][j+b[i+2]]$ nếu $i+2\le n$, $b[i]=0$ và chỉ số đếm mới không vượt $m$.

Chỉ cộng thông tin của **bậc đến**. Bậc xuất phát quyết định có được nhảy $2$ bậc hay không. Khởi tạo không cộng $b[1]$; bậc $n$ được tính qua lần chuyển đến nó.

Mọi phép cộng lấy modulo $10^9+7$. Đáp án là $dp[n][m]$. Không cần lưu trạng thái có bộ đếm lớn hơn $m$, vì bộ đếm không bao giờ giảm.

## Chứng minh

Trạng thái ban đầu biểu diễn đúng một cách chưa di chuyển. Mỗi lần chuyển chỉ đặt chân lên đúng bậc đến. Vì thế tăng bộ đếm theo trạng thái trơn của bậc đến là chính xác. Quy tắc hạn chế nhảy được kiểm tra trên bậc xuất phát, và bậc $1$ không được đưa vào bộ đếm. Mỗi đường đi không rỗng có duy nhất một bước cuối, nên các phép chuyển không bỏ sót hoặc đếm trùng. Theo thứ tự tăng của bậc, tất cả trạng thái đều được tính đúng, vì vậy $dp[n][m]$ là đáp án.

## Độ phức tạp và lời giải tham khảo

Thời gian $O(n(m+1))$. Nếu lưu toàn bộ bảng, bộ nhớ là $O(n(m+1))$.

Lời giải `sol/correct.cpp` chỉ lưu ba hàng DP theo chỉ số bậc modulo $3$, vì mỗi bước tăng nhiều nhất $2$ bậc. Chỉ xóa hàng hiện tại sau khi chuyển hết các trạng thái; không xóa các đóng góp đã có ở hai hàng kế tiếp. Bộ nhớ cho DP là $O(m+1)$; cộng mảng đánh dấu bậc trơn, tổng bộ nhớ là $O(n+m)$.

Lời giải `sol/backward.cpp` dùng bảng đầy đủ theo chiều ngược: đếm số cách từ bậc $i$ đến $n$ với đúng $j$ sự kiện được tính thêm. Khởi tạo $ways[n][0]=1$, rồi duyệt từ $n-1$ về $1$. Đáp án là $ways[1][m]$.
