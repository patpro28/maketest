# Tổng các phần tử thỏa điều kiện trong đoạn

Mười bài cùng một dạng: giữ nguyên giá trị phần tử thỏa điều kiện, thay phần tử còn lại bằng 0, rồi dùng tổng tiền tố trả lời truy vấn [L,R]. Mức độ phù hợp để học tiếp sau bộ đếm phần tử thỏa điều kiện.

Theo yêu cầu, mã thư mục dùng `dppsum011`–`dppsum020`, còn nhãn trong đề, lời giải và trường `title` của `info.toml` dùng `PREFIX011`–`PREFIX020`.

| Mã thư mục | Nhãn | Nội dung |
| --- | --- | --- |
| dppsum011 | PREFIX011 | Tổng các số chẵn |
| dppsum012 | PREFIX012 | Tổng các số dương |
| dppsum013 | PREFIX013 | Tổng các số âm |
| dppsum014 | PREFIX014 | Tổng các số chia hết cho K cố định |
| dppsum015 | PREFIX015 | Tổng các số thuộc khoảng [U,V] cố định |
| dppsum016 | PREFIX016 | Tổng các số chính phương |
| dppsum017 | PREFIX017 | Tổng các số nguyên tố |
| dppsum018 | PREFIX018 | Tổng các số đối xứng |
| dppsum019 | PREFIX019 | Tổng các số có tổng chữ số bằng K cố định |
| dppsum020 | PREFIX020 | Tổng các số chứa chữ số 7 |

Mỗi bài có `task.md`, hai ví dụ, `solution.md`, lời giải C++ độc lập, bộ sinh, verifier, checker, `hash.json` và cấu hình upload theo PREFIX09, với `types = ['dp_prefix_sum', 'dp_sequence']`. Không có Subtask và không xuất HTML. Không gọi API upload trong quy trình kiểm tra.

Giới hạn N,Q là 200000. Tổng có thể âm và trị tuyệt đối có thể đạt 200000000000000; lời giải cần số nguyên 64 bit. Các phần tử trùng giá trị ở các vị trí khác nhau đều được cộng riêng. Mỗi phần tử chỉ đóng góp một lần dù chứa nhiều chữ số 7. Với bài nguyên tố, giá trị phần tử không vượt 1000000.

## Sinh và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check_conditional_sum.py --generate
```

Quy trình biên dịch lời giải, bộ sinh, verifier và checker; sinh 22 test mỗi bài; xác thực toàn bộ đầu vào; tạo đầu ra và chạy checker. Lời giải Python độc lập lưu các vị trí thỏa điều kiện, cộng dồn trọng số tại các vị trí đó và dùng tìm kiếm nhị phân để trả lời truy vấn. Mỗi bài còn được đối chiếu trên 120 dãy vét cạn nhỏ và 160 trường hợp ngẫu nhiên bằng cách cộng trực tiếp các phần tử của từng đoạn.

Các phép thử verifier/checker gồm dữ liệu sai giới hạn, tham số không hợp lệ, đoạn sai, thiếu/thừa dữ liệu, đáp án sai, thiếu/thừa số và định dạng khoảng trắng. Cuối cùng ghi `hash.json`, sinh lại dữ liệu với cùng seed và xác nhận hash không thay đổi. Bộ kiểm tra cũng xác nhận nhãn PREFIX, cấu hình upload và cấu trúc đề theo mẫu knapsack.

Mỗi bài có bốn test kích thước tối đa và ít nhất một đáp án vượt miền số nguyên 32 bit có dấu. Các test bao phủ tổng âm, số 0, đoạn một phần tử, cả dãy, biên giá trị, K bằng 1 hoặc cực đại, khoảng chỉ chứa một giá trị, số sát chính phương, 0/1 không nguyên tố, số đối xứng lớn và số chứa nhiều chữ số 7.

Kiểm tra lại dữ liệu và chương trình đã sinh:

```sh
python3 custom/prefix_tests/check_conditional_sum.py
```

Chọn riêng một bài:

```sh
python3 custom/prefix_tests/check_conditional_sum.py --problem dppsum016 --generate
python3 custom/dppsum016/tests/check.py
```
