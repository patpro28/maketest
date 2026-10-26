# Lời giải — Chênh lệch với mốc

### Thông tin tại mỗi nút

Mỗi nút lưu một giá trị đại diện `first` là phần tử đầu đoạn và $g=\gcd(|A_i-\text{first}|)$ với mọi phần tử trong đoạn. Lá chứa $x$ lưu `first = x`, `g = 0`. Có thêm cờ nhận biết nút rỗng.

### Phép ghép

Với hai đoạn không rỗng $L,R$, giữ `first = L.first` và đặt $g=\gcd(L.g,R.g,|L.first-R.first|)$. Ghép với nút rỗng trả lại nút còn lại.

### Xử lý thao tác

Mỗi lần gán sửa lá tương ứng và tính lại các nút trên đường lên gốc. Mỗi truy vấn ghép các đoạn con rời nhau theo thứ tự trái sang phải để thu được thông tin của đoạn cần hỏi.

Khi đổi gốc từ `R.first` sang `L.first`, hiệu của hai gốc cùng GCD nội bộ đủ mô tả mọi độ chênh lệch. Với mốc $c$, đáp án là $\gcd(g,|\text{first}-c|)$. Công thức tương đương với cách dùng GCD các chênh lệch kề nhau. Dùng số nguyên 64 bit khi tính hiệu và trị tuyệt đối.

### Tính đúng đắn

Thông tin tại mỗi lá đúng theo định nghĩa. Một số nguyên dương chia hết mọi hiệu so với gốc trái khi và chỉ khi nó chia hết các hiệu nội bộ của hai đoạn và hiệu giữa hai gốc. Vì vậy công thức ghép GCD bảo toàn đúng thông tin cần lưu. Bằng quy nạp theo chiều cao cây, mọi nút đều đúng sau khi dựng cây. Cập nhật tính lại tất cả nút bị ảnh hưởng nên duy trì tính chất đó. Truy vấn ghép đúng các đoạn con phủ đoạn cần hỏi; kết hợp với công thức tính đáp án ở trên, kết quả được in là đúng.

### Độ phức tạp

Dựng cây cần $O(N)$ phép ghép; mỗi thao tác cần $O(\log N)$ phép ghép. Mỗi phép GCD mất $O(\log V)$ với $V=2\cdot10^9$. Tổng thời gian $O((N+Q\log N)\log V)$, bộ nhớ $O(N)$.
