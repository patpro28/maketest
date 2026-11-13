## Hợp các đường tiếp viện

Đặt gốc tại thành phố $1$. Mỗi thành phố $v$ do lính canh $k$ phụ trách cho phép $k$ tiếp viện mọi đỉnh trên đường từ $v$ lên gốc. Các đỉnh mà $k$ tiếp viện được là hợp của những đường này. Mỗi đỉnh cần lưu số lính canh có hợp đường đi chứa nó.

Xét việc thêm thành phố $v$ vào một nhóm lính canh. Đường $v$ lên gốc giao với đường $w$ lên gốc tại đoạn từ $\operatorname{LCA}(v,w)$ lên gốc. Gọi $z$ là LCA sâu nhất khi xét mọi $w$ đã có trong nhóm. Ta chỉ cần cộng $1$ trên đường từ $v$ lên đến ngay dưới $z$. Nếu nhóm rỗng, cộng trên cả đường đến gốc. Khi bỏ $v$, tìm $z$ trong số các đỉnh còn lại và trừ $1$ trên cùng đoạn đường.

## Tìm điểm dừng

Đánh số DFS sao cho mỗi cây con chiếm một đoạn liên tiếp. Trong một nhóm lính canh, lưu các số thứ tự DFS trong một tập có thứ tự. Xét đỉnh $w$ đứng trước $v$ trong nhóm. Nếu $p$ là đỉnh ngay trước $v$, thứ tự DFS của $p$ nằm giữa $w$ và $v$. Cây con của $\operatorname{LCA}(v,w)$ chứa cả $w$ và $v$, nên cũng chứa $p$. Do đó $\operatorname{LCA}(v,p)$ sâu ít nhất bằng $\operatorname{LCA}(v,w)$. Lập luận tương tự cho phía sau. Chỉ cần so sánh LCA của $v$ với hai đỉnh kề theo thứ tự DFS, nếu có.

## Cập nhật đường đi và trả lời

Dùng phân rã nặng nhẹ (HLD), đánh số DFS với con nặng được thăm trước. Mỗi chuỗi nặng chiếm một đoạn liên tiếp. Một đường đi lên tổ tiên cắt qua $O(\log N)$ chuỗi nặng, nên có thể tách mỗi đoạn cần cập nhật thành $O(\log N)$ đoạn chỉ số.

Dùng cây Fenwick lưu mảng hiệu. Để cộng $d$ trên đoạn $[l,r]$, cộng $d$ tại $l$ và trừ $d$ tại $r+1$ nếu còn trong mảng. Tổng tiền tố tại số thứ tự của $u$ trả về số lính canh có thể tiếp viện cho $u$.

Khởi tạo bằng cách thêm lần lượt các đỉnh theo thứ tự DFS. Khi đổi phân công, bỏ đỉnh khỏi nhóm cũ rồi thêm vào nhóm mới. Có thể bỏ qua sự kiện gán lại đúng mã hiện tại.

## Chứng minh và độ phức tạp

Mỗi bước thêm hoặc bỏ một đỉnh thay đổi đúng phần chênh lệch giữa hai hợp đường đi của lính canh đó. Mảng hiệu vì thế luôn biểu diễn tổng đóng góp của tất cả lính canh và truy vấn điểm cho đáp án đúng.

Tìm hai đỉnh kề và tính LCA bằng HLD mất $O(\log N)$ mỗi lần thêm hoặc bỏ. Mỗi lần cập nhật đường đi mất $O(\log^2 N)$, còn mỗi truy vấn đếm mất $O(\log N)$. Tổng thời gian trong trường hợp xấu nhất là $O((N+M)\log^2 N)$ và bộ nhớ là $O(N+K)$.
