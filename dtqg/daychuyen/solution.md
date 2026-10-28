# Lời giải DAYCHUYEN — Dây chuyền sản xuất

## Đồ thị phụ thuộc

Tạo một đỉnh cho mỗi công việc. Ràng buộc $(l,r,u)$ tạo các cạnh $j\to u$ với mọi $j\in[l,r]$. Một lịch hợp lệ tồn tại khi và chỉ khi đồ thị này không có chu trình: mọi công việc có thời gian thực hiện dương, nên không thể hoàn thành các công việc phụ thuộc vòng vào nhau.

Nếu đồ thị là DAG, thời điểm hoàn thành sớm nhất của công việc $u$ là

$$F_u=d_u+\max_{v\to u}F_v,$$

trong đó giá trị lớn nhất của tập rỗng bằng $0$. Đáp án là $\max_u F_u$. Không cộng thời gian của các nhánh độc lập vì chúng có thể chạy song song.

## Nén các cạnh đoạn → điểm

Dựng segment tree trên chỉ số công việc. Lá $j$ là đỉnh công việc $j$; mỗi nút trong có một đỉnh phụ. Thêm cạnh từ mỗi đỉnh con đến đỉnh cha. Đỉnh phụ có thời gian thực hiện bằng $0$.

Với ràng buộc $(l,r,u)$, phân rã $[l,r]$ thành $O(\log N)$ nút chuẩn. Từ mỗi nút đó, thêm cạnh đến lá $u$.

Đỉnh đại diện một đoạn chỉ được xử lý sau khi cả hai đỉnh con đã được xử lý. Thời điểm tại đỉnh này là giá trị lớn nhất trong các thời điểm hoàn thành của toàn bộ công việc thuộc đoạn. Vì vậy, cạnh từ đỉnh đoạn đến $u$ biểu diễn đúng yêu cầu chờ tất cả công việc trong đoạn.

## Topo và quy hoạch động

Dùng thuật toán Kahn. Đếm bậc vào theo từng cạnh, kể cả các cạnh trùng nhau.

1. Đưa mọi đỉnh có bậc vào bằng $0$ vào hàng đợi. Khởi tạo nhãn thời gian của mọi đỉnh bằng $0$.
2. Khi lấy đỉnh $u$ ra, nếu đó là công việc thật thì cộng $d_u$ vào nhãn của nó; nếu là đỉnh phụ thì không cộng gì.
3. Với mỗi cạnh $u\to v$, cập nhật nhãn của $v$ bằng giá trị lớn hơn giữa nhãn hiện tại và nhãn của $u$. Giảm bậc vào của $v$; nếu về $0$, đưa $v$ vào hàng đợi.
4. Nếu số đỉnh xử lý được nhỏ hơn tổng số đỉnh, in $-1$. Ngược lại, in nhãn lớn nhất tại các lá.

Dùng số nguyên $64$ bit cho nhãn thời gian. Cộng thời gian công việc đúng một lần, tại lúc lấy lá ra khỏi hàng đợi.

## Chứng minh đúng

Mỗi cạnh gốc $j\to u$ được thay bằng đường đi từ lá $j$ lên nút chuẩn chứa $j$, sau đó đến lá $u$. Mọi đường đi như vậy đều ứng với một ràng buộc thật.

Các cạnh cây tự chúng không tạo chu trình. Bất kỳ chu trình nào trong đồ thị nén cũng phải sử dụng các cạnh từ nút đoạn đến lá; thay các đoạn đường đó bằng cạnh phụ thuộc gốc sẽ tạo một chu trình trong đồ thị gốc. Chiều ngược lại suy ra từ việc mỗi cạnh gốc có đường đi thay thế. Do đó, hai đồ thị đồng thời có hoặc không có chu trình.

Khi đồ thị không có chu trình, thứ tự topo bảo đảm mọi tiền nhiệm được xử lý trước đỉnh hiện tại. Quy nạp theo thứ tự này, nhãn tại một đỉnh phụ là thời điểm sớm nhất toàn bộ công việc trong đoạn của nó hoàn thành, còn nhãn tại lá $u$ bằng $d_u$ cộng thời điểm sớm nhất mọi điều kiện của $u$ được thỏa mãn. Đây vừa là cận dưới bắt buộc, vừa đạt được bằng cách bắt đầu mỗi công việc ngay khi các điều kiện được thỏa mãn. Lấy giá trị lớn nhất tại các lá cho đáp án đúng.

## Độ phức tạp

- Đồ thị có $2N-1$ đỉnh và $O(N+Q\log(N+1))$ cạnh.
- Thời gian và bộ nhớ: $O(N+Q\log(N+1))$.

## Kiểm thử

Chạy `python3 custom/daychuyen/tests/check.py` từ gốc dự án. Các test bao gồm chạy song song, chuỗi phụ thuộc dài, nhiều ràng buộc trùng hoặc chồng nhau, tự phụ thuộc và chu trình nằm trong một phần đồ thị. Oracle dùng các đoạn lũy thừa hai kiểu sparse table thay cho cây phân đôi; các trường hợp nhỏ còn được đối chiếu bằng đồ thị phụ thuộc dựng trực tiếp. Không xuất HTML.
