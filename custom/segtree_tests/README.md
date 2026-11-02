# Kiểm thử nhóm segment tree cơ bản

| Mã bài | Nội dung |
| --- | --- |
| segtree020 | Min, max và độ chênh lệch nhiệt độ |
| segtree010 | Đảo trạng thái một đèn, đếm đèn sáng |
| segtree050 | Đếm số chẵn và số lẻ |
| segtree060 | Giá trị lớn nhất và số lần xuất hiện |
| segtree082 | Dấu của tích |
| segtree090 | Số cụm màu liên tiếp |

Từ thư mục gốc dự án, chạy toàn bộ nhóm:

```sh
python3 custom/segtree_tests/check.py
```

Hoặc chạy riêng một bài:

```sh
python3 custom/segtree090/tests/check.py
```

Khi chủ động thay đổi bộ sinh hoặc đáp án chuẩn, dùng `--update-hashes` để cập nhật `hash.json`. Lần chạy thông thường chỉ đối chiếu hash và báo lỗi nếu khác.

Quy trình gọi riêng các bước của `Problem`, không gọi `--dev`, `--test` hoặc xuất HTML. Không cần thư viện xuất HTML. Các chương trình C++ được biên dịch bằng cấu hình của dự án; thư viện `testlib.h` và bộ sinh số ngẫu nhiên có sẵn trong `common/`.

Mỗi bài có 36 test: 2 ví dụ, 12 trường hợp biên, 8 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Có test với $N=Q=200000$, đoạn một phần tử, đoạn toàn dãy, kích thước không phải lũy thừa của hai, truy vấn không cập nhật và cập nhật không truy vấn. Các trường hợp chuyên biệt bao gồm số âm, số 0, cực trị trùng nhau, cập nhật cùng giá trị, đảo đèn lặp lại và nhập/tách cụm màu.

Ngoài kiểm tra đầu vào và chạy lời giải qua checker trên mọi test, quy trình còn:

- Đối chiếu toàn bộ đáp án bằng lời giải độc lập trong `oracle.cpp`: chia căn cho min/max và cực đại kèm số lần, Fenwick đếm trạng thái cho các bài còn lại. Bài màu dùng công thức $1+$ số cặp ô kề nhau khác màu trong đoạn.
- Đối chiếu các test nhỏ bằng cách duyệt trực tiếp mảng.
- Duyệt mọi mảng độ dài từ 1 đến 4 trên bảng giá trị nhỏ, thử cập nhật từng vị trí và truy vấn mọi đoạn; thêm 150 test ngẫu nhiên mỗi bài. Tổng cộng 1.530 trường hợp bổ sung cho cả nhóm.
- Kiểm tra verifier từ chối dữ liệu vượt giới hạn, sai chỉ số, đảo ngược đoạn, thiếu hoặc thừa dữ liệu.
- Kiểm tra checker chấp nhận đáp án đúng với khoảng trắng khác nhau, từ chối đáp án sai, thiếu, thừa và không đúng định dạng; bao gồm trường hợp không có đầu ra.
- Đối chiếu cấu trúc đề, bảng subtask khi có, nội dung ví dụ, tính tái lập của bộ sinh và `hash.json`.

Các tệp `params.h`, chương trình đã biên dịch và thư mục `in/`, `out/` là sản phẩm sinh tự động. Mã nguồn bộ sinh, ví dụ, lời giải và `hash.json` được lưu để tái tạo bộ test.

Các bộ kiểm thử dùng `CASE_KINDS` để tách mã bài hiện tại khỏi định danh kịch bản kiểm thử. Khi đổi mã bài theo nhóm kiến thức, các định danh kịch bản, seed của bộ sinh và hash dữ liệu được giữ ổn định. Các bảng và lệnh bên dưới sử dụng mã bài hiện tại.

## Nhóm truy vấn tĩnh, tổng, cực tiểu, GCD và LCM

| Mã bài | Nội dung |
| --- | --- |
| segtree000 | Tổng lượng mưa trên dãy cố định |
| segtree002 | Đếm vị trí có giá trị ít nhất bằng ngưỡng cố định |
| segtree011 | Gán lượng hàng tại một kho, truy vấn tổng đoạn |
| segtree021 | Giá trị nhỏ nhất và chỉ số xuất hiện đầu tiên |
| segtree030 | GCD số kẹo trong các bao |
| segtree031 | LCM các chu kỳ là ước dương của 2520 |

Chạy riêng nhóm này từ thư mục gốc:

```sh
python3 custom/segtree_tests/check_foundations.py
```

Chạy một bài, hoặc cập nhật hash sau khi chủ động sửa dữ liệu:

```sh
python3 custom/segtree031/tests/check.py
python3 custom/segtree_tests/check_foundations.py --update-hashes
```

Nhóm này cũng có 36 test mỗi bài, với giới hạn $N,Q\le200000$, và không xuất HTML. Hai bài `000`, `002` chỉ có truy vấn, không có thao tác cập nhật. Bốn bài còn lại có cả test chỉ truy vấn lẫn test chỉ cập nhật.

`oracle_foundations.cpp` đối chiếu toàn bộ đáp án bằng tổng tiền tố cho hai bài tĩnh, Fenwick cho tổng động, chia căn cho cực tiểu kèm chỉ số và GCD. Với bài LCM, lời giải độc lập dùng Fenwick đếm các phần tử chia hết cho từng lũy thừa nguyên tố $2,4,8,3,9,5,7$, rồi dựng lại LCM từ số mũ lớn nhất.

Ngoài 216 test chính, quy trình kiểm tra thêm 2.100 trường hợp bằng duyệt trực tiếp mảng: duyệt mọi mảng độ dài từ 1 đến 4 trên bảng ba giá trị, thử mọi đoạn và các cập nhật đơn; bài ngưỡng thử thêm năm ngưỡng cho mỗi mảng; sau đó thêm 150 test ngẫu nhiên mỗi bài. Các kiểm tra đề, ví dụ, checker, verifier, tính tái lập và hash được thực hiện tương tự nhóm trước. Verifier bài `031` còn phải từ chối các số nằm trong $[1,2520]$ nhưng không là ước của 2520, cả ở dữ liệu ban đầu và thao tác cập nhật.

## Nhóm bài còn lại trong các dải 000–039

| Mã bài | Nội dung |
| --- | --- |
| segtree001 | Min, max và độ chênh lệch trên dãy cố định |
| segtree012 | Tổng thu và tổng chi không âm |
| segtree013 | Tổng đan dấu, bắt đầu bằng dấu cộng tại đầu đoạn |
| segtree022 | Tổng hai giá trị lớn nhất ở hai vị trí khác nhau |
| segtree023 | Kiểm tra mọi số đo trong đoạn có thuộc hai biên cho phép |
| segtree032 | GCD các chênh lệch tuyệt đối giữa hai phần tử kề nhau |

Chạy toàn bộ nhóm hoặc chạy riêng một bài:

```sh
python3 custom/segtree_tests/check_remaining.py
python3 custom/segtree032/tests/check.py
```

Dùng `--update-hashes` khi chủ động cập nhật dữ liệu hoặc đáp án chuẩn. Mỗi bài có 36 test theo cùng cấu hình 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên, 6 lớn. Không xuất HTML; các đề mới không có mục Subtask theo quy tắc dự án hiện tại. Hàm kiểm tra cấu trúc đề dùng `with_subtask=False` cho nhóm mới và vẫn hỗ trợ các đề có Subtask đã tạo trước đây.

Toàn bộ đáp án được đối chiếu bằng `oracle_remaining.cpp`: hai tổng Fenwick cho thu/chi, tổng Fenwick có dấu theo chỉ số cho tổng đan dấu, chia căn cho các bài min/max và hai giá trị lớn nhất. Với bài chênh lệch, lời giải độc lập không duy trì mảng hiệu: mỗi khối lưu GCD của khoảng cách từ các giá trị tới phần tử đầu khối. Khi truy vấn, ghép về phần tử đầu đoạn để tính $\gcd(|A_i-A_l|)$, bằng GCD của các chênh lệch kề nhau nhờ tính chất tổng và hiệu của các bội của GCD. Cập nhật chỉ dựng lại một khối.

Ngoài 216 test chính, nhóm có 1.617 trường hợp đối chiếu trực tiếp bằng duyệt mảng. Các trường hợp vét cạn thử mọi mảng độ dài từ 1 đến 4 trên bảng $\{-1,0,1\}$, mọi đoạn và cập nhật đơn; riêng bài hai vận động viên bắt đầu từ độ dài 2. Bài kiểm định thử thêm nhiều cặp biên bằng nhau hoặc bao trùm các phần tử. Mỗi bài có thêm 150 test ngẫu nhiên.

Các test kiểm tra tổng 64 bit, số âm, số 0, phần tử cực đại trùng nhau, đoạn một phần tử nếu được phép, thay đổi đồng thời hai chênh lệch kề nhau, chênh lệch đạt $2\cdot10^9$, chỉ số ở hai đầu dãy, cập nhật giữ nguyên giá trị, chỉ truy vấn và chỉ cập nhật. Verifier phải từ chối đoạn một phần tử ở bài `022`, các biên đảo ngược hoặc thiếu ở bài `023`. Checker được thử với đáp án đúng, sai, thiếu, thừa, khoảng trắng khác nhau và đầu ra rỗng khi không có truy vấn.

