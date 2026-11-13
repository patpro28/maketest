# Kiểm tra đồng bộ mã DPSTR — 06/11/2026

Đã thống nhất tiền tố `dpstr` cho 22 bài thuộc hai nhóm dãy con chung và đoạn con liên tiếp chung, cùng tên thư mục, tiêu đề đề, trường `title`, đường dẫn bộ kiểm tra và tài liệu liên quan. Thư mục kiểm tra đoạn con chung là `custom/dpstr_substring_tests/`.

Tất cả 22 bài dùng `types = ['dp_string', 'dp_common_substring']`, `timelimit = 1.0` và `[upload].time_limit = 1.0`. Các trường cấu hình khác được giữ nguyên, bao gồm checker riêng của bài `dpstr101`.

| Phạm vi | Số bài | Cặp input/output | Vét cạn dữ liệu đã sinh | Vét cạn bổ sung |
| --- | --- | --- | --- | --- |
| 100, 101, 102, 103, 130, 131, 132, 150, 151, 152 | 10 | 328 | 206 | 3097 |
| 153 | 1 | 35 | 23 | 3161 |
| 154 | 1 | 37 | 23 | 1020 |
| 200, 201, 202, 203, 230, 231, 232, 250, 251, 252 | 10 | 341 | 221 | 3729 |
| Tổng | 22 | 741 | 473 | 11007 |

Các bộ kiểm tra đã được chạy đầy đủ ở đường dẫn mới: sinh lại dữ liệu, xác thực đầu vào, chạy lời giải trong giới hạn đã cấu hình, kiểm tra checker, đối chiếu lời giải độc lập và vét cạn, tính tái lập và mã băm. Mười bài LCS đầu tiên đạt cả C++ và Python; các bài còn lại đạt C++ và oracle riêng. Có thêm 24 trường hợp biên khối bit của bài 154.

Đối chiếu với bản ghi trước khi đổi tên xác nhận 1.559 file mẫu/input/output/`hash.json` giữ nguyên từng byte. Toàn bộ 1.482 mục mã băm khớp; công cụ tìm bài tra được đủ 22 mã mới, không có mã trùng.

Checker riêng của `dpstr101` vẫn chấp nhận các LCS tối ưu khác nhau. Cả tám test hồi quy của `dpstr150` và test điểm âm đầu đoạn của `dpstr230` đều đạt kiểm tra bắt thuật toán sai.

Không xuất HTML hoặc upload. Kết quả trên được kiểm tra cục bộ; cấu hình API đã được đối chiếu bằng metadata tạo từ từng bài.

Chi tiết từng bộ:

- [Quy trình LCS](README.md).
- [Kết quả bài 153](../dpstr153/tests/results.md).
- [Kết quả bài 154](../dpstr154/tests/results.md).
- [Kết quả đoạn con chung](../dpstr_substring_tests/results.md).
