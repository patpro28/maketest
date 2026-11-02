# PREFIX041–PREFIX050 — Đoạn dài cố định có tổng tốt nhất

Bộ bài tiếp nối nhóm đếm đoạn dài đúng K. Học sinh vẫn dùng tổng tiền tố để tính tổng từng đoạn; bước tiếp theo là so sánh các tổng, lưu vị trí và xử lý các đoạn bằng tổng.

Tên thư mục dùng `dppsum041`–`dppsum050`; nhãn trong đề, lời giải và trường `title` dùng `PREFIX041`–`PREFIX050`.

| Mã thư mục | Nhãn | Kết quả cần in |
| --- | --- | --- |
| dppsum041 | PREFIX041 | Tổng lớn nhất |
| dppsum042 | PREFIX042 | Tổng nhỏ nhất |
| dppsum043 | PREFIX043 | Vị trí bắt đầu nhỏ nhất của đoạn có tổng lớn nhất |
| dppsum044 | PREFIX044 | Vị trí bắt đầu nhỏ nhất của đoạn có tổng nhỏ nhất |
| dppsum045 | PREFIX045 | Vị trí bắt đầu lớn nhất của đoạn có tổng lớn nhất |
| dppsum046 | PREFIX046 | Vị trí bắt đầu lớn nhất của đoạn có tổng nhỏ nhất |
| dppsum047 | PREFIX047 | Số đoạn đạt tổng lớn nhất |
| dppsum048 | PREFIX048 | Số đoạn đạt tổng nhỏ nhất |
| dppsum049 | PREFIX049 | Tổng lớn nhất, vị trí đầu tiên, số đoạn tối ưu |
| dppsum050 | PREFIX050 | Tổng nhỏ nhất, vị trí cuối cùng, số đoạn tối ưu |

Tất cả đoạn đều có đúng K phần tử, được phép chồng lấn và không nối vòng. Mỗi đoạn được phân biệt bằng vị trí bắt đầu. K nằm từ 1 đến N nên luôn có ít nhất một đoạn để xét, kể cả khi dãy toàn âm.

Công thức chung: tổng đoạn kết thúc tại R là `P[R] - P[R-K]`. Khởi tạo kết quả bằng tổng đoạn đầu tiên. Khi tổng tốt hơn thì cập nhật, khi bằng nhau thì xử lý vị trí/số lượng theo yêu cầu từng bài. Chỉ dùng tổng tiền tố và so sánh các tổng đoạn.

Giới hạn N=200000, giá trị phần tử từ -1000000000 đến 1000000000. Các tổng cần số nguyên 64 bit. Mỗi bài có đề, hai ví dụ, hướng dẫn giải, lời giải C++ độc lập, bộ sinh, verifier, checker và hash. Không có Subtask; không xuất HTML.

Cấu hình upload giữ hai nhãn `dp_prefix_sum`, `dp_sequence` và các trường như nhóm trước. Quy trình kiểm tra không thực hiện upload.

## Sinh và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check_fixed_best.py --generate
```

Mỗi bài có 22 test (hai ví dụ và 20 test theo seed), gồm bốn test N=200000. Quy trình biên dịch các chương trình, sinh và xác thực đầu vào, tạo đáp án và chạy checker. Tất cả dữ liệu được đối chiếu với lời giải Python dùng tổng trượt và sắp xếp cặp (tổng, vị trí), độc lập với lời giải C++ dùng prefix và giữ kết quả tốt nhất khi duyệt.

Mỗi bài còn được kiểm tra trên 426 trường hợp vét cạn (mọi K của dãy tối đa 4 phần tử từ tập {-1,0,1}) và 160 trường hợp ngẫu nhiên. Cách vét cạn cộng trực tiếp từng đoạn rồi lấy tổng tối ưu và danh sách mọi vị trí đạt tổng đó.

Bộ kiểm tra xác nhận có K=1, K=N, K=N-1, dãy toàn âm, nhiều đoạn cùng tối ưu, trường hợp chỉ có đoạn đầu hoặc đoạn cuối tối ưu, và tổng tối ưu dương/âm vượt giới hạn 32 bit. Các phép thử verifier/checker bao gồm giới hạn sai, dữ liệu thiếu/thừa, kết quả sai và định dạng khoảng trắng. Bài có ba kết quả còn được thử sai riêng vị trí và số lượng.

Sau cùng ghi `hash.json`, sinh lại đầu vào cùng seed và xác nhận hash không đổi.

Kiểm tra lại dữ liệu và chương trình đã sinh:

```sh
python3 custom/prefix_tests/check_fixed_best.py
```

Chọn một bài:

```sh
python3 custom/prefix_tests/check_fixed_best.py --problem dppsum049 --generate
python3 custom/dppsum049/tests/check.py
```
