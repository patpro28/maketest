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
