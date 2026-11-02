# PREFIX080–PREFIX089 — Mức 08x: đoạn có độ dài thay đổi

Mười bài trên dãy số nguyên không âm, dùng hai con trỏ kết hợp tổng tiền tố. Độ dài đoạn không còn cố định. Chỉ xét đoạn không rỗng; không nối vòng.

Tên thư mục dùng `dppsum080`–`dppsum089`; nhãn trong đề, lời giải và trường `title` dùng `PREFIX080`–`PREFIX089`.

| Mã thư mục | Nhãn | Yêu cầu |
| --- | --- | --- |
| dppsum080 | PREFIX080 | Độ dài lớn nhất của đoạn có tổng <= T |
| dppsum081 | PREFIX081 | Độ dài và hai đầu mút của đoạn dài nhất có tổng <= T |
| dppsum082 | PREFIX082 | Độ dài nhỏ nhất của đoạn có tổng >= T |
| dppsum083 | PREFIX083 | Độ dài và hai đầu mút của đoạn ngắn nhất có tổng >= T |
| dppsum084 | PREFIX084 | Đếm đoạn có tổng <= T |
| dppsum085 | PREFIX085 | Đếm đoạn có tổng < T |
| dppsum086 | PREFIX086 | Đếm đoạn có tổng >= T |
| dppsum087 | PREFIX087 | Đếm đoạn có tổng > T |
| dppsum088 | PREFIX088 | Đếm đoạn có tổng = T |
| dppsum089 | PREFIX089 | Đếm đoạn có tổng thuộc khoảng đóng [U,V] |

Hai bài có đầu mút chọn vị trí bắt đầu nhỏ nhất nếu hòa. Nếu không có đoạn phù hợp, các bài chỉ hỏi độ dài in 0; hai bài có đầu mút in `0 0 0`. Các bài đếm in 0 nếu không có đoạn nào. Với T=0, độ dài nhỏ nhất của đoạn không rỗng có tổng >=T luôn là 1.

Điểm học mới: các phần tử không âm nên tổng không giảm khi tăng đầu phải và không tăng khi tăng đầu trái. Hai con trỏ có thể chỉ tiến về phía trước. Nhóm đếm xây dựng F(X), số đoạn có tổng <=X, rồi dùng hiệu hoặc phần bù để xử lý các điều kiện còn lại. F(X)=0 khi X<0; quy tắc này xử lý T=0 và U=0 mà vẫn không đếm đoạn rỗng.

Giới hạn N=200000, 0<=A_i<=1000000000, các ngưỡng không vượt 200000000000000. Tổng và số lượng đoạn cần số nguyên 64 bit; số đoạn không rỗng có thể đạt 20000100000.

Mỗi bài có ba ví dụ, hướng dẫn giải, lời giải C++ độc lập, bộ sinh, verifier, checker và hash. Không có Subtask; không xuất HTML. Cấu hình upload giữ `types = ['dp_prefix_sum', 'dp_sequence', 'tech_two_pointers']` và các trường của bộ trước. Quy trình kiểm tra không thực hiện upload.

## Sinh và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check_variable_nonnegative.py --generate
```

Mỗi bài có 23 test (ba ví dụ và 20 test theo seed), gồm bốn test N=200000. Quy trình biên dịch đầy đủ, sinh và xác thực toàn bộ đầu vào, tạo đáp án và chạy checker. Lời giải đối chiếu Python dùng tìm kiếm nhị phân trên tổng tiền tố không giảm, độc lập với hai con trỏ trong lời giải C++. Các bài đếm dùng trực tiếp cận trái/cận phải của tổng tiền tố, không lặp lại công thức phần bù của chương trình C++.

Chín bài đầu được đối chiếu trên 180 trường hợp vét cạn (dãy có tối đa ba phần tử từ {0,1,2}, xét mọi T từ 0 đến tổng toàn dãy cộng 1) và 160 trường hợp ngẫu nhiên mỗi bài. Bài khoảng tổng có 547 trường hợp vét cạn với mọi U,V trong miền nhỏ tương ứng và thêm 160 trường hợp ngẫu nhiên. Phương án vét cạn duyệt mọi đoạn không rỗng, tính trực tiếp tổng và áp dụng đúng điều kiện.

Bộ kiểm tra xác nhận có ngưỡng 0, dãy toàn 0, dãy trộn 0 với số dương, có/không có đáp án, tổng vượt 32 bit và trường hợp N tối đa. Mọi bài đếm đều có đáp án vượt 32 bit. Các trường hợp số 0 liên tiếp giúp kiểm tra nghiêm ngặt việc không đếm đoạn rỗng và không bỏ sót nhiều đoạn cùng tổng.

Verifier được thử với N, giá trị phần tử, ngưỡng ngoài giới hạn, U>V và dữ liệu thiếu/thừa. Checker được thử với đáp án sai, thiếu/thừa số, định dạng khoảng trắng khác nhau; các bài in đầu mút được thử sai riêng từng trường kết quả. Cuối cùng ghi `hash.json`, sinh lại đầu vào với cùng seed và xác nhận hash không đổi.

Kiểm tra lại dữ liệu và chương trình đã sinh:

```sh
python3 custom/prefix_tests/check_variable_nonnegative.py
```

Chọn riêng một bài:

```sh
python3 custom/prefix_tests/check_variable_nonnegative.py --problem dppsum088 --generate
python3 custom/dppsum088/tests/check.py
```
