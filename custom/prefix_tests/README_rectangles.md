# PREFIX070–PREFIX079 — Mức 07x: truy vấn hình chữ nhật

Mười bài cùng dạng truy vấn hình chữ nhật tĩnh trên bảng số. Bài đầu tính tổng giá trị; chín bài tiếp theo đếm các ô thỏa điều kiện. Các truy vấn tính cả ô trên biên và ở bốn góc, không cập nhật dữ liệu.

Tên thư mục dùng `dppsum070`–`dppsum079`; nhãn trong đề, lời giải và trường `title` dùng `PREFIX070`–`PREFIX079`.

| Mã thư mục | Nhãn | Yêu cầu trong hình chữ nhật |
| --- | --- | --- |
| dppsum070 | PREFIX070 | Tổng giá trị các ô |
| dppsum071 | PREFIX071 | Đếm số chẵn |
| dppsum072 | PREFIX072 | Đếm số dương |
| dppsum073 | PREFIX073 | Đếm số âm |
| dppsum074 | PREFIX074 | Đếm số chia hết cho D cố định |
| dppsum075 | PREFIX075 | Đếm số thuộc khoảng đóng [U,V] cố định |
| dppsum076 | PREFIX076 | Đếm số chính phương |
| dppsum077 | PREFIX077 | Đếm số nguyên tố |
| dppsum078 | PREFIX078 | Đếm số đối xứng |
| dppsum079 | PREFIX079 | Đếm số chứa chữ số 7 |

Mục tiêu mới: xây dựng prefix hai chiều và dùng công thức cộng trừ bốn góc. Với bài tổng, giữ nguyên giá trị từng ô. Với bài đếm, thay ô thỏa điều kiện bằng 1, còn lại bằng 0.

Giới hạn N,M là 500 và Q là 200000. Bài tổng cần số nguyên 64 bit vì trị tuyệt đối có thể đạt 250000000000000. Các kết quả đếm không vượt 250000. Bài nguyên tố có giá trị từ 0 đến 1000000; hai bài chữ số có giá trị từ 0 đến 1000000000; các bài còn lại cho phép từ -1000000000 đến 1000000000.

Mỗi bài có hai ví dụ, hướng dẫn giải, lời giải C++ độc lập, bộ sinh, verifier, checker và hash. Không có Subtask; không xuất HTML. Upload giữ `types = ['dp_prefix_sum', 'dp_sequence']` và các trường của bộ trước. Quy trình kiểm tra không thực hiện upload.

## Sinh và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check_rectangles.py --generate
```

Mỗi bài có 22 test (hai ví dụ và 20 test theo seed), gồm bốn test N=M=500, Q=200000. Quy trình biên dịch đầy đủ, sinh và xác thực đầu vào, tạo đáp án và chạy checker. Toàn bộ dữ liệu được đối chiếu với lời giải Python quét theo hàng: truy vấn tạo sự kiện cộng/trừ theo hàng, còn dữ liệu được cộng dồn trên một vector tiền tố theo cột. Phương án này không xây dựng bảng prefix hai chiều như lời giải C++.

Mỗi bài còn được kiểm tra trên 102 bảng nhỏ vét cạn với các kích thước 1x1, 1x2, 2x1, 2x2 và 160 bảng ngẫu nhiên tối đa 7x7. Mọi hình chữ nhật của từng bảng nhỏ đều được xét bằng cách cộng trực tiếp các ô. Bài nguyên tố dùng phép chia thử ở kiểm tra nhỏ và sàng độc lập ở dữ liệu lớn. Bài chính phương dùng căn bậc hai nguyên; các bài chữ số dùng chuỗi để đối chiếu cách tách chữ số C++.

Bộ kiểm tra xác nhận bảng một hàng/một cột, bảng không vuông, truy vấn toàn bảng, một ô và vùng không bắt đầu tại hàng/cột 1. Bài tổng có cả đáp án dương và âm vượt 32 bit. Dữ liệu còn có số 0, số âm khi được phép, giá trị trùng, hai biên U/V, D=1, chính phương lớn và các số sát nó, 0/1 không nguyên tố, số đối xứng có chữ số 0 và số chứa nhiều chữ số 7.

Verifier được thử với số hàng/cột/truy vấn ngoài giới hạn, giá trị hoặc tham số sai, tọa độ ngoài bảng, hai góc bị đảo và dữ liệu thiếu/thừa. Checker được thử trên cả hai ví dụ với đáp án sai, thiếu/thừa số, ký tự không phải số và khoảng trắng khác nhau. Cuối cùng ghi `hash.json`, sinh lại đầu vào với cùng seed và xác nhận hash không đổi.

Kiểm tra lại dữ liệu và chương trình đã sinh:

```sh
python3 custom/prefix_tests/check_rectangles.py
```

Chọn riêng một bài:

```sh
python3 custom/prefix_tests/check_rectangles.py --problem dppsum077 --generate
python3 custom/dppsum077/tests/check.py
```
