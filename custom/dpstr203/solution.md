Đảo ngược toàn bộ $B$, thu được $R$. Mỗi đoạn liên tiếp trong $B$ sau khi đảo ngược trở thành một đoạn liên tiếp của $R$, và ngược lại. Do đó bài toán tương đương tìm đoạn con chung dài nhất của $A$ và $R$.

Gọi $E[i][j]$ là độ dài đoạn chung dài nhất kết thúc đúng tại vị trí $i$ của $A$ và $j$ của $B$. Các biên bằng $0$.

Nếu $A_i=B_j$, đặt $E[i][j]=E[i-1][j-1]+1$; nếu khác nhau, đặt $E[i][j]=0$. Vì hai đoạn phải liên tiếp, khi nối ký tự cuối phải nối từ đúng cặp vị trí liền trước, không được lấy ô phía trên hoặc bên trái.

Nếu hai ký tự cuối khác nhau thì không có đoạn khớp không rỗng kết thúc tại đó. Nếu bằng nhau, bỏ ký tự cuối của mỗi đoạn sẽ còn một đoạn chung kết thúc tại cặp vị trí liền trước; ngược lại, nối ký tự vừa khớp tạo ra một đoạn chung hợp lệ. Quy nạp theo độ dài tiền tố chứng minh công thức đúng.

Đáp án là giá trị lớn nhất trên bảng cho $A,R$. Phép đảo xâu bảo toàn độ dài và tạo tương ứng hai chiều giữa các phương án của hai bài toán, nên đáp án thu được là đúng.

Độ phức tạp thời gian $O(NM)$, bộ nhớ phụ của DP $O(M)$.
