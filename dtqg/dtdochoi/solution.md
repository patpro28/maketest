## Sắp xếp theo mã màu

Sắp xếp đồ chơi theo $c_i$ và đánh lại chỉ số từ $0$ đến $n-1$. Trong một cách chia tối ưu, xét đoạn từ đồ chơi đầu tiên tới đồ chơi cuối cùng của Alice. Chuyển cho Alice mọi đồ chơi trong đoạn đó giữ nguyên chênh lệch mã màu và chỉ có thể làm giảm chênh lệch kích thước của Bob. Nếu đoạn là cả dãy, giao đồ chơi đầu tiên cho Bob và giao phần còn lại cho Alice. Bob nhận đúng một đồ chơi, còn chênh lệch mã màu của Alice không tăng.

Vì vậy có nghiệm tối ưu mà Alice nhận một đoạn $[l,k)$ với $0\le l<k\le n$. Bob nhận tiền tố $[0,l)$ và hậu tố $[k,n)$. Tính trước cực tiểu và cực đại kích thước của các hậu tố. Các trường hợp $l=0$ hoặc $k=n$ được xét bằng một lượt quét với cực trị tiền tố và hậu tố, bỏ qua trường hợp Bob nhận rỗng.

## Thu hẹp các đoạn cần xét

Chọn một vị trí có kích thước nhỏ nhất và một vị trí có kích thước lớn nhất của cả dãy. Gọi hai vị trí này theo thứ tự xuất hiện là $x\le y$, và gọi $D$ là hiệu giữa kích thước lớn nhất và nhỏ nhất. Cho Alice một đồ chơi bất kỳ thì tổng chênh lệch không vượt quá $D$. Mặt khác, nếu đoạn của Alice tránh cả $x$ và $y$, Bob giữ cả hai cực trị nên tổng chênh lệch ít nhất là $D$.

Khởi tạo đáp án bằng $D$. Sau khi xét các đoạn chạm đầu hoặc cuối dãy, chỉ cần xét hai miền chỉ số sau.

- Đoạn chứa $x$, với $1\le l\le x$ và $x+1\le k\le n-1$.
- Đoạn chứa $y$ và bắt đầu sau $x$, với $x+1\le l\le y$ và $y+1\le k\le n-1$.

Trong mỗi miền, cận dưới $L$ của $k$ được cố định. Vì $L>l$ trong cả miền nên mọi lựa chọn $k$ đều tạo thành đoạn không rỗng.

## Tìm cực tiểu bằng deque đơn điệu

Với $l$ cố định, gọi $p_{\min},p_{\max}$ là hai cực trị kích thước của tiền tố $[0,l)$. Gọi $q_{\min}(k),q_{\max}(k)$ là hai cực trị của hậu tố $[k,n)$. Chi phí của đoạn $[l,k)$ là

$$
c_{k-1}-c_l+\max(p_{\max},q_{\max}(k))-\min(p_{\min},q_{\min}(k)).
$$

Khi $k$ tăng, $q_{\min}(k)$ không giảm và $q_{\max}(k)$ không tăng. Đặt $a$ là chỉ số $k$ nhỏ nhất trong $[L,n-1]$ sao cho $q_{\min}(k)\ge p_{\min}$. Đặt $b$ tương tự cho điều kiện $q_{\max}(k)\le p_{\max}$. Nếu một điều kiện không có chỉ số thỏa mãn, lấy mốc tương ứng bằng $n$.

Sau khi bỏ hạng tử chung $-c_l$, chi phí có bốn dạng. Bỏ qua mọi khoảng rỗng.

| Khoảng của $k$ | Biểu thức cần lấy cực tiểu |
| --- | --- |
| $[L,\min(a,b)-1]$ | $c_{k-1}+q_{\max}(k)-q_{\min}(k)$ |
| $[b,a-1]$ | $c_{k-1}-q_{\min}(k)+p_{\max}$ |
| $[a,b-1]$ | $c_{k-1}+q_{\max}(k)-p_{\min}$ |
| $[\max(a,b),n-1]$ | $c_{k-1}+p_{\max}-p_{\min}$ |

Quét $l$ tăng dần. Tiền tố dài thêm nên $p_{\min}$ chỉ giảm hoặc giữ nguyên, còn $p_{\max}$ chỉ tăng hoặc giữ nguyên. Vì thế $a$ và $b$ chỉ dịch sang trái. Duy trì hai mốc bằng hai con trỏ, mỗi con trỏ bắt đầu ở $n$.

Ba khoảng đầu có cả hai đầu mút không tăng. Với mỗi khoảng, dùng một deque giữ cực tiểu của phần biểu thức chỉ phụ thuộc vào $k$. Chèn chỉ số theo thứ tự giảm dần, loại ở đầu deque các chỉ số lớn hơn cận phải và loại ở cuối deque mọi giá trị lớn hơn hoặc bằng giá trị mới. Chỉ số mới nhỏ hơn nên tồn tại ít nhất lâu bằng chỉ số bị loại khi cận phải dịch sang trái. Giá trị tại đầu deque là cực tiểu trong cửa sổ hiện tại. Ở khoảng cuối, chọn trực tiếp $k$ nhỏ nhất vì $c_{k-1}$ không giảm.

## Tính đúng đắn và độ phức tạp

Phép chuyển đồ chơi vào đoạn liên tiếp giữ được một cách chia tối ưu. Nếu đoạn tối ưu chạm một đầu dãy, lượt quét các đoạn biên xét nó. Nếu đoạn tránh cả hai vị trí cực trị, giá trị khởi tạo $D$ đã không vượt chi phí của nó. Các đoạn còn lại thuộc một trong hai miền được quét. Với mỗi $l$ trong một miền, bốn khoảng phân hoạch toàn bộ các $k$ hợp lệ. Mỗi deque trả về cực tiểu chính xác của khoảng tương ứng, nên thuật toán tìm được chi phí nhỏ nhất trong miền. Tất cả chi phí đem so sánh đều ứng với cách chia hợp lệ, còn $D$ là cận trên của đáp án. Vì thế kết quả bằng đáp án tối ưu.

Sau khi sắp xếp, mỗi con trỏ và mỗi deque xử lý một chỉ số nhiều nhất một lần trong mỗi miền. Phần quét mất $O(n)$ thời gian và $O(n)$ bộ nhớ. Tính cả sắp xếp, lời giải dùng $O(n\log n)$ thời gian và $O(n)$ bộ nhớ. Nên dùng cách đọc dữ liệu có bộ đệm vì đầu vào có thể chứa đến bốn triệu số.

Với $n=2\,000\,000$, một sparse table lưu giá trị bằng số nguyên $32$ bit cho mọi đoạn có độ dài là lũy thừa của hai đã cần hơn $150$ MiB. Các deque chỉ giữ những chỉ số còn có khả năng đạt cực tiểu trong cửa sổ đang xét.
