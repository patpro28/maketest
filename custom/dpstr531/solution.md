Gọi $F[i][j]$ là chi phí nhỏ nhất khi đã xử lý $i$ vị trí nguồn và $j$ vị trí đích. Bước cuối là xóa $A_i$ với giá $D_i$, chèn $B_j$ với giá $I_j$, hoặc ghép cặp cuối với giá $R[A_i\ne B_j]$. Lấy nhỏ nhất của ba trạng thái trước cộng giá tương ứng. Nếu một phía rỗng, phải trả tổng chi phí của mọi vị trí đã xử lý bên còn lại.

Mọi phương án kết thúc bằng một trong ba bước được phép. Bỏ bước cuối luôn thu được một phương án cho đúng hai tiền tố ngắn hơn. Ngược lại, ghép bước đó vào phương án tiền tố hợp lệ tạo phương án mới với chi phí cộng đúng. Quy nạp theo $i+j$ chứng minh công thức.

Thời gian $O(NM)$ và bộ nhớ $O(N+M)$ kể cả hai mảng giá. Dùng 64 bit cho tổng chi phí. Không gộp chi phí của những vị trí có cùng chữ.
