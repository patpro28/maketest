# Kiểm thử đề đội tuyển quốc gia 2025, buổi 10

| Bài | Trang PDF | Ví dụ | Test sinh | Ca đối chiếu độc lập |
| --- | --- | ---: | ---: | ---: |
| [DTOCSEN](../dtocsen/task.md) | 5–6 | 4 | 16 | 120 |
| [DTORCHARD](../dtorchard/task.md) | 7–9 | 1 | 16 | 120 |
| [DTESPORT](../dtesport/task.md) | 10–15 | 4 | 16 | 120 |
| [DTQUANHE](../dtquanhe/task.md) | 16–17 | 1 | 16 | 120 |

Nguồn là `dtqg141024.en.pdf`, SHA-256 `fc5c133da8320c74b535e0b8bf23fbf811225287aa62662f4131e0b58eae37c2`. Đã đối chiếu các trang PDF hiển thị, gồm các công thức, ví dụ dạng ảnh và ví dụ DTESPORT bị ngắt trang.

## Cách chạy

Tại thư mục gốc, chạy `python3 dtqg/dtqg141024_tests/check.py`. Dùng `--problem` để chọn một mã bài hoặc `--update-hashes` khi chủ động đổi dữ liệu. Quy trình sinh và xác thực input, chạy lời giải với giới hạn 1 giây, gọi checker và đối chiếu `hash.json` cho từng bài. Mỗi ví dụ nguồn được đối chiếu riêng. Các test đối chiếu độc lập và test đầu vào hoặc đầu ra sai không đưa vào bộ test chấm.

## Phạm vi kiểm tra

- DTOCSEN dùng mô phỏng từng bước đến khi đạt đích hoặc gặp lại độ cao đầu ngày. Các ca biên gồm ngày thoát gần $10^{12}$, tổng dịch chuyển không dương, và trường hợp vẫn thoát được vào ngày $1$.
- DTORCHARD liệt kê trực tiếp các hình chữ nhật hợp lệ trên bảng nhỏ. Bộ test bao phủ cả ba miền kích thước sau khi hợp nhất ràng buộc của đề nguồn và trường hợp tổng tốt nhất trên toàn vườn bị loại vì Bin cần phần đất riêng. Dữ liệu vào/ra dùng tệp `ORCHARD.INP` và `ORCHARD.OUT`.
- DTESPORT mô phỏng các thao tác trực tiếp trên mảng nhỏ. Các ca lớn gồm truy vấn tĩnh, cập nhật toàn dãy, cập nhật điểm và các thao tác cộng/gán chồng nhau. Có ca mà tổng phần cộng dồn đúng bằng $2^{32}$ để bắt lỗi tràn số 32 bit. Dữ liệu vào/ra dùng tệp `ESPORT.INP` và `ESPORT.OUT`.
- DTQUANHE vét cạn cách gán trên đồ thị nhỏ, kiểm tra chuỗi và chu trình dài tới $10^5$ đỉnh, đồng thời xác nhận checker chấp nhận hai cách gán tối ưu khác nhau của ví dụ. Đề nguồn chỉ quy định đầu ra cho cách gán hợp lệ, nên bài dùng dữ liệu có nghiệm. Verifier loại các chu trình mâu thuẫn.
