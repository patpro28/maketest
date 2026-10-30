# Lời giải DTBASAC — Bộ ba khác màu

## Từ tần suất màu tới số bộ ba

Xét một tập đỉnh. Gọi $cnt_c$ là số đỉnh màu $c$ và đặt

$$T=\sum_c cnt_c,\qquad S_2=\sum_c cnt_c^2,\qquad S_3=\sum_c cnt_c^3.$$

Số bộ ba không thứ tự có ba màu khác nhau là

$$\boxed{B=\frac{T^3-3TS_2+2S_3}{6}}.$$

Để chứng minh, xét các bộ ba có thứ tự, cho phép lặp đỉnh. Có $T^3$ bộ. Gọi ba sự kiện xấu là màu tại cặp vị trí $(1,2)$, $(1,3)$ hoặc $(2,3)$ bằng nhau. Mỗi sự kiện có $TS_2$ bộ. Giao của hai hoặc ba sự kiện đều là ba màu bằng nhau, có $S_3$ bộ. Bao hàm–loại trừ cho $T^3-3TS_2+2S_3$ bộ có ba màu khác nhau. Chúng tự động gồm ba đỉnh khác nhau; chia $6$ để bỏ thứ tự.

Khi thêm hoặc xóa một đỉnh màu $c$, chỉ một tần suất đổi từ $x$ thành $y=x\pm1$. Cập nhật

$$T\gets T\pm1,\quad S_2\gets S_2+y^2-x^2,\quad S_3\gets S_3+y^3-x^3.$$

Mỗi thao tác mất $O(1)$. Nén các màu trước để dùng mảng tần suất.

## Dùng Sack cho mọi cây con

Tính kích thước cây con và chọn con nặng của mỗi đỉnh là con có cây con lớn nhất. Một lượt DFS tiền thứ tự cho đoạn Euler liên tiếp của từng cây con.

Khi xử lý đỉnh $u$:

1. Xử lý các con nhẹ, lấy đáp án rồi xóa dữ liệu của chúng.
2. Xử lý con nặng và giữ nguyên dữ liệu của nó.
3. Duyệt các đoạn Euler của con nhẹ, thêm từng đỉnh trở lại; thêm chính $u$.
4. Dữ liệu hiện tại là đúng cây con $u$. Tính công thức bộ ba và lưu đáp án.
5. Nếu lời gọi không được yêu cầu giữ dữ liệu, xóa mọi đỉnh trong cây con $u$.

Biến `keep` chỉ quyết định việc giữ hay xóa sau khi đã lấy đáp án. Không được để dữ liệu từ hai lời gọi con nhẹ trộn vào nhau trước lúc xử lý con nặng.

## Tính đúng đắn

Quy nạp theo cây: mỗi cây con nhẹ được xử lý và dọn sạch; cây con nặng để lại đúng các đỉnh của nó. Khi thêm các cây con nhẹ cùng đỉnh cha, tập đang giữ trở thành đúng cây con cần xét. Các đại lượng $T,S_2,S_3$ được cập nhật đúng sau mỗi thay đổi tần suất, nên công thức tổ hợp trả đúng đáp án. Việc dọn dữ liệu bảo toàn bất biến cho lời gọi tiếp theo.

## Độ phức tạp và cài đặt

Nếu một đỉnh nằm trong cây con nhẹ của tổ tiên, kích thước cây con ít nhất tăng gấp đôi khi đi lên qua cạnh nhẹ đó. Vì vậy mỗi đỉnh bị duyệt lại $O(\log N)$ lần. Tổng thời gian là $O(N\log N)$, bao gồm nén màu; bộ nhớ $O(N)$.

Lời giải mẫu dùng `tree.h` để xây thứ tự Euler và mô phỏng các pha Sack bằng ngăn xếp sự kiện, tránh đệ quy sâu trên cây dây. Các giá trị $T^3$, $3TS_2$ và $S_3$ đều phải tính bằng `long long`; giới hạn hiện tại bảo đảm các giá trị trung gian nằm trong phạm vi $64$ bit. Cây con có ít hơn ba đỉnh hoặc ít hơn ba màu tự cho kết quả bằng $0$.
