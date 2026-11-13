# Kết quả kiểm tra nhóm 4

Đợt kiểm tra đầy đủ ban đầu dùng lời giải C++11, 0,5 giây mỗi test trên máy cục bộ. Các số đo trong bảng dưới thuộc đợt này. Không xuất HTML hoặc upload.

Sau khi cố định giới hạn thời gian thành **1 giây**, đã kiểm tra lại cả `timelimit`, `[upload].time_limit` và metadata gửi lên API của 10 bài; chạy lại lời giải C++ trên đủ **340 cặp test** với giới hạn mới, tất cả đều đạt. Đối chiếu toàn bộ 680 mục mã băm thành công.

| Mã | Cặp test | Vét cạn test đã sinh | Vét cạn bổ sung | Công thức | Chậm nhất (giây) | Test |
| --- | --- | --- | --- | --- | --- | --- |
| dpstr300 | 34 | 22 | 3399 | 0 | 0.0117 | max_04.in |
| dpstr301 | 34 | 22 | 3399 | 0 | 0.0129 | max_04.in |
| dpstr302 | 34 | 22 | 3399 | 0 | 0.0130 | max_03.in |
| dpstr303 | 34 | 22 | 300 | 5 | 0.0287 | max_01.in |
| dpstr330 | 34 | 22 | 324 | 7 | 0.0214 | max_00.in |
| dpstr331 | 34 | 22 | 660 | 5 | 0.0100 | max_01.in |
| dpstr332 | 34 | 22 | 300 | 5 | 0.0389 | max_00.in |
| dpstr350 | 34 | 22 | 660 | 5 | 0.0299 | max_00.in |
| dpstr351 | 34 | 22 | 660 | 4 | 0.0158 | max_00.in |
| dpstr352 | 34 | 22 | 315 | 2 | 0.0493 | max_03.in |

Tổng: 340 cặp test; 220 lượt vét cạn dữ liệu đã sinh; 13416 trường hợp bổ sung.

Tất cả đối chiếu độc lập và kiểm tra cấu hình, công cụ, dữ liệu, tính tái lập, mã băm đều đạt.
