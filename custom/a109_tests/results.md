# Kết quả kiểm tra ngày 07/11/2026

Đã chạy thành công `python3 custom/a109_tests/check.py` cho toàn bộ 10 bài sau khi rút gọn các đề theo mẫu A109000004 và đồng bộ tên struct trong lời giải; toàn bộ hash hiện có vẫn khớp.

- 250 test chính với đầu vào nhị phân thật, gồm 30 test lớn có 200.000 bản ghi. Mỗi lời giải đọc đúng tệp `A109xxxxxx.INP` và ghi đúng tệp văn bản `A109xxxxxx.OUT` trong thư mục chạy riêng, với luồng vào chuẩn bị đóng và không có kết quả in ra luồng ra chuẩn.
- 600 trường hợp ngẫu nhiên bổ sung, đáp án đối chiếu bằng mô hình Python độc lập.
- Cả 10 lời giải biên dịch và chạy được với C++11, C++14, C++17, C++20.
- Verifier từ chối các dữ liệu không hợp lệ; checker chấp nhận và từ chối đúng các trường hợp kiểm tra.
- Mỗi lần chạy lời giải dùng giới hạn 1 giây. Thời gian lớn nhất quan sát trong lượt chạy thành công là khoảng 0,286 giây, tính cả khởi động tiến trình trên máy cục bộ.
- Kiểm tra lại cấu trúc cả 10 đề, ví dụ hex, kiểu dữ liệu cơ bản, cấu hình upload và đủ 500 hash của các tệp đầu vào/đầu ra đều khớp.
- Công cụ chuyển ví dụ hex tạo đúng các byte của tệp mẫu thực tế.
- Sau khi chuyển sang bố trí struct mặc định, đã sinh lại các tệp nhị phân, ví dụ và hash. Ba trường hợp bổ sung xác nhận byte đệm căn chỉnh có thể chứa giá trị bất kỳ mà không làm thay đổi kết quả.

Sau khi cập nhật tài liệu API và cấu hình upload:

- Cả 10 `[upload]` có `io_method = 'file'`, `io_input_file`, `io_output_file` đúng tên trong đề.
- 60 kiểm thử upload với máy chủ giả lập cục bộ đều đạt, gồm xác nhận ba trường mới được gửi trong POST/PATCH và không bị đưa vào manifest testcase.
- 6 kiểm thử công cụ chạy lời giải đều đạt, gồm file I/O, giữ nguyên byte, giới hạn thời gian, thiếu đầu ra và chế độ luồng chuẩn.
- Đã sinh lại đáp án bằng công cụ chung `Problem.make_outputs` cho cả 250 test A109, chạy checker và đối chiếu hash thành công; không cần thay đổi hash dữ liệu.

Các bài A109000003, A109000004, A109000006, A109000007 và A109000009 đã bỏ struct chỉ chứa số lượng bản ghi, đọc/ghi trực tiếp một số nguyên `int` ở đầu tệp. Đã sinh lại và kiểm tra toàn bộ 250 test chính cùng 600 trường hợp ngẫu nhiên bổ sung; các byte dữ liệu, ví dụ và hash không thay đổi.

Đã kiểm tra chỉ đề A109000001 có hướng dẫn mở, đọc/ghi tệp nhị phân; các đề còn lại trình bày gọn theo A109000004. Khai báo struct trong mỗi đề khớp lời giải tham khảo. Cả 250 test chính và 600 trường hợp ngẫu nhiên bổ sung đều đạt, dữ liệu và hash vẫn khớp.

Không xuất HTML và chưa tải bài lên máy chủ.

## Kiểm tra trực tiếp tmath cho lỗi 1175/1223

- Tệp `random_00.in` trong ZIP trên máy chủ có hash khớp dữ liệu cục bộ, dài 22.248 byte và có tổng đúng 1223.
- Đã tái hiện kết quả 1175 bằng chính hàm chuẩn hóa của DMOJ đang chạy, với cờ dữ liệu nhị phân tắt.
- Đã sao lưu cấu hình và bật `binary_data: true` cho 9 bài A109 hiện có trên máy chủ.
- Đã biên dịch C++11 và chạy thành công cả 225 test của 9 bài bằng đầu vào do chính bộ nạp dữ liệu DMOJ cung cấp. Test `random_00` của bài 1 cho 1223.
- Bộ nạp của cả ba container `epsilon`, `gamma`, `beta` giữ nguyên hash đầu vào bài 1 sau sửa.
- Không thay đổi test, đáp án hay hash để khớp với dữ liệu đã bị biến đổi. Chưa chấm lại các bài nộp cũ.

## Hỗ trợ binary_data trong lệnh -u

Đã cập nhật theo phiên bản PROBLEM_IMPORT_API.md có `binary_data` ở cấp manifest testcase:

- Cả 10 bài đã đặt `[upload].binary_data = true`; cờ gửi trong manifest và không bị đưa vào JSON tạo/cập nhật đề.
- 67 kiểm thử upload đều đạt, gồm CLI `-u`, `--skip-statement`, giá trị true/false, kiểm tra boolean nghiêm ngặt, ưu tiên manifest riêng, checker riêng và bảo toàn byte trong ZIP.
- 10 kiểm thử công cụ chạy/sinh dữ liệu đều đạt, gồm bỏ chuẩn hóa xuống dòng Windows khi dữ liệu nhị phân và vẫn giữ xử lý văn bản khi cờ tắt.
- Đã sinh lại, kiểm tra đầu vào, chạy lời giải/checker, đóng gói và đối chiếu toàn bộ 250 cặp test A109. Cả 500 hash vẫn khớp; `random_00` của bài 1 giữ đáp án 1223.
- Lần cập nhật này chỉ kiểm thử upload với máy chủ giả lập/công cụ ghi nhận cục bộ; chưa thực hiện upload thật lên tmath.
