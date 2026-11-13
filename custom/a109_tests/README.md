# 10 bài nhập môn đọc struct từ tệp nhị phân

Các mã `a109000001`–`a109000010` luyện đọc bản ghi có định dạng cố định. Thuật toán chỉ dùng vòng lặp, điều kiện, phép tính cơ bản và mảng cố định. Các trường dữ liệu dùng `char`, `unsigned char`, `unsigned short`, `int`, `unsigned int`, `long long`; không dùng các kiểu có hậu tố `_t`. Lời giải học sinh không dùng `vector`, `string`, sắp xếp hay cấu trúc dữ liệu nâng cao.

| Mã | Tên bài | Thao tác chính |
| --- | --- | --- |
| [A109000001](../a109000001/task.md) | Tổng giá trị trong tệp | Đọc đến EOF, tính tổng |
| [A109000002](../a109000002/task.md) | Đếm học sinh đạt yêu cầu | Đọc phần đầu và đếm |
| [A109000003](../a109000003/task.md) | Tổng tiền hàng | Nhân số lượng với đơn giá, cộng tổng |
| [A109000004](../a109000004/task.md) | Học sinh có tổng điểm cao nhất | Mảng ký tự, ba điểm, tìm lớn nhất |
| [A109000005](../a109000005/task.md) | Số dư cuối ngày | Bản ghi có loại giao dịch, cộng trừ |
| [A109000006](../a109000006/task.md) | Thống kê ba loại sản phẩm | Cộng vào ba tổng |
| [A109000007](../a109000007/task.md) | Các điểm trên mặt phẳng | Phân loại bằng dấu tọa độ |
| [A109000008](../a109000008/task.md) | Tổng thời gian hoạt động | Đọc đến EOF, lọc trạng thái |
| [A109000009](../a109000009/task.md) | Sách còn trong kho | Lọc vào mảng, in đúng thứ tự |
| [A109000010](../a109000010/task.md) | Ngày có nhiệt độ cao nhất | Đọc struct lồng nhau, tìm lớn nhất |

## Định dạng và cách chạy

Các đề dùng cách trình bày gọn theo bài A109000004: mô tả đầu vào, khai báo struct theo từng trường, đầu ra, ràng buộc và ví dụ. Chỉ đề A109000001 có hướng dẫn cách mở, đọc và ghi tệp nhị phân; các đề còn lại nêu định dạng dữ liệu cần xử lý.

Đầu vào `.in` là **tệp nhị phân thật**, không phải số viết dưới dạng văn bản. Mỗi đề mô tả đầy đủ phần đầu, thứ tự trường, kích thước bản ghi và kích thước toàn tệp. Số nguyên dùng little-endian, kiểu có dấu dùng bù hai. Máy chấm có byte 8 bit, `int`/`unsigned int` 4 byte, `long long` 8 byte, `unsigned short` 2 byte. Các bản ghi dùng cách bố trí `struct` mặc định của C++, đọc và ghi bằng `sizeof`. Ba bài A109000005, A109000006 và A109000008 có byte đệm do căn chỉnh trường; kích thước và vị trí trường được ghi rõ trong đề. Các byte đệm không mang dữ liệu cần xử lý.

Ở các bài A109000003, A109000004, A109000006, A109000007 và A109000009, số lượng $N$ là một số nguyên `int` ghi riêng ở đầu tệp và được đọc trực tiếp bằng `fin.read((char*)&n, sizeof(n))`. Không cần struct riêng chỉ để chứa số lượng bản ghi.

Mỗi chương trình đọc tệp nhị phân **`MÃ_BÀI.INP`** và ghi tệp văn bản **`MÃ_BÀI.OUT`**, với mã viết hoa. Ví dụ: `A109000001.INP` và `A109000001.OUT`. Các tệp được mở trong thư mục chạy chương trình; tên tệp phân biệt chữ hoa và chữ thường. Lời giải dùng `ifstream` với `ios::binary` và `ofstream`, không đọc từ bàn phím hoặc in kết quả ra màn hình.

Mỗi đề có hai ví dụ. `Sample Input` hiển thị các byte theo hệ hex để người đọc quan sát được. Các dấu cách và xuống dòng trong bản hiển thị không nằm trong tệp thật. Hai tệp mẫu thật được lưu tại `gen/example_00.in`, `gen/example_01.in`; khi dùng, sao chép hoặc đổi tên thành tên `.INP` mà đề yêu cầu.

Ví dụ biên dịch, tạo tệp đầu vào từ phần hex của đề và chạy bài 1, bắt đầu ở thư mục gốc dự án:

```sh
g++ -O2 -std=c++11 custom/a109000001/sol/correct.cpp -o /tmp/a109-demo
python3 custom/a109_tests/sample_binary.py a109000001 1 /tmp/A109000001.INP
cd /tmp
./a109-demo
cat A109000001.OUT
```

Tệp `A109000001.OUT` chứa `9`. Tệp đầu vào được mở ở chế độ nhị phân, giữ nguyên các byte điều khiển trên cả Windows.

## Thành phần mỗi bài

- `task.md`: đề tiếng Việt, đúng thứ tự heading của mẫu knapsack, hai ví dụ và giải thích cuối bài; không có subtask.
- `solution.md` và `sol/correct.cpp`: ý tưởng, chứng minh, độ phức tạp và chương trình C++11 độc lập.
- `format.h`: khai báo struct thông thường và kiểm tra kích thước dùng cho bộ sinh và verifier.
- `gen/`: hai đầu vào mẫu nhị phân và bốn nhóm sinh dữ liệu.
- `verifier.cpp`: kiểm tra các byte đầu vào, giới hạn, độ dài và các trường cố định.
- `checker.cpp`: so sánh token đầu ra, không đọc các trường của đầu vào nhị phân.
- `info.toml`, `hash.json`, `tests/check.py`: cấu hình, hash và lệnh kiểm thử.

Các chương trình sinh và kiểm tra dùng chung mã nguồn trong thư mục `a109_tests`. Khi sao chép bài để sinh lại dữ liệu, giữ cả thư mục dùng chung. `sol/correct.cpp` của từng bài tự chứa đầy đủ và có thể biên dịch riêng.

## Kiểm thử

Chạy từ thư mục gốc dự án:

```sh
python3 custom/a109_tests/check.py
python3 custom/a109000004/tests/check.py
```

Khi chủ động thay đổi bộ sinh hoặc đáp án, cập nhật hash bằng:

```sh
python3 custom/a109_tests/check.py --update-hashes
```

Quy trình không gọi xuất HTML, không yêu cầu cài thêm thư viện. Mỗi bài có **25 test chính**: 2 ví dụ, 8 test biên, 6 test nhỏ, 6 test ngẫu nhiên và 3 test lớn với 200.000 bản ghi. Tổng cộng 250 test chính và 600 trường hợp ngẫu nhiên bổ sung. Mọi lần chạy lời giải và verifier đều dùng giới hạn 1 giây. Với mỗi lượt chạy lời giải, quy trình tạo thư mục riêng, chép dữ liệu sang đúng tên `.INP`, đóng luồng vào chuẩn, chạy chương trình và đọc đúng tệp `.OUT`; đồng thời yêu cầu chương trình không in kết quả ra luồng ra chuẩn. Trình chạy chung trong `problem.py` cũng dùng ba trường I/O trong `[upload]` để đọc/ghi đúng tên tệp khi sinh đáp án và kiểm tra lời giải.

Các phép kiểm tra bao gồm:

- Đọc các byte bằng mô hình Python `struct` độc lập với lời giải C++, tính lại và so sánh đáp án trên toàn bộ test chính và các test bổ sung.
- Biên dịch và chạy lời giải bằng cả C++11, C++14, C++17, C++20.
- Từ chối tệp thiếu hoặc thừa byte, sai số bản ghi, vượt giới hạn, giá trị trường không hợp lệ, mã rỗng, ký tự sai hoặc byte đệm sau mã không hợp lệ.
- Kiểm tra các byte đệm căn chỉnh của struct có thể chứa giá trị bất kỳ, không ảnh hưởng dữ liệu; kiểm tra chữ ký `A109`, ngày tháng, loại giao dịch và trạng thái; chấp nhận mã đủ 8/12 ký tự không có byte kết thúc.
- Kiểm tra tệp rỗng ở hai bài cho phép đọc đến EOF; kiểm tra tổng 64 bit, số âm, dữ liệu hòa, số lượng bằng 0 và các trục tọa độ.
- Kiểm tra checker chấp nhận đáp án đúng với khoảng trắng khác, từ chối đáp án sai, thiếu và thừa token.
- Đối chiếu byte ví dụ trong đề với tệp mẫu và đáp án, cấu trúc heading, cấu hình upload, tính tái lập của bộ sinh và SHA-256 của mọi tệp `.in`/`.out`.

`in/`, `out/` và các chương trình đã biên dịch là sản phẩm sinh lại được. Dữ liệu đầu vào vẫn được giữ dưới dạng byte nhị phân khi tạo hash hoặc đóng gói ZIP; không mở bằng trình xử lý văn bản rồi lưu lại. Không chạy nhánh chuẩn hóa xuống dòng dành cho tệp văn bản trên Windows với dữ liệu này.