## Nhóm XOR, ngoặc, tổng biến đổi và GCD với mốc

| Mã bài | Nội dung |
| --- | --- |
| segtree003 | XOR đoạn trên dãy cố định |
| segtree080 | Kiểm tra xâu ngoặc con đúng, không cập nhật |
| segtree070 | Tổng với trọng số bắt đầu lại từ 1 tại đầu đoạn |
| segtree071 | Tổng sai số bình phương so với mốc của mỗi truy vấn |
| segtree081 | Hiệu lớn nhất của cặp có thứ tự, bắt buộc chọn hai vị trí |
| segtree072 | Kích thước gói lớn nhất và tổng số gói |
| segtree034 | GCD các chênh lệch tuyệt đối so với mốc truy vấn |

Chạy cả nhóm hoặc một bài:

```sh
python3 custom/segtree_tests/check_extra.py
python3 custom/segtree080/tests/check.py
```

Có thể thêm `--update-hashes` khi chủ động thay đổi bộ sinh hoặc đáp án chuẩn. Mỗi bài có 36 test, bao gồm 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn. Các đề không có mục Subtask và không xuất HTML. Mọi `info.toml` của nhóm có các trường `[upload]` dùng chung khớp với `segtree012`: `group`, `classes`, `types`, `allowed_languages`, `partial`. Quy trình kiểm tra đối chiếu các giá trị này; thiết lập riêng từng bài như `time_limit` được giữ độc lập.

Toàn bộ 252 test chính được so sánh với `oracle_extra.cpp`. Lời giải độc lập dùng XOR tiền tố, tổng cân bằng ngoặc tiền tố kết hợp bảng thưa lấy min, Fenwick cho hai bài tổng, chia căn cho hiệu có thứ tự và GCD. Bài `034` dùng mảng chênh lệch kề nhau, cập nhật tối đa hai hiệu, rồi ghép GCD với chênh lệch của phần tử đầu đoạn so với mốc; cách này độc lập với nút lưu giá trị đại diện của lời giải segment tree.

Có thêm 2.278 trường hợp đối chiếu trực tiếp bằng duyệt mảng: mọi mảng ba giá trị dài từ 1 đến 4; bài cặp có thứ tự bắt đầu từ độ dài 2; bài ngoặc thử mọi xâu đến độ dài 8; mỗi bài thêm 150 trường hợp ngẫu nhiên. Các bài có mốc thử nhiều mốc cho từng đoạn. Một trường hợp XOR riêng kiểm tra kết quả $2^{30}-1$, lớn hơn giới hạn giá trị của một phần tử.

Các kiểm tra bổ sung bao gồm tổng 64 bit, hai biên số nguyên, đoạn một phần tử khi được phép, dãy giảm nghiêm ngặt với đáp án âm, ngoặc có tổng cân bằng bằng 0 nhưng tiền tố sai, GCD toàn số 0, mốc trùng phần tử, số gói vượt 32 bit, cập nhật lặp lại, chỉ cập nhật và chỉ truy vấn. Verifier và checker được thử bằng dữ liệu sai, thiếu, thừa và khoảng trắng đầu ra khác nhau; bộ sinh phải tái lập đúng mọi test và `hash.json` phải khớp toàn bộ tệp vào/ra.

## Sáu bài bù cho các dải mã cơ bản

| Mã bài | Nội dung hiện tại | Nhóm |
| --- | --- | --- |
| segtree004 | Chia thanh gỗ: GCD trên dãy cố định | 000–009, truy vấn tĩnh |
| segtree014 | Ghi nhận doanh số: cộng thêm tại một điểm, tính tổng đoạn | 010–019, tổng đoạn |
| segtree015 | Mã tổng kiểm tra: gán tại một điểm, tổng modulo cố định | 010–019, tổng đoạn |
| segtree025 | Bậc thang cao nhất: max chênh lệch kề nhau | 020–029, min/max |
| segtree033 | Chu kỳ vượt giới hạn: LCM có chặn | 030–039, GCD/LCM |
| segtree051 | Đếm bội số của một số cố định | 050–059, đếm điều kiện |

Các mã này được dùng cho bài mới sau khi những bài cũ đã chuyển sang 070–072 và 080–082. Chạy bộ kiểm thử riêng cho nội dung mới:

```sh
python3 custom/segtree_tests/check_refill.py
python3 custom/segtree033/tests/check.py
```

Dùng `--update-hashes` khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn. Các bộ kiểm thử cũ vẫn dùng `CASE_KINDS` và các mã đã chuyển; bộ mới dùng `oracle_refill.cpp`, nên không nhầm nội dung khi tái sử dụng mã bài.

Mỗi bài có 36 test: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên, 6 lớn; toàn nhóm có 216 test chính. Đề không có Subtask và không xuất HTML. Phần `[upload]` được sao chép từ cấu hình hiện tại của `segtree012`, bao gồm `time_limit = 1.0`; `timelimit` kiểm tra tại máy cũng là 1 giây. Bộ kiểm thử đối chiếu các trường upload dùng chung và xác nhận hai giới hạn thời gian khớp nhau.

Lời giải độc lập dùng bảng thưa cho GCD tĩnh, Fenwick cho tổng cộng thêm, tổng modulo và đếm bội. Bài bậc thang dùng chia căn lưu chênh lệch lớn nhất bên trong khối cùng hai độ cao ở đầu/cuối; cập nhật dựng lại một khối, truy vấn tự ghép bậc ở biên khối, thay vì cập nhật mảng hiệu như lời giải segment tree. Bài LCM dùng chia căn và phép nhân số nguyên 128 bit để đối chiếu cách chặn bằng phép chia của lời giải chính.

Ngoài test chính, có 2.826 trường hợp đối chiếu trực tiếp: mọi mảng độ dài 1–4 trên bảng ba giá trị, mọi đoạn, các cập nhật đơn và nhiều môđun/ngưỡng/số chia; mỗi bài thêm 150 test ngẫu nhiên. Bài LCM có thêm các ca đúng bằng ngưỡng, ngay dưới/trên ngưỡng, LCM thực vượt 64 bit, chu kỳ đơn lẻ vượt ngưỡng và cập nhật phục hồi từ vượt ngưỡng về hợp lệ. Bài bậc thang có thêm cập nhật tại biên khối.

Các kiểm tra còn bao gồm cộng dồn làm phần tử vượt $10^9$, tổng vượt 32 bit, cộng thêm 0, môđun bằng 1, số chia bằng 1, bội âm và số 0, chênh lệch đạt $2\cdot10^9$, chỉ cập nhật hoặc chỉ truy vấn. Verifier phải từ chối dữ liệu ngoài giới hạn, chỉ số sai, đoạn đảo ngược, thiếu hoặc thừa dữ liệu và tham số cố định không hợp lệ. Checker, cấu trúc đề, ví dụ, khả năng tái lập bộ sinh và toàn bộ hash cũng được kiểm tra.

## SEG1 — Tìm kiếm trực tiếp trên segment tree

| Mã bài | Nội dung | Phân nhóm |
| --- | --- | --- |
| segtree100 | Ô trống đầu tiên | Basic Tree Search |
| segtree110 | Hai vị trí ngoài cùng khác màu cho trước | First Position |
| segtree120 | Người đang hoạt động thứ k | K-th Element |
| segtree130 | Vị trí đầu tiên đạt mốc tổng tiền tố | Prefix Sum Search |
| segtree140 | Phân phòng tại khách sạn đầu tiên đủ sức chứa | First Value At Least X |
| segtree150 | Cửa hàng đầu tiên có giá trong ngân sách | First Value At Most X |
| segtree160 | Vị trí đầu tiên ngoài hai biên cho phép trong một đoạn | Search within Range |
| segtree170 | Đoạn xa nhất từ điểm xuất phát theo ngân sách | Subarray Search |
| segtree180 | Đoạn xa nhất thỏa tổng và max–min | Multi-Field Search |
| segtree190 | Tìm theo max, tổng tiền tố và số kho có hàng | Searching Mixed Problems |

Chạy cả nhóm hoặc một bài:

```sh
python3 custom/segtree_tests/check_search.py
python3 custom/segtree180/tests/check.py
```

Dùng `--update-hashes` khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn. Mỗi bài có 36 test theo cấu hình 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn; toàn nhóm có 360 test chính. Các đề không có Subtask và không xuất HTML. Các cấu hình `[upload]` được sao chép từ `segtree012`; giới hạn upload và giới hạn kiểm tra lời giải tại máy cùng là 1 giây.

Lời giải mẫu đều tìm kiếm trực tiếp bằng cách đi xuống cây, với cập nhật điểm khi có thay đổi. Các bài tìm tổng hoặc điểm cuối dùng dữ liệu không âm. Không dùng lazy hay tìm nhị phân kết hợp nhiều lần truy vấn đoạn. Các tìm kiếm thông thường trả về `-1` khi không tồn tại; hai bài tìm đoạn từ $l$ trả về $l-1$ khi đoạn rỗng. Bài khách sạn tự trừ số phòng sau mỗi lần phân phòng thành công và luôn in kết quả cho từng đoàn.

