# MATHA2 — Hướng dẫn giải

Với số nguyên dương $d$, số bội của $d$ trong đoạn $[L,R]$ là:

$$C_d(L,R)=\left\lfloor\frac{R}{d}\right\rfloor-\left\lfloor\frac{L-1}{d}\right\rfloor.$$

Công thức đúng vì có $\lfloor R/d\rfloor$ bội trong $[1,R]$ và $\lfloor(L-1)/d\rfloor$ bội trong $[1,L-1]$.

Nếu $x$ chia hết cho $A$ và $x/A$ chẵn thì $x=2Ak$ với một số nguyên dương $k$. Chiều ngược lại cũng đúng. Do đó, đáp án là:

$$C_{2A}(L,R).$$

Mỗi bộ dữ liệu được xử lý trong $O(1)$ thời gian và $O(1)$ bộ nhớ phụ. Tổng thời gian là $O(T)$.

Dùng số nguyên 64 bit cho $L,R,A$ và các phép tính; không dùng số thực. Đáp án có thể vượt giới hạn số nguyên 32 bit. Khi $L=1$, giá trị $L-1=0$ vẫn áp dụng được công thức.

## Theo từng subtask

- Subtask 1 (60%): vì $T=1$ và $R\le10^6$, có thể duyệt từng số $x$ trong đoạn và kiểm tra trực tiếp hai điều kiện của đề. Thời gian $O(R-L+1)$, bộ nhớ phụ $O(1)$.
- Subtask 2 (30%): vì $A=1$, bài toán trở thành đếm số chẵn trong đoạn. Đáp án là $\left\lfloor\frac{R}{2}\right\rfloor-\left\lfloor\frac{L-1}{2}\right\rfloor$. Xử lý mỗi bộ dữ liệu trong $O(1)$ và dùng số nguyên 64 bit.
- Subtask 3 (10%): dùng công thức đếm bội tổng quát ở trên, với $A$ bất kỳ theo giới hạn chung.
