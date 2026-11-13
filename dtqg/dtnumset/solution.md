## Dùng biểu diễn chuẩn của mỗi giá trị

Một số dương thuộc tập cần đếm khi và chỉ khi biểu diễn thập phân chuẩn của nó là dãy con của $n$. Nếu một cách chọn có các chữ số $0$ ở đầu, bỏ chúng đi vẫn tạo được chính biểu diễn chuẩn. Chiều ngược lại là trực tiếp.

Số $0$ thuộc tập khi và chỉ khi $n$ có ít nhất một chữ số `0`. Vì vậy chỉ đếm các dãy con không bắt đầu bằng `0`, và xét riêng giá trị $0$. Cách chọn vị trí khác nhau cho cùng nội dung chỉ được tính một lần.

Có hai miền dữ liệu, dùng hai thuật toán tương ứng.

## Miền xâu dài, đoạn giá trị hẹp

Lập $next[p][d]$ là vị trí đầu tiên chứa chữ số $d$ từ vị trí $p$ trở đi, hoặc $n$ nếu không có. Tính từ phải sang trái trong $O(10n)$.

Để kiểm tra một số $X$ có phải dãy con, lần lượt lấy vị trí xuất hiện sớm nhất cho mỗi chữ số bằng bảng $next$. Tham lam này đúng vì lấy sớm nhất không làm giảm phần xâu còn lại.

Không kiểm tra độc lập toàn bộ chữ số của từng số trong $[A,B]$. Hai số nguyên liên tiếp thường chỉ khác vài chữ số ở cuối. Giữ một mảng vị trí khớp cho mọi tiền tố của số hiện tại. Khi tăng số thêm $1$:

- Tìm từ phải sang trái các chữ số `9`, đổi chúng thành `0`, rồi tăng chữ số đứng trước.
- Giữ nguyên kết quả khớp của tiền tố không đổi và chỉ tính lại từ chữ số đầu tiên thay đổi.
- Khi tràn toàn bộ, thêm chữ số `1` ở đầu và tính lại biểu diễn mới.

Vị trí không khớp được lưu bằng dấu thất bại và lan truyền tới hết hậu tố. Khi một tiền tố thay đổi, phải phục hồi từ tiền tố vẫn giữ nguyên; không kết luận mọi số về sau cũng thất bại.

Tính $B-A$ bằng phép trừ trên xâu, chặn tại $10^6+1$, rồi lặp đúng số lần cần thiết. Như vậy không so sánh hai xâu dài trong mỗi lượt tăng.

Trong $W=B-A+1$ lần kiểm tra liên tiếp, số chữ số hậu tố phải cập nhật là $O(L+W)$: hàng đơn vị thay đổi mỗi lượt, hàng chục mỗi mười lượt, hàng trăm mỗi một trăm lượt, cộng thêm các lần truyền nhớ ban đầu dài tối đa $L$. Tổng thời gian $O(10n+L+W)$, bộ nhớ $O(10n+L)$, với $L$ là độ dài lớn nhất của hai cận. Kết quả trong miền này không vượt $1000001$.

## Miền tổng quát có tối đa 1000 chữ số

### Đếm dãy con phân biệt theo độ dài

Đánh số vị trí từ $0$. Đặt $f[p][r]$ là số xâu khác nhau dài đúng $r$ có thể lấy từ hậu tố $n[p\ldots]$, tạm cho phép chữ số `0` ở đầu.

Khởi tạo $f[p][0]=1$ và $f[n][r>0]=0$. Gọi $j$ là lần xuất hiện tiếp theo của chữ số $n[p]$ sau $p$. Ta có

$$f[p][r]=f[p+1][r]+f[p+1][r-1]-f[j+1][r-1],$$

trong đó bỏ số hạng trừ nếu không có $j$.

Hai số hạng đầu tương ứng bỏ vị trí $p$ hoặc lấy nó làm ký tự đầu. Phần trùng là những xâu bắt đầu cùng chữ số và đã lấy được khi bỏ $p$; chúng có biểu diễn lấy chữ số đầu tại $j$, nên được đếm đúng bởi $f[j+1][r-1]$.

