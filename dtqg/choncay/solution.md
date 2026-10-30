# Lời giải CHONCAY — Chọn đỉnh trên cây động

## DP tĩnh và lý do cập nhật khó

Đặt gốc cây tại $1$. Gọi $f_0(u),f_1(u)$ là giá trị tốt nhất trong cây con $u$, khi lần lượt không chọn và chọn $u$:

$$f_0(u)=\sum_{v\text{ là con của }u}\max(f_0(v),f_1(v)),$$
$$f_1(u)=W_u+\sum_{v\text{ là con của }u}f_0(v).$$

Đáp án là $\max(f_0(1),f_1(1))$. Giá trị $f_1$ có thể âm; không thay nó bằng $0$, vì trạng thái này bắt buộc chọn đỉnh đang xét. Trạng thái $f_0$ luôn cho phép chọn tập rỗng.

Sau khi đổi trọng số tại một đỉnh, các giá trị DP trên đường lên gốc có thể thay đổi. Cập nhật lần lượt từng tổ tiên sẽ chậm trên cây dây. Ta cần gộp việc truyền DP trên một đường dài bằng ma trận.

## Tách đóng góp con nặng và con nhẹ

Chọn con nặng $h(u)$ là con có kích thước cây con lớn nhất. Các con khác là con nhẹ. Đặt

$$g_0(u)=\sum_{v\text{ là con nhẹ}}\max(f_0(v),f_1(v)),$$
$$g_1(u)=W_u+\sum_{v\text{ là con nhẹ}}f_0(v).$$

Khi đó

$$f_0(u)=g_0(u)+\max(f_0(h),f_1(h)),\qquad f_1(u)=g_1(u)+f_0(h).$$

Nếu không có con nặng, dùng vector giả $(0,0)^\mathsf{T}$. Hai công thức được viết thành **vector cột**:

$$\begin{pmatrix}f_0(u)\\f_1(u)\end{pmatrix}=
M_u\otimes\begin{pmatrix}f_0(h)\\f_1(h)\end{pmatrix},\qquad
M_u=\begin{pmatrix}g_0(u)&g_0(u)\\g_1(u)&-\infty\end{pmatrix}.$$

Ở bài này, hàng là trạng thái đầu ra tại cha, cột là trạng thái đầu vào từ con nặng. Giữ nhất quán quy ước này khi nhân.

## Tích ma trận trên chuỗi nặng

Phân rã heavy-light chia cây thành các chuỗi cạnh nặng. Đánh số các đỉnh để mỗi chuỗi nằm trên một đoạn liên tiếp, theo thứ tự từ đầu chuỗi xuống cuối chuỗi.

Với chuỗi $u_1,u_2,\ldots,u_k$, ta có

$$\begin{pmatrix}f_0(u_1)\\f_1(u_1)\end{pmatrix}=
M_{u_1}\otimes M_{u_2}\otimes\cdots\otimes M_{u_k}\otimes\begin{pmatrix}0\\0\end{pmatrix}.$$

Nếu tích của chuỗi là $B$, hai giá trị ở đầu chuỗi là $\max(B[0][0],B[0][1])$ và $\max(B[1][0],B[1][1])$. Dùng segment tree để cập nhật một ma trận đỉnh và lấy tích một chuỗi trong $O(\log N)$.

## Truyền một cập nhật qua các chuỗi

Khi gán $W_u=x$, tăng $g_1(u)$ thêm $x-W_u^{\text{cũ}}$. Chỉ ma trận $M_u$ cần đổi ngay tại chuỗi chứa $u$.

Lặp các bước sau với đỉnh cần cập nhật $v$:

1. Gọi $a$ là đầu chuỗi chứa $v$. Lấy cặp DP cũ $(b_0,b_1)$ tại $a$ từ segment tree; lúc này ma trận mới của $v$ chưa được đưa vào cây.
2. Cập nhật ma trận $M_v$ trên segment tree, rồi lấy cặp DP mới $(c_0,c_1)$ tại $a$.
3. Nếu $a$ là gốc, kết thúc. Nếu không, đặt $p=\operatorname{parent}(a)$. Đỉnh $a$ là con nhẹ của $p$, nên cập nhật

$$g_0(p)\mathrel{+}=\max(c_0,c_1)-\max(b_0,b_1),\qquad
g_1(p)\mathrel{+}=c_0-b_0.$$

4. Gán $v=p$ và tiếp tục. Ma trận ở $p$ sẽ được đưa vào segment tree ở vòng kế tiếp.

Sau khi hoàn tất, lấy DP tại đầu chuỗi chứa gốc và in max của hai trạng thái. Mọi tổng đóng góp con nhẹ đều được duy trì bằng chênh lệch; không duyệt lại danh sách con sau mỗi cập nhật.

## Chứng minh đúng

Công thức DP tĩnh là đúng vì các cây con độc lập sau khi cố định việc chọn đỉnh cha. Tách một con nặng chỉ đổi cách nhóm các số hạng, nên ma trận $M_u$ biểu diễn chính xác quan hệ DP giữa $u$ và con nặng. Tích ma trận vì thế truyền đúng DP qua toàn bộ chuỗi.

Một cập nhật trong chuỗi chỉ có thể ảnh hưởng ra ngoài chuỗi qua DP tại đầu chuỗi. Đầu chuỗi là con nhẹ của đỉnh cha ở chuỗi tiếp theo; hai công thức chênh lệch thay đúng đóng góp cũ của con nhẹ bằng đóng góp mới. Theo quy nạp qua các chuỗi tới gốc, mọi ảnh hưởng của cập nhật được truyền đầy đủ và đáp án tại gốc đúng.

## Độ phức tạp và lưu ý

Khi đi qua cạnh nhẹ từ cha xuống con, kích thước cây con giảm ít nhất một nửa. Do đó một đường lên gốc đi qua $O(\log N)$ chuỗi. Mỗi vòng dùng truy vấn tích và cập nhật điểm trong $O(\log N)$, nên mỗi cập nhật mất $O(\log^2 N)$ với ma trận kích thước $2$.

Tiền xử lý mất $O(N)$, tổng thời gian $O(N+Q\log^2N)$ và bộ nhớ $O(N)$. Lời giải mẫu duyệt cây không đệ quy để xử lý được cây dây dài $10^5$. Các tổng, chênh lệch và phần tử ma trận đều dùng số nguyên có dấu $64$ bit; bỏ qua số hạng chứa $-\infty$.
