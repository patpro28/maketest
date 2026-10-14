# Lời giải — Được phép sửa một món đồ

Dùng hai trạng thái cho mỗi tổng trọng lượng $w$: `unused[w]` là giá trị lớn nhất khi chưa sửa món nào; `used[w]` là giá trị lớn nhất khi đã sửa đúng một món. Khởi tạo `unused[0]=0`, các trạng thái khác bằng âm vô cùng.

Với món $(W_i,V_i)$, có ba lựa chọn: bỏ qua; lấy nguyên trạng và giữ cờ đã sửa/chưa sửa; hoặc chuyển từ chưa sửa sang đã sửa bằng cách lấy món với trọng lượng $\lfloor W_i/2\rfloor$. Lời giải mẫu đọc từ hai mảng cũ và ghi vào hai mảng mới, nên mỗi món chỉ được dùng một lần ngay cả khi trọng lượng sau sửa bằng $0$.

Bất biến được bảo toàn vì ba lựa chọn mô tả đầy đủ hành động với món hiện tại. Cờ chỉ chuyển từ chưa sửa sang đã sửa một lần và chuyển đó luôn lấy món, nên không thể sửa một món không được chọn. Đáp án chỉ lấy lớn nhất trong `used`, bảo đảm điều kiện **đúng một lần**. Nếu mọi trạng thái `used` không đạt được, in `-1`.

Thời gian $O(NC)$, bộ nhớ $O(C)$. Tổng giá trị có thể tới $2\cdot10^{11}$, dùng số nguyên 64 bit.

## Kiểm thử

32 file: 2 ví dụ, 10 trường hợp biên, 6 trường hợp nhỏ, 8 ngẫu nhiên và 6 trường hợp lớn. Nhóm `max` chứa test đạt giới hạn, cùng các dạng đặc biệt ở kích thước lớn. Các subtask có thể chồng lấp; điểm chỉ nhận khi đúng tất cả test thỏa ràng buộc subtask tương ứng.

Chạy `python3 custom/knapsack17/tests/check.py` từ thư mục gốc để sinh và kiểm tra test, đối chiếu lời giải với vét cạn độc lập, kiểm tra verifier/checker và đối chiếu `hash.json`. Khi chủ động đổi dữ liệu, thêm `--update-hashes`. Quy trình không xuất HTML.
