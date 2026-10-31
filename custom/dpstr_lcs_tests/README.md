# DPSTR — Dãy con chung của hai xâu

## Phân mức và danh sách bài

| Dải mã | Mức độ | Nội dung |
| --- | --- | --- |
| dpstr100–dpstr129 | Nhập môn | LCS cơ bản, truy vết và ứng dụng trực tiếp |
| dpstr130–dpstr149 | Trung bình | Trọng số, chi phí và điều kiện ký tự cuối |
| dpstr150–dpstr199 | Khó | Ký tự bắt buộc, giới hạn nguyên âm và ký tự cuối |

Đã tạo các bài sau; các mã còn lại được để trống cho những bài bổ sung sau này.

| Mã | Tên bài | Giới hạn mỗi xâu | Thuật toán chính |
| --- | --- | --- | --- |
| [dpstr100](../dpstr100/task.md) | Thông điệp chung | 1.000 | Độ dài LCS, $O(NM)$ |
| [dpstr101](../dpstr101/task.md) | Khôi phục thông điệp | 1.000 | Bảng LCS và truy vết, $O(NM)$ |
| [dpstr102](../dpstr102/task.md) | Xóa để giống nhau | 1.000 | $N+M-2LCS$ |
| [dpstr103](../dpstr103/task.md) | Bản ghi hợp nhất | 1.000 | $N+M-LCS$ |
| [dpstr130](../dpstr130/task.md) | Thông điệp có điểm | 600 | LCS có trọng số theo chữ, $O(NM)$ |
| [dpstr131](../dpstr131/task.md) | Bảo tồn ký tự quý | 600 | Chi phí xóa theo vị trí, $O(NM)$ |
| [dpstr132](../dpstr132/task.md) | Thông điệp kết thúc đúng chữ | 600 | LCS tiền tố và cặp ký tự cuối, $O(NM)$ |
| [dpstr150](../dpstr150/task.md) | Ký tự bắt buộc | 300 | Trạng thái có chứa ký tự bắt buộc, $O(NM)$ |
| [dpstr151](../dpstr151/task.md) | Giới hạn nguyên âm | 200 | Thêm giới hạn $K\le5$, $O(NM(K+1))$ |
| [dpstr152](../dpstr152/task.md) | Thông điệp không lặp cạnh nhau | 250 | Lưu chữ cuối trong ba chữ `a`, `b`, `c`, $O(3^2NM)$ |

Mỗi bài có `task.md` theo mẫu knapsack, hai ví dụ, `solution.md`, lời giải C++11 và Python 3, bộ sinh, verifier, checker và `hash.json`. Không thêm Subtask và không xuất HTML. Các lời giải chỉ trình bày thuật toán và chứng minh; tài liệu kiểm thử nằm ở đây.

## Cấu hình chấm

Tất cả bài dùng `timelimit = 0.5` và cấu hình:

```toml
[upload]
time_limit = 0.5
group = '03'
classes = 'C'
types = ['dp_string']
allowed_languages = ['PY3', 'CPP11', 'CPP14', 'CPP17', 'CPP20', 'JAVA8', 'C', 'PAS']
partial = true
```

### Checker riêng của dpstr101

Bài truy vết cho phép in bất kỳ LCS tối ưu nào. `custom/dpstr101/checker.cpp` đọc hai xâu đầu vào, kiểm tra độ dài khai báo, thứ tự xuất hiện trong cả hai xâu, độ dài tối ưu và token dư. Checker chấp nhận cả `ac` và `bc` cho cặp `abc`, `bac`; không so sánh xâu nộp với một đáp án cố định.

API nhập bài đã hỗ trợ tải mã custom checker; xem `PROBLEM_IMPORT_API.md` ở gốc dự án. `[upload]` của `dpstr101` đặt `checker = 'custom'`: lệnh `python3 generate.py -u dpstr101` sẽ gửi `checker.cpp` lên endpoint `/checker` trước khi nhập ZIP. Manifest ZIP không đặt lại checker, nên hệ thống giữ checker riêng vừa cài và chấp nhận mọi LCS tối ưu. Chín bài còn lại dùng checker `standard`.

Không thực hiện upload trong quá trình tạo hoặc kiểm tra bộ bài.

## Sinh và kiểm tra

Từ thư mục gốc dự án:

```sh
python3 custom/dpstr_lcs_tests/check.py
python3 custom/dpstr_lcs_tests/check.py --problem dpstr101 dpstr151
```

Chỉ khi đã chủ động thay đổi dữ liệu và cần cập nhật mã băm:

```sh
python3 custom/dpstr_lcs_tests/check.py --update-hashes
```

