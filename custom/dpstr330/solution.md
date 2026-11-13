## Trạng thái và chuyển

Đặt $F[i][j]$ là số cặp gồm cách thay mọi dấu hỏi trong tiền tố $A[1\ldots i]$ và cách chọn vị trí tạo tiền tố $B[1\ldots j]$. Ban đầu $F[0][0]=1$, các trạng thái khác bằng $0$.

Nếu $A_i$ là chữ cố định, công thức giống đếm dãy con thông thường:

$$F[i][j]=F[i-1][j]+[A_i=B_j]F[i-1][j-1].$$

Nếu $A_i$ là `?`:

$$F[i][j]=26F[i-1][j]+F[i-1][j-1]\quad(j>0),$$

và $F[i][0]=26F[i-1][0]$. Mọi phép tính lấy modulo $10^9+7$.

## Tính đúng đắn

Với một dấu hỏi không được chọn, cả $26$ chữ thay vào đều hợp lệ và tạo thành các cách khác nhau, nên nhân $26$. Với một dấu hỏi được chọn để tạo ký tự thứ $j$, nó bắt buộc trở thành $B_j$, chỉ có một lựa chọn. Hai trường hợp rời nhau. Với chữ cố định, chỉ có thể chọn khi khớp chữ đích. Quy nạp theo độ dài tiền tố nguồn chứng minh các trạng thái đếm đúng toàn bộ các cặp cần tìm.

## Độ phức tạp và cài đặt

Nén một hàng và duyệt $j$ giảm dần. Cập nhật $f[0]$ sau các trạng thái $j>0$ để chúng đọc đúng hàng cũ. Dùng 64 bit cho phép nhân với $26$ trước khi lấy dư. Thời gian $O(NM)$, bộ nhớ $O(M)$; tối đa $25\cdot10^6$ cặp chỉ số.
