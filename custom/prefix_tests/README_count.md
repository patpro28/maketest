# PREFIX001–PREFIX009 — Đếm phần tử thỏa điều kiện trong đoạn

Các mã dùng đúng ba chữ số, riêng biệt với `prefix01`–`prefix09`. Cả chín bài chỉ yêu cầu đếm số phần tử, dùng mảng đánh dấu 0/1 và tổng tiền tố. Không có Subtask.

| Mã bài | Tên bài | Điều kiện |
| --- | --- | --- |
| PREFIX001 | Đếm số dương | Lớn hơn 0 |
| PREFIX002 | Đếm số âm | Nhỏ hơn 0 |
| PREFIX003 | Đếm số chia hết | Chia hết cho K cố định |
| PREFIX004 | Đếm số trong khoảng giá trị | Thuộc khoảng đóng [U,V] cố định |
| PREFIX005 | Đếm số chính phương | Là bình phương của số nguyên không âm |
| PREFIX006 | Đếm số nguyên tố | Là số nguyên tố, giá trị không vượt 1000000 |
| PREFIX007 | Đếm số đối xứng | Biểu diễn thập phân đối xứng |
| PREFIX008 | Đếm số có tổng chữ số bằng K | Tổng chữ số bằng K cố định |
| PREFIX009 | Đếm số chứa chữ số 7 | Có ít nhất một chữ số 7 |

Mỗi bài có `task.md`, hai ví dụ, `solution.md`, lời giải C++ độc lập, bộ sinh test, verifier, checker, `info.toml` và `hash.json`. Số phần tử và số truy vấn đều không vượt 200000. Cấu hình `[upload]` được sao chép nguyên từ PREFIX09; quá trình tạo và kiểm tra không gọi API upload.

## Sinh và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check_count.py --generate
```

Quy trình biên dịch lời giải, bộ sinh, verifier và checker; sinh 22 test mỗi bài (hai ví dụ và 20 test theo seed); xác thực đầu vào; sinh đáp án và chạy checker; đối chiếu mọi test với lời giải Python dùng danh sách vị trí và tìm kiếm nhị phân. Sau đó kiểm tra vét cạn 120 dãy nhỏ và 160 trường hợp ngẫu nhiên mỗi bài bằng cách duyệt trực tiếp từng đoạn. Bài nguyên tố dùng phép thử chia trực tiếp ở kiểm tra nhỏ, sàng độc lập ở dữ liệu lớn. Các bài chữ số dùng biểu diễn chuỗi để kiểm tra lời giải tách chữ số C++.

Bộ kiểm tra còn thử đầu vào sai giới hạn, sai tham số, đoạn không hợp lệ, dữ liệu thiếu/thừa; thử checker với đầu ra đúng, khoảng trắng khác nhau, đáp án sai, thiếu/thừa số và ký tự không phải số. Cuối cùng ghi `hash.json`, sinh lại đầu vào và xác nhận hash không đổi. Không xuất HTML.

Bốn test mỗi bài đạt kích thước tối đa. Các test bao phủ số 0, số âm khi được phép, giá trị cực đại, giá trị lặp lại, hai biên U/V, số sát chính phương lớn nhất trong miền, số nguyên tố lớn, 0/1 không nguyên tố, số đối xứng có chữ số 0, K bằng 0/81 ở bài tổng chữ số và số chứa nhiều chữ số 7. Truy vấn có cả dãy, một phần tử, vị trí đầu/cuối và đoạn ngẫu nhiên.

Kiểm tra lại dữ liệu và chương trình đã sinh:

```sh
python3 custom/prefix_tests/check_count.py
```

Chọn riêng một bài:

```sh
python3 custom/prefix_tests/check_count.py --problem prefix005 --generate
python3 custom/prefix005/tests/check.py
```
