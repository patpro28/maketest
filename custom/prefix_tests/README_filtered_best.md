# PREFIX060–PREFIX069 — Mức 06x: tối ưu tổng sau khi lọc điều kiện

Mười bài cùng một dạng: trong các đoạn dài đúng K có ít nhất T phần tử phù hợp, chọn đoạn có tổng lớn nhất. Tổng được tính trên toàn bộ K phần tử, kể cả phần tử không phù hợp. Nếu hòa, chọn vị trí bắt đầu nhỏ nhất.

Tên thư mục dùng `dppsum060`–`dppsum069`; nhãn trong đề, lời giải và trường `title` dùng `PREFIX060`–`PREFIX069`.

| Mã thư mục | Nhãn | Phần tử được dùng để kiểm tra điều kiện đếm |
| --- | --- | --- |
| dppsum060 | PREFIX060 | Số chẵn |
| dppsum061 | PREFIX061 | Số dương |
| dppsum062 | PREFIX062 | Số âm |
| dppsum063 | PREFIX063 | Chia hết cho M cố định |
| dppsum064 | PREFIX064 | Thuộc khoảng đóng [U,V] cố định |
| dppsum065 | PREFIX065 | Số chính phương |
| dppsum066 | PREFIX066 | Số nguyên tố |
| dppsum067 | PREFIX067 | Số đối xứng |
| dppsum068 | PREFIX068 | Chứa ít nhất một chữ số 7 |
| dppsum069 | PREFIX069 | Có tổng chữ số bằng H cố định |

Mỗi bài in tổng lớn nhất và vị trí bắt đầu sớm nhất. Nếu không có đoạn đủ điều kiện, in `NONE`. Tổng hợp lệ có thể bằng -1 nên không dùng riêng giá trị -1 để biểu diễn không có đáp án. Khi T=0, mọi đoạn dài đúng K đều đủ điều kiện.

Bước mới so với 05x: dùng một prefix đếm để lọc đoạn và một prefix tổng để đánh giá đoạn. Lọc bằng `C[R] - C[R-K] >= T`, rồi so sánh tổng `S[R] - S[R-K]`. Dùng biến đánh dấu đã tìm thấy đoạn hợp lệ để xử lý cả tổng âm và trường hợp không có đáp án.

Giới hạn N=200000, 1<=K<=N, 0<=T<=K. Bài nguyên tố giới hạn giá trị từ 0 đến 1000000; ba bài chữ số dùng giá trị từ 0 đến 1000000000. Các bài còn lại cho phép giá trị từ -1000000000 đến 1000000000. Tổng cần số nguyên 64 bit.

Mỗi bài có ba ví dụ: đoạn có tổng lớn nhất toàn cục bị loại, không có đoạn đủ điều kiện, và nhiều đoạn đủ điều kiện cùng tổng. Có đầy đủ hướng dẫn giải, lời giải C++ độc lập, bộ sinh, verifier, checker và hash. Không có Subtask; không xuất HTML. Upload giữ `types = ['dp_prefix_sum', 'dp_sequence']` và các trường của bộ trước. Quy trình kiểm tra không thực hiện upload.

## Sinh và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check_filtered_best.py --generate
```

Mỗi bài có 23 test (ba ví dụ và 20 test theo seed), gồm bốn test N=200000. Quy trình biên dịch đầy đủ, sinh và xác thực mọi đầu vào, tạo đáp án và chạy checker. Lời giải đối chiếu Python dùng tổng trượt cho tổng toàn đoạn, tìm kiếm nhị phân trên vị trí phần tử phù hợp để kiểm tra số lượng và chọn theo cặp (-tổng, vị trí).

Mỗi bài còn có 294 trường hợp vét cạn, xét mọi K và mọi T từ 0 đến K trên dãy có tối đa ba phần tử, cộng 160 trường hợp ngẫu nhiên. Cách vét cạn duyệt trực tiếp từng phần tử của từng đoạn. Nguyên tố dùng phép chia thử ở các ca nhỏ và sàng độc lập ở dữ liệu lớn; chính phương dùng căn bậc hai nguyên; các bài chữ số dùng chuỗi để đối chiếu cách tách chữ số C++.

Bộ kiểm tra xác nhận K=1, K=N, K=N-1, T=0, T=K, có/không có đáp án, nhiều đoạn hòa, trường hợp bước lọc thay đổi đáp án và tổng dương lớn vượt 32 bit. Với các bài cho phép số âm, có cả tổng âm lớn vượt 32 bit.

Verifier được thử với tham số, giá trị ngoài giới hạn và dữ liệu thiếu/thừa. Checker được thử cả hai nhánh kết quả số và NONE, sai riêng tổng/vị trí, đầu ra thiếu/thừa, sai chữ hoa/thường và khoảng trắng khác nhau. Sau cùng ghi `hash.json`, sinh lại đầu vào cùng seed và đối chiếu hash.

Kiểm tra lại dữ liệu và chương trình đã sinh:

```sh
python3 custom/prefix_tests/check_filtered_best.py
```

Chọn riêng một bài:

```sh
python3 custom/prefix_tests/check_filtered_best.py --problem dppsum061 --generate
python3 custom/dppsum061/tests/check.py
```
