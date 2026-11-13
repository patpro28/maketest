Gọi $E[i][j][h]$ là độ dài đoạn chung dài nhất kết thúc tại ba vị trí tương ứng. Nếu $A_i=B_j=D_h$, đặt $E[i][j][h]=E[i-1][j-1][h-1]+1$; nếu không, đặt bằng $0$. Các biên bằng $0$.

Mọi đoạn chung không rỗng kết thúc tại ba vị trí phải có ba chữ cuối bằng nhau. Bỏ chúng đi thì còn đoạn chung tại ba vị trí liền trước; ngược lại, nối cùng chữ đó vào đoạn trước tạo ra phương án hợp lệ. Quy nạp chứng minh công thức và lấy lớn nhất trên toàn bộ bảng cho đáp án.

Chỉ cần hai lớp theo chỉ số $i$, mỗi lớp có $(M+1)(P+1)$ ô. Không lưu toàn bộ khối ba chiều.

Độ phức tạp thời gian $O(NMP)$, bộ nhớ phụ của DP $O(MP)$.
