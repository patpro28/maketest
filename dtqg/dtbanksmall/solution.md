## Ý tưởng và thuật toán

Biểu diễn tập các gói đã dùng bằng mặt nạ $m$ bit. Tính trước $sum[sub]$ cho mọi tập con bằng cách bỏ một bit bật.

Xử lý các công trình theo thứ tự chỉ số. Sau khi hoàn thành $i$ công trình, đặt $dp[mask]$ là số phương án dùng đúng tập gói $mask$. Khởi tạo $dp[0]=1$.

Để cấp tiền cho công trình tiếp theo có nhu cầu $a_{i+1}$, liệt kê mọi tập con không rỗng $sub$ của các gói chưa dùng. Nếu $sum[sub]=a_{i+1}$ thì cộng $dp[mask]$ vào $next[mask\cup sub]$. Thay bảng sau khi hoàn thành công trình này.

Sau $n$ lượt, cộng tất cả $dp[mask]$ vì các gói còn lại được phép không sử dụng. Tính các số cách modulo $10^9+7$; dùng số nguyên 64 bit cho tổng tiền.

## Chứng minh tính đúng đắn

Ban đầu chỉ có một cách cấp tiền cho không công trình nào và dùng tập rỗng. Giả sử bảng đúng sau $i$ công trình. Trong một phương án của $i+1$ công trình, tập gói cấp cho công trình cuối rời với các gói đã dùng và có tổng đúng nhu cầu. Đây chính là một tập $sub$ được liệt kê. Ngược lại, mỗi phép chuyển tạo một phương án hợp lệ và xác định duy nhất tập của công trình cuối. Không có phương án nào bị bỏ sót hoặc đếm lặp. Cộng các trạng thái sau cùng chấp nhận mọi lựa chọn gói không dùng, nên cho đáp án cần tìm.

## Độ phức tạp

Tổng số cặp $(mask,sub)$ rời nhau là $3^m$: mỗi gói thuộc $mask$, thuộc $sub$, hoặc không thuộc cả hai. Mỗi bộ dữ liệu tốn $O(n3^m)$ thời gian và $O(2^m)$ bộ nhớ, phù hợp với $m\le10$.
