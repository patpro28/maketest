### Ý tưởng

Đặt $b_1=1$; với $i>1$, đặt $b_i=[a_i\ne a_{i-1}]$. Như vậy $b_i=1$ đúng khi ô $i$ bắt đầu một cụm màu. Segment tree lưu tổng các dấu trên mỗi đoạn.

Khi đổi màu ô $i$, tính lại $b_i$ và, nếu $i<N$, tính lại $b_{i+1}$. Không có dấu nào khác bị ảnh hưởng.

Với truy vấn thứ $k$, nếu tổng tại gốc nhỏ hơn $k$ thì trả lời $-1$. Ngược lại, gọi $L$ là tổng con trái. Nếu $k\le L$, đi xuống con trái; nếu $k>L$, đi xuống con phải với thứ hạng mới $k-L$. Lá đến được chính là vị trí bắt đầu của cụm cần tìm.

### Chứng minh tính đúng đắn

Ô đầu tiên luôn bắt đầu một cụm. Một ô sau đó bắt đầu cụm mới đúng khi màu khác ô ngay trước nó. Do đó các dấu $1$ tương ứng một-một với các cụm theo đúng thứ tự trái sang phải. Cập nhật màu chỉ đổi hai quan hệ kề tại $i$ và $i+1$, nên tính lại hai dấu duy trì sự tương ứng này.

Tại mỗi nút, tất cả dấu thuộc con trái đứng trước mọi dấu thuộc con phải. Nếu có $L$ dấu bên trái, thứ hạng $k\le L$ nằm bên trái; nếu $k>L$ thì nằm bên phải ở thứ hạng $k-L$. Theo quy nạp trên chiều cao cây, quá trình đi xuống tìm đúng dấu thứ $k$, tức đúng cụm thứ $k$.

### Độ phức tạp

$O(N+Q\log N)$ thời gian và $O(N)$ bộ nhớ.

### Lưu ý cài đặt

Luôn giữ $b_1=1$. Một lần đổi màu có thể gộp hai biên cụm cùng lúc hoặc tách một cụm thành ba cụm.
