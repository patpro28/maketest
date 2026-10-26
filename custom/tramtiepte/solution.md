# Lời giải TRAMTIEPTE — Trạm tiếp tế

## Ý tưởng

Tách phí xây trạm khỏi phí vận chuyển. Đặt

$$F(u)=\sum_i A_i d(u,i),\qquad Q=\sum_i A_i.$$

Chọn gốc $1$. Gọi $S_v$ là tổng nhu cầu trong cây con gốc $v$. Duyệt cây để tính khoảng cách từ $1$, suy ra $F(1)$; duyệt thứ tự ngược để tính các $S_v$.

Xét cạnh cha $u$ nối con $v$ dài $w$. Khi chuyển trạm từ $u$ sang $v$:

- Mỗi kiện hàng trong cây con $v$ đi ít hơn $w$, giảm tổng $S_vw$.
- Mỗi kiện hàng bên ngoài cây con $v$ đi nhiều hơn $w$, tăng tổng $(Q-S_v)w$.

Do đó

$$F(v)=F(u)+(Q-2S_v)w.$$

Duyệt các đỉnh theo thứ tự cha trước con để tính toàn bộ $F$. Cuối cùng lấy giá trị nhỏ nhất của $F(u)+B_u$; duyệt chỉ số tăng dần và chỉ thay đáp án khi chi phí nhỏ hơn để xử lý phá hòa.

## Chứng minh đúng

Khoảng cách từ gốc và tổng nhu cầu cây con được tính đúng nhờ đường đi duy nhất trong cây. Công thức chuyển gốc xét đủ hai tập đỉnh rời nhau: bên trong và bên ngoài cây con $v$, với độ thay đổi khoảng cách chính xác là $-w$ và $+w$. Vì vậy, từ $F(u)$ đúng sẽ tính được $F(v)$ đúng. Theo thứ tự duyệt, mọi chi phí vận chuyển đều đúng. So sánh thêm phí xây trạm ở mọi đỉnh cho đáp án tối ưu; quy tắc chỉ thay khi nhỏ hơn giữ lại chỉ số nhỏ nhất khi hòa.

## Độ phức tạp và lưu ý

- Thời gian $O(N)$; bộ nhớ $O(N)$.
- Dùng `long long` cho nhu cầu cộng dồn, khoảng cách và mọi phép nhân, tổng chi phí.
- Một cận trên đơn giản cho tổng chi phí là $10^{15}+N\cdot1000\cdot(N-1)\cdot1000<4.1\cdot10^{16}$, nằm trong số nguyên có dấu $64$ bit.
- Không cộng $B_u$ vào $F(u)$ rồi áp dụng công thức chuyển gốc: phí xây dựng không tuân theo công thức này.
- Lời giải mẫu dùng thứ tự duyệt lưu trong mảng, tránh tràn ngăn xếp khi cây là đường thẳng dài $200000$ đỉnh.
- Mọi nhu cầu bằng $0$ thì chỉ cần chọn $B_u$ nhỏ nhất, nhưng thuật toán vẫn xử lý trực tiếp được.

## Hướng làm ban đầu

Với dữ liệu nhỏ, thử từng vị trí đặt trạm và duyệt cây để tính tổng chi phí, mất $O(N^2)$. Đây cũng là cách kiểm chứng độc lập cho lời giải nhanh.
