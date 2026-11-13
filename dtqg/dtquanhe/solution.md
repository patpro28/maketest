## Đồ thị ràng buộc

Đổi mỗi quan hệ thành một hoặc hai bất đẳng thức dạng $v_j\ge v_i+w$. Dùng cạnh có hướng $i\to j$ với trọng số $w=1$ nếu yêu cầu $v_i<v_j$, và $w=0$ nếu yêu cầu $v_i\le v_j$. Quan hệ theo chiều ngược thì đổi chỗ hai biến. Với quan hệ bằng nhau, thêm cạnh trọng số $0$ ở cả hai chiều.

Trong một thành phần liên thông mạnh, mỗi đỉnh đi được đến mọi đỉnh còn lại. Theo các cạnh, giá trị chỉ có thể tăng hoặc giữ nguyên, nên tất cả biến trong cùng thành phần phải có cùng giá trị. Vì dữ liệu có nghiệm, mọi cạnh bên trong một thành phần đều có trọng số $0$.

## Tìm giá trị nhỏ nhất

Tìm các thành phần liên thông mạnh bằng Kosaraju. Sau khi co mỗi thành phần thành một đỉnh, đồ thị còn lại là DAG. Duyệt các đỉnh theo thứ tự topo và khởi tạo $d[C]=0$ với mọi thành phần $C$. Với mỗi cạnh $C\to C'$ có trọng số $w$, cập nhật $d[C']\gets\max(d[C'],d[C]+w)$.

Khi duyệt xong, $d[C]$ là tổng trọng số lớn nhất trên một đường đi kết thúc tại $C$, kể cả đường đi rỗng có tổng $0$. Gán mọi biến thuộc $C$ giá trị $d[C]$.

## Tính đúng đắn

Mọi cạnh giữa hai thành phần thỏa $d[C']\ge d[C]+w$ theo bước cập nhật. Các cạnh bên trong một thành phần có trọng số $0$ và hai đầu được gán cùng giá trị. Do đó phép gán thỏa toàn bộ quan hệ.

Với một cách gán hợp lệ bất kỳ, giá trị tại điểm đầu của một đường đi ít nhất là $0$. Cộng các bất đẳng thức dọc đường đi cho thấy giá trị tại điểm cuối ít nhất bằng tổng trọng số đường đi. Lấy lớn nhất trên mọi đường đi tới $C$, giá trị của thành phần này phải ít nhất là $d[C]$. Phép gán trên đạt cận dưới đồng thời ở mọi thành phần, nên giá trị lớn nhất của nó cũng nhỏ nhất có thể.

## Độ phức tạp

Thời gian và bộ nhớ đều là $O(n+m)$. Dùng ngăn xếp tường minh cho các lượt DFS để xử lý đường đi dài tới $n$ đỉnh.
