## Thêm trạng thái của bit trước

Viết mỗi $x_i$ bằng đúng 60 bit. Khi xử lý từ bit thấp lên bit cao, cần biết loại nào đã có bit $1$ tại vị trí ngay trước đó.

Đặt $dp_t[c_a][c_b][prev]$ là số cách chọn $t$ bit thấp, khớp các bit thấp của $A,B$, có hai số nhớ $c_a,c_b$ và mặt nạ $prev$ ghi các loại có bit $1$ ở vị trí $t-1$. Với $t=0$, dùng $prev=0$.

Nếu tập bit hiện tại là $cur$, điều kiện không có hai bit $1$ liên tiếp trong từng $x_i$ chính xác là

$$cur\mathbin{\&}prev=0.$$

## Số nhớ và chuyển trạng thái

Tính trước $u[cur]=\sum_{i\in cur}a_i$, $v[cur]=\sum_{i\in cur}b_i$. Gọi $\alpha_t,\beta_t$ là hai bit mục tiêu.

Từ trạng thái hữu hạn, duyệt các $cur$ rời $prev$. Chỉ nhận khi

$$c_a+u[cur]\equiv\alpha_t\pmod2,\qquad c_b+v[cur]\equiv\beta_t\pmod2.$$

Đặt

$$c_a'=\frac{c_a+u[cur]-\alpha_t}{2},\qquad c_b'=\frac{c_b+v[cur]-\beta_t}{2}.$$

Cộng $dp_t[c_a][c_b][prev]$ vào $dp_{t+1}[c_a'][c_b'][cur]$ modulo $10^9$.

Khởi tạo chỉ $dp_0[0][0][0]=1$. Sau 60 bit, đáp án là

$$\sum_{prev}dp_{60}[0][0][prev]\pmod{10^9}.$$

Mặt nạ cuối không bắt buộc bằng $0$: bit cao nhất của một số có thể bằng $1$. Tuy nhiên hai số nhớ cuối phải bằng $0$.

## Giới hạn số nhớ và liệt kê mặt nạ

Đặt $S_a=\sum_i a_i$, $S_b=\sum_i b_i$. Giữ $0\le c_a<S_a$, $0\le c_b<S_b$. Miền này bất biến vì $u[cur]\le S_a$ và

$$\left\lfloor\frac{S_a-1+S_a}{2}\right\rfloor=S_a-1,$$

tương tự cho nguyên liệu Q.

Với một $prev$, các $cur$ hợp lệ là các mặt nạ con của phần bù $prev$ trong $m$ bit. Có thể tính trước danh sách rồi chia bốn nhóm theo chẵn lẻ của $u[cur],v[cur]$. Mỗi trạng thái chỉ cần duyệt một nhóm phù hợp.

Không được chỉ gộp các tập theo hai tổng $(u,v)$: hai tập có cùng tổng nhưng khác mặt nạ sẽ cấm các lựa chọn khác nhau ở bit kế tiếp.

## Chứng minh đúng

Sau mỗi lớp, số nhớ ghi chính xác phần vượt các bit mục tiêu đã khớp. Điều kiện chẵn lẻ và hai công thức chuyển cần và đủ để khớp thêm một bit.

Mặt nạ $prev$ lưu đúng bit thấp kề hiện tại của từng biến. Điều kiện rời nhau loại chính xác các cặp bit $11$; mọi cặp bit kề trong mỗi số sẽ được xét đúng một lần. Số $0$ tương ứng toàn bit $0$ và luôn được phép.

Mỗi bộ số lượng có duy nhất một chuỗi mặt nạ bit. Một chuỗi kết thúc với hai số nhớ bằng $0$ thỏa hai phương trình, và các phép chuyển bảo đảm mọi số không có hai bit $1$ liên tiếp. Do đó thuật toán đếm đúng và không đếm trùng.

## Độ phức tạp

Với một cặp $(prev,cur)$ rời nhau, mỗi loại có ba khả năng: thuộc $prev$, thuộc $cur$, hoặc không thuộc cả hai. Vì vậy tổng số cặp mặt nạ cần xét là $3^m$, không phải $4^m$.

Thời gian $O(60S_aS_b3^m)$; bộ nhớ $O(S_aS_b2^m+3^m)$ khi lưu hai lớp và danh sách chuyển. Với $m\le8$, $S_a,S_b\le16$, chặn thô gần 101 triệu lượt xét trước khi bỏ các trạng thái không đạt tới và chia nhóm chẵn lẻ.

Dùng số nguyên 64 bit cho $A,B$ và phép dịch bit; số cách được lấy modulo sau mỗi phép cộng.
