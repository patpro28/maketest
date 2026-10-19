# BS52A — Hướng dẫn giải

## Liệt kê trực tiếp khi dữ liệu nhỏ

Xét mọi bộ ba $i<j<\ell$, ghi lại $\min(A_i,A_j,A_\ell)$ rồi sắp xếp danh sách. Mỗi truy vấn $K$ lấy phần tử thứ $K$ trong danh sách đó. Cách này cần $\Theta(N^3)$ phần tử, nên chỉ dùng được cho dữ liệu nhỏ và làm lời giải đối chiếu.

## Sắp xếp và đếm theo phần tử nhỏ nhất

Sắp xếp các chỉ số thành dãy $B_1\le B_2\le\cdots\le B_N$. Thứ tự ban đầu chỉ dùng để biểu diễn mỗi nhóm ba gia đình đúng một lần, nên sắp xếp không làm thay đổi danh sách các giá trị nhỏ nhất.

Gán mỗi bộ ba cho vị trí nhỏ nhất của nó trong dãy đã sắp xếp. Với vị trí đó là $i$, hai vị trí còn lại được chọn trong $N-i$ vị trí phía sau. Có:

$$w_i=\binom{N-i}{2}=\frac{(N-i)(N-i-1)}{2}$$

nhóm được gán cho $i$ và mọi nhóm đều có mức đánh giá $B_i$.

Vì vậy danh sách đánh giá tăng dần gồm các khối: khối $i$ chứa $w_i$ bản sao của $B_i$, với $1\le i\le N-2$. Mỗi gia đình vẫn là một phần tử riêng biệt, kể cả khi nhiều gia đình có cùng chỉ số sinh hoạt.

## Tìm kiếm nhị phân

Số phần tử trong các khối từ $1$ đến $i$ là:

$$P_i=\sum_{j=1}^{i}\binom{N-j}{2}=\binom{N}{3}-\binom{N-i}{3}.$$

Đẳng thức này đếm tất cả nhóm, trừ các nhóm có cả ba vị trí nằm trong $N-i$ vị trí cuối. Quy ước $\binom{x}{3}=0$ nếu $x<3$.

Với mỗi $K$, tìm chỉ số nhỏ nhất $i\in[1,N-2]$ sao cho $P_i\ge K$. Khi đó $P_{i-1}<K\le P_i$, nên phần tử thứ $K$ thuộc khối $i$, có giá trị $B_i$.

Lời giải `sol/correct.cpp` tính công thức khi tìm kiếm nhị phân. Lời giải `sol/prefix.cpp` xây mảng cộng dồn theo các trọng số $w_i$ rồi gọi `lower_bound`.

Khi có nhiều giá trị bằng nhau, $P_i$ là số phần tử trong các khối được gán đến vị trí $i$; không nhất thiết bằng tổng số nhóm có mức đánh giá không vượt $B_i$. Cách chia khối vẫn giữ đủ số lần xuất hiện và trả về đúng giá trị.

## Chứng minh

Mỗi bộ ba có duy nhất một vị trí nhỏ nhất sau khi sắp xếp, nên thuộc đúng một khối. Số nhóm trong từng khối là $w_i$, và giá trị đánh giá của chúng đều là $B_i$. Các $B_i$ không giảm, nên ghép các khối theo thứ tự chỉ số cho đúng danh sách đánh giá tăng dần. Tìm khối đầu tiên có tổng số phần tử đạt ít nhất $K$ vì thế cho đúng phần tử nhỏ thứ $K$.

## Độ phức tạp và kiểu dữ liệu

Mỗi bộ dữ liệu mất $O(N\log N+Q\log N)$ thời gian và $O(N)$ bộ nhớ. Xử lý lần lượt từng bộ dữ liệu để đáp ứng giới hạn tổng $N,Q$.

Dùng số nguyên 64 bit cho $K$, trọng số, tổng cộng dồn và các phép nhân tính tổ hợp. Với $N=300000$, có $4499955000100000$ nhóm. Cần ép sang 64 bit trước khi nhân, chẳng hạn `1LL * n * (n - 1) * (n - 2) / 6`; cả tích trước phép chia vẫn nằm trong giới hạn số nguyên có dấu 64 bit.
