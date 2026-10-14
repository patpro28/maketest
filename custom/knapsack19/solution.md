# Lời giải — Khóa kỹ năng

Nếu chọn một kỹ năng thì phải chọn cả đường đi từ gốc đến kỹ năng đó. Các nhánh con độc lập sau khi đã học nút cha, nên có thể gộp các nhánh bằng knapsack trên cây.

Với nút $u$, `dp_u[s]` là sức mạnh lớn nhất của một tập kỹ năng hợp lệ trong cây con $u$, có tổng chi phí **đúng** $s$ và **bắt buộc chọn $u$**. Khởi tạo chỉ `dp_u[C_u]=V_u` khi $C_u\le W$; các trạng thái khác bằng âm vô cùng.

Duyệt các con $v$ của $u$. Sau khi tính `dp_v`, với từng tổng đang đạt được $a$, có thể bỏ toàn bộ nhánh $v$ hoặc chọn một trạng thái $b$ của `dp_v` và cập nhật tổng $a+b$ với sức mạnh `dp_u[a]+dp_v[b]`. Gộp vào mảng mới để không dùng một nhánh nhiều lần.

Một tập hợp lệ có chọn $u$ giao với mỗi cây con $v$ hoặc là rỗng, hoặc là tập hợp lệ có chọn $v$. Các cây con rời nhau nên cách phân tách này là duy nhất. Quy nạp theo cây cho thấy việc gộp liệt kê đúng mọi tập hợp lệ và giữ sức mạnh lớn nhất cho từng chi phí. Cuối cùng lấy lớn nhất trong DP của gốc và $0$ (phương án không học gì).

Nếu $C_u>W$, không tập hợp lệ có chọn $u$ nào vừa ngân sách; có thể trả ngay mảng không đạt được, không cần duyệt hậu duệ. Thời gian $O(NW^2)$, bộ nhớ $O(N(W+1))$ trong trường hợp xấu nhất. Dùng số nguyên 64 bit cho tổng sức mạnh.

## Kiểm thử

32 file: 2 ví dụ, 10 trường hợp biên, 6 trường hợp nhỏ, 8 ngẫu nhiên và 6 trường hợp lớn. Nhóm `max` chứa test đạt giới hạn, cùng các dạng đặc biệt ở kích thước lớn. Các subtask có thể chồng lấp; điểm chỉ nhận khi đúng tất cả test thỏa ràng buộc subtask tương ứng.

Chạy `python3 custom/knapsack19/tests/check.py` từ thư mục gốc để sinh và kiểm tra test, đối chiếu lời giải với vét cạn độc lập, kiểm tra verifier/checker và đối chiếu `hash.json`. Khi chủ động đổi dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
