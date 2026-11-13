# DPSTR6xx — Nhóm 7: DP trên đoạn, xâu đối xứng

Bộ bài dành cho lộ trình từ nhập môn DP trên đoạn tới các biến thể khó. Mọi bài đều xoay quanh đoạn trong và hai đầu xâu; không yêu cầu học sinh biết Manacher, hashing, suffix array hay cây palindrome. Những thuật toán khác vẫn được chấp nhận nếu cho đáp án đúng trong giới hạn.

## Phân nhóm DP xâu đã thống nhất

| Nhóm | Nội dung |
| --- | --- |
| 1 | DP một chiều trên xâu |
| 2 | Dãy con chung của hai xâu |
| 3 | Đoạn con liên tiếp chung |
| 4 | Đếm cách tạo dãy con |
| 5 | Chia xâu thành các đoạn hợp lệ |
| 6 | Biến đổi một xâu thành xâu khác |
| 7 | DP trên đoạn — xâu đối xứng |

## Mã bài và mức độ

| Dải mã | Mức độ |
| --- | --- |
| dpstr600–629 | Dễ / nhập môn |
| dpstr630–649 | Trung bình |
| dpstr650–699 | Khó |

| Mã | Tên bài | Nội dung | Giới hạn | Cận tính toán chính |
| --- | --- | --- | --- | --- |
| [dpstr600](../dpstr600/task.md) | Hỏi đoạn đối xứng | Bảng đối xứng và truy vấn tĩnh | N ≤ 5000, Q ≤ 500000 | 13.002.500 ô và truy vấn |
| [dpstr601](../dpstr601/task.md) | Đoạn gương dài nhất | Đoạn liên tiếp dài nhất, ưu tiên vị trí đầu nhỏ nhất | N ≤ 5000 | 12.502.500 ô |
| [dpstr602](../dpstr602/task.md) | Đếm đoạn gương | Đếm đoạn liên tiếp theo hai đầu mút | N ≤ 5000 | 12.502.500 ô |
| [dpstr603](../dpstr603/task.md) | Giữ lại thông điệp đối xứng | Độ dài dãy con đối xứng dài nhất | N ≤ 5000 | 12.502.500 ô |
| [dpstr630](../dpstr630/task.md) | Chèn chữ tạo gương | Số ký tự cần chèn ít nhất | N ≤ 5000 | 12.502.500 ô |
| [dpstr631](../dpstr631/task.md) | Xóa chữ có chi phí | Chi phí xóa theo từng vị trí | N ≤ 5000 | 37.507.500 lựa chọn |
| [dpstr632](../dpstr632/task.md) | Đếm cách giữ xâu đối xứng | Dãy con không rỗng, đếm theo bộ vị trí | N ≤ 5000 | 12.502.500 ô |
| [dpstr650](../dpstr650/task.md) | Sửa bản tin thành gương | Xóa hoặc thay, chi phí theo vị trí ban đầu | N ≤ 5000 | 37.507.500 lựa chọn |
| [dpstr651](../dpstr651/task.md) | Đối xứng với ít lần thay chữ | Dãy con dài nhất với không quá K lần thay | N ≤ 4000, K ≤ 5 | 48.012.000 trạng thái |
| [dpstr652](../dpstr652/task.md) | Những xâu đối xứng khác nhau | Đếm nội dung dãy con đối xứng phân biệt | N ≤ 5000 | 12.502.500 ô |

Cận thiết kế không vượt $5\cdot10^7$ trạng thái/lựa chọn chính, không phải số lệnh CPU. Giới hạn độ dài dùng các mốc tròn. Các bài 632 và 652 lấy modulo $10^9+7$; các bài còn lại in chính xác, riêng chi phí ở 631/650 cần số nguyên 64 bit.

Mỗi bài có `task.md` theo mẫu knapsack, hai ví dụ, lời giải có chứng minh và độ phức tạp, code C++11, bộ sinh, verifier, checker, `hash.json` và lệnh kiểm tra riêng. Không thêm Subtask, không xuất HTML.

## Các điểm cần phân biệt

- 600–602 xét **đoạn liên tiếp**; 603 và các bài dãy con cho phép bỏ ký tự bên trong.
- 601 chọn vị trí đầu nhỏ nhất khi nhiều đoạn cùng dài nhất; đáp án vì vậy được xác định duy nhất.
- 602 đếm theo vị trí đầu–cuối, không đếm nội dung phân biệt; đoạn một ký tự được tính, đoạn rỗng không được tính.
- 631 vẫn phải xét xóa một đầu khi hai đầu cùng chữ. Ví dụ `aaba`, chi phí `1 100 1000 1`: xóa chữ đầu giá 1 tốt hơn giữ cả hai đầu rồi xóa bên trong giá ít nhất 100. Bộ sinh có trường hợp này ở `edge_05.in`.
- 632 đếm bộ vị trí: `aaa` có 7 cách; 652 đếm nội dung: `aaa` chỉ có 3 nội dung.
- 650 chỉ xử lý từng vị trí ban đầu bằng một lựa chọn giữ/xóa/thay. Chi phí không đổi sau khi xóa vị trí khác; không chèn chữ.
- 651 dùng **không quá** K lần thay, không phải đúng K. Mỗi cặp ký tự khác nhau được giữ ở hai đầu cần đúng một lần thay; các cặp đã bằng nhau không cần thay.

