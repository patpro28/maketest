## Ý tưởng

Gọi $D_{i,j}$ là độ dài dãy con chung dài nhất của $i$ ký tự đầu của $A$ và $j$ ký tự đầu của $B$. Nếu một tiền tố rỗng thì giá trị bằng $0$.

Có thể bỏ ký tự cuối của một trong hai tiền tố, cho hai ứng viên $D_{i-1,j}$ và $D_{i,j-1}$. Nếu $A_i=B_j$, có thể ghép chúng sau một dãy con chung của hai tiền tố ngắn hơn, cho ứng viên $D_{i-1,j-1}+1$. Lấy giá trị lớn nhất trong các ứng viên hợp lệ.

## Chứng minh tính đúng đắn

Nếu một phương án dùng cả hai vị trí cuối thì chúng phải ghép với nhau, vì chúng lần lượt là vị trí cuối được chọn ở mỗi xâu. Khi đó phần trước thuộc trạng thái $(i-1,j-1)$. Các phương án còn lại bỏ ít nhất một vị trí cuối và được xét bởi hai phép chuyển bỏ ký tự. Mỗi ứng viên cũng tạo ra một dãy con chung hợp lệ, nên các phép chuyển cho đúng tối ưu.

## Độ phức tạp

Thời gian $O(NM)$, bộ nhớ phụ $O(M)$ khi lưu hai hàng liên tiếp của bảng.
