# Bộ nền tảng KNAPSACK00–KNAPSACK04

Năm bài rèn quy hoạch động knapsack 0–1: mỗi món đồ hoặc vị trí chỉ được chọn tối đa một lần. Mục tiêu có thể bằng 0; tất cả trọng lượng và các số trong dãy đều dương.

| Mã | Bài | Trạng thái cần học |
| --- | --- | --- |
| [knapsack00](../knapsack00/task.md) | Chọn đồ vào túi | Giá trị lớn nhất với trọng lượng không vượt sức chứa |
| [knapsack01](../knapsack01/task.md) | Chọn các số có tổng cho trước | Khả năng đạt đúng một tổng |
| [knapsack02](../knapsack02/task.md) | Chọn ít thẻ nhất | Số phần tử ít nhất để đạt đúng tổng |
| [knapsack03](../knapsack03/task.md) | Đếm số cách chọn đạt đúng tổng | Đếm tập chỉ số, lấy modulo $10^9+7$ |
| [knapsack04](../knapsack04/task.md) | Chọn đồ lấp đầy túi | Giá trị lớn nhất với trọng lượng đúng bằng sức chứa |

KNAPSACK00 và KNAPSACK04 có cùng dữ liệu ở ví dụ đầu nhưng đáp án khác nhau, giúp phân biệt hai cách hiểu về sức chứa. Các đề quy định rõ cách xử lý tập rỗng và những phần tử trùng giá trị.

Mỗi thư mục có đề `task.md`, lời giải và chứng minh `solution.md`, lời giải C++ `sol/correct.cpp`, `info.toml`, bộ kiểm tra đầu vào/đầu ra, các bộ sinh test và `hash.json`. Không xuất HTML.

Mỗi bài có 32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Tổng cộng 160 cặp test. Dữ liệu bao phủ mục tiêu 0, không có nghiệm, một món không được lấy nhiều lần, các phần tử trùng nhau, tổng giá trị vượt số nguyên 32 bit và số cách vượt modulo. Nhóm `max` có test đạt $N=200$ và mục tiêu bằng $10000$. Test `random_07` thuộc subtask 2. Khi chấm subtask, dùng tất cả test thỏa ràng buộc của subtask đó, không chỉ một nhóm tên file.

Chạy từ thư mục gốc:

```sh
# Sinh lại và kiểm tra 5 bài; đối chiếu hash đã lưu.
python3 custom/knapsack_tests/check_basic.py

# Kiểm tra riêng một bài.
python3 custom/knapsack03/tests/check.py

# Cập nhật hash khi chủ động thay bộ dữ liệu.
python3 custom/knapsack_tests/check_basic.py --update-hashes
```

Quy trình biên dịch với cảnh báo thành lỗi, xác thực mọi đầu vào, chạy lời giải theo giới hạn thời gian, kiểm tra ví dụ trong đề và độ phủ subtask, đối chiếu mọi kết quả với thuật toán độc lập, rồi đối chiếu hash. Có thêm 3.183 trường hợp vét cạn/ngẫu nhiên nhỏ được kiểm tra bằng liệt kê tập con trực tiếp. Verifier và checker được thử với dữ liệu đúng, sai, thiếu và thừa; các bộ sinh được chạy lại để kiểm tra tính tái lập.

Lời giải kiểm chứng dùng tập trạng thái thưa và loại trạng thái bị trội cho bài tối ưu, bitset cho khả năng đạt tổng, bitset theo số lượng cho bài ít thẻ nhất, và tích đa thức theo nhóm giá trị bằng nhau với hệ số nhị thức cho bài đếm. Các trường hợp có trọng lượng đồng nhất được kiểm tra thêm bằng công thức độc lập.

Đầu vào và đầu ra đã sinh nằm trong `in/` và `out/`, được bỏ qua bởi Git theo cấu hình dự án. Để học biến thể dùng một loại nhiều lần, xem [KNAPSACK05–KNAPSACK09](README_unbounded.md). Để luyện tiếp các bài biến đổi và mở rộng, xem [KNAPSACK10–KNAPSACK19](README.md).
