Tính tổng tiền tố $P_0=0$, $P_i=P_{i-1}+A_i$. Duyệt đầu phải $R$ từ $K$ đến $N$. Đoạn dài đúng $K$ kết thúc tại $R$ bắt đầu ở $R-K+1$, nên có tổng $S=P_R-P_{R-K}$. Nếu $S$ thỏa điều kiện, tăng đáp án thêm $1$.

Kiểm tra đồng thời $U\le S$ và $S\le V$.

Tính đúng đắn: mỗi đoạn dài đúng $K$ có duy nhất một đầu phải $R$ trong khoảng từ $K$ đến $N$. Vòng lặp xét mỗi đầu phải đó đúng một lần. Hiệu hai tổng tiền tố cho đúng tổng các phần tử trong đoạn, nên đáp án được tăng khi và chỉ khi đoạn đó thỏa điều kiện. Vì vậy mọi đoạn hợp lệ được đếm đủ và không trùng.

Thời gian $O(N)$, bộ nhớ $O(N)$.

Dùng số nguyên 64 bit cho tổng tiền tố, tổng đoạn và các tham số tổng. Trị tuyệt đối của tổng không vượt $2\cdot10^{14}$.
