# PREFIX021–PREFIX030 — Mức 2 và mức 3

Bộ bài dành cho học sinh đã quen tổng tiền tố đếm hoặc cộng các phần tử thỏa điều kiện. Tên thư mục dùng `dppsum021`–`dppsum030`; nhãn trong đề, lời giải và `info.toml` dùng `PREFIX021`–`PREFIX030`.

## Mức 2: nhiều mảng prefix

Mỗi truy vấn trả về hai hoặc ba kết quả theo thứ tự cố định.

| Mã thư mục | Nhãn | Bài tập |
| --- | --- | --- |
| dppsum021 | PREFIX021 | Tổng các số chẵn và tổng các số lẻ |
| dppsum022 | PREFIX022 | Tổng các số dương và tổng các số âm |
| dppsum023 | PREFIX023 | Số lượng và tổng các phần tử chia hết cho K cố định |
| dppsum024 | PREFIX024 | Số ký tự a, b, c trong chuỗi con |
| dppsum025 | PREFIX025 | Số phần tử nhỏ hơn, bằng, lớn hơn K cố định |

## Mức 3: biến đổi từ hai phần tử kề nhau

Cả hai phần tử của một cặp phải nằm trong đoạn truy vấn. Đoạn một phần tử luôn cho kết quả 0. Với mảng biến đổi lưu ở vị trí bên phải của cặp, công thức là `P[R] - P[L]`.

| Mã thư mục | Nhãn | Bài tập |
| --- | --- | --- |
| dppsum026 | PREFIX026 | Đếm cặp bằng nhau liên tiếp |
| dppsum027 | PREFIX027 | Đếm lần tăng giữa hai vị trí liên tiếp |
| dppsum028 | PREFIX028 | Tổng trị tuyệt đối của chênh lệch liên tiếp |
| dppsum029 | PREFIX029 | Đếm lần đổi tính chẵn lẻ |
| dppsum030 | PREFIX030 | Tổng mức tăng, bỏ qua các lần giảm |

Mỗi bài có hai ví dụ, hướng dẫn giải, lời giải C++ độc lập, bộ sinh, verifier, checker và hash. Không có Subtask; không xuất HTML. Giới hạn N,Q là 200000. Tổng dùng số nguyên 64 bit; độ lệch giữa hai giá trị có thể đạt 2000000000.

Cấu hình upload giữ hai nhãn `dp_prefix_sum`, `dp_sequence` và các trường giống bộ trước. Quy trình sinh và kiểm tra không thực hiện upload.

## Sinh và kiểm tra

Từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check_levels23.py --generate
```

Mỗi bài có 22 test (hai ví dụ và 20 test theo seed), gồm bốn test đạt N=Q=200000. Quy trình biên dịch đầy đủ, xác thực mọi đầu vào, sinh đáp án, chạy checker, so sánh mọi test với lời giải Python độc lập, rồi kiểm tra trên 120 dãy nhỏ vét cạn và 160 trường hợp ngẫu nhiên mỗi bài. Tất cả đoạn của các dãy nhỏ đều được xét.

Lời giải đối chiếu mức 2 lưu vị trí và trọng số từng nhóm, dùng tìm kiếm nhị phân. Mức 3 đánh số cạnh theo đầu trái, khác với cách lưu theo đầu phải trong lời giải C++. Lời giải vét cạn trực tiếp xét các phần tử hoặc cặp trong từng đoạn.

Các test có giá trị âm, 0, phần tử bằng nhau, dãy tăng/giảm, chẵn lẻ xen kẽ và hai số lẻ âm/dương. Truy vấn bao phủ một vị trí, hai vị trí kề nhau, cả dãy, đầu/cuối dãy và đoạn ngẫu nhiên. Các bài có tổng đều có đáp án vượt giới hạn 32 bit.

Bộ kiểm tra thử verifier với giá trị, tham số và đoạn sai; thử checker với kết quả sai, thiếu/thừa kết quả và định dạng khoảng trắng khác nhau. Sau cùng ghi hash, sinh lại đầu vào cùng seed và đối chiếu hash.

Kiểm tra lại dữ liệu đã sinh và chương trình đã biên dịch:

```sh
python3 custom/prefix_tests/check_levels23.py
```

Chọn một bài:

```sh
python3 custom/prefix_tests/check_levels23.py --problem dppsum028 --generate
python3 custom/dppsum028/tests/check.py
```
