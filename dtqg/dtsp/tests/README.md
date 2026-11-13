# Kiểm thử DTSP

Nguồn: `/Users/patpro28/Downloads/Thay Dong/sp.pdf`; SHA-256: `eee3d9495809230fa23752ba5d77a73499dfc86db2e37182ee61b68dbe095df7`. Đã đối chiếu bản trích xuất và hình trang. Những thay đổi giới hạn, chỗ làm rõ nội dung, thứ tự luyện tập và thuật toán tham chiếu nằm tại [tài liệu chung](../../thaydong_tests/README.md).

Có 26 test chính thức, gồm hai ví dụ nguồn, 16 test sinh ban đầu và tám test mới bắt cách tham lam ưu tiên nắp 3 điểm. Các bộ sinh dùng seed cố định. Ví dụ có trọng số 0, mỗi test sinh có trọng số 1, tổng điểm bài là 100. Không chia subtask và không dùng manifest điểm riêng. Mỗi file input không vượt 1.000.000 byte.

Chạy từ thư mục gốc:

```sh
python3 dtqg/thaydong_tests/check.py --problem dtsp
```

Sau khi chủ động thay đổi dữ liệu, thêm `--update-hashes`. Các bước sinh, xác thực dữ liệu, sinh đáp án, checker và đối chiếu hash được gọi riêng; không xuất HTML.

## Kết quả

Đạt 26 test chính thức và 80 trường hợp nhỏ độc lập; 7 đầu vào sai bị loại, 16 tình huống checker và 1 lượt nhập/xuất tệp nguồn đạt. Toàn bộ 52 mục hash khớp.

Input lớn nhất: 20 byte. Thời gian lời giải mẫu lớn nhất đo được: 0.0781 giây. Số đo phụ thuộc máy chạy; giới hạn thời gian thực tế nằm trong `info.toml`.

## Bắt cách tham lam ưu tiên nắp 3 điểm

Code học sinh được lưu tại `tests/wrong_greedy.cpp`, giữ nguyên thuật toán, chỉ thay `bits/stdc++.h` bằng các include chuẩn để biên dịch trên máy hiện tại. Bộ 18 test ban đầu chưa bắt được code này. Nhóm `gen/greedy_trap.cpp` bổ sung tám phản ví dụ, mỗi test có trọng số 1 như các test sinh khác:

| Test | a b c s | Code học sinh | Đáp án |
| --- | --- | ---: | ---: |
| `greedy_trap_00` | 0 4 2 7 | 1 | 2 |
| `greedy_trap_01` | 0 6 2 9 | 1 | 2 |
| `greedy_trap_02` | 0 4 4 10 | 1 | 2 |
| `greedy_trap_03` | 0 4 6 13 | 1 | 2 |
| `greedy_trap_04` | 1 4 4 7 | 2 | 3 |
| `greedy_trap_05` | 1 4 7 10 | 2 | 3 |
| `greedy_trap_06` | 0 270 135 7 | 118 | 135 |
| `greedy_trap_07` | 1 270 135 7 | 118 | 135 |

Ở test đầu, code lấy hai nắp 3 điểm rồi thêm một nắp 2 điểm, nhận một gấu với nhóm 8 điểm. Ba nắp 2 điểm còn lại chỉ có 6 điểm. Cách tối ưu dùng hai nhóm, mỗi nhóm một nắp 3 điểm và hai nắp 2 điểm, đúng 7 điểm. Tổng 14 điểm cũng chứng minh không thể có hơn hai nhóm.

Ở test lớn `greedy_trap_06`, chia được 135 nhóm 3+2+2, dùng hết nắp và nhận 135 gấu, trong khi code học sinh chỉ nhận 118. Các test có đủ ba loại nắp cũng loại được code, tránh chỉ dựa vào trường hợp số lượng nắp 1 bằng 0.

Chương trình kiểm tra biên dịch code học sinh và chạy trực tiếp trên cả tám test, yêu cầu checker trả WA. Mọi đáp án được so với cả lời giải mẫu lẫn oracle liệt kê các nhóm đổi tối thiểu. Tất cả 18 cặp input/output cũ được đối chiếu hash trước/sau và giữ nguyên nội dung.
