## Chạy kiểm thử

Từ thư mục gốc dự án:

```sh
python3 custom/str67c/tests/run.py
```

Chỉ dùng `--update-hashes` khi chủ động cập nhật bộ dữ liệu chuẩn. Quy trình gọi riêng các bước biên dịch, sinh dữ liệu, kiểm tra đầu vào, tạo đáp án và kiểm tra đầu ra; không xuất HTML.

## Phạm vi

- 1 file ví dụ gốc, giữ dòng kết quả rỗng ở bộ dữ liệu thứ ba.
- 6 file biên: từng phím đơn/lặp đôi, ký tự xuất hiện nhiều lần nhưng vẫn là phím tốt, thứ tự bảng chữ cái đảo ngược, đầy đủ 26 phím, toàn phím tốt, toàn phím hỏng, trạng thái xen kẽ; có dữ liệu đạt $t=100$, $|S|=500$.
- 20 file ngẫu nhiên: chọn trạng thái cố định cho mỗi phím rồi mô phỏng các lần nhấn khác nhau liên tiếp. Giới hạn chuỗi là 500 ký tự, không phải 500 lần nhấn.
- Đối chiếu mọi đáp án đã sinh bằng cách xét hai ký tự hàng xóm của từng vị trí, độc lập với cách chia đoạn của lời giải chuẩn.
- Vét cạn mọi dãy nhấn hợp lệ dài từ 1 đến 7 trên ba phím và cả 8 cách gán trạng thái. Đáp án được suy ra trực tiếp từ trạng thái phím ban đầu và tập phím đã nhấn.
- Kiểm tra verifier từ chối dữ liệu vượt giới hạn, rỗng, sai bảng chữ cái, sai số dòng, đoạn lặp dài hơn hai hoặc trạng thái một phím không nhất quán.
- Kiểm tra checker chấp nhận đáp án đúng, CRLF, khoảng trắng hai đầu dòng; từ chối thiếu dòng rỗng, đặt sai dòng rỗng, sai thứ tự, lặp ký tự, khoảng trắng giữa ký tự và dữ liệu thừa. Có cả trường hợp kết quả cuối cùng rỗng và mọi kết quả đều rỗng.
- Đối chiếu cấu trúc đề bài, mã bài, mã nguồn tham khảo trong lời giải và SHA-256 của toàn bộ cặp input/output trong `hash.json`.

`checker.cpp` được dùng trong quy trình kiểm thử cục bộ để kiểm tra dòng kết quả rỗng. Bài không cấu hình upload checker riêng.
