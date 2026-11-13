## Chuyển thành bài toán đếm

Với một ngưỡng $x$, thay $A_i$ bằng $+1$ nếu $A_i\ge x$, ngược lại bằng $-1$. Trung vị trên của một đoạn ít nhất bằng $x$ khi và chỉ khi tổng của đoạn sau biến đổi không âm: số phần tử ít nhất bằng $x$ phải chiếm ít nhất một nửa độ dài đoạn, làm tròn lên khi độ dài lẻ.

Gọi $P_0=0,P_i$ là tổng tiền tố. Cần đếm các cặp $0\le i<j\le N$ có $P_i\le P_j$. Quét $j$ tăng dần và dùng Fenwick lưu tần suất các tổng tiền tố đã gặp. Các tổng thuộc $[-N,N]$, nên chỉ cần dịch chỉ số; truy vấn **bao gồm cả trường hợp bằng nhau**.

Đặt $M=N(N+1)/2$. Trung vị trên của $B$ ít nhất bằng $x$ khi có ít nhất $\lceil M/2\rceil$ phần tử của $B$ không nhỏ hơn $x$. Tìm nhị phân giá trị lớn nhất thỏa điều kiện này trong các giá trị phân biệt của $A$.

## Tính đúng đắn

Phép biến đổi diễn tả chính xác điều kiện một đoạn có trung vị ít nhất bằng ngưỡng. Fenwick đếm mỗi đoạn đúng một lần qua cặp tổng tiền tố của nó. Do đó phép kiểm tra ngưỡng trả về đúng điều kiện đối với trung vị của toàn bộ $B$. Điều kiện đơn điệu theo $x$, và kết quả phải là một giá trị trong $A$, nên tìm nhị phân cho đúng đáp án.

## Độ phức tạp

$O(N\log^2 N)$ thời gian, $O(N)$ bộ nhớ. Dùng số nguyên 64 bit cho số đoạn.
