# Knapsack vô hạn nâng cao — KNAPSACK20–KNAPSACK29

Bộ 10 bài được xây dựng theo các ý tưởng đã thống nhất, kết hợp [SAMPLE_TASK.md](SAMPLE_TASK.md) với KNAPSACK00–KNAPSACK19. Các bài hướng tới mức C–D theo giới hạn dữ liệu.

| Mã | Bài | Kỹ thuật chính |
| --- | --- | --- |
| [knapsack20](../knapsack20/task.md) | Phá khiên quái vật | Chi phí ít nhất, chặn sát thương ở mục tiêu |
| [knapsack21](../knapsack21/task.md) | Đổi tiền tối ưu có bao nhiêu cách? | Lưu giá trị tối ưu và số cách đạt tối ưu |
| [knapsack22](../knapsack22/task.md) | Pha đồ uống đúng độ ngọt | Biến đổi trung bình, thêm chiều số cốc |
| [knapsack23](../knapsack23/task.md) | Xưởng robot hàng loạt | Tính trước chi phí thao tác rồi knapsack vô hạn |
| [knapsack24](../knapsack24/task.md) | Một phiếu giảm giá | Cờ dùng ưu đãi đúng một lần |
| [knapsack25](../knapsack25/task.md) | Sản xuất bằng hai nguyên liệu | Hai chiều tài nguyên |
| [knapsack26](../knapsack26/task.md) | Mở dây chuyền rồi sản xuất | Trả phí mở một lần, sản xuất nhiều lần |
| [knapsack27](../knapsack27/task.md) | Dàn máy có bộ điều phối đủ mạnh | Gom mức tối đa và đếm knapsack vô hạn |
| [knapsack28](../knapsack28/task.md) | Xây số lớn nhất chia hết | Độ dài tối ưu, số dư tiền tố và truy vết |
| [knapsack29](../knapsack29/task.md) | Ghép đường ray dài tới 10^18 | Dijkstra trên số dư, nhiều truy vấn lớn |

Các điều kiện giữ bài toán hữu hạn được nêu trong đề: trọng lượng/giá/chi phí sản phẩm dương; robot phải trả một năng lượng tạo khung; đồ uống phải có đúng K cốc; chỉ một sản phẩm được dùng phiếu, kể cả khi giá giảm về 0. Bài đếm không phân biệt thứ tự. KNAPSACK21 có mệnh giá đôi một khác nhau; KNAPSACK22/27 phân biệt công thức/mẫu theo mã dù thông số trùng nhau. Bài giảm giá bắt buộc dùng đúng một phiếu. Bài đường ray cho phép các chiều dài trùng nhau và truy vấn 0.

Mỗi bài có đề tiếng Việt `task.md`, lời giải và chứng minh `solution.md`, `sol/correct.cpp`, `info.toml`, verifier, checker, bộ sinh dữ liệu và `hash.json`. Mỗi bài có 32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên, 6 test lớn. Tổng cộng 320 cặp đầu vào/đầu ra và 640 hash SHA-256.

Nhóm `max` bao phủ kích thước tối đa và các trường hợp đặc biệt. Bài 20 có sát thương $10^9$, bài 21 có số cách tối ưu vượt modulo, bài 22 có công thức trùng độ ngọt, bài 23 có mẫu sức mạnh 1 và 1000, bài 24 có ưu đãi miễn phí đúng một sản phẩm, bài 25 có ngân sách của một tài nguyên bằng 0, bài 26 có phí mở bằng 0 hoặc vượt ngân sách, bài 27 có nhiều mẫu trùng sức mạnh, bài 28 có đáp án dài 2000 chữ số và điều kiện chia hết, bài 29 có $N=50$, $Q=100000$, số dư nhỏ nhất 5000, đoạn dài $10^6$ và truy vấn $10^{18}$. `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc tương ứng, có thể chồng lấp.

Chạy từ thư mục gốc:

```sh
# Sinh lại và kiểm tra cả 10 bài, đối chiếu hash đã lưu, không xuất HTML.
python3 custom/knapsack_tests/check_advanced.py

