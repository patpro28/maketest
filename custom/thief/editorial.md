Đây là dạng bài mở rộng của bài 0-1 knapsack.

Ta có thể giải bài này bằng cách sử dụng dynamic programming.

Trong 0-1 knapsack, ta sẽ sử dụng một mảng $dp[n][W]$ để lưu giá trị lớn nhất của bài toán khi ta chọn trong $n$ món đồ đầu tiên và tổng trọng lượng của chúng không vượt quá $W$. Tuy nhiên bài toán này có thể việc cầm một món vào tay, nên ta sẽ sử dụng một mảng $dp[n][W][2]$ để lưu giá trị lớn nhất của bài toán khi ta chọn trong $n$ món đồ đầu tiên và tổng trọng lượng của chúng không vượt quá $W$, chiều còn lại là việc đã cầm một món vào tay hay chưa.

Xét món thứ $i$, ta có 3 trường hợp:

* Bỏ qua món thứ $i$, ta có $dp[i][j][k] = dp[i-1][j][k]$.
* Đặt món thứ $i$ vào túi, ta có $dp[i][j][k] = dp[i-1][j-w_i][k] + c_i$.
* Đặt món thứ $i$ vào tay (tất nhiên $w_i \le H$), ta có $dp[i][j][1] = dp[i-1][j][0] + c_i$.

Vấn đề còn lại là $W$ quá lớn để lưu trữ mảng, tuy nhiên ta thấy rắng $c_i\le 1000$. Vì vậy chúng ta sẽ sử dụng kĩ thuật đảo biến, đảo $W$ và $C$ cho nhau do $sumC \le 10^5$.

Đặt $dp[n][C][2]$ là khối lượng nhỏ nhất để đạt được giá trị $C$ khi xét $n$ món đồ đầu tiên và có thể cầm một món vào tay hay không. Ta sẽ chỉnh lại công thức quy hoạch động như sau:

* Bỏ qua món thứ $i$, ta có $dp[i][j][k] = dp[i-1][j][k]$.
* Đặt món thứ $i$ vào túi, ta có $dp[i][j][k] = dp[i-1][j-c_i][k] + w_i$.
* Đặt món thứ $i$ vào tay (tất nhiên $w_i \le H$), ta có $dp[i][j][1] = dp[i-1][j-c_i][0]$.

Bây giờ cần tìm $C$ lớn nhất sao cho $dp[n][C][0] \le W$ hoặc $dp[n][C][1] \le W$.

Độ phức tạp của thuật toán là $O(nC)$.
