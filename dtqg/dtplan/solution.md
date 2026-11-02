Ta cần đếm các bộ số nguyên không âm $(x_1,\ldots,x_m)$ thỏa mãn

$$\sum_{i=1}^{m}a_ix_i=A,\qquad \sum_{i=1}^{m}b_ix_i=B.$$

Trong toàn bộ lời giải, các giá trị đếm phương án đều được lấy modulo $M=10^9$. Hai loại sản phẩm khác nhau vẫn phải được phân biệt, kể cả khi có cùng cặp hệ số $(a_i,b_i)$.

## Subtask 1 — DP theo lượng nguyên liệu

**Giới hạn:** $A,B\le1000$, chiếm 10% số điểm.

### Trạng thái và chuyển trạng thái

Gọi $F_i(p,q)$ là số cách dùng $i$ loại sản phẩm đầu tiên để tiêu thụ đúng $p$ đơn vị P và $q$ đơn vị Q.

Khởi tạo $F_0(0,0)=1$, các trạng thái khác bằng $0$. Khi xét loại $i$, chia phương án thành hai nhóm:

- Không sản xuất loại $i$: có $F_{i-1}(p,q)$ cách.
- Sản xuất ít nhất một sản phẩm loại $i$: bỏ đi một sản phẩm loại này, còn một phương án dùng $i$ loại và tiêu thụ $(p-a_i,q-b_i)$.

Vì vậy

$$F_i(p,q)=F_{i-1}(p,q)+F_i(p-a_i,q-b_i),$$

trong đó số hạng thứ hai chỉ tồn tại khi $p\ge a_i$ và $q\ge b_i$. Hai nhóm rời nhau và phép bỏ một sản phẩm là một song ánh, nên công thức đếm đúng mọi phương án.

### Bỏ chiều loại sản phẩm

Dùng một bảng $f[p][q]$, ban đầu chỉ có $f[0][0]=1$. Xét từng loại ở vòng ngoài, rồi duyệt lượng nguyên liệu **tăng dần**:

```text
for i = 1 .. m:
    for p = a[i] .. A:
        for q = b[i] .. B:
            f[p][q] = (f[p][q] + f[p-a[i]][q-b[i]]) mod M
```

Duyệt tăng cho phép dùng loại đang xét nhiều lần. Xét loại sản phẩm ở vòng ngoài bảo đảm đếm theo số lượng từng loại, không đếm các thứ tự sản xuất khác nhau. Đáp án là $f[A][B]$.

**Độ phức tạp:** thời gian $O(mAB)$, bộ nhớ $O(AB)$. Với $m\le20$ và $A,B\le1000$, cách này phù hợp.

### Vì sao cần đổi cách làm?

Ở các subtask sau, $A,B$ có thể tới $10^9$. Không thể cấp phát bảng theo toàn bộ hai lượng nguyên liệu. Ta chuyển sang xử lý từng chữ số của các số lượng $x_i$; khi đó chỉ cần nhớ số nhớ của hai phép cộng.

## Subtask 2 — Digit DP trong hệ 10

**Giới hạn:** $m\le3$, chiếm 20% số điểm.

### Viết các số lượng theo chữ số

Vì $a_i,b_i\ge1$, mọi nghiệm hợp lệ có

$$0\le x_i\le\min(A/a_i,B/b_i)\le10^9.$$

Do đó có thể biểu diễn mỗi $x_i$ bằng đúng 10 chữ số, thêm các số $0$ ở đầu:

$$x_i=\sum_{t=0}^{9}d_{i,t}10^t,\qquad d_{i,t}\in\{0,1,\ldots,9\}.$$

Xử lý từ hàng đơn vị lên hàng cao hơn. Ở một vị trí, chọn đồng thời chữ số của cả $m$ biến. Có $10^m\le1000$ bộ chữ số nên có thể liệt kê tất cả.

Đặt

$$S_a=\sum_i a_i,\qquad S_b=\sum_i b_i.$$

### Trạng thái số nhớ

Trước khi xử lý vị trí $t$, gọi $dp_t[c_a][c_b]$ là số cách chọn $t$ chữ số thấp của các $x_i$, sao cho hai tổng đã khớp $t$ chữ số thấp của $A,B$ và có số nhớ sang vị trí $t$ là $c_a,c_b$.

Cụ thể, nếu $x_i^{(t)}$ là phần gồm $t$ chữ số thấp đã chọn, ta giữ bất biến

