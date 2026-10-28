# Lời giải MANGDONG — Mạng liên lạc biến động

## Subtask 1 — 30%

Lưu tập đường đang tồn tại. Với mỗi dấu `?`, dựng đồ thị hiện tại và duyệt các thành phần liên thông bằng BFS/DFS. Một thành phần có $r$ đỉnh đỏ và $b$ đỉnh xanh đóng góp $rb$ cặp.

Tối đa có $Q$ đường đang tồn tại. Thời gian $O(Q(N+Q))$, phù hợp $N,Q\le2000$.

## Subtask 2 — 30%

Không có thao tác xóa, nên dùng DSU thông thường với nén đường đi. Mỗi gốc lưu số đỉnh đỏ và xanh. Giữ tổng đáp án $F$ của mọi thành phần.

Khi hợp nhất hai thành phần khác nhau $(r_1,b_1)$ và $(r_2,b_2)$:

$$F\gets F+r_1b_2+r_2b_1.$$

Nếu hai đầu đã cùng thành phần thì không thay đổi gì. Đáp án cho dấu `?` là $F$. Tổng thời gian $O((N+Q)\alpha(N))$.

## Subtask 3 — 40%: khoảng tồn tại của một đường

Đánh số thao tác từ $0$ đến $Q-1$. Chuẩn hóa đường bằng cặp $(\min(u,v),\max(u,v))$.

Đường được thêm tại thời điểm $l$, xóa tại $r$ tồn tại trong đoạn thời gian $[l,r-1]$. Nếu chưa bị xóa khi hết dữ liệu thì đoạn tồn tại là $[l,Q-1]$. Cùng một đường được thêm lại sẽ tạo một đoạn tồn tại khác; không gộp qua thời gian nó đã bị xóa.

Dựng segment tree trên trục thời gian. Đưa mỗi đường vào các nút phủ đoạn tồn tại của nó, mất $O(\log Q)$ nút cho một đoạn. Một đường không cần được đưa xuống mọi lá riêng lẻ.

## DSU rollback

DSU vẫn lưu cha, kích thước thành phần, số đỉnh hai màu và $F$. Dùng gộp theo kích thước, **không nén đường đi**, để mỗi lần gộp chỉ thay đổi một số hữu hạn trường và có thể hoàn tác.

Mỗi lần gộp thành công lưu hai gốc và giá trị $F$ cũ vào lịch sử. Gốc bị gắn vào gốc khác vẫn giữ nguyên kích thước và số màu của nó; khi hoàn tác, dùng các giá trị này để trừ khỏi gốc nhận. Nếu hai đầu đã cùng gốc, không thêm bản ghi. Trước khi xử lý một nút, lưu kích thước lịch sử; sau khi xong nút, hoàn tác đến đúng kích thước đó.

DFS trên segment tree:

1. Lưu mốc lịch sử, gộp mọi đường lưu tại nút.
2. Nếu là lá tương ứng dấu `?`, in $F$.
3. Nếu chưa là lá, duyệt lần lượt hai con.
4. Hoàn tác về mốc trước khi vào nút.

## Chứng minh đúng

Một đường đang tồn tại tại thời điểm $t$ được lưu đúng một lần trên đường từ gốc segment tree đến lá $t$, theo tính chất phân rã đoạn thành các nút rời nhau. Đường không tồn tại tại $t$ không có nút lưu nào trên đường đi đó. Vì vậy khi tới lá $t$, DSU biểu diễn đúng đồ thị tại thời điểm này.

Mỗi thành phần có đúng $rb$ cặp đỏ–xanh. Công thức gộp thêm chính xác các cặp nằm giữa hai thành phần trước đó. Các đường tạo chu trình không đổi phân hoạch nên không đổi đáp án. Rollback phục hồi toàn bộ trạng thái trước khi rời nhánh, do đó các nhánh không ảnh hưởng nhau. Mọi câu trả lời được tính đúng và in theo thứ tự thời gian.

## Độ phức tạp và lưu ý

- Dựng các đoạn bằng `map`: $O(Q\log Q)$.
- DSU gộp theo kích thước không nén đường đi có chiều cao $O(\log N)$.
- Tổng thời gian $O(N+Q\log Q\log N)$, bộ nhớ $O(N+Q\log Q)$.
- $F\le\lfloor N^2/4\rfloor\le10^{10}$: dùng `long long` cho số cặp và các phép nhân.
- Không hoàn tác theo số cạnh thử gộp: cạnh tạo chu trình không tạo bản ghi. Phải hoàn tác theo mốc kích thước lịch sử.
- Cần xử lý cạnh còn tồn tại đến cuối, cạnh thêm lại và cách viết đảo hai đầu.

## Kiểm chứng

Bộ kiểm tra đối chiếu dữ liệu nhỏ với BFS trên đồ thị hiện tại. Test lớn có xóa được đối chiếu bằng một thuật toán chia khối thời gian độc lập: dựng DSU từ các cạnh không thay đổi trong khối, rồi gộp riêng các cạnh thay đổi cho mỗi truy vấn. Oracle này không dùng rollback hay segment tree thời gian.
