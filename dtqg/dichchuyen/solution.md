# Lời giải DICHCHUYEN — Cổng dịch chuyển liên vùng

## Vì sao cần hai cây

Một cổng $(l,r,a,b,c)$ biểu diễn cạnh trọng số $c$ từ mọi đỉnh của đoạn nguồn $[l,r]$ đến mọi đỉnh của đoạn đích $[a,b]$. Dựng trực tiếp có thể tốn $O(QN^2)$ cạnh.

Cần thu một đỉnh bất kỳ của đoạn nguồn về một đại diện, rồi phát từ đại diện đến một đỉnh bất kỳ của đoạn đích. Hai chiều này phải dùng hai cây riêng; nếu thêm cả hai chiều trên cùng một cây, người dùng có thể đi miễn phí giữa các địa điểm mà không sử dụng cổng nào.

## Cấu trúc đồ thị nén

Dùng hai segment tree có cùng cách chia đoạn và dùng chung các lá $1,\ldots,N$:

- **Cây nhận:** cạnh từ con lên cha, trọng số $0$.
- **Cây phát:** cạnh từ cha xuống con, trọng số $0$.

Các nút trong của hai cây là các đỉnh khác nhau. Chỉ các lá đại diện địa điểm thật được dùng chung.

Với mỗi cổng, tạo một đỉnh trung gian $h$ riêng:

1. Phân rã đoạn nguồn $[l,r]$ thành các nút chuẩn trên cây nhận. Với mỗi nút có đỉnh $v$, thêm cạnh $v\to h$ trọng số $c$.
2. Phân rã đoạn đích $[a,b]$ thành các nút chuẩn trên cây phát. Với mỗi nút có đỉnh $w$, thêm cạnh $h\to w$ trọng số $0$.

Đỉnh trung gian bảo đảm mỗi cổng chỉ thêm $O(\log N)$ cạnh. Không nối chéo từng cặp nút phủ đoạn nguồn và đoạn đích vì cách đó thêm $O(\log^2 N)$ cạnh mỗi cổng. Chi phí $c$ chỉ được tính một lần trên một lần sử dụng cổng.

## Đường đi ngắn nhất

Chạy Dijkstra từ lá $S$. Khoảng cách đến lá $T$ là đáp án. Có thể kết thúc khi lấy được trạng thái hiện hành của $T$ ra khỏi hàng đợi ưu tiên. Nếu không tới được $T$, in $-1$.

Khoảng cách dùng số nguyên $64$ bit. Chi phí bằng $0$, đoạn giao nhau, cổng trùng nhau và $S=T$ không cần xử lý bằng quy tắc riêng ngoài Dijkstra thông thường.

## Chứng minh đúng

Xét một lần dùng cổng từ $x\in[l,r]$ tới $y\in[a,b]$. Từ lá $x$, đi lên cây nhận tới nút chuẩn của đoạn nguồn chứa $x$, đi qua đỉnh trung gian với chi phí $c$, rồi xuống cây phát đến lá $y$. Đường đi có đúng chi phí $c$. Vì vậy, mọi hành trình hợp lệ đều có đường đi cùng chi phí trong đồ thị nén.

Ngược lại, khi đi từ một lá lên cây nhận, đường đi chỉ có thể rời cây nhận qua một đỉnh trung gian của cổng có đoạn nguồn chứa lá đó. Từ đỉnh trung gian, đường đi vào cây phát và chỉ đi xuống được đến các lá trong đoạn đích của cùng cổng. Không có cạnh trực tiếp giữa các nút trong của cây nhận và cây phát. Do đó, một đường đi giữa các lá tách được thành những lần dùng cổng hợp lệ, giữ nguyên tổng chi phí.

Hai đồ thị giữ nguyên chi phí đường đi ngắn nhất giữa các địa điểm. Do mọi trọng số không âm, Dijkstra tính đúng đáp án.

## Độ phức tạp

Hai cây dùng chung lá có $3N-2$ đỉnh. Thêm $Q$ đỉnh trung gian và $O(N+Q\log(N+1))$ cạnh.

- Thời gian: $O((N+Q\log(N+1))\log(N+Q+1))$.
- Bộ nhớ: $O(N+Q\log(N+1))$, tính cả hàng đợi ưu tiên.

## Kiểm thử

Chạy `python3 custom/dichchuyen/tests/check.py` từ gốc dự án. Oracle không dùng đồ thị segment tree: nó kích hoạt cổng khi gặp địa điểm nguồn có khoảng cách nhỏ nhất, dùng chia căn để tìm cổng chưa kích hoạt, và dùng tập kế tiếp để duyệt các địa điểm đích chưa chốt. Các test nhỏ còn được so sánh với đồ thị dựng đủ mọi cạnh nguồn–đích. Không xuất HTML.
