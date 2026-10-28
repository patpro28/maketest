# Bộ luyện MANGDONG – MATMA – TACHLO

Ba bài tự biên soạn theo thứ tự tăng dần độ khó, ưu tiên kỹ thuật khác bộ TRAMTIEPTE – DOITUYEN – CHIACHUYEN.

| Bài | Trọng tâm | Thuật toán đầy đủ | Giới hạn thời gian |
| --- | --- | --- | --- |
| MANGDONG | DSU rollback, chia để trị theo thời gian | $O(N+Q\log Q\log N)$ | 6 giây |
| MATMA | Aho–Corasick, max-plus | $O(S^3\log L)$, $S\le81$ | 5 giây |
| TACHLO | DP Monge, chia để trị, cửa sổ di động | $O(KN\log N)$ | 6 giây |

Mỗi thư mục bài có đề tiếng Việt, ba ví dụ, `solution.md`, lời giải C++17, checker, verifier, bộ sinh, `hash.json` và `manifest.json`. Không xuất HTML.

## Subtask và điểm

Mỗi bài có ba subtask 30%–30%–40%. Ràng buộc nằm trong đề; phân nhóm testcase và điểm được lưu trong `manifest.json`. Dùng `[upload].manifest` trong `info.toml` để nối manifest vào Problem Import API của dự án; MANGDONG đã cấu hình trường này. Không thực hiện upload trong quy trình tạo và kiểm tra bài.

Manifest sử dụng ba cặp dòng `S`/`E` có điểm 30, 30, 40. Mỗi testcase xuất hiện đúng một lần. Nhóm `sub1.cpp`, `sub2.cpp`, `sub3.cpp` được đưa vào subtask tương ứng; test biên và ví dụ được phân vào subtask có ràng buộc phù hợp. Quy trình kiểm tra đọc lại dữ liệu từng test để xác nhận điều kiện subtask, không chỉ suy từ tên file.

Các file `.gitignore` cục bộ cho phép theo dõi `manifest.json`, dù quy tắc gốc bỏ qua các file JSON khác ngoài `hash.json`.

## Sinh và kiểm tra

Từ thư mục gốc dự án:

```sh
python3 custom/hsgadvanced_tests/check.py
```

Sau khi chủ động sửa dữ liệu hoặc cách phân nhóm, cập nhật cả hash và manifest:

```sh
python3 custom/hsgadvanced_tests/check.py --update-hashes
```

Kiểm tra từng bài:

```sh
python3 dtqg/mangdong/tests/check.py
python3 dtqg/matma/tests/check.py
python3 dtqg/tachlo/tests/check.py
```

Mỗi bài có **45 test nền**: 3 ví dụ, 12 test biên, 8 test cho subtask 1, 8 test cho subtask 2 và 14 test cho subtask 3. MANGDONG có thêm 3 test `stress.cpp` bắt lỗi gộp theo kích thước DSU, thành **48 test**, tổng cả bộ **138 test**. Input/output sinh tại `in/`, `out/`; hash theo đúng `Problem.calc_hashes()` của dự án. Bộ kiểm tra tìm thư mục bài trong `dtqg/`, hoặc `custom/` nếu chưa di chuyển. Không cần thư viện bổ sung.

## Các bước kiểm tra

- Biên dịch C++17 với cảnh báo được coi là lỗi; chạy lại lời giải với giới hạn thời gian trong `info.toml`.
- Verifier kiểm tra mọi dữ liệu sinh, gồm điều kiện tồn tại đường khi thêm/xóa, ký tự mẫu và tổng độ dài mẫu, miền giá trị kiện hàng.
- Đối chiếu tất cả test sinh với oracle. Kiểm tra tính xác định của seed đầu mỗi nhóm.
- So sánh cấu trúc đề với mẫu knapsack: tiêu đề, thứ tự heading, bảng 30/30/40, khối `text`, nội dung mẫu và phần giải thích ở cuối.
- Đọc lại manifest và xác nhận tổng điểm 100, testcase đủ và không trùng, mọi testcase thỏa ràng buộc subtask được gán.
- Tạo dữ liệu đầu vào sai để kiểm tra verifier; thử đáp án sai, thiếu/thừa số, số thực, từ không phải số và số quá lớn để kiểm tra checker.
- Đối chiếu và lưu `hash.json` sau khi tất cả bước đạt.