`oracle_search.cpp` đối chiếu toàn bộ test bằng cấu trúc độc lập: tập chỉ số ô trống; tập ranh giới giữa các cụm màu để tìm hai đầu khác màu; Fenwick và binary lifting cho thứ k, tổng tiền tố, ngân sách; chia căn cho tìm theo min/max trong đoạn và tìm đoạn với nhiều điều kiện. Bài điều phối phối hợp Fenwick với các khối lấy max.

Có thêm 2.525 trường hợp đối chiếu bằng duyệt trực tiếp: mọi mảng độ dài 1–4 trên bảng hai hoặc ba giá trị, nhiều truy vấn sau cập nhật từng vị trí, 150 test ngẫu nhiên mỗi bài, một ca phân phòng thất bại không đổi trạng thái và các ca cập nhật ở biên khối cho bốn bài cuối. Toàn bộ ví dụ cũng được đối chiếu với cả lời giải độc lập và duyệt trực tiếp.

Các test lớn kiểm tra trường hợp không có đáp án, đáp án ở đầu/cuối dãy, mọi giá trị bằng nhau, nhiều số 0, tổng vượt 32 bit, mốc đúng bằng tổng hoặc lớn hơn tổng, cạn phòng sau nhiều lượt, đoạn rỗng, chỉ cập nhật và chỉ tìm kiếm. Verifier được thử với loại thao tác, chỉ số, thứ k, mốc, ngân sách, chênh lệch và cặp biên không hợp lệ, cùng dữ liệu thiếu/thừa. Checker phải từ chối đáp án sai/thiếu/thừa và chấp nhận khoảng trắng đầu ra khác nhau. Bộ sinh phải tái lập toàn bộ test; cấu trúc đề, upload và mọi hash đều được đối chiếu.

## Mười bài SEG1 bổ sung

| Mã | Tên bài | Phân nhóm chính |
| --- | --- | --- |
| segtree101 | Số nhỏ nhất còn thiếu | Basic Tree Search |
| segtree111 | Chỗ đứt của dãy tăng | First Position |
| segtree121 | Món hàng thứ k theo giá | K-th Element |
| segtree131 | Điểm cân bằng dân cư | Prefix Sum Search |
| segtree151 | Ngày giá giảm trở lại | First Value At Most X |
| segtree161 | Bội số thứ k trong đoạn | Search within Range |
| segtree171 | Đoạn còn đủ ước chung | Subarray Search |
| segtree172 | Thu thập đủ tín hiệu | Subarray Search |
| segtree181 | Đủ kinh phí và nhân lực | Multi-Field Search |
| segtree191 | Vòng tròn loại người | Searching Mixed Problems |

Chạy cả nhóm hoặc một bài:

```sh
python3 custom/segtree_tests/check_search_more.py
python3 custom/segtree181/tests/check.py
```

Dùng `--update-hashes` khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn. Mỗi bài có 36 test: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn. Toàn nhóm có 360 test chính. Toàn bộ `[upload]` được sao chép từ `segtree000`, gồm `time_limit = 0.5`, `group = '04'`, lớp D, loại segtree, danh sách ngôn ngữ và chấm điểm từng phần. Giới hạn kiểm tra lời giải tại máy cũng là 0,5 giây. Không thêm Subtask và không xuất HTML.

Các lời giải mẫu đều đi xuống cây trực tiếp, chỉ cập nhật điểm. Bài MEX nhận tần suất ban đầu cho từng giá trị từ 0 đến N, in đáp án sau mọi thao tác và cho phép MEX bằng N+1. Bài bán hàng xóa một món sau khi tìm thành công; lần bán thất bại giữ nguyên tồn kho. Bài cân bằng dân cư trả về đầu đoạn nếu tổng bằng 0. Bài giá giảm dùng so sánh nghiêm ngặt. Bài GCD dùng điều kiện GCD không nhỏ hơn ngưỡng, trả về l−1 cho đoạn rỗng. Bài tín hiệu cho phép OR có thêm bit ngoài mặt nạ yêu cầu. Bài vòng tròn tính người bắt đầu là người thứ nhất, với số bước tới 10^18.

`oracle_search_more.cpp` dùng cấu trúc độc lập: Fenwick cho MEX, tồn kho theo giá, tổng dân số, đếm bội số và thứ hạng trong vòng tròn; tập có thứ tự của các chỗ giảm; chia căn cho tìm giá nhỏ hơn và ranh giới GCD/OR. Bài kinh phí và nhân lực tìm hai điểm đạt ngưỡng riêng bằng hai Fenwick rồi lấy điểm muộn hơn, độc lập với phép tìm kiếm đồng thời của lời giải mẫu.

Có thêm 3.951 trường hợp đối chiếu bằng duyệt trực tiếp. Bộ kiểm tra bổ sung duyệt mọi cấu hình nhỏ trên bảng giá trị hữu hạn, mọi đoạn và nhiều ngưỡng, kiểm tra lại sau cập nhật từng vị trí; liệt kê chuỗi bước đếm vòng tròn nhỏ và chạy 150 trường hợp ngẫu nhiên mỗi bài. Có các ca riêng tại vị trí 450/451 quanh biên khối của lời giải độc lập. Toàn bộ test chính đều được đối chiếu với lời giải độc lập; các ví dụ, test biên và test nhỏ còn được đối chiếu bằng duyệt trực tiếp.

Test lớn kiểm tra vị trí ở cuối, không có đáp án, mọi giá trị xuất hiện, tần suất lặp, tổng vượt 32 bit, nhiều số 0, cập nhật liên tiếp, tìm kiếm liên tiếp và bước đếm rất lớn. Verifier được thử bằng dữ liệu sai giới hạn, sai định dạng, thiếu/thừa token và xóa phần tử vắng mặt. Checker phải chấp nhận khác biệt khoảng trắng và từ chối đáp án sai/thiếu/thừa. Bộ kiểm tra cũng đối chiếu cấu trúc đề, hai ví dụ, upload, khả năng tái lập bộ sinh và toàn bộ hash.

## Mười bài SEG1 tiếp theo

| Mã | Tên bài | Phân nhóm chính |
| --- | --- | --- |
| segtree102 | Tín hiệu tương thích đầu tiên | Basic Tree Search |
| segtree112 | Trạm cứu hộ gần nhất | First Position |
| segtree122 | Khôi phục thứ tự xếp hàng | K-th Element |
| segtree132 | Chia đều ba chặng | Prefix Sum Search |
| segtree162 | Kiện hàng sai quy cách | Search within Range |
| segtree173 | Chu kỳ còn trong giới hạn | Subarray Search |
| segtree174 | Tuyến đường ít loại hàng | Subarray Search |
| segtree182 | Đủ tải và đạt độ phân giải | Multi-Field Search |
| segtree192 | Bãi đỗ xe vòng tròn | Searching Mixed Problems |
| segtree193 | Chọn hộp vừa nhất | Searching Mixed Problems |

Chạy cả nhóm hoặc một bài:

```sh
python3 custom/segtree_tests/check_search_next.py
python3 custom/segtree173/tests/check.py
```

Dùng `--update-hashes` khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn. Mỗi bài có 36 test: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn, tổng cộng 360 test chính. Toàn bộ `[upload]` được sao chép từ `segtree000`, gồm `time_limit = 0.5`, `group = '04'`, lớp D, loại segtree, danh sách ngôn ngữ và chấm điểm từng phần. Giới hạn kiểm tra lời giải tại máy cũng là 0,5 giây. Không thêm Subtask và không xuất HTML.

Các lời giải mẫu dùng tìm kiếm trực tiếp trên cây cùng cập nhật điểm. Bài 122 chỉ có đầu vào tĩnh, nhưng quá trình khôi phục tìm phần tử thứ k và xóa từng giá trị. Bài 132 in cặp nhỏ nhất theo thứ tự từ điển, xử lý riêng tổng bằng 0, yêu cầu ba đoạn không rỗng và kiểm tra đạt đúng tổng tiền tố. Bài 173 chặn LCM tại 10^18+1, kiểm tra trước khi nhân và cho phép một nút từng vượt giới hạn trở lại nhỏ sau cập nhật. Bài 174 dùng mặt nạ 26 bit. Bài 192 trả chỗ đã trống không làm đổi trạng thái. Bài 193 cho phép không có hộp ban đầu, giữ hộp rỗng và in sức chứa trước khi đặt món.

`oracle_search_next.cpp` dùng cấu trúc độc lập: chia căn với OR cho tương thích bit; tập có thứ tự cho trạm gần nhất và bãi xe; Fenwick cho khôi phục hoán vị và chia ba tổng; chia căn với GCD/LCM/mặt nạ cho ba bài tìm đoạn và kiện sai quy cách; multiset cho chọn hộp. Bài 182 tìm riêng vị trí đạt tổng bằng Fenwick và vị trí đạt GCD bằng chia căn rồi lấy vị trí muộn hơn. LCM của lời giải đối chiếu dùng phép nhân 128 bit, độc lập với phép kiểm tra chia trước khi nhân trong lời giải mẫu.

