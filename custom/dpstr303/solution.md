## Trạng thái và chuyển

Đặt $F[i][j]$ là số cách chọn trong $i$ ký tự đầu của $A$ để tạo $j$ ký tự đầu của $B$. Ta có $F[i][0]=1$ và $F[0][j]=0$ với $j>0$.

Luôn có phương án bỏ $A_i$, đóng góp $F[i-1][j]$. Nếu $A_i=B_j$ thì có thêm phương án chọn $A_i$, đóng góp $F[i-1][j-1]$:

$$F[i][j]=F[i-1][j]+[A_i=B_j]F[i-1][j-1].$$

Tính modulo $10^9+7$. Đáp án là $F[N][M]$, tự bằng $0$ khi $M>N$.

## Tính đúng đắn

Chia mọi cách chọn theo việc có dùng vị trí $i$ hay không. Nhóm không dùng tương ứng một-một với các cách của $F[i-1][j]$. Nhóm dùng chỉ tồn tại khi hai chữ cuối khớp và tương ứng một-một với $F[i-1][j-1]$ sau khi bỏ vị trí cuối. Hai nhóm rời nhau và phủ mọi cách chọn, nên công thức đúng theo quy nạp.

## Độ phức tạp và cài đặt

Nén còn mảng $f[j]$, khởi tạo $f[0]=1$. Với mỗi ký tự nguồn, duyệt $j$ **giảm dần** để không dùng lại cùng một vị trí. Thời gian $O(NM)$, bộ nhớ $O(M)$. Có tối đa $25\cdot10^6$ lượt xét cặp ký tự.
