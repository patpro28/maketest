## 1. Vì sao cần đổi trạng thái?

Với cách đặt $dp[i][j]$ là độ dài LCS của hai tiền tố, phải xử lý $NM$ ô. Khi $N=5000,M=10^6$, số ô có thể lên tới $5\cdot10^9$.

Trong khi vị trí trong $B$ có thể rất lớn, độ dài dãy con chung không vượt $N$. Ta đảo vai trò của vị trí $j$ và giá trị độ dài.

## 2. Đảo biến: dp[i][j] = len thành f[i][len] = j

Đặt $f[i][\ell]$ là **độ dài tiền tố ngắn nhất của $B$** chứa một dãy con chung dài đúng $\ell$ với tiền tố $A_1\ldots A_i$.

Tương đương, giá trị của trạng thái là vị trí kết thúc nhỏ nhất trong $B$, với vị trí đánh số từ $1$. Dãy rỗng có vị trí kết thúc $0$. Nếu không thể tạo độ dài đó, trạng thái bằng $INF=M+1$.

Với cùng độ dài $\ell$ và cùng tiền tố của $A$, kết thúc trong $B$ càng sớm càng tốt: phần ký tự còn lại của $B$ sẽ không ít hơn. Vì các vị trí tiếp theo trong $A$ đều nằm sau tiền tố đã xét, việc giữ một cách khớp kết thúc sớm nhất không làm mất phương án mở rộng.

## 3. Bảng vị trí xuất hiện tiếp theo

Đánh số ký tự của $B$ từ $0$. Xây dựng $next[p][c]$ là vị trí đánh số từ $1$ của lần xuất hiện đầu tiên của chữ $c$ trong phần $B_p\ldots B_{M-1}$. Nếu không có thì giá trị bằng $M+1$.

Nếu đã khớp xong ở vị trí đánh số từ $1$ là $p$, ký tự tiếp theo chỉ được lấy từ chỉ số $0$ không nhỏ hơn $p$. Vì vậy tra trực tiếp $next[p][c]$ sẽ tìm đúng vị trí **sau** lần khớp trước, không tái sử dụng ký tự đó.

Khởi tạo hàng $next[M]$ toàn giá trị $INF$. Duyệt $p$ từ $M-1$ về $0$, sao chép hàng $next[p+1]$ sang hàng hiện tại rồi đặt $next[p][B_p]=p+1$.

## 4. Chuyển trạng thái

Khởi tạo $f[0][0]=0$; các trạng thái độ dài dương trước khi xét ký tự nào đều bằng $INF$.

Khi xét $A_i$, có hai khả năng:

- Bỏ ký tự: giữ $f[i-1][\ell]$.
- Giữ ký tự: từ $p=f[i-1][\ell-1]$, nếu $p\le M$ thì nối $A_i$ tại vị trí $next[p][A_i]$.

Do đó:

$$f[i][\ell]=\min\left(f[i-1][\ell],\ next[f[i-1][\ell-1]][A_i]\right),$$

trong đó nhánh thứ hai bị bỏ qua nếu trạng thái trước là $INF$.

Chỉ có thể đạt $\ell\le\min(i,M)$. Sau khi xử lý hết $A$, lấy $\ell$ lớn nhất có $f[N][\ell]\le M$.

## 5. Nén bộ nhớ

Mỗi hàng chỉ phụ thuộc hàng trước nên dùng một mảng $f[\ell]$. Duyệt $\ell$ **giảm dần** để khi đọc $f[\ell-1]$, giá trị đó vẫn thuộc tiền tố trước của $A$.

Nếu duyệt tăng, một ký tự của $A$ có thể bị nối nhiều lần trong cùng một lượt. Chẳng hạn với $A=$ `ab`, $B=$ `bb`, đáp án chỉ là $1$, nhưng cách cập nhật tăng có thể lấy chữ `b` của $A$ hai lần.

## 6. Chứng minh tính đúng đắn

Chứng minh bằng quy nạp theo $i$. Ở $i=0$, chỉ có dãy rỗng, nên các trạng thái ban đầu đúng.

Giả sử hàng $i-1$ đã lưu đúng các vị trí kết thúc nhỏ nhất. Một dãy chung của hai tiền tố dài $\ell$ hoặc không dùng $A_i$, hoặc dùng nó làm ký tự cuối. Trường hợp đầu thuộc nhánh bỏ ký tự. Trong trường hợp sau, phần trước có độ dài $\ell-1$ và khớp với tiền tố $A_1\ldots A_{i-1}$. Vị trí kết thúc của phần trước không thể sớm hơn $f[i-1][\ell-1]$.

Lấy lần xuất hiện đầu tiên của $A_i$ sau vị trí nhỏ nhất này cho vị trí kết thúc không muộn hơn bất kỳ cách mở rộng nào khác. Đồng thời, phép nối tạo ra một dãy chung hợp lệ. Lấy minimum giữa hai nhánh vì thế thu được chính vị trí kết thúc nhỏ nhất cho trạng thái mới.

Theo quy nạp, toàn bộ trạng thái đúng. Một độ dài đạt được khi và chỉ khi trạng thái cuối không phải $INF$, nên lấy độ dài đạt được lớn nhất cho đúng LCS.

## 7. Độ phức tạp và lưu ý

- Tiền xử lý: $O(26M)$.
- DP: $O(N\min(N,M))$, không vượt $N(N+1)/2$ lượt chuyển khi chỉ duyệt các độ dài có thể đạt.
- Bộ nhớ: $O(26M+N)$ ngoài hai xâu đầu vào.

Tại cận lớn nhất, tổng quy mô tiền xử lý và chuyển trạng thái là $26\cdot10^6+5000\cdot5001/2=38502500$, nhỏ hơn $5\cdot10^7$.

Bảng $next$ dùng số nguyên 32 bit cần khoảng 100 MiB khi $M=10^6$; cùng với dữ liệu và DP vẫn nằm trong giới hạn 128 MiB. Mã nguồn lưu một hàng DP thay vì toàn bộ bảng $f$.

Luôn kiểm tra trạng thái không thể đạt trước khi tra bảng. Không truy cập hàng $next[M+1]$. Không giả sử $N\le M$ và không coi dãy con là đoạn liên tiếp.
