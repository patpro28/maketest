# Tám biến thể luyện tập PALINCUT và PLAN

Mỗi bài có đề tiếng Việt, hai ví dụ, lời giải với chứng minh, lời giải mẫu C++17, validator, checker, bộ sinh có seed cố định và `hash.json`. Không chia subtask; hai ví dụ có trọng số 0, các test còn lại có trọng số 1, tổng điểm bài là 100.

## Thứ tự luyện tập

| Mã bài | Tên bài | Trọng tâm | Giới hạn chính |
| --- | --- | --- | --- |
| [DTPALORDER](../dtpalorder/task.md) | Cắt theo đúng thứ tự | Manacher, tham lam, in cách chọn | n, k ≤ 200000 |
| [DTPALCOUNT](../dtpalcount/task.md) | Ba loại chuỗi hạt | DP số lượng, cơ số hỗn hợp, truy vết | n ≤ 100000, d ≤ 3, mỗi số lượng ≤ 20 |
| [DTPALPRE](../dtpalpre/task.md) | Đơn hàng có quan hệ trước sau | DP tập con, mặt nạ tiền nhiệm | n ≤ 100000, k ≤ 18 |
| [DTPALCOST](../dtpalcost/task.md) | Cắt chuỗi với chi phí nhỏ nhất | DP vị trí và tập con, tổng tiền tố | n ≤ 5000, k ≤ 10 |
| [DTPLANONE](../dtplanone/task.md) | Một kho nguyên liệu | Ba lô không giới hạn, đếm số lượng | m ≤ 30, A ≤ 200000 |
| [DTPLANKINDS](../dtplankinds/task.md) | Sử dụng đúng số loại sản phẩm | DP số loại dương, hai bảng | m ≤ 20, A, B ≤ 150 |
| [DTPLANTOTAL](../dtplantotal/task.md) | Sản xuất đúng tổng số sản phẩm | Digit DP hệ 2, ba số nhớ, ways | m ≤ 8, A, B, C ≤ 10^18 |
| [DTPLANBITS](../dtplanbits/task.md) | Kế hoạch có số lượng đặc biệt | Digit DP, mặt nạ bit trước, 3^m cặp rời nhau | m ≤ 8, A, B ≤ 10^18 |

Hai bài in cách chọn dùng checker riêng, được cấu hình upload bằng `checker = 'custom'`. Checker xác thực đoạn đối xứng, biên, thứ tự, tính không giao nhau và đủ số lần xuất hiện; không yêu cầu trùng đúng các đoạn của lời giải mẫu. Sáu bài còn lại có đáp án duy nhất. Cấu hình upload theo DAYNEN, nhóm `04`, lớp `E`, loại `doituyen`; giới hạn thời gian từng bài nằm trong `info.toml`, bộ nhớ 256 MiB.

## Chạy lại

Từ thư mục gốc dự án:

```sh
python3 dtqg/palplan_tests/check.py
```

Chỉ kiểm tra một bài:

```sh
python3 dtqg/palplan_tests/check.py --problem dtplanbits
```

Khi chủ động thay đổi dữ liệu, thêm `--update-hashes`. Quy trình gọi riêng bước sinh dữ liệu, validator, sinh đáp án, checker và đối chiếu hash; không xuất HTML. Có thể chọn trình biên dịch và cờ qua `CXX`, `CXXFLAGS`.

## Nội dung kiểm tra

