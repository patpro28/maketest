# Kiểm thử bộ DPALL

Bộ bài gồm ba bài cơ bản (0000–0002), bốn bài tổng hợp (0003–0006) và ba bài tư duy mới (0007–0009).

Mỗi bài có hai ví dụ, các ca biên cố định và 18 ca sinh từ seed. Tám seed đầu sinh dữ liệu nhỏ, sáu seed kế sinh dữ liệu vừa, bốn seed cuối sinh dữ liệu lớn. Trình kiểm tra đầu vào kiểm tra giới hạn và định dạng. Trình chấm đối chiếu toàn bộ đáp án.

Để biên dịch, sinh lại dữ liệu, đối chiếu mã băm và chấm toàn bộ bộ bài, chạy lệnh sau từ thư mục gốc với Python 3.11 trở lên.

```sh
python3 custom/dpall_tests/check.py --regenerate
```

Công cụ đối chiếu các ví dụ, ca biên và ca sinh nhỏ bằng vét cạn độc lập, rồi sinh thêm 60 ca nhỏ cho mỗi bài. Công cụ cũng kiểm tra cấu trúc đề, cấu hình giới hạn thời gian và khả năng từ chối đầu vào thừa, đáp án sai, đáp án thừa hoặc đáp án rỗng. Bỏ tùy chọn `--regenerate` để chỉ chạy những kiểm tra này trên dữ liệu đã sinh.

| Mã bài | Cách vét cạn |
| --- | --- |
| DPALL0000, DPALL0003 | Liệt kê các dãy bước nhảy hợp lệ |
| DPALL0001, DPALL0005 | Liệt kê số lượng lấy từ mỗi dòng |
| DPALL0002 | Tạo tập dãy con của hai xâu theo từng độ dài |
| DPALL0004 | Liệt kê vị trí các bước xuống trong đường đi |
| DPALL0006 | Liệt kê hai bộ chỉ số ghép |
| DPALL0007 | Duyệt mọi cặp đầu mút và thử từng đoạn cấm |
| DPALL0008 | Đảo trực tiếp từng đoạn rồi tính lại tổng điểm |
| DPALL0009 | Duyệt các đường đi với tập ô đã đi qua |
