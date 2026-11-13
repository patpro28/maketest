# Kiểm thử DTFACTOR

Nguồn: `/Users/patpro28/Downloads/Thay Dong/factor.pdf`; SHA-256: `78a2f16710e9b9e12a994982fe2779d1d8ece9a4df28af4edae793d1cb32f034`. Đã đối chiếu bản trích xuất và hình trang. Những thay đổi giới hạn, chỗ làm rõ nội dung, thứ tự luyện tập và thuật toán tham chiếu nằm tại [tài liệu chung](../../thaydong_tests/README.md).

Có 18 test chính thức, gồm ví dụ nguồn và 16 test sinh có seed cố định. Ví dụ có trọng số 0, mỗi test sinh có trọng số 1, tổng điểm bài là 100. Không chia subtask và không dùng manifest điểm riêng. Mỗi file input không vượt 1.000.000 byte.

Chạy từ thư mục gốc:

```sh
python3 dtqg/thaydong_tests/check.py --problem dtfactor
```

Sau khi chủ động thay đổi dữ liệu, thêm `--update-hashes`. Các bước sinh, xác thực dữ liệu, sinh đáp án, checker và đối chiếu hash được gọi riêng; không xuất HTML.

## Kết quả

Đạt 18 test chính thức và 80 trường hợp nhỏ độc lập; 8 đầu vào sai bị loại, 16 tình huống checker và 1 lượt nhập/xuất tệp nguồn đạt. Toàn bộ 36 mục hash khớp.

Input lớn nhất: 1954 byte. Thời gian lời giải mẫu lớn nhất đo được: 0.0534 giây. Số đo phụ thuộc máy chạy; giới hạn thời gian thực tế nằm trong `info.toml`.
