# Kết quả kiểm tra nhóm 7

Lời giải C++11, giới hạn 1 giây mỗi test trên máy cục bộ. Không xuất HTML hoặc upload.

Riêng `dpstr600` đã tăng Q lên 500000 sau lần đo cả bộ trong bảng dưới. Kết quả mới nằm tại [báo cáo riêng](../dpstr600/tests/results.md), chi tiết dữ liệu và phép đo cách sao chép/đảo đoạn ở [tài liệu kiểm tra](../dpstr600/tests/README.md).

| Mã | Cặp test | Vét cạn test đã sinh | Vét cạn bổ sung | Công thức | Chậm nhất (giây) | Test |
| --- | --- | --- | --- | --- | --- | --- |
| dpstr600 | 34 | 22 | 256 | 5 | 0.2838 | max_02.in |
| dpstr601 | 34 | 22 | 256 | 7 | 0.0102 | max_01.in |
| dpstr602 | 34 | 22 | 256 | 6 | 0.0054 | max_03.in |
| dpstr603 | 34 | 22 | 256 | 6 | 0.0089 | max_00.in |
| dpstr630 | 34 | 22 | 256 | 7 | 0.0146 | max_00.in |
| dpstr631 | 34 | 22 | 258 | 8 | 0.0271 | max_01.in |
| dpstr632 | 34 | 22 | 256 | 6 | 0.0486 | max_01.in |
| dpstr650 | 34 | 22 | 258 | 8 | 0.0492 | max_02.in |
| dpstr651 | 34 | 22 | 514 | 5 | 0.0438 | max_01.in |
| dpstr652 | 34 | 22 | 256 | 8 | 0.0507 | max_00.in |

Tổng: 340 cặp test; 220 lượt vét cạn dữ liệu đã sinh; 2822 trường hợp bổ sung.

Đối chiếu oracle, verifier, checker, cấu hình, cấu trúc đề, tính tái lập và mã băm đều đạt.

Đo thêm lời giải `dpstr652` trên `max_00.in`: bộ nhớ thường trú cực đại khoảng 97,16 MiB, dưới giới hạn 128 MiB; đáp án khớp trong giới hạn 1 giây.
