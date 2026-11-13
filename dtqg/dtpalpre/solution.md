## Biểu diễn yêu cầu

Đánh số đơn hàng từ $0$. Dùng mặt nạ $mask$ ghi các đơn hàng đã hoàn thành. Với mỗi đơn hàng $i$, lập $need[i]$ chứa các đơn hàng phải đứng trước nó theo các yêu cầu đầu vào.

Chỉ được thêm $i$ khi bit $i$ chưa có và

$$(mask\mathbin{\&}need[i])=need[i].$$

Không cần tính bao đóng bắc cầu: khi từng quan hệ trực tiếp được tuân thủ, mọi đường đi của quan hệ trước sau cũng được tuân thủ. Nếu có chu trình, không thể hoàn thành toàn bộ đơn hàng.

## Tiền xử lý xâu

Tính các bán kính Manacher $odd[c]$ và $even[c]$ trong $O(n)$ bằng cách tái sử dụng bán kính tại tâm đối xứng trong đoạn có biên phải xa nhất, rồi mở rộng phần chưa biết.

Đoạn bắt đầu $p$, dài $L$ được kiểm tra trong $O(1)$: cần $p+L\le n$, và $odd[p+L/2]\ge L/2+1$ nếu $L$ lẻ, hoặc $even[p+L/2]\ge L/2$ nếu $L$ chẵn.

Với mỗi độ dài phân biệt $L$, lập $next_L[p]$ là kết thúc sớm nhất của một đoạn phù hợp bắt đầu không trước $p$. Duyệt phải sang trái, lấy $p+L$ nếu đoạn tại $p$ phù hợp, ngược lại lấy $next_L[p+1]$; không có đoạn thì dùng $INF=n+1$.

## DP tập con

Đặt $dp[mask]$ là kết thúc sớm nhất khi đã chọn các đơn hàng trong $mask$ theo một thứ tự thỏa các yêu cầu giữa chúng. Khởi tạo $dp[0]=0$; các giá trị khác bằng $INF$.

Từ $dp[mask]=p$ hữu hạn, với đơn hàng $i$ được phép thêm:

$$dp[mask\cup\{i\}]=\min\left(dp[mask\cup\{i\}],next_{l_i}[p]\right).$$

Duyệt mặt nạ tăng dần. Trả lời `YES` khi trạng thái đầy đủ không vượt $n$. Có thể loại ngay khi tổng độ dài vượt $n$.

## Chứng minh đúng

Hai phương án dùng cùng một mặt nạ có cùng tập đơn hàng đủ điều kiện xét tiếp; điều kiện trước sau chỉ phụ thuộc mặt nạ. Nếu một phương án kết thúc sớm hơn, nó còn chứa toàn bộ các lựa chọn tương lai của phương án muộn hơn. Vì vậy chỉ giữ kết thúc sớm nhất không mất đáp án.

Mọi phương án hợp lệ có một đơn hàng cuối $i$, với toàn bộ tiền nhiệm đã thuộc mặt nạ trước đó. DP thử đúng chuyển này. Thay phần trước bằng phương án sớm nhất và lấy đoạn cuối sớm nhất không làm kết thúc muộn hơn. Quy nạp theo số bit cho thấy DP tìm đúng giá trị tối ưu. Ngược lại, mỗi chuyển chỉ thêm đoạn đối xứng không giao nhau và tuân thủ các tiền nhiệm, nên trạng thái đầy đủ hữu hạn tạo ra đáp án hợp lệ.

## Độ phức tạp

Với $D\le k$ độ dài phân biệt, thời gian $O(nD+k2^k)$ và bộ nhớ $O(nD+2^k)$. Những đơn hàng trùng độ dài dùng chung bảng tìm đoạn nhưng vẫn dùng các bit riêng vì có thể có quan hệ trước sau khác nhau.
