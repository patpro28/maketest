Gọi $E[i][j]$ là độ dài đoạn chung dài nhất kết thúc đúng tại vị trí $i$ của $A$ và $j$ của $B$. Các biên bằng $0$.

Nếu $A_i=B_j$, đặt $E[i][j]=E[i-1][j-1]+1$; nếu khác nhau, đặt $E[i][j]=0$. Vì hai đoạn phải liên tiếp, khi nối ký tự cuối phải nối từ đúng cặp vị trí liền trước, không được lấy ô phía trên hoặc bên trái.

Nếu hai ký tự cuối khác nhau thì không có đoạn khớp không rỗng kết thúc tại đó. Nếu bằng nhau, bỏ ký tự cuối của mỗi đoạn sẽ còn một đoạn chung kết thúc tại cặp vị trí liền trước; ngược lại, nối ký tự vừa khớp tạo ra một đoạn chung hợp lệ. Quy nạp theo độ dài tiền tố chứng minh công thức đúng.

Lấy giá trị lớn nhất của tất cả các ô, không chỉ ô $(N,M)$, vì đoạn tối ưu có thể nằm giữa hai xâu. Chỉ cần một hàng: duyệt $j$ giảm dần để ô $j-1$ vẫn thuộc hàng trước. Đáp án khởi tạo bằng $0$.

Độ phức tạp thời gian $O(NM)$, bộ nhớ phụ của DP $O(M)$.
