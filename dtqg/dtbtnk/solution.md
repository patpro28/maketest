## Đếm bậc không vượt h

Gọi $F(h)$ là số dãy con khác nhau tạo thành biểu thức ngoặc đúng có bậc không vượt $h$, kể cả xâu rỗng. Đáp án cần tìm là

$$F(k)-F(k-1)\pmod{111539786}.$$

Xâu rỗng xuất hiện ở cả hai vế nên tự triệt tiêu. Không cần lưu đồng thời độ sâu lớn nhất và độ cân bằng.

## Trạng thái theo độ cân bằng

Khi đọc một tiền tố của $S$, đặt $dp[b]$ là số xâu ngoặc khác nhau có thể lấy từ tiền tố, mọi tiền tố của xâu được lấy đều có độ cân bằng trong $[0,h]$, và độ cân bằng cuối bằng $b$.

Độ cân bằng là số ngoặc mở trừ số ngoặc đóng. Khởi tạo $dp[0]=1$ cho xâu rỗng. Ngoặc mở tăng cân bằng một, ngoặc đóng giảm cân bằng một.

Nếu chỉ cộng các cách nối ký tự, cùng một xâu có thể bị đếm nhiều lần vì chọn vị trí khác nhau. Cần trừ đúng các xâu đã được tạo tại lần xuất hiện trước của cùng ký tự.

## Loại trùng bằng hai bản chụp

Giữ $lastOpen[b]$ là giá trị $dp[b]$ ngay trước lần đọc dấu `(` gần nhất; tương tự $lastClose[b]$. Nếu ký tự chưa xuất hiện thì bản chụp bằng $0$.

Khi đọc `(`, khởi tạo $next=dp$ cho các xâu không dùng ký tự mới. Với $1\le b\le h$:

$$next[b]=dp[b]+dp[b-1]-lastOpen[b-1].$$

Sau đó gán $lastOpen=dp$ của lớp cũ rồi thay $dp=next$.

Khi đọc `)`, với $0\le b<h$:

$$next[b]=dp[b]+dp[b+1]-lastClose[b+1].$$

Lưu $lastClose=dp$ của lớp cũ rồi thay lớp. Những ô không có phép nối giữ nguyên. Mỗi phép cộng/trừ lấy modulo và chuẩn hóa về miền không âm.

Sau toàn bộ xâu, $F(h)=dp[0]$.

## Vì sao phép trừ đúng?

Xét ký tự mới $c$ và lần xuất hiện trước của nó tại vị trí $j$. Những xâu mới có dạng $Xc$, với $X$ được lấy trước vị trí hiện tại và có độ cân bằng cần thiết. Phép nối một ký tự cố định là đơn ánh trên nội dung xâu $X$.

Một xâu $Xc$ đã tồn tại trước vị trí hiện tại khi và chỉ khi $X$ có thể được lấy trước $j$: nếu đã có cách lấy $Xc$ trước đó, có thể dời ký tự cuối $c$ tới lần xuất hiện gần nhất $j$ mà vẫn giữ thứ tự; chiều ngược lại dùng ngay vị trí $j$. Bản chụp trước $j$ đếm đúng các xâu $X$ này.

Các ràng buộc cân bằng phụ thuộc nội dung xâu, nên phép trừ vẫn đúng khi chỉ giữ cân bằng trong $[0,h]$. Do đó mỗi lượt giữ đúng tập xâu khác nhau. Cuối cùng cân bằng $0$ và không âm trên mọi tiền tố tương đương biểu thức ngoặc đúng; chặn trên $h$ tương đương bậc không vượt $h$.

## Độ phức tạp

Hai lần tính có thời gian $O(n(k+1))$ và bộ nhớ $O(k+1)$. Với $n\le4000$, $k\le2000$, tổng số ô được duyệt trong hai lần không vượt $2n(k+1)\le16008000$.

Không được hiểu dãy con là đoạn liên tiếp, và không đếm theo số bộ vị trí được chọn.
