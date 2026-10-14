# Bộ bài KNAPSACK10–KNAPSACK19

Các bộ bài nền tảng học trước: [KNAPSACK00–KNAPSACK04 — 0–1](README_basic.md) và [KNAPSACK05–KNAPSACK09 — vô hạn](README_unbounded.md).

Các bài được đánh số theo thứ tự tăng dần đề xuất ở cuối tài liệu ý tưởng. Đề bài đặt trong `task.md`; lời giải và chứng minh đặt trong `solution.md`.

| Mã | Bài | Nội dung chính |
| --- | --- | --- |
| [knapsack10](../knapsack10/task.md) | Đặt dấu cộng hoặc trừ | Biến đổi về tổng tập con |
| [knapsack11](../knapsack11/task.md) | Hai tuyến xe buýt | Chia hai nhóm để giảm thời điểm hoàn thành |
| [knapsack12](../knapsack12/task.md) | Nâng cấp robot | Trừ cấu hình nền, hạn chế số linh kiện ép xung |
| [knapsack13](../knapsack13/task.md) | Mua vé đạt đủ điểm | Chi phí nhỏ nhất, chặn tổng điểm ở mục tiêu |
| [knapsack14](../knapsack14/task.md) | Chia hai đội cân bằng | Tổng tập con với số lượng cố định |
| [knapsack15](../knapsack15/task.md) | Xây số lớn nhất | Chi phí chính xác, chữ số dùng nhiều lần, truy vết |
| [knapsack16](../knapsack16/task.md) | Đội trưởng phải đủ mạnh | Sắp xếp và đếm tập con, xử lý sức mạnh trùng nhau |
| [knapsack17](../knapsack17/task.md) | Được phép sửa một món đồ | Sửa đúng một món được chọn, thêm cờ trạng thái |
| [knapsack18](../knapsack18/task.md) | Ba bếp | Hai chiều tổng thời gian |
| [knapsack19](../knapsack19/task.md) | Khóa kỹ năng | Gộp knapsack trên cây có phụ thuộc |

Mỗi bài có `info.toml`, `task.md`, `solution.md`, `sol/correct.cpp`, `checker.cpp`, `verifier.cpp`, bộ sinh test và `hash.json`. Các bộ sinh, lời giải và bộ kiểm tra của từng bài không phụ thuộc bài khác. Các tệp `tests/check.py` gọi bộ kiểm thử dùng chung trong thư mục này.

Mỗi bài có 32 cặp dữ liệu: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn. Riêng KNAPSACK13 có thêm 3 test lớn, thành 35 cặp; các test bổ sung có $N=200$, điểm từng hoạt động gần $20000$ và tổng điểm tới $4000000$. Tổng cộng 323 cặp đầu vào/đầu ra. Test `random_07` được dành cho subtask 2; các test nhỏ bao phủ subtask 1 và nhóm `max` chứa dữ liệu đạt giới hạn. Subtask được chấm theo toàn bộ test thỏa ràng buộc của nó, có thể chồng lấp.

Chạy từ thư mục gốc:

```sh
# Sinh lại, kiểm tra dữ liệu và lời giải, đối chiếu hash đã lưu; không xuất HTML.
python3 custom/knapsack_tests/check.py

# Kiểm tra riêng một bài.
python3 custom/knapsack15/tests/check.py

# Chỉ dùng khi chủ động cập nhật bộ dữ liệu và hash.
python3 custom/knapsack_tests/check.py --update-hashes
```

Quy trình biên dịch có bật cảnh báo thành lỗi, kiểm tra tất cả dữ liệu bằng verifier, chạy lời giải theo giới hạn thời gian trong `info.toml`, đối chiếu 323 kết quả với thuật toán kiểm chứng độc lập, kiểm tra ví dụ trong đề và độ phủ các subtask, thử verifier/checker với dữ liệu đúng và sai, rồi đối chiếu SHA-256 của đầu vào và đầu ra. Thêm 4.788 trường hợp vét cạn/ngẫu nhiên nhỏ được kiểm tra bằng liệt kê trực tiếp; bài xây số dùng một lời giải kiểm chứng lưu chuỗi trực tiếp.

Các thuật toán kiểm chứng dùng bitset số nguyên cho tổng tập con, bitset theo số lượng cho robot/chia đội, bài toán bỏ vé để tiết kiệm tiền, đếm theo từng nhóm sức mạnh, tách tiền tố/hậu tố và cố định món được sửa, bộ trạng thái ba tải đã sắp thứ tự, và duyệt trước cây với thao tác bỏ qua cả cây con. Bài xây số được đối chiếu thêm bằng DP số nguyên chính xác có độ dài tùy ý, tối ưu trực tiếp giá trị số thay vì độ dài và truy vết tham lam.

Đầu ra đã sinh nằm trong `out/`, đầu vào trong `in/`; đây là dữ liệu sinh lại được và được bỏ qua bởi Git theo cấu hình hiện có. Không cần thư viện xuất HTML.

Bộ tiếp theo: [KNAPSACK20–KNAPSACK29 — knapsack vô hạn nâng cao](README_advanced_unbounded.md).
