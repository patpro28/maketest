# DPSTR2xx — DP đoạn con liên tiếp chung

## Mã bài và giới hạn

| Dải mã | Mức độ |
| --- | --- |
| dpstr200–dpstr229 | Dễ, nhập môn |
| dpstr230–dpstr249 | Trung bình |
| dpstr250–dpstr299 | Khó, mở rộng |

| Mã | Tên bài | Giới hạn | Thuật toán chuẩn | Cận quy mô |
| --- | --- | --- | --- | --- |
| [dpstr200](../dpstr200/task.md) | Đoạn tin trùng nhau | $N,M\le5000$ | Độ dài đoạn khớp kết thúc, $O(NM)$ | 25.000.000 ô |
| [dpstr201](../dpstr201/task.md) | Định vị đoạn tin | $N,M\le5000$ | DP và ưu tiên vị trí bắt đầu | 25.000.000 ô |
| [dpstr202](../dpstr202/task.md) | Đoạn tin có dấu mốc | $N,M\le5000$ | DP và vị trí gần nhất của chữ bắt buộc | 25.000.000 ô |
| [dpstr203](../dpstr203/task.md) | Đọc ngược thông điệp | $N,M\le5000$ | Đảo xâu rồi DP đoạn khớp | 25.000.000 ô |
| [dpstr230](../dpstr230/task.md) | Đoạn tin giá trị | $N,M\le5000$ | Điểm đoạn khớp kết thúc, cho phép bắt đầu lại | 25.000.000 ô |
| [dpstr231](../dpstr231/task.md) | Bản sao có lỗi | $N,M\le2500$, $K\le5$ | DP với giới hạn số lỗi | 37.500.000 trạng thái |
| [dpstr232](../dpstr232/task.md) | Đếm đoạn tin chung | $N,M\le5000$ | Tổng độ dài khớp ở mọi cặp vị trí cuối | 25.000.000 ô |
| [dpstr250](../dpstr250/task.md) | Ba bản ghi | $N,M,P\le350$ | DP ba xâu, nén theo lớp | 42.875.000 ô |
| [dpstr251](../dpstr251/task.md) | Hai mảnh thông điệp | $N,M\le4000$ | Đoạn tốt nhất trong tiền tố và đoạn bắt đầu ở hậu tố | Cận thiết kế $3NM\le48.000.000$ |
| [dpstr252](../dpstr252/task.md) | Khôi phục bản tin có điểm | $N,M\le2500$, $K\le5$ | DP điểm có giới hạn số lỗi | 37.500.000 trạng thái |

Mọi bài giữ cận thiết kế không quá $5\cdot10^7$. Số này tính quy mô trạng thái/lượt duyệt chính, không phải số lệnh CPU. Lời giải 251 thực tế gộp thành hai lượt duyệt; bảng tiền tố dùng `uint16_t`, khoảng 32 MB. Các bài khác nén theo hàng hoặc lớp. Điểm và đáp án đếm dùng số nguyên 64 bit.

Mỗi thư mục có đề `task.md` đúng cấu trúc knapsack, 2 ví dụ, `solution.md` gồm thuật toán/chứng minh/độ phức tạp, lời giải `sol/correct.cpp`, bộ sinh, verifier, checker, `hash.json` và lệnh kiểm tra riêng. Không thêm mục Subtask và không xuất HTML.

## Những quy ước đã chốt trong đề

- Tất cả các đoạn đều phải liên tiếp; không được bỏ ký tự bên trong đoạn.
- Bài 201 in duy nhất bộ `L l_A l_B`, ưu tiên độ dài, rồi vị trí trong A, rồi vị trí trong B. Không có ký tự chung in `0 0 0`. Dùng checker so sánh số nguyên vì đáp án đã được xác định duy nhất.
- Bài 202 yêu cầu chữ bắt buộc nằm trong đoạn được chọn; không có đáp án in `-1`.
- Bài 230 và 252 có điểm âm; cho phép đoạn rỗng điểm 0. Mỗi lần xuất hiện được tính điểm riêng.
- Bài 231 và 252 đếm số cặp khác nhau ở cùng độ lệch, không có phép chèn/xóa bên trong đoạn.
- Bài 232 đếm theo vị trí và độ dài, không đếm các nội dung xâu phân biệt, không lấy modulo.
- Bài 251 chọn đúng hai mảnh không rỗng theo cùng thứ tự trong hai xâu. Các mảnh được đứng sát nhau và được giống nhau về nội dung; nếu không chọn đủ hai mảnh thì in `-1`.

## Cấu hình upload

Tất cả bài dùng `timelimit = 1.0` và:

```toml
[upload]
time_limit = 1.0
group = '03'
classes = 'C'
types = ['dp_string', 'dp_common_substring']
allowed_languages = ['PY3', 'CPP11', 'CPP14', 'CPP17', 'CPP20', 'JAVA8', 'C', 'PAS']
partial = true
```

