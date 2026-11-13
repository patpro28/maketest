# Kiểm tra dpstr101

Chạy từ thư mục gốc dự án:

```sh
python3 custom/dpstr101/tests/check.py
```

Tài liệu và quy trình đầy đủ ở `custom/dpstr_lcs_tests/README.md`.

`checker.cpp` chấp nhận mọi dãy con chung tối ưu, không yêu cầu xâu giống đáp án mẫu hoặc đáp án sinh bởi lời giải chuẩn. Trường hợp `abc`, `bac` phải nhận cả `2 / ac` và `2 / bc`. Trường hợp không có ký tự chung nhận `0` và cho phép dòng thứ hai trống.

Lệnh `python3 generate.py -u dpstr101` tự tải checker riêng qua endpoint `/checker`, rồi nhập ZIP test. `[upload].checker = 'custom'` chọn `checker.cpp` của bài; manifest ZIP không đặt lại checker sau bước này. Có thể thêm `[upload].checker_args = {time_limit = 3}` khi cần giới hạn thời gian riêng cho checker.