## Cách kiểm chứng độc lập

**MANGDONG:** Dữ liệu nhỏ dùng BFS cho từng truy vấn; dữ liệu chỉ thêm dùng DSU trực tuyến. Dữ liệu lớn có xóa dùng chia khối thời gian độc lập: DSU nền cho các cạnh không đổi trong khối và DSU tạm cho những cạnh thay đổi. Không dùng rollback hoặc segment tree thời gian trong oracle. Test có cạnh tạo chu trình, xóa/thêm lại, đảo đầu cạnh, cạnh sống tới cuối, cùng một màu và số cặp vượt 32 bit. Một test lớn dựng hai thành phần đơn sắc 50000 đỉnh rồi liên tục bật/tắt cầu nối.

Ba test `stress_00`–`stress_02` có chuỗi dài màu 0 và các cạnh tạo chu trình để bắt việc chỉ so sánh số đỉnh màu 1 thay vì tổng kích thước. Mọi test này đều có hai màu; một test có số cặp vượt 32 bit, một test có xóa cạnh và câu trả lời thay đổi về 0. Chúng được đối chiếu với bản lưu tại `dtqg/mangdong/tests/counterexamples/` và công thức đếm cặp riêng, ngoài oracle chung.

**MATMA:** Vét cạn mọi xâu với $L\le8$. Với xâu dài hơn, dựng tập trạng thái từ các tiền tố mẫu và tìm hậu tố bằng so sánh xâu trực tiếp, không dùng failure link. Dùng DP tuyến tính tới $10^5$, rồi một cài đặt ma trận với chiều vector khác lời giải mẫu cho $L$ lớn. Test có mẫu trùng, điểm triệt tiêu nhau, mẫu là hậu tố của mẫu khác, các lần xuất hiện chồng lấn, mọi phương án đều âm, mẫu dài 80 và độ dài quanh lũy thừa hai.

**TACHLO:** Liệt kê mọi tập điểm cắt khi $N\le14$; DP trực tiếp khi $N\le3000$. Test lớn có công thức riêng cho $K=1$ hoặc dãy tuần hoàn với các loại khác nhau trong chu kỳ. Các test lớn còn lại dùng cài đặt tối ưu thứ hai trên dãy đảo, quét điểm chia theo chiều ngược, phá hòa ngược và đảo thứ tự duyệt nhánh. Hai cài đặt tối ưu cùng dựa trên tính chất Monge; các mức nhỏ được đối chiếu bằng vét cạn và DP không tối ưu để kiểm tra cơ sở đó. Test có mọi loại bằng nhau, mọi loại khác nhau, tần suất nhỏ/lớn, nhiều điểm chia hòa nhau, $K=N$ ở dữ liệu nhỏ và chi phí vượt 32 bit.

## Kết quả kiểm tra bộ bài

| Bài | Test chính thức | Đối chiếu nhỏ | Đầu vào sai bị từ chối | Kiểm tra checker | Số test subtask 1/2/3 | Kết quả |
| --- | ---: | ---: | ---: | ---: | --- | --- |
| MANGDONG | 48 | 872 | 15 | 31 | 23/10/15 | Đạt |
| MATMA | 45 | 555 | 13 | 27 | 18/9/18 | Đạt |
| TACHLO | 45 | 881 | 10 | 27 | 23/8/14 | Đạt |
| Tổng | 138 | 2308 | 38 | 85 | — | Đạt |

Mọi ví dụ khớp đề, lời giải mẫu qua giới hạn thời gian, hash và manifest đã được đối chiếu. Điểm ba subtask là 30/30/40, không phụ thuộc số testcase trong nhóm. Các số liệu ghi nhận bộ bài hiện tại; cần chạy lại quy trình sau khi sửa nguồn hoặc dữ liệu.
