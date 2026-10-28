# Lời giải VEXE — Vé xe theo khu vực

## Đồ thị trực tiếp

Mỗi trạm là một đỉnh. Vé $(u,l,r,c)$ tương đương với các cạnh $u\to j$ trọng số $c$ cho mọi $j\in[l,r]$. Bài toán trở thành tìm đường đi ngắn nhất từ $S$ trên đồ thị có trọng số không âm.

Tuy nhiên, đồ thị trực tiếp có thể có $NQ$ cạnh. Cần nén nhóm cạnh có cùng điểm đầu và trọng số.

## Segment tree phát xuống

Dựng segment tree trên $[1,N]$. Lá $j$ dùng chính đỉnh của trạm $j$. Mỗi nút trong có một đỉnh phụ riêng, đại diện cho đoạn mà nút quản lý.

Với mỗi nút trong, thêm hai cạnh từ đỉnh của nó đến hai đỉnh con, trọng số $0$. Vì vậy, từ đỉnh đại diện một đoạn có thể đi miễn phí đến bất kỳ lá nào trong đoạn. Không thêm các cạnh theo chiều ngược lại: một trạm không được tự ý đi sang trạm khác.

Phân rã đoạn đích $[l,r]$ của mỗi vé thành $O(\log N)$ nút chuẩn. Với mỗi nút có đỉnh $v$, thêm cạnh $u\to v$ trọng số $c$.

Chạy Dijkstra từ lá $S$ trên đồ thị vừa dựng, rồi lấy khoảng cách tại $N$ lá. Dùng số nguyên có dấu $64$ bit cho khoảng cách và một giá trị vô cực đủ lớn. Vé có chi phí $0$ và chu trình chi phí $0$ đều được Dijkstra xử lý bình thường. Khi lấy trạng thái ra khỏi hàng đợi ưu tiên, bỏ qua trạng thái có khoảng cách đã lỗi thời.

## Chứng minh đúng

Với mỗi chuyến đi hợp lệ từ $u$ đến $j$ bằng một vé, có đúng một nút trong phép phân rã đoạn đích chứa $j$. Đi theo cạnh vé tới nút đó rồi theo các cạnh cây xuống lá $j$ tạo thành đường đi có đúng chi phí của vé. Mọi hành trình gốc đều chuyển được thành đường đi cùng chi phí trong đồ thị nén.

Ngược lại, các cạnh cây chỉ đi xuống. Từ một lá, muốn rời lá phải sử dụng cạnh của một loại vé có trạm xuất phát tại đó. Sau cạnh vé, các cạnh cây chỉ dẫn tới các trạm trong đoạn đích của vé. Do đó, chia một đường đi giữa các lá tại các lần sử dụng cạnh vé sẽ thu được một hành trình hợp lệ cùng chi phí.

Hai đồ thị có cùng chi phí đường đi ngắn nhất giữa các trạm. Vì trọng số không âm, Dijkstra tính đúng mọi đáp án cần tìm.

## Độ phức tạp

Cây có $2N-1$ đỉnh, $2N-2$ cạnh phụ trợ. Mỗi vé thêm $O(\log N)$ cạnh; với $N=1$ thì thêm một cạnh.

- Thời gian: $O((N+Q\log(N+1))\log(N+Q+1))$.
- Bộ nhớ: $O(N+Q\log(N+1))$, tính cả hàng đợi ưu tiên.

## Kiểm thử

Chạy `python3 custom/vexe/tests/check.py` từ gốc dự án. Bộ kiểm tra sinh 36 test, kiểm tra đầu vào, chạy lời giải qua checker, đối chiếu mọi test với một thuật toán không nén đồ thị bằng segment tree, và đối chiếu các trường hợp nhỏ với đồ thị dựng trực tiếp. Không xuất HTML. Chi tiết nằm trong `custom/graphcompression_tests/README.md`.
