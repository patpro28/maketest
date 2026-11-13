Gọi $E[i][j]$ là độ dài đoạn chung dài nhất kết thúc đúng tại vị trí $i$ của $A$ và $j$ của $B$. Các biên bằng $0$.

Nếu $A_i=B_j$, đặt $E[i][j]=E[i-1][j-1]+1$; nếu khác nhau, đặt $E[i][j]=0$. Vì hai đoạn phải liên tiếp, khi nối ký tự cuối phải nối từ đúng cặp vị trí liền trước, không được lấy ô phía trên hoặc bên trái.

Nếu hai ký tự cuối khác nhau thì không có đoạn khớp không rỗng kết thúc tại đó. Nếu bằng nhau, bỏ ký tự cuối của mỗi đoạn sẽ còn một đoạn chung kết thúc tại cặp vị trí liền trước; ngược lại, nối ký tự vừa khớp tạo ra một đoạn chung hợp lệ. Quy nạp theo độ dài tiền tố chứng minh công thức đúng.

Nếu $E[i][j]=x$, với mỗi độ dài $1,2,\ldots,x$ có đúng một bộ ba kết thúc tại $(i,j)$; các vị trí bắt đầu là $i-L+1,j-L+1$. Không có độ dài nào lớn hơn $x$ hợp lệ tại ô này. Vì mỗi bộ ba có duy nhất một cặp vị trí kết thúc, tổng $\sum_{i,j}E[i][j]$ đếm mỗi bộ đúng một lần.

Dùng số nguyên 64 bit cho tổng. Với hai xâu gồm $5000$ chữ giống nhau, kết quả là $\sum_{t=1}^{5000}t^2=41679167500$, vượt số nguyên 32 bit.

Độ phức tạp thời gian $O(NM)$, bộ nhớ phụ của DP $O(M)$.
