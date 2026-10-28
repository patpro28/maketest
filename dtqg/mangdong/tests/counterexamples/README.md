# Kiểm tra lỗi gộp theo kích thước của DSU rollback

## Lỗi trong code được gửi

Điều kiện đang viết là:

```cpp
if (szr[ru] + szb[ru] < szr[rv] + szb[ru]) swap(ru, rv);
```

Hai vế cùng có `szb[ru]`, nên thực chất chỉ so sánh `szr[ru] < szr[rv]`. Cần sửa thành:

```cpp
if (szr[ru] + szb[ru] < szr[rv] + szb[rv]) swap(ru, rv);
```

Trong code này, `szr` đếm màu 1 và `szb` đếm màu 0. Việc đảo tên hai màu không làm sai tích số cặp. Tuy nhiên, một thành phần chỉ có màu 0 luôn có `szr=0`; điều kiện sai không dùng kích thước thật và có thể tạo chuỗi cha dài tuyến tính. `find` không nén đường đi là đúng với rollback, nên không có cơ chế khác rút ngắn chuỗi này.

Ví dụ các lệnh gộp `(2,1), (3,2), (4,3), ...` trên các đỉnh màu 0 sẽ lần lượt tạo `1 -> 2 -> 3 -> 4 -> ...`. Sau đó thêm các cạnh tạo chu trình từ đỉnh 1 khiến nhiều lần `find(1)` phải đi hết chuỗi. Với điều kiện gộp đúng, chiều cao được giữ ở $O(\log N)$.

## Ba test chính thức bổ sung

| Test chính thức | Bản lưu | N | Q | Đáp án |
| --- | --- | ---: | ---: | --- |
| `stress_00` | `blue_chain.in` | 100001 | 200000 | Hai dòng đều là 100000 |
| `stress_01` | `mixed_large_pairs.in` | 120000 | 200000 | Ba dòng đều là 3200000000 |
| `stress_02` | `rollback_cycles.in` | 99501 | 200000 | 500 dòng 99500, rồi một dòng 0 |

Tên `blue_chain` nói tới mảng `szb` trong code được hỏi; các đỉnh của chuỗi có giá trị màu **0** theo dữ liệu đề. Cả ba test đều chứa hai màu và có câu trả lời khác 0, nên không vượt qua được bằng cách chỉ xử lý nhanh trường hợp toàn bộ đỉnh cùng màu.

- `stress_00`: dựng đường đi 100000 đỉnh màu 0, nối thêm một đỉnh màu 1, rồi thêm các cạnh từ đỉnh đầu tới những đỉnh trên đường đi. Các cạnh thêm sau tạo chu trình nhưng vẫn buộc gọi `find`.
- `stress_01`: tương tự, với 80000 đỉnh màu 0 và một cây 40000 đỉnh màu 1. Đáp án vượt 32 bit.
- `stress_02`: dựng đường đi 99500 đỉnh màu 0, nối thêm một đỉnh màu 1 và thêm các cạnh tạo chu trình. Sau đó xóa 500 cạnh chu trình, hỏi sau mỗi lần xóa; cuối cùng xóa cầu nối đỉnh màu 1 và hỏi lại. Các câu trả lời đầu là 99500, câu cuối là 0.

Hai test đầu không có xóa, thuộc subtask 2. Test cuối thuộc subtask 3. Bộ chính thức hiện có 48 test; manifest vẫn chia điểm 30/30/40. Bộ kiểm tra đối chiếu từng byte của ba test với các bản lưu ở đây, kiểm tra verifier, đáp án oracle và checker.

Tạo lại các bản lưu:

```sh
python3 dtqg/mangdong/tests/counterexamples/generate.py
```

Sinh và kiểm tra toàn bộ bài, cập nhật hash và manifest:

```sh
python3 dtqg/mangdong/tests/check.py --update-hashes
```

## Đánh giá code

Code gốc được biên dịch bằng GCC C++17 `-O2`. Trên 45 test ban đầu, 44 test đúng và một test `sub2_04` vượt 6 giây. Vì vậy bộ cũ đã phát hiện được vấn đề; ba test mới bổ sung các trường hợp có chủ đích, không dựa vào trường hợp chỉ có một màu.

Ba test mới đều làm code gốc vượt 6 giây trên máy kiểm tra. Bản chỉ sửa điều kiện gộp được đối chiếu với đáp án của cả ba test. Các kết quả đo chi tiết được ghi bên dưới sau khi chạy lại test chính thức.

## Một điểm cần sửa cho đúng biểu diễn thời gian

Khi xóa cạnh tại thao tác `i`, khoảng tồn tại nên kết thúc tại `i-1`, thay vì `i`. Code hiện tại vẫn cho đúng câu trả lời vì thao tác xóa và thao tác hỏi nằm ở hai dòng khác nhau, nên không in trạng thái tại chính dòng xóa. Đây không phải nguyên nhân TLE.

Không thêm nén đường đi vào `find` khi chưa lưu và hoàn tác đầy đủ các thay đổi cha. Sửa phép so sánh kích thước đã khôi phục cận chiều cao logarithm mà DSU rollback cần.

## Kết quả chạy lại test chính thức

Biên dịch GCC C++17 `-O2`, ngưỡng dừng 6 giây theo `timelimit` cục bộ. Bản sửa chỉ thay `szb[ru]` ở vế phải thành `szb[rv]`, không thay phần nào khác:

| Test | Code gốc | Chỉ sửa phép so sánh | Lời giải mẫu |
| --- | --- | --- | --- |
| stress_00 | TLE (>6s) | AC (0.068s) | AC (0.378s) |
| stress_01 | TLE (>6s) | AC (0.068s) | AC (0.403s) |
| stress_02 | TLE (>6s) | AC (0.068s) | AC (0.391s) |

Bản sửa qua cả 48 test chính thức và 872 trường hợp nhỏ đối chiếu. Thời gian lớn nhất đo trên 48 test là 0.103 giây trên máy kiểm tra. Thời gian đo phụ thuộc máy; cấu hình upload hiện có ngưỡng 1 giây. Hash và manifest 30/30/40 đã được cập nhật và đối chiếu.
