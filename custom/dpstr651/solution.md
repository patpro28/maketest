## Trạng thái và chuyển

Đặt $F_t[L][R]$ là độ dài dãy con lớn nhất trong đoạn $S[L\ldots R]$ có thể thành đối xứng bằng không quá $t$ lần thay chữ. Đoạn rỗng có giá trị $0$, đoạn một ký tự có giá trị $1$ ở mọi lớp ngân sách.

Luôn có thể bỏ một đầu:

$$F_t[L][R]=\max(F_t[L+1][R],F_t[L][R-1]).$$

Nếu hai chữ bằng nhau, xét thêm $F_t[L+1][R-1]+2$. Nếu hai chữ khác nhau và $t>0$, xét thêm $F_{t-1}[L+1][R-1]+2$. Đáp án là $F_K[1][N]$.

## Tính đúng đắn

Một dãy con tối ưu hoặc bỏ ít nhất một đầu, hoặc giữ cả hai làm cặp ngoài cùng. Với cặp bằng nhau không cần thay; với cặp khác nhau cần ít nhất một lần thay và đúng một lần là đủ. Sau khi xử lý cặp này, phần trong có đúng bài toán cùng loại với ngân sách còn lại. Mọi chuyển đều tạo một phương án hợp lệ và các trường hợp phủ mọi phương án, nên quy nạp theo độ dài đoạn chứng minh tính tối ưu. Vì trạng thái dùng ngân sách không quá $t$, không cần dùng hết $K$ lần thay.

## Nén bộ nhớ và độ phức tạp

Duyệt đầu trái giảm, đầu phải tăng, giữ một hàng cho mỗi lớp $t$. Các biến chéo lưu hàng trước ở đầu phải liền trước. Khi duyệt $t$ tăng, phải giữ lại giá trị chéo cũ của lớp $t-1$ trước khi ghi đè nó, để chuyển dùng thêm một lần thay đọc đúng đoạn trong.

Thời gian $O(N^2(K+1))$, bộ nhớ $O(N(K+1))$. Với $N=4000,K=5$, có $6\cdot4000\cdot4001/2=48012000$ trạng thái chính, dưới $5\cdot10^7$.