Có thêm 4.042 trường hợp đối chiếu bằng duyệt trực tiếp. Các kiểm tra bổ sung liệt kê mọi hoán vị độ dài 1–6 và tự tính số nghịch thế ban đầu; liệt kê mọi mảng nhỏ, các đoạn và nhiều ngưỡng rồi kiểm tra lại sau cập nhật. Bài 132 đối chiếu bằng cách thử mọi cặp vị trí cắt. Bài hộp mô phỏng trực tiếp từng hộp, bãi xe mô phỏng thứ tự vòng tròn, bài chuỗi dùng tập ký tự. Mỗi bài có thêm 150 trường hợp ngẫu nhiên; có ca biên khối 450/451 và các ca riêng về LCM lớn hơn 64 bit, ngưỡng bằng đúng LCM, giảm LCM sau cập nhật, tiền tố nhảy qua ngưỡng và cặp cắt nhỏ nhất khi có nhiều số 0.

Toàn bộ test chính được đối chiếu bằng lời giải độc lập; các ví dụ, test biên và test nhỏ còn được đối chiếu bằng duyệt trực tiếp. Các test lớn kiểm tra vị trí cuối, thất bại, tổng vượt 32 bit, bảng đủ 26 ký tự, vòng qua đầu bãi xe, sức chứa chuyển xuống 0, nhiều hộp cùng mức và chuỗi chỉ cập nhật hoặc chỉ tìm kiếm. Bộ kiểm tra thử verifier bằng dữ liệu sai giới hạn, thiếu/thừa token, ký tự sai và chuỗi sai độ dài; thử checker bằng đáp án sai/thiếu/thừa và khoảng trắng thay đổi; đồng thời đối chiếu cấu trúc đề, hai ví dụ, upload, khả năng tái lập bộ sinh và mọi hash.

## Tám bài bổ sung trong SEG100–SEG129

| Mã | Tên bài | Phân nhóm chính |
| --- | --- | --- |
| segtree103 | Giá trị phổ biến nhất | Basic Tree Search |
| segtree104 | Thiết bị thiếu tính năng | Basic Tree Search |
| segtree113 | Đỉnh núi đầu tiên | First Position |
| segtree114 | Tiền tố chung của hai bản ghi | First Position |
| segtree115 | Hai đầu bảng thành tích | First Position |
| segtree123 | Trung vị trên băng chuyền | K-th Element |
| segtree124 | Giá trị phân biệt thứ k | K-th Element |
| segtree125 | Ký tự thứ k trong văn bản nén | K-th Element |

Chạy cả nhóm hoặc một bài:

```sh
python3 custom/segtree_tests/check_search_early.py
python3 custom/segtree125/tests/check.py
```

Dùng `--update-hashes` khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn. Mỗi bài có 36 test: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn; tổng cộng 288 test chính. Toàn bộ `[upload]` tiếp tục được sao chép từ `segtree000`, gồm `time_limit = 0.5`, `group = '04'`, lớp D, loại segtree, danh sách ngôn ngữ và chấm điểm từng phần. Giới hạn kiểm tra lời giải tại máy cũng là 0,5 giây. Không thêm Subtask và không xuất HTML.

Các lời giải mẫu đều tìm kiếm trực tiếp trên cây và chỉ cập nhật điểm. Bài 103 ưu tiên giá trị nhỏ nhất khi tần suất hòa, trả về −1 cho đa tập rỗng. Bài 104 dùng AND để bỏ qua đoạn mà mọi thiết bị đều đủ yêu cầu. Bài 113 xét đỉnh nghiêm ngặt và cập nhật tối đa ba dấu hiệu; hai đầu không phải đỉnh. Bài 114 cập nhật một trong hai chuỗi, trả về độ dài tiền tố chung từ 0 đến N. Bài 115 tìm hai đầu cực đại bằng hai hướng đi xuống, hỗ trợ cả điểm âm. Bài 123 tìm trung vị dưới, kể cả cửa sổ chẵn và phần tử lặp. Bài 124 lưu dấu hiện diện thay vì tần suất thực. Bài 125 lưu độ dài 64 bit, giữ chỉ số của khối rỗng và khối kề nhau cùng ký tự, in ký tự cùng chỉ số khối và thứ tự nội bộ.

`oracle_search_early.cpp` đối chiếu bằng các cấu trúc độc lập: tập cặp (âm tần suất, giá trị) cho mode; chia khối AND cho thiết bị; tập có thứ tự các đỉnh hoặc vị trí khác nhau cho hai bài tiếp theo; map từ điểm tới tập vị trí cho hai đầu cực đại. Trung vị cửa sổ dùng hai multiset được cân bằng, độc lập với cây tần suất của lời giải mẫu. Hai bài cuối dùng Fenwick cho số giá trị hiện diện hoặc tổng độ dài, kết hợp tìm theo thứ hạng.

Có thêm 4.513 trường hợp đối chiếu bằng duyệt trực tiếp. Kiểm tra bổ sung liệt kê các mảng nhỏ và thao tác cập nhật từng vị trí, mọi cặp chuỗi nhị phân nhỏ, mọi cửa sổ trên các dãy ngắn và nhiều cấu hình khối nén gồm ký tự cùng độ dài 0–2. Mỗi bài có thêm 150 trường hợp ngẫu nhiên. Có ca tại biên khối 450/451, số lần lặp và tổng vượt 32 bit, thứ hạng đúng ranh giới hai khối cùng ký tự, các khối rỗng và thứ hạng vượt tổng. Bài trung vị có ca riêng cửa sổ chẵn để phân biệt trung vị dưới với trung vị trên.

Toàn bộ test chính được đối chiếu với lời giải độc lập; các ví dụ, test biên và test nhỏ còn được đối chiếu bằng duyệt trực tiếp hoặc sắp xếp từng cửa sổ. Verifier được thử với xóa giá trị vắng mặt, sai thứ hạng, sai giới hạn, chuỗi sai độ dài, ký tự sai và dữ liệu thiếu/thừa. Bài 125 có checker riêng so sánh đúng ký tự và các trường số; bộ kiểm tra sửa riêng từng trường để xác nhận checker từ chối đáp án sai, đồng thời kiểm tra thiếu/thừa và khoảng trắng. Cấu trúc đề, hai ví dụ, upload, khả năng tái lập bộ sinh và toàn bộ hash đều được đối chiếu.

## Năm bài SEG1: lịch hẹn và thứ hạng

| Mã | Tên bài | Phân nhóm chính |
| --- | --- | --- |
| segtree116 | Lịch hẹn bị chồng | First Position — TOP-A2ZNC92KAE |
| segtree126 | Cụm màu thứ k | K-th Element — TOP-HVXB701KRY |
| segtree127 | Số còn thiếu thứ k | K-th Element — TOP-HVXB701KRY |
| segtree128 | Hàng chờ luân chuyển | K-th Element — TOP-HVXB701KRY |
| segtree129 | Cặp thi đấu thứ k | K-th Element — TOP-HVXB701KRY |

Chạy cả nhóm hoặc một bài:

```sh
python3 custom/segtree_tests/check_search_five.py
python3 custom/segtree129/tests/check.py
```

Dùng `--update-hashes` khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn. Mỗi bài có 36 test: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn; tổng cộng 180 test chính. `[upload]` lấy từ `segtree000`, riêng `types` được đổi thành `['ds_segment_tree']` theo yêu cầu; các trường còn lại gồm `time_limit = 0.5`, `group = '04'`, lớp D, danh sách ngôn ngữ và chấm điểm từng phần. Giới hạn kiểm tra lời giải tại máy cũng là 0,5 giây. Không thêm Subtask và không xuất HTML.

Các lời giải mẫu tìm kiếm trực tiếp trên cây và chỉ cập nhật điểm. Bài 116 đánh dấu cặp cuộc hẹn liên tiếp bị chồng bằng so sánh nghiêm ngặt; thời điểm bắt đầu cố định, cập nhật cuộc hẹn cuối không đổi dấu nào, và N=1 luôn trả về −1. Bài 126 chọn dấu bắt đầu cụm thứ k, tính lại tối đa hai dấu khi đổi màu. Bài 127 lưu dấu tần suất bằng 0, giữ tần suất thật bằng số nguyên 64 bit, chỉ xét miền 1..M và cho phép tần suất tăng quá 10^9. Bài 128 dành N+Q vị trí, bỏ dấu ở vị trí cũ rồi đưa người xuống vị trí mới; luôn còn đúng N người, kể cả khi chuyển người vốn đã ở cuối. Bài 129 dùng số cặp của mỗi câu lạc bộ làm trọng số, tìm thứ hạng nội bộ rồi dùng công thức tổng để xác định hai thành viên; tổng số trận tối đa là 9.999.000.000.000, và truy vấn không xóa trận.

`oracle_search_five.cpp` dùng tập có thứ tự cho các cặp lịch hẹn bị chồng và Fenwick cho các bài thứ hạng. Cặp thi đấu được xác định bằng nghịch đảo số tam giác qua căn bậc hai rồi hiệu chỉnh bằng số nguyên, độc lập với tìm nhị phân trong lời giải mẫu. Toàn bộ 180 test chính được đối chiếu với lời giải độc lập; hai ví dụ, test biên và test nhỏ còn được đối chiếu bằng duyệt trực tiếp.