# Kiểm tra riêng một bài.
python3 custom/knapsack29/tests/check.py

# Cập nhật hash khi chủ động thay bộ dữ liệu.
python3 custom/knapsack_tests/check_advanced.py --update-hashes
```

Quy trình biên dịch với cảnh báo thành lỗi, kiểm tra dữ liệu vào, chạy lời giải theo giới hạn thời gian, đối chiếu ví dụ trong đề và độ phủ subtask, kiểm tra mọi kết quả bằng thuật toán độc lập, thử verifier/checker với dữ liệu đúng/sai/thiếu/thừa, chạy lại các bộ sinh để xác nhận tính tái lập và đối chiếu hash. Có thêm 2.852 trường hợp vét cạn/ngẫu nhiên nhỏ; các trường hợp phù hợp được kiểm tra bằng liệt kê trực tiếp số lượng lấy của từng loại, chuỗi chữ số hoặc DP đến các truy vấn nhỏ.

Các thuật toán kiểm chứng:

- **20:** Dijkstra trên mức sát thương đã chặn.
- **21:** BFS tìm số đồng ít nhất cho từng tổng, sau đó đếm các tổ hợp chỉ qua những tổng có số đồng tối ưu. Một test lớn được kiểm tra thêm bằng số nguyên chính xác.
- **22:** Hai lớp DP, thử rõ từng số lần dùng mỗi công thức, thay vì cập nhật vô hạn tại chỗ.
- **23:** BFS cho thao tác nâng cấp; tối ưu đường đi trên tổng năng lượng chính xác.
- **24:** Cố định loại sản phẩm dùng phiếu, phần còn lại mua đủ giá.
- **25:** Đường đi trên các cặp lượng nguyên liệu tiêu thụ chính xác.
- **26:** DP chi phí chính xác, tối ưu số lượng sản phẩm bằng cực đại tiền tố theo từng lớp đồng dư của chi phí sản xuất.
- **27:** Chọn mẫu có mã cuối cùng được sử dụng trong một thứ tự cố định, thay vì gom theo nhóm sức mạnh.
- **28:** DP bằng số nguyên độ dài tùy ý, tối ưu trực tiếp giá trị số tại mỗi chi phí và số dư, độc lập với DP độ dài và truy vết của lời giải mẫu.
- **29:** Đồ thị số dư dùng một chiều dài có sẵn lớn hơn khi có thể, cùng kiểm tra tổng nhỏ và các công thức chia hết.

Đầu vào/đầu ra đã sinh nằm trong `in/` và `out/`, được bỏ qua bởi Git theo cấu hình dự án. Xem các bộ trước: [0–1 nền tảng](README_basic.md), [vô hạn nền tảng](README_unbounded.md), [các bài biến đổi KNAPSACK10–19](README.md).

## Bài mở rộng KNAPSACK30

[KNAPSACK30 — Phá khiên trong đúng K lượt](../knapsack30/task.md) bổ sung điều kiện dùng đúng K lần phép. DP phải giữ thông tin đã đủ sát thương qua các lượt tiếp theo; bỏ tổng chính xác vượt 2X có thể làm mất nghiệm. Đề không có mục Subtask. Phần `[upload]` được sao chép nguyên vẹn từ KNAPSACK19.

Bài có 37 cặp test, lời giải, verifier/checker và bộ kiểm thử riêng. Chạy `python3 custom/knapsack30/tests/check.py` để sinh và kiểm tra; thêm `--update-hashes` khi chủ động đổi dữ liệu. Bộ kiểm thử đối chiếu bằng DP sát thương còn thiếu, 748 trường hợp vét cạn/ngẫu nhiên nhỏ và các công thức biên; xác nhận bắt được lỗi bỏ tổng vượt 2X và lỗi dừng trước K lượt. Không xuất HTML.
