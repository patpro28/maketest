# PREFIX051–PREFIX059 — Mức 05x: đoạn có nhiều phần tử thỏa điều kiện nhất

Chín bài cùng một dạng: tìm đoạn gồm đúng K phần tử liên tiếp có nhiều phần tử thỏa điều kiện nhất. Nếu nhiều đoạn cùng tốt nhất, chọn vị trí bắt đầu nhỏ nhất. Mỗi bài luôn in hai số theo thứ tự: số lượng nhiều nhất, vị trí bắt đầu sớm nhất. Nếu không có phần tử phù hợp, in `0 1`.

Tên thư mục dùng `dppsum051`–`dppsum059`; nhãn trong đề, lời giải và trường `title` dùng `PREFIX051`–`PREFIX059`.

| Mã thư mục | Nhãn | Phần tử được đếm |
| --- | --- | --- |
| dppsum051 | PREFIX051 | Số chẵn |
| dppsum052 | PREFIX052 | Số dương |
| dppsum053 | PREFIX053 | Số âm |
| dppsum054 | PREFIX054 | Chia hết cho M cố định |
| dppsum055 | PREFIX055 | Thuộc khoảng đóng [U,V] cố định |
| dppsum056 | PREFIX056 | Số chính phương |
| dppsum057 | PREFIX057 | Số nguyên tố |
| dppsum058 | PREFIX058 | Số đối xứng |
| dppsum059 | PREFIX059 | Chứa ít nhất một chữ số 7 |

Học sinh kết hợp mảng đánh dấu 0/1 với kỹ năng tìm tổng tốt nhất của đoạn dài cố định. Tính tổng tiền tố P của mảng đánh dấu; số phần tử phù hợp của đoạn kết thúc tại R là `P[R] - P[R-K]`. Chỉ cập nhật vị trí khi số lượng lớn hơn để giữ đúng đoạn đầu tiên nếu hòa. Không cần mảng prefix min/max.

Giới hạn N=200000. Bài nguyên tố có giá trị phần tử từ 0 đến 1000000; hai bài chữ số dùng giá trị từ 0 đến 1000000000; các bài còn lại cho phép từ -1000000000 đến 1000000000. Mỗi vị trí phù hợp đóng góp một đơn vị, không phải giá trị phần tử. Các vị trí trùng giá trị vẫn được đếm riêng; số chứa nhiều chữ số 7 cũng chỉ đóng góp một đơn vị.

Mỗi bài có hai ví dụ, hướng dẫn giải, lời giải C++ độc lập, bộ sinh, verifier, checker và hash. Không có Subtask; không xuất HTML. Cấu hình upload giữ `types = ['dp_prefix_sum', 'dp_sequence']` và các trường của bộ trước. Quy trình kiểm tra không thực hiện upload.

## Sinh và kiểm tra

Chạy từ thư mục gốc dự án:

```sh
python3 custom/prefix_tests/check_predicate_best.py --generate
```

Mỗi bài có 22 test (hai ví dụ và 20 test theo seed), gồm bốn test N=200000. Quy trình biên dịch các chương trình, sinh và xác thực toàn bộ đầu vào, tạo đáp án và chạy checker. Lời giải Python độc lập lưu vị trí các phần tử phù hợp, dùng tìm kiếm nhị phân đếm từng đoạn, rồi chọn theo cặp (-số lượng, vị trí).

Mỗi bài còn được kiểm tra trên 426 trường hợp vét cạn (mọi K của các dãy nhỏ tối đa 4 phần tử) và 160 trường hợp ngẫu nhiên. Cách vét cạn duyệt trực tiếp phần tử trong từng đoạn. Bài nguyên tố dùng phép chia thử ở kiểm tra nhỏ và sàng độc lập ở dữ liệu lớn. Bài chính phương dùng căn bậc hai nguyên; các bài chữ số dùng chuỗi để đối chiếu cách tách chữ số C++.

Bộ kiểm tra xác nhận có K=1, K=N, K=N-1, không phần tử phù hợp, nhiều đoạn cùng tối ưu, và trường hợp chỉ đoạn đầu hoặc chỉ đoạn cuối tốt nhất. Các test còn có số 0, số âm khi được phép, hai đầu mút U/V, M=1, chính phương lớn và các số sát nó, 0/1 không nguyên tố, số nguyên tố lớn, số đối xứng có chữ số 0 và số chứa nhiều chữ số 7.

Verifier được thử với giới hạn, tham số, dữ liệu thiếu/thừa không hợp lệ. Checker được thử sai riêng số lượng và vị trí, thiếu/thừa kết quả, ký tự không phải số và khoảng trắng khác nhau. Cuối cùng ghi `hash.json`, sinh lại đầu vào với cùng seed và đối chiếu hash.

Kiểm tra lại dữ liệu và chương trình đã sinh:

```sh
python3 custom/prefix_tests/check_predicate_best.py
```

Chọn một bài:

```sh
python3 custom/prefix_tests/check_predicate_best.py --problem dppsum057 --generate
python3 custom/dppsum057/tests/check.py
```
