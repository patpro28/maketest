Ta cần chọn các đoạn đối xứng liên tiếp, không giao nhau. Có thể bỏ ký tự thừa và có thể sắp lại thứ tự các độ dài yêu cầu. Các độ dài bằng nhau vẫn là nhiều yêu cầu riêng.

Nếu $\sum_i l_i>n=|S|$, trả lời `NO` ngay. Đây chỉ là điều kiện loại nhanh: tổng không vượt $n$ chưa bảo đảm các đoạn đối xứng có thể đặt không giao nhau.

## Subtask 1 — Chỉ cần một đoạn đối xứng

**Giới hạn:** $k=1$, $T\le200$, chiếm 25% số điểm.

Mỗi yêu cầu chỉ hỏi có đoạn đối xứng độ dài $L$ hay không. Tiền xử lý xâu một lần để dùng chung cho mọi yêu cầu.

### Bán kính đối xứng và Manacher

Đánh số ký tự từ $0$ tới $n-1$. Dùng hai mảng:

- $odd[i]$: bán kính lớn nhất sao cho $S[i-r+1\ldots i+r-1]$ đối xứng, với $r=odd[i]\ge1$.
- $even[i]$: bán kính lớn nhất sao cho $S[i-r\ldots i+r-1]$ đối xứng, với $r=even[i]\ge0$. Tâm nằm giữa $i-1$ và $i$.

Tính cả hai mảng bằng thuật toán Manacher trong $O(n)$. Ý tưởng là giữ đoạn đối xứng có biên phải xa nhất đã biết. Nếu tâm mới nằm trong đoạn đó, dùng tâm đối xứng của nó để sao chép phần bán kính chắc chắn đúng, chặn lại ở biên phải. Sau đó mới mở rộng bằng so sánh ký tự. Những lần mở rộng vượt biên làm biên phải tăng; tổng số lần tăng chỉ là $O(n)$.

Đặt

$$L_{odd}=\max_i(2odd[i]-1),\qquad L_{even}=\max_i2even[i].$$

Một đoạn đối xứng có thể bỏ đồng thời hai ký tự đầu/cuối mà vẫn đối xứng. Vì vậy:

- Nếu $L$ lẻ, có đoạn phù hợp khi và chỉ khi $L\le L_{odd}$.
- Nếu $L$ chẵn, có đoạn phù hợp khi và chỉ khi $L\le L_{even}$.

Đây là điều kiện cần và đủ: một chiều theo định nghĩa độ dài lớn nhất; chiều còn lại lấy đoạn lớn nhất cùng tính chẵn/lẻ rồi thu ngắn đối xứng tới đúng $L$.

**Độ phức tạp:** $O(n+T)$ thời gian, $O(n)$ bộ nhớ. Không cần duyệt lại xâu cho từng yêu cầu.

## Subtask 2 — DP vị trí và tập độ dài đã dùng

**Giới hạn:** $n\le200$, $k\le13$, $T\le3$, chiếm 25% số điểm.

### Tiền xử lý đoạn đối xứng

Vì xâu ngắn, có thể lập bảng $pal[l][r]$ cho biết $S[l\ldots r]$ có đối xứng hay không:

$$pal[l][r]=(S[l]=S[r])\ \land\ \big(r-l+1\le2\ \lor\ pal[l+1][r-1]\big).$$

Duyệt độ dài đoạn tăng dần để tính đúng phụ thuộc. Bảng mất $O(n^2)$ thời gian và bộ nhớ.

### Biểu diễn yêu cầu bằng mặt nạ

Đánh số các độ dài $l_0,\ldots,l_{k-1}$. Mặt nạ $mask$ có bit $i$ bằng $1$ khi đã chọn một đoạn đáp ứng yêu cầu $i$. Hai yêu cầu bằng độ dài vẫn có hai bit khác nhau, nên không bị mất số lần cần chọn.

Đặt $f[p][mask]$ là khả năng đã xét $p$ ký tự đầu và chọn được các đoạn ứng với $mask$, tất cả nằm hoàn toàn trong tiền tố đó. Ban đầu $f[0][0]=true$.

Từ trạng thái đúng $(p,mask)$, có hai loại chuyển:

1. **Bỏ ký tự:** nếu $p<n$, gán $f[p+1][mask]=true$.
2. **Chọn một đoạn:** với bit $i$ chưa dùng, nếu $p+l_i\le n$ và $pal[p][p+l_i-1]$ đúng, gán

$$f[p+l_i][mask\cup\{i\}]=true.$$

Duyệt $p$ tăng dần; mọi chuyển đều sang vị trí lớn hơn. Đáp án là $f[n][(1\ll k)-1]$. Nếu đã chọn đủ các đoạn trước cuối xâu, các phép bỏ ký tự còn lại đưa trạng thái tới $p=n$.

### Tính đúng đắn và độ phức tạp

Mỗi đường chuyển chỉ chọn các đoạn đối xứng và chuyển vị trí tới ngay sau đoạn vừa chọn, nên các đoạn không giao nhau. Các phép bỏ ký tự cho phép để khoảng trống tùy ý. Ngược lại, xét một cách chọn hợp lệ theo thứ tự từ trái sang phải: bỏ các ký tự không dùng và lần lượt chọn các đoạn sẽ tạo một đường chuyển của DP. Chọn bit chưa dùng bất kỳ cho phép mọi thứ tự độ dài.

Thời gian là $O(n^2+Tnk2^k)$, bộ nhớ $O(n^2+n2^k)$ nếu xử lý từng trường hợp độc lập. Giới hạn nhỏ của xâu và số trường hợp cho phép dùng cách này.

### Điểm cần tối ưu

Với một tập độ dài đã dùng, DP đang giữ nhiều vị trí kết thúc. Nhưng nếu cùng một tập đã có thể xếp xong ở vị trí sớm hơn, kết thúc muộn hơn không thể làm phần còn lại dễ hơn. Ta chỉ cần giữ vị trí sớm nhất, thay vì một hàng trạng thái cho mọi vị trí.

## Subtask 3 — Vị trí kết thúc sớm nhất của mỗi tập

**Giới hạn:** toàn bộ đề bài, chiếm 50% số điểm.

### Nén chiều vị trí

Gọi $dp[mask]$ là số ký tự của tiền tố ngắn nhất có thể chứa các đoạn đáp ứng đúng tập yêu cầu $mask$. Dùng đoạn nửa mở $[l,r)$ để $r$ cũng là vị trí bắt đầu sớm nhất cho đoạn tiếp theo.

Khởi tạo $dp[0]=0$, các giá trị khác bằng $INF=n+1$.

Việc chỉ giữ vị trí sớm nhất là đúng: nếu một phương án kết thúc tại $p$ và một phương án khác dùng cùng tập yêu cầu kết thúc tại $q\ge p$, mọi lựa chọn tương lai bắt đầu không sớm hơn $q$ cũng có thể nối sau phương án tại $p$, bằng cách bỏ các ký tự giữa $p$ và $q$. Vì vậy trạng thái tại $q$ bị trạng thái tại $p$ bao phủ.

### Tìm nhanh đoạn tiếp theo có độ dài cho trước

Với mỗi độ dài $L$ cần dùng, đặt $next_L[p]$ là vị trí kết thúc nhỏ nhất của một đoạn đối xứng độ dài $L$ có vị trí bắt đầu không nhỏ hơn $p$. Nếu không có, giá trị bằng $INF$.

Sau khi có mảng Manacher, đoạn bắt đầu tại $p$, dài $L$, được nhận biết trong $O(1)$:

- Nếu $L$ lẻ, tâm là $c=p+\lfloor L/2\rfloor$ và cần $odd[c]\ge\lfloor L/2\rfloor+1$.
- Nếu $L$ chẵn, tâm là $c=p+L/2$ và cần $even[c]\ge L/2$.

Chỉ xét khi $p+L\le n$. Tính bảng bằng một lượt từ phải sang trái:

```text
next_L[n] = INF
for p = n-1 down to 0:
    next_L[p] = next_L[p+1]
    if p+L <= n and S[p .. p+L-1] is a palindrome:
        next_L[p] = p+L
```

Nếu đoạn bắt đầu ngay tại $p$ phù hợp thì nó kết thúc sớm nhất trong mọi đoạn cùng độ dài bắt đầu từ $p$ trở đi. Nếu không, phải tìm từ $p+1$. Do đó công thức tính đúng $next$.