Có thể chạy riêng `tests/check.py` trong từng bài. Quy trình gọi trực tiếp các bước của `Problem`, không dùng `--dev` hoặc `--test`, không xuất HTML và không kết nối máy chủ.

Mỗi bài có 32 cặp test nền: 2 ví dụ, 10 biên, 8 nhỏ, 6 ngẫu nhiên, 6 lớn. Riêng `dpstr150` có thêm 8 cặp hồi quy, tổng cộng 40 cặp; xem `custom/dpstr150/tests/README.md`. Bộ kiểm tra thực hiện:

- Biên dịch lời giải C++ theo C++11; biên dịch bộ sinh và công cụ theo C++17, bật cảnh báo lỗi.
- Sinh và xác thực mọi đầu vào, tạo đáp án bằng C++, chấm cả C++ và Python trong 0,5 giây mỗi test.
- Đối chiếu mọi đáp án với lời giải Python: DP xóa trực tiếp cho bài 102; DP siêu dãy trực tiếp cho bài 103; tối đa chi phí giữ lại cho bài 131; đảo xâu cho bài 132; ghép hai phía của một ký tự bắt buộc cho bài 150; đếm nguyên âm chính xác cho bài 151; vị trí xuất hiện kế tiếp cho bài 152.
- Vét cạn tất cả 20 test ví dụ/biên/nhỏ của mỗi bài bằng cách liệt kê các dãy con của cả hai xâu; với `dpstr150`, kiểm tra thêm 6 test hồi quy ngắn, tổng cộng 26 test. Với chi phí theo vị trí, lưu tổng chi phí giữ lại lớn nhất cho mỗi xâu con ở từng phía.
- Vét cạn mọi cặp xâu nhị phân có độ dài từ 1 đến 3: 196 cặp mỗi bài; thêm 100 trường hợp ngẫu nhiên và các trường hợp đặc trưng.
- Thử verifier với sai độ dài, sai bảng chữ cái, thiếu/thừa dữ liệu, chi phí ngoài giới hạn, ký tự bắt buộc sai và $K$ ngoài giới hạn.
- Thử checker với đáp án đúng/sai, token dư, kết quả rỗng, số nguyên 64 bit và kết quả $-1$. Riêng bài 101 kiểm tra nhiều LCS tối ưu, số ký tự không khớp khai báo, xâu không phải dãy con, đáp án ngắn hơn tối ưu và trường hợp LCS rỗng.
- Kiểm tra cả hai độ dài cùng đạt tối đa, đáp án vượt 32 bit của hai bài trọng số, đồng thời $N=M=200,K=5$ của bài 151.
- Kiểm tra bộ sinh tái lập được từng test, đối chiếu `hash.json`, cấu trúc đề, ví dụ, nội dung lời giải và cấu hình `[upload]`.

Test có các xâu đồng nhất, không giao ký tự, nhiều chữ lặp, khối ký tự đảo thứ tự, xâu xen kẽ có nhiều LCS, xâu độ dài chênh lệch lớn, điểm bằng 0/cực đại, nguyên âm lặp và ký tự bắt buộc không xuất hiện ở cả hai phía. Các trường hợp trọng số còn kiểm tra việc phương án ngắn hơn có điểm cao hơn và các vị trí có cùng chữ nhưng chi phí khác nhau.

## Kết quả kiểm tra ngày 28/10/2026

Toàn bộ 10 bài đã qua quy trình trên: 320 cặp input/output, 200 lượt vét cạn trên các test đã sinh và 3.097 trường hợp vét cạn bổ sung. Hai lời giải C++ và Python đều được chấm AC trong giới hạn 0,5 giây trên bộ test cục bộ. Cấu trúc đề, verifier, checker, tính tái lập và toàn bộ 640 mục mã băm đều hợp lệ. Phần kiểm tra cấu hình upload đã được cập nhật để xác nhận `dpstr101` đính kèm đúng mã nguồn checker, còn chín bài còn lại giữ checker `standard`.

## Bổ sung hồi quy ngày 30/10/2026

Đã thêm 8 test cho `dpstr150` để bắt lỗi dùng sự xuất hiện của ký tự bắt buộc trong tiền tố thay cho điều kiện trên dãy con được chọn. Tổng dữ liệu của bộ bài tăng lên 328 cặp. Quy trình kiểm tra riêng `dpstr150` yêu cầu cả hai lời giải đúng đạt trên 40 cặp và mô hình thuật toán sai bị checker từ chối trên đủ 8 test mới; mã băm được cập nhật tương ứng. Nội dung 32 cặp test cũ của bài được giữ nguyên.
