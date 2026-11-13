Gọi $E[i][j]$ là độ dài đoạn chung dài nhất kết thúc đúng tại vị trí $i$ của $A$ và $j$ của $B$. Các biên bằng $0$.

Nếu $A_i=B_j$, đặt $E[i][j]=E[i-1][j-1]+1$; nếu khác nhau, đặt $E[i][j]=0$. Vì hai đoạn phải liên tiếp, khi nối ký tự cuối phải nối từ đúng cặp vị trí liền trước, không được lấy ô phía trên hoặc bên trái.

Nếu hai ký tự cuối khác nhau thì không có đoạn khớp không rỗng kết thúc tại đó. Nếu bằng nhau, bỏ ký tự cuối của mỗi đoạn sẽ còn một đoạn chung kết thúc tại cặp vị trí liền trước; ngược lại, nối ký tự vừa khớp tạo ra một đoạn chung hợp lệ. Quy nạp theo độ dài tiền tố chứng minh công thức đúng.

Lưu $last[i]$, vị trí gần nhất không vượt $i$ có chữ $C$ trong $A$, hoặc $0$ nếu chưa xuất hiện. Đoạn của ô $(i,j)$ bắt đầu tại $i-E[i][j]+1$ và chứa $C$ khi $E[i][j]>0$ và $last[i]\ge i-E[i][j]+1$.

Nếu đoạn chung dài nhất kết thúc tại một ô không chứa $C$, thì mọi đoạn chung ngắn hơn cùng kết thúc tại ô đó đều là hậu tố của nó và cũng không chứa $C$. Nếu nó có chứa $C$, chính nó là phương án tốt nhất tại ô này. Vì vậy chỉ cần kiểm tra một đoạn ở mỗi ô và lấy lớn nhất trên các ô hợp lệ. Không có ô hợp lệ thì trả về $-1$. Điều kiện phải kiểm tra vị trí $C$ nằm trong đoạn, không chỉ có mặt trong tiền tố.

Độ phức tạp thời gian $O(NM)$, bộ nhớ phụ của DP $O(M)$.
