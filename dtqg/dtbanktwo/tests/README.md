# Kiểm thử DTBANKTWO

Bài thuộc lộ trình BANK3; thứ tự luyện tập, thuật toán đối chiếu và cách chạy nằm tại [README chung](../../bankgame_tests/README.md).

## Dữ liệu và cách chạy

Có 30 test chính thức: 2 ví dụ và 28 test sinh, gồm 10 test biên, 8 test nhỏ và 10 test lớn. Ví dụ trọng số 0, các test sinh trọng số 1, tổng điểm bài là 100; không chia subtask. Bộ sinh tại `gen/cases.cpp` dùng `../../bankgame_tests/generator.h`. Đầu vào được kiểm tra bởi `verifier.cpp`, dùng phần triển khai chung tại `../bankgame_tests/validator.h`.

Từ thư mục gốc dự án:

```sh
python3 dtqg/bankgame_tests/check.py --problem dtbanktwo
```

Chỉ thêm `--update-hashes` khi chủ động thay đổi dữ liệu. Quy trình gọi riêng từng bước, không xuất HTML.

## Kết quả

- Đạt 30 test chính thức; mọi seed sinh lại cho dữ liệu giống hệt.
- Đạt 120 đầu vào nhỏ độc lập, đối chiếu bằng phép duyệt trực tiếp.
- Có 33 lượt đối chiếu bổ sung các bộ dữ liệu chính thức bằng phương pháp độc lập và 30 tệp chính thức được so với mã nguồn người dùng cung cấp.
- Loại đúng 12 đầu vào sai; đạt 20 tình huống checker.
- Khớp toàn bộ 60 mục trong `hash.json`.
- Thời gian lời giải mẫu lớn nhất đo được 0.0152 giây, dưới giới hạn 1 giây. Thời gian phụ thuộc máy chạy.

## Lỗi nhắm tới

Gộp các gói hoặc công trình có giá trị bằng nhau; bắt buộc dùng hết gói; đếm thứ tự gói trong cùng công trình; dùng một gói cho nhiều công trình; cấp thiếu/thừa tiền; tràn số khi cộng các giá trị tới 10^9. Các dữ liệu lớn đồng giá trị còn kiểm tra công thức đếm và modulo.
