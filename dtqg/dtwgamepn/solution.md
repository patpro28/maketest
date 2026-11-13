## Xử lý đường đi đối xứng

Đặt $L=m+n-1$ và $\ell=|S|$. Nếu $\ell>L$, không có đường thắng cuộc. Nếu một trong hai đầu mút bị cấm hoặc hai ký tự đầu mút khác nhau, đáp án cũng bằng $0$.

Dùng hai con trỏ đi từ hai đầu đường đi vào giữa. Sau $t$ bước của mỗi con trỏ, các cột được suy ra từ các hàng $x,u$: chúng lần lượt bằng $t-x$ và $L-1-t-u$, với chỉ số từ $0$. Chỉ mở rộng tới hai ô không cấm có cùng ký tự. Các điều kiện này kiểm tra tính đối xứng.

Gọi $X$ là xâu đọc từ đầu đến vị trí của con trỏ thứ nhất, đã bao gồm ký tự ở vị trí đó. Tại lúc kết thúc, toàn bộ xâu có dạng:

- $X+\operatorname{rev}(X)$ nếu $L$ chẵn;
- $X+\operatorname{rev}(X\text{ bỏ ký tự cuối})$ nếu $L$ lẻ.

Vấn đề còn lại là lưu ít thông tin về $X$ nhưng vẫn xác định được toàn bộ xâu chứa $S$ hay không.

## Bộ tự động cho hai mẫu

Đặt $R=\operatorname{rev}(S)$. Nếu $X$ đã chứa $S$ hoặc $R$ thì đường đối xứng hoàn chỉnh chắc chắn chứa $S$: trường hợp chứa $R$ sẽ cho $S$ ở nửa phản chiếu.

Dùng một trạng thái hấp thụ `found` cho trường hợp đã gặp một trong hai mẫu. Các trạng thái khác là những tiền tố thực sự khác nhau của $S$ hoặc $R$, bao gồm xâu rỗng. Trạng thái $q$ biểu diễn hậu tố dài nhất của $X$ thuộc tập tiền tố này. Số trạng thái không vượt $2\ell$.

Với mỗi trạng thái biểu diễn xâu $W$ và ký tự $c$:

1. Nếu $W+c$ chứa $S$ hoặc $R$, chuyển sang `found`.
2. Nếu không, tìm hậu tố dài nhất của $W+c$ là tiền tố thực sự của một trong hai mẫu.

Trạng thái `found` chuyển về chính nó với mọi ký tự. Do $\ell\le20$, có thể xây bảng chuyển trực tiếp bằng so sánh xâu thay vì cài cấu trúc phức tạp hơn.

Bảng chuyển này cập nhật đúng trạng thái: mọi tiền tố mẫu là hậu tố của $X+c$, sau khi bỏ ký tự cuối, phải là một hậu tố của $X$ thuộc tập tiền tố. Hậu tố dài nhất đã lưu chứa tất cả các hậu tố ngắn hơn có thể cần dùng.

## Kiểm tra mẫu bắc qua tâm

Nếu đã ở `found`, trạng thái luôn được chấp nhận. Với trạng thái khác, lấy xâu đại diện $W$ và tạo xâu đối xứng từ $W$ theo cùng quy tắc chẵn/lẻ của $L$. Chấp nhận nếu xâu này chứa $S$.

Vì sao chỉ cần $W$? Khi chưa vào `found`, $S$ không thể nằm hoàn toàn trong một nửa của đường đi: nếu nằm trong nửa phản chiếu thì $R$ đã nằm trong $X$. Mọi lần xuất hiện còn lại phải bắc qua tâm. Phần nằm bên trái của lần xuất hiện đó là một hậu tố của $X$ và một tiền tố của $S$. Do $W$ là hậu tố dài nhất thuộc tập tiền tố của hai mẫu, nó chứa toàn bộ phần bên trái cần thiết. Phần bên phải là phản chiếu của một đoạn nằm trong $X$ và tương ứng với một hậu tố của $X$ là tiền tố của $R$. Đoạn này cũng nằm trong $W$ vì đã đưa cả tiền tố của $R$ vào tập trạng thái.

Vì vậy việc phản chiếu $W$ giữ đủ cả hai phần của một lần xuất hiện qua tâm. Ngược lại, xâu đối xứng tạo từ $W$ nằm ở chính giữa đường đi hoàn chỉnh, nên một lần xuất hiện trong xâu này cũng là lần xuất hiện thật trên đường. Với $L$ lẻ, phải bỏ đúng một bản sao ký tự giữa để tránh tính lặp ô tâm.

## Trạng thái quy hoạch động

Ở lớp $t$, dùng $dp[x][u][q]$: số cặp đoạn đường từ hai đầu tới hai hàng $x,u$, đã ghép các ký tự đối xứng bằng nhau, và bộ tự động sau khi đọc nửa trái có trạng thái $q$.

Khởi tạo bằng ký tự ở ô đầu, với số cách $1\bmod D$. Mỗi bước thử bốn cách kết hợp xuống/phải từ đầu và lên/trái từ cuối. Khi hai ô mới hợp lệ và cùng ký tự $c$, chuyển trạng thái tự động theo $c$ rồi cộng số cách modulo $D$.

Không để hai con trỏ vượt nhau theo hàng hay cột. Dừng sau $\lfloor(L-1)/2\rfloor$ bước: hai con trỏ phải cùng ô nếu $L$ lẻ, hoặc kề nhau nếu $L$ chẵn. Cộng đúng các trạng thái có kết quả chấp nhận đã tính trước. Chỉ giữ lớp hiện tại và lớp tiếp theo; chuyển vị bảng nếu cần để số hàng nhỏ hơn số cột.

## Chứng minh tính đúng đắn

Theo quy nạp theo lớp, mỗi trạng thái đếm đúng các cặp đoạn có ký tự đối xứng bằng nhau và đúng trạng thái của bộ tự động trên nửa trái: khởi tạo đúng ở hai đầu, bốn phép mở rộng liệt kê đầy đủ và không lặp mọi cặp bước hợp lệ. Bộ tự động chuyển đúng theo lập luận về hậu tố.

Tại lớp cuối, điều kiện gặp hoặc kề nhau ghép mỗi cặp đoạn thành đúng một đường đối xứng. Phép chấp nhận xử lý đầy đủ cả trường hợp mẫu nằm trong một nửa lẫn trường hợp qua tâm, nên tương đương việc xâu toàn đường chứa $S$. Mỗi đường thắng cuộc có duy nhất một dãy cặp bước và một dãy trạng thái tự động. Do đó tổng thu được chính xác là đáp án.

## Độ phức tạp

Đặt $r=\min(m,n)$. Có $O(r^2\ell)$ trạng thái mỗi lớp và $O(m+n)$ lớp, mỗi trạng thái thử bốn chuyển tiếp. Tổng thời gian là $O((m+n)r^2\ell+26\ell^3)$, trong đó hạng sau dành cho cách dựng bảng chuyển trực tiếp. Bộ nhớ là $O(r^2\ell+26\ell+\ell^2)$, gồm hai lớp, bảng chuyển và các xâu đại diện. Mọi lần cộng hai số dư đều nằm trong số nguyên có dấu 32 bit vì $D\le10^9$.
