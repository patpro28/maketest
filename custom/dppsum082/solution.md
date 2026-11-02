Tính tổng tiền tố $P$. Duyệt đầu phải $R$ từ $1$ đến $N$, giữ đầu trái $L=1$. Trong khi $L\le R$ và $P_R-P_{L-1}\ge T$, ghi nhận độ dài $R-L+1$ rồi tăng $L$ để thử rút ngắn đoạn. Khởi tạo độ dài tốt nhất bằng $N+1$; nếu không cập nhật được thì không có đáp án. Nếu không có đoạn không rỗng phù hợp, in độ dài $0$.

Tính đúng đắn: Với một đầu trái $L$ cố định, tổng không giảm khi tăng đầu phải. Ngay lần đầu tổng đạt ít nhất $T$, đoạn đó có đầu phải sớm nhất phù hợp với $L$ và ngắn hơn mọi đoạn có cùng đầu trái ở các thời điểm sau. Sau khi ghi nhận, có thể bỏ đầu trái này. Vòng lặp lần lượt xét tất cả các đầu trái có khả năng tạo đáp án; đoạn ngắn nhất toàn cục vì thế không bị bỏ sót. Điều kiện $L\le R$ bảo đảm không nhận đoạn rỗng, kể cả khi $T=0$.

Mỗi con trỏ chỉ tăng và đi qua dãy nhiều nhất một lần. Mỗi lượt tính mất $O(N)$ thời gian; số lượt là hằng số, nên tổng thời gian $O(N)$, bộ nhớ $O(N)$ cho tổng tiền tố.

Dùng số nguyên 64 bit cho tổng tiền tố và các ngưỡng vì tổng có thể đạt $2\cdot10^{14}$. Không nhận đoạn rỗng làm đáp án.
