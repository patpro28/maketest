# Kiểm thử bốn phiên bản Lính canh của Victor

| Mã bài | Phiên bản | Giới hạn | Thuật toán chính |
| --- | --- | --- | --- |
| [DTVICTOR1](../dtvictor1/task.md) | Subtask 1 | $N,M\le 2000$ | DFS trên cây con cho mỗi truy vấn |
| [DTVICTOR2](../dtvictor2/task.md) | Subtask 2 | $N,M\le 200000$, phân công cố định | Trọng số LCA và tổng cây con tính trước |
| [DTVICTOR3](../dtvictor3/task.md) | Subtask 3 | $N,M\le 200000$, có đổi phân công | HLD, tập có thứ tự và Fenwick cho cập nhật đường đi |
| [DTVICTOR4](../dtvictor4/task.md) | Subtask 4 | $N\le 500000$, $M\le 300000$ | Trọng số LCA động, tập có thứ tự và Fenwick cho tổng đoạn |

Nguồn đề là DMOPC '20 Contest 1 P5 — Victor Takes Over Canada. Bản II giữ ví dụ tĩnh của đề gốc và thêm một ví dụ có cùng một lính canh phụ trách mọi thành phố. Các bản còn lại giữ cả hai ví dụ gốc theo thứ tự. Bốn bài chấm độc lập trên thang 100 điểm và dùng giới hạn 1 giây, bộ nhớ 512 MiB.

Từ thư mục gốc của dự án, chạy `python3 dtqg/victor_tests/check.py` để sinh lại và kiểm tra toàn bộ. Có thể chọn một bài bằng `--problem dtvictor4`. Chỉ thêm `--update-hashes` khi chủ động cập nhật bộ dữ liệu. Có thể đặt `CXX` và `CXXFLAGS` để chọn trình biên dịch và cờ. Bộ sinh và trình xác thực đầu vào của bốn bài dùng chung các tệp `generator.h` và `validator.h` tại đây.

Mỗi bài có 2 ví dụ, 14 test nhỏ hoặc biên và 8 test ở kích thước tối đa. Dữ liệu có cây đường thẳng, cây sao, cây nhị phân, cây ngẫu nhiên và cây có nhiều lá ở cuối một đường dài. Các bản có cập nhật thử gán lại cùng mã, chuyển sang mã chưa được dùng, đổi phân công ở gốc và ở lá, và bộ sự kiện chỉ có cập nhật. Đầu vào lớn dùng số hiệu thành phố và thứ tự cạnh đã xáo trộn.

Quy trình sinh lại từng test để so sánh nội dung, xác thực đầu vào, chạy lời giải với giới hạn 1 giây, đối chiếu bằng lời giải duyệt trực tiếp và chạy checker. Mỗi bài còn được đối chiếu trên 120 bộ dữ liệu nhỏ tạo độc lập. Trình xác thực được thử với cạnh lặp, khuyên, mã lính canh ngoài miền, sự kiện thiếu hoặc thừa và cập nhật trong bản tĩnh. Checker được thử với đáp án sai, thiếu, thừa, số tràn, token không phải số và đáp án đúng có khoảng trắng khác. Kết quả được đối chiếu với `hash.json`.

## Kết quả

Với Apple Clang, cả 96 test chính thức và 480 bộ dữ liệu đối chiếu nhỏ đều đạt. Trình xác thực loại đúng 55 đầu vào sai, checker đạt 27 trường hợp và 192 mục SHA-256 khớp. Thời gian dưới đây là thời gian thực lớn nhất trong các test chính thức, có tính thời gian khởi động tiến trình.

| Mã bài | Test chính thức | Thời gian lớn nhất | Giới hạn |
| --- | ---: | ---: | ---: |
| DTVICTOR1 | 24 | 0,087 giây | 1 giây |
| DTVICTOR2 | 24 | 0,311 giây | 1 giây |
| DTVICTOR3 | 24 | 0,313 giây | 1 giây |
| DTVICTOR4 | 24 | 0,375 giây | 1 giây |
