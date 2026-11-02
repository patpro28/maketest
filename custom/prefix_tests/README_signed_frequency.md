# PREFIX090–PREFIX099 — Mức 09x: tổng tiền tố và bảng tần suất

Mười bài đếm đoạn không rỗng có độ dài thay đổi, cho phép số âm, số 0 và số dương. Các đoạn được phép chồng lấn; hai đoạn khác nhau nếu đầu trái hoặc đầu phải khác nhau.

Tên thư mục dùng `dppsum090`–`dppsum099`; nhãn trong đề, lời giải và trường `title` dùng `PREFIX090`–`PREFIX099`.

| Mã thư mục | Nhãn | Yêu cầu |
| --- | --- | --- |
| dppsum090 | PREFIX090 | Đếm đoạn có tổng bằng 0 |
| dppsum091 | PREFIX091 | Đếm đoạn có tổng bằng T |
| dppsum092 | PREFIX092 | Đếm đoạn tổng T có độ dài chẵn |
| dppsum093 | PREFIX093 | Đếm đoạn tổng T có độ dài lẻ |
| dppsum094 | PREFIX094 | Đếm đoạn tổng T có độ dài ít nhất K |
| dppsum095 | PREFIX095 | Đếm đoạn tổng T có độ dài không vượt K |
| dppsum096 | PREFIX096 | Đếm đoạn tổng T có độ dài thuộc [L,R] |
| dppsum097 | PREFIX097 | Đếm đoạn có tổng chia hết cho M |
| dppsum098 | PREFIX098 | Đếm đoạn có tổng đồng dư C theo M |
| dppsum099 | PREFIX099 | Đếm đoạn có số phần tử dương bằng số phần tử âm |

Ý tưởng chung: tổng đoạn từ j+1 đến r bằng P[r]-P[j]. Muốn tổng bằng T, tìm các tiền tố trước đó có giá trị P[r]-T. Bảng tần suất ghi số chỉ số tiền tố có cùng giá trị, không chỉ ghi có/không. Hỏi trước khi thêm tiền tố hiện tại để loại đoạn rỗng.

Các bài giới hạn độ dài duy trì đúng tập chỉ số tiền tố được phép ghép với đầu phải hiện tại. Khi loại một chỉ số, chỉ giảm một đơn vị tần suất; không xóa toàn bộ những chỉ số khác có cùng tổng. Bài chẵn/lẻ tách tần suất theo tính chẵn lẻ của chỉ số tiền tố. Các bài modulo chuẩn hóa phần dư âm. Bài cân bằng đổi số dương thành 1, số âm thành -1 và số 0 thành 0.

Giới hạn N=200000, giá trị phần tử từ -1000000000 đến 1000000000. T có thể âm và trị tuyệt đối không vượt 200000000000000. M không vượt 200000. Tổng tiền tố, khóa của bảng và đáp án cần số nguyên 64 bit; đáp án có thể đạt 20000100000.

Lời giải dùng `std::map` cho các tổng tiền tố bất kỳ, thời gian O(N log N); hai bài modulo dùng mảng tần suất, thời gian O(N+M). Mỗi bài có ba ví dụ, hướng dẫn giải, lời giải C++ độc lập, bộ sinh, verifier, checker và hash. Không có Subtask; không xuất HTML. Upload giữ `types = ['dp_prefix_sum', 'dp_sequence']` cùng các trường của nhóm trước. Quy trình kiểm tra không thực hiện upload.

## Sinh và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check_signed_frequency.py --generate
```

Mỗi bài có 23 test (ba ví dụ và 20 test theo seed), gồm bốn test N=200000. Quy trình biên dịch đầy đủ, sinh và xác thực mọi đầu vào, tạo đáp án và chạy checker. Lời giải đối chiếu Python nhóm toàn bộ chỉ số tiền tố theo giá trị/phần dư/tính chẵn lẻ, rồi dùng tìm kiếm nhị phân giới hạn chỉ số hợp lệ cho từng đầu phải. Cách này độc lập với cập nhật bảng tần suất theo thời gian trong lời giải C++.

Bộ kiểm tra vét cạn xét dãy có tối đa ba phần tử từ {-1,0,1}, nhiều tổng mục tiêu, mọi K hoặc mọi khoảng độ dài và mọi phần dư trong các mô-đun nhỏ tùy bài. Mỗi bài thêm 160 trường hợp ngẫu nhiên. Cách vét cạn duyệt mọi đoạn không rỗng và cộng trực tiếp giá trị; bài cân bằng đếm trực tiếp số dương và số âm, không dùng tổng biến đổi.

Các test bao phủ số 0 liên tiếp, tiền tố trùng giá trị, tổng mục tiêu âm, giới hạn độ dài 1/N và L=R, M=1/M=200000, phần dư khác 0 và tổng tiền tố âm. Mọi bài đều có tiền tố dương/âm vượt 32 bit và đáp án vượt 32 bit. Một số ca N tối đa đã được đo thời gian thực thi để đối chiếu cấu hình upload.

Verifier được thử với N, giá trị, T, độ dài, M, C sai giới hạn và dữ liệu thiếu/thừa. Checker được thử đáp án sai, âm, thiếu/thừa số, ký tự không phải số và khoảng trắng khác nhau. Sau cùng ghi `hash.json`, sinh lại đầu vào với cùng seed và xác nhận hash không đổi.

Kiểm tra lại dữ liệu và chương trình đã sinh:

```sh
python3 custom/prefix_tests/check_signed_frequency.py
```

Chọn một bài:

```sh
python3 custom/prefix_tests/check_signed_frequency.py --problem dppsum096 --generate
python3 custom/dppsum096/tests/check.py
```
