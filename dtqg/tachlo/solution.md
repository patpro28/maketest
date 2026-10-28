# Lời giải TACHLO — Chia lô tránh xung đột

## Quy hoạch động

Gọi $C(l,r)$ là số cặp cùng loại trong đoạn $[l,r]$. Đặt $D_g[i]$ là chi phí nhỏ nhất chia $i$ kiện đầu thành đúng $g$ lô không rỗng.

$$D_g[i]=\min_{g-1\le j<i}\{D_{g-1}[j]+C(j+1,i)\}.$$

Có $D_0[0]=0$, $D_0[i>0]=+\infty$, và các trạng thái $i<g$ không khả thi. Đáp án là $D_K[N]$.

Công thức xét vị trí $j$ kết thúc $g-1$ lô đầu, còn lô cuối là $[j+1,i]$. Mọi cách chia hợp lệ có đúng một vị trí như vậy, nên truy hồi đúng.

## Subtask 1 và 2 — 30% mỗi subtask

Với mỗi đầu phải $r$, kéo đầu trái từ $r$ về $1$, giữ tần suất các loại. Khi thêm một kiện thuộc loại đã có $f$ kiện, số cặp tăng thêm $f$. Nhờ đó tính toàn bộ bảng $C(l,r)$ trong $O(N^2)$.

Sau đó tính DP trực tiếp trong $O(KN^2)$, bộ nhớ $O(N^2+N)$. Phù hợp $N\le200$ và $N\le3000$. Ở mức $3000$, có thể lưu bảng chi phí bằng `int` vì mỗi đoạn có không quá $\binom{3000}{2}$ cặp; các lớp DP vẫn nên dùng `long long`.

## Tính chất Monge

Với $a\le b\le c\le d$, ta có

$$C(a,c)+C(b,d)\le C(a,d)+C(b,c).$$

Hiệu vế phải trừ vế trái chính là số cặp cùng loại mà một đầu nằm trong $[a,b-1]$, đầu còn lại trong $[c+1,d]$, nên không âm.

Gọi $\operatorname{opt}_g(i)$ là chỉ số chia nhỏ nhất đạt tối ưu ở $D_g[i]$. Tính chất Monge cho phép suy ra

$$\operatorname{opt}_g(i)\le\operatorname{opt}_g(i+1).$$

Để thấy điều này, giả sử hai đầu phải $x<y$ có các điểm chia tối ưu ngược thứ tự $p>q$. Nếu $p$ là một ứng viên hợp lệ ở $x$, thì cả $p,q$ đều hợp lệ cho hai đầu phải. Bất đẳng thức Monge cho hai điểm chia và hai đầu phải, kết hợp hai bất đẳng thức tối ưu, buộc các lựa chọn hoán đổi cũng tối ưu. Khi đó tại $x$ có thể dùng $q<p$, trái quy tắc chọn điểm chia nhỏ nhất. Vì vậy không có nghịch thế.

## Chia để trị một lớp DP

Hàm xử lý các đầu phải trong $[l,r]$, biết điểm chia tối ưu thuộc $[p,q]$:

1. Lấy $m=\lfloor(l+r)/2\rfloor$.
2. Thử điểm chia từ $p$ tới $\min(q,m-1)$ để tìm $D_g[m]$ và điểm chia tốt nhất $b$.
3. Xử lý nửa trái với khoảng điểm chia $[p,b]$.
4. Xử lý nửa phải với khoảng điểm chia $[b,q]$.

Khởi đầu lớp $g$ bằng các đầu phải $[g,N]$ và điểm chia $[g-1,N-1]$. Khi hòa, luôn giữ điểm chia nhỏ nhất.

## Không lưu bảng chi phí ở bản đầy đủ

Duy trì một cửa sổ $[L,R]$, tần suất $f_v$ và tổng số cặp $F$:

- Thêm một kiện loại $v$: $F\gets F+f_v$, rồi tăng $f_v$.
- Bỏ một kiện loại $v$: giảm $f_v$, rồi $F\gets F-f_v$.

Dịch hai đầu cửa sổ để trả $C(j+1,m)$ cho từng ứng viên được xét. Mỗi lần dịch một vị trí mất $O(1)$, không cần lưu bảng $N^2$ phần tử.

Trong một lớp, tổng số ứng viên và tổng độ dịch cửa sổ theo các mức chia để trị là $O(N\log N)$. Tại mỗi mức, các đoạn xét điểm chia nằm theo thứ tự và chỉ giao ở biên tối ưu, nên tổng độ dài của chúng là $O(N)$; độ dịch các đầu phải cũng có cùng cận. Có $O(\log N)$ mức.

## Chứng minh đúng và độ phức tạp

Truy hồi DP đúng theo cách chọn lô cuối. Tính đơn điệu bảo đảm các khoảng ứng viên truyền xuống hai nhánh luôn chứa điểm chia tối ưu. Cửa sổ giữ đúng số cặp nhờ công thức thêm/bỏ kiện. Vì vậy mọi lớp DP được tính đúng, và $D_K[N]$ là đáp án.

- Thời gian bản đầy đủ: $O(KN\log N)$.
- Bộ nhớ: $O(N)$.
- Chi phí lớn nhất là $\binom{10^5}{2}=4999950000$, vượt `int`. Dùng `long long` cho chi phí cửa sổ và DP.
- Phân biệt chỉ số kiện hàng với số kiện trong tiền tố: điểm chia $j$ tạo lô $[j+1,i]$.
- Bắt buộc đúng $K$ lô không rỗng; không cho $j=i$ hoặc trạng thái trước có ít hơn $g-1$ kiện.

## Kiểm chứng

Oracle liệt kê mọi tập điểm cắt khi $N\le14$, tính DP trực tiếp khi $N\le3000$. Test lớn có $K=1$ hoặc dãy tuần hoàn với các loại khác nhau trong một chu kỳ được kiểm tra bằng công thức đếm cặp và tính lồi theo độ dài lô. Các test lớn còn lại đối chiếu với cài đặt tối ưu thứ hai: đảo dãy, xét điểm chia giảm dần, giữ điểm chia lớn nhất khi hòa và duyệt nhánh phải trước. Cài đặt này vẫn dùng tính chất Monge; độ tin cậy của tính chất được kiểm tra thêm bằng vét cạn trên dữ liệu nhỏ.
