# Kiểm thử và phân điểm bộ A3

Mỗi bài có **40 test chấm điểm**, mỗi test **2,5 điểm**, tổng **100 điểm**. Các ví dụ trong đề có **0 điểm** và không đưa vào ZIP chấm điểm.

| Bài | Subtask 1 | Subtask 2 | Subtask 3 |
| --- | --- | --- | --- |
| MATHA3 | 24 test, 60 điểm | 12 test, 30 điểm | 4 test, 10 điểm |
| STRINGA3 | 20 test, 50 điểm | 12 test, 30 điểm | 8 test, 20 điểm |
| BS13C | 20 test, 50 điểm | 20 test, 50 điểm | — |
| DPUPSTAIR03C | 12 test, 30 điểm | 8 test, 20 điểm | 20 test, 50 điểm |
| BS52C | 40 test, 100 điểm | — | — |

Tên file xác định nhóm: `subtask1_00.in`, `subtask1_01.in`, … thuộc subtask 1; tương tự cho các nhóm khác. Output có cùng tên và đuôi `.out`. Mỗi test được gán đúng một nhóm, dù có thể thỏa ràng buộc của nhiều nhóm.

Trong thư mục mỗi bài:

- `scoring.md`: bảng tên test, số lượng và số điểm từng nhóm để người ra đề kiểm tra.
- `scoring.json`: danh sách cụ thể input/output của từng nhóm và cấu hình mỗi test 2,5 điểm, ví dụ 0 điểm.
- `<mã bài>.zip`: chỉ gồm đúng 40 cặp input/output chấm điểm; khi nhập vào hệ thống chấm, đặt mỗi test 2,5 điểm trên thang 100.
- `hash.json`: đối chiếu cả 40 test chấm điểm và các ví dụ lưu trong kho.

Đây là cấu hình chấm cộng điểm từng test. Các file mô tả phân điểm không tự thay đổi thiết lập trên một hệ thống chấm bên ngoài.

Chạy tại thư mục gốc dự án bằng Python 3 và trình biên dịch C++17:

```sh
python3 custom/a3_tests/run.py --build
```

Quy trình sinh input/output, kiểm tra input bằng verifier, chấm cả hai lời giải bằng checker, đối chiếu `hash.json`, tạo bảng phân điểm và đóng gói ZIP. Các bước được gọi trực tiếp qua `Problem`, không xuất HTML.

Sau bước sinh, chương trình kiểm tra cấu trúc đề và ví dụ, tỉ lệ subtask, số lượng và ràng buộc của test từng nhóm, gán nhóm duy nhất, giới hạn 40 test chấm điểm mỗi bài, tổng 100 điểm và nội dung ZIP. Chương trình còn kiểm tra checker từ chối đáp án sai/thừa/thiếu/không phải số, verifier từ chối input sai và đối chiếu hai lời giải với vét cạn độc lập. Riêng bài lát hành lang được xét tất cả tập ô đặt chậu cây với N từ 1 đến 7 và mọi số gạch đôi có thể dùng, kể cả yêu cầu không thể đạt.

Nếu đã biên dịch và sinh test, chỉ chạy kiểm tra hồi quy:

```sh
python3 custom/a3_tests/run.py
```

Khi chủ động thay đổi bộ sinh test và muốn cập nhật manifest sau khi xem lại thay đổi:

```sh
python3 custom/a3_tests/run.py --build --update-hashes
```