Có thêm 2.341 trường hợp đối chiếu bằng duyệt trực tiếp: 544 cho lịch hẹn, 544 cho cụm màu, 301 cho số còn thiếu, 406 cho hàng chờ và 546 cho cặp thi đấu. Các kiểm tra liệt kê mọi cấu hình nhỏ, nhiều cập nhật từng vị trí, mọi thứ hạng phù hợp và 180 trường hợp ngẫu nhiên mỗi bài. Hàng chờ được mô phỏng bằng danh sách, gồm mọi chuỗi ba lần chuyển cho N từ 1 đến 5 và chuyển lặp lại cùng một người. Cặp thi đấu được đối chiếu bằng duyệt các nhóm thành viên đầu tiên; với một câu lạc bộ có 2–25 thành viên, kiểm tra mọi trận và một thứ hạng thất bại. Có thêm ca câu lạc bộ 10.000 thành viên tại ranh giới nhóm, thứ hạng 2.147.483.648, tổng chính xác, tổng+1 và 10^18.

Các test lớn kiểm tra đáp án ở cuối, trường hợp không có đáp án, dãy đồng nhất, tần suất 0 hoặc lặp nhiều, cập nhật liên tiếp và tìm kiếm liên tiếp. Verifier được thử với 94 dữ liệu không hợp lệ: loại thao tác, chỉ số, màu, tần suất, số thành viên, thứ hạng sai giới hạn; thời điểm bắt đầu không tăng, thời điểm kết thúc trước khi bắt đầu; xóa số vắng mặt và dữ liệu thiếu/thừa. Checker phải chấp nhận khác biệt khoảng trắng, từ chối đáp án sai/thiếu/thừa và nhận ra từng trường số bị sửa, gồm cả bộ ba trận đấu. Bộ kiểm tra cũng đối chiếu cấu trúc đề, hai ví dụ, toàn bộ upload, khả năng tái lập mọi test sinh và 360 hash SHA-256.

## SEGTREE008 — Tự do cho đàn kiến

Bài thuộc Static Range Query (`TOP-FB61J3EYJR`), chỉ có truy vấn tĩnh, không cập nhật, không tìm kiếm vị trí trên cây và không lazy. Đầu vào giữ đúng thứ tự của đề được cung cấp: n trên dòng đầu, dãy sức mạnh trên dòng hai, m trên dòng ba rồi m cặp L R. Giới hạn n,m là 100.000, sức mạnh từ 1 đến 10^9. Ví dụ gốc và bốn đáp án 4,4,1,1 được giữ nguyên; có thêm ví dụ về GCD không xuất hiện và đoạn một phần tử. Đề không có Subtask, không xuất HTML.

Câu mô tả ban đầu ghi kiến i nhận điểm nếu s_i bị chia hết bởi s_j, ngược với ví dụ. Đề được chuẩn hóa theo ví dụ: kiến i nhận điểm nếu s_j chia hết cho s_i. Hai kiến cùng sức mạnh đều nhận điểm khi so với nhau; kiến được tự do khi sức mạnh bằng GCD của đoạn. Các truy vấn độc lập, không thực sự xóa kiến. Lưu ý này giải thích việc hiệu chỉnh nội dung nguồn, không phải thay đổi mẫu hay giới hạn.

Chạy toàn bộ kiểm tra:

```sh
python3 custom/segtree008/tests/check.py
# Chỉ dùng khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn:
python3 custom/segtree008/tests/check.py --update-hashes
```

Lời giải mẫu ghép GCD và số phần tử bằng GCD trong segment tree. `oracle_ants.cpp` dùng sparse table cho GCD và các vector vị trí xuất hiện để đếm bằng hai phép tìm nhị phân. Cấu trúc đối chiếu này độc lập với phép ghép số lượng của lời giải mẫu. Với dữ liệu nhỏ, `check_ants.py` mô phỏng từng lần so sánh giữa hai con kiến và tính điểm trực tiếp, không sử dụng nhận xét GCD.

Có 36 test chính: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn. Bộ sinh bao phủ n=1, đoạn một phần tử, toàn đoạn, đoạn đầu/cuối, số phần tử không phải lũy thừa của 2, mọi sức mạnh bằng nhau, GCD không xuất hiện, GCD xuất hiện nhiều lần, có sức mạnh 1, sức mạnh 10^9, số nguyên tố lớn và chuỗi lũy thừa. Sáu test lớn đạt m=100.000 và n=100.000 hoặc 99.999, gồm ca mọi kiến đều tự do và ca chỉ một giá trị bằng GCD ở giữa dãy.

Có thêm 1.570 trường hợp đối chiếu trực tiếp: mọi mảng độ dài 1–5 trên các giá trị 1,2,3,6 với mọi đoạn; 200 trường hợp ngẫu nhiên; 6 cấu hình riêng cho GCD vắng mặt, nhiều phần tử bằng GCD, hai đầu trùng nhau, toàn bộ bằng nhau và giá trị lớn. Verifier được thử bằng 18 dữ liệu sai về số lượng, giá trị, biên đoạn, thứ tự biên, định dạng và dữ liệu thiếu/thừa. Checker được thử với đáp án đúng, khác khoảng trắng, đáp án sai/thiếu/thừa. Quy trình đối chiếu hai ví dụ, cấu trúc đề, metadata, khả năng tái lập mọi test sinh và 72 hash SHA-256. `[upload]` lấy từ `segtree000`, riêng types là `['ds_segment_tree']`; giới hạn kiểm tra và upload đều là 0,5 giây.

## SEGTREE310 — Trọng lượng của đoạn

Bài thuộc SEG3 — Advanced Node Segment Tree, phân nhóm Maximum Subarray Sum (`TOP-8RN1DX07M4`, dải 310–319). Dãy không thay đổi, nhưng trọng tâm là thiết kế nút tổng/tiền tố/hậu tố/đoạn con tốt nhất. Đầu vào giữ nguyên thứ tự của đề được cung cấp: n, dãy a, m rồi m cặp u v. Giữ nguyên giới hạn n,m ≤ 50.000 và ví dụ gốc với đáp án 7,5,6. Giới hạn trị tuyệt đối của a_i được bổ sung là 10^9 theo trao đổi với người dùng. Đoạn con phải không rỗng, nên đoạn toàn âm trả về phần tử lớn nhất. Có thêm ví dụ toàn âm; không thêm Subtask và không xuất HTML.

Chạy toàn bộ kiểm tra:

```sh
python3 custom/segtree310/tests/check.py
# Chỉ dùng khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn:
python3 custom/segtree310/tests/check.py --update-hashes
```

Lời giải mẫu dùng segment tree dạng lặp với hai biến tích lũy để giữ thứ tự trái–phải. Nút rỗng có dấu hiệu riêng; giá trị 0 ở nút rỗng không được dùng như một đáp án hợp lệ cho đoạn thật. Các tổng dùng số nguyên 64 bit. `oracle_max_subarray.cpp` giải độc lập bằng chia để trị ngoại tuyến: truy vấn nằm trong một nửa được chuyển xuống đệ quy, truy vấn cắt điểm giữa được trả lời bằng các lượt quét Kadane từ hai phía và tổng qua ranh giới. Đối chiếu mọi test chính với cách giải này. Với dữ liệu nhỏ, `check_max_subarray.py` duyệt mọi đoạn con và cộng trực tiếp để tìm đáp án.

Có 36 test chính: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn. Bao phủ n=1, đoạn một phần tử, toàn đoạn, biên đầu/cuối, dãy không có độ dài là lũy thừa của 2, toàn âm, toàn dương, toàn 0, số âm/dương xen kẽ, nhiều đáp án bằng nhau và đáp án tốt nhất nằm hoàn toàn bên trong đoạn. Sáu test lớn đạt m=50.000 và n=50.000 hoặc 49.999. Ca toàn dương có tổng đúng bằng 50.000.000.000.000; ca toàn âm kiểm tra kết quả luôn âm. Có ca chỉ một phần tử dương giữa các số âm rất lớn và truy vấn lấy hoặc bỏ phần tử này.

Có thêm 4.113 trường hợp đối chiếu: mọi mảng độ dài 1–5 trên các giá trị −3,−1,0,1,3 với mọi đoạn; 200 trường hợp ngẫu nhiên; 8 cấu hình riêng cho toàn âm, toàn dương, toàn 0, giá trị biên và các truy vấn cần giữ đúng thứ tự ghép. Verifier được thử với 17 dữ liệu sai về số lượng, giá trị, biên và thứ tự đoạn, định dạng và dữ liệu thiếu/thừa. Checker được thử với đáp án đúng, khoảng trắng thay đổi và đáp án sai/thiếu/thừa. Quy trình đối chiếu cấu trúc đề theo mẫu knapsack, hai ví dụ, toàn bộ metadata, khả năng tái lập bộ sinh và 72 hash SHA-256. `[upload]` lấy từ `segtree000`, riêng types là `['ds_segment_tree']`; giới hạn kiểm tra và upload đều là 0,5 giây.

## SEGTREE311 — Trọng lượng sau cập nhật

