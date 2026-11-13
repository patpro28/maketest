## Trạng thái và chuyển

Đặt $F[i][j][t]$ là số cách tạo $B[1\ldots j]$ bằng các vị trí trong $A[1\ldots i]$, trong đó đúng $t$ vị trí đã đánh dấu được chọn. Khởi tạo $F[0][0][0]=1$, các trạng thái khác bằng $0$.

Luôn có chuyển bỏ ký tự: $F[i][j][t]\mathrel{+}=F[i-1][j][t]$. Đặt $c=C_i\in\{0,1\}$. Nếu $j>0$, $A_i=B_j$ và $t\ge c$, thêm:

$$F[i][j][t]\mathrel{+}=F[i-1][j-1][t-c].$$

Chỉ cần lưu $0\le t\le K$ vì số vị trí đánh dấu đã chọn không thể giảm. Đáp án là $F[N][M][K]$ modulo $10^9+7$.

## Tính đúng đắn

Một cách chọn hoặc bỏ vị trí cuối, hoặc dùng nó cho chữ đích cuối. Ở trường hợp dùng, số vị trí đánh dấu tăng đúng $C_i$; xóa vị trí cuối khỏi bộ chỉ số cho một cách của trạng thái nguồn trong công thức. Hai trường hợp rời nhau và phép mở rộng là duy nhất, nên chuyển đếm đủ và không lặp. Trạng thái giữ số lượng chính xác, vì vậy lấy lớp $K$ đáp ứng yêu cầu đúng $K$.

## Độ phức tạp và cài đặt

Nén chiều $i$. Duyệt $j$ giảm dần; lúc đó mọi lớp $t$ ở cột $j-1$ vẫn thuộc hàng trước, kể cả khi $C_i=0$. Không khởi tạo mọi lớp đếm rỗng bằng $1$: chỉ lớp $t=0$ có cách chọn rỗng. Thời gian $O(NM(K+1))$, bộ nhớ $O(M(K+1))$, tối đa $37.5\cdot10^6$ trạng thái chính.
