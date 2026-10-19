# BS52C — Hướng dẫn giải

Sắp xếp mảng $A$ không giảm. Với ngưỡng $x$, gọi $c$ là số phần tử có giá trị không vượt $x$.

Một nhóm có trung vị không vượt $x$ khi và chỉ khi ít nhất hai phần tử của nhóm không vượt $x$. Hai trường hợp rời nhau là:

- Cả ba phần tử không vượt $x$: $\binom c3$ nhóm.
- Đúng hai phần tử không vượt $x$: $\binom c2(N-c)$ nhóm.

Do đó số mức đánh giá không vượt $x$ là

$$F(x)=\binom c3+\binom c2(N-c).$$

Với mỗi giá trị phân biệt $V$ của mảng đã sắp xếp, tính $c$ là vị trí cuối cùng của nhóm giá trị $V$ (đánh số từ $1$) và lưu $F(V)$. Với truy vấn $K$, tìm giá trị $V$ đầu tiên có $F(V)\ge K$. Theo định nghĩa thứ hạng, đây chính là phần tử nhỏ thứ $K$. Phải xử lý cả nhóm giá trị trùng nhau khi tính $c$.

Độ phức tạp $O(N\log N+Q\log N)$, bộ nhớ $O(N)$. Dùng số nguyên 64 bit, kể cả $K$. Với $N\le300000$, tích $N(N-1)(N-2)$ nhỏ hơn $2.7\cdot10^{16}$, nên các phép tính đều vừa kiểu này.

Lời giải đối chiếu cố định vị trí giữa $i$ trong mảng đã sắp xếp (đánh số từ $0$). Có $i(N-1-i)$ nhóm nhận $A_i$ làm giá trị giữa, bằng cách chọn một vị trí trước và một vị trí sau. Lập tổng tiền tố các trọng số này rồi tìm kiếm nhị phân theo $K$. Kể cả khi các giá trị bằng nhau, mỗi bộ ba vẫn có đúng một vị trí giữa và được đếm một lần.