$$\sum_i a_ix_i^{(t)}=(A\bmod10^t)+c_a10^t,$$

$$\sum_i b_ix_i^{(t)}=(B\bmod10^t)+c_b10^t.$$

Khởi tạo $dp_0[0][0]=1$, các trạng thái còn lại bằng $0$.

### Chuyển bằng một bộ chữ số

Gọi $\alpha_t,\beta_t$ là chữ số thứ $t$ của $A,B$. Với bộ chữ số $(d_1,\ldots,d_m)$ đang chọn, đặt

$$u=\sum_i a_id_i,\qquad v=\sum_i b_id_i.$$

Cần thỏa mãn hai phép cộng ở vị trí hiện tại:

$$c_a+u=\alpha_t+10c_a',\qquad c_b+v=\beta_t+10c_b'.$$

Chỉ nhận lựa chọn nếu

$$c_a+u\equiv\alpha_t\pmod{10},\qquad c_b+v\equiv\beta_t\pmod{10}.$$

Khi đó số nhớ mới được xác định duy nhất:

$$c_a'=\frac{c_a+u-\alpha_t}{10},\qquad c_b'=\frac{c_b+v-\beta_t}{10}.$$

Cập nhật

$$dp_{t+1}[c_a'][c_b']\mathrel{+}=dp_t[c_a][c_b].$$

Các tử số không âm vì số ở vế trái không âm và có chữ số cuối đúng bằng chữ số mục tiêu. Có thể tính trước cặp $(u,v)$ cho mỗi bộ chữ số để không phải tính lại trong từng trạng thái DP. Các bộ khác nhau cho cùng cặp tổng vẫn được giữ riêng ở subtask này.

### Vì sao số nhớ nhỏ?

Ban đầu $c_a=0$. Giả sử $0\le c_a<S_a$. Vì mỗi chữ số không quá $9$, ta có $u\le9S_a$, nên

$$c_a'\le\left\lfloor\frac{(S_a-1)+9S_a}{10}\right\rfloor=S_a-1.$$

Tương tự $0\le c_b'<S_b$. Do đó chỉ cần $S_aS_b$ trạng thái mỗi lớp. Với $m\le3$, $S_a,S_b\le15$, tức nhiều nhất 225 trạng thái.

Sau 10 chữ số, đáp án là $dp_{10}[0][0]$. Số nhớ cuối phải bằng $0$: nếu còn số nhớ, tổng nguyên liệu vượt mục tiêu một bội của $10^{10}$. Thêm các số $0$ ở đầu không làm một phương án bị đếm nhiều lần vì mỗi số có duy nhất một biểu diễn gồm đúng 10 chữ số.

### Tính đúng đắn và độ phức tạp

Bất biến mô tả chính xác các chữ số thấp đã khớp. Hai phương trình chuyển là điều kiện cần và đủ để khớp thêm một chữ số, nên quy nạp theo vị trí cho thấy DP đếm đúng. Mỗi phương án có một dãy bộ chữ số duy nhất và ngược lại, mỗi dãy kết thúc với số nhớ $(0,0)$ tạo một phương án hợp lệ.

Tiền xử lý các bộ chữ số mất $O(m10^m)$. DP mất $O(10S_aS_b10^m)$, bộ nhớ $O(S_aS_b+10^m)$ khi chỉ giữ hai lớp. Ở $m=3$, chặn số lần xét của phần DP là $10\cdot225\cdot1000=2250000$.

### Nút thắt khi m tăng

Trạng thái số nhớ vẫn nhỏ, nhưng số bộ chữ số tăng theo $10^m$. Với $m=10$, đã có $10^{10}$ bộ ở mỗi vị trí. Ta cần giảm số lựa chọn cho từng biến.

## Subtask 3 — Đổi digit DP sang hệ 2

**Giới hạn:** $m\le10$, chiếm 30% số điểm.

### Mỗi chữ số chỉ còn hai lựa chọn

Giữ nguyên ý tưởng số nhớ, nhưng viết

$$x_i=\sum_{t=0}^{29}\varepsilon_{i,t}2^t,\qquad\varepsilon_{i,t}\in\{0,1\}.$$

Đủ 30 bit vì $x_i\le10^9<2^{30}$. Tại mỗi bit, chọn một tập $S$ các loại có $\varepsilon_{i,t}=1$. Số lựa chọn giảm từ $10^m$ xuống $2^m\le1024$, đổi lại có 30 vị trí thay vì 10.

