## Đếm qua tổng trọng số cây con

Đặt gốc tại thành phố $1$. Thành phố $u$ nhận được tiếp viện từ đúng các mã lính canh xuất hiện trong cây con của $u$. Đánh số các đỉnh theo thứ tự DFS khi vào đỉnh. Cây con của $u$ chiếm đoạn $[\operatorname{tin}(u),\operatorname{tout}(u)]$.

Gán trọng số $+1$ cho mỗi đỉnh. Với từng mã lính canh, sắp xếp các đỉnh mang mã đó theo thứ tự DFS. Mỗi cặp liên tiếp $a,b$ đóng góp $-1$ tại $\operatorname{LCA}(a,b)$. Trong một cây con chứa $t>0$ đỉnh mang cùng mã, $t$ đỉnh này xuất hiện liên tiếp trong danh sách của mã. Đúng $t-1$ cặp liên tiếp có LCA thuộc cây con, vì một LCA nằm trong cây con khi và chỉ khi cả hai đầu mút nằm trong đó. Tổng đóng góp là $t-(t-1)=1$. Mã vắng mặt có đóng góp $0$. Do đó tổng trọng số trên đoạn cây con là đáp án.

## Đổi lính canh bằng hai cập nhật điểm

Duy trì một tập có thứ tự DFS cho từng mã. Khi chèn $x$ vào một tập, gọi $p,s$ là đỉnh liền trước và liền sau vị trí chèn. Nếu cả hai tồn tại, cặp $(p,s)$ mất đi, còn $(p,x)$ và $(x,s)$ xuất hiện.

Do $x$ nằm giữa $p$ và $s$ theo thứ tự DFS, nó nằm trong cây con của $w=\operatorname{LCA}(p,s)$. Cả $\operatorname{LCA}(p,x)$ và $\operatorname{LCA}(x,s)$ đều nằm trên đường từ $w$ đến $x$. Ít nhất một trong hai bằng $w$. Nếu cả hai đều nằm dưới $w$, chúng phải thuộc cùng nhánh con của $w$ chứa $x$, kéo theo cả $p$ và $s$ thuộc nhánh đó. Điều này mâu thuẫn với $w=\operatorname{LCA}(p,s)$.

Vì vậy, khôi phục $+1$ tại LCA của cặp cũ triệt tiêu một trong hai khoản $-1$ của các cặp mới. Khi chèn $x$, chỉ cần trừ $1$ tại LCA sâu hơn trong hai LCA mới. Nếu chỉ có một đỉnh kề thì trừ tại LCA duy nhất, còn nếu tập rỗng thì không đổi trọng số. Khi xóa $x$, thực hiện phép ngược lại với hai đỉnh kề còn lại. Hai LCA đều là tổ tiên của $x$, nên LCA sâu hơn có số thứ tự DFS lớn hơn. Khoản $+1$ tại bản thân $x$ được giữ nguyên vì mỗi thành phố luôn có đúng một lính canh.

Dùng cây Fenwick để cập nhật các trọng số và lấy tổng đoạn cây con. Mỗi lần đổi mã cần nhiều nhất hai cập nhật điểm.

## Cài đặt LCA và độ phức tạp

Duyệt cây bằng ngăn xếp, ghi lại mỗi đỉnh lúc vào và ghi lại cha sau khi quay về từ mỗi con. Dãy Euler có $2N-1$ phần tử. Trên đoạn giữa hai lần xuất hiện đầu tiên của $a$ và $b$, đỉnh nông nhất là $\operatorname{LCA}(a,b)$. Toàn bộ đoạn nằm trong cây con của LCA và có đi qua LCA, nên có thể dùng số thứ tự DFS nhỏ nhất trên đoạn để lấy chính LCA. Với bảng thưa, mỗi lần tìm giá trị nhỏ nhất mất $O(1)$.

Khởi tạo các tập theo thứ tự DFS để biết ngay cặp liền trước của mỗi đỉnh. Bảng thưa tốn $O(N\log N)$ thời gian và bộ nhớ. Mỗi lần đổi mã hoặc truy vấn đếm tốn $O(\log N)$ thời gian. Tổng thời gian là $O((N+M)\log N)$ và bộ nhớ là $O(N\log N+K)$.