Các yêu cầu có chung độ dài dùng chung một bảng; các trường hợp thử cùng xâu cũng dùng chung các bảng này.

### Chuyển DP tập con

Với mỗi trạng thái hữu hạn $dp[mask]=p$, thử mọi bit $i$ chưa dùng. Ghép thêm đoạn có độ dài $l_i$ kết thúc sớm nhất:

$$\boxed{dp[mask\cup\{i\}]=\min\big(dp[mask\cup\{i\}],\ next_{l_i}[p]\big)}.$$

Duyệt các mặt nạ theo giá trị tăng dần; thêm một bit luôn tạo mặt nạ lớn hơn. Đáp án là `YES` khi và chỉ khi $dp[(1\ll k)-1]\le n$.

Không cần ép vị trí cuối bằng $n$: được phép bỏ phần đuôi. Không ép chọn độ dài theo thứ tự đầu vào, tăng dần hay giảm dần; phải thử các bit chưa dùng vì thứ tự tối ưu phụ thuộc vị trí các đoạn trong xâu.

### Chứng minh đúng

Quy nạp theo số bit của mặt nạ. Với tập rỗng, vị trí kết thúc sớm nhất là $0$. Giả sử đã biết vị trí sớm nhất cho các tập nhỏ hơn. Mọi cách chọn ứng với tập mới đều có một đoạn cuối, đáp ứng một chỉ số $i$. Các đoạn trước nó ứng với tập bỏ bit $i$.

Thay các đoạn trước bằng cách xếp kết thúc sớm nhất không làm mất khả năng đặt đoạn cuối. Từ vị trí đó, dùng đoạn độ dài $l_i$ kết thúc sớm nhất cũng không làm kết quả muộn hơn. Vì DP thử mọi chỉ số $i$ có thể là đoạn cuối, nó tìm đúng vị trí kết thúc nhỏ nhất. Mọi phép chuyển dùng đoạn đối xứng bắt đầu sau phần đã chọn, nên cũng không tạo cách chọn sai. Tập đầy đủ hữu hạn tương đương tồn tại lời giải.

### Độ phức tạp và bộ nhớ

Gọi $D$ là số độ dài phân biệt cần lập bảng sau khi bỏ các yêu cầu có tổng độ dài lớn hơn $n$. Lập Manacher mất $O(n)$, lập các bảng $next$ mất $O(nD)$. Mỗi trường hợp mất $O(k2^k)$ cho DP. Tổng thời gian:

$$O\left(n+nD+\sum_{q=1}^{T}k_q2^{k_q}\right),\qquad D\le\sum_q k_q\le2600.$$

Bộ nhớ là $O(nD+2^{13}+\sum_q k_q)$. Các vị trí và $INF$ không vượt $10001$, nên lưu các bảng $next$ bằng `uint16_t`: chặn $2600\cdot10001$ phần tử chiếm khoảng 52 MB. Không dùng bảng số nguyên 32 bit nếu muốn giữ bộ nhớ thấp.

Lời giải mẫu xử lý riêng các yêu cầu $k=1$ bằng hai độ dài đối xứng lớn nhất, nên không cần lập bảng $next$ chỉ để trả lời chúng.

## Lưu ý chung

- Một đoạn được chọn phải liên tiếp trong xâu; không phải dãy con được phép xóa ký tự bên trong.
- Hai đoạn có thể đứng sát nhau nhưng không được dùng chung ký tự. Với đoạn $[l,r)$, đoạn sau được phép bắt đầu tại $r$.
- Đề không nêu chặn trên riêng cho số nguyên dương $l_i$. Nếu $l_i>n$ thì đáp án chắc chắn `NO`. Lời giải mẫu đọc mỗi độ dài dưới dạng token và chặn giá trị tại $n+1$ để xử lý đúng cả số rất lớn, không gây tràn số.
- Lời giải mẫu đọc/ghi `PALINCUT.INP` và `PALINCUT.OUT` nếu tệp đầu vào có trong thư mục chạy; nếu không, dùng nhập/xuất chuẩn để tương thích hệ thống chấm.
