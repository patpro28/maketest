## Biểu diễn mỗi lính canh bằng trọng số

Đặt gốc tại thành phố $1$. Một lính canh tiếp viện được cho $u$ khi có ít nhất một thành phố do người đó phụ trách trong cây con của $u$. Vì các phân công cố định, ta có thể tính trước đáp án cho mọi đỉnh.

Đánh số các đỉnh theo thứ tự DFS khi vào đỉnh. Mỗi cây con chiếm một đoạn liên tiếp theo thứ tự này. Với một mã lính canh, gọi $v_1,\ldots,v_s$ là các đỉnh mang mã đó, theo thứ tự DFS. Cộng $1$ vào trọng số của mỗi $v_i$ và trừ $1$ tại $\operatorname{LCA}(v_i,v_{i+1})$ với $1\le i<s$.

## Chứng minh

Xét cây con của $u$. Nếu có $t>0$ đỉnh mang mã đang xét trong cây con, chúng tạo thành một đoạn liên tiếp trong dãy $v_1,\ldots,v_s$. Hai đỉnh có LCA nằm trong cây con khi và chỉ khi cả hai thuộc cây con. Vì thế cây con chứa $t$ đóng góp dương và $t-1$ đóng góp âm từ các cặp liên tiếp, cho tổng $1$. Khi $t=0$, cây con không chứa đóng góp nào của mã này.

Cộng trọng số của mọi mã, tổng trọng số trong cây con của $u$ bằng số mã khác nhau xuất hiện ở đó, cũng là số lính có thể tiếp viện cho $u$.

## Cài đặt và độ phức tạp

Dùng DFS với ngăn xếp để lấy thứ tự vào đỉnh, cha và độ sâu. Xây bảng nhảy tổ tiên để tính LCA trong $O(\log N)$. Khởi tạo trọng số của mỗi đỉnh bằng $1$. Duyệt các đỉnh theo thứ tự DFS và lưu đỉnh gặp gần nhất của từng mã để tìm ngay cặp liên tiếp cần xử lý.

Duyệt ngược thứ tự DFS, cộng tổng đã tính của mỗi đỉnh vào cha. Tất cả con cháu được xử lý trước cha, nên sau bước này mỗi đỉnh đã lưu tổng trọng số cây con. Trả lời mỗi yêu cầu trong $O(1)$.

Tổng thời gian là $O(N\log N+M)$ và bộ nhớ là $O(N\log N+K)$.
