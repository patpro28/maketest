# Kiểm thử DPCSTR153

Bài thuộc nhóm khó của dải `dpcstr100–199`: dãy con chung không bắt buộc liên tiếp. Lời giải chính dùng mặt nạ của xâu ngắn nhất và đảo biến thành vị trí khớp sớm nhất trong từng xâu còn lại.

## Chạy kiểm tra

Từ thư mục gốc dự án:

```sh
python3 custom/dpcstr153/tests/check.py
```

Chỉ khi chủ động thay đổi dữ liệu và cần cập nhật mã băm:

```sh
python3 custom/dpcstr153/tests/check.py --update-hashes
```

Quy trình sinh và xác thực đầu vào, tạo đáp án, kiểm tra hai thuật toán độc lập, verifier, checker, cấu hình upload và `hash.json`. Không xuất HTML hoặc upload.

## Bộ dữ liệu

Có 35 cặp test: 3 ví dụ, 12 biên, 8 nhỏ, 6 ngẫu nhiên và 6 lớn. Các trường hợp chính:

- Xâu ngắn nhất ở đầu, giữa hoặc cuối danh sách; hai xâu hoặc đủ 40 xâu.
- Không có ký tự chung; chỉ có một ký tự chung; đáp án là toàn bộ xâu ngắn nhất.
- Chữ lặp nhiều lần, số lần xuất hiện khác nhau giữa các xâu. Không cho dùng lại cùng một vị trí để khớp nhiều ký tự.
- Các xâu chỉ có dãy con chung không liên tiếp, phân biệt với đoạn con chung.
- Hai LCS khác nhau của cùng một cặp xâu: `ab`, `ba`, `a` và `ab`, `ba`, `b`, để tránh chỉ giữ một LCS rồi ghép tiếp.
- Các cặp xâu có ký tự chung nhưng không có chữ chung của toàn bộ nhóm, như `ab`, `bc`, `ca`.
- Mặt nạ có nhiều bit, thứ tự chữ khác nhau, bảo đảm phép bỏ ký tự cuối tương ứng với bit cao nhất.

Sáu test lớn đều có tổng độ dài 100.000 và độ dài xâu ngắn nhất là 20. Năm test có $K=40$; test cuối có $K=2$ với một xâu dài 99.980 ký tự. Các đáp án được biết theo cấu trúc:

| Test | Cấu trúc chính | Đáp án |
| --- | --- | --- |
| max_00 | Xâu mốc gồm 20 chữ khác nhau, có nguyên xâu mốc trong mọi xâu còn lại | 20 |
| max_01 | Tất cả chỉ gồm chữ `a`, xâu mốc nằm cuối | 20 |
| max_02 | Các xâu đầu chứa xâu mốc; xâu cuối chỉ có 20 chữ mốc theo thứ tự đảo và các chữ `z` | 1 |
| max_03 | Xâu cuối chỉ có chữ `z`, không có trong xâu mốc | 0 |
| max_04 | Xâu mốc có 20 chữ `a`, mỗi xâu khác chỉ có 10 chữ `a` | 10 |
| max_05 | Xâu đầu dài 99.980, xâu mốc 20 ký tự ở cuối | 20 |

Các test `max_00`, `max_01`, `max_02`, `max_03` giữ nhiều hoặc toàn bộ $2^{20}$ mặt nạ khả thi qua nhiều bản ghi trước khi có thể loại ứng viên, nhằm kiểm tra quy mô DP thật sự.

## Đối chiếu độc lập

`tests/oracle.cpp` không dùng bảng DP theo mặt nạ. Nó tìm kiếm các dãy ứng viên theo thứ tự chọn vị trí trong xâu ngắn nhất, đồng thời giữ vị trí khớp trong tất cả các xâu khác; cắt nhánh bằng số vị trí còn lại. Kết quả của mọi test đã sinh đều được đối chiếu với oracle.

Vét cạn trực tiếp 23 test ví dụ/biên/nhỏ bằng cách dựng các nội dung dãy con, rồi kiểm tra thứ tự bằng cách quét từng xâu. Kiểm tra bổ sung gồm mọi cặp và mọi bộ ba xâu nhị phân dài từ 1 đến 3, các nhóm ngẫu nhiên, đảo thứ tự bản ghi và các trường hợp đặc trưng.

Verifier được thử với $K$ ngoài cận, xâu rỗng, sai chữ cái, thiếu/thừa dữ liệu, tổng độ dài vượt cận và không có xâu dài tối đa 20. Checker được thử với đáp án đúng/sai, ngoài khoảng 0–20, rỗng hoặc dư token. Bộ sinh được chạy lại với từng seed để đối chiếu tính tái lập.

## Hiệu năng và cấu hình

Lời giải được biên dịch theo C++11 và chạy với giới hạn 0,5 giây trên mỗi test cục bộ. Không suy ra hiệu năng ở các ngôn ngữ khác chỉ từ việc chúng nằm trong danh sách ngôn ngữ được phép.

Cấu hình `[upload]` giữ `group = '03'`, `classes = 'C'`, `types = ['dp_common_substring']`, `partial = true`, cùng danh sách ngôn ngữ của bộ bài trước. Bài chỉ in độ dài nên dùng checker `standard` khi upload.

Kết quả lần kiểm tra gần nhất được lưu trong `tests/results.md`.
