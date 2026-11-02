### Chọn giá trị chung

Xét đoạn $[L,R]$, gọi $M$ là giá trị lớn nhất trong đoạn. Vì chỉ được tăng, giá trị chung $T$ phải thỏa mãn $T\ge M$.

Để tăng một phần tử $a$ lên $T$, cần ít nhất

$$\left\lceil\frac{T-a}{2}\right\rceil$$

thao tác: dùng nhiều lần tăng $2$ nhất có thể, và thêm một lần tăng $1$ nếu hiệu là số lẻ. Khi tăng $T$, số thao tác cần cho từng phần tử không giảm. Do đó chọn $T=M$ luôn tối ưu.

### Kết hợp các đại lượng

Gọi $k=R-L+1$, $S$ là tổng các phần tử trong đoạn và $C$ là số phần tử có tính chẵn/lẻ khác với $M$. Khi đó $M-A_i$ lẻ đúng khi $A_i$ khác tính chẵn/lẻ với $M$. Vì vậy:

$$\left\lceil\frac{M-A_i}{2}\right\rceil
=\frac{M-A_i+[A_i\bmod2\ne M\bmod2]}{2}.$$

Cộng trên toàn đoạn được đáp án:

$$\boxed{\frac{kM-S+C}{2}}.$$

Cần cộng phần hiệu chỉnh chẵn/lẻ trước khi chia, thay vì làm tròn một lần cho tổng các hiệu.

### Segment tree

Mỗi nút lưu:

- `sum`: tổng các phần tử trong đoạn.
- `maximum`: phần tử lớn nhất trong đoạn.
- `odd`: số phần tử lẻ trong đoạn.

Với lá chứa $x$, thông tin là $(x,x,x\bmod2)$. Ghép hai nút bằng cách cộng `sum`, lấy lớn nhất của `maximum` và cộng `odd`.

Với truy vấn gán, thay thông tin ở lá rồi tính lại các tổ tiên. Với truy vấn đoạn, lấy $(S,M,O)$ và tính:

- Nếu $M$ chẵn thì $C=O$.
- Nếu $M$ lẻ thì $C=k-O$.

Thay vào công thức để in kết quả. Các phép tăng trong truy vấn loại `2` chỉ được xét để tính toán, không cập nhật cây. Bài không cần lazy propagation hay tìm kiếm vị trí trên cây.

### Chứng minh tính đúng đắn

Với một giá trị chung $T\ge M$, mỗi thao tác tăng nhiều nhất $2$, nên phần tử $a$ cần ít nhất $\lceil(T-a)/2\rceil$ thao tác. Sử dụng các lần tăng $2$ và nhiều nhất một lần tăng $1$ đạt đúng cận dưới này. Các phần tử được tăng độc lập nên tổng các chi phí riêng là số thao tác tối thiểu để đạt $T$.

Mỗi chi phí riêng là hàm không giảm theo $T$. Vì vậy $M$, giá trị chung khả thi nhỏ nhất, cho tổng chi phí tối thiểu. Công thức $(kM-S+C)/2$ chính là tổng các chi phí riêng tại $T=M$, nên tính đúng đáp án từ ba đại lượng.

Các lá lưu đúng tổng, giá trị lớn nhất và số phần tử lẻ. Phép ghép duy trì đúng cả ba đại lượng trên đoạn hợp. Sau mỗi lần gán, cập nhật lá và tính lại các tổ tiên bảo đảm bất biến này vẫn đúng. Do đó truy vấn cây trả về đúng $S,M,O$ trên dãy hiện tại; cách tính $C$ và công thức trên cho đúng số thao tác ít nhất.

### Độ phức tạp

Dựng cây mất $O(N)$ thời gian. Mỗi truy vấn gán hoặc truy vấn đoạn mất $O(\log N)$ thời gian. Tổng thời gian là $O(N+Q\log N)$; bộ nhớ là $O(N)$.

### Lưu ý cài đặt

Dùng số nguyên 64 bit cho tổng, tích $kM$ và đáp án, vì $kM$ có thể đạt $5\cdot10^{14}$. Ép kiểu sang 64 bit trước khi nhân. Khi đoạn chỉ có một phần tử hoặc mọi phần tử đã bằng nhau, công thức cho kết quả $0$.
