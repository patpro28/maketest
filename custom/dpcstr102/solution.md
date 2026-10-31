# Lời giải — DPSTR102

Đặt $L[i][j]$ là độ dài dãy con chung dài nhất của hai tiền tố $A_1\ldots A_i$ và $B_1\ldots B_j$. Khi một tiền tố rỗng, giá trị bằng $0$.

Nếu $A_i=B_j$ thì $L[i][j]=L[i-1][j-1]+1$. Ngược lại, $L[i][j]=\max(L[i-1][j],L[i][j-1])$.

Khi hai ký tự cuối bằng nhau, có một phương án tối ưu ghép chúng: nếu một phương án tối ưu dùng một ký tự cuối nhưng ghép với vị trí sớm hơn, có thể chuyển lần ghép đó đến hai vị trí cuối mà không giảm độ dài; nếu không dùng cả hai ký tự cuối thì có thể nối thêm ký tự chung. Khi chúng khác nhau, không thể dùng đồng thời cả hai làm ký tự cuối của cùng một dãy chung, nên ít nhất một vị trí bị bỏ. Các công thức vì thế xét đủ các phương án và đều tạo ra dãy chung hợp lệ. Quy nạp theo tổng độ dài hai tiền tố chứng minh bảng DP đúng.

Nếu xâu chung còn lại dài $t$, phải xóa đúng $N-t$ ký tự của $A$ và $M-t$ ký tự của $B$, tổng cộng $N+M-2t$. Muốn ít lần xóa nhất cần tối đa hóa $t$, do đó đáp án là $N+M-2L[N][M]$. Mọi dãy con chung đều có thể thu được bằng cách xóa các vị trí còn lại, nên cận này đạt được.

Độ phức tạp thời gian $O(NM)$, bộ nhớ của phần DP $O(M)$.
