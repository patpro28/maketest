# Bộ bài ICPC0711

Chuyển đủ 12 bài A–L từ đề chung kết ICPC PTIT 2025, ngày 21/09/2025. Mỗi bài nằm trong `custom/icpc0711<chữ cái>/`, gồm đề, lời giải bằng tiếng Việt, chương trình C++17 riêng, bộ sinh, bộ kiểm tra đầu vào, checker và `hash.json`. Các mẫu vào/ra giữ nguyên giá trị và thứ tự của nguồn. Không xuất HTML, không thêm Subtask. Lời giải không chứa mã tham khảo và đề không có mục Nguồn, theo yêu cầu người dùng.

| Mã bài | Tên | Trang in trong PDF | Số mẫu | Số test tổng |
| --- | --- | --- | ---: | ---: |
| [ICPC0711A](../icpc0711a/task.md) | Xâu ABC | 1 | 2 | 18 |
| [ICPC0711B](../icpc0711b/task.md) | Phần tử trung vị | 2 | 3 | 19 |
| [ICPC0711C](../icpc0711c/task.md) | Số lập phương đối xứng | 3 | 3 | 19 |
| [ICPC0711D](../icpc0711d/task.md) | Biến đổi dãy số bằng phép XOR | 3–4 | 4 | 20 |
| [ICPC0711E](../icpc0711e/task.md) | Thành phần liên thông | 4–5 | 3 | 19 |
| [ICPC0711F](../icpc0711f/task.md) | Số 357 | 5 | 3 | 19 |
| [ICPC0711G](../icpc0711g/task.md) | Thứ tự xâu | 5–6 | 2 | 18 |
| [ICPC0711H](../icpc0711h/task.md) | Đổi chỗ quân bài | 6–7 | 3 | 19 |
| [ICPC0711I](../icpc0711i/task.md) | Thu thập kho báu | 7–9 | 2 | 18 |
| [ICPC0711J](../icpc0711j/task.md) | Tổng các chữ số | 9 | 3 | 19 |
| [ICPC0711K](../icpc0711k/task.md) | Dãy số TriSeq | 10 | 1 | 17 |
| [ICPC0711L](../icpc0711l/task.md) | Thao tác trên dữ liệu dạng cây | 11–13 | 2 | 18 |

Tổng cộng 223 test, gồm 31 mẫu gốc và 192 test tự sinh. Test tự sinh không phải bộ test chính thức của kỳ thi.

## Các điểm làm rõ khi chuyển đề

- Mục lục PDF bỏ sót bài E; nội dung trang 4–5 có bài này nên vẫn nhập đầy đủ.
- Bài A, giải thích truy vấn thứ hai của mẫu 1 ghi nhầm “2 xâu con”; sửa thành 1, khớp mẫu đầu ra và xâu sau cập nhật.
- Bài H không quy định trường hợp vô nghiệm trong PDF. Người dùng đã chọn **chỉ dùng dữ liệu bảo đảm có lời giải**. Đề ghi rõ điều kiện này; bộ sinh xây dựng một hoán vị đích khả thi; verifier kiểm tra lại tính khả thi bằng DP tập con không tối ưu hóa chi phí. Nhánh `-1` trong chương trình chỉ là phòng vệ, không phải một loại đầu ra hợp lệ của bộ dữ liệu.
- Bài K hiểu ba phần tử là ba vị trí phân biệt; với N < 3 điều kiện luôn đúng. T là thứ hạng hợp lệ và A là TriSeq, đúng miền xác định của hai yêu cầu. Verifier kiểm tra cả hai điều kiện.
- Bài L sửa lỗi gõ “i - 1 dòng” thành n - 1 cạnh. Làm rõ kết quả bằng 0 khi chỉ có một đỉnh đen và chu trình hai đỉnh đi-về, phù hợp các mẫu.
- PDF không nêu bảng chữ cái cho G; không tự giới hạn verifier vào chữ thường. Dùng các xâu dạng token không có khoảng trắng, so sánh từ điển như xâu C++.
- PDF không cấm khuyên/cạnh trùng cho E; verifier không áp thêm điều kiện. Các trường hợp này vẫn được xử lý theo định nghĩa đồ thị tích.
- Giới hạn thời gian cấu hình 1.0 giây ở cả cấp bài và `[upload]`, theo quy định dự án; bộ nhớ 256 MiB. Chưa tải bài lên máy chủ.

## Chạy lại

Từ thư mục gốc dự án:

```sh
python3 custom/icpc0711_tests/run.py
python3 custom/icpc0711_tests/oracle.py
```

`run.py` ưu tiên `CXX` nếu được đặt, tiếp theo là `g++-16`, rồi `g++`. Trên macOS cần GCC có `bits/stdc++.h`, như các bài khác trong dự án. Biên dịch với C++17, O2, `-Wall -Wextra -Werror`.

