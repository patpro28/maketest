# BS14 — Hướng dẫn giải

## Cách vét cạn cho dữ liệu nhỏ

Liệt kê tất cả bộ ba $i<j<\ell$, ghi lại $\max(A_i,A_j,A_\ell)$ rồi sắp xếp danh sách kết quả. Trả lời truy vấn $K$ bằng phần tử ở chỉ số $K-1$. Cách này tốn $\Theta(N^3)$ phần tử và không phù hợp với giới hạn đầy đủ, nhưng dùng được để kiểm tra đáp án trên dữ liệu nhỏ.

## Sắp xếp dãy ban đầu

Sắp xếp các chỉ số thành dãy không giảm $B_1\le B_2\le\cdots\le B_N$.

Mỗi nhóm là một tập gồm ba gia đình khác nhau; điều kiện chỉ số tăng dần chỉ giúp biểu diễn mỗi tập đúng một lần. Vì vậy, đổi thứ tự các gia đình bằng cách sắp xếp không làm thay đổi danh sách giá trị lớn nhất. Các gia đình có chỉ số sinh hoạt bằng nhau vẫn là các phần tử riêng biệt.

Gán mỗi bộ ba cho vị trí lớn nhất của nó trong dãy đã sắp xếp. Nếu vị trí đó là $i$, hai phần tử còn lại được chọn từ $i-1$ vị trí trước, có:

$$\binom{i-1}{2}=\frac{(i-1)(i-2)}{2}$$

cách chọn. Mọi bộ ba như vậy có giá trị lớn nhất bằng $B_i$.

Vì $B_i$ không giảm, danh sách đánh giá tăng dần có thể được biểu diễn bằng các khối: với mỗi $i$ từ $3$ đến $N$, lặp lại $B_i$ đúng $\binom{i-1}{2}$ lần. Các khối bằng giá trị nhau vẫn giữ đầy đủ số lần xuất hiện.

## Tìm kiếm nhị phân theo vị trí

Tổng số phần tử trong các khối đến vị trí $i$ là:

$$P_i=\sum_{j=3}^{i}\binom{j-1}{2}=\binom{i}{3}=\frac{i(i-1)(i-2)}{6}.$$

Đẳng thức đúng vì cả hai vế đều đếm số cách chọn ba vị trí trong $i$ vị trí đầu tiên.

Với mỗi truy vấn $K$, tìm vị trí nhỏ nhất $i\in[3,N]$ sao cho $P_i\ge K$. Khi đó $P_{i-1}<K\le P_i$, nên phần tử nhỏ thứ $K$ thuộc khối của $B_i$ và đáp án là $B_i$.

Có thể tự viết tìm kiếm nhị phân và tính $\binom{i}{3}$ khi cần (`sol/correct.cpp`), hoặc xây mảng cộng dồn bằng trọng số $\binom{i-1}{2}$ rồi dùng `lower_bound` (`sol/prefix.cpp`).

Lưu ý: khi có giá trị trùng nhau, $P_i$ là số phần tử của các **khối được gán đến vị trí $i$**, không nhất thiết là toàn bộ số nhóm có giá trị lớn nhất không vượt $B_i$. Cách gán khối vẫn chính xác và cho đúng giá trị đáp án.

## Độ đúng

Mỗi bộ ba có duy nhất một vị trí lớn nhất sau khi sắp xếp, nên việc gán bộ ba vào các khối không bỏ sót hoặc đếm trùng. Mọi giá trị trong khối $i$ bằng $B_i$ và các khối được xếp theo thứ tự không giảm. Tìm khối đầu tiên có tổng số phần tử đạt ít nhất $K$ vì thế trả về đúng phần tử nhỏ thứ $K$.

## Độ phức tạp và số nguyên lớn

Mỗi bộ dữ liệu cần $O(N\log N+Q\log N)$ thời gian và $O(N)$ bộ nhớ. Xử lý các bộ dữ liệu lần lượt để không phải lưu mọi bộ dữ liệu cùng lúc.

Dùng số nguyên 64 bit cho $K$, các trọng số, tổng cộng dồn và phép tính tổ hợp. Với $N=300000$, số nhóm là $4499955000100000$. Phải ép sang 64 bit **trước khi nhân**, chẳng hạn `1LL * n * (n - 1) * (n - 2) / 6`. Cả tích trước phép chia cũng nằm trong giới hạn số nguyên có dấu 64 bit.
