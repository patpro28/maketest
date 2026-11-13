Mỗi ô $(i,j)$ giữ chi phí tốt nhất và số đường đi đạt giá đó. Xét ba cạnh đến ô như bài khoảng cách chỉnh sửa. Nếu cạnh cho chi phí thấp hơn, thay cả chi phí và số cách bằng kết quả từ cạnh đó. Nếu chi phí bằng nhau, cộng số cách. Khởi tạo ở $(0,0)$ bằng $(0,1)$. Trên mỗi trục chỉ có một kịch bản.

Các đường đi tới cùng một ô phân hoạch theo bước cuối. Nhánh không đạt chi phí nhỏ nhất không thể đóng góp cách tối ưu. Với mỗi nhánh đạt tối ưu, mọi đường đi tối ưu đến ô trước đều cho một đường đi mới khác nhau. Do vậy quy nạp theo hai độ dài đếm đúng các kịch bản, kể cả khi các ký tự lặp.

Thời gian $O(NM)$, bộ nhớ $O(M)$ khi nén hàng. Chi phí lưu riêng, vì số cách modulo có thể bằng $0$.
