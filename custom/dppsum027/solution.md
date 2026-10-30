# PREFIX027 — Hướng dẫn giải

Đặt $B_1=0$. Với $i\ge2$, đặt $B_i=1$ nếu $A_i>A_{i-1}$, ngược lại bằng $0$. Tính tổng tiền tố $P$ của $B$. Truy vấn trả về $P_R-P_L$.

Tính đúng đắn: $B_i$ biểu diễn đúng một lần tăng tại cặp kết thúc ở $i$. Trong đoạn chỉ có các cặp kết thúc từ $L+1$ đến $R$, nên tổng các $B_i$ này là đáp án. Không dùng $P_{L-1}$ vì sẽ tính nhầm cặp đi từ ngoài đoạn vào $L$.

Thời gian $O(N+Q)$, bộ nhớ $O(N)$.

Các bộ đếm không vượt quá $N$.
