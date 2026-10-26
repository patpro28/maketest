# DPSTRING00–09 — DP tiền tố trên xâu

Bộ bài dành cho học sinh THCS, tập trung vào quyết định chọn, xóa, giữ hoặc thay ký tự khi duyệt xâu. Trạng thái lưu loại ký tự, ký tự cuối hoặc một phần đuôi ngắn. Không có bài dãy tăng/LIS, LCS, đếm dãy con, chia xâu, hay DP trên đoạn.

| Mã | Tên bài | Trọng tâm | Thời gian lời giải C++ |
| --- | --- | --- | --- |
| dpstring00 | Xóa chữ trùng nhau | Chọn/bỏ; kết thúc bằng `a` hoặc `b` | $O(N)$ |
| dpstring01 | Giai điệu nguyên âm | Dãy con có điểm lớn nhất; hai loại ký tự xen kẽ | $O(N)$ |
| dpstring02 | Biển hiệu không lặp | Chi phí xóa; 26 trạng thái ký tự cuối | $O(26N)$ |
| dpstring03 | Không có bộ ba | Ký tự cuối và độ dài nhóm cuối | $O(N)$ |
| dpstring04 | Sơn lại dải đèn | Chi phí thay ký tự; ba màu | $O(3^2N)$ |
| dpstring05 | Điền tín hiệu | Dấu `?`, ký tự cố định, chi phí chuyển có hướng | $O(N)$ |
| dpstring06 | Nhịp đọc dễ nhớ | Giới hạn khác nhau cho nguyên âm và phụ âm | $O(N)$ |
| dpstring07 | Ghép cặp khác chữ | Cặp đã hoàn tất và ký tự chờ ghép | $O(N)$ |
| dpstring08 | Tránh mẫu aba | Xóa ký tự; ba trạng thái đuôi viết trực tiếp | $O(N)$ |
| dpstring09 | Bốn màu cách biệt | Chi phí thay ký tự; lưu hai màu cuối | $O(4^3N)$ |

`dpstring00` là bài khởi động và cũng có lời giải tham lam. `dpstring02` có thể giải bằng cách giữ ký tự đắt nhất trong từng nhóm giống nhau liên tiếp; bài dùng để luyện cách xây dựng trạng thái trước khi chuyển sang các điều kiện phức tạp hơn. Không giới hạn phương pháp giải của học sinh. Hai bài cuối phù hợp cuối nhóm; không yêu cầu KMP hoặc kiến thức automaton tổng quát.

Mỗi bài có hai ví dụ, `task.md`, `solution.md`, lời giải C++11 và Python 3, bộ sinh test, verifier đầu vào, checker đầu ra và `hash.json`. Không thêm mục Subtask; `partial = true` là cấu hình chấm trong `[upload]`.

## Cấu hình

Tất cả các bài dùng `timelimit = 0.5` và:

```toml
[upload]
time_limit = 0.5
group = '03'
classes = 'C'
types = ['dp_string']
allowed_languages = ['PY3', 'CPP11', 'CPP14', 'CPP17', 'CPP20', 'JAVA8', 'C', 'PAS']
partial = true
```

Giới hạn độ dài là 50.000, riêng `dpstring09` là 10.000. Điểm và chi phí từ 0 đến $10^9$; các lời giải dùng số nguyên 64 bit khi cần.

## Sinh và kiểm tra

Từ thư mục gốc dự án:

```sh
python3 custom/dpstring_tests/check.py
python3 custom/dpstring_tests/check.py --problem dpstring07
```

Chỉ khi chủ động thay đổi dữ liệu test và cần ghi lại mã băm:

```sh
python3 custom/dpstring_tests/check.py --update-hashes
```

Quy trình gọi riêng các bước của `Problem`, không xuất HTML và không kết nối máy chủ. Mỗi bài có 32 test: 2 ví dụ, 10 biên, 8 nhỏ, 6 ngẫu nhiên và 6 lớn. Bộ kiểm tra thực hiện:

- Biên dịch lời giải C++ theo C++11; biên dịch các công cụ theo C++17.
- Sinh lại và xác thực toàn bộ đầu vào; tạo đáp án; chấm cả C++ và Python theo giới hạn 0,5 giây cho mỗi lần chạy.
- Đối chiếu tất cả đáp án bằng lời giải Python viết theo cách lưu trạng thái khác; vét cạn 20 test ví dụ/biên/nhỏ của mỗi bài.
- Vét cạn các xâu ngắn và kiểm tra thêm 100 trường hợp ngẫu nhiên cho mỗi bài bằng cách liệt kê phương án.
- Kiểm tra verifier từ chối dữ liệu sai, checker nhận đáp án đúng và từ chối đáp án sai, rỗng hoặc có token dư.
- Kiểm tra độ dài tối đa, đáp án vượt số nguyên 32 bit, tính tái lập của bộ sinh và mã băm.
- Đối chiếu tiêu đề, thứ tự heading, các ví dụ trong đề và toàn bộ cấu hình `[upload]`.

Các test lớn bao gồm xâu đồng nhất, xen kẽ, theo nhóm, ngẫu nhiên, điểm 0, điểm cực đại và chi phí lệch nhau. Riêng bài điền tín hiệu có toàn dấu `?`, ký tự cố định và chi phí có hướng; bài tránh `aba` có chuỗi `abba` để kiểm tra việc xóa có thể tạo ra mẫu cấm; bài ghép cặp có các cặp sát nhau như `abba`.
