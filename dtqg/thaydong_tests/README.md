# Bộ bài từ bảy PDF của Thầy Đồng

Đã loại toàn bộ `Kiem tra.pdf` theo yêu cầu. Bộ này chỉ gồm bảy bài từ bảy PDF riêng; ROBOT ở đây là bài đếm lần rẽ, không phải Robot chuyển hộp trong đề kiểm tra.

## Thứ tự luyện tập từ dễ đến khó

Thứ tự dựa trên độ khó nhận xét, số trạng thái và yêu cầu cài đặt, không chỉ dựa trên thời gian chạy.

| Thứ tự | Mã bài | Tên bài | Trọng tâm và lý do |
| ---: | --- | --- | --- |
| 1 | [DTROBOT](../dtrobot/task.md) | Robot đếm lần rẽ | Mô phỏng một lượt, định thức hai vectơ, phân biệt quay ngược với rẽ |
| 2 | [DTREBUSS](../dtrebuss/task.md) | Điền chữ số trong phép cộng | DP hai số nhớ, điều kiện chữ số đầu, truy vết một đáp án |
| 3 | [DTSP](../dtsp/task.md) | Bán hàng khuyến mại | DP ba số lượng, chứng minh chỉ cần giữ tiến độ lớn nhất |
| 4 | [DTFACTOR](../dtfactor/task.md) | Phân tích thành thừa số | Phân tích nguyên tố, kết quả phụ thuộc số mũ, DP trên ước và lưu kết quả theo dạng |
| 5 | [DTBTNK](../dtbtnk/task.md) | Biểu thức ngoặc bậc k | DP cân bằng, loại dãy con trùng bằng lần xuất hiện trước, hiệu hai chặn độ sâu |
| 6 | [DTDNA](../dtdna/task.md) | So sánh hai đoạn DNA | Gặp nhau ở giữa, sinh trạng thái bằng đảo đoạn, mã hóa đầy đủ 128 bit |
| 7 | [DTNUMSET](../dtnumset/task.md) | Tập số | Dãy con phân biệt, cận số, chuẩn hóa số 0, số nguyên lớn và xử lý riêng đoạn hẹp |

Mỗi bài có `task.md`, `solution.md`, lời giải C++17, validator, checker, bộ sinh, dữ liệu đầu vào/đáp án và `hash.json`. Chỉ REBUSS có nhiều đáp án và dùng checker riêng khi upload. Cấu hình upload theo DAYNEN: nhóm `04`, lớp `E`, loại `doituyen`, tổng điểm 100, bộ nhớ 256 MiB. Ví dụ có trọng số 0, mỗi test sinh có trọng số 1. Không dùng manifest điểm riêng và không chia subtask.

## Giới hạn, khối lượng xử lý và kích thước input

Mọi file `.in` phải không vượt **1.000.000 byte**, mức chặt hơn 1 MiB. Chương trình kiểm tra đo trực tiếp số byte sau khi sinh, không chỉ dựa vào độ dài lý thuyết.

Giới hạn công việc được tính theo lượt xử lý chính của từng thuật toán. Đây không phải số lệnh máy: một ô DP hoặc một thao tác tập băm gồm nhiều lệnh; phép toán số lớn được phân biệt riêng theo các khối cơ số 10^9. Chạy `python3 dtqg/thaydong_tests/budget.py` để tái lập các chặn trong `budget.json`.

| Bài | Giới hạn được dùng | Chặn công việc chính | Thay đổi so với PDF |
| --- | --- | --- | --- |
| ROBOT | n ≤ 70000 | 69998 cặp bước liên tiếp | Giảm từ 10^6 để mọi cách ghi tọa độ theo định dạng chuẩn nằm trong 1 MB |
| REBUSS | mỗi xâu dài ≤ 100000 | ≤ 20000000 cặp chữ số | Tăng từ 50 chữ số |
| SP | a, b, c ≤ 270, s ≤ 10^6 | 19902511 ô DP, mỗi ô tối đa ba chuyển hằng số | Tăng các số lượng từ 200 lên 270 |
| FACTOR | T ≤ 150, N ≤ 10^12 | < 20000000 lượt thử chia, đánh dấu sàng và xét cặp ước, nhờ dùng chung kết quả theo (m,k) | Tăng T từ 100 lên 150, giữ giới hạn N |
| BTNK | n ≤ 4000, k ≤ n/2 | ≤ 16008000 ô cân bằng trong hai lượt | Tăng n từ 1000 lên 4000 |
| DNA | n ≤ 45 | < 18000000 lượt đổi cặp ký tự và sinh trạng thái ở hai phía | Tăng n từ 30 lên 45 |
| NUMSET | dạng tổng quát ≤ 1000 chữ số; dạng hẹp ≤ 200000 chữ số, B−A ≤ 1000000 | < 19000000 phép cộng/trừ khối 10^9 ở miền tổng quát; miền hẹp chỉ cần bảng next và cập nhật hậu tố số tăng dần | Giữ dạng tổng quát 1000 chữ số vì chi phí số lớn; tăng miền dài từ 30000 lên 200000 và độ rộng từ dưới 1000 lên 1000000 |

