# Lời giải KHUNGSANG — Tổng diện tích các khung sáng

## Xét từng hàng làm đáy

Với một hàng đáy cố định, gọi $H_j$ là số ô $1$ liên tiếp đi lên từ ô ở cột $j$. Khi đọc hàng mới, tăng $H_j$ nếu ô bằng $1$, ngược lại đặt bằng $0$.

Với một đoạn cột $[l,r]$ rộng $w=r-l+1$ và $h=\min(H_l,\ldots,H_r)$, mọi hình có đáy hiện tại và cùng đoạn cột có chiều cao từ $1$ tới $h$. Tổng diện tích của chúng là

$$w\cdot T(h),\qquad T(h)=\frac{h(h+1)}2.$$

Mỗi hình có đúng một hàng đáy, nên cộng kết quả trên mọi hàng sẽ đếm đúng một lần.

## Nhóm điểm bắt đầu bằng stack đơn điệu

Quét đầu phải $r$ của đoạn cột từ trái sang phải. Stack gom các điểm bắt đầu $l$ có cùng cực tiểu hiện tại $h$. Mỗi nhóm lưu:

- Giá trị cực tiểu $h$.
- Số điểm bắt đầu $c$.
- Tổng chỉ số điểm bắt đầu $s$.

Giữ hai tổng toàn cục

$$P=\sum_l T(\min H[l..r]),\qquad Q=\sum_l l\,T(\min H[l..r]).$$

Tổng diện tích của các hình với đầu phải $r$ và đáy hiện tại là

$$\sum_l(r-l+1)T(\min H[l..r])=(r+1)P-Q.$$

Khi thêm chiều cao $H_r$, tạo nhóm ban đầu $(H_r,1,r)$. Trong khi đỉnh stack có chiều cao không nhỏ hơn $H_r$, bỏ đóng góp nhóm đó khỏi $P,Q$, cộng số lượng và tổng chỉ số của nó vào nhóm mới. Sau đó đưa nhóm mới lên stack và thêm đóng góp mới. Các nhóm còn lại không đổi cực tiểu.

Chiều cao $0$ vẫn được xử lý bình thường; $T(0)=0$, nên các đoạn đi qua ô $0$ không gây chi phí nhưng vẫn ngăn việc gộp sai sang hàng/cột khác.

## Chứng minh đúng

Các điểm bắt đầu được phân thành các nhóm liên tiếp với cùng cực tiểu. Khi thêm một cột, chỉ các nhóm có cực tiểu ít nhất $H_r$ đổi sang $H_r$; chúng chính là một dãy nhóm trên đỉnh stack. Bước gộp cập nhật đúng các nhóm này, nên $P,Q$ giữ đúng định nghĩa. Công thức $(r+1)P-Q$ nhân đúng chiều rộng cho từng điểm bắt đầu. Cộng các đầu phải rồi cộng các đáy cho tổng diện tích yêu cầu.

## Độ phức tạp và số nguyên

- Mỗi cột vào/ra stack nhiều nhất một lần trong một hàng.
- Tổng thời gian $O(RC)$, bộ nhớ $O(C)$; lời giải mẫu chỉ đọc từng hàng.
- Dùng `long long` cho $T(h)$, số lượng, tổng chỉ số, các tổng và đáp án; không lấy modulo.
- Với $P=RC\le10^6$, số hình không vượt $P(P+1)/2$ vì mỗi hình được xác định bởi hai ô góc đối diện. Mỗi diện tích không vượt $P$, nên tổng không vượt $P^2(P+1)/2<5.1\cdot10^{17}$, nằm trong số nguyên 64 bit.
- Một hàng toàn $1$ dài $C$ có đáp án $C(C+1)(C+2)/6$, không phải chỉ $C(C+1)/2$.
