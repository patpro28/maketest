# Bộ bài HASHING000–HASHING009

Mười bài tự biên soạn từ mức Vừa đến Khó nâng cao. Mỗi bài có đề tiếng Việt trong `task.md`, hai ví dụ, lời giải trong `solution.md`, lời giải C++17, verifier, checker, bộ sinh xác định theo seed, và `hash.json` của các test đã sinh. Không có mục Subtask và không xuất HTML.

| Mã | Tên bài | Kiến thức chính | Mức độ | Giới hạn thời gian |
| --- | --- | --- | --- | --- |
| hashing000 | Thông điệp xuất hiện nhiều lần | Hash, tần suất, tìm kiếm nhị phân | Vừa | 3 s |
| hashing001 | Giai điệu chuyển tông | Dãy hiệu, số âm, hash dãy số | Vừa | 3 s |
| hashing002 | Sao chép không chồng lấn | Hash, vị trí sớm nhất, tìm kiếm nhị phân | Vừa | 3 s |
| hashing003 | Bản sao sai một ký tự | Hash, tiền tố chung, đúng một vị trí sai | Vừa–khó | 3 s |
| hashing004 | So sánh từ điển các đoạn | Hash, tiền tố chung, thứ tự từ điển | Vừa–khó | 3 s |
| hashing005 | Mật khẩu chung của nhiều người | Giao tập hash, tìm kiếm nhị phân | Vừa–khó | 5 s |
| hashing006 | Những vòng chữ tương đương | Chuẩn hóa phép xoay, so sánh bằng hash | Khó | 5 s |
| hashing007 | Hai mảnh bản đồ có thể xoay | Hash hai chiều, chuyển tọa độ qua bốn góc xoay | Khó | 5 s |
| hashing008 | Gương chữ biến đổi | Segment tree, hash xuôi và ngược | Khó | 3 s |
| hashing009 | Thông điệp trên đường đi | HLD, hash có hướng, ghép đường đi | Khó nâng cao | 5 s |

## Sinh và kiểm tra

Chạy tại thư mục gốc dự án:

```sh
python3 custom/hashing_tests/check.py
```

Lệnh trên biên dịch với C++17 và cảnh báo nghiêm ngặt, sinh lại test, chạy verifier, tạo đáp án, chấm lời giải theo giới hạn thời gian, đối chiếu lời giải độc lập, kiểm tra các ca vét cạn/ngẫu nhiên, thử dữ liệu sai và checker, kiểm tra định dạng đề, tính tái lập và hash. Không gọi bước xuất HTML.

Khi chủ động thay đổi bộ test hoặc đáp án:

```sh
python3 custom/hashing_tests/check.py --update-hashes
```

Chạy riêng một bài:

```sh
python3 custom/hashing_tests/check.py --problem hashing009
python3 custom/hashing009/tests/check.py
```

Mỗi bài có 30 test chính thức: 2 ví dụ, 10 test biên, 6 test nhỏ, 6 test ngẫu nhiên trung bình, 6 test sát giới hạn. Seed được truyền dưới dạng tham số đầu tiên của từng bộ sinh. Các file trong `in/`, `out/`, chương trình đã biên dịch và `params.h` tuân theo quy tắc bỏ qua của dự án; có thể tái tạo bằng lệnh trên.

## Đối chiếu độc lập

- `hashing000`: suffix array, LCP và cửa sổ trượt.
- `hashing001`: KMP trên dãy hiệu 64 bit.
- `hashing002`: suffix array và cực trị vị trí trong nhóm có chung tiền tố.
- `hashing003`: Z theo hai chiều.
- `hashing004`: suffix array, LCP và RMQ.
- `hashing005`: suffix array của nhiều xâu với dấu phân cách riêng, cửa sổ chứa đủ màu.
- `hashing006`: Booth và so sánh trực tiếp đại diện dạng xâu.
- `hashing007`: hash hai chiều độc lập với cơ số và số học 64 bit khác lời giải chính, công thức tọa độ viết riêng; vét cạn trực tiếp trên các bảng nhỏ.
- `hashing008`: Fenwick với hash trọng số theo vị trí, độc lập với segment tree; vét cạn trực tiếp trên các xâu nhỏ.
- `hashing009`: binary lifting và LCA, độc lập với HLD; tìm đường đi và so sánh trực tiếp trên cây nhỏ.

Các lời giải chính dùng hash kép. Các lời giải đối chiếu có dùng hash vẫn mang tính xác suất; các phép đối chiếu vét cạn dùng so sánh trực tiếp.

## Các trường hợp được kiểm tra

- Xâu một ký tự, mọi ký tự bằng nhau, chu kỳ ngắn, không có đáp án, đáp án phủ toàn xâu.
- Phân biệt việc cho phép chồng lấn ở `hashing000` và cấm chồng lấn ở `hashing002`.
- Mẫu dài hơn văn bản, mẫu dài một phần tử, hiệu cao độ đạt ±2 tỷ.
- Mẫu bằng hoàn toàn bị loại ở `hashing003`; vị trí sai ở đầu hoặc cuối.
- Đoạn bằng nhau, tiền tố thực sự và ký tự khác nhau đầu/cuối trong so sánh từ điển.
- Một xâu duy nhất, nhiều xâu ngắn, tổng độ dài cực đại, một xâu ngắn giới hạn đáp án.
- Xâu tuần hoàn, các phép xoay trùng nhau, phép đảo không phải phép xoay.
- Bảng chữ nhật, một hàng/cột, bốn góc xoay và trường hợp chỉ lật gương.
- Cập nhật lặp cùng ký tự, chỉ cập nhật nên đầu ra rỗng, chỉ truy vấn.
- Cây một đỉnh, cây dây dài 200000 đỉnh, cây sao, cây nhị phân, cây ngẫu nhiên đổi nhãn, cạnh nhập theo cả hai chiều.
- Đường đi ngược chiều, độ dài khác nhau, hai đầu trùng nhau và ghép qua nhiều chuỗi nặng.

Kết quả lần chạy đầy đủ được lưu trong `REPORT.md`.
