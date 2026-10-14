# Hướng dẫn giải

Đặt `dp[i][t]` là trạng thái có thể đạt tổng $t$ sau khi chọn đúng một mặt cho mỗi thẻ trong $i$ thẻ đầu tiên. Khởi tạo `dp[0][0]` là đúng, các trạng thái còn lại là sai.

Từ một trạng thái đạt được `dp[i][t]`, chọn mặt trước để chuyển đến `dp[i+1][t+a_i]`, hoặc chọn mặt sau để chuyển đến `dp[i+1][t+b_i]`. Chỉ lưu các tổng không vượt quá $S$ vì mọi giá trị đều dương. Hai lớp trạng thái phải tách biệt để không dùng một thẻ nhiều lần.

Ở mỗi trạng thái mới, lưu ký tự `A` hoặc `B` của phép chuyển. Nếu `dp[N][S]` không đạt được, in `No`. Ngược lại, truy vết từ $(N,S)$: đọc mặt đã chọn, trừ giá trị tương ứng và chuyển về lớp trước. Các ký tự được điền vào đúng vị trí thẻ, rồi in `Yes` và xâu kết quả.

Mỗi cách chọn của $i+1$ thẻ có một mặt của thẻ cuối cùng và một cách chọn của $i$ thẻ đầu. Hai phép chuyển xét đủ cả hai khả năng này, nên theo quy nạp bảng trạng thái biểu diễn chính xác các tổng đạt được. Truy vết đi theo các phép chuyển hợp lệ, do đó tạo ra đúng $N$ lựa chọn có tổng $S$.

Độ phức tạp: $O(NS)$ thời gian và $O(NS)$ bộ nhớ.

Lời giải đối chiếu `suffix.cpp` dùng bitset cho các tổng đạt được của đoạn thẻ còn lại, rồi dựng đáp án từ trái sang phải. Checker tự kiểm tra tính khả thi và tổng của xâu được in, chấp nhận mọi đáp án hợp lệ dùng `A`/`B`.
