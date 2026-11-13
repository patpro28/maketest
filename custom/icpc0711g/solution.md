## Tách xâu và thứ tự từ điển

Sắp xếp $N$ xâu gốc. Vì không xâu nào là tiền tố của xâu khác, mỗi lần đọc $X$ có duy nhất một xâu gốc khớp ở đầu phần chưa đọc. Đồng thời, thứ tự từ điển của các xâu ghép đúng bằng thứ tự từ điển của dãy chỉ số các xâu thành phần sau sắp xếp: tại thành phần khác nhau đầu tiên, hai xâu đã khác nhau trước khi một thành phần kết thúc.

Có thể tách bằng trie. Một cách khác là tìm nhị phân trong danh sách xâu đã sắp xếp, so sánh một xâu gốc với phần đầu có cùng độ dài của hậu tố $X$ hiện tại; không sao chép toàn bộ hậu tố.

## Tính thứ hạng

Giả sử đã chọn $i$ thành phần, đánh số $i$ từ $0$. Nếu thành phần tiếp theo có $c_i$ xâu chưa dùng đứng trước nó, mỗi lựa chọn nhỏ hơn tạo ra

$$w_i=P(N-i-1,K-i-1)$$

cách điền phần còn lại. Khi đó

$$\operatorname{rank}(X)=1+\sum_{i=0}^{K-1}c_iw_i\pmod{10^9+7}.$$

Tính trước $w_{K-1}=1$, $w_i=w_{i+1}(N-i-1)$. Fenwick ban đầu lưu $1$ tại mọi chỉ số xâu. Truy vấn tổng trước chỉ số hiện tại để lấy $c_i$, rồi giảm giá trị tại chỉ số đó đi $1$.

## Tính đúng đắn

Mỗi xâu ghép đứng trước $X$ có duy nhất vị trí thành phần đầu tiên nhỏ hơn thành phần tương ứng của $X$. Công thức cộng đúng số cách cho vị trí đó, với tiền tố cố định bằng $X$, nên không trùng và không thiếu. Cộng $1$ chuyển sang thứ hạng bắt đầu từ $1$.

## Độ phức tạp

Gọi $L$ là tổng độ dài các xâu gốc. Sắp xếp bằng so sánh xâu và tách bằng tìm nhị phân tốn $O(L\log N)$ thời gian; các phép Fenwick tốn $O((N+K)\log N)$ nếu khởi tạo từng phần tử, hoặc khởi tạo trực tiếp trong $O(N)$ bằng cách gán trực tiếp mỗi ô Fenwick bằng độ dài đoạn nó quản lý. Bộ nhớ $O(L+N+K)$.
