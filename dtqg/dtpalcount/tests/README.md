# Kiểm thử DTPALCOUNT

Bài tự biên soạn, biến thể của PALINCUT. Có 34 test: hai ví dụ, tám test biên, tám test nhỏ ngẫu nhiên, tám test lớn và tám test buộc thay đổi thứ tự hoặc xen kẽ các loại độ dài. Ví dụ có trọng số 0, mỗi test còn lại có trọng số 1; tổng điểm bài là 100. Không dùng manifest riêng và không chia subtask.

`gen/cases.cpp` dùng phần triển khai chung `../palplan_tests/generator.h` tính từ thư mục bài. Nhóm mới nằm tại `gen/order_trap.cpp`. Dữ liệu được sinh bằng seed cố định. Hướng dẫn chung nằm tại [README chung](../../palplan_tests/README.md).

Chạy riêng bài này từ thư mục gốc:

```sh
python3 dtqg/palplan_tests/check.py --problem dtpalcount
```

Khi chủ động thay đổi dữ liệu, thêm `--update-hashes`.

## Bắt lời giải chọn hết từng loại theo thứ tự đầu vào

Lời giải học sinh được lưu tại `tests/wrong_input_order.cpp`. Chỉ thay phần include bằng các thư viện chuẩn và thêm ép kiểu tương đương ở phép so sánh kích thước để biên dịch với cảnh báo nghiêm ngặt; giữ nguyên thuật toán và hai modulo hash.

Trước khi bổ sung, `cases_07.in` đã bắt được lời giải này: xâu `aaab`, cần một đoạn dài 1 và một đoạn dài 3. Đáp án hợp lệ là `aaa | b`, nhưng chọn đoạn dài 1 trước làm lời giải in `NO`.

Tám test mới đều có đáp án `YES`, với một cách chọn được bộ sinh cung cấp ở chế độ `witness`:

| Test | Dữ liệu chính | Mục tiêu |
| --- | --- | --- |
| `order_trap_00` | `aaab`, độ dài 1 và 3 | Phải đổi thứ tự hai loại |
| `order_trap_01` | `aabbbcc`, hai đoạn dài 2, một đoạn dài 3 | Phải chọn thứ tự 2, 3, 2 |
| `order_trap_02` | Cùng xâu, đổi thứ tự hai dòng yêu cầu | Không thể giải bằng đổi thứ tự hai nhóm |
| `order_trap_03` | Sáu khối, ba độ dài 3, 4, 5 | Ba loại xen kẽ, mỗi loại xuất hiện hai lần |
| `order_trap_04` | Hai độ dài 2, 3 xen kẽ, mỗi loại 20 đoạn | Số lượng lớn nhất của hai loại |
| `order_trap_05` | Ba độ dài 3, 4, 5 xen kẽ, mỗi loại 20 đoạn | Đủ 60 đoạn cần chọn |
| `order_trap_06` | Ba độ dài 1000, 1001, 1002, mỗi loại 20 đoạn | Đoạn dài, đổi thứ tự dòng yêu cầu |
| `order_trap_07` | n = 100000, ba độ dài 1600, 1601, 1602, mỗi loại 20 đoạn | Đạt giới hạn xâu, có tiền tố thừa |

Các khối dùng các ký tự khác nhau ở lân cận. Độ dài khối nằm trong khoảng từ L đến nhỏ hơn 2L, nên không thể chia một khối thành hai đoạn yêu cầu. Các test 1 đến 6 dùng đúng toàn bộ chiều dài cho các đoạn; test 7 có tiền tố `xyz` lặp không cung cấp đoạn đối xứng dài yêu cầu. Nhóm này buộc chọn các loại theo thứ tự khối, thay vì gom tất cả đoạn cùng loại thành một nhóm.

Quy trình kiểm tra biên dịch và chạy trực tiếp code học sinh trên cả tám test, yêu cầu nó in `NO` và checker trả WA. Đồng thời thử mọi hoán vị của các nhóm độ dài: cả bảy test từ 1 đến 7 vẫn làm cách chọn từng nhóm thất bại. Witness được xác thực trực tiếp bằng checker, độc lập với thứ tự các đoạn do lời giải mẫu chọn.

## Kết quả

Đạt 34 test chính thức, 100 trường hợp nhỏ độc lập và 21 test chính thức được đối chiếu thêm bằng liệt kê trực tiếp; tám đầu vào sai bị loại và 25 tình huống checker đạt yêu cầu. Code học sinh bị bắt ở cả tám test mới; cách thử mọi hoán vị của các nhóm bị bắt ở bảy test mới.

Toàn bộ 68 mục hash khớp. Cả 26 cặp đầu vào/đáp án cũ được giữ nguyên nội dung và đối chiếu hash trước/sau. Thời gian lời giải mẫu lớn nhất đo được là 0.0103 giây, dưới giới hạn upload 3 giây.
