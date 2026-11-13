Có thể quy một dãy thao tác tối ưu về cách ghép các vị trí còn lại theo thứ tự. Mỗi vị trí nguồn bị loại cần một lần xóa, mỗi vị trí đích mới cần một lần chèn, và mỗi cặp chữ nguồn–đích khác nhau cần một lần thay. Các bước trung gian tác động lên cùng ký tự không thể rẻ hơn một thao tác trực tiếp. Ngược lại, mọi cách ghép như vậy thực hiện được bằng các thao tác được phép.

Đặt $F[i][j]$ là chi phí biến tiền tố dài $i$ của $A$ thành tiền tố dài $j$ của $B$. Ba chuyển lần lượt bỏ ký tự nguồn cuối, thêm ký tự đích cuối, hoặc ghép cặp ký tự cuối. Chúng đọc $F[i-1][j]$, $F[i][j-1]$ và $F[i-1][j-1]$. Cộng chi phí của thao tác tương ứng rồi lấy nhỏ nhất. Hàng và cột rỗng tính bằng tổng chi phí chèn hoặc xóa.

Tính theo thứ tự tăng của hai độ dài. Chỉ cần hai hàng, hoặc một hàng và một biến giữ ô chéo cũ. Thời gian $O(NM)$ và bộ nhớ $O(M)$.
