# Kiểm thử DTPLANBITS

Bài tự biên soạn, biến thể của PLAN. Có 26 test: hai ví dụ, tám test biên, tám test nhỏ ngẫu nhiên và tám test lớn. Ví dụ có trọng số 0, mỗi test còn lại có trọng số 1; tổng điểm bài là 100. Không dùng manifest riêng và không chia subtask.

Bộ sinh nằm tại `gen/cases.cpp`, dùng phần triển khai chung `../palplan_tests/generator.h` tính từ thư mục bài. Dữ liệu được sinh bằng seed cố định. Hướng dẫn kiểm tra và kết quả tổng hợp nằm tại [README chung](../../palplan_tests/README.md).

Chạy riêng bài này từ thư mục gốc: `python3 dtqg/palplan_tests/check.py --problem dtplanbits`. Khi chủ động thay đổi dữ liệu, thêm `--update-hashes`.

## Kết quả

Đạt 26 test chính thức, 100 trường hợp nhỏ độc lập và 17 test chính thức được đối chiếu thêm bằng liệt kê trực tiếp; 8 đầu vào sai bị loại và 18 tình huống checker đạt yêu cầu. Toàn bộ 52 mục hash khớp. Thời gian lời giải mẫu lớn nhất đo được là 0.0048 giây, dưới giới hạn upload 4 giây.
