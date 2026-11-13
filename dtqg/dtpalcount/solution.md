## Trạng thái theo số lượng

Nếu $\sum_i L_ic_i>n$, trả lời `NO`. Các yêu cầu cùng độ dài không cần được phân biệt bằng nhiều bit.

Đặt $dp[t_1,\ldots,t_d]$ là vị trí kết thúc sớm nhất sau khi chọn đúng $t_i$ đoạn dài $L_i$ với mọi $i$. Vị trí kết thúc của đoạn nửa mở $[l,r)$ là $r$.

Khởi tạo $dp[0,\ldots,0]=0$; các trạng thái khác bằng $INF=n+1$.

Chỉ giữ kết thúc sớm nhất là đủ: nếu hai cách dùng cùng số lượng kết thúc tại $p\le q$, mọi đoạn nối được sau $q$ cũng nối được sau $p$, bằng cách bỏ phần xâu từ $p$ tới $q$.

## Tìm đoạn tiếp theo

Tính Manacher với bán kính lẻ $odd[c]$ và chẵn $even[c]$. Đoạn $[p,p+L)$ đối xứng khi nằm trong xâu và thỏa:

- $L$ lẻ: $odd[p+L/2]\ge L/2+1$.
- $L$ chẵn: $even[p+L/2]\ge L/2$.

Manacher dùng tâm đối xứng trong đoạn có biên phải xa nhất để tái sử dụng bán kính, rồi mới mở rộng; tổng thời gian $O(n)$.

Với mỗi $L_i$, lập $next_i[p]$ là kết thúc sớm nhất của đoạn đối xứng dài $L_i$ bắt đầu không trước $p$. Duyệt $p$ giảm dần:

$$next_i[n]=INF,$$

$$next_i[p]=\begin{cases}p+L_i,&\text{nếu đoạn tại }p\text{ phù hợp},\\next_i[p+1],&\text{ngược lại}.\end{cases}$$

## Chuyển trạng thái và khôi phục

Với $dp[t_1,\ldots,t_d]=p$ hữu hạn, thử mỗi $i$ còn $t_i<c_i$, chuyển sang trạng thái tăng $t_i$ thêm một với kết thúc $next_i[p]$. Lấy giá trị nhỏ nhất và lưu loại $i$ tạo ra cải thiện.

Có thể mã hóa trạng thái bằng hệ cơ số hỗn hợp. Đặt $stride_1=1$, $stride_i=\prod_{j<i}(c_j+1)$ và $state=\sum_i t_i\,stride_i$. Thêm loại $i$ làm chỉ số tăng $stride_i$, nên duyệt chỉ số tăng dần là một thứ tự tính đúng.

Nếu trạng thái đầy đủ hữu hạn, lần ngược các loại đã lưu. Với loại $i$ được thêm cuối và kết thúc $r$, đoạn tương ứng là $[r-L_i,r)$. Đảo danh sách để in theo thứ tự từ trái sang phải.

## Chứng minh đúng

Quy nạp theo tổng số đoạn đã chọn. Mọi phương án cho trạng thái khác rỗng có một đoạn cuối thuộc một loại $i$. Thay phần trước bằng phương án kết thúc sớm nhất không làm mất khả năng chọn đoạn cuối; sau đó lấy đoạn loại $i$ kết thúc sớm nhất cũng không làm kết quả muộn hơn. Thuật toán thử mọi loại có thể là đoạn cuối nên tìm đúng kết thúc nhỏ nhất.

Mọi phép chuyển chỉ thêm một đoạn đối xứng sau các đoạn đã chọn và tăng đúng một số lượng, nên không sinh phương án sai. Trạng thái đầy đủ hữu hạn khi và chỉ khi có đáp án.

## Độ phức tạp

Đặt $P=\prod_{i=1}^{d}(c_i+1)\le21^3$. Thời gian $O(dn+dP)$, bộ nhớ $O(dn+P)$. Có thể có 60 đoạn cần chọn nhưng không cần $2^{60}$ trạng thái.
