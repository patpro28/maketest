# Lời giải

Không thể chỉ tìm cây khung có tổng chi phí chẵn. Ví dụ $n=2$, cả bốn cạnh đều có chi phí $1$: mọi cây khung có chi phí $3$, nhưng chọn cả chu trình cho đáp án $4$.

Xử lý lần lượt các cột từ trái sang phải. Giữ `dp[s][p]` là tổng chi phí nhỏ nhất của tập cạnh trên phần đã xử lý, trong đó:

- `s=1` nếu hai đỉnh của cột cuối cùng cùng thành phần liên thông; `s=0` nếu chúng khác thành phần.
- `p` là tính chẵn lẻ của tổng chi phí.
- Mọi thành phần liên thông đều phải chứa ít nhất một đỉnh thuộc cột cuối cùng. Thành phần đã mất tiếp xúc với biên sẽ không bao giờ nối được với các cột tương lai.

Khởi tạo cột đầu bằng hai lựa chọn: bỏ cạnh đứng (`dp[0][0]=0`), hoặc chọn cạnh đứng (`dp[1][w_1 mod 2]=w_1`).

Khi thêm cột $i+1$, có ba cạnh mới: hai cạnh ngang và cạnh đứng của cột mới. Duyệt cả tám tập con của ba cạnh này. Dùng DSU trên bốn đỉnh để xác định liên thông; hợp nhất sẵn hai đỉnh cũ nếu `s=1`. Loại chuyển trạng thái nếu một thành phần chứa đỉnh cũ không chứa đỉnh mới nào. Các chuyển còn lại cập nhật trạng thái liên thông, chẵn lẻ và chi phí. Không loại chuyển tạo chu trình.

Có thể tính trước bảng chuyển `next[s][mask]`, vì tính hợp lệ không phụ thuộc trọng số. Sau cột cuối, lấy `dp[1][0]`; nếu không đạt được thì in `-1`.

## Tính đúng đắn

Mỗi nghiệm liên thông cuối cùng khi giới hạn vào các cột đã xét đều thỏa điều kiện biên: nếu có một thành phần không chạm cột cuối, không cạnh nào ở tương lai có thể nối nó vào phần còn lại. Mỗi tập cạnh mới thuộc đúng một trong tám lựa chọn được duyệt, và phép kiểm tra DSU loại chính xác các lựa chọn làm mất điều kiện biên. Do đó quy hoạch động xét mọi nghiệm có thể hoàn thành, đồng thời chỉ giữ chi phí nhỏ nhất cho mỗi trạng thái tương đương đối với phần tương lai. Tại cột cuối, điều kiện `s=1` cùng bất biến biên bảo đảm toàn bộ đồ thị liên thông; `p=0` bảo đảm tổng chi phí chẵn. Giá trị lấy ra là đáp án tối ưu.

## Độ phức tạp

Thời gian $O(n)$ mỗi bộ dữ liệu. Trạng thái DP dùng $O(1)$ bộ nhớ; chương trình lưu hai hàng cạnh ngang nên tổng bộ nhớ $O(n)$. Dùng số nguyên 64 bit cho chi phí và giá trị vô cực.

## Bộ test

40 file: 10 file nhóm nhỏ (gồm ví dụ), 10 file toàn chi phí chẵn, 10 file $n\le1000$, 10 file tổng quát. Có $n=1$, trường hợp vô nghiệm, toàn cạnh lẻ, chu trình cần thiết, trọng số cực đại, nhiều cạnh bằng nhau, cạnh đứng/ngang đắt hoặc rẻ, và $T=20$ với mọi $n=10^5$.

Chạy `python3 custom/net2line/tests/check.py` từ thư mục gốc để sinh và kiểm tra toàn bộ dữ liệu, đối chiếu vét cạn, kiểm tra validator/checker và đối chiếu hash, không xuất HTML.
