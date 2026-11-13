## Trạng thái và chuyển

Đặt $P[L][R]$ cho biết đoạn $S[L\ldots R]$ có đối xứng hay không. Đoạn một ký tự luôn đối xứng. Với đoạn dài hơn:

$$P[L][R]=(S_L=S_R)\land\bigl(R-L<2\;\lor\;P[L+1][R-1]\bigr).$$

Duyệt $L$ giảm dần, với mỗi $L$ duyệt $R$ từ $L$ đến $N$. Như vậy đoạn bên trong đã được tính trước. Mỗi truy vấn chỉ cần tra bảng.

## Tính đúng đắn

Một đoạn có ít nhất hai ký tự đối xứng khi và chỉ khi hai đầu bằng nhau và phần ở giữa đối xứng. Với độ dài $2$, phần giữa rỗng nên chỉ cần so sánh hai đầu. Quy nạp theo độ dài chứng minh bảng đúng trên mọi đoạn, vì vậy mọi kết quả truy vấn đều đúng.

## Độ phức tạp và cài đặt

Tiền xử lý $O(N^2)$, trả lời $O(1)$ mỗi truy vấn; tổng $O(N^2+Q)$, bộ nhớ $O(N^2)$. Dùng kiểu một byte cho mỗi ô, bảng tại $N=5000$ chiếm khoảng $25$ MB. Có $N(N+1)/2+Q\le13002500$ ô và truy vấn chính. Không đọc ô bên trong khi đoạn dài dưới $3$.
