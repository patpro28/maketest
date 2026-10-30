# PREFIX19 — Hướng dẫn giải

Gọi tổng toàn dãy là $T$. Nếu $T$ không chia hết cho $3$, đáp án bằng $0$. Ngược lại đặt $U=T/3$. Duyệt $j$ từ $1$ đến $N-1$, duy trì số vị trí $i<j$ có tổng tiền tố bằng $U$. Nếu tổng tiền tố tại $j$ bằng $2U$, cộng số vị trí đó vào đáp án; sau đó mới thêm $j$ vào bộ đếm nếu tổng tiền tố tại $j$ bằng $U$.

Tính đúng đắn: Ba đoạn bằng tổng khi và chỉ khi hai tổng tiền tố tại i và j lần lượt bằng U và 2U. Bộ đếm chỉ chứa i nhỏ hơn j, và j không vượt N-1, nên cả ba đoạn không rỗng. Cập nhật đáp án trước bộ đếm còn bảo đảm đúng khi U=0. Mỗi cặp hợp lệ được đếm đúng một lần tại j của nó.

Thời gian: $O(N)$. Bộ nhớ: $O(N)$.

Dùng số nguyên 64 bit cho tổng và số cách.
