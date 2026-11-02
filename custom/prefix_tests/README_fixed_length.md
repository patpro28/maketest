# PREFIX031–PREFIX040 — Đếm đoạn có độ dài cố định

Mười bài cùng một dạng: đếm các đoạn gồm đúng K phần tử liên tiếp có tổng thỏa điều kiện. Mỗi bài chỉ có một dãy và một bộ tham số, không có truy vấn L,R. Các đoạn được phép chồng lấn; không nối vòng.

Tên thư mục dùng `dppsum031`–`dppsum040`; nhãn trong đề, lời giải và `info.toml` dùng `PREFIX031`–`PREFIX040`.

| Mã thư mục | Nhãn | Điều kiện của tổng đoạn |
| --- | --- | --- |
| dppsum031 | PREFIX031 | Bằng T |
| dppsum032 | PREFIX032 | Lớn hơn T |
| dppsum033 | PREFIX033 | Nhỏ hơn T |
| dppsum034 | PREFIX034 | Thuộc khoảng đóng [U,V] |
| dppsum035 | PREFIX035 | Chia hết cho M |
| dppsum036 | PREFIX036 | Chia M dư C |
| dppsum037 | PREFIX037 | Là số chẵn |
| dppsum038 | PREFIX038 | Có tổng chữ số bằng H |
| dppsum039 | PREFIX039 | Là số chính phương |
| dppsum040 | PREFIX040 | Là số đối xứng |

Công thức chung: tính tổng tiền tố P, duyệt đầu phải R từ K đến N và kiểm tra tổng `P[R] - P[R-K]`. Mỗi đầu phải tương ứng duy nhất một đoạn, nên học sinh chỉ cần thay điều kiện kiểm tra ở mỗi bài.

Các bài 036, 038 và 040 dùng phần tử không âm để tập trung vào điều kiện và tránh quy ước biểu diễn số âm. Các bài còn lại cho phép phần tử âm. Số 0 được xử lý rõ trong từng đề. N không vượt 200000; tổng có thể đạt trị tuyệt đối 200000000000000 và cần số nguyên 64 bit.

Mỗi bài có hai ví dụ, hướng dẫn giải, lời giải C++ độc lập, bộ sinh, verifier, checker và hash. Không có Subtask; không xuất HTML. Cấu hình upload giữ `types = ['dp_prefix_sum', 'dp_sequence']` cùng các trường của bộ trước. Quy trình kiểm tra không thực hiện upload.

## Sinh và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check_fixed_length.py --generate
```

Mỗi bài có 22 test: hai ví dụ và 20 test theo seed, gồm bốn test đạt N=200000. Quy trình biên dịch các chương trình, sinh và xác thực đầu vào, tạo đáp án và chạy checker. Toàn bộ dữ liệu được đối chiếu với lời giải Python dùng tổng trượt thay vì mảng prefix. Bài chính phương dùng căn bậc hai nguyên; bài chữ số và đối xứng dùng chuỗi để đối chiếu cách tách chữ số C++.

Bộ kiểm tra còn xét mọi K từ 1 đến N trên các dãy nhỏ có tối đa 4 phần tử, tổng cộng 426 trường hợp, rồi thêm 160 trường hợp ngẫu nhiên mỗi bài. Phương án vét cạn tính lại trực tiếp tổng từng đoạn. Các test có K=1, K=N, đoạn chồng lấn, đoạn hợp lệ cuối dãy, tổng âm/0, tổng bằng ngưỡng, U=V, M=1, H=0/135, số chính phương và đối xứng lớn. Mọi bài đều có tổng vượt miền số nguyên 32 bit.

Các phép thử verifier/checker gồm giá trị hoặc tham số ngoài giới hạn, K=0 hoặc K>N, dữ liệu thiếu/thừa, đầu ra sai, âm, thiếu/thừa số và khoảng trắng khác nhau. Sau cùng ghi hash, sinh lại đầu vào với cùng seed và xác nhận hash không đổi.

Kiểm tra lại dữ liệu và chương trình đã sinh:

```sh
python3 custom/prefix_tests/check_fixed_length.py
```

Chọn một bài:

```sh
python3 custom/prefix_tests/check_fixed_length.py --problem dppsum039 --generate
python3 custom/dppsum039/tests/check.py
```
