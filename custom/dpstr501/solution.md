Nếu $M>N$ thì không thể tăng độ dài. Ngược lại, giữ đúng $M$ vị trí của $A$ theo thứ tự và thay chữ nếu cần sẽ luôn tạo được $B$. Các ký tự được thay rồi xóa hoặc bị thay nhiều lần có thể xử lý trực tiếp với chi phí không lớn hơn.

Đặt $F[i][j]$ là số thao tác nhỏ nhất cho hai tiền tố. Ta có $F[i][0]=i$, còn $F[0][j]$ vô cực khi $j>0$. Xét ký tự nguồn cuối: nếu xóa thì dùng $F[i-1][j]+1$. Nếu giữ thì nó phải tương ứng với ký tự đích cuối, dùng $F[i-1][j-1]+[A_i\ne B_j]$. Hai lựa chọn phủ hết các cách chọn vị trí và đều xây được phương án, nên lấy nhỏ nhất.

Thời gian $O(NM)$ và bộ nhớ $O(M)$ sau khi nén hàng.
