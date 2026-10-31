# Lời giải — DPSTR103

Đặt $L[i][j]$ là độ dài dãy con chung dài nhất của hai tiền tố $A_1\ldots A_i$ và $B_1\ldots B_j$. Khi một tiền tố rỗng, giá trị bằng $0$.

Nếu $A_i=B_j$ thì $L[i][j]=L[i-1][j-1]+1$. Ngược lại, $L[i][j]=\max(L[i-1][j],L[i][j-1])$.

Khi hai ký tự cuối bằng nhau, có một phương án tối ưu ghép chúng: nếu một phương án tối ưu dùng một ký tự cuối nhưng ghép với vị trí sớm hơn, có thể chuyển lần ghép đó đến hai vị trí cuối mà không giảm độ dài; nếu không dùng cả hai ký tự cuối thì có thể nối thêm ký tự chung. Khi chúng khác nhau, không thể dùng đồng thời cả hai làm ký tự cuối của cùng một dãy chung, nên ít nhất một vị trí bị bỏ. Các công thức vì thế xét đủ các phương án và đều tạo ra dãy chung hợp lệ. Quy nạp theo tổng độ dài hai tiền tố chứng minh bảng DP đúng.

Đáp án là $N+M-L[N][M]$. Để xây dựng một xâu đạt độ dài này, lấy một LCS làm các ký tự dùng chung, rồi chèn các phần còn lại của hai xâu vào giữa các ký tự đã ghép theo đúng thứ tự.

Để chứng minh không thể ngắn hơn, xét hai cách nhúng $A,B$ vào một xâu $T$ bất kỳ. Gọi $q$ là số vị trí của $T$ được cả hai cách nhúng dùng chung. Các ký tự tại những vị trí đó tạo thành một dãy con chung nên $q\le L[N][M]$. Hợp hai tập vị trí có $N+M-q$ phần tử và nằm trong $T$, suy ra $|T|\ge N+M-q\ge N+M-L[N][M]$.

Độ phức tạp thời gian $O(NM)$, bộ nhớ của phần DP $O(M)$.
