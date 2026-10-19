# MATHA3 — Hướng dẫn giải

Gọi $P=A+B$ và $F(x)$ là số phút bật trong $x$ phút đầu, với $F(0)=0$.

Có $\lfloor x/P\rfloor$ chu kỳ hoàn chỉnh, mỗi chu kỳ đóng góp $A$ phút bật. Phần còn lại có $x\bmod P$ phút; vì đèn bật ở đầu mỗi chu kỳ nên đóng góp $\min(x\bmod P,A)$ phút.

$$F(x)=\left\lfloor\frac{x}{A+B}\right\rfloor A+\min(x\bmod(A+B),A).$$

Đáp án cho $[L,R]$ là $F(R)-F(L-1)$. Công thức đếm từng phút đúng một lần theo chu kỳ, còn phép trừ loại đúng các phút trước $L$.

Độ phức tạp $O(Q)$, bộ nhớ phụ $O(1)$. Dùng số nguyên 64 bit cho thời gian và đáp án; mọi tích trong công thức không vượt $10^{18}$.

Lời giải đối chiếu chuyển phút sang chỉ số bắt đầu từ $0$, tách riêng phần chu kỳ đầu, phần chu kỳ cuối và các chu kỳ đầy đủ ở giữa.

### Theo subtask

- Subtask 1 (60%): chỉ có một truy vấn và $R\le10^6$, có thể duyệt từng phút và kiểm tra $(t-1)\bmod(A+B)<A$.
- Subtask 2 (30%): $A=1$, các phút bật là $1,1+(B+1),1+2(B+1),\ldots$. Với $x\ge1$, $F(x)=\lfloor(x-1)/(B+1)\rfloor+1$; đặt $F(0)=0$ rồi lấy hiệu hai tiền tố.
- Subtask 3 (10%): áp dụng công thức chu kỳ tổng quát ở trên.
