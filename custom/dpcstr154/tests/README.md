# Kiểm thử DPCSTR154

Bài `DPCSTR154 — Hai bản ghi lệch độ dài` thuộc nhóm khó của dải `dpcstr100–199`. Kỹ thuật chính là đảo trạng thái LCS từ `dp[i][j] = len` thành `f[i][len] = vị trí kết thúc nhỏ nhất trong B`, kết hợp bảng `next` và nén DP theo hàng.

## Chạy kiểm tra

Từ thư mục gốc dự án:

```sh
python3 custom/dpcstr154/tests/check.py
```

Chỉ khi chủ động thay đổi dữ liệu và cần cập nhật mã băm:

```sh
python3 custom/dpcstr154/tests/check.py --update-hashes
```

Không dùng các chế độ xuất HTML, không cài thêm thư viện và không upload trong quá trình kiểm tra.

## Cấu hình và quy mô

- $N\le5000$, $M\le10^6$; không bắt buộc $N\le M$.
- Quy mô chính của lời giải là $26M+N(N+1)/2\le38502500$, dưới cận thiết kế $5\cdot10^7$.
- Thời gian 0,5 giây; bộ nhớ upload 131.072 KiB, tương đương 128 MiB. Bảng `next` đầy đủ dùng 104.000.104 byte tại cận lớn; cùng với hai xâu và DP một hàng, dữ liệu tường minh khoảng 101 MiB.
- `[upload]` giữ `group = '03'`, `classes = 'C'`, `types = ['dp_common_substring']`, `partial = true` và danh sách ngôn ngữ của bộ trước. Checker upload là `standard` vì đáp án là một số nguyên.
- Hiệu năng được đo bằng lời giải C++11 trên máy cục bộ; không suy ra rằng mọi cách cài đặt ở mọi ngôn ngữ được phép đều đạt giới hạn thời gian này.

## Bộ test

Có **37 cặp**: 3 ví dụ, 12 biên, 8 nhỏ, 6 ngẫu nhiên và 8 lớn.

Các test nhỏ bao gồm không có ký tự chung, dãy chung không liên tiếp, thứ tự đảo nhau, chữ lặp, $M<N$, lời giải chỉ có một ký tự và lựa chọn cách khớp sớm nhất có lợi cho việc mở rộng về sau.

Hai trường hợp đặc trưng:

- `A = ab`, `B = bb`, đáp án 1: bắt lỗi cập nhật độ dài tăng dần khiến chữ `b` của A bị sử dụng nhiều lần.
- `A = aa`, `B = ab`, đáp án 1: bắt lỗi tra lần xuất hiện không nằm sau vị trí đã dùng, khiến chữ `a` của B bị sử dụng nhiều lần.

Tám test lớn:

| Test | Cấu trúc | Đáp án |
| --- | --- | --- |
| max_00 | A dài 5.000 và B dài 1.000.000, cả hai ngẫu nhiên trên đủ 26 chữ | 5000 |
| max_01 | Hai xâu chỉ gồm `a`, cùng đạt cận tương ứng | 5000 |
| max_02 | A chỉ có `a`, B chỉ có `b` | 0 |
| max_03 | A dùng đủ 26 chữ, toàn bộ A xuất hiện sát cuối B | 5000 |
| max_04 | A là khối `a` rồi `b`; B là khối `b` rồi `a` | 2500 |
| max_05 | A chỉ có `a`; B chỉ có một `a` tại vị trí cuối | 1 |
| max_06 | A xen kẽ `ab`; B chỉ có `ab` ở hai vị trí cuối và các chữ `z` trước đó | 2 |
| max_07 | A có 5.000 chữ `a`, B chỉ có một chữ `a` | 1 |

Các test cực đại phân biệt thời gian $O(NM)$ với cách đảo trạng thái và kiểm tra bảng `next` ở vị trí gần $M$, $M$ và trường hợp không tìm được ký tự tiếp theo.

## Đối chiếu độc lập

Lời giải chuẩn không dùng chung thuật toán với `tests/oracle.cpp`. Oracle tính LCS bằng phép toán bit, lưu các vị trí của A trong các từ 64 bit và quét B. Phép trừ nhiều từ có xử lý nhớ mượn giữa các từ. Mọi đáp án đã sinh đều được đối chiếu bằng oracle này.

23 test ví dụ/biên/nhỏ được kiểm tra thêm bằng cách liệt kê các dãy con của xâu ngắn hơn và quét xâu còn lại. Kiểm tra bổ sung gồm mọi cặp xâu nhị phân dài từ 1 đến 4, 120 trường hợp ngẫu nhiên và các độ dài ở biên 63/64/65, 127/128/129, 255/256/257. Các trường hợp biên từ 64 bit được đối chiếu thêm bằng DP LCS hai tiền tố thông thường để xác thực oracle.

Verifier được thử với sai độ dài, chữ cái sai, xâu rỗng, thiếu/thừa token và vượt giới hạn riêng của N hoặc M. Checker được thử với đáp án đúng/sai, ngoài cận, rỗng và dư token, bao gồm các đáp án sai 2 của hai trường hợp tái sử dụng ký tự ở trên.

Quy trình còn kiểm tra cấu trúc đề theo mẫu knapsack, các ví dụ, nội dung lời giải, cấu hình upload, tính tái lập của từng seed và `hash.json`. Kết quả gần nhất nằm tại `tests/results.md`.
