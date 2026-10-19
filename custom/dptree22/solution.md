# Lời giải — Phủ sóng các ngôi làng

### Trạng thái

Chọn đỉnh $1$ làm gốc. Với cây con của $u$, lưu ba giá trị:

- $S[u]$: đặt trạm tại $u$, mọi đỉnh trong cây con đều được phủ.
- $D[u]$: không đặt trạm tại $u$, mọi đỉnh đều được phủ và $u$ được phủ bởi ít nhất một người con có trạm.
- $P[u]$: không đặt trạm tại $u$, mọi đỉnh khác $u$ trong cây con đều được phủ; $u$ chưa được phủ và cần trạm tại cha.

Một trạng thái không thể đạt được có giá trị $+\infty$.

### Chuyển trạng thái

Khi đặt trạm tại $u$, trạm này có thể phủ người con đang chờ cha:

$$
S[u]=C_u+\sum_{v\text{ là con của }u}\min(S[v],D[v],P[v]).
$$

Khi $u$ chờ cha phủ, không người con nào được có trạm, vì như vậy $u$ đã được phủ. Mỗi con phải được phủ từ phía dưới:

$$
P[u]=\sum_{v\text{ là con của }u}D[v].
$$

Khi $u$ được phủ bởi con, mỗi con phải dùng trạng thái $S$ hoặc $D$, và ít nhất một con phải dùng $S$. Đặt:

$$
B=\sum_{v\text{ là con của }u}\min(S[v],D[v]).
$$

Khi đó:

$$
D[u]=B+\min_{v\text{ là con của }u}\bigl(S[v]-\min(S[v],D[v])\bigr).
$$

Phần cộng thêm ép ít nhất một con có trạm. Nếu lựa chọn cơ sở đã chứa một con có trạm thì phần cộng thêm bằng $0$.

Tại lá: $S[u]=C_u$, $D[u]=+\infty$, $P[u]=0$. Gốc không có cha nên không được chờ phủ; đáp án là $\min(S[1],D[1])$.

### Tính đúng đắn

Với một đỉnh, ba trạng thái phân biệt đầy đủ việc có trạm, được con phủ, hoặc cần cha phủ. Chỉ trạm tại chính đỉnh, cha hoặc con trực tiếp mới phủ được đỉnh đó.

Giả sử các trạng thái ở các con đã đúng. Nếu $u$ có trạm thì cả ba trạng thái ở mỗi con đều được phép. Nếu $u$ không có trạm thì không con nào được chờ cha phủ; các con chỉ được dùng $S$ hoặc $D$. Trong số này, ít nhất một con dùng $S$ tương ứng với trạng thái $D[u]$, còn không con nào dùng $S$ tương ứng với $P[u]$.

Các cây con độc lập sau khi cố định trạng thái của $u$. Công thức cho $D[u]$ trước hết lấy phương án tốt nhất của từng con, rồi trả chi phí bổ sung nhỏ nhất để bảo đảm có một trạm ở con. Nó không bỏ sót phương án nào có thể tốt hơn. Do đó cả ba công thức đều tối ưu theo quy nạp từ lá lên.

Tại gốc chỉ hai trạng thái được phủ là hợp lệ, nên lấy min của chúng cho đúng đáp án.

### Cài đặt và độ phức tạp

Lưu thứ tự duyệt cây bằng vòng lặp và xử lý ngược thứ tự, tránh DFS đệ quy trên cây dây. Tổng và giá trị trung gian dùng số nguyên 64 bit. Chọn $INF=2^{60}$ và chặn các tổng biểu diễn bất khả thi ở $INF$ để tránh cộng dồn vô hạn.

Mỗi cạnh được xét số lần hằng số. Thời gian $O(N)$, bộ nhớ $O(N)$.
