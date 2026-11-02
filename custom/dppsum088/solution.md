Gọi $F(X)$ là số đoạn không rỗng có tổng không vượt $X$. Nếu $X<0$, đặt $F(X)=0$ vì mọi tổng đều không âm. Với $X\ge0$, duyệt đầu phải $R$, giữ đầu trái $L$ ban đầu bằng $1$. Khi $L\le R$ và $P_R-P_{L-1}>X$, tăng $L$. Cộng $R-L+1$ vào $F(X)$.

Đáp án là $F(T)-F(T-1)$. Hiệu này giữ đúng các đoạn có tổng bằng $T$, kể cả khi có nhiều số $0$.

Tính đúng đắn: Sau khi thu hẹp, các đoạn kết thúc tại $R$ có đầu trái từ $L$ đến $R$ đều hợp lệ vì bỏ bớt phần tử không âm không làm tổng tăng. Các đầu trái trước $L$ đều không hợp lệ. Do đó có đúng $R-L+1$ đoạn hợp lệ kết thúc tại $R$; nếu $L=R+1$ thì không có đoạn nào. Mỗi đoạn được đếm đúng một lần theo đầu phải. Công thức kết hợp các giá trị $F$ sau đó giữ đúng các đoạn cần đếm.

Mỗi con trỏ chỉ tăng và đi qua dãy nhiều nhất một lần. Mỗi lượt tính mất $O(N)$ thời gian; số lượt là hằng số, nên tổng thời gian $O(N)$, bộ nhớ $O(N)$ cho tổng tiền tố.

Dùng số nguyên 64 bit cho tổng tiền tố và các ngưỡng vì tổng có thể đạt $2\cdot10^{14}$. Số đoạn có thể đạt $N(N+1)/2=20000100000$, cũng cần số nguyên 64 bit. Các công thức dùng $T-1$ hoặc $U-1$ phải giữ kiểu có dấu để nhận đúng giá trị $-1$ khi ngưỡng bằng $0$.
