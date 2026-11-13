Đặt $F[i]$ là chi phí nhỏ nhất để xử lý $i$ vị trí đầu. Mảnh cuối dài $1$ luôn được phép và có chi phí $[A_i\ne B_i]$. Mảnh cuối dài $2$ được phép khi $A_{i-1}=B_i$ và $A_i=B_{i-1}$, khi đó chi phí là $1$. Ghép mảnh cuối với trạng thái $F[i-1]$ hoặc $F[i-2]$ tương ứng.

Mỗi phương án có đúng một mảnh cuối. Sau khi bỏ mảnh đó, các vị trí còn lại vẫn tạo một phương án cho tiền tố ngắn hơn. Ngược lại, ghép hai phần không làm một vị trí tham gia hai thao tác. Vì vậy các chuyển xét đủ và chỉ xét phương án hợp lệ.

Thời gian $O(N)$ và bộ nhớ $O(N)$, có thể nén còn hai trạng thái.
