# TDIFF000–TDIFF009 — Kiểm thử mảng hiệu cơ bản

| Mã bài | Đề bài |
| --- | --- |
| TDIFF000 | [Tính mảng hiệu](../tdiff000/task.md) |
| TDIFF001 | [Khôi phục dãy số](../tdiff001/task.md) |
| TDIFF002 | [Khôi phục từ một mốc](../tdiff002/task.md) |
| TDIFF003 | [Các đoạn bằng nhau](../tdiff003/task.md) |
| TDIFF004 | [Cộng vào cuối dãy](../tdiff004/task.md) |
| TDIFF005 | [Đổi một phần tử](../tdiff005/task.md) |
| TDIFF006 | [Hai đầu mút](../tdiff006/task.md) |
| TDIFF007 | [Dãy sau một lần cộng](../tdiff007/task.md) |
| TDIFF008 | [Hiệu tại vị trí được hỏi](../tdiff008/task.md) |
| TDIFF009 | [Tìm phép cộng đoạn](../tdiff009/task.md) |

Mỗi bài có hai ví dụ và 18 tệp sinh bằng seed. Các tệp bao gồm nhiều bộ test kích thước nhỏ, dữ liệu ngẫu nhiên và trường hợp đạt giới hạn của số bộ test hoặc tổng kích thước. Dữ liệu có dãy một phần tử, số âm, số 0, số lớn, phép cộng ở hai đầu dãy và các kết quả vượt 32 bit. TDIFF008 có thêm các tệp đạt giới hạn tổng số câu hỏi và lặp lại câu hỏi. TDIFF009 có các cặp dãy bằng nhau, các phép cập nhật hợp lệ và các cặp dãy không thể biến đổi trong một lần.

Chạy từ thư mục gốc của kho bằng Python và trình biên dịch C++ của dự án. Có thể đặt biến môi trường `CXX` để chọn trình biên dịch.

```sh
python3 custom/tdiff_tests/check.py
python3 custom/tdiff_tests/check.py --problem 8
```

Tập lệnh biên dịch, sinh dữ liệu, chạy verifier, kiểm tra từng lời giải trong giới hạn 1 giây và so sánh đáp án với mô hình Python. Các bài cập nhật được đối chiếu bằng cách khôi phục dãy rồi cập nhật trực tiếp. TDIFF009 được đối chiếu bằng cách lấy hai vị trí sai khác ngoài cùng rồi thử áp dụng phép cộng. Verifier được kiểm tra với đầu vào sai, gồm cả các tệp vượt giới hạn tổng dù kích thước từng bộ hợp lệ. Checker được kiểm tra với kết quả đúng và kết quả sai, thiếu hoặc thừa số.

Mặc định tập lệnh đối chiếu các tệp `hash.json` đã lưu. Dùng `--update-hashes` khi chủ động sửa dữ liệu hoặc định dạng kết quả. Quy trình này chỉ sinh dữ liệu và đáp án cục bộ.