## Cấu hình upload

Tất cả các bài dùng `timelimit = 1.0`. Ví dụ cấu hình bài A109000001; các bài khác thay tên tệp bằng đúng mã bài viết hoa:

```toml
[upload]
time_limit = 1
group = '01'
classes = 'A'
types = ['intro_files']
partial = true
allowed_languages = ['CPP11', 'CPP14', 'CPP17', 'CPP20']
io_method = 'file'
io_input_file = 'A109000001.INP'
io_output_file = 'A109000001.OUT'
binary_data = true
```

Chưa thực hiện tải bài lên máy chủ.

## Cấu hình file I/O trên máy chấm

Theo bản mới của [PROBLEM_IMPORT_API.md](../../PROBLEM_IMPORT_API.md), API tạo/cập nhật đề hỗ trợ `io_method`, `io_input_file`, `io_output_file`. Cả 10 bài đã đặt `io_method = 'file'` và tên tệp đúng như đề trong `[upload]`. Công cụ upload gửi ba trường I/O cùng thông tin đề, còn `binary_data = true` được gửi trong manifest của request upload testcase. Cả 10 bài đã bật rõ cờ này; backend lưu cờ để giữ nguyên byte qua những lần cập nhật sau.

`input_file` và `output_file` trong manifest vẫn là đường dẫn của hai tệp testcase trong ZIP. Bởi vậy các tên trong ZIP vẫn là `example_00.in`, `example_00.out`, v.v.; tên tệp khi chấm là `A109000001.INP`/`A109000001.OUT`, tương tự cho các bài còn lại.

Có thể dùng lệnh upload thông thường để gửi cả tên tệp cùng đề và testcase. Nếu chỉ cập nhật thông tin đề, tên tệp và lời giải, giữ bộ test trên máy chủ, dùng `--skip-testcase`. Không dùng `--skip-statement` khi cần gửi thay đổi I/O, vì tùy chọn này bỏ qua cấu hình đề. Ngày 07/11/2026 đã sửa cờ giữ nguyên byte trực tiếp trên máy chấm `tmath` cho 9 bài đã có dữ liệu, như phần dưới.

## Sự cố random_00 của A109000001 trên máy chấm

Máy chấm DMOJ phải có cấu hình sau trong `init.yml` của mỗi bài có dữ liệu nhị phân:

```yaml
binary_data: true
```

Chế độ `file_io` chỉ đặt tên tệp vào/ra, không tự bật `binary_data`. Nếu thiếu cờ này, DMOJ chuẩn hóa xuống dòng và làm thay đổi các byte trong bản ghi. Với `random_00` của A109000001, có 2.781 bản ghi, tổng đúng là 1223. Có 16 bản ghi có `value = 13`; chuẩn hóa byte `0D` thành `0A` biến các giá trị này thành 10, khiến chương trình trả `1223 - 16 * 3 = 1175`. File ZIP và đáp án lưu sẵn vẫn đúng; lỗi phát sinh khi máy chấm nạp đầu vào.

Đã bật cờ trên `/mnt/problems/a109000001/init.yml` đến `/mnt/problems/a109000009/init.yml` của `tmath`. Cấu hình cũ được sao lưu tại `/home/ubuntu/a109-binary-backup-20261107T065513Z`. A109000010 chưa có thư mục dữ liệu trên máy chấm tại thời điểm kiểm tra.

Đã chạy 225 test bằng bộ nạp testcase thực tế của DMOJ trong container `epsilon` và biên dịch/chạy các lời giải C++11: tất cả đều đạt. `random_00` sau sửa cho 1223. Kiểm tra thêm bộ nạp dữ liệu của `gamma`, `beta` cũng giữ nguyên đúng 22.248 byte của test này, với SHA-256 `c4b7662b96cad05d0a8eec3ef9a7319c1492c7919c7a58e5a7228a7be131ebb8`.

Bản API mới đã hỗ trợ `binary_data` trong manifest testcase và lưu vào database. Lệnh `-u` hiện gửi cờ từ `[upload].binary_data = true`, nên không cần sửa tay `init.yml` sau mỗi lần nhập test. API giữ cờ qua nhập ZIP không gửi cờ, upload checker, đổi I/O và tái tạo pretest; cần triển khai migration `0252_problemdata_binary_data` theo tài liệu API. Cờ cũng được gửi khi dùng `--skip-statement`; `--skip-testcase` và `--only-editorial` không thay đổi cờ vì không gửi bộ test. Các kết quả chấm cũ cần chấm lại hoặc nộp lại để sử dụng cấu hình mới.