Bài thuộc SEG3 — Advanced Node Segment Tree, phân nhóm Maximum Subarray Sum (`TOP-8RN1DX07M4`, dải 310–319), tiếp nối phiên bản tĩnh SEGTREE310. Giữ nguyên giới hạn n,m ≤ 200.000, −10^9 ≤ a_i,y ≤ 10^9 và ví dụ gốc với đáp án 6,4,−3. Chuẩn hóa phần mô tả dữ liệu: mỗi thao tác có ba số; `0 x y` gán a_x=y, còn `1 u v` hỏi tổng đoạn con lớn nhất không rỗng; chỉ thao tác loại 1 sinh dòng kết quả. Có thêm ví dụ toàn âm chuyển sang có số 0 và số dương sau cập nhật. Không thêm Subtask và không xuất HTML.

Chạy toàn bộ kiểm tra:

```sh
python3 custom/segtree311/tests/check.py
# Chỉ dùng khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn:
python3 custom/segtree311/tests/check.py --update-hashes
```

Lời giải mẫu dùng segment tree đệ quy, lưu tổng, tiền tố, hậu tố và đoạn con tốt nhất bằng số nguyên 64 bit. Mỗi cập nhật gán lại đủ bốn trường tại lá rồi ghép lại các tổ tiên. Truy vấn chỉ đi vào các đoạn có giao và ghép trái trước phải, không cần nút rỗng. `oracle_max_subarray_update.cpp` giải độc lập bằng chia căn: gán một phần tử thì dựng lại khối chứa nó bằng các lượt quét Kadane và tổng biên; truy vấn quét phần khối lẻ và dùng thông tin các khối nguyên. Kích thước khối là 700, có các kiểm tra riêng quanh biên khối. Với dữ liệu nhỏ, `check_max_subarray_update.py` mô phỏng cập nhật trên mảng rồi duyệt mọi đoạn con để tìm đáp án.

Có 36 test chính: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn. Bao phủ n=1, truy vấn một phần tử, toàn đoạn, biên đầu/cuối, dãy không có độ dài là lũy thừa của 2, toàn âm, toàn dương, toàn 0, dấu xen kẽ, cập nhật cùng vị trí nhiều lần, gán lại giá trị cũ và chuyển giữa số âm/0/dương. Có test chỉ cập nhật (đầu ra rỗng), chỉ truy vấn và nhiều cập nhật trước một truy vấn cuối. Sáu test lớn đạt m=200.000, n=200.000 hoặc 199.999. Ca toàn âm giữ mọi lần gán âm; ca toàn dương có đáp án chính xác 200.000.000.000.000.

Có thêm 4.116 trường hợp đối chiếu trực tiếp: mọi mảng độ dài 1–5 trên các giá trị −3,−1,0,1,3, truy vấn mọi đoạn trước và sau khi lần lượt cập nhật từng vị trí bằng từng giá trị trong bảng; 200 trường hợp ngẫu nhiên với các tỉ lệ cập nhật khác nhau; 8 cấu hình riêng về giá trị biên, dãy đồng nhất và thứ tự ghép; một ca chỉ cập nhật; một ca n=1; một ca cập nhật quanh các vị trí 699–702 và 1399–1403, kiểm tra cả đoạn ngắn và toàn dãy sau mỗi lần thay đổi.

Toàn bộ test chính được đối chiếu với lời giải chia căn; các ví dụ, test biên và test nhỏ còn được đối chiếu bằng duyệt mọi đoạn con. Verifier được thử với 23 dữ liệu sai về loại thao tác, số lượng, giá trị, chỉ số cập nhật, biên và thứ tự đoạn, định dạng và dữ liệu thiếu/thừa. Checker được thử với đáp án đúng, khác khoảng trắng và đáp án sai/thiếu/thừa, bao gồm test có đầu ra rỗng. Bộ kiểm tra xác nhận số dòng đầu ra đúng bằng số thao tác loại 1, cấu trúc đề theo mẫu knapsack, hai ví dụ, metadata, khả năng tái lập mọi test sinh và 72 hash SHA-256. `[upload]` lấy từ `segtree000`, riêng types là `['ds_segment_tree']`; giới hạn kiểm tra và upload đều là 0,5 giây.

## SEGTREE073 — Cân bằng đoạn

Bài thuộc SEG0, phân nhóm Multi-Aggregate Query (`TOP-BSQJMN7ST3`, dải 070–079). Mã 073 được chọn sau các bài 070–072 đã có. Trọng tâm là kết hợp giá trị lớn nhất, tổng và số lượng phần tử chẵn/lẻ để tính đáp án; số trường trong nút không phải lý do chuyển sang nhóm 060–069. Chỉ cần cập nhật điểm và truy vấn đoạn, không lazy và không tìm kiếm vị trí trên cây.

Giữ nguyên giới hạn N,Q ≤ 500.000, giá trị 1..10^9 và ví dụ gốc với đáp án 1,0. Mô tả làm rõ thao tác tăng chỉ áp dụng cho chỉ số trong đoạn đang xét; truy vấn loại 2 không thay đổi dãy. Ví dụ bổ sung hỏi lặp lại cùng đoạn để thể hiện tính độc lập, sau đó cập nhật làm giá trị lớn nhất đổi tính chẵn/lẻ. Không thêm Subtask và không xuất HTML.

Chạy toàn bộ kiểm tra:

```sh
python3 custom/segtree073/tests/check.py
# Chỉ dùng khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn:
python3 custom/segtree073/tests/check.py --update-hashes
```

Lời giải mẫu dùng segment tree lưu tổng S, giá trị lớn nhất M và số phần tử lẻ. Đáp án là (kM−S+C)/2, với C là số phần tử khác tính chẵn/lẻ với M. `oracle_equalize.cpp` dùng hai Fenwick cho tổng floor(A_i/2) và số phần tử lẻ, kết hợp chia căn để lấy max; tính chi phí bằng công thức riêng tùy max chẵn hay lẻ. Khối lấy max được dựng lại bằng duyệt khi cập nhật, độc lập với phép ghép cây của lời giải mẫu.

Với dữ liệu nhỏ, `check_equalize.py` mô phỏng các lần gán trực tiếp, thử các giá trị đích từ max đến max+2 và dùng quy hoạch động đổi tiền bằng bước 1,2 cho từng phần tử. Với chênh lệch lớn, tính riêng số bước cho từng phần tử rồi cộng, không dùng công thức gộp của lời giải mẫu. Chỉ cần ba giá trị đích này vì tăng đích thêm 2 làm chi phí của mỗi phần tử tăng đúng 1. Bộ đối chiếu không thay đổi dãy khi tính đáp án loại 2.

Có 36 test chính: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn. Bao phủ N=1, đoạn một phần tử, toàn đoạn, biên đầu/cuối, độ dài không phải lũy thừa của 2, toàn bộ bằng nhau, toàn lẻ, toàn chẵn, hai tính chẵn/lẻ xen kẽ, giá trị 1 và 10^9, cập nhật lặp hoặc gán lại giá trị cũ. Có test chỉ truy vấn, chỉ cập nhật với đầu ra rỗng, và nhiều cập nhật trước một truy vấn cuối. Sáu test lớn có Q=500.000 và N=500.000 hoặc 499.999. Một ca đồng nhất giữ đáp án 0; một ca có phần tử đầu bằng 10^9, các phần tử khác bằng 1, cho đáp án chính xác 249.999.500.000.000. Một ca thay đổi liên tiếp cực đại giữa 999.999.999 và 1.000.000.000 để kiểm tra hiệu chỉnh chẵn/lẻ.

Có thêm 1.574 trường hợp đối chiếu: mọi mảng độ dài 1–5 trên các giá trị 1,2,3,4 với mọi đoạn, hỏi lặp lại và kiểm tra sau khi cập nhật từng vị trí; 200 trường hợp ngẫu nhiên với tỉ lệ cập nhật khác nhau; 9 cấu hình riêng cho làm tròn, giá trị biên và cực đại đổi tính chẵn/lẻ; một ca cập nhật quanh vị trí 699–702 và 1399–1403. Verifier được thử với 24 dữ liệu sai về loại truy vấn, số lượng, giá trị, chỉ số, biên đoạn, định dạng và dữ liệu thiếu/thừa. Checker được thử với đáp án đúng, khác khoảng trắng và đáp án sai/thiếu/thừa, gồm cả trường hợp không có dòng kết quả. Quy trình đối chiếu mọi test chính với lời giải độc lập, đối chiếu ví dụ/test biên/test nhỏ bằng cách tính trực tiếp, xác nhận số dòng kết quả, cấu trúc đề theo mẫu knapsack, hai ví dụ, metadata, khả năng tái lập bộ sinh và 72 hash SHA-256. `[upload]` lấy từ `segtree000`, riêng types là `['ds_segment_tree']`; giới hạn kiểm tra và upload đều là 0,5 giây.

## SEGTREE220 — Cộng đoạn và lấy lớn nhất

Bài thuộc SEG2 — Lazy Segment Tree, phân nhóm Range Add - Range Min-Max (`TOP-FD439S2HWB`, dải 220–229). Giữ nguyên giới hạn n,m ≤ 100.000, |a_i|,|k| ≤ 10.000 và ví dụ gốc với đáp án 4. Đề làm rõ k có thể âm hoặc bằng 0, giới hạn a_i chỉ áp dụng ban đầu và chỉ truy vấn loại 1 sinh kết quả. Có thêm ví dụ toàn âm và các cập nhật âm/dương. Không thêm Subtask và không xuất HTML.