## Cấu hình

Tất cả các bài đặt `timelimit = 1.0` và:

```toml
[upload]
time_limit = 1.0
memory_limit = 131072
group = '03'
classes = 'C'
types = ['dp_string', 'dp_palindrome']
allowed_languages = ['PY3', 'CPP11', 'CPP14', 'CPP17', 'CPP20', 'JAVA8', 'C', 'PAS']
partial = true
```

Bộ nhớ là 128 MiB. Bảng một byte của bài 600 chiếm 25 MB; bảng số dư 32 bit của bài 652 chiếm 100 MB ở cận lớn; các bài còn lại nén theo hàng. Các đáp án đều duy nhất nên dùng checker `standard` khi upload; checker cục bộ 600 so sánh các token `YES/NO`, những bài còn lại so sánh số nguyên và từ chối token dư.

Việc tạo bài và kiểm tra không kết nối máy chủ. Hiệu năng ghi nhận là của C++11 trên máy cục bộ, không khẳng định mọi cách cài đặt trong mọi ngôn ngữ được phép đều đạt giới hạn.

## Sinh và kiểm tra

Từ thư mục gốc dự án:

```sh
python3 custom/dpstr_palindrome_tests/check.py
python3 custom/dpstr_palindrome_tests/check.py --problem dpstr631 dpstr652
python3 custom/dpstr651/tests/check.py
```

Chỉ dùng lệnh sau khi đã chủ động thay dữ liệu và cần ghi lại mã băm:

```sh
python3 custom/dpstr_palindrome_tests/check.py --update-hashes
```

Quy trình gọi trực tiếp các bước sinh và kiểm tra của `Problem`, bỏ bước HTML. Mỗi bài có **34 cặp test**: 2 ví dụ, 12 biên, 8 nhỏ, 6 ngẫu nhiên, 6 lớn. Tổng cộng **340 cặp**, tương ứng **680 mục mã băm**.

Các bước kiểm tra:

- Biên dịch lời giải bằng C++11 và công cụ bằng C++17, cảnh báo coi là lỗi. Sinh toàn bộ đầu vào, xác thực, tạo đáp án và kiểm tra bằng checker; chạy lời giải theo đúng giới hạn 1 giây đã cấu hình.
- Đối chiếu toàn bộ đáp án với `oracle.cpp`. Các bài 600–602 dùng bán kính Manacher; 603/630 dùng LCS với xâu đảo; 631/650 tối đa lợi ích giữ lại thay vì tối thiểu chi phí xử lý; 632 cộng các cách mới theo cặp vị trí ngoài cùng thay vì công thức cộng–trừ; 651 tối thiểu số xóa theo ngân sách thay, giữ các bảng đoạn đầy đủ; 652 nhóm nội dung theo chữ ngoài cùng với các vị trí biên rộng nhất, thay vì truy hồi khử trùng theo hai đầu.
- Vét cạn 22 test ví dụ/biên/nhỏ mỗi bài. Với đoạn liên tiếp, liệt kê đoạn và đảo trực tiếp; với dãy con, liệt kê mọi tập vị trí. Với 650/651, tính riêng chi phí hoặc số cặp ký tự khác nhau của từng dãy được chọn. Bài 652 lưu tập nội dung để loại trùng.
- Xét mọi xâu nhị phân dài 1 đến 6, thêm 120 xâu ngẫu nhiên mỗi bài và các trường hợp đặc trưng. Riêng 651 xét thêm nhiều lớp K trên từng xâu, kể cả K = 0 và K = 5.
- So với công thức đóng trên xâu đồng nhất: N(N+1)/2 đoạn liên tiếp; $2^N-1$ bộ vị trí không rỗng; đúng N nội dung đối xứng phân biệt. Có test chi phí vượt 32 bit, số đếm buộc lấy modulo, sửa miễn phí và xóa miễn phí.
- Thử verifier bằng dữ liệu sai độ dài, ký tự, chỉ số truy vấn, chi phí, K, thiếu/thừa dữ liệu. Thử checker bằng đáp án đúng, sai, rỗng, thiếu/thừa token; bài 601 thử sai vị trí ưu tiên, bài 600 thử sai cả đầu/cuối danh sách trả lời.
- Kiểm tra đồng thời N = 5000 và Q = 500000 ở bài 600, gồm các test hỏi toàn đoạn và các test chủ yếu hỏi đoạn dài; N và K cực đại ở bài 651; giới hạn bộ nhớ tường minh; cấu hình upload; cấu trúc đề và ví dụ; tính tái lập của mọi seed; toàn bộ mã băm.

Kết quả lần kiểm tra cả bộ nằm trong `results.md`. Nếu chỉ chạy một phần, báo cáo nằm tại `tests/results.md` của bài đầu tiên được chọn. Các lần đo này phục vụ kiểm tra cục bộ; máy judge có thể có hiệu năng khác.