Các bài dùng checker `standard` khi upload. Quy trình tạo bộ bài không gửi dữ liệu lên máy chủ. Lời giải được chấm hiệu năng trong bộ kiểm tra là C++11; danh sách ngôn ngữ được phép không có nghĩa đã đo lời giải ở mọi ngôn ngữ. Giới hạn 1 giây được kiểm tra trên máy cục bộ; máy judge có thể có hiệu năng khác.

## Sinh và kiểm tra

Từ thư mục gốc dự án:

```sh
python3 custom/dpstr_substring_tests/check.py
python3 custom/dpstr_substring_tests/check.py --problem dpstr251 dpstr252
python3 custom/dpstr201/tests/check.py
```

Chỉ khi chủ động thay đổi test và cần cập nhật mã băm:

```sh
python3 custom/dpstr_substring_tests/check.py --update-hashes
```

Mỗi bài có **34 cặp test nền**: 2 ví dụ, 12 biên, 8 nhỏ, 6 ngẫu nhiên và 6 lớn. Riêng `dpstr230` có thêm `regression_00`, tổng cộng 35 cặp, để kiểm tra việc bỏ ký tự đầu điểm âm và chỉ lấy ký tự cuối điểm dương. Cả bộ có **341 cặp**, tương ứng 682 mục trong các file `hash.json`. Chi tiết test bổ sung ở `custom/dpstr230/tests/README.md`.

Bộ kiểm tra gọi riêng các bước của `Problem`, bỏ bước HTML, không cài thêm thư viện, không kết nối máy chủ. Các bước gồm:

- Biên dịch lời giải theo C++11; biên dịch công cụ theo C++17 với cảnh báo được coi là lỗi.
- Sinh lại mọi đầu vào, chạy verifier, tạo đáp án và đối chiếu với checker. Chạy lời giải trên từng test với thời gian tối đa 1 giây.
- Đối chiếu tất cả đáp án bằng oracle độc lập: duyệt đường chéo cho các bài hai xâu; cửa sổ theo vị trí lỗi cho 231; tổng tiền tố và deque cực tiểu cho 252; giao các tập đoạn theo độ dài và tìm kiếm nhị phân cho 250; DP tiến theo mảnh đang ghép cho 251.
- Vét cạn 22 test ví dụ/biên/nhỏ mỗi bài bằng cách liệt kê trực tiếp hai vị trí bắt đầu và độ dài; bài 230 kiểm tra thêm test hồi quy, tổng cộng 23 test. Riêng 251 liệt kê mọi cặp mảnh có thứ tự và không giao nhau; 250 liệt kê các đoạn rồi kiểm tra xuất hiện trong cả ba xâu.
- Kiểm tra thêm mọi cặp xâu nhị phân độ dài từ 1 đến 3, thêm 100 trường hợp ngẫu nhiên và các trường hợp riêng cho từng dạng. Bài 250 dùng thêm bốn lựa chọn xâu thứ ba cho từng cặp.
- Kiểm tra công thức đóng trên các xâu đồng nhất, gồm đáp án vượt 32 bit: hai xâu 5.000 chữ `a` có 41.679.167.500 bộ đoạn chung.
- Thử verifier bằng dữ liệu sai cận, sai độ dài, sai chữ cái, thiếu/thừa token, $K$ ngoài cận, điểm và mức phạt ngoài cận.
- Thử checker bằng đáp án đúng, khoảng trắng hợp lệ, đáp án sai, token thiếu/thừa, kết quả rỗng và số 64 bit. Bài 201 kiểm tra riêng sai từng vị trí trong bộ đáp án.
- Kiểm tra mọi kích thước cùng đạt tối đa; riêng 231/252 có test đạt cả hai độ dài tối đa đồng thời $K=5$.
- Kiểm tra bộ sinh tái lập đúng từng file, cấu trúc đề và ví dụ, cấu hình upload, nội dung lời giải và `hash.json`.

Các test phân biệt LCS với đoạn liên tiếp, xâu không có ký tự chung, xâu đồng nhất, nhiều chữ lặp, nhiều đáp án hòa vị trí, lỗi trước/sau/giữa đoạn, $K=0$, mức phạt 0, điểm âm/0/cực đại, hai mảnh sát nhau, không đủ hai mảnh, chữ bắt buộc có trong tiền tố nhưng nằm ngoài đoạn khớp và đoạn chung chỉ xuất hiện trong hai trong ba xâu.

## Kết quả kiểm tra

Kết quả cả bộ và thời gian chậm nhất được ghi trong `results.md`. Khi chỉ chạy một phần bộ bài, kết quả riêng được ghi vào `tests/results.md` của bài được chọn đầu tiên; chẳng hạn kết quả sau khi bổ sung test cho 230 nằm tại `custom/dpstr230/tests/results.md`. Các mốc thời gian này chỉ phản ánh máy chạy kiểm tra, không thay thế việc đo trên máy judge.