- Bảy bài có 26 test chính thức: hai ví dụ, tám test biên, tám test nhỏ và tám test lớn. DTPALCOUNT có thêm tám test `order_trap`, tổng cộng 34 test. Toàn bộ seed được sinh lại để kiểm tra tính tái lập.
- Mỗi bài có thêm 100 đầu vào nhỏ được sinh độc lập, đối chiếu bằng cách liệt kê vị trí các đoạn hoặc số lượng sản phẩm. Các test chính thức đủ nhỏ cũng được đối chiếu bằng cách này.
- DTPALORDER được so với cách kiểm tra đối xứng trực tiếp bằng đảo xâu. DTPALCOUNT và DTPALPRE có bản tham chiếu dùng kiểm tra xâu trực tiếp thay cho Manacher, kết hợp các điều kiện đủ trên xâu đồng nhất hoặc xen kẽ. Các trường hợp nhỏ dùng duyệt mọi cách đặt đoạn, không chỉ giữ kết thúc sớm nhất.
- DTPALCOST được so với `oracle_cost.cpp`: bảng đối xứng bậc hai và DP theo thứ tự mặt nạ, lấy cực tiểu tiền tố theo vị trí. Lời giải mẫu dùng Manacher và DP duyệt theo vị trí.
- DTPLANONE được đối chiếu bằng các lớp mới theo từng lớp đồng dư; trường hợp hệ số đồng nhất dùng công thức tổ hợp nguyên chính xác.
- DTPLANKINDS được so với `oracle_kinds.cpp`, liệt kê số lượng sản phẩm của loại mới, độc lập với truy hồi bảng dùng dương của lời giải mẫu.
- DTPLANTOTAL được đối chiếu bằng đại số: gộp bốn cặp hệ số, biểu diễn tổng số lượng các nhóm theo một biến, dùng công thức chia kẹo cho từng nhóm và tổng đa thức bằng sai phân hữu hạn. Các hệ số nhị thức tính bằng số nguyên chính xác, không dùng nghịch đảo modulo. Cách này kiểm tra được cả mục tiêu 10^18 và các loại trùng hệ số.
- DTPLANBITS được so với `oracle_bits.cpp`, đệ quy có nhớ theo hai lượng nguyên liệu còn lại sau khi bỏ bit thấp, mặt nạ cấm và chặn không âm. Lời giải mẫu duyệt các lớp số nhớ từ thấp lên cao. Trên dữ liệu nhỏ, cả hai được so thêm với liệt kê trực tiếp các số lượng và kiểm tra `x & (x >> 1)`.
- Validator có các đầu vào sai miền, sai số lượng token, thiếu/thừa dữ liệu. Checker được thử với đáp án đúng, khác khoảng trắng, sai giá trị, ký tự thừa, thiếu dữ liệu, tràn miền và cách chọn khác đáp án mẫu.
- Cấu trúc đề, hai ví dụ, mã bài, quy tắc không có tiêu đề cấp 1 trong lời giải, cấu hình upload, điểm và toàn bộ hash đều được đối chiếu.

## Các lỗi mà bộ test nhắm tới

- Đổi thứ tự độ dài của DTPALORDER; đếm một độ dài một lần thay vì đủ số lượng của DTPALCOUNT. Với DTPALCOUNT, code học sinh chọn hết từng loại theo thứ tự đầu vào bị bắt ở cả tám test mới; thử mọi hoán vị của các nhóm vẫn sai trên bảy test buộc xen kẽ. Chi tiết tại `../dtpalcount/tests/README.md`.
- Bỏ quan hệ trước sau, nhầm hướng cạnh, không xử lý chu trình trong DTPALPRE.
- Giữ duy nhất vị trí kết thúc sớm nhất trong DTPALCOST; dùng số nguyên 32 bit cho chi phí; nhầm chi phí giữ với chi phí bỏ.
- Đếm thứ tự sản xuất hoặc dùng mỗi loại một lần trong DTPLANONE; gộp nhầm các loại trùng hệ số.
- Tăng số loại mỗi lần thêm sản phẩm, hoặc dùng bảng lớp hiện tại để bắt đầu loại mới trong DTPLANKINDS.
- Bỏ phương trình tổng sản phẩm, bỏ hệ số ways, xử lý thiếu bit hoặc nhận số nhớ cuối khác 0 trong DTPLANTOTAL.
- Áp dụng điều kiện bit cho tổng thay vì từng biến; chỉ lưu hai số nhớ; gộp hai tập có cùng tổng nhưng khác mặt nạ trong DTPLANBITS.

## Kết quả

Lượt kiểm tra đầy đủ đạt cho cả tám bài: **216 test chính thức**, **800 trường hợp nhỏ độc lập**, 146 test chính thức được đối chiếu thêm bằng liệt kê trực tiếp, **64 đầu vào sai** và **156 tình huống checker**. Toàn bộ **432 mục hash** khớp.

| Mã bài | Thời gian lớn nhất của lời giải mẫu | Giới hạn upload |
| --- | ---: | ---: |
| DTPALORDER | 0.1382 giây | 2 giây |
| DTPALCOUNT | 0.0103 giây | 3 giây |
| DTPALPRE | 0.0219 giây | 3 giây |
| DTPALCOST | 0.0704 giây | 4 giây |
| DTPLANONE | 0.0136 giây | 2 giây |
| DTPLANKINDS | 0.0054 giây | 3 giây |
| DTPLANTOTAL | 0.0025 giây | 3 giây |
| DTPLANBITS | 0.0048 giây | 4 giây |

Chi tiết được ghi tại `results.json`. Thời gian phụ thuộc máy chạy; các bài được chạy với giới hạn thời gian upload thực tế.