Chạy toàn bộ kiểm tra:

```sh
python3 custom/segtree220/tests/check.py
# Chỉ dùng khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn:
python3 custom/segtree220/tests/check.py --update-hashes
```

Lời giải mẫu dùng lazy segment tree, mỗi nút lưu max và lượng cộng đang chờ truyền xuống. Truy vấn chỉ đi vào các đoạn có giao để không lấy 0 làm giá trị lớn nhất của đoạn rỗng khi dữ liệu toàn âm. `oracle_range_add_max.cpp` giải độc lập bằng chia căn với khối 450 phần tử: cộng khối nguyên bằng độ lệch chung, cộng một phần khối vào mảng cơ sở rồi dựng lại max khối. Với dữ liệu nhỏ, `check_range_add_max.py` cập nhật trực tiếp từng phần tử và lấy max trên đoạn.

Có 36 test chính: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn. Bao phủ n=1, đoạn một phần tử, toàn đoạn, đầu/cuối dãy, kích thước không là lũy thừa của 2, toàn âm, toàn dương, toàn 0, số âm/dương xen kẽ, cộng 0, hai lần cộng triệt tiêu, cập nhật và truy vấn lồng nhau. Có test chỉ cập nhật (đầu ra rỗng), chỉ truy vấn và nhiều cập nhật trước một truy vấn cuối. Sáu test lớn có m=100.000, n=100.000 hoặc 99.999. Hai ca cộng toàn dãy 99.999 lần trước khi hỏi cho kết quả chính xác 1.000.000.000 và −1.000.000.000; một ca cộng toàn dãy rồi truy vấn các đoạn nhỏ để buộc đẩy cập nhật chờ.

Có thêm 1.155 trường hợp đối chiếu trực tiếp: 363 mảng độ dài 1–5 trên các giá trị −2,0,3, hỏi mọi đoạn trước và sau mỗi lần cộng lên từng đoạn; 584 cặp cập nhật trên mọi cặp đoạn với lượng cộng ±1 khi n=1–4, bao gồm đoạn rời nhau, chồng nhau và lồng nhau; 200 trường hợp ngẫu nhiên với các tỉ lệ cập nhật khác nhau; 7 cấu hình riêng về giá trị biên, dãy đồng nhất và dấu xen kẽ; một ca tại các biên khối 450/451 và 899/900/901. Mỗi ví dụ, test biên và test nhỏ còn được đối chiếu trực tiếp; mọi test chính được đối chiếu với lời giải chia căn.

Verifier được thử bằng dữ liệu sai về loại thao tác, số lượng, giá trị ban đầu, lượng cộng, biên đoạn và định dạng, bao gồm thiếu/thừa số ở hai loại thao tác có độ dài khác nhau. Checker được thử với đáp án đúng, khác khoảng trắng và đáp án sai/thiếu/thừa, gồm trường hợp không có dòng kết quả. Bộ kiểm tra xác nhận số dòng kết quả đúng bằng số thao tác loại 1, cấu trúc đề theo mẫu knapsack, hai ví dụ, metadata, khả năng tái lập bộ sinh và 72 hash SHA-256. `[upload]` lấy từ `segtree000`, riêng types là `['ds_segment_tree']`; giới hạn kiểm tra và upload đều là 0,5 giây.

## Sáu bài SEG200–SEG205 — Lazy cơ bản, hỏi một vị trí

| Mã | Tên bài | Nhãn gộp | Nhãn rỗng |
| --- | --- | --- | --- |
| segtree200 | Tiền thưởng đồng loạt | Tổng hai lượng cộng | 0 |
| segtree201 | Sơn lại các ô | Lần gán mới thay lần gán cũ | −1, khác màu 0 hợp lệ |
| segtree202 | Mức hỗ trợ tối thiểu | Max của hai ngưỡng | 0 |
| segtree203 | Giới hạn hạn mức | Min của hai ngưỡng | 1.000.000.001 |
| segtree204 | Rút gọn các con số | GCD của hai nhãn | 0 |
| segtree205 | Đổi nhãn ba màu | Hợp thành hoán vị: mới sau cũ | Hoán vị đồng nhất |

Cả sáu bài thuộc Basic Lazy Propagation (`TOP-001EY9JH9S`, dải 200–209). Chỉ có cập nhật đoạn và hỏi một vị trí; trọng tâm là nhãn, phép ghép nhãn, phần tử đồng nhất và bước đẩy trước khi đi xuống. Không truy vấn tổng hay min/max đoạn. Giới hạn chung N,Q ≤ 200.000. Bài 200 có số dư ban đầu và lượng cộng trong −10^9..10^9; các cập nhật có thể đưa số dư vượt 32 bit. Bài 201–203 dùng giá trị 0..10^9; bài 204 dùng giá trị dương 1..10^9; bài 205 dùng đúng ba màu 1,2,3. Các phép đổi màu diễn ra đồng thời, cho phép đổi một màu với chính nó.

Chạy cả nhóm hoặc một bài:

```sh
python3 custom/segtree_tests/check_lazy_basic.py
python3 custom/segtree205/tests/check.py
```

Dùng `--update-hashes` khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn. Mỗi bài có 36 test: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn; toàn nhóm có 216 test chính. Đề theo cấu trúc knapsack, có ít nhất hai ví dụ, không thêm Subtask và không xuất HTML. `[upload]` lấy từ `segtree000`, riêng types là `['ds_segment_tree']`; giới hạn kiểm tra và upload đều là 0,5 giây.

Lời giải mẫu giữ riêng dãy ban đầu, chỉ lưu nhãn trên segment tree. Cập nhật phủ toàn bộ nút ghép nhãn mới vào sau nhãn cũ; trước khi cập nhật một phần hoặc hỏi xuống con, đẩy nhãn cha xuống cả hai con rồi xóa nhãn cha. Đến lá thì áp dụng nhãn lên giá trị ban đầu. Quy tắc này xử lý thống nhất cả các phép không giao hoán là gán màu và hợp thành hoán vị; các phép max/min/GCD được thực hiện tại lá mà không cần thông tin gộp của đoạn.

`oracle_lazy_basic.cpp` dùng các cấu trúc độc lập: Fenwick trên dãy hiệu cho cộng đoạn/hỏi điểm; map các đoạn có cùng giá trị cho sơn màu, tách hai đầu rồi ghi đè đoạn; chia căn với khối 450 phần tử cho max, min và GCD. Ba phép sau giao hoán nên khối nguyên gộp nhãn, khối lẻ cập nhật mảng cơ sở. Bài ba màu dùng hoán vị trên khối nguyên; khi đổi một phần khối, áp dụng hết hoán vị khối vào mảng rồi đổi trực tiếp các ô được chọn. Mọi test chính được đối chiếu với lời giải độc lập; các ví dụ, test biên và test nhỏ còn được đối chiếu bằng mô phỏng từng phần tử.

Bộ kiểm tra bổ sung duyệt mọi mảng độ dài 1–4 trên bảng ba giá trị, hỏi mọi vị trí trước và sau khi cập nhật từng đoạn với nhiều nhãn. Kiểm tra mọi cặp trong 12 cập nhật trên các đoạn toàn phần, một điểm và hai đoạn giao nhau; thêm 200 trường hợp ngẫu nhiên mỗi bài, ca quanh biên khối 449/450/451 và 899/900/901, cùng ca riêng về nhãn rỗng và cực trị. Bài đổi màu có thêm mọi chuỗi độ dài 5 trên ba phép đổi cặp màu khác nhau, tổng cộng 243 chuỗi, trước khi hỏi cả ba màu ban đầu. Tổng số trường hợp bổ sung là 3.039: 466 cho mỗi bài 200–204 và 709 cho bài 205.

Test lớn có N,Q bằng 200.000, hoặc N=199.999; cập nhật toàn dãy rồi hỏi cuối dãy, cập nhật lồng nhau, chỉ hỏi, chỉ cập nhật và nhiều cập nhật trước một câu hỏi cuối. Bài 200 có kết quả đúng bằng 200.000.000.000.000. Bài 201 có gán màu 0 trên toàn dãy rồi ghi đè đoạn nhỏ. Bài 205 có các phép đổi không giao hoán và phép đổi đồng nhất. Kiểm tra verifier với dữ liệu sai loại thao tác, số lượng, chỉ số, thứ tự đoạn, giá trị, màu, độ dài thao tác và dữ liệu thiếu/thừa; checker phải chấp nhận thay đổi khoảng trắng và từ chối đáp án sai/thiếu/thừa, kể cả đầu ra rỗng. Quy trình xác nhận số dòng kết quả bằng số thao tác loại 2, metadata, hai ví dụ, khả năng tái lập mọi test sinh và 432 hash SHA-256.

## SEGTREE005 — Cực đại sau các phép cộng

