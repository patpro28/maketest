# Lời giải

Đặt $M=10^9+7$. Khi chọn đỉnh bắt đầu $r$, xem cây được gốc hóa tại $r$.

Một thứ tự ghi số hợp lệ khi và chỉ khi mọi đỉnh cha được ghi số trước các đỉnh con. Thật vậy, các đỉnh đã ghi số luôn tạo thành một phần liên thông chứa $r$, nên muốn ghi số lên một đỉnh phải đi qua cha của nó trước. Ngược lại, nếu cha đã được ghi số thì đỉnh con thỏa mãn điều kiện của thao tác.

## Đếm với một gốc cố định

Gọi $s_r(u)$ là số đỉnh trong cây con của $u$ khi gốc là $r$. Số thứ tự hợp lệ là

$$
\operatorname{ans}[r]=\frac{N!}{\prod_u s_r(u)}.
$$

Để chứng minh, xét một cây con gốc $u$ có kích thước $s$, với các cây con của các con có kích thước $s_1,\ldots,s_t$. Đỉnh $u$ phải đứng đầu. Sau đó có thể xen kẽ các thứ tự hợp lệ của các cây con theo

$$
\frac{(s-1)!}{s_1!\cdots s_t!}
$$

cách. Nhân với số cách trong từng cây con và áp dụng quy nạp, ta được công thức trên. Mọi phép chia được thực hiện bằng cách nhân với nghịch đảo modulo $M$; tất cả kích thước đều nhỏ hơn $M$.

## Đổi gốc

Gốc hóa cây tại đỉnh $1$, tính $s(u)=s_1(u)$ và đáp án cho đỉnh $1$.

Xét một cạnh nối cha $u$ với con $v$. Bỏ cạnh này chia cây thành hai phần có kích thước $s(v)$ và $N-s(v)$. Khi đổi gốc từ $u$ sang $v$, chỉ kích thước cây con của hai đỉnh $u,v$ thay đổi:

- Với gốc $u$, hai kích thước là $N$ và $s(v)$.
- Với gốc $v$, hai kích thước là $N-s(v)$ và $N$.

Vì vậy,

$$
\operatorname{ans}[v]
=\operatorname{ans}[u]\cdot s(v)\cdot (N-s(v))^{-1}\pmod M.
$$

Duyệt theo thứ tự cha trước con để tính đáp án cho mọi đỉnh. Lời giải dùng phép duyệt lặp để tránh tràn ngăn xếp trên cây dạng đường thẳng.

Tiền xử lý các nghịch đảo từ $1$ đến $N$ theo công thức

$$
\operatorname{inv}[1]=1,\qquad
\operatorname{inv}[i]=M-\left\lfloor\frac{M}{i}\right\rfloor
\operatorname{inv}[M\bmod i]\bmod M.
$$

Độ phức tạp thời gian: $O(N)$. Bộ nhớ: $O(N)$.
