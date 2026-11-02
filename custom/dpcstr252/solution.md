Đặt $F_t[i][j]$ là điểm lớn nhất của hai đoạn kết thúc tại $(i,j)$ có không quá $t$ lỗi, cho phép $0$ biểu diễn đoạn rỗng. Biên bằng $0$.

- Nếu $A_i=B_j=c$: $F_t[i][j]=\max(0,F_t[i-1][j-1]+W_c)$.
- Nếu $A_i\ne B_j$ và $t>0$: $F_t[i][j]=\max(0,F_{t-1}[i-1][j-1]-Q)$.
- Nếu hai chữ khác nhau và $t=0$: giá trị bằng $0$.

Với cặp khớp, cộng đúng điểm của chữ; với cặp khác nhau, trừ mức phạt và dùng thêm một lỗi. Mọi đoạn không rỗng đều được phân tích thành đoạn kết thúc tại cặp vị trí liền trước cộng một cặp cuối, nên các chuyển xét đủ các phương án. Một phần đầu có điểm âm có thể bỏ hoàn toàn để bắt đầu lại, đồng thời không tăng số lỗi; vì vậy giữ giá trị không âm là đủ. Mỗi giá trị dương tạo ra một phương án hợp lệ, nên lấy lớn nhất trên lớp $K$ và $0$ cho đáp án đúng.

Duyệt từng lớp lỗi từ $K$ xuống $0$ và từng chỉ số $j$ giảm dần để nén theo hàng mà vẫn đọc trạng thái cũ. Dùng số nguyên 64 bit cho điểm và mức phạt. Không bỏ các cặp bị phạt nằm giữa đoạn đang chọn.

Độ phức tạp thời gian $O(NM(K+1))$, bộ nhớ phụ của DP $O(M(K+1))$.
