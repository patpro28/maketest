# Quy tắc làm việc trong dự án

## Cấu trúc đề bài

- Khi tạo bài mới hoặc chỉnh sửa đề bài, `task.md` phải theo cấu trúc của các bài `custom/knapsack00` đến `custom/knapsack29`. Có thể đối chiếu `custom/knapsack00/task.md` và `custom/knapsack27/task.md` làm mẫu.
- Tiêu đề dùng cấp 1, theo dạng `# MÃ_BÀI — Tên bài tiếng Việt`; mã bài viết hoa và khớp với tên thư mục bài, ví dụ `# ABC160F — Phân phối số nguyên`.
- Các mục dùng cấp 3 và xuất hiện đúng thứ tự:
  1. `### Đề bài`
  2. `### Dữ liệu vào`
  3. `### Dữ liệu ra`
  4. `### Ràng buộc`
  5. `### Subtask` (chỉ khi người dùng yêu cầu)
  6. Các cặp `### Sample Input 1`, `### Sample Output 1`, tiếp tục đánh số tăng dần cho các ví dụ còn lại.
  7. `### Giải thích`
- Viết nội dung bằng tiếng Việt, rõ ràng và thống nhất ký hiệu. Mô tả dữ liệu vào theo từng dòng bằng danh sách; mô tả chính xác yêu cầu đầu ra; trình bày ràng buộc bằng danh sách và công thức LaTeX `$...$`.
- Chỉ thêm mục `Subtask` khi người dùng yêu cầu rõ ràng. Mặc định không thêm mục này, kể cả subtask 100% hoặc khi đề nguồn có subtask. Khi được yêu cầu thêm, dùng bảng với ba cột `Subtask | Tỉ lệ | Ràng buộc bổ sung`, tổng tỉ lệ bằng 100%; dòng áp dụng toàn bộ ràng buộc ghi `Không có ràng buộc bổ sung`. Nếu đề nguồn có subtask và người dùng yêu cầu giữ, giữ đúng cách chia của nguồn.
- Mỗi Sample Input/Output đặt trong khối mã có nhãn `text`, giữ nguyên định dạng và thứ tự ví dụ từ đề nguồn. Với bài tự biên soạn, cung cấp ít nhất hai ví dụ phù hợp.
- Gom giải thích các ví dụ vào một mục `### Giải thích` ở cuối, chỉ rõ đang giải thích ví dụ nào; không đặt mục giải thích xen giữa các cặp Sample Input/Output.
- Khi chuyển bài từ PDF hoặc nguồn khác, giữ nguyên ý nghĩa, giới hạn và ví dụ, đồng thời chuyển cách trình bày sang cấu trúc trên. Có thể thêm mục `### Nguồn` sau `### Giải thích` để ghi xuất xứ.
- Trước khi hoàn tất, đối chiếu `task.md` với mẫu knapsack để kiểm tra tiêu đề, cấp heading, thứ tự mục và định dạng ví dụ; chỉ kiểm tra bảng subtask khi người dùng yêu cầu có mục này. Quy tắc này áp dụng cho các bài trong mọi thư mục của dự án.

## Đề bài và kiểm thử

- Khi tạo hoặc cập nhật bài tập, lưu đề bài trong `task.md` và bỏ qua bước xuất HTML đề bài, trừ khi người dùng yêu cầu rõ ràng.
- Không cài thêm thư viện chỉ để xuất HTML và không coi việc thiếu HTML là lỗi hay công việc chưa hoàn thành.
- Vẫn thực hiện đầy đủ việc sinh test, kiểm tra dữ liệu đầu vào, kiểm tra lời giải, checker và cập nhật hoặc đối chiếu `hash.json` khi cần.
- Các chế độ `--dev` và `--test` hiện tự gọi bước xuất HTML. Khi dùng quy trình này, hãy chạy riêng các bước sinh và kiểm tra cần thiết để bỏ qua bước HTML; không bỏ qua kiểm thử chỉ vì không xuất HTML.

## Phân nhóm bài segment tree

- Toàn bộ dải `segtree000`–`segtree099` (đầu 0) thuộc **SEG0 — Basic Segment Tree**. Phạm vi gồm dựng cây, truy vấn đoạn và cập nhật điểm; nhóm 000–009 chỉ có truy vấn tĩnh, không cập nhật.
- Các kỹ thuật tìm kiếm trên segment tree (search, đi xuống cây để tìm vị trí) và lazy propagation thuộc nơi khác, không đưa vào các bài SEG0. Các nhóm 080–089 và 090–099 vẫn phải giữ phạm vi cơ bản này dù phép ghép hoặc bài toán có tính tổng hợp.
- Khi đề xuất hoặc tạo bài `segtreeXXX`, chọn mã theo trọng tâm kiến thức của bài và đúng dải mã trong bảng dưới đây. Đối chiếu nhóm trước khi chốt ý tưởng và trước khi hoàn tất bài để tránh ra nhầm dạng.
- Với bài có nhiều đặc điểm giao nhau, phân nhóm theo mục tiêu luyện tập chính. Việc một nút lưu nhiều trường không tự động khiến bài thuộc nhóm 060–069; cần phân biệt trọng tâm lưu thông tin trên nút, truy vấn kết hợp nhiều đại lượng và phép ghép tùy chỉnh.

| Dải mã | Nội dung | Tên tiếng Anh | Topic ID |
| --- | --- | --- | --- |
| 000–009 | Xây dựng cây, truy vấn cơ bản, không cập nhật | Static Range Query | TOP-FB61J3EYJR |
| 010–019 | Tổng đoạn – Range Sum | Range Sum | TOP-ZX6N9JZ9KY |
| 020–029 | Min / Max đoạn | Range Min-Max | TOP-F4DA53XX74 |
| 030–039 | GCD / LCM đoạn | Range GCD-LCM | TOP-8GKH14W0VW |
| 040–049 | AND / OR / XOR đoạn | Range Bitwise Operations | TOP-E08D6J678N |
| 050–059 | Đếm phần tử thỏa mãn điều kiện | Conditional Counting | TOP-H04T7B98ME |
| 060–069 | Lưu nhiều thông tin trên nút | Multi-Field Node | TOP-ZHW1HQ0YJ2 |
| 070–079 | Truy vấn kết hợp nhiều đại lượng | Multi-Aggregate Query | TOP-BSQJMN7ST3 |
| 080–089 | Segment Tree với phép toán kết hợp tùy chỉnh | Custom Associative Operation | TOP-9QZWEP977C |
| 090–099 | Bài toán tổng hợp cơ bản | Basic Mixed Problems | TOP-HJSCY8W2S3 |
