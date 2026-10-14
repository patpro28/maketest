# Quy tắc làm việc trong dự án

## Cấu trúc đề bài

- Khi tạo bài mới hoặc chỉnh sửa đề bài, `task.md` phải theo cấu trúc của các bài `custom/knapsack00` đến `custom/knapsack29`. Có thể đối chiếu `custom/knapsack00/task.md` và `custom/knapsack27/task.md` làm mẫu.
- Tiêu đề dùng cấp 1, theo dạng `# MÃ_BÀI — Tên bài tiếng Việt`; mã bài viết hoa và khớp với tên thư mục bài, ví dụ `# ABC160F — Phân phối số nguyên`.
- Các mục dùng cấp 3 và xuất hiện đúng thứ tự:
  1. `### Đề bài`
  2. `### Dữ liệu vào`
  3. `### Dữ liệu ra`
  4. `### Ràng buộc`
  5. `### Subtask`
  6. Các cặp `### Sample Input 1`, `### Sample Output 1`, tiếp tục đánh số tăng dần cho các ví dụ còn lại.
  7. `### Giải thích`
- Viết nội dung bằng tiếng Việt, rõ ràng và thống nhất ký hiệu. Mô tả dữ liệu vào theo từng dòng bằng danh sách; mô tả chính xác yêu cầu đầu ra; trình bày ràng buộc bằng danh sách và công thức LaTeX `$...$`.
- Mục `Subtask` bắt buộc dùng bảng với ba cột `Subtask | Tỉ lệ | Ràng buộc bổ sung`. Tổng tỉ lệ phải bằng 100%; dòng áp dụng toàn bộ ràng buộc ghi `Không có ràng buộc bổ sung`. Nếu đề nguồn có subtask, giữ đúng cách chia của nguồn; nếu không có và người dùng không yêu cầu chia thêm, dùng một subtask 100% với toàn bộ ràng buộc.
- Mỗi Sample Input/Output đặt trong khối mã có nhãn `text`, giữ nguyên định dạng và thứ tự ví dụ từ đề nguồn. Với bài tự biên soạn, cung cấp ít nhất hai ví dụ phù hợp.
- Gom giải thích các ví dụ vào một mục `### Giải thích` ở cuối, chỉ rõ đang giải thích ví dụ nào; không đặt mục giải thích xen giữa các cặp Sample Input/Output.
- Khi chuyển bài từ PDF hoặc nguồn khác, giữ nguyên ý nghĩa, giới hạn và ví dụ, đồng thời chuyển cách trình bày sang cấu trúc trên. Có thể thêm mục `### Nguồn` sau `### Giải thích` để ghi xuất xứ.
- Trước khi hoàn tất, đối chiếu `task.md` với mẫu knapsack để kiểm tra tiêu đề, cấp heading, thứ tự mục, bảng subtask và định dạng ví dụ. Quy tắc này áp dụng cho các bài trong mọi thư mục của dự án.

## Đề bài và kiểm thử

- Khi tạo hoặc cập nhật bài tập, lưu đề bài trong `task.md` và bỏ qua bước xuất HTML đề bài, trừ khi người dùng yêu cầu rõ ràng.
- Không cài thêm thư viện chỉ để xuất HTML và không coi việc thiếu HTML là lỗi hay công việc chưa hoàn thành.
- Vẫn thực hiện đầy đủ việc sinh test, kiểm tra dữ liệu đầu vào, kiểm tra lời giải, checker và cập nhật hoặc đối chiếu `hash.json` khi cần.
- Các chế độ `--dev` và `--test` hiện tự gọi bước xuất HTML. Khi dùng quy trình này, hãy chạy riêng các bước sinh và kiểm tra cần thiết để bỏ qua bước HTML; không bỏ qua kiểm thử chỉ vì không xuất HTML.