ROBOT có thể cần 14 byte cho một dòng tọa độ có hai thành phần âm năm chữ số. Với 70000 điểm và dòng đầu, định dạng LF chuẩn vẫn dưới 1.000.000 byte. Các file sinh dùng đúng một dấu cách giữa số và LF cuối dòng.

## Đối chiếu nguồn và các chỗ làm rõ

Bảy PDF gốc đều được trích xuất văn bản và xem hình trang để xác nhận ký hiệu, giới hạn, ví dụ. Đường dẫn và SHA-256 nằm trong `sources.json`. Các ví dụ gốc được giữ nguyên thứ tự và nội dung; REBUSS chấp nhận mọi cách điền hợp lệ thay vì bắt đúng cách điền được minh họa trong PDF.

- FACTOR: PDF viết thừa số nguyên dương, nhưng cho phép thừa số 1 sẽ tạo vô hạn cách, trái yêu cầu và ví dụ. Bản chuyển ghi rõ mỗi thừa số từ 2 trở lên, có ít nhất hai thừa số. Ví dụ 64 cho 10 cách, 30 cho 4 và 100 cho 8 đều khớp. Giữ đúng giả thiết các số mũ nguyên tố bằng nhau; không mở rộng âm thầm sang mọi N.
- BTNK: từ “xâu con” trong PDF được định nghĩa bằng xóa ký tự. Bản chuyển dùng “dãy con” và nhấn mạnh đếm theo nội dung, không theo các bộ vị trí. Bậc là đúng k; không tính tất cả bậc ≤ k.
- DNA: giữ nguyên bảng chữ cái `A`, `D`, `G`, `T` của nguồn, không đổi `D` thành `C`. Mỗi thao tác đảo một đoạn liên tiếp, không phải chọn tùy ý các vị trí.
- SP: một nhóm cần ít nhất s điểm; mỗi nắp chỉ dùng một lần, không chia nắp, không chuyển điểm dư sang nhóm khác.
- REBUSS: các dấu sao độc lập; chữ số đầu khác 0, kể cả số một chữ số. Xâu có chữ số 0 cố định ở đầu là đầu vào hợp lệ nhưng không có lời giải.
- NUMSET: kết quả là số nguyên chính xác, không tự thêm modulo; số 0 được tính đúng một lần khi nguồn có chữ số 0. Hai miền dữ liệu được ghi trong ràng buộc, không thêm bảng subtask khi chưa được yêu cầu.

Các chương trình dùng nhập/xuất chuẩn khi không có tệp nguồn; nếu tệp `*.INP` tương ứng hiện diện, chúng đọc/ghi theo tên gốc. FACTOR giữ tên `factor.INP`/`factor.OUT` đúng chữ hoa/thường của PDF.

## Chạy lại

Từ thư mục gốc:

```sh
python3 dtqg/thaydong_tests/check.py
```

Chỉ kiểm tra một hoặc nhiều bài:

```sh
python3 dtqg/thaydong_tests/check.py --problem dtbtnk --problem dtnumset
```

Sau khi chủ động sửa dữ liệu, thêm `--update-hashes`. Không dùng chế độ tự xuất HTML. Có thể chọn trình biên dịch qua `CXX` và cờ qua `CXXFLAGS`.

## Kiểm tra độc lập

Mỗi bài có 16 test sinh ban đầu: bốn test biên, bốn test nhỏ, bốn test trung bình và bốn test lớn, ngoài ví dụ nguồn. SP có thêm tám test `greedy_trap`, tổng cộng 26 test chính thức cho riêng SP. Mỗi bài còn có 80 trường hợp nhỏ được tạo độc lập. Mọi seed chính thức được sinh lại và so nội dung, mỗi input được validator kiểm tra, mỗi đáp án được checker xác nhận, toàn bộ hash được đối chiếu.

