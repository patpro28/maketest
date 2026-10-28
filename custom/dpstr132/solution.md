# Lời giải — DPSTR132

Đặt $L[i][j]$ là độ dài dãy con chung dài nhất của hai tiền tố $A_1\ldots A_i$ và $B_1\ldots B_j$. Khi một tiền tố rỗng, giá trị bằng $0$.

Nếu $A_i=B_j$ thì $L[i][j]=L[i-1][j-1]+1$. Ngược lại, $L[i][j]=\max(L[i-1][j],L[i][j-1])$.

Khi hai ký tự cuối bằng nhau, có một phương án tối ưu ghép chúng: nếu một phương án tối ưu dùng một ký tự cuối nhưng ghép với vị trí sớm hơn, có thể chuyển lần ghép đó đến hai vị trí cuối mà không giảm độ dài; nếu không dùng cả hai ký tự cuối thì có thể nối thêm ký tự chung. Khi chúng khác nhau, không thể dùng đồng thời cả hai làm ký tự cuối của cùng một dãy chung, nên ít nhất một vị trí bị bỏ. Các công thức vì thế xét đủ các phương án và đều tạo ra dãy chung hợp lệ. Quy nạp theo tổng độ dài hai tiền tố chứng minh bảng DP đúng.

Xét hai vị trí $i,j$ có $A_i=B_j=C$, được dùng làm ký tự cuối. Phần đứng trước là một dãy chung bất kỳ của hai tiền tố dài $i-1,j-1$, nên độ dài tốt nhất cho cách kết thúc này là $L[i-1][j-1]+1$.

Lấy giá trị lớn nhất trên mọi cặp vị trí như vậy; nếu không có cặp, in $-1$. Mọi đáp án hợp lệ đều kết thúc tại một cặp được xét. Ngược lại, nối $C$ vào một LCS của hai tiền tố tạo ra một đáp án hợp lệ, nên phép lấy lớn nhất cho kết quả đúng.

Trong cách nén một hàng, đánh giá ứng viên bằng ô chéo cũ trước khi cập nhật bảng LCS.

Độ phức tạp thời gian $O(NM)$, bộ nhớ của phần DP $O(M)$.
