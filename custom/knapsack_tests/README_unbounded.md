# Bộ knapsack vô hạn KNAPSACK05–KNAPSACK09

Năm bài nối tiếp bộ nền tảng 0–1. Mỗi loại đồ vật, đoạn dây hoặc mệnh giá có số lượng không giới hạn. Các trọng lượng và mệnh giá đều dương; mục tiêu có thể bằng 0.

| Mã | Bài | Nội dung chính |
| --- | --- | --- |
| [knapsack05](../knapsack05/task.md) | Chọn đồ vào túi | Tối đa giá trị với trọng lượng không vượt sức chứa |
| [knapsack06](../knapsack06/task.md) | Ghép đoạn dây đạt đúng độ dài | Kiểm tra khả năng đạt đúng tổng |
| [knapsack07](../knapsack07/task.md) | Đổi tiền với ít đồng nhất | Số đồng tiền ít nhất để đạt đúng tổng |
| [knapsack08](../knapsack08/task.md) | Đếm số cách đổi tiền | Đếm bộ số lượng; không phân biệt thứ tự |
| [knapsack09](../knapsack09/task.md) | Chọn đồ lấp đầy túi | Tối đa giá trị với trọng lượng chính xác |

KNAPSACK05 và KNAPSACK09 dùng cùng dữ liệu ở ví dụ đầu để làm rõ sự khác biệt giữa “không vượt sức chứa” và “đúng sức chứa”. KNAPSACK08 yêu cầu các mệnh giá đôi một khác nhau; các bài còn lại cho phép các loại có cùng thông số.

Lời giải mẫu dùng tổng tăng dần để lấy một loại nhiều lần. Bài đếm duyệt mệnh giá ở vòng ngoài để mỗi bộ số lượng chỉ được tính một lần. Bài ít đồng tiền nhất dùng `INF=X+1`, vì số đồng cần lấy có thể lớn hơn số mệnh giá. Hai bài tối ưu giá trị dùng số nguyên 64 bit và có test đạt đáp án $10^{13}$.

Mỗi thư mục chứa `task.md`, `solution.md`, `sol/correct.cpp`, `info.toml`, verifier, checker, các bộ sinh test và `hash.json`. Mỗi bài có 32 cặp test: 2 ví dụ, 10 test biên, 6 test nhỏ, 8 test ngẫu nhiên và 6 test lớn; tổng cộng 160 cặp. Test có mục tiêu 0, dùng lại một loại, không có nghiệm, tham lam đổi tiền thất bại, mệnh giá vượt mục tiêu, giới hạn đầu vào và đầu ra lớn. Nhóm `max` bao phủ $N=100$, mục tiêu $10000$ và trọng lượng/mệnh giá $10000$. Test `random_07` thuộc subtask 2. Subtask được chấm theo mọi test thỏa ràng buộc tương ứng, có thể chồng lấp.

Chạy từ thư mục gốc:

```sh
# Sinh lại, kiểm tra và đối chiếu hash của cả 5 bài.
python3 custom/knapsack_tests/check_unbounded.py

# Kiểm tra riêng một bài.
python3 custom/knapsack08/tests/check.py

# Cập nhật hash khi chủ động thay bộ dữ liệu.
python3 custom/knapsack_tests/check_unbounded.py --update-hashes
```

Quy trình biên dịch với cảnh báo thành lỗi, kiểm tra mọi đầu vào bằng verifier, chạy lời giải theo giới hạn thời gian, đối chiếu ví dụ trong đề và độ phủ subtask, kiểm tra mọi kết quả với thuật toán độc lập và đối chiếu hash. Có thêm 3.029 trường hợp vét cạn/ngẫu nhiên nhỏ, kiểm tra bằng liệt kê trực tiếp số lượng lấy ở từng loại. Các bộ sinh được chạy lại để kiểm tra tính tái lập. Verifier/checker được thử với dữ liệu đúng, sai, thiếu, thừa; riêng KNAPSACK08 còn kiểm tra từ chối mệnh giá trùng nhau và chấp nhận mệnh giá chưa sắp xếp.

Lời giải kiểm chứng tối ưu giá trị dùng đường đi trên các tổng trọng lượng; bài khả thi/ít đồng dùng BFS trên các tổng. Bài đếm dùng hệ thức đa thức: nếu $Q(z)=\prod_i(1-z^{A_i})$, chuỗi số cách $F(z)$ thỏa mãn $Q(z)F(z)=1$. Các hệ số được tính độc lập với cách duyệt mệnh giá của lời giải mẫu. Bài đếm còn đối chiếu một test lớn bằng số nguyên chính xác để xác nhận số cách vượt modulo. Những trường hợp có trọng lượng đồng nhất được kiểm tra thêm bằng công thức.

Đề bài lưu ở Markdown, không xuất HTML. Đầu vào/đầu ra đã sinh nằm trong `in/` và `out/`, được bỏ qua bởi Git theo cấu hình dự án. Xem thêm [KNAPSACK00–KNAPSACK04](README_basic.md) và [KNAPSACK10–KNAPSACK19](README.md).

Bộ tiếp theo: [KNAPSACK20–KNAPSACK29 — knapsack vô hạn nâng cao](README_advanced_unbounded.md).
