# Kiểm tra DPSTR600 với Q ≤ 500000

Giới hạn hiện tại là N ≤ 5000, Q ≤ 500000; thời gian 1 giây và bộ nhớ 128 MiB. Đề, `Q_MAX`, verifier và bộ kiểm tra dùng cùng giới hạn. Quy mô DP và trả lời truy vấn không quá 13.002.500 ô/truy vấn chính.

Chạy từ gốc dự án:

```sh
python3 custom/dpstr600/tests/check.py
```

Chỉ khi chủ động thay dữ liệu:

```sh
python3 custom/dpstr600/tests/check.py --update-hashes
```

Bài giữ 34 cặp test. Năm cặp lớn `max_00`–`max_04` đều đạt N = 5000 và Q = 500000; 29 cặp còn lại giữ nguyên từng byte so với trước khi tăng Q.

- `max_00`: nguồn ngẫu nhiên, chủ yếu hỏi đoạn dài, thêm một số đoạn một ký tự và toàn xâu.
- `max_01`: nguồn đồng nhất; tất cả truy vấn hỏi toàn xâu, luôn trả YES.
- `max_02`: hai khối ký tự khác nhau; tất cả truy vấn hỏi toàn xâu, luôn trả NO.
- `max_03`: nguồn xen kẽ; chủ yếu hỏi đoạn dài, gồm cả trường hợp đối xứng và không đối xứng.
- `max_04`: nguồn đối xứng; tất cả truy vấn hỏi toàn xâu, luôn trả YES.
- `max_05`: N = Q = 1, giữ trường hợp biên nhỏ.

Bộ kiểm tra yêu cầu tổng độ dài truy vấn của mỗi test đạt cả hai cận lớn không dưới 2 tỷ. Ba test hỏi toàn xâu có tổng độ dài 2,5 tỷ. Mọi đầu vào được verifier chấp nhận, mọi đáp án khớp oracle Manacher; 22 test nhỏ được vét cạn và có thêm 256 trường hợp bổ sung. Checker, tính tái lập, cấu trúc đề và 68 mục mã băm đều đạt. Kết quả lời giải chuẩn nằm tại [results.md](results.md).

## Đo lại cách sao chép rồi đảo đoạn

Đo trên máy cục bộ, biên dịch C++17 với `-O2`, giữ nguyên thuật toán code được gửi trong hội thoại: mỗi truy vấn lấy `substr`, sao chép, `reverse`, so sánh. Thời gian dưới đây là thời gian thực của cả tiến trình, gồm truyền input/output qua bộ đo, không phải kết quả từ máy judge.

| Test | Tổng độ dài truy vấn | Thời gian (giây) |
| --- | --- | --- |
| max_00 | 2.230.546.794 | 0,9661 |
| max_01 | 2.500.000.000 | 1,0223 |
| max_02 | 2.500.000.000 | 0,9588 |
| max_03 | 2.230.659.688 | 1,0347 |
| max_04 | 2.500.000.000 | 1,0270 |

Lời giải DP qua cả 34 test với thời gian chậm nhất khoảng 0,637 giây trong lần kiểm tra này. Cách sao chép/đảo đang sát ngưỡng 1 giây, nên dữ liệu mới chưa bảo đảm cách đó bị TLE trên mọi máy judge; cần đo ở judge nếu muốn kết luận về việc phân biệt hiệu năng. Không thay giới hạn thời gian và không upload trong lần cập nhật này.
