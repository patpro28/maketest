# DPSTR4xx và DPSTR5xx

## Nhóm 5 — Chia xâu thành các đoạn hợp lệ

| Mức | Mã | Bài toán | Thuật toán chính |
| --- | --- | --- | --- |
| Dễ | [dpstr400](../dpstr400/task.md) | Kiểm tra có thể phủ xâu bằng bốn mảnh cho sẵn | DP đúng/sai trên tiền tố |
| Dễ | [dpstr401](../dpstr401/task.md) | Đếm cách tách chữ số thành các số từ 1 đến 26 | DP đếm với mảnh dài 1 hoặc 2 |
| Dễ | [dpstr402](../dpstr402/task.md) | Chia ít đoạn số nhất với giá trị trong một khoảng | Thử tối đa 10 chữ số sau mỗi điểm cắt |
| Dễ | [dpstr403](../dpstr403/task.md) | Đếm cách chia khi hai đầu của mỗi mảnh cùng chữ | DP đếm với độ dài mảnh giới hạn |
| Trung bình | [dpstr430](../dpstr430/task.md) | Chia xâu thành các từ có tổng chi phí nhỏ nhất | Cây tiền tố và DP chi phí |
| Trung bình | [dpstr431](../dpstr431/task.md) | Chia đúng số đoạn có tổng chữ số chia hết | DP theo số đoạn và gom tổng theo phần dư |
| Trung bình | [dpstr432](../dpstr432/task.md) | Chia ít đoạn nhất với độ dài cho phép và các chữ khác nhau | DP dùng mặt nạ 26 chữ |
| Khó | [dpstr450](../dpstr450/task.md) | Chia đúng số đoạn rồi sửa mỗi đoạn thành đối xứng | Chi phí trên đoạn và DP theo số đoạn |
| Khó | [dpstr451](../dpstr451/task.md) | Đếm cách chia thành dãy số tăng nghiêm ngặt | DP theo độ dài số cuối, tổng tiền tố và LCP |
| Khó | [dpstr452](../dpstr452/task.md) | Tìm số mảnh ít nhất và đếm cách tối ưu | Khoảng điểm cắt hợp lệ và cây đoạn |

## Nhóm 6 — Biến đổi xâu

| Mức | Mã | Bài toán | Thuật toán chính |
| --- | --- | --- | --- |
| Dễ | [dpstr500](../dpstr500/task.md) | Tối thiểu số lần chèn, xóa và thay | Khoảng cách chỉnh sửa trên hai tiền tố |
| Dễ | [dpstr501](../dpstr501/task.md) | Biến đổi bằng xóa và thay | DP bỏ hoặc giữ vị trí nguồn |
| Dễ | [dpstr502](../dpstr502/task.md) | Thay chữ hoặc đổi chỗ trong những cặp kề nhau rời nhau | DP theo mảnh dài 1 hoặc 2 |
| Dễ | [dpstr503](../dpstr503/task.md) | Chèn, xóa và thay theo bảng giá | DP khoảng cách có trọng số |
| Trung bình | [dpstr530](../dpstr530/task.md) | Khớp xâu nguồn với mẫu có dấu hỏi | DP với phí ghép phụ thuộc mẫu |
| Trung bình | [dpstr531](../dpstr531/task.md) | Xóa và chèn với giá theo từng vị trí | DP trên hai tiền tố với chi phí vị trí |
| Trung bình | [dpstr532](../dpstr532/task.md) | Đếm kịch bản chỉnh sửa tối ưu | DP cặp chi phí và số cách |
| Khó | [dpstr550](../dpstr550/task.md) | Chỉnh sửa với phí mở và kéo dài mỗi đợt chèn/xóa | DP ba trạng thái bước cuối |
| Khó | [dpstr551](../dpstr551/task.md) | Chỉnh sửa hai xâu dài trong ngân sách nhỏ | DP trong dải quanh đường chéo |
| Khó | [dpstr552](../dpstr552/task.md) | Tìm đoạn đích không rỗng gần nhất và phá hòa theo vị trí | DP nén hàng giữ chi phí và đầu trái |

## Cấu hình và kiểm tra

Cả hai nhóm dùng `types = ['dp_string']`, thời gian 1 giây và bộ nhớ 128 MiB. Quy mô tính toán chính tối đa là 48 triệu trạng thái ở bài 550.

Mỗi bài có đề với hai ví dụ, giải thích, lời giải C++11, bộ sinh, verifier, checker và mã băm. Trong 32 cặp input/output của mỗi bài, có 2 ví dụ, 12 trường hợp biên, 8 trường hợp nhỏ, 6 trường hợp ngẫu nhiên và 4 trường hợp lớn. Các trường hợp lớn được xây dựng với đáp án suy ra từ cấu trúc dữ liệu hoặc công thức tổ hợp. Bộ kiểm tra đối chiếu dữ liệu còn lại bằng liệt kê điểm cắt, chọn vị trí giữ lại hoặc tính theo hướng khác với lời giải chuẩn.

Chạy từ thư mục gốc dự án.

```sh
python3 custom/dpstr_partition_edit_tests/check.py
python3 custom/dpstr_partition_edit_tests/check.py --problem dpstr451 dpstr552
python3 custom/dpstr551/tests/check.py
```

Dùng `--update-hashes` khi chủ động thay dữ liệu. Xem thời gian đo cục bộ và số cặp đã đối chiếu trong [báo cáo kiểm tra](results.md).