Bài thuộc SEG0, Static Range Query (`TOP-FB61J3EYJR`, dải 000–009). Toàn bộ phép cộng diễn ra trước mọi câu hỏi; lời giải mẫu tiền xử lý bằng mảng hiệu rồi dựng segment tree max kèm số lần xuất hiện. Trong giai đoạn truy vấn, dãy cố định và cây không cập nhật. Không cần lazy hoặc tìm kiếm vị trí trên cây.

Giữ nguyên ví dụ gốc với đáp án 3,1. Nâng n,m,q từ 50.000 lên 200.000, đặt 1 ≤ k ≤ 10^9 và thay giới hạn giá trị sau cập nhật từ 2^31−1 bằng cận 2·10^14 suy ra từ m và k. Thống nhất ký hiệu q cho số câu hỏi thay cho việc dùng cả p và q trong nguồn. Có thêm ví dụ về phần tử không được cộng vẫn bằng 0, hai cực đại rời nhau và số lần xuất hiện trên đoạn toàn 0. Không thêm Subtask và không xuất HTML.

Chạy toàn bộ kiểm tra:

```sh
python3 custom/segtree005/tests/check.py
# Chỉ dùng khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn:
python3 custom/segtree005/tests/check.py --update-hashes
```

Lời giải mẫu dùng mảng hiệu 64 bit, dựng cây có nút (maximum,count), ghép count khi hai maximum bằng nhau. Nút rỗng hoặc lá đệm có count=0; vị trí thật chưa được cộng có giá trị 0 nhưng count=1. `oracle_static_max_count.cpp` dựng dãy cuối bằng cách sắp xếp các sự kiện ở hai đầu đoạn rồi quét, độc lập với mảng hiệu của lời giải mẫu. Sau đó dùng sparse table cho max và vector cặp (giá trị,vị trí) đã sắp xếp để đếm bằng hai phép tìm nhị phân. Với dữ liệu nhỏ, `check_static_max_count.py` thực hiện từng phép cộng trên từng phần tử rồi duyệt đoạn để tìm max và đếm trực tiếp.

Có 36 test chính: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn. Bao phủ n=1, câu hỏi một phần tử, toàn dãy, hai đầu đoạn, kích thước không là lũy thừa của 2, phép cộng kết thúc tại n, đoạn cộng rời nhau, chồng nhau và lồng nhau, mọi phần tử cùng cực đại, các cực đại rời nhau, vị trí không được cộng và giá trị vượt 32 bit. Sáu test lớn có m=q=200.000, n=200.000 hoặc 199.999. Các đáp án đầu tiên được xác nhận riêng gồm: (200.000.000.000.000,200.000) khi toàn dãy đồng nhất; (0,100.000) khi hỏi nửa dãy chưa được cộng; (1,200.000) khi mỗi vị trí được cộng 1 đúng một lần; (100.000.000.000.000,2) khi chỉ hai vị trí rời nhau cùng cực đại.

Có thêm 1.761 trường hợp đối chiếu trực tiếp: mọi một hoặc hai phép cộng trên mọi đoạn với k=1,2 khi n=1–5, hỏi mọi đoạn; 200 trường hợp ngẫu nhiên; 7 cấu hình riêng cho giá trị lớn, cực đại ở đầu/cuối, đoạn toàn 0, cực đại lặp và ranh giới 256/257 trên dãy 513 phần tử. Toàn bộ test chính được đối chiếu với lời giải độc lập; ví dụ, test biên và test nhỏ còn được đối chiếu bằng mô phỏng trực tiếp. Verifier được thử với 21 dữ liệu sai về n,m,q, lượng cộng không dương hoặc vượt giới hạn, biên đoạn, thứ tự biên, định dạng và dữ liệu thiếu/thừa. Checker được thử bằng đáp án đúng, khoảng trắng thay đổi và đáp án sai/thiếu/thừa. Quy trình xác nhận cấu trúc đề theo mẫu knapsack, hai ví dụ, số dòng kết quả, metadata, khả năng tái lập bộ sinh và 72 hash SHA-256. `[upload]` lấy từ `segtree000`, riêng types là `['ds_segment_tree']`; giới hạn kiểm tra và upload đều là 0,5 giây.

## SEGTREE006, SEGTREE007, SEGTREE009 — Truy vấn tĩnh không dùng hiệu tổng tiền tố

| Mã | Tên bài | Thông tin cần truy vấn |
| --- | --- | --- |
| segtree006 | Mức giá nhỏ thứ hai | Hai mức giá nhỏ nhất khác nhau |
| segtree007 | Chu kỳ chung của đoạn | BCNN, chặn khi vượt 10^18 |
| segtree009 | Cặp hàng kề nhau rẻ nhất | Min trên dãy giá hai phần tử kề nhau |

Cả ba thuộc Static Range Query (`TOP-FB61J3EYJR`, dải 000–009), N,Q ≤ 200.000, không cập nhật, không tìm kiếm vị trí trên cây và không lazy. Bài 006 và 009 dùng giá 0..10^9; bài 007 dùng chu kỳ dương 1..10^9. Bài 006 loại trùng mức giá, trả −1 khi không có mức giá thứ hai. Bài 007 in −1 khi BCNN lớn hơn 10^18, kiểm tra trước khi nhân để tránh tràn số. Bài 009 yêu cầu đúng hai món có chỉ số kề nhau cùng nằm trong đoạn, trả −1 khi L=R; lời giải tạo B_i=A_i+A_{i+1} rồi truy vấn min trên [L,R−1]. Dù bài 006 lưu hai trường, trọng tâm vẫn là truy vấn tĩnh, không đổi sang nhóm 060–069.

Chạy cả nhóm hoặc một bài:

```sh
python3 custom/segtree_tests/check_static_three.py
python3 custom/segtree007/tests/check.py
```

Dùng `--update-hashes` khi chủ động thay đổi dữ liệu hoặc đáp án chuẩn. Mỗi bài có 36 test: 2 ví dụ, 12 biên, 8 nhỏ, 8 ngẫu nhiên và 6 lớn; tổng cộng 108 test chính. Đề theo cấu trúc knapsack, không Subtask và không HTML. `[upload]` lấy từ `segtree000`, riêng types là `['ds_segment_tree']`; giới hạn kiểm tra và upload đều 0,5 giây.

Mảng tổng tiền tố của dữ liệu đầu vào không đủ trả lời bằng hiệu hai tổng. Bộ kiểm tra có các cặp cùng độ dài và tổng nhưng đáp án khác nhau: bài 006 là [0,2,4] và [1,1,4], tổng 6, đáp án 2 và 4; bài 007 là [2,6] và [3,5], tổng 8, BCNN 6 và 15; bài 009 là [1,4,1,4] và [1,1,4,4], cùng tổng 10 và cùng tập giá nhưng giá cặp kề rẻ nhất là 5 và 2. Các cặp này đều được chạy qua lời giải và đối chiếu trực tiếp. Bài 009 vẫn cần một phép truy vấn min sau khi biến đổi thành dãy giá cặp; cộng tổng tiền tố của dãy giá cặp không thay thế được truy vấn min. Đây không phải yêu cầu bắt buộc duy nhất một cấu trúc dữ liệu: các kỹ thuật truy vấn tĩnh khác vẫn có thể giải được nếu đáp ứng giới hạn.

`oracle_static_three.cpp` dùng lời giải độc lập: chia căn với từng khối được sắp xếp cho bài 006, tìm min đoạn trước rồi tìm phần tử nhỏ nhất lớn hơn min bằng upper_bound trên các khối nguyên; chia căn với BCNN khối cho bài 007, dùng phép nhân 128 bit và chặn sau khi nhân, độc lập với kiểm tra chia trước nhân của lời giải mẫu; sparse table min cho bài 009. Mọi test chính được đối chiếu với lời giải độc lập; ví dụ, test biên và test nhỏ còn được đối chiếu bằng sắp xếp tập giá, math.lcm số nguyên tùy ý hoặc duyệt từng cặp kề nhau.

Có thêm 4.717 trường hợp đối chiếu: 1.572 cho bài 006, 1.573 cho bài 007 và 1.572 cho bài 009. Mỗi bài liệt kê mọi mảng độ dài 1–5 trên bảng bốn giá trị và hỏi mọi đoạn, thêm 200 trường hợp ngẫu nhiên cùng các cấu hình riêng về giá trị biên, phần tử lặp, GCD/LCM có thừa số chung, BCNN sát ngưỡng hoặc vượt ngưỡng, hai mức giá nhỏ nhất trùng nhiều lần và hai món rẻ nhất không kề nhau. Có ca quanh các biên khối 449/450/451 và 899/900/901. Test lớn có N=Q=200.000 hoặc N=199.999, dãy đồng nhất, giá trị nhỏ thứ hai chỉ xuất hiện ở cuối, BCNN vượt ngưỡng và tổng giá cặp 2.000.000.000.

Verifier được thử với 16 dữ liệu sai mỗi bài về N,Q, giá trị, chỉ số, thứ tự biên, định dạng và dữ liệu thiếu/thừa. Checker được thử với đáp án đúng, khác khoảng trắng và đáp án sai/thiếu/thừa. Quy trình xác nhận hai ví dụ, cấu trúc đề, metadata, số dòng kết quả, khả năng tái lập mọi test sinh và 216 hash SHA-256.
