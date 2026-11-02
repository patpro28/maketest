Tính tổng tiền tố $P$. Duyệt đầu phải $R$ từ $1$ đến $N$, giữ đầu trái $L$ ban đầu bằng $1$. Khi $L\le R$ và $P_R-P_{L-1}>T$, tăng $L$. Sau đó, nếu $L\le R$, đoạn $[L,R]$ là đoạn dài nhất kết thúc tại $R$ có tổng không vượt $T$. So sánh độ dài với kết quả đang giữ. Nếu không có đoạn không rỗng phù hợp, in độ dài $0$.

Tính đúng đắn: Vì các phần tử không âm, tăng đầu phải không làm tổng giảm, tăng đầu trái không làm tổng tăng. Mỗi đầu trái bị bỏ qua đều tạo tổng vượt $T$ tại lúc loại và cũng không thể hợp lệ ở các đầu phải sau. Vì vậy sau vòng lặp thu hẹp, $L$ là đầu trái nhỏ nhất còn hợp lệ cho $R$. Xét mọi $R$ sẽ xét được một đoạn dài nhất toàn cục.

Mỗi con trỏ chỉ tăng và đi qua dãy nhiều nhất một lần. Mỗi lượt tính mất $O(N)$ thời gian; số lượt là hằng số, nên tổng thời gian $O(N)$, bộ nhớ $O(N)$ cho tổng tiền tố.

Dùng số nguyên 64 bit cho tổng tiền tố và các ngưỡng vì tổng có thể đạt $2\cdot10^{14}$. Không nhận đoạn rỗng làm đáp án.