`run.py` gọi riêng kiểm tra cấu hình, sinh dữ liệu và kiểm tra đầu vào, chạy lời giải với timeout đúng 1.0 giây mỗi test, kiểm tra đầu ra bằng checker, đối chiếu mẫu và cấu trúc Markdown, sau đó so sánh SHA-256 với `hash.json`. Checker được thử với đáp án đúng, thiếu kết quả, sai kết quả và dữ liệu thừa. Không gọi quy trình xuất HTML. Chỉ dùng `--update-hashes` khi chủ động thay đổi dữ liệu chuẩn. Có thể giới hạn bằng `--letters abc` khi làm việc trên một số bài.

## Phạm vi bộ test

Mỗi bài có 16 lần sinh tái lập, hạt giống cố định theo chỉ số: 11 test nhỏ/biên và 5 test lớn/biên lớn (với C, F dùng danh sách cận số đặc biệt).

- A: cập nhật đầu/cuối, xâu ngắn, nhiều ABC, bảng chữ cái rộng.
- B: giá trị bằng nhau, tăng/giảm, xen kẽ hai cực trị, ngẫu nhiên tới N = 100000.
- C: quanh các lập phương đối xứng, N = 1 và N = 10^18.
- D: đa tập mở rộng khớp/không khớp, dãy bằng nhau, nhiều chu trình đổi chỗ tách rời, giá trị trùng.
- E: không cạnh, đường thẳng, nhiều tam giác, khuyên/cạnh trùng, N = 100000 và M = 200000.
- F: quanh 357 và các mốc toàn chữ số 7, N = 10^9.
- G: K = 1/K = N/K trung gian, thứ tự xâu đầu vào xáo trộn, xâu dài tới tổng 10^6, nhiều xâu ngắn; mẫu gốc có độ dài khác nhau.
- H: có mặt trước/mặt sau khác nhau, số trùng, dãy đảo ngược cần 153 thao tác, N = 18; chỉ dữ liệu khả thi.
- I: điểm phía ngoài bức tường, các điểm cùng hoành độ, tọa độ lớn và ngẫu nhiên, tổng trọng số vượt 32 bit. Bộ sinh và verifier loại các điểm chung tia từ mỗi đầu bức tường.
- J: nhiều lần nhớ liên tiếp, 10^15, 10^15 - 1, các giá trị ngẫu nhiên 15 chữ số, N = 200000.
- K: N nhỏ, N = 18, dãy toàn 1/toàn N, các phần tử trong nửa trên miền giá trị; bổ sung kiểm tra thứ hạng cuối trong oracle.
- L: cây đường thẳng, sao, nhị phân và ngẫu nhiên, trọng số 10^9, n = q = 200000; đổi màu xen kẽ cả hai loại truy vấn. Mọi truy vấn được bảo đảm có đỉnh đen.

## Đáp án đối chiếu độc lập

`oracle.py` không chỉ so lời giải với chính đáp án đã sinh:

- A đếm lại mọi vị trí; B dựng tất cả trung vị; C kiểm tra đối xứng bằng chuỗi; F duyệt tích Descartes của ba chữ số.
- D BFS trên các dãy đạt được bằng thao tác XOR thật.
- E dựng đồ thị tích ở cỡ nhỏ và đếm liên thông trực tiếp.
- G sinh, ghép và sắp xếp mọi chỉnh hợp nhỏ.
- H duyệt mọi hoán vị, xét mặt hiện và số nghịch thế; kiểm tra verifier từ chối các trường hợp vô nghiệm ngẫu nhiên.
- I dùng tích có hướng để xét ba nửa mặt phẳng của từng tam giác.
- J cộng trực tiếp tổng chữ số cho mọi cặp nhỏ.
- K duyệt mọi dãy tới N = 6, đối chiếu đếm/hạng/khôi phục; ở N = 6,10,18 dùng công thức đếm theo hai giá trị nhỏ nhất để kiểm tra độc lập thứ hạng cuối.
- L dùng Held–Karp trên đồ thị khoảng cách đầy đủ, độc lập với công thức cây nối và đường kính.
- B, E, H, J có thêm dữ liệu lớn biết đáp án bằng công thức đơn giản.
- Thử dữ liệu ngoài giới hạn, thiếu/thừa dữ liệu, xâu tiền tố hoặc lặp thành phần, điểm nằm trên hàng rào, dãy không TriSeq, thứ hạng quá lớn và truy vấn cây không có đỉnh đen.

Kết quả thực tế nằm trong [results.md](results.md). Thời gian đo phụ thuộc máy chạy, không phải cam kết cho mọi môi trường chấm.

## Nhận diện tài liệu nguồn

- Tệp: `/Users/patpro28/Downloads/ĐỀ CHUNG KẾT ICPC 2025.pdf`
- SHA-256: `de4e28e384fc34b05a9670eb6ff8672d0b260b4247709f8c2a55cecfa38818b5`
- 14 trang vật lý: 1 trang bìa và 13 trang đề.
