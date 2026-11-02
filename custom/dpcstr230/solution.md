Đặt $F[i][j]$ là điểm lớn nhất của một đoạn chung kết thúc tại $(i,j)$, cho phép giá trị $0$ biểu diễn việc chưa bắt đầu hoặc kết thúc đoạn trước đó.

Nếu hai chữ khác nhau, đặt $F[i][j]=0$. Nếu $A_i=B_j=c$, đặt:

$$F[i][j]=\max(0,F[i-1][j-1]+W_c).$$

Trước một ký tự khớp, có thể nối đoạn đã có hoặc bắt đầu lại tại vị trí hiện tại. Phần trước có điểm âm không có lợi so với bỏ toàn bộ phần đó; giá trị $0$ đã bao gồm phương án bắt đầu mới. Khi hai ký tự khác nhau phải ngắt đoạn. Mọi đoạn tối ưu có điểm dương được tạo ra bởi một chuỗi chuyển như trên, còn mỗi giá trị dương đều tương ứng một đoạn chung hợp lệ. Lấy lớn nhất của $0$ và mọi giá trị trong bảng. Không tối đa hóa độ dài trước rồi mới tính điểm.

Độ phức tạp thời gian $O(NM)$, bộ nhớ phụ của DP $O(M)$.
