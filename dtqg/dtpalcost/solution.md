## Vì sao phải giữ vị trí?

Hai phương án dùng cùng tập độ dài nhưng kết thúc ở các vị trí khác nhau có thể có chi phí khác nhau. Phương án muộn hơn có thể rẻ hơn, nên không được chỉ giữ vị trí kết thúc sớm nhất.

Đánh số yêu cầu từ $0$ tới $k-1$; các yêu cầu bằng độ dài vẫn có các bit riêng. Đặt $f[p][mask]$ là chi phí nhỏ nhất khi đã xét $p$ ký tự đầu, chọn đủ các yêu cầu trong $mask$ và chưa dùng ký tự nào phía sau $p$.

## Kiểm tra đối xứng và chi phí đoạn

Dùng Manacher để tính bán kính lẻ $odd$ và chẵn $even$ trong $O(n)$. Bán kính ở tâm trong đoạn có biên phải xa nhất được khởi tạo từ tâm đối xứng rồi mở rộng.

Đoạn nửa mở $[p,p+L)$ đối xứng khi $p+L\le n$ và thỏa $odd[p+L/2]\ge L/2+1$ nếu $L$ lẻ, hoặc $even[p+L/2]\ge L/2$ nếu $L$ chẵn.

Đặt $W[p]=\sum_{j=1}^{p}w_j$, $W[0]=0$. Chi phí giữ đoạn $[p,p+L)$ là $W[p+L]-W[p]$.

## Công thức chuyển

Khởi tạo $f[0][0]=0$, các trạng thái khác bằng $INF$ đủ lớn. Từ một trạng thái hữu hạn:

- Bỏ ký tự tiếp theo nếu $p<n$: cập nhật $f[p+1][mask]$ bằng $f[p][mask]$.
- Với bit $i$ chưa dùng, nếu đoạn $[p,p+l_i)$ đối xứng, cập nhật

$$f[p+l_i][mask\cup\{i\}]=\min\left(f[p+l_i][mask\cup\{i\}],f[p][mask]+W[p+l_i]-W[p]\right).$$

Duyệt $p$ tăng dần vì mọi chuyển đều sang vị trí lớn hơn. Đáp án là $f[n][2^k-1]$; nếu vô hạn thì in `-1`. Các phép bỏ ký tự cuối xâu không tăng chi phí.

## Chứng minh đúng

Mỗi chuyển chọn đoạn chỉ giữ một đoạn đối xứng có đúng độ dài, chưa dùng yêu cầu đó và bắt đầu sau tất cả đoạn trước, nên sinh phương án hợp lệ với chi phí đúng. Chuyển bỏ ký tự tương ứng bỏ phần thừa.

Ngược lại, xét mọi cách chọn hợp lệ theo thứ tự từ trái sang phải. Lần lượt bỏ các ký tự thừa rồi chọn đúng các đoạn của cách đó tạo thành một đường chuyển của DP. Vì DP lấy nhỏ nhất trên mọi đường chuyển, nó không bỏ sót phương án tối ưu và không nhận giá trị nhỏ hơn chi phí một phương án hợp lệ.

## Độ phức tạp và kiểu dữ liệu

Thời gian $O(nk2^k)$, bộ nhớ $O(n2^k)$. Ở giới hạn lớn nhất, bảng 64 bit có khoảng 5,12 triệu ô, chiếm khoảng 41 MB.

Tổng chi phí có thể tới $5\cdot10^{12}$ nên cần số nguyên 64 bit. Không cộng chi phí vào trạng thái vô hạn.