Tính trước cho mỗi mặt nạ tập con:

$$u_S=\sum_{i\in S}a_i,\qquad v_S=\sum_{i\in S}b_i.$$

### Công thức chuyển trong hệ 2

Gọi $\alpha_t,\beta_t$ là bit thứ $t$ của $A,B$. Từ trạng thái $(c_a,c_b)$, chỉ dùng tập $S$ nếu

$$c_a+u_S\equiv\alpha_t\pmod2,\qquad c_b+v_S\equiv\beta_t\pmod2.$$

Trạng thái tiếp theo là

$$c_a'=\frac{c_a+u_S-\alpha_t}{2},\qquad c_b'=\frac{c_b+v_S-\beta_t}{2}.$$

Với mỗi tập hợp lệ, cộng $dp_t[c_a][c_b]$ vào $dp_{t+1}[c_a'][c_b']$ modulo $M$.

Giới hạn số nhớ vẫn là $c_a<S_a$, $c_b<S_b$, vì

$$\left\lfloor\frac{(S_a-1)+S_a}{2}\right\rfloor=S_a-1.$$

Khởi tạo $(0,0)$ có một cách; sau 30 bit chỉ lấy trạng thái $(0,0)$. Chứng minh đúng giống hệ 10: thay $10^t$ bằng $2^t$ trong bất biến và dùng tính duy nhất của biểu diễn nhị phân.

### Độ phức tạp và giới hạn của cách liệt kê

Nếu tính tổng từng mặt nạ trực tiếp, tiền xử lý mất $O(m2^m)$. Phần DP mất $O(30S_aS_b2^m)$, bộ nhớ $O(S_aS_b+2^m)$.

Với $m\le10$, ta có $S_a,S_b\le50$. Chặn số lần xét là

$$30\cdot50\cdot50\cdot2^{10}=76800000.$$

Nhưng với $m=20$, mỗi trạng thái phải xét tới $2^{20}=1048576$ tập. Nhiều tập trong số này có cùng tổng $(u_S,v_S)$ và dẫn tới cùng một trạng thái mới. Đây là phần việc có thể gộp lại.

## Subtask 4 — Tính trước ways để gộp các lựa chọn

**Giới hạn:** toàn bộ đề bài, $m\le20$, chiếm 40% số điểm.

### Chỉ cặp tổng ảnh hưởng tới phép chuyển

Trong subtask 3, công thức chuyển không dùng trực tiếp tập $S$, mà chỉ dùng hai số $u_S,v_S$. Đặt

$$ways[u][v]=\#\left\{S\subseteq\{1,\ldots,m\}:\sum_{i\in S}a_i=u,\ \sum_{i\in S}b_i=v\right\}.$$

Ví dụ, với các cặp hệ số $(1,1),(2,2),(3,3)$, hai tập $\{3\}$ và $\{1,2\}$ cùng cho tổng $(3,3)$, nên $ways[3][3]=2$. Hai tập này vẫn tương ứng với hai lựa chọn bit khác nhau; không được chỉ đánh dấu cặp tổng đó là có thể đạt tới.

Vì $S_a,S_b\le100$, cặp tổng chỉ nằm trong một bảng kích thước không quá $101\times101$, nhỏ hơn nhiều số tập $2^{20}$.

### Tính ways bằng ba lô 0/1

Có thể liệt kê tập con để lập bảng, nhưng không cần thực hiện bước tăng theo $2^m$. Tính bảng bằng DP theo loại sản phẩm:

- Ban đầu $ways[0][0]=1$, tương ứng tập rỗng; các ô khác bằng $0$.
- Với mỗi loại $i$, hoặc bỏ nó khỏi tập bit, hoặc chọn nó đúng một lần.

Cập nhật tại chỗ như sau:

```text
ways[0][0] = 1
for i = 1 .. m:
    for u = S_a down to a[i]:
        for v = S_b down to b[i]:
            ways[u][v] += ways[u-a[i]][v-b[i]]
```

Ở đây phải duyệt **giảm dần**, khác subtask 1: ta đang chọn một bit của mỗi $x_i$, nên một loại được chọn nhiều nhất một lần trong tập bit. Bằng quy nạp theo số loại, bảng đếm đúng số tập có từng cặp tổng.

