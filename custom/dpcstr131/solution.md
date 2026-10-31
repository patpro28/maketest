# Lời giải — DPSTR131

Đặt $dp[i][j]$ là chi phí nhỏ nhất để hai tiền tố dài $i,j$ trở nên bằng nhau. Biên $dp[i][0]=\sum_{t=1}^iU_t$ và $dp[0][j]=\sum_{t=1}^jV_t$.

Ở mỗi ô, có thể xóa ký tự cuối của một trong hai tiền tố:

$$dp[i][j]=\min(dp[i-1][j]+U_i,dp[i][j-1]+V_j).$$

Nếu $A_i=B_j$, có thêm lựa chọn giữ cả hai ký tự và ghép chúng, với chi phí $dp[i-1][j-1]$.

Trong mọi phương án hợp lệ, nếu không xóa một trong hai ký tự cuối thì hai ký tự đó phải bằng nhau và được ghép với nhau ở cuối xâu kết quả. Công thức xét đủ ba khả năng, còn mỗi chuyển đều hợp lệ. Quy nạp từ các biên chứng minh đáp án $dp[N][M]$ là nhỏ nhất.

Các vị trí có cùng chữ vẫn có thể có chi phí khác nhau, nên không thay mảng chi phí bằng một điểm cố định cho từng chữ. Nén DP còn một hàng và lưu ô chéo cũ.

Độ phức tạp thời gian $O(NM)$, bộ nhớ của phần DP $O(M)$. Dùng số nguyên 64 bit vì điểm hoặc tổng chi phí có thể vượt giới hạn số nguyên 32 bit. Mã nguồn còn lưu mảng dữ liệu đầu vào.
