# Bộ bài PREFIX00–PREFIX09

| Mã bài | Tên bài | Kỹ thuật chính |
| --- | --- | --- |
| PREFIX00 | Kho hàng theo ngày | Tổng tiền tố, truy vấn đoạn |
| PREFIX01 | Ngày lập kỷ lục | Min/max tiền tố, so sánh nghiêm ngặt |
| PREFIX02 | Điểm cân bằng | Tổng tiền tố và tổng toàn dãy |
| PREFIX03 | Mua rồi bán | Min tiền tố trước ngày bán |
| PREFIX04 | Bình năng lượng | Min của tổng tiền tố |
| PREFIX05 | Đoạn lợi nhuận tốt nhất | Tổng tiền tố trừ min tiền tố |
| PREFIX06 | Chia đội công bằng | Max tiền tố và min hậu tố |
| PREFIX07 | Ca làm có thời lượng tối thiểu | Min tiền tố với điều kiện độ dài |
| PREFIX08 | Nhật ký chia hết | Phần dư tổng tiền tố và tần suất |
| PREFIX09 | Trạm xuất phát trên vòng tròn | Nhân đôi dãy, tổng tiền tố, deque lấy min |

Mỗi bài có hai ví dụ và 24 test sinh xác định bằng seed. Chỉ thêm mục Subtask khi người dùng yêu cầu. Giới hạn chung là `N <= 200000`; các tổng và số đoạn cần số nguyên 64 bit.

## Sinh và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check.py --generate
```

Quy trình biên dịch lời giải, bộ sinh, verifier và checker; sinh và xác thực đầu vào; tạo đầu ra và chạy checker; so sánh toàn bộ 26 test mỗi bài với lời giải Python độc lập; đối chiếu vét cạn các dãy nhỏ và 200 trường hợp ngẫu nhiên mỗi bài; thử đầu vào sai, đầu ra sai, thiếu/thừa kết quả và định dạng khoảng trắng; tạo `hash.json`, sinh lại đầu vào và đối chiếu hash. Không xuất HTML.

Kiểm tra lại bộ dữ liệu đã sinh và các chương trình đã biên dịch:

```sh
python3 custom/prefix_tests/check.py
```

Có thể chọn một bài:

```sh
python3 custom/prefix_tests/check.py --problem prefix09 --generate
python3 custom/prefix09/tests/check.py
```

Bộ sinh có các trường hợp nhỏ nhất, dãy bằng nhau, toàn 0, toàn dương/âm, xen kẽ hai cực trị, tăng/giảm, và phần tử cực trị ở đầu/cuối. Tám test mỗi bài có kích thước tối đa. Với PREFIX00 có truy vấn cả dãy và một phần tử; PREFIX07 có `K = 1`, `K = N` và độ dài trung gian; PREFIX08 có `M = 1` và `M = 200000`; PREFIX09 có mọi trạm hợp lệ, không trạm hợp lệ và các trường hợp phải đi qua điểm nối vòng.

Bộ bài tổng tiền tố cơ bản tiếp theo: [PREFIX10–PREFIX19](README_sum.md).

Bộ bài đếm phần tử thỏa điều kiện: [PREFIX001–PREFIX009](README_count.md).
