### Ý tưởng

Tạo dãy $B$ gồm $N-1$ phần tử:

$$B_i=A_i+A_{i+1}\quad(1\le i<N).$$

Mỗi $B_i$ là giá của cặp kề nhau bắt đầu tại vị trí $i$. Với truy vấn $L<R$, các cặp hợp lệ bắt đầu tại $L,L+1,\dots,R-1$. Do đó đáp án là

$$\min(B_L,B_{L+1},\dots,B_{R-1}).$$

Dựng segment tree lưu giá trị nhỏ nhất trên dãy $B$. Truy vấn trên đoạn $[L,R-1]$; nếu $L=R$, trả lời $-1$ ngay.

### Chứng minh tính đúng đắn

Một cặp được chọn hợp lệ khi và chỉ khi có chỉ số $i,i+1$ với $L\le i<R$. Ánh xạ cặp này tới $B_i$ là tương ứng một-một giữa mọi cặp hợp lệ và các phần tử của dãy $B$ trên đoạn $[L,R-1]$. Giá của cặp đúng bằng $B_i$, nên giá cặp nhỏ nhất chính là min của đoạn đó.

Các lá của cây lưu đúng giá mỗi cặp; nút trong lấy min của hai con nên theo quy nạp mọi nút và truy vấn đều cho min đúng. Trường hợp $L=R$ không có chỉ số $i$ hợp lệ, nên trả lời $-1$ đúng yêu cầu.

### Độ phức tạp

Tạo dãy $B$ và dựng cây mất $O(N)$ thời gian. Mỗi truy vấn mất $O(\log N)$, tổng $O(N+Q\log N)$. Bộ nhớ $O(N)$.

### Lưu ý cài đặt

Biên phải khi hỏi trên dãy $B$ là $R-1$, không phải $R$. Khi $N=1$, dãy $B$ rỗng và mọi truy vấn đều trả lời $-1$. Dùng số nguyên 64 bit cho giá cặp để thuận tiện cài đặt.

### Vì sao không dùng hiệu tổng tiền tố

Tổng cả đoạn không cho biết giá cặp rẻ nhất. Chẳng hạn $[1,4,1,4]$ và $[1,1,4,4]$ có cùng tổng $10$ và cùng tập giá, nhưng đáp án lần lượt là $5$ và $2$. Tổng tiền tố của $B$ cũng chỉ cho tổng các giá cặp, không cho giá trị nhỏ nhất của chúng. Cần truy vấn min trên dãy đã biến đổi.
