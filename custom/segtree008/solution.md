### Ý tưởng

Xét một truy vấn $[L,R]$ và đặt $g=\gcd(s_L,s_{L+1},\dots,s_R)$.

Kiến $i$ được tự do khi $s_j$ chia hết cho $s_i$ với mọi $j$ trong đoạn. Điều này tương đương với $s_i=g$:

- Nếu kiến $i$ được tự do thì $s_i$ là ước chung của cả đoạn, do đó $s_i\mid g$. Mặt khác, $g$ là ước của mọi phần tử, nên $g\mid s_i$. Hai số nguyên dương này vì thế bằng nhau.
- Nếu $s_i=g$ thì mọi sức mạnh trong đoạn đều chia hết cho $s_i$, nên kiến $i$ nhận đủ điểm và được tự do.

Vì vậy, đáp án là độ dài đoạn trừ số phần tử có giá trị đúng bằng GCD của đoạn. GCD có thể không xuất hiện trong đoạn; khi đó không con kiến nào được tự do.

### Thông tin lưu trên cây

Mỗi nút của segment tree lưu hai trường:

- `gcd`: GCD của tất cả sức mạnh trong đoạn của nút.
- `count`: số phần tử trong đoạn có giá trị bằng `gcd` của chính nút đó.

Lá chứa sức mạnh $x$ có thông tin $(x,1)$.

Để ghép hai nút $(g_A,c_A)$ và $(g_B,c_B)$, tính $g=\gcd(g_A,g_B)$. Số phần tử bằng $g$ trong đoạn ghép là

$$c=[g_A=g]\,c_A+[g_B=g]\,c_B,$$

trong đó dấu ngoặc vuông có giá trị $1$ nếu điều kiện đúng, ngược lại bằng $0$.

Giá trị trung hòa cho một đoạn rỗng là $(0,0)$. Sử dụng $\gcd(0,x)=x$ để ghép như bình thường.

Với mỗi truy vấn, lấy thông tin $(g,c)$ trên đoạn $[L,R]$, rồi in $R-L+1-c$. Không có cập nhật và không cần tìm kiếm vị trí trên cây.

### Chứng minh tính đúng đắn

Trước hết, kiến được tự do đúng khi sức mạnh bằng GCD của đoạn, như đã chứng minh ở phần ý tưởng.

Ta chứng minh phép ghép duy trì đúng ý nghĩa của nút. GCD của hai đoạn ghép bằng GCD của hai GCD riêng. Xét đoạn con bên trái. Nếu $g_A=g$ thì có đúng $c_A$ phần tử bên trái bằng $g$. Nếu $g_A\ne g$ thì $g$ là ước thực sự của $g_A$, nên $g<g_A$. Mọi phần tử bên trái đều là bội dương của $g_A$, vì vậy không phần tử nào bằng $g$. Lập luận tương tự áp dụng cho đoạn bên phải. Công thức tính $c$ do đó đếm đúng mọi phần tử bằng GCD mới.

Các lá đúng theo định nghĩa, nên theo quy nạp, mọi nút và kết quả ghép của truy vấn đều đúng. Trường `count` của kết quả truy vấn chính là số kiến được tự do; lấy độ dài đoạn trừ số này cho đúng số kiến không được tự do.

### Độ phức tạp

Nếu coi phép tính GCD là một thao tác cơ bản, dựng cây mất $O(n)$ thời gian, mỗi truy vấn mất $O(\log n)$ thời gian. Tổng thời gian là $O(n+m\log n)$ và bộ nhớ là $O(n)$.

Nếu tính thêm chi phí thuật toán Euclid với $S=\max s_i$, một cận trên cho thời gian là $O((n+m\log n)\log S)$.

### Lưu ý cài đặt

Khi $L=R$, kết quả nút là $(s_L,1)$ nên đáp án bằng $0$. Các con kiến có cùng sức mạnh được tính riêng. Không thay `count` bằng số lần xuất hiện của phần tử nhỏ nhất nếu chưa kiểm tra phần tử đó bằng GCD của đoạn.
