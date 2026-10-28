# Lời giải — DPSTR130

Đặt $dp[i][j]$ là điểm lớn nhất của một dãy con chung của hai tiền tố. Biên bằng $0$, tương ứng xâu rỗng. Luôn có hai phương án bỏ một ký tự cuối; khi hai ký tự bằng nhau, có thêm phương án ghép chúng:

$$dp[i][j]=\max\left(dp[i-1][j],dp[i][j-1],dp[i-1][j-1]+W_{A_i}\ \text{nếu }A_i=B_j\right).$$

Mỗi phương án trong công thức tạo ra một dãy chung hợp lệ. Ngược lại, một phương án tối ưu hoặc không dùng một trong hai ký tự cuối, hoặc ghép cả hai với nhau; các khả năng này đã được xét. Quy nạp theo hai tiền tố cho thấy DP đúng. Đáp án là $dp[N][M]$.

Không tối đa hóa độ dài trước rồi mới tính điểm: một dãy ngắn có thể có điểm cao hơn dãy dài. Điểm mỗi lần ghép chỉ cộng một lần. Có thể nén còn một hàng và lưu ô chéo cũ.

Độ phức tạp thời gian $O(NM)$, bộ nhớ của phần DP $O(M)$. Dùng số nguyên 64 bit vì điểm hoặc tổng chi phí có thể vượt giới hạn số nguyên 32 bit. Mã nguồn còn lưu mảng dữ liệu đầu vào.
