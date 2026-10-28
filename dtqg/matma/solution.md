# Lời giải MATMA — Thông điệp có thưởng và phạt

## Subtask 1 — 30%

Liệt kê $3^L$ xâu độ dài $L$. Với mỗi xâu, kiểm tra từng vị trí bắt đầu của từng mẫu để cộng điểm. Các lần xuất hiện chồng lấn và các mẫu trùng nhau đều được tính riêng. Với $L\le10$, phương án này đủ nhỏ.

## Automaton Aho–Corasick

Dựng trie từ các mẫu. Tại nút kết thúc mẫu, cộng $W_i$ vào điểm của nút, không ghi đè: nhiều mẫu có thể trùng nhau.

Dựng liên kết thất bại và các chuyển tiếp theo ba chữ bằng BFS. Gọi $g(v)$ là tổng điểm mọi mẫu kết thúc tại trạng thái $v$, bao gồm các mẫu là hậu tố thông qua liên kết thất bại:

$$g(v)=\operatorname{terminalScore}(v)+g(\operatorname{link}(v)).$$

Khi thêm một ký tự, automaton chuyển từ $u$ tới $v$ và nhận thêm $g(v)$. Đây là điểm của mọi mẫu có lần xuất hiện kết thúc tại ký tự vừa thêm, nên không bỏ sót mẫu ngắn là hậu tố của mẫu dài.

Số trạng thái $S\le1+\sum|S_i|\le81$.

## Subtask 2 — 30%

Đặt $D[t][u]$ là điểm lớn nhất của một xâu đúng $t$ ký tự, kết thúc ở trạng thái $u$.

- $D[0][\text{root}]=0$; các trạng thái khác không thể tới.
- Với mỗi ký tự $c$, chuyển $v=\operatorname{go}(u,c)$ và cập nhật $D[t+1][v]$ bằng $D[t][u]+g(v)$.

Lấy max trên mọi trạng thái ở lớp $L$. Thời gian $O(3LS)$, bộ nhớ $O(S)$ khi chỉ giữ hai lớp. Với $L\le10^5$, số chuyển tiếp không quá khoảng $2.43\cdot10^7$.

## Subtask 3 — 40%: ma trận max-plus

Gọi $A[u][v]$ là điểm lớn nhất khi đi từ trạng thái $u$ tới $v$ bằng đúng một ký tự. Nếu không có ký tự nào thực hiện được chuyển đó thì giá trị là $-\infty$.

Định nghĩa phép nhân:

$$(A\otimes B)[u][v]=\max_k(A[u][k]+B[k][v]).$$

Nếu $A$ biểu diễn đi đúng $x$ bước và $B$ biểu diễn đi đúng $y$ bước, tích này biểu diễn đi đúng $x+y$ bước: chọn trạng thái trung gian $k$ tốt nhất và cộng điểm hai phần. Phép nhân có tính kết hợp, nên dùng bình phương nhanh để tính chuyển tiếp đúng $L$ bước.

Lời giải mẫu giữ một vector điểm ban đầu chỉ có gốc bằng $0$. Khi bit tương ứng của $L$ bật, nhân vector với ma trận lũy thừa; giữa các bit, bình phương ma trận. Đáp án là phần tử lớn nhất của vector cuối.

## Chứng minh đúng

Sau mỗi tiền tố, trạng thái Aho–Corasick lưu hậu tố dài nhất phù hợp với một tiền tố mẫu. Tổng điểm $g(v)$ đếm đúng mọi mẫu kết thúc tại vị trí vừa thêm. Mỗi lần xuất hiện có đúng một vị trí kết thúc, nên điểm của đường đi trong automaton bằng chính xác điểm xâu.

Ngược lại, mỗi chuỗi chuyển tiếp hợp lệ tương ứng với một cách chọn các ký tự của xâu. Phép nhân max-plus xét đủ mọi trạng thái ở chỗ nối hai phần và lấy điểm lớn nhất. Bằng quy nạp theo số bước và các phép bình phương, vector cuối chứa đúng điểm tốt nhất cho xâu dài $L$ ở từng trạng thái. Lấy max cho đáp án yêu cầu.

## Độ phức tạp và lưu ý

- Dựng automaton: $O(\sum|S_i|+3S)$.
- Lũy thừa: $O(S^3\log L)$ thời gian, $O(S^2)$ bộ nhớ.
- Không khởi tạo ma trận bằng $0$: nhiều chuyển tiếp không tồn tại và điểm tối ưu có thể âm.
- Không cho phép dừng sớm hoặc chọn xâu rỗng: cần đúng $L$ bước.
- Dùng `long long` cho $L$, điểm và mọi phép cộng. Tổng trị tuyệt đối không vượt $ML\max|W_i|\le2\cdot10^{16}$.
- Dùng một hằng âm đủ nhỏ, như `-4e18`, cho trạng thái không thể tới. Không cộng các giá trị đánh dấu không thể tới.
- Mẫu dài hơn $L$ không xuất hiện; chuỗi nhiều chữ giống nhau và mẫu lồng nhau vẫn phải đếm đủ các lần chồng lấn.