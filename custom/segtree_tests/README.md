# Kiểm thử nhóm segment tree cơ bản

| Mã bài | Nội dung |
| --- | --- |
| segtree020 | Min, max và độ chênh lệch nhiệt độ |
| segtree010 | Đảo trạng thái một đèn, đếm đèn sáng |
| segtree050 | Đếm số chẵn và số lẻ |
| segtree060 | Giá trị lớn nhất và số lần xuất hiện |
| segtree051 | Dấu của tích |
| segtree090 | Số cụm màu liên tiếp |

Từ thư mục gốc dự án, chạy toàn bộ nhóm:

```sh
python3 custom/segtree_tests/check.py
```

Hoặc chạy riêng một bài:

```sh
python3 custom/segtree090/tests/check.py
```

Khi chủ động thay đổi bộ sinh hoặc đáp án chuẩn, dùng `--update-hashes` để cập nhật `hash.json`. Lần chạy thông thường chỉ đối chiếu hash và báo lỗi nếu khác.

Quy trình gọi riêng các bước của `Problem`, không gọi `--dev`, `--test` hoặc xuất HTML. Không cần thư viện xuất HTML. Các chương trình C++ được biên dịch bằng cấu hình của dự án; thư viện `testlib.h` và bộ sinh số ngẫu nhiên có sẵn trong `common/`.

Mỗi bài có 36 test: 2 ví dụ, 12 trường hợp biên, 8 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Có test với $N=Q=200000$, đoạn một phần tử, đoạn toàn dãy, kích thước không phải lũy thừa của hai, truy vấn không cập nhật và cập nhật không truy vấn. Các trường hợp chuyên biệt bao gồm số âm, số 0, cực trị trùng nhau, cập nhật cùng giá trị, đảo đèn lặp lại và nhập/tách cụm màu.

Ngoài kiểm tra đầu vào và chạy lời giải qua checker trên mọi test, quy trình còn:

- Đối chiếu toàn bộ đáp án bằng lời giải độc lập trong `oracle.cpp`: chia căn cho min/max và cực đại kèm số lần, Fenwick đếm trạng thái cho các bài còn lại. Bài màu dùng công thức $1+$ số cặp ô kề nhau khác màu trong đoạn.
- Đối chiếu các test nhỏ bằng cách duyệt trực tiếp mảng.
- Duyệt mọi mảng độ dài từ 1 đến 4 trên bảng giá trị nhỏ, thử cập nhật từng vị trí và truy vấn mọi đoạn; thêm 150 test ngẫu nhiên mỗi bài. Tổng cộng 1.530 trường hợp bổ sung cho cả nhóm.
- Kiểm tra verifier từ chối dữ liệu vượt giới hạn, sai chỉ số, đảo ngược đoạn, thiếu hoặc thừa dữ liệu.
- Kiểm tra checker chấp nhận đáp án đúng với khoảng trắng khác nhau, từ chối đáp án sai, thiếu, thừa và không đúng định dạng; bao gồm trường hợp không có đầu ra.
- Đối chiếu cấu trúc đề, bảng subtask, nội dung ví dụ, tính tái lập của bộ sinh và `hash.json`.

Các tệp `params.h`, chương trình đã biên dịch và thư mục `in/`, `out/` là sản phẩm sinh tự động. Mã nguồn bộ sinh, ví dụ, lời giải và `hash.json` được lưu để tái tạo bộ test.
