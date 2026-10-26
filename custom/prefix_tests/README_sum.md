# PREFIX10–PREFIX19 — Tổng tiền tố cơ bản

Các bài chỉ dùng tổng tiền tố, không cần prefix min/max. Không thêm mục Subtask.

| Mã bài | Tên bài | Trọng tâm |
| --- | --- | --- |
| PREFIX10 | Đếm số chẵn | Tổng tiền tố của mảng đánh dấu |
| PREFIX11 | Tổng xen kẽ | Đổi dấu theo vị trí, điều chỉnh dấu đầu đoạn |
| PREFIX12 | Đếm chữ trong đoạn | 26 mảng tổng tiền tố đếm ký tự |
| PREFIX13 | Tổng có trọng số | Tổng tiền tố của giá trị và chỉ số nhân giá trị |
| PREFIX14 | Tổng hình chữ nhật | Tổng tiền tố hai chiều |
| PREFIX15 | Đoạn trên vòng tròn | Nhân đôi dãy và lấy tổng đoạn |
| PREFIX16 | Đường đi lên xuống | Tổng chi phí cạnh giữa các trạm |
| PREFIX17 | Các nhóm ký tự | Đếm lần đổi ký tự trong chuỗi con |
| PREFIX18 | Tổng tích lũy nhiều ngày | Tổng tiền tố hai lần |
| PREFIX19 | Chia thành ba phần bằng tổng | Đếm điểm cắt với tổng tiền tố bằng một phần ba tổng |

Mỗi bài có đề `task.md`, hai ví dụ, hướng dẫn `solution.md`, lời giải C++, bộ sinh, verifier, checker và `hash.json`. Toàn bộ phần `[upload]` trong `info.toml` được sao chép từ PREFIX09, gồm `time_limit = 0.25`, nhóm `03`, lớp `C`, loại `dp_day_so`, danh sách ngôn ngữ và `partial = true`. Đây là cấu hình để upload; quy trình kiểm tra không gọi API upload. Lời giải dùng bộ đọc/ghi đệm trong `sol/fast_io.h` để đáp ứng giới hạn thời gian chặt.

Giới hạn dãy và số truy vấn là 200000. PREFIX14 có tối đa 700 hàng và 700 cột. PREFIX13 và PREFIX18 giới hạn giá trị mỗi phần tử ở 1000000 để các tổng có trọng số và tổng số dư không vượt miền số nguyên 64 bit có dấu.

## Sinh dữ liệu và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check_sum.py --generate
```

Quy trình biên dịch các chương trình, sinh 22 test mỗi bài (hai ví dụ và 20 test theo seed), xác thực đầu vào, tạo đáp án, chạy checker và đối chiếu mọi test với lời giải Python độc lập. Ngoài ra có vét cạn các dãy nhỏ, 160 trường hợp ngẫu nhiên mỗi bài và các phép thử verifier/checker với dữ liệu sai, thiếu/thừa đầu ra và khoảng trắng. Sau cùng ghi `hash.json`, sinh lại đầu vào và xác nhận hash không đổi. Không xuất HTML.

Các test gồm kích thước nhỏ nhất, giá trị 0, giá trị âm, cực trị, dãy xen kẽ, ký tự giống nhau, ký tự không xuất hiện, bảng một hàng/một cột, đoạn một phần tử, đoạn cả dãy, đoạn qua điểm nối vòng, truy vấn đi ngược chiều và chia ba khi tổng bằng 0. Mỗi bài có bốn test kích thước tối đa, gồm một test ngẫu nhiên lớn.

Kiểm tra lại dữ liệu và chương trình đã sinh:

```sh
python3 custom/prefix_tests/check_sum.py
```

Chọn một bài hoặc chạy từ thư mục bài:

```sh
python3 custom/prefix_tests/check_sum.py --problem prefix19 --generate
python3 custom/prefix19/tests/check.py
```