Duyệt $p$ giảm dần. Chỉ cần giữ $r\le\min(n-p,|B|)$; các ô ngoài miền bằng $0$. Số cách có thể rất lớn nên dùng số nguyên lớn chính xác, không lấy modulo.

### Đếm không vượt một cận

Gọi $C(X)$ là số giá trị thuộc tập không vượt $X$.

Trước hết cộng $1$ nếu số $0$ thuộc tập. Với mỗi độ dài $r<|X|$, thử chữ số đầu $d=1,\ldots,9$. Gọi $j=next[0][d]$; nếu tồn tại thì cộng $f[j+1][r-1]$. Đây là mọi số dương ngắn hơn $X$.

Với các số cùng độ dài, đi theo tiền tố của $X$. Tại vị trí $i$, đã khớp tiền tố trước đó kết thúc trước vị trí $p$ của xâu nguồn:

1. Thử chữ số $d$ nhỏ hơn chữ số thứ $i$ của $X$, từ $1$ nếu $i=0$, từ $0$ nếu $i>0$.
2. Lấy $j=next[p][d]$. Nếu có, cộng $f[j+1][|X|-i-1]$; hậu tố này được chọn tùy ý vì giá trị đã nhỏ hơn cận.
3. Tiếp tục nhánh bằng chữ số của $X$ theo lần xuất hiện sớm nhất. Nếu không tìm thấy thì kết thúc; nếu khớp hết thì cộng thêm $1$ cho chính $X$.

Mỗi xâu có biểu diễn lấy các ký tự tiền tố sớm nhất duy nhất. Các nhánh được chia theo vị trí đầu tiên nhỏ hơn $X$, nên không giao nhau và không đếm trùng.

Kết quả là $C(B)-C(A-1)$. Nếu $A=0$, coi $C(-1)=0$ và không thực hiện phép giảm $0$ trên xâu.

## Chứng minh đúng

Chuẩn hóa đã đưa bài toán số về các dãy chữ số không có `0` vô nghĩa ở đầu, với $0$ xét riêng. Truy hồi hậu tố loại đúng phần trùng giữa lấy và bỏ chữ số đầu, nên quy nạp theo độ dài hậu tố cho thấy bảng $f$ đếm đúng các nội dung khác nhau.

Trong phép đếm theo cận, các độ dài ngắn hơn đều nhỏ hơn cận. Các số cùng độ dài được phân hoạch bởi chữ số đầu tiên khác cận, hoặc bằng hoàn toàn. Bảng $next$ dùng cách khớp sớm nhất nên bao phủ mọi hậu tố có thể nối, và bảng $f$ đếm mỗi hậu tố khác nhau một lần. Vì vậy $C(X)$ đúng, hiệu hai cận cho đúng đoạn đóng.

Ở miền hẹp, từng biểu diễn chuẩn được kiểm tra bằng tham lam dãy con đúng; việc tái sử dụng chỉ giữ những tiền tố không đổi, nên không thay đổi kết quả so với kiểm tra độc lập.

## Độ phức tạp và số nguyên lớn

Miền tổng quát có $O(n\min(n,|B|))$ ô DP, mỗi ô gồm một phép cộng và có thể một phép trừ số nguyên lớn; phần đếm hai cận thêm $O(10(n+|A|+|B|))$ phép cộng/tra cứu. Bộ nhớ cùng bậc số ô, chỉ cấp phát các độ dài không vượt độ dài hậu tố.

Đây là số phép toán trên số nguyên lớn, không phải chặn số phép toán máy. Một kết quả có không quá $n\log_{10}2+1$ chữ số vì tập chứa không quá $2^n-1$ nội dung lấy được. Có thể tự lưu số lớn bằng các khối cơ số $10^9$, hỗ trợ cộng, trừ không âm và in thập phân. Miền tổng quát $n\le1000$ bảo đảm các khối ngắn; miền xâu rất dài dùng thuật toán đoạn hẹp để tránh bảng bậc hai.
