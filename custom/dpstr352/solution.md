## Trạng thái và công thức

Đặt $E_j[i]$ là số cách tạo $B[1\ldots j]$ và chọn vị trí cuối **đúng bằng** $i$ trong $A$. Với $j=1$, $E_1[i]=[A_i=B_1]$, vì chưa có điều kiện khoảng cách cần kiểm tra.

Với $j>1$, nếu $A_i\ne B_j$ thì $E_j[i]=0$. Nếu hai chữ bằng nhau:

$$E_j[i]=\sum_{p=\max(1,i-R)}^{i-L} E_{j-1}[p].$$

Khoảng rỗng cho tổng $0$. Đáp án là $\sum_{i=1}^N E_M[i]$ modulo $10^9+7$.

## Tăng tốc tổng đoạn

Duyệt $i$ tăng dần trên mỗi hàng $j$. Giữ tổng cửa sổ của hàng trước trên khoảng $[i-R,i-L]$: thêm phần tử ở $i-L$ nếu chỉ số hợp lệ và bỏ phần tử ở $i-R-1$ nếu chỉ số hợp lệ. Khi đó mỗi ô tính trong $O(1)$. Chỉ giữ hàng trước và hàng hiện tại.

## Tính đúng đắn

Mỗi bộ chỉ số tạo tiền tố đích dài $j$ có một vị trí cuối $i$ duy nhất. Vị trí liền trước $p$ bắt buộc thuộc $[i-R,i-L]$. Bỏ vị trí cuối cho đúng một bộ được đếm trong $E_{j-1}[p]$, và ngược lại thêm $i$ vào mọi bộ đó tạo ra một bộ hợp lệ. Các lựa chọn $p$ khác nhau rời nhau, chứng minh công thức. Cửa sổ chỉ thay cách tính cùng tổng, nên giữ nguyên kết quả.

## Độ phức tạp và cài đặt

Thời gian $O(NM)$, bộ nhớ $O(N)$, tối đa $25\cdot10^6$ cặp chỉ số. Chuẩn hóa số dư sau phép trừ. Khoảng cách là hiệu chỉ số, nên biên phải là $i-L$ và biên trái là $i-R$; không cộng thêm $1$ vào định nghĩa khoảng cách. Không áp điều kiện khoảng cách cho ký tự đầu tiên.
