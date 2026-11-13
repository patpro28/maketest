## Nhìn truy vấn trên cây có gốc

Đặt gốc cây tại thành phố $1$. Đường đi từ thành phố $v$ lên gốc đi qua $u$ khi và chỉ khi $v$ thuộc cây con của $u$, tính cả $u$. Vì vậy, đáp án là số mã lính canh khác nhau trong cây con đó. Mỗi mã xuất hiện trong cây con có thể chọn một thành phố làm nơi xuất phát, nên tất cả các mã tìm được đều có thể tiếp viện.

## Thuật toán

Duyệt cây một lần để tạo danh sách con của từng đỉnh. Lưu mã lính canh hiện tại của mỗi thành phố trong mảng $c$.

- Với sự kiện `1 u k`, gán $c_u\gets k$.
- Với yêu cầu `2 u`, dùng DFS từ $u$ và chỉ đi theo cạnh nối một đỉnh với các con của nó. Dùng mảng `seen` lưu số thứ tự sự kiện gần nhất đã đếm mỗi mã. Khi gặp mã $c_v$ lần đầu trong sự kiện hiện tại, tăng đáp án và ghi lại số thứ tự sự kiện.

DFS thăm đúng các thành phố thuộc cây con của $u$. Mảng `seen` đảm bảo mỗi mã xuất hiện ở đó đóng góp đúng một đơn vị, nên giá trị in ra là số lính có thể tiếp viện. Dùng ngăn xếp tường minh để duyệt cây.

## Độ phức tạp

Dựng danh sách con mất $O(N)$ thời gian. Cập nhật mất $O(1)$. Một yêu cầu đếm mất thời gian tuyến tính theo kích thước cây con, nên tổng thời gian là $O(NM)$ trong trường hợp xấu nhất. Bộ nhớ là $O(N+K)$.
