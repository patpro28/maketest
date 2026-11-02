Gọi $E[i][j]$ là độ dài đoạn chung dài nhất kết thúc đúng tại vị trí $i$ của $A$ và $j$ của $B$. Các biên bằng $0$.

Nếu $A_i=B_j$, đặt $E[i][j]=E[i-1][j-1]+1$; nếu khác nhau, đặt $E[i][j]=0$. Vì hai đoạn phải liên tiếp, khi nối ký tự cuối phải nối từ đúng cặp vị trí liền trước, không được lấy ô phía trên hoặc bên trái.

Nếu hai ký tự cuối khác nhau thì không có đoạn khớp không rỗng kết thúc tại đó. Nếu bằng nhau, bỏ ký tự cuối của mỗi đoạn sẽ còn một đoạn chung kết thúc tại cặp vị trí liền trước; ngược lại, nối ký tự vừa khớp tạo ra một đoạn chung hợp lệ. Quy nạp theo độ dài tiền tố chứng minh công thức đúng.

Một ô có giá trị $L>0$ cho phương án bắt đầu tại $i-L+1$ và $j-L+1$. So sánh các phương án theo thứ tự: độ dài lớn hơn, vị trí trong $A$ nhỏ hơn, rồi vị trí trong $B$ nhỏ hơn. Mọi đoạn chung tối ưu đều là đoạn được ghi nhận tại một ô kết thúc, nên phép so sánh này chọn đúng độ dài và quy tắc ưu tiên. Nếu mọi ô bằng $0$, trả về bộ $(0,0,0)$. Có thể nén bảng còn một hàng.

Độ phức tạp thời gian $O(NM)$, bộ nhớ phụ của DP $O(M)$.
