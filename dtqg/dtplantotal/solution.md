## Biểu diễn nhị phân và ba số nhớ

Đặt $S_a=\sum_i a_i$, $S_b=\sum_i b_i$. Vì hệ số dương, mỗi nghiệm có $x_i\le10^{18}<2^{60}$. Biểu diễn các $x_i$ bằng đúng 60 bit, thêm số $0$ ở đầu.

Ở vị trí bit $t$, chọn tập $S$ những loại có bit hiện tại bằng $1$. Tập này đóng góp

$$u_S=\sum_{i\in S}a_i,\qquad v_S=\sum_{i\in S}b_i,\qquad h_S=|S|.$$

Đặt $dp_t[c_a][c_b][c_c]$ là số cách chọn $t$ bit thấp, đã khớp $t$ bit thấp của ba mục tiêu và có ba số nhớ tương ứng. Cụ thể, với $x_i^{(t)}$ là phần $t$ bit thấp đã chọn:

$$\sum_i a_ix_i^{(t)}=(A\bmod2^t)+c_a2^t,$$

và tương tự cho $B$ với hệ số $b_i$, cho $C$ với hệ số $1$.

## Phép chuyển

Gọi $\alpha_t,\beta_t,\gamma_t$ là ba bit mục tiêu. Chỉ nhận tập $S$ nếu $c_a+u_S$, $c_b+v_S$, $c_c+h_S$ có chẵn lẻ tương ứng với ba bit đó. Các số nhớ mới là

$$c_a'=\frac{c_a+u_S-\alpha_t}{2},\quad c_b'=\frac{c_b+v_S-\beta_t}{2},\quad c_c'=\frac{c_c+h_S-\gamma_t}{2}.$$

Khởi tạo $dp_0[0][0][0]=1$. Sau 60 bit, chỉ lấy $dp_{60}[0][0][0]$; số nhớ khác $0$ tương ứng vượt mục tiêu ở các bit cao.

## Miền số nhớ và gộp lựa chọn

Luôn có $0\le c_a<S_a$, $0\le c_b<S_b$, $0\le c_c<m$. Ví dụ nếu $c_a<S_a$ thì

$$c_a'\le\left\lfloor\frac{(S_a-1)+S_a}{2}\right\rfloor=S_a-1.$$

Ba miền có nhiều nhất $16\cdot16\cdot8$ trạng thái mỗi lớp.

Tính trước $ways[u][v][h]$ là số tập con có bộ tổng $(u,v,h)$. Các tập khác nhau cùng bộ tổng tạo cùng chuyển, nên thay các phép cộng riêng bằng phép cộng $dp\cdot ways$ modulo $10^9$. Có thể liệt kê $2^m$ tập để lập bảng. Không gộp các loại trùng hệ số thành một loại duy nhất vì chúng vẫn tạo các phương án khác nhau.

Chia bộ tổng thành tám nhóm theo ba tính chẵn lẻ. Với mỗi trạng thái, chỉ duyệt nhóm khớp ba bit mục tiêu.

## Chứng minh đúng

Bất biến số nhớ đúng ở lớp khởi tạo. Ba phương trình chuyển là điều kiện cần và đủ để khớp thêm một bit của cả ba tổng, nên bất biến được duy trì.

Mỗi bộ số lượng có duy nhất một chuỗi tập bit gồm 60 vị trí. Ngược lại, một chuỗi được nhận với số nhớ cuối bằng $0$ tạo đúng ba tổng mục tiêu. Bảng $ways$ giữ đủ số tập tạo từng bộ tổng, nên việc gộp không đổi số phương án. Do đó đáp án được đếm đúng một lần cho mỗi bộ hợp lệ.

## Độ phức tạp

Đặt $H$ là số bộ tổng có $ways>0$, khi đó $H\le2^m$. Tiền xử lý mất $O(m2^m)$; DP mất $O(60S_aS_bmH)$, bộ nhớ $O(S_aS_bm+H)$. Không gộp lựa chọn thì chặn thời gian là $O(60S_aS_bm2^m)$, khoảng 31,5 triệu lượt xét ở giới hạn lớn nhất.

Dùng số nguyên 64 bit cho các mục tiêu, các phép dịch bit và tích trước khi lấy modulo. Không dùng nghịch đảo modulo vì $10^9$ không phải số nguyên tố.
