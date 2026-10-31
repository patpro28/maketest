# Lời giải — DPSTR150

Lưu hai bảng: $L[i][j]$ là LCS thông thường của hai tiền tố; $F[i][j]$ là độ dài lớn nhất của dãy chung có chứa $C$. Biên của $L$ bằng $0$; biên của $F$ là âm vô cùng vì một tiền tố rỗng không thể chứa ký tự bắt buộc.

Với $F$, luôn có thể bỏ một ký tự cuối bằng cách lấy lớn nhất của $F[i-1][j]$ và $F[i][j-1]$. Khi $A_i=B_j$:

- Nếu ký tự đó là $C$, cập nhật bằng $L[i-1][j-1]+1$; điều kiện đã được bảo đảm bởi ký tự mới.
- Nếu ký tự đó khác $C$, chỉ nối vào một trạng thái $F[i-1][j-1]$ có thể đạt, rồi cộng $1$.

Mỗi chuyển tạo ra một dãy hợp lệ. Mọi dãy tối ưu hoặc bỏ ít nhất một ký tự cuối, hoặc ghép cả hai; trong trường hợp ghép, điều kiện bắt buộc được thỏa bởi ký tự mới hoặc bởi phần trước. Vì thế các trường hợp đầy đủ và DP đúng theo quy nạp.

Nếu $F[N][M]$ vẫn là âm vô cùng, in $-1$; ngược lại in giá trị đó. Không thay âm vô cùng bằng $0$, vì có thể nhận nhầm dãy không chứa $C$. Hai bảng đều có thể nén theo hàng.

Độ phức tạp thời gian $O(NM)$, bộ nhớ của phần DP $O(M)$.
