# Lời giải — DPSTR101

Đặt $L[i][j]$ là độ dài dãy con chung dài nhất của hai tiền tố $A_1\ldots A_i$ và $B_1\ldots B_j$. Khi một tiền tố rỗng, giá trị bằng $0$.

Nếu $A_i=B_j$ thì $L[i][j]=L[i-1][j-1]+1$. Ngược lại, $L[i][j]=\max(L[i-1][j],L[i][j-1])$.

Khi hai ký tự cuối bằng nhau, có một phương án tối ưu ghép chúng: nếu một phương án tối ưu dùng một ký tự cuối nhưng ghép với vị trí sớm hơn, có thể chuyển lần ghép đó đến hai vị trí cuối mà không giảm độ dài; nếu không dùng cả hai ký tự cuối thì có thể nối thêm ký tự chung. Khi chúng khác nhau, không thể dùng đồng thời cả hai làm ký tự cuối của cùng một dãy chung, nên ít nhất một vị trí bị bỏ. Các công thức vì thế xét đủ các phương án và đều tạo ra dãy chung hợp lệ. Quy nạp theo tổng độ dài hai tiền tố chứng minh bảng DP đúng.

Lưu toàn bộ bảng để truy vết từ $(N,M)$. Nếu hai ký tự cuối bằng nhau, thêm ký tự đó vào đáp án và giảm cả hai chỉ số. Nếu khác nhau, đi đến ô phía trên hoặc bên trái có giá trị bằng ô hiện tại. Khi hòa, chọn hướng nào cũng được. Dừng khi một chỉ số bằng $0$, rồi đảo ngược các ký tự đã thu được.

Mỗi bước lấy ký tự giảm độ dài tối ưu đi đúng $1$; bước bỏ ký tự giữ nguyên độ dài tối ưu. Các chỉ số lấy được tăng dần sau khi đảo ngược, nên xâu kết quả là dãy con của cả hai xâu và có đúng $L[N][M]$ ký tự. Khi giá trị này bằng $0$, chỉ in dòng chứa $0$.

Độ phức tạp thời gian $O(NM)$, bộ nhớ của phần DP $O(NM)$. Truy vết tốn thêm $O(N+M)$ thời gian và $O(\min(N,M))$ bộ nhớ cho xâu kết quả.