Mỗi ô không vượt tổng số tập $2^{20}=1048576$, nên có thể lưu số lượng chính xác bằng `int`. Không cần lấy modulo bảng `ways` ở giới hạn này.

### Chuyển DP bằng số cách đã gộp

Chỉ giữ các cặp $(u,v)$ có $ways[u][v]>0$. Từ trạng thái $(c_a,c_b)$, kiểm tra chẵn/lẻ như subtask 3. Nếu hợp lệ, đặt

$$c_a'=\frac{c_a+u-\alpha_t}{2},\qquad c_b'=\frac{c_b+v-\beta_t}{2}$$

và cập nhật

$$\boxed{dp_{t+1}[c_a'][c_b']\mathrel{+}=dp_t[c_a][c_b]\cdot ways[u][v]\pmod M}.$$

Đó chính là cộng gộp các phép chuyển giống nhau của subtask 3. Không xóa hay đồng nhất loại sản phẩm trùng hệ số: DP ba lô vẫn xét từng loại riêng và giữ đủ số lựa chọn trong `ways`.

### Chỉ duyệt nhóm chẵn/lẻ phù hợp

Chia các cặp tổng thành bốn nhóm theo $(u\bmod2,v\bmod2)$. Với một trạng thái và hai bit mục tiêu đã cố định, chỉ một nhóm có thể hợp lệ:

$$u\bmod2=\alpha_t\mathbin{\oplus}(c_a\bmod2),\qquad
v\bmod2=\beta_t\mathbin{\oplus}(c_b\bmod2),$$

trong đó $\oplus$ là XOR trên hai bit. Không cần duyệt ba nhóm còn lại. Đồng thời bỏ qua trạng thái có giá trị DP bằng $0$ và dùng hai lớp DP luân phiên.

Sau đủ 30 bit, in $dp_{30}[0][0]$. Không cộng các trạng thái số nhớ khác: chúng chỉ khớp 30 bit thấp và còn phần nguyên liệu dư ở các bit cao.

### Tính đúng đắn và độ phức tạp

Subtask 3 đã đếm đúng từng chuỗi lựa chọn tập bit. Bảng `ways` đếm đúng số tập thuộc mỗi cặp tổng. Mọi tập trong cùng nhóm có cùng điều kiện chẵn/lẻ và cùng số nhớ mới, nên thay các phép cộng riêng bằng một phép nhân với số lượng tập giữ nguyên giá trị DP. Phân nhóm chẵn/lẻ chỉ bỏ các phép chuyển không hợp lệ. Do đó thuật toán tối ưu vẫn đếm đúng mọi phương án, mỗi phương án một lần.

Gọi $H$ là số cặp tổng có `ways` khác $0$:

$$H\le\min\big(2^m,(S_a+1)(S_b+1)\big).$$

Tiền xử lý mất $O(mS_aS_b)$. Chặn thời gian của DP là $O(30S_aS_bH)$, bộ nhớ $O(S_aS_b+H)$. Các nhóm chẵn/lẻ và các trạng thái không đạt tới làm số phép chuyển thực hiện nhỏ hơn chặn tích các miền này.

Phải dùng `long long` trong tích $dp[c_a][c_b]\cdot ways[u][v]$ trước khi lấy modulo. Không dùng nghịch đảo modulo: $10^9$ không phải số nguyên tố, nhưng thuật toán chỉ cần cộng, nhân và các phép chia nguyên chính xác để tính số nhớ.

## Tóm tắt quá trình tối ưu

| Subtask | Đại lượng được lưu trong DP | Lựa chọn ở một bước | Điểm thay đổi chính |
| --- | --- | --- | --- |
| 1 | Hai lượng nguyên liệu đã dùng | Thêm sản phẩm theo từng loại | Dùng trực tiếp khi $A,B$ nhỏ |
| 2 | Hai số nhớ trong hệ 10 | $10^m$ bộ chữ số | Bỏ sự phụ thuộc tuyến tính vào $A,B$ |
| 3 | Hai số nhớ trong hệ 2 | $2^m$ tập bit | Giảm số lựa chọn của mỗi biến |
| 4 | Hai số nhớ trong hệ 2 | Các cặp tổng có số lượng `ways` | Gộp các lựa chọn có cùng tác động |

Lời giải mẫu đọc/ghi `PLAN.INP` và `PLAN.OUT` nếu có tệp đầu vào đó trong thư mục chạy; nếu không có, dùng nhập/xuất chuẩn để tương thích hệ thống chấm.