- ROBOT: cách tham chiếu mã hóa bốn hướng và xét hiệu hướng modulo 4, độc lập với định thức. Có quay ngược, đi thẳng, vòng rẽ một phía, tọa độ âm dài và số điểm tối đa.
- REBUSS: cách tham chiếu chọn chữ số tổng và chữ số số hạng đầu rồi suy ra chữ số số hạng còn lại, có nhớ bộ chuyển; lời giải mẫu chọn hai số hạng và suy ra tổng. Checker xác thực mẫu, số 0 đầu, từng cột cộng, độ dài và dữ liệu thừa. Có phép điền khác đáp án mẫu, toàn dấu sao, dây truyền nhớ dài, số không có cột cao và trạng thái không có lời giải.
- SP: `oracle_sp.cpp` liệt kê các nhóm đổi tối thiểu theo số nắp từng loại, rồi DP lấy một nhóm hoàn chỉnh từ kho còn lại. Cách này độc lập với DP tiến độ sau từng nắp của lời giải mẫu. Có phản ví dụ lấy tổng điểm chia s, s nhỏ hơn giá trị một nắp, không có nắp, số lượng tối đa và s vượt tổng điểm. Tám test `greedy_trap` chạy trực tiếp code học sinh ưu tiên nắp 3 điểm và yêu cầu checker trả WA; gồm các ngưỡng 7, 9, 10, 13, trường hợp đủ ba loại và số lượng 270. Chi tiết tại `../dtsp/tests/README.md`.
- FACTOR: `oracle_factor.cpp` đệ quy chọn các thừa số không giảm, với bộ nhớ theo phần tích còn lại và cận thừa số. Không dùng DP đồng xu trên ước hoặc cache theo (m,k) như lời giải mẫu. Dữ liệu phủ các dạng số mũ cho phép, số nguyên tố gần 10^12, lũy thừa nguyên tố, dạng bình phương của bảy số nguyên tố và nhiều bộ lặp dạng.
- BTNK: cách tham chiếu dùng vị trí xuất hiện đầu tiên của từng loại ngoặc làm biểu diễn dãy con duy nhất, DP theo vị trí/cân bằng và đã chạm k hay chưa. Cách này không trừ bản chụp lần xuất hiện trước. Dữ liệu nhỏ còn liệt kê mọi tập vị trí, gom xâu bằng tập và kiểm tra cân bằng/độ sâu trực tiếp.
- DNA: cách tham chiếu dùng xâu đầy đủ và hai lớp đảo đoạn, độc lập với mã hai bit. Các xâu nhỏ được kiểm tra thêm bằng BFS một phía tới độ sâu bốn. Có cùng đa tập ký tự nhưng Different, xâu giống nhau, khác số lượng ký tự, đảo toàn bộ và các trường hợp độ dài 45.
- NUMSET: dữ liệu nhỏ liệt kê mọi tập vị trí, chuyển thành số nguyên để chuẩn hóa rồi gom tập. Miền lớn có công thức đếm mọi dãy con chuẩn phân biệt không giới hạn độ dài, trường hợp chỉ có một xâu đủ độ dài, và digit DP trên hậu tố sau tiền tố chung cho miền hẹp. Cách miền hẹp tham chiếu không tăng từng số hoặc tái sử dụng mảng vị trí như lời giải mẫu. Có số 0, nhiều chữ số lặp, A=B, số lớn hơn 64 bit, kết quả dài hơn 64 bit, tăng qua nhiều chữ số 9 và qua lũy thừa 10.

Validator còn được thử với đầu vào thiếu/thừa dòng, sai miền, sai ký tự, tọa độ không kề nhau, các số mũ nguyên tố không bằng nhau và dữ liệu số dài nằm ngoài miền hẹp. Checker được thử với dữ liệu đúng, khác khoảng trắng, sai đáp án, tràn độ dài, thiếu và thừa token. Mỗi bài có một lượt kiểm tra tên tệp nhập/xuất nguồn. Cấu trúc đề theo mẫu knapsack, quy tắc tiêu đề, nội dung lời giải và cấu hình điểm upload đều được đối chiếu.

## Kết quả

Kết quả cụ thể và thời gian từng bài nằm trong `results.json`. Tổng cộng 130 test chính thức, 560 trường hợp nhỏ độc lập, 53 đầu vào sai bị loại, 85 tình huống checker và bảy lượt nhập/xuất tệp đã đạt. Toàn bộ 260 mục hash khớp.

File input lớn nhất là **841124 byte**, thuộc ROBOT. Toàn bộ 130 input không vượt 1.000.000 byte. Thời gian đo phụ thuộc máy chạy; các lượt lời giải mẫu đều dùng đúng giới hạn upload trong cấu hình bài.
