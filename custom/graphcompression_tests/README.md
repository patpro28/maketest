# Ba bài luyện segment tree để nén đồ thị

| Mã bài | Nội dung | Cấu trúc và thuật toán |
| --- | --- | --- |
| VEXE | Vé từ một trạm đến một trạm bất kỳ trong đoạn đích | Cây phát, cạnh điểm → đoạn, Dijkstra |
| DAYCHUYEN | Một công việc chờ tất cả công việc trong đoạn | Cây nhận, cạnh đoạn → điểm, topo và DP |
| DICHCHUYEN | Cổng có đoạn nguồn và đoạn đích | Hai cây chung lá, đỉnh trung gian cho mỗi cổng, Dijkstra |

Các bài dùng mã riêng trong `custom/vexe`, `custom/daychuyen`, `custom/dichchuyen`. Trọng tâm là nén quan hệ phụ thuộc bằng segment tree, thuộc biến thể chuyên sâu; không xếp vào dải SEG0 hay nhóm segment tree trên thời gian.

Mỗi thư mục có đề tiếng Việt trong `task.md`, lời giải trong `solution.md`, chương trình C++17 chuẩn, bộ sinh, verifier, checker, hai ví dụ và `hash.json`. Các đề theo cấu trúc knapsack của dự án, không có Subtask và không xuất HTML.

## Sinh và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/graphcompression_tests/check.py
```

Chạy riêng một bài:

```sh
python3 custom/vexe/tests/check.py
python3 custom/daychuyen/tests/check.py
python3 custom/dichchuyen/tests/check.py
```

Chỉ khi chủ động sửa bộ sinh hoặc đáp án chuẩn, cập nhật hash bằng:

```sh
python3 custom/graphcompression_tests/check.py --update-hashes
```

Có thể chọn một hoặc nhiều bài bằng `--problem vexe daychuyen`. Script gọi riêng các bước biên dịch, sinh đầu vào, kiểm tra đầu vào, sinh đáp án và chấm của `Problem`; không gọi `--dev`, `--test` hay bước HTML. Không cần cài thư viện mới. Trình biên dịch lấy từ `CXX`, cờ biên dịch lấy từ `CXXFLAGS` nếu có; mặc định là C++17 với cảnh báo được coi là lỗi.

## Bộ dữ liệu chính

Mỗi bài có 36 test: 2 ví dụ, 12 trường hợp biên, 8 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Giới hạn chung là $N,Q\le100000$, cho phép $Q=0$.

- Có $N=1$, kích thước không phải lũy thừa hai, đoạn một phần tử, đoạn toàn dãy, đoạn gần toàn dãy và các đầu mút biên.
- Hai bài đường đi có chi phí bằng $0$, cạnh/cổng trùng nhau, chu trình, hướng đi một chiều, đỉnh không đến được, đường rẻ hơn được phát hiện sau và chuỗi chi phí vượt $32$ bit.
- Bài dây chuyền có các nhánh song song, nhiều điều kiện cùng tác động một công việc, ràng buộc trùng/chồng nhau, DAG theo cả hai chiều chỉ số, tự phụ thuộc và chu trình nhiều đỉnh.
- Bài dịch chuyển có nguồn giao đích, $S=T$, kiểm tra không được đi miễn phí giữa các lá và các cổng rộng cần đỉnh trung gian để tránh nhân số cạnh lên $O(\log^2N)$.
- Test chuỗi lớn có đáp án được kiểm tra bằng công thức: VEXE là các bội liên tiếp của $10^9$, DAYCHUYEN là $10^{14}$, DICHCHUYEN là $99999\cdot10^9$.

Giới hạn thời gian tại máy và khi tải lên được đặt thống nhất: VEXE 4 giây, DAYCHUYEN 4 giây, DICHCHUYEN 6 giây. Cấu hình bộ nhớ khi tải lên là 512 MiB.

## Đối chiếu độc lập

Mọi test chính được so với `oracle.cpp`, dùng cách tổ chức khác lời giải chuẩn:

- **VEXE:** hàng đợi ưu tiên chứa đề nghị đến một đoạn; tập kế tiếp bỏ qua các trạm đã chốt. Một vé được kích hoạt khi trạm xuất phát được chốt. Không dựng đồ thị segment tree.
- **DAYCHUYEN:** dựng đồ thị các đoạn lũy thừa hai kiểu sparse table; mỗi ràng buộc nối từ tối đa hai đoạn có thể chồng nhau. Cách chia và số đỉnh khác cây phân đôi của lời giải chuẩn.
- **DICHCHUYEN:** chia căn tìm các cổng có đoạn nguồn chứa địa điểm vừa chốt; kích hoạt mỗi cổng đúng một lần. Hàng đợi đề nghị đoạn đích và tập kế tiếp giống nguyên lý của oracle VEXE. Không dựng hai segment tree.

Các ví dụ, test biên và test nhỏ còn được đối chiếu bằng đồ thị gốc dựng đủ cạnh. Hai bài đường đi dùng Bellman–Ford; bài dây chuyền quét lặp các công việc có đủ tiền nhiệm hoàn thành, độc lập với cách sắp topo của lời giải chuẩn.

Script còn kiểm tra 1.813 trường hợp bổ sung:

- VEXE: vét cạn mọi vé đơn với chi phí thuộc $\{0,1,10^9\}$ và mọi trạm xuất phát khi $N\le3$.
- DAYCHUYEN: vét cạn mọi đồ thị phụ thuộc điểm trên tối đa ba công việc, gồm cả khuyên tự phụ thuộc.
- DICHCHUYEN: vét cạn mọi cặp đoạn của một cổng khi $N\le3$, với hai mức chi phí và các cặp nguồn–đích đại diện.
- Mỗi bài thêm 250 dữ liệu ngẫu nhiên nhỏ và 20 trường hợp biến đổi bằng cách hoán vị hoặc nhân đôi ràng buộc. Bài dây chuyền có DAG theo thứ tự topo hoán vị ngẫu nhiên, ngoài các dữ liệu có thể chứa chu trình.

Ngoài đáp án, script kiểm tra verifier từ chối dữ liệu sai giới hạn, thiếu/thừa trường, đoạn đảo ngược, thời gian công việc không dương; kiểm tra checker chấp nhận thay đổi khoảng trắng, từ chối sai/thiếu/thừa đáp án, chữ và số tràn 64 bit. Đồng thời đối chiếu heading, nội dung ví dụ, tính tái lập của toàn bộ bộ sinh và tất cả hash đầu vào/đầu ra.

Các chương trình đã biên dịch, `params.h`, `in/` và `out/` là sản phẩm sinh tự động. Mã nguồn và hash được lưu để tái tạo bộ test.
